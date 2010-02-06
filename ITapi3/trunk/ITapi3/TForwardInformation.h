// TForwardInformation.h
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
		// Forward declaration
		ref class TTapi;
		ref class TCall;

		[Flags]
		public enum struct LINEFORWARDMODES
		{
			Unconditional = LINEFORWARDMODE_UNCOND,
			UnconditionalInternal = LINEFORWARDMODE_UNCONDINTERNAL,
			UnconditionalExternal = LINEFORWARDMODE_UNCONDEXTERNAL,
			UnconditionalSpecific = LINEFORWARDMODE_UNCONDSPECIFIC,
			Busy = LINEFORWARDMODE_BUSY,
			BusyInternal = LINEFORWARDMODE_BUSYINTERNAL,
			BusyExternal = LINEFORWARDMODE_BUSYEXTERNAL,
			BusySpecific = LINEFORWARDMODE_BUSYSPECIFIC,
			NoAnswer = LINEFORWARDMODE_NOANSW,
			NoAnswerInternal = LINEFORWARDMODE_NOANSWINTERNAL,
			NoAnswerExternal = LINEFORWARDMODE_NOANSWEXTERNAL, 
			NoAnswerSpecific = LINEFORWARDMODE_NOANSWSPECIFIC, 
			BusyNoAnswer = LINEFORWARDMODE_BUSYNA,
			BusyNoAnswerInternal = LINEFORWARDMODE_BUSYNAINTERNAL, 
			BusyNoAnswerExternal = LINEFORWARDMODE_BUSYNAEXTERNAL, 
			BusyNoAnswerSpecific = LINEFORWARDMODE_BUSYNASPECIFIC, 
			Unknown = LINEFORWARDMODE_UNKNOWN,        
			Unavailable = LINEFORWARDMODE_UNAVAIL
		};

		[Flags]
		public enum struct LINEADDRESSTYPES
		{
			PhoneNumber = LINEADDRESSTYPE_PHONENUMBER,
			SDP = LINEADDRESSTYPE_SDP,
			EmailName = LINEADDRESSTYPE_EMAILNAME,
			DomainName = LINEADDRESSTYPE_DOMAINNAME,
			IPAddress = LINEADDRESSTYPE_IPADDRESS
		};

		public ref class TForwardInformation : Internal::TapiBase
		{
		protected public:
			TForwardInformation(IUnknown* pi) : Internal::TapiBase(pi) {/* */}
			CComPtr<Native::ITForwardInformation2> GetForwardInformation2Itf() { return CastToInterface<Native::ITForwardInformation2, true>(); }
			CComPtr<Native::ITForwardInformation2> GetForwardInformationItf() { return CastToInterface<Native::ITForwardInformation2, true>(); }

		public:
			~TForwardInformation()
			{
				Release(false);
			}

			property long NumRingsNoAnswer
			{
				long get()
				{
					long lValue;
					TapiException::ThrowExceptionForHR(GetForwardInformationItf()->get_NumRingsNoAnswer(&lValue));
					return lValue;
				}
				void set(long value)
				{
					TapiException::ThrowExceptionForHR(GetForwardInformationItf()->put_NumRingsNoAnswer(value));
				}
			}
			property String^ ForwardTypeDestination[LINEFORWARDMODES]
			{
				String^ get(LINEFORWARDMODES mode)
				{
					CComBSTR bstrValue;
					TapiException::ThrowExceptionForHR(GetForwardInformationItf()->get_ForwardTypeDestination((long)mode, &bstrValue));
					return gcnew String((wchar_t*)bstrValue);
				}
			}
			property String^ ForwardTypeCaller[LINEFORWARDMODES]
			{
				String^ get(LINEFORWARDMODES mode)
				{
					CComBSTR bstrValue;
					TapiException::ThrowExceptionForHR(GetForwardInformationItf()->get_ForwardTypeCaller((long)mode, &bstrValue));
					return gcnew String((wchar_t*)bstrValue);
				}
			}

			void GetForwardType(LINEFORWARDMODES mode, [Out] String^% destAddress, [Out] String^% callerAddress)
			{
				CComBSTR bstrDest, bstrCaller;
				TapiException::ThrowExceptionForHR(GetForwardInformationItf()->GetForwardType((long)mode, &bstrDest, &bstrCaller));
				destAddress = gcnew String((wchar_t*)bstrDest);
				callerAddress = gcnew String((wchar_t*)bstrCaller);
			}

			void SetForwardType(LINEFORWARDMODES mode, String^ destAddress, String^ callerAddress)
			{
				CComBSTR bstrDest = (BSTR) Marshal::StringToBSTR(destAddress).ToPointer();
				CComBSTR bstrCaller = (BSTR) Marshal::StringToBSTR(callerAddress).ToPointer();
				TapiException::ThrowExceptionForHR(GetForwardInformationItf()->SetForwardType((long)mode, bstrDest, bstrCaller));
			}
			

			void GetForwardType(LINEFORWARDMODES mode, [Out] String^% destAddress, [Out] LINEADDRESSTYPES% addrType, [Out] String^% callerAddress, [Out] LINEADDRESSTYPES% callType)
			{
				CComBSTR bstrDest, bstrCaller;
				long destType, callerType;
				TapiException::ThrowExceptionForHR(GetForwardInformation2Itf()->GetForwardType2((long)mode, &bstrDest, &destType, &bstrCaller, &callerType));
				destAddress = gcnew String((wchar_t*)bstrDest);
				callerAddress = gcnew String((wchar_t*)bstrCaller);
				addrType = (LINEADDRESSTYPES)destType;
				callType = (LINEADDRESSTYPES)callerType;
			}

			void SetForwardType(LINEFORWARDMODES mode, String^ destAddress, LINEADDRESSTYPES addrType, String^ callerAddress, LINEADDRESSTYPES callerType)
			{
				CComBSTR bstrDest = (BSTR) Marshal::StringToBSTR(destAddress).ToPointer();
				CComBSTR bstrCaller = (BSTR) Marshal::StringToBSTR(callerAddress).ToPointer();
				TapiException::ThrowExceptionForHR(GetForwardInformation2Itf()->SetForwardType2((long)mode, bstrDest, (long)addrType, bstrCaller, (long)callerType));
			}

			property LINEADDRESSTYPES ForwardTypeDestinationAddressType[LINEFORWARDMODES]
			{
				LINEADDRESSTYPES get(LINEFORWARDMODES mode)
				{
					long lValue;
					TapiException::ThrowExceptionForHR(GetForwardInformationItf()->get_ForwardTypeDestinationAddressType((long) mode, &lValue));
					return (LINEADDRESSTYPES) lValue;
				}
			}

			property LINEADDRESSTYPES ForwardTypeCallerAddressType[LINEFORWARDMODES]
			{
				LINEADDRESSTYPES get(LINEFORWARDMODES mode)
				{
					long lValue;
					TapiException::ThrowExceptionForHR(GetForwardInformationItf()->get_ForwardTypeCallerAddressType((long) mode, &lValue));
					return (LINEADDRESSTYPES) lValue;
				}
			}

			void Clear()
			{
				TapiException::ThrowExceptionForHR(GetForwardInformationItf()->Clear());
			}
		};
	}
}
