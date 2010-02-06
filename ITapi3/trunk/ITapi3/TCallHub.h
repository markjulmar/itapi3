// TCallHub.h
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
using namespace System::Threading;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

namespace JulMar
{
	namespace Tapi3 
	{
		public enum struct CALLHUB_STATE
		{	
			CHS_ACTIVE	= 0,
			CHS_IDLE	= ( CHS_ACTIVE + 1 ) 
		};

		public ref class TCallHub : Internal::TapiBase
		{
		private:
			TTapi^ _owner;
			TCallHub(TTapi^ owner, IUnknown* p) : Internal::TapiBase(p), _owner(owner) {/* */}
		protected public:
			static TCallHub^ CreateCallHub(TTapi^ owner, IUnknown* p);
			CComPtr<Native::ITCallHub> GetCallHubItf() { return CastToInterface<Native::ITCallHub,true>(); }
		public:
			virtual String^ ToString() override
			{
				return String::Format("TCallHub: Calls={0}", NumCalls);
			}

			~TCallHub()
			{
				Release(false);
			}

			void Clear()
			{
				TapiException::ThrowExceptionForHR(GetCallHubItf()->Clear());
			}

			property array<TCall^>^ Calls
			{
				array<TCall^>^ get()
				{
					return EnumerateCalls();
				}
			}

			property long NumCalls
			{
				long get()
				{
					long lValue;
					if (SUCCEEDED(GetCallHubItf()->get_NumCalls(&lValue)))
						return lValue;
					return 0;
				}
			}

			property CALLHUB_STATE State
			{
				CALLHUB_STATE get()
				{
					Native::CALLHUB_STATE ch;
					TapiException::ThrowExceptionForHR(GetCallHubItf()->get_State(&ch));
					return (CALLHUB_STATE) ch;
				}
			}
		private:
			array<TCall^>^ EnumerateCalls();

		};
	}
}