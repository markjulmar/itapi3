// TapiException.h
//
// This is part of the ITAPI3 Managed Library for TAPI 3.x
//
// Copyright (c) 2006-2010 JulMar Technology, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
// persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

using namespace System;
using namespace System::Runtime::Serialization;
using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics;

namespace JulMar
{
	namespace Tapi3
	{
		public ref class TapiException : COMException
		{
		private:
			static TraceSource^ _trcOut = gcnew TraceSource("ITapiTrace");

		public:
			TapiException() : COMException() {/* */}
			TapiException(String^ s) : COMException(s) {/* */}
			TapiException(String^ s, Exception^ e) : COMException(s, e) {/* */}
			TapiException(SerializationInfo^ si, StreamingContext ctx) : COMException(si, ctx) {/* */}
			TapiException(String^ s, System::Int32 err) : COMException(s, err) {/* */}
			TapiException(HRESULT err) : COMException(TapiException::GetErrorString(err), err) {/* */}

		protected public:
			static void TraceOut(TraceEventType evtType, String^ formatBuffer, ... array<Object^>^ params)
			{
				_trcOut->TraceEvent(evtType, 0, String::Format(formatBuffer, params));
				_trcOut->Flush();
			}

			static String^ GetErrorString(HRESULT hr)
			{
				String^ retBuffer = nullptr;

				if (hr == E_NOINTERFACE)
					retBuffer = "The operation is not supported at this time.";
				else if (hr == E_FAIL)
					retBuffer = "The operation failed - E_FAIL";

				else if (FAILED(hr))
				{
					LPVOID lpBuffer;
					HMODULE hMod = LoadLibraryW(L"TAPI3.DLL");
					if (hMod != NULL)
					{
						if (FormatMessage(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ALLOCATE_BUFFER, 
							hMod, hr, 0, (LPTSTR)&lpBuffer, 256, NULL) > 0)
						{
							retBuffer = gcnew String((wchar_t*)lpBuffer);
							LocalFree(lpBuffer);
						}
						FreeLibrary(hMod);
					}

					if (retBuffer == nullptr)
					{
						if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 
							hMod, hr, 0, (LPTSTR)&lpBuffer, 256, NULL) > 0)
						{
							retBuffer = gcnew String((wchar_t*)lpBuffer);
							LocalFree(lpBuffer);
						}
					}
				}

				return retBuffer;
			}
			static void ThrowExceptionForHR(HRESULT hr)
			{
				if (!FAILED(hr))
					return;

				String^ errStr = GetErrorString(hr);

				System::Diagnostics::StackTrace^ st = gcnew System::Diagnostics::StackTrace();
				TraceOut(System::Diagnostics::TraceEventType::Error, 
					"COM Hresult 0x{0:X} \"{1}\" generated {2}", hr, errStr, st->ToString());

				if (errStr != nullptr)
					throw gcnew TapiException(errStr, hr);
				throw gcnew TapiException(String::Format("Unknown error 0x{0:X}", hr));
			}
		};
	}
}

