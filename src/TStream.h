// TStream.h
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

#include "TTerminal.h"

using namespace System;
using namespace System::Collections::Generic;

namespace JulMar
{
	namespace Tapi3
	{
		public ref class TStream : Internal::TapiBase
		{
		private:
			TStream(IUnknown* p) : Internal::TapiBase(p) {/* */}
		protected public:
			CComPtr<Native::ITStream> GetStreamItf() { return CastToInterface<Native::ITStream,true>(); }
			static TStream^ CreateStream(IUnknown* p);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TStream: {0} {1} {2}", Name, MediaType, Direction);
			}
			
			~TStream()
			{
				Release(false);
			}

			property TAPIMEDIATYPES MediaType
			{
				TAPIMEDIATYPES get()
				{
					long lValue;
					TapiException::ThrowExceptionForHR(GetStreamItf()->get_MediaType(&lValue));
					return (TAPIMEDIATYPES)lValue;
				}
			}

			property TERMINAL_DIRECTION Direction
			{
				TERMINAL_DIRECTION get()
				{
					Native::TERMINAL_DIRECTION dir;
					TapiException::ThrowExceptionForHR(GetStreamItf()->get_Direction(&dir));
					return (TERMINAL_DIRECTION) dir;
				}
			}

			property String^ Name 
			{
				String^ get()
				{
					CComBSTR bstrName;
					TapiException::ThrowExceptionForHR(GetStreamItf()->get_Name(&bstrName));
					return gcnew String((wchar_t*)bstrName);
				}
			}

			void StartStream()
			{
				TapiException::ThrowExceptionForHR(GetStreamItf()->StartStream());
			}

			void PauseStream()
			{
				TapiException::ThrowExceptionForHR(GetStreamItf()->PauseStream());
			}

			void StopStream()
			{
				TapiException::ThrowExceptionForHR(GetStreamItf()->StopStream());
			}

			void SelectTerminal(TTerminal^ term)
			{
				if (term == nullptr)
					throw gcnew ArgumentNullException("term");

				CComPtr<Native::ITTerminal> it = term->GetTerminalItf();
				TapiException::ThrowExceptionForHR(GetStreamItf()->SelectTerminal(it));
			}

			void UnselectTerminal(TTerminal^ term)
			{
				if (term == nullptr)
					throw gcnew ArgumentNullException("term");

				CComPtr<Native::ITTerminal> it = term->GetTerminalItf();
				TapiException::ThrowExceptionForHR(GetStreamItf()->UnselectTerminal(it));
			}

			property array<TTerminal^>^ Terminals
			{
				array<TTerminal^>^ get()
				{
					List<TTerminal^>^ retList = gcnew List<TTerminal^>();

					try
					{
						CComPtr<Native::IEnumTerminal> iePtr;
						TapiException::ThrowExceptionForHR(GetStreamItf()->EnumerateTerminals(&iePtr));

						CComPtr<Native::ITTerminal> termInfo;
						while (iePtr->Next(1, &termInfo, NULL) == S_OK)
						{
							retList->Add(TTerminal::CreateTerminal(termInfo));
							termInfo = NULL;
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retList->ToArray();
				}
			}

			TTerminal^ FindTerminal(TAPIMEDIATYPES mediaType, TERMINAL_DIRECTION direction)
			{
				array<TTerminal^>^ list = this->Terminals;
				if (list != nullptr)
				{
					for each (TTerminal^ term in list)
					{
						if (term->Direction == direction &&
							term->MediaType == mediaType)
							return term;
					}
				}
				return nullptr;
			}
		};
	}
}