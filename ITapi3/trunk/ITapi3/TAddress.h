// TAddress.h
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

#include "TForwardInformation.h"
#include "TAddressTranslationInfo.h"
#include "TLineLocationOptions.h"

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
		ref class TPhone;

		public enum struct ADDRESS_STATE
		{
			AS_INSERVICE	= 0,
			AS_OUTOFSERVICE	= ( AS_INSERVICE + 1 ) 
		};

		public enum struct ADDRESS_CAPABILITY
		{
			AC_ADDRESSTYPES	= 0,
			AC_BEARERMODES	= ( AC_ADDRESSTYPES + 1 ) ,
			AC_MAXACTIVECALLS	= ( AC_BEARERMODES + 1 ) ,
			AC_MAXONHOLDCALLS	= ( AC_MAXACTIVECALLS + 1 ) ,
			AC_MAXONHOLDPENDINGCALLS	= ( AC_MAXONHOLDCALLS + 1 ) ,
			AC_MAXNUMCONFERENCE	= ( AC_MAXONHOLDPENDINGCALLS + 1 ) ,
			AC_MAXNUMTRANSCONF	= ( AC_MAXNUMCONFERENCE + 1 ) ,
			AC_MONITORDIGITSUPPORT	= ( AC_MAXNUMTRANSCONF + 1 ) ,
			AC_GENERATEDIGITSUPPORT	= ( AC_MONITORDIGITSUPPORT + 1 ) ,
			AC_GENERATETONEMODES	= ( AC_GENERATEDIGITSUPPORT + 1 ) ,
			AC_GENERATETONEMAXNUMFREQ	= ( AC_GENERATETONEMODES + 1 ) ,
			AC_MONITORTONEMAXNUMFREQ	= ( AC_GENERATETONEMAXNUMFREQ + 1 ) ,
			AC_MONITORTONEMAXNUMENTRIES	= ( AC_MONITORTONEMAXNUMFREQ + 1 ) ,
			AC_DEVCAPFLAGS	= ( AC_MONITORTONEMAXNUMENTRIES + 1 ) ,
			AC_ANSWERMODES	= ( AC_DEVCAPFLAGS + 1 ) ,
			AC_LINEFEATURES	= ( AC_ANSWERMODES + 1 ) ,
			AC_SETTABLEDEVSTATUS	= ( AC_LINEFEATURES + 1 ) ,
			AC_PARKSUPPORT	= ( AC_SETTABLEDEVSTATUS + 1 ) ,
			AC_CALLERIDSUPPORT	= ( AC_PARKSUPPORT + 1 ) ,
			AC_CALLEDIDSUPPORT	= ( AC_CALLERIDSUPPORT + 1 ) ,
			AC_CONNECTEDIDSUPPORT	= ( AC_CALLEDIDSUPPORT + 1 ) ,
			AC_REDIRECTIONIDSUPPORT	= ( AC_CONNECTEDIDSUPPORT + 1 ) ,
			AC_REDIRECTINGIDSUPPORT	= ( AC_REDIRECTIONIDSUPPORT + 1 ) ,
			AC_ADDRESSCAPFLAGS	= ( AC_REDIRECTINGIDSUPPORT + 1 ) ,
			AC_CALLFEATURES1	= ( AC_ADDRESSCAPFLAGS + 1 ) ,
			AC_CALLFEATURES2	= ( AC_CALLFEATURES1 + 1 ) ,
			AC_REMOVEFROMCONFCAPS	= ( AC_CALLFEATURES2 + 1 ) ,
			AC_REMOVEFROMCONFSTATE	= ( AC_REMOVEFROMCONFCAPS + 1 ) ,
			AC_TRANSFERMODES	= ( AC_REMOVEFROMCONFSTATE + 1 ) ,
			AC_ADDRESSFEATURES	= ( AC_TRANSFERMODES + 1 ) ,
			AC_PREDICTIVEAUTOTRANSFERSTATES	= ( AC_ADDRESSFEATURES + 1 ) ,
			AC_MAXCALLDATASIZE	= ( AC_PREDICTIVEAUTOTRANSFERSTATES + 1 ) ,
			AC_LINEID	= ( AC_MAXCALLDATASIZE + 1 ) ,
			AC_ADDRESSID	= ( AC_LINEID + 1 ) ,
			AC_FORWARDMODES	= ( AC_ADDRESSID + 1 ) ,
			AC_MAXFORWARDENTRIES	= ( AC_FORWARDMODES + 1 ) ,
			AC_MAXSPECIFICENTRIES	= ( AC_MAXFORWARDENTRIES + 1 ) ,
			AC_MINFWDNUMRINGS	= ( AC_MAXSPECIFICENTRIES + 1 ) ,
			AC_MAXFWDNUMRINGS	= ( AC_MINFWDNUMRINGS + 1 ) ,
			AC_MAXCALLCOMPLETIONS	= ( AC_MAXFWDNUMRINGS + 1 ) ,
			AC_CALLCOMPLETIONCONDITIONS	= ( AC_MAXCALLCOMPLETIONS + 1 ) ,
			AC_CALLCOMPLETIONMODES	= ( AC_CALLCOMPLETIONCONDITIONS + 1 ) ,
			AC_PERMANENTDEVICEID	= ( AC_CALLCOMPLETIONMODES + 1 ) ,
			AC_GATHERDIGITSMINTIMEOUT	= ( AC_PERMANENTDEVICEID + 1 ) ,
			AC_GATHERDIGITSMAXTIMEOUT	= ( AC_GATHERDIGITSMINTIMEOUT + 1 ) ,
			AC_GENERATEDIGITMINDURATION	= ( AC_GATHERDIGITSMAXTIMEOUT + 1 ) ,
			AC_GENERATEDIGITMAXDURATION	= ( AC_GENERATEDIGITMINDURATION + 1 ) ,
			AC_GENERATEDIGITDEFAULTDURATION	= ( AC_GENERATEDIGITMAXDURATION + 1 ) 
		};

		public enum struct ADDRESS_CAPABILITY_STRING
		{
			ACS_PROTOCOL	= 0,
			ACS_ADDRESSDEVICESPECIFIC	= ( ACS_PROTOCOL + 1 ) ,
			ACS_LINEDEVICESPECIFIC	= ( ACS_ADDRESSDEVICESPECIFIC + 1 ) ,
			ACS_PROVIDERSPECIFIC	= ( ACS_LINEDEVICESPECIFIC + 1 ) ,
			ACS_SWITCHSPECIFIC	= ( ACS_PROVIDERSPECIFIC + 1 ) ,
			ACS_PERMANENTDEVICEGUID	= ( ACS_SWITCHSPECIFIC + 1 ) 
		};

		public ref class TAddress sealed : Internal::TapiBase
		{
		private:
			TTapi^ _owner;
			long _notify;

		private:
			TAddress(TTapi^ owner, IUnknown* p) : TapiBase(p), _owner(owner), _notify(-1)  {/* */}

		protected public:
			static TAddress^ CreateAddress(TTapi^ owner, IUnknown* p);

			TTapi^ GetOwner()
			{
				return _owner;
			}

			virtual void Release(bool isFinalizer) override
			{
				if (!isFinalizer)
					Close();
				__super::Release(isFinalizer);
			}

			TTerminal^ FindTerminalByInterface(Native::ITTerminal* piTerm)
			{
				return TTerminal::CreateTerminal(piTerm);
			}

			void DeviceSpecific(CComPtr<Native::ITCallInfo>& call, array<byte>^ data)
			{
				CHeapPtr<byte, CComAllocator> lpdw;
				DWORD dwSize = data->Length;
				if (dwSize > 0)
				{
					lpdw.Allocate(dwSize);
					pin_ptr<byte> srcData = &data[0];
					memcpy_s(lpdw, dwSize, srcData, dwSize);
				}

				TapiException::ThrowExceptionForHR(GetAddress2Itf()->DeviceSpecific(call, lpdw, dwSize));
			}

		protected public:
			CComPtr<Native::ITAddress> GetAddressItf() { return CastToInterface<Native::ITAddress,true>(); }
			CComPtr<Native::ITAddress2> GetAddress2Itf() { return CastToInterface<Native::ITAddress2,true>(); }
			CComPtr<Native::ITAddressCapabilities> GetAddressCapabilityItf() { return CastToInterface<Native::ITAddressCapabilities,true>();}
			CComPtr<Native::ITAddressTranslation> GetAddressTranslationItf() { return CastToInterface<Native::ITAddressTranslation,true>();}
			CComPtr<Native::ITLegacyAddressMediaControl> GetLegacyAddressMediaControlItf() { return CastToInterface<Native::ITLegacyAddressMediaControl,true>();}
			CComPtr<Native::ITLegacyAddressMediaControl2> GetLegacyAddressMediaControl2Itf() { return CastToInterface<Native::ITLegacyAddressMediaControl2,true>();}
			CComPtr<Native::ITMediaSupport> GetMediaSupportItf() { return CastToInterface<Native::ITMediaSupport,true>();}
			CComPtr<Native::ITTerminalSupport> GetTerminalSupportItf() { return CastToInterface<Native::ITTerminalSupport,false>();}

		public:
			virtual String^ ToString() override
			{
				return AddressName;
			}

			property TTapi^ TapiObject
			{
				TTapi^ get()
				{
					return _owner;
				}
			}
			property ADDRESS_STATE State
			{
				ADDRESS_STATE get()
				{
					Native::ADDRESS_STATE as;
					if (SUCCEEDED(GetAddressItf()->get_State(&as)))
					{
						return (ADDRESS_STATE) as;
					}
					return ADDRESS_STATE::AS_OUTOFSERVICE;
				}
			}

			// Common test used to see whether the address supports media streams.
			property bool SupportsMediaStreams
			{
				bool get()
				{
					Native::ITMediaSupport* p;
					if (SUCCEEDED(_p->QueryInterface(Native::IID_ITMediaSupport, (void**)&p)))
					{
						p->Release();
						return true;
					}
					return false;
				}
			}

			property System::String^ AddressName
			{
				System::String^ get()
				{
					BSTR bstrName;
					if (SUCCEEDED(GetAddressItf()->get_AddressName(&bstrName)))
					{
						System::String^ name = gcnew System::String((wchar_t*)bstrName);
						SysFreeString(bstrName);
						return name;
					}
					return System::String::Empty;
				}
			}

			property System::String^ DialableAddress
			{
				System::String^ get()
				{
					BSTR bstrAddress;
					if (SUCCEEDED(GetAddressItf()->get_DialableAddress(&bstrAddress)))
					{
						System::String^ addr = gcnew System::String((wchar_t*)bstrAddress);
						SysFreeString(bstrAddress);
						return addr;
					}
					return System::String::Empty;
				}
			}

			property System::String^ ServiceProviderName
			{
				System::String^ get()
				{
					BSTR bstrName;
					if (SUCCEEDED(GetAddressItf()->get_ServiceProviderName(&bstrName)))
					{
						System::String^ name = gcnew System::String((wchar_t*)bstrName);
						SysFreeString(bstrName);
						return name;
					}
					return System::String::Empty;
				}
			}

			property bool MessageWaiting
			{
				bool get()
				{
					VARIANT_BOOL vb;
					if (SUCCEEDED(GetAddressItf()->get_MessageWaiting(&vb)))
					{
						return (vb == VARIANT_TRUE) ? true : false;
					}
					return false;
				}

				void set(bool value)
				{
					VARIANT_BOOL vb = (value == true) ? VARIANT_TRUE : VARIANT_FALSE;
					HRESULT hr = GetAddressItf()->put_MessageWaiting(vb);
					TapiException::ThrowExceptionForHR(hr);
				}
			}

			property bool DoNotDisturb
			{
				bool get()
				{
					VARIANT_BOOL vb;
					if (SUCCEEDED(GetAddressItf()->get_DoNotDisturb(&vb)))
					{
						return (vb == VARIANT_TRUE) ? true : false;
					}
					return false;
				}

				void set(bool value)
				{
					VARIANT_BOOL vb = (value == true) ? VARIANT_TRUE : VARIANT_FALSE;
					HRESULT hr = GetAddressItf()->put_DoNotDisturb(vb);
					TapiException::ThrowExceptionForHR(hr);
				}
			}

			void SetCallHubTracking(bool onoff);
			void Monitor(TAPIMEDIATYPES supportedMediaTypes);
			void Open(TAPIMEDIATYPES supportedMediaTypes);
			void OpenAndMonitor(TAPIMEDIATYPES supportedMediaTypes);
			void Close();

			TCall^ CreateCall(String^ destAddress, LINEADDRESSTYPES addrType, TAPIMEDIATYPES mediaTypes)
			{
				CComBSTR bstrNumber;
				if (!String::IsNullOrEmpty(destAddress))
					bstrNumber = (BSTR) Marshal::StringToBSTR(destAddress).ToPointer();
				CComPtr<Native::ITBasicCallControl> piCall;
				TapiException::ThrowExceptionForHR(GetAddressItf()->CreateCall(bstrNumber, (long) addrType, (long)mediaTypes, &piCall));

				return TCall::CreateCallAppearance(this, piCall);	
			}

			TForwardInformation^ CreateForwardInfoObject()
			{
				CComPtr<Native::ITForwardInformation> pitf;
				TapiException::ThrowExceptionForHR(GetAddressItf()->CreateForwardInfoObject(&pitf));
				return gcnew TForwardInformation(pitf);
			}

			property TForwardInformation^ CurrentForwardInfo
			{
				TForwardInformation^ get()
				{
					CComPtr<Native::ITForwardInformation> pitf;
					TapiException::ThrowExceptionForHR(GetAddressItf()->get_CurrentForwardInfo(&pitf));
					return gcnew TForwardInformation(pitf);
				}
			}

			void Forward(TForwardInformation^ fwdInfo, TCall^ consultationCall)
			{
				CComPtr<Native::ITForwardInformation> piFwd;
				if (fwdInfo != nullptr)
					piFwd = fwdInfo->GetForwardInformationItf();
				CComPtr<Native::ITBasicCallControl> piCall;
				if (consultationCall != nullptr)
					piCall = consultationCall->GetBasicCallControlItf();

				TapiException::ThrowExceptionForHR(GetAddressItf()->Forward(piFwd, piCall));
			}

			property array<TCall^>^ Calls
			{
				array<TCall^>^ get() 
				{
					List<TCall^>^ retList = gcnew List<TCall^>();
					try
					{
						CComPtr<Native::IEnumCall> iePtr;
						TapiException::ThrowExceptionForHR(GetAddressItf()->EnumerateCalls(&iePtr));
						CComPtr<Native::ITCallInfo> callInfo;
						while (iePtr->Next(1, &callInfo, NULL) == S_OK)
						{
							retList->Add(TCall::CreateCallAppearance(this, callInfo));
							callInfo = NULL;
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retList->ToArray();
				}
			}
			

			property long AddressCapability[ADDRESS_CAPABILITY]
			{
				long get(ADDRESS_CAPABILITY cap)
				{
					long lValue;
					TapiException::ThrowExceptionForHR(this->GetAddressCapabilityItf()->get_AddressCapability((Native::ADDRESS_CAPABILITY)cap, &lValue));
					return lValue;
				}
			}

			property String^ AddressCapability[ADDRESS_CAPABILITY_STRING]
			{
				String^ get(ADDRESS_CAPABILITY_STRING cap)
				{
					CComBSTR bstrValue;
					TapiException::ThrowExceptionForHR(this->GetAddressCapabilityItf()->get_AddressCapabilityString((Native::ADDRESS_CAPABILITY_STRING)cap, &bstrValue));
					return gcnew String((wchar_t*)bstrValue);
				}
			}

			property array<String^>^ CallTreatments
			{
				array<String^>^ get()
				{
					List<String^>^ retList = gcnew List<String^>();
					try 
					{
						CComPtr<Native::IEnumBstr> pEnumCallT;
						HRESULT hr = this->GetAddressCapabilityItf()->EnumerateCallTreatments(&pEnumCallT);
						if (SUCCEEDED(hr))
						{
							CComBSTR bstrValue;
							while (pEnumCallT->Next(1, &bstrValue, NULL) == S_OK)
							{
								retList->Add(gcnew String((wchar_t*)bstrValue));
								bstrValue.Empty();
							}
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retList->ToArray();
				}
			}

			property array<String^>^ DeviceClasses
			{
				array<String^>^ get()
				{
					List<String^>^ retList = gcnew List<String^>();
					try 
					{
						CComPtr<Native::IEnumBstr> pEnumDevC;
						HRESULT hr = this->GetAddressCapabilityItf()->EnumerateDeviceClasses(&pEnumDevC);
						if (SUCCEEDED(hr))
						{
							CComBSTR bstrValue;
							while (pEnumDevC->Next(1, &bstrValue, NULL) == S_OK)
							{
								retList->Add(gcnew String((wchar_t*)bstrValue));
								bstrValue.Empty();
							}
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retList->ToArray();
				}
			}

			property array<String^>^ CompletionMessages
			{
				array<String^>^ get()
				{
					List<String^>^ retList = gcnew List<String^>();

					try 
					{
						CComPtr<Native::IEnumBstr> pEnumMsgs;
						HRESULT hr = this->GetAddressCapabilityItf()->EnumerateCompletionMessages(&pEnumMsgs);
						if (SUCCEEDED(hr))
						{
							CComBSTR bstrValue;
							while (pEnumMsgs->Next(1, &bstrValue, NULL) == S_OK)
							{
								retList->Add(gcnew String((wchar_t*)bstrValue));
								bstrValue.Empty();
							}
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retList->ToArray();
				}
			}

			TAddressTranslationInfo^ TranslateAddress(String^ address, long Card, LINETRANSLATEOPTIONS options)
			{
				CComPtr<Native::ITAddressTranslationInfo> pTranslated;
				CComBSTR bstrValue = (BSTR)Marshal::StringToBSTR(address).ToPointer();
				TapiException::ThrowExceptionForHR(GetAddressTranslationItf()->TranslateAddress(bstrValue, Card, (long) options, &pTranslated));
				return gcnew TAddressTranslationInfo(pTranslated);
			}

			void TranslateDialog(IntPtr hwnd, String^ address)
			{
				CComBSTR bstrValue = (BSTR)Marshal::StringToBSTR(address).ToPointer();
				TapiException::ThrowExceptionForHR(GetAddressTranslationItf()->TranslateDialog((long)hwnd.ToPointer(), bstrValue));
			}

			property array<TLocationInfo^>^ Locations
			{
				array<TLocationInfo^>^ get()
				{
					List<TLocationInfo^>^ retList = gcnew List<TLocationInfo^>();

					try
					{
						CComPtr<Native::IEnumLocation> iePtr;
						TapiException::ThrowExceptionForHR(GetAddressTranslationItf()->EnumerateLocations(&iePtr));
						CComPtr<Native::ITLocationInfo> locInfo;
						while (iePtr->Next(1, &locInfo, NULL) == S_OK)
						{
							retList->Add(gcnew TLocationInfo(locInfo));
							locInfo = NULL;
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retList->ToArray();
				}
			}

			property array<TCallingCard^>^ CallingCards
			{
				array<TCallingCard^>^ get()
				{
					List<TCallingCard^>^ retList = gcnew List<TCallingCard^>();

					try
					{
						CComPtr<Native::IEnumCallingCard> iePtr;
						TapiException::ThrowExceptionForHR(GetAddressTranslationItf()->EnumerateCallingCards(&iePtr));
						CComPtr<Native::ITCallingCard> cardInfo;
						while (iePtr->Next(1, &cardInfo, NULL) == S_OK)
						{
							retList->Add(gcnew TCallingCard(cardInfo));
							cardInfo = NULL;
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retList->ToArray();
				}
			}

			array<byte>^ GetID(String^ deviceClass)
			{
				CComBSTR bstrName = (BSTR) Marshal::StringToBSTR(deviceClass).ToPointer();
				array<byte>^ retData = nullptr;
				BYTE* lpdw;
				DWORD dwSize = 0; 

				if (SUCCEEDED(GetLegacyAddressMediaControlItf()->GetID(bstrName, &dwSize, &lpdw)))
				{
					if (dwSize > 0)
					{
						retData = gcnew array<byte>(dwSize);
						pin_ptr<byte> ptrTest = &retData[0];
						memcpy_s(ptrTest, dwSize, lpdw, dwSize);
						ptrTest = nullptr; 
						CoTaskMemFree(lpdw);
					}
				}
				return retData;
			}

			array<byte>^ GetDevConfig(String^ deviceClass)
			{
				CComBSTR bstrName = (BSTR) Marshal::StringToBSTR(deviceClass).ToPointer();
				array<byte>^ retData = nullptr;
				BYTE* lpdw = NULL;
				DWORD dwSize = 0;
				if (SUCCEEDED(GetLegacyAddressMediaControlItf()->GetDevConfig(bstrName, &dwSize, &lpdw)))
				{
					if (dwSize > 0)
					{
						retData = gcnew array<byte>(dwSize);
						pin_ptr<byte> ptrTest = &retData[0];
						memcpy_s(ptrTest, dwSize, lpdw, dwSize);
						ptrTest = nullptr; 
						CoTaskMemFree(lpdw);
					}
				}
				return retData;
			}

			void SetDevConfig(String^ deviceClass, array<byte>^ arrData)
			{
				CComBSTR bstrName = (BSTR) Marshal::StringToBSTR(deviceClass).ToPointer();
				CComHeapPtr<byte> lpdw;
				DWORD dwSize = arrData->Length;
				if (dwSize > 0)
				{
					lpdw.Allocate(dwSize);
					pin_ptr<byte> srcData = &arrData[0];
					memcpy_s(lpdw, dwSize, srcData, dwSize);
				}
				TapiException::ThrowExceptionForHR(GetLegacyAddressMediaControlItf()->SetDevConfig(bstrName, dwSize, lpdw));
			}

			bool ConfigDialog(IntPtr hwnd, String^ deviceClass)
			{
				CComBSTR bstrName;
				if (!String::IsNullOrEmpty(deviceClass))
					bstrName = (BSTR) Marshal::StringToBSTR(deviceClass).ToPointer();
				return (SUCCEEDED(GetLegacyAddressMediaControl2Itf()->ConfigDialog((HWND)hwnd.ToPointer(), bstrName)));
			}

			bool ConfigDialogEdit(IntPtr hwnd, String^ deviceClass, array<byte>^ dataIn, [Out] array<byte>^% dataOut)
			{
				dataOut = nullptr;

				CComBSTR bstrName;
				if (!String::IsNullOrEmpty(deviceClass))
					bstrName = (BSTR) Marshal::StringToBSTR(deviceClass).ToPointer();
				DWORD dwInSize = dataIn->Length; 
				CComHeapPtr<byte> lpdwIn;
				DWORD dwOutSize = 0; BYTE* lpdwOut = NULL;

				if (dwInSize > 0)
				{
					lpdwIn.Allocate(dwInSize);
					pin_ptr<byte> srcData = &dataIn[0];
					memcpy_s(lpdwIn, dwInSize, srcData, dwInSize);
				}

				if (SUCCEEDED(GetLegacyAddressMediaControl2Itf()->ConfigDialogEdit((HWND)hwnd.ToPointer(), bstrName, dwInSize, lpdwIn, &dwOutSize, &lpdwOut)))
				{
					if (dwOutSize > 0)
					{
						dataOut = gcnew array<byte>(dwOutSize);
						pin_ptr<byte> ptrTest = &dataOut[0];
						memcpy_s(ptrTest, dwOutSize, lpdwOut, dwOutSize);
						ptrTest = nullptr; 
						CoTaskMemFree(lpdwOut);
					}
				}
				return dataOut != nullptr;
			}

			property TAPIMEDIATYPES MediaTypes 
			{
				TAPIMEDIATYPES get()
				{
					long lValue;
					TapiException::ThrowExceptionForHR(GetMediaSupportItf()->get_MediaTypes(&lValue));
					return (TAPIMEDIATYPES) lValue;
				}
			}

			bool QueryMediaType(TAPIMEDIATYPES type)
			{
				VARIANT_BOOL vb;
				HRESULT hr = GetMediaSupportItf()->QueryMediaType((long)type, &vb);
				return (SUCCEEDED(hr) && vb == VARIANT_TRUE);
			}

			property array<TTerminal^>^ StaticTerminals
			{
				array<TTerminal^>^ get()
				{
					List<TTerminal^>^ retList = gcnew List<TTerminal^>();
					try 
					{
						CComPtr<Native::ITTerminalSupport> termItf = GetTerminalSupportItf();
						if (termItf != NULL)
						{
							CComPtr<Native::IEnumTerminal> iePtr;
							TapiException::ThrowExceptionForHR(termItf->EnumerateStaticTerminals(&iePtr));
							CComPtr<Native::ITTerminal> termInfo;
							while (iePtr->Next(1, &termInfo, NULL) == S_OK)
							{
								retList->Add(TTerminal::CreateTerminal(termInfo));
								termInfo = NULL;
							}
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retList->ToArray();
				}
			}

			property array<Guid>^ DynamicTerminalClasses
			{
				array<Guid>^ get()
				{
					List<Guid>^ retList = gcnew List<Guid>();

					try 
					{
						CComPtr<Native::ITTerminalSupport> termItf = GetTerminalSupportItf();
						if (termItf != NULL)
						{
							CComPtr<Native::IEnumTerminalClass> iePtr;
							TapiException::ThrowExceptionForHR(termItf->EnumerateDynamicTerminalClasses(&iePtr));
							GUID guid;
							while (iePtr->Next(1, &guid, NULL) == S_OK)
								retList->Add(Internal::ConversionFunctions::FromGUID(guid));
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retList->ToArray();
				}
			}

			TTerminal^ CreateTerminal(String^ terminalClass, TAPIMEDIATYPES mediaType, TERMINAL_DIRECTION direction)
			{
				CComPtr<Native::ITTerminalSupport> termItf = GetTerminalSupportItf();
				if (termItf != NULL)
				{
					CComBSTR bstrName;
					if (!String::IsNullOrEmpty(terminalClass))
						bstrName = (BSTR) Marshal::StringToBSTR(terminalClass).ToPointer();
					CComPtr<Native::ITTerminal> pitf;
					if (SUCCEEDED(termItf->CreateTerminal(bstrName, (long)mediaType, (Native::TERMINAL_DIRECTION)direction, &pitf)))
					{
						if (pitf != NULL)
							return TTerminal::CreateTerminal(pitf);
					}
				}
				return nullptr;
			}

			TTerminal^ GetDefaultStaticTerminal(TAPIMEDIATYPES mediaType, TERMINAL_DIRECTION direction)
			{
				CComPtr<Native::ITTerminalSupport> termItf = GetTerminalSupportItf();
				if (termItf != NULL)
				{
					CComPtr<Native::ITTerminal> pitf;
					if (SUCCEEDED(termItf->GetDefaultStaticTerminal((long)mediaType, (Native::TERMINAL_DIRECTION)direction, &pitf)))
					{
						if (pitf != NULL)
							return TTerminal::CreateTerminal(pitf);
					}
				}
				return nullptr;
			}

			long NegotiateExtVersion(long lowVersion, long hiVersion)
			{
				long rVersion;
				TapiException::ThrowExceptionForHR(GetAddress2Itf()->NegotiateExtVersion(lowVersion, hiVersion, &rVersion));
				return rVersion;
			}

			property array<TPhone^>^ Phones
			{
				array<TPhone^>^ get()
				{
					return EnumeratePhones();
				}
			}

			property array<TPhone^>^ PreferredPhones
			{
				array<TPhone^>^ get()
				{
					return EnumeratePreferredPhones();
				}
			}
			TPhone^ GetPhoneFromTerminal(TTerminal^ terminal);

			private:
				array<TPhone^>^ EnumeratePhones();
				array<TPhone^>^ EnumeratePreferredPhones();
		};

	}
}
