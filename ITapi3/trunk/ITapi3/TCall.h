// TCall.h
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

namespace JulMar
{
	namespace Tapi3
	{
		public enum struct CALL_PRIVILEGE
		{
			CP_OWNER = 0,
			CP_MONITOR = ( CP_OWNER + 1 )
		};

		public enum struct CALLINFO_LONG
		{
			CIL_MEDIATYPESAVAILABLE	= 0,
			CIL_BEARERMODE	= ( CIL_MEDIATYPESAVAILABLE + 1 ) ,
			CIL_CALLERIDADDRESSTYPE	= ( CIL_BEARERMODE + 1 ) ,
			CIL_CALLEDIDADDRESSTYPE	= ( CIL_CALLERIDADDRESSTYPE + 1 ) ,
			CIL_CONNECTEDIDADDRESSTYPE	= ( CIL_CALLEDIDADDRESSTYPE + 1 ) ,
			CIL_REDIRECTIONIDADDRESSTYPE	= ( CIL_CONNECTEDIDADDRESSTYPE + 1 ) ,
			CIL_REDIRECTINGIDADDRESSTYPE	= ( CIL_REDIRECTIONIDADDRESSTYPE + 1 ) ,
			CIL_ORIGIN	= ( CIL_REDIRECTINGIDADDRESSTYPE + 1 ) ,
			CIL_REASON	= ( CIL_ORIGIN + 1 ) ,
			CIL_APPSPECIFIC	= ( CIL_REASON + 1 ) ,
			CIL_CALLPARAMSFLAGS	= ( CIL_APPSPECIFIC + 1 ) ,
			CIL_CALLTREATMENT	= ( CIL_CALLPARAMSFLAGS + 1 ) ,
			CIL_MINRATE	= ( CIL_CALLTREATMENT + 1 ) ,
			CIL_MAXRATE	= ( CIL_MINRATE + 1 ) ,
			CIL_COUNTRYCODE	= ( CIL_MAXRATE + 1 ) ,
			CIL_CALLID	= ( CIL_COUNTRYCODE + 1 ) ,
			CIL_RELATEDCALLID	= ( CIL_CALLID + 1 ) ,
			CIL_COMPLETIONID	= ( CIL_RELATEDCALLID + 1 ) ,
			CIL_NUMBEROFOWNERS	= ( CIL_COMPLETIONID + 1 ) ,
			CIL_NUMBEROFMONITORS	= ( CIL_NUMBEROFOWNERS + 1 ) ,
			CIL_TRUNK	= ( CIL_NUMBEROFMONITORS + 1 ) ,
			CIL_RATE	= ( CIL_TRUNK + 1 ) ,
			CIL_GENERATEDIGITDURATION	= ( CIL_RATE + 1 ) ,
			CIL_MONITORDIGITMODES	= ( CIL_GENERATEDIGITDURATION + 1 ) ,
			CIL_MONITORMEDIAMODES	= ( CIL_MONITORDIGITMODES + 1 ) 
		};

		public enum struct CALLINFO_STRING
		{
			CIS_CALLERIDNAME	= 0,
			CIS_CALLERIDNUMBER	= ( CIS_CALLERIDNAME + 1 ) ,
			CIS_CALLEDIDNAME	= ( CIS_CALLERIDNUMBER + 1 ) ,
			CIS_CALLEDIDNUMBER	= ( CIS_CALLEDIDNAME + 1 ) ,
			CIS_CONNECTEDIDNAME	= ( CIS_CALLEDIDNUMBER + 1 ) ,
			CIS_CONNECTEDIDNUMBER	= ( CIS_CONNECTEDIDNAME + 1 ) ,
			CIS_REDIRECTIONIDNAME	= ( CIS_CONNECTEDIDNUMBER + 1 ) ,
			CIS_REDIRECTIONIDNUMBER	= ( CIS_REDIRECTIONIDNAME + 1 ) ,
			CIS_REDIRECTINGIDNAME	= ( CIS_REDIRECTIONIDNUMBER + 1 ) ,
			CIS_REDIRECTINGIDNUMBER	= ( CIS_REDIRECTINGIDNAME + 1 ) ,
			CIS_CALLEDPARTYFRIENDLYNAME	= ( CIS_REDIRECTINGIDNUMBER + 1 ) ,
			CIS_COMMENT	= ( CIS_CALLEDPARTYFRIENDLYNAME + 1 ) ,
			CIS_DISPLAYABLEADDRESS	= ( CIS_COMMENT + 1 ) ,
			CIS_CALLINGPARTYID	= ( CIS_DISPLAYABLEADDRESS + 1 ) 
		};

		public enum struct CALLINFO_BUFFER
		{
			CIB_USERUSERINFO	= 0,
			CIB_DEVSPECIFICBUFFER	= ( CIB_USERUSERINFO + 1 ) ,
			CIB_CALLDATABUFFER	= ( CIB_DEVSPECIFICBUFFER + 1 ) ,
			CIB_CHARGINGINFOBUFFER	= ( CIB_CALLDATABUFFER + 1 ) ,
			CIB_HIGHLEVELCOMPATIBILITYBUFFER	= ( CIB_CHARGINGINFOBUFFER + 1 ) ,
			CIB_LOWLEVELCOMPATIBILITYBUFFER	= ( CIB_HIGHLEVELCOMPATIBILITYBUFFER + 1 ) 
		};

		public enum struct DISCONNECT_CODE
		{
			DC_NORMAL	= 0,
			DC_NOANSWER	= ( DC_NORMAL + 1 ) ,
			DC_REJECTED	= ( DC_NOANSWER + 1 ) 
		};

		public enum struct QOS_SERVICE_LEVEL
		{
			QSL_NEEDED	= 1,
			QSL_IF_AVAILABLE	= 2,
			QSL_BEST_EFFORT	= 3
		};

		public enum struct FINISH_MODE
		{
			FM_ASTRANSFER	= 0,
			FM_ASCONFERENCE	= ( FM_ASTRANSFER + 1 ) 
		};

		public ref class TCall : Internal::TapiBase
		{
		private:
			TAddress^ _owner;
		protected public:
			CComPtr<Native::ITCallInfo> GetCallInfoItf() { return CastToInterface<Native::ITCallInfo, true>(); }
			CComPtr<Native::ITBasicCallControl> GetBasicCallControlItf() { return CastToInterface<Native::ITBasicCallControl, true>(); }
			CComPtr<Native::ITBasicCallControl2> GetBasicCallControl2Itf() { return CastToInterface<Native::ITBasicCallControl2, true>(); }
			CComPtr<Native::ITStreamControl> GetStreamControlItf() { return CastToInterface<Native::ITStreamControl, false>(); }
			CComPtr<Native::ITLegacyCallMediaControl> GetLegacyCallMediaControlItf() { return CastToInterface<Native::ITLegacyCallMediaControl, true>(); }
			CComPtr<Native::ITLegacyCallMediaControl2> GetLegacyCallMediaControl2Itf() { return CastToInterface<Native::ITLegacyCallMediaControl2, true>(); }
			static TCall^ CreateCallAppearance(TAddress^ addr, IUnknown* p);

			virtual void Release(bool inFinalizer) override;

		private:
			TCall(TAddress^ owner, IUnknown* p) : TapiBase(p), _owner(owner) {/* */}
			TCallHub^ GetCallHub();

		public:
			~TCall()
			{
				if (IsValid())
					Release(false);
			}

			virtual int GetHashCode() override
			{
				return (int)_p;
			}

			property TAddress^ Address
			{
				TAddress^ get()
				{
					return _owner;
				}
			}

			property CALL_STATE CallState 
			{
				CALL_STATE get()
				{
					if (IsValid())
					{
						Native::CALL_STATE cs;
						if (SUCCEEDED(GetCallInfoItf()->get_CallState(&cs)))
							return (CALL_STATE) cs;
					}
					return CALL_STATE::CS_UNKNOWN;
				}
			}

			property CALL_PRIVILEGE Privilege
			{
				CALL_PRIVILEGE get()
				{
					ThrowNotValid();
					Native::CALL_PRIVILEGE cp;
					TapiException::ThrowExceptionForHR(GetCallInfoItf()->get_Privilege(&cp));
					return (CALL_PRIVILEGE) cp;
				}
			}

			property long CallInfo[CALLINFO_LONG]
			{
				long get(CALLINFO_LONG cil)
				{
					ThrowNotValid();
					long l;
					return (SUCCEEDED(GetCallInfoItf()->get_CallInfoLong((Native::CALLINFO_LONG) cil, &l))) ? l : 0;
				}
				void set(CALLINFO_LONG cil, long value)
				{
					ThrowNotValid();
					Native::CALLINFO_LONG tcil = (Native::CALLINFO_LONG) cil;
					TapiException::ThrowExceptionForHR(GetCallInfoItf()->put_CallInfoLong(tcil, value));
				}
			}

			property String^ CallInfo[CALLINFO_STRING]
			{
				String^ get(CALLINFO_STRING cis)
				{
					ThrowNotValid();
					Native::CALLINFO_STRING tcis = (Native::CALLINFO_STRING) cis;
					CComBSTR bstrValue;
					HRESULT hr = GetCallInfoItf()->get_CallInfoString(tcis, &bstrValue);
					if (SUCCEEDED(hr))
						return gcnew System::String((wchar_t*)bstrValue);
					return System::String::Empty;
				}
				void set(CALLINFO_STRING cis, System::String^ value)
				{
					ThrowNotValid();

					Native::CALLINFO_STRING tcis = (Native::CALLINFO_STRING) cis;
					CComBSTR bstrValue = (BSTR)Marshal::StringToBSTR(value).ToPointer();
					HRESULT hr = GetCallInfoItf()->put_CallInfoString(tcis, bstrValue);
					TapiException::ThrowExceptionForHR(hr);
				}
			}

			property Object^ CallInfo[CALLINFO_BUFFER]
			{
				Object^ get(CALLINFO_BUFFER cib)
				{
					ThrowNotValid();
					System::Object^ obj = nullptr;
					VARIANT vt;
					if (SUCCEEDED(GetCallInfoItf()->get_CallInfoBuffer((Native::CALLINFO_BUFFER) cib, &vt)))
					{
						obj = Marshal::GetObjectForNativeVariant(IntPtr(&vt));
						CoTaskMemFree(vt.byref);
					}
					return obj;
				}
				void set(CALLINFO_BUFFER cib, System::Object^ value)
				{
					ThrowNotValid();

					IntPtr ip = Marshal::AllocCoTaskMem(Marshal::SizeOf(value));
					Marshal::GetNativeVariantForObject(value, ip);
					HRESULT hr = GetCallInfoItf()->put_CallInfoBuffer((Native::CALLINFO_BUFFER) cib, *((VARIANT*)ip.ToPointer()));
					Marshal::FreeCoTaskMem(ip);
					TapiException::ThrowExceptionForHR(hr);
				}
			}

			void ReleaseUserUserInfo()
			{
				ThrowNotValid();
				GetCallInfoItf()->ReleaseUserUserInfo();
			}

			property TCallHub^ CallHub
			{
				TCallHub^ get()
				{
					ThrowNotValid();
					return GetCallHub();
				}
			}

			void Answer()
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->Answer());
			}

			void Connect(bool synchronous)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->Connect((synchronous) ? VARIANT_TRUE : VARIANT_FALSE));
			}

			void Disconnect(DISCONNECT_CODE dc)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->Disconnect((Native::DISCONNECT_CODE)dc));
			}

			void Hold(bool onoffHold)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->Hold((onoffHold) ? VARIANT_TRUE : VARIANT_FALSE));
			}

			void HandoffDirect(System::String^ appName)
			{
				ThrowNotValid();
				CComBSTR bstrValue = (BSTR)Marshal::StringToBSTR(appName).ToPointer();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->HandoffDirect(bstrValue));
			}

			void HandoffIndirect(TAPIMEDIATYPES mediaType)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->HandoffIndirect((long)mediaType));
			}

			void Transfer(TCall^ consultationCall, bool syncAsync)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->Transfer(consultationCall->GetBasicCallControlItf(), (syncAsync) ? VARIANT_TRUE : VARIANT_FALSE));
			}

			void BlindTransfer(System::String^ destAddress)
			{
				ThrowNotValid();
				CComBSTR bstrValue = (BSTR)Marshal::StringToBSTR(destAddress).ToPointer();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->BlindTransfer(bstrValue));
			}

			void Conference(TCall^ consultationCall, bool syncAsync)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->Conference(consultationCall->GetBasicCallControlItf(), (syncAsync) ? VARIANT_TRUE : VARIANT_FALSE));
			}

			void SwapHold(TCall^ consultationCall)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->SwapHold(consultationCall->GetBasicCallControlItf()));
			}

			void ParkDirect(System::String^ destAddress)
			{
				ThrowNotValid();
				CComBSTR bstrValue = (BSTR)Marshal::StringToBSTR(destAddress).ToPointer();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->ParkDirect(bstrValue));
			}

			System::String^ ParkIndirect()
			{
				ThrowNotValid();
				CComBSTR bstrValue;
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->ParkIndirect(&bstrValue));
				return gcnew System::String((wchar_t*)bstrValue);
			}

			void Unpark()
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->Unpark());
			}

			void SetQOS(TAPIMEDIATYPES mediaType, QOS_SERVICE_LEVEL level)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->SetQOS((long)mediaType, (Native::QOS_SERVICE_LEVEL)level));
			}

			void Pickup(System::String^ groupId)
			{
				ThrowNotValid();
				CComBSTR bstrValue = (BSTR)Marshal::StringToBSTR(groupId).ToPointer();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->Pickup(bstrValue));
			}

			void Dial(System::String^ address)
			{
				ThrowNotValid();
				CComBSTR bstrValue = (BSTR)Marshal::StringToBSTR(address).ToPointer();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->Dial(bstrValue));
			}

			void Finish(FINISH_MODE mode)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->Finish((Native::FINISH_MODE)mode));
			}

			void RemoveFromConference()
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(this->GetBasicCallControlItf()->RemoveFromConference());
			}

			void SelectTerminalOnCall(TTerminal^ term);
			void UnselectTerminalOnCall(TTerminal^ terminal);

			TStream^ CreateStream(TAPIMEDIATYPES mediaType, TERMINAL_DIRECTION dir)
			{
				ThrowNotValid();

				CComPtr<Native::ITStreamControl> piCtl = GetStreamControlItf();
				if (piCtl)
				{
					CComPtr<Native::ITStream> pi;
					HRESULT hr = piCtl->CreateStream((long)mediaType, (Native::TERMINAL_DIRECTION) dir, &pi);
					if (SUCCEEDED(hr))
						return TStream::CreateStream(pi);
				}
				return nullptr;				
			}

			void RemoveStream(TStream^ stm)
			{
				if (stm == nullptr)
					throw gcnew ArgumentNullException("stm");

				ThrowNotValid();

				CComPtr<Native::ITStreamControl> piCtl = GetStreamControlItf();
				if (piCtl)
				{
					CComPtr<Native::ITStream> pi = stm->GetStreamItf();
					TapiException::ThrowExceptionForHR(piCtl->RemoveStream(pi));
				}
			}

			property array<TStream^>^ Streams
			{
				array<TStream^>^ get()
				{
					ThrowNotValid();
					List<TStream^>^ retData = gcnew List<TStream^>();
					try
					{
						CComPtr<Native::ITStreamControl> piCtl = GetStreamControlItf();
						if (piCtl)
						{
							CComPtr<Native::IEnumStream> piEnum;
							if (SUCCEEDED(piCtl->EnumerateStreams(&piEnum)) && piEnum)
							{
								CComPtr<Native::ITStream> piStm;
								while (piEnum->Next(1, &piStm, NULL) == S_OK)
								{
									retData->Add(TStream::CreateStream(piStm));
									piStm = NULL;
								}
							}
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retData->ToArray();
				}
			}
			
			void DetectDigits(LINEDIGITMODE digitMode)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(GetLegacyCallMediaControlItf()->DetectDigits((Native::TAPI_DIGITMODE)digitMode));
			}

			void GenerateDigits(String^ digits, LINEDIGITMODE digitMode)
			{
				ThrowNotValid();
				CComBSTR bstrValue = (BSTR) Marshal::StringToBSTR(digits).ToPointer();
				TapiException::ThrowExceptionForHR(GetLegacyCallMediaControlItf()->GenerateDigits(bstrValue, (Native::TAPI_DIGITMODE)digitMode));
			}

			void GenerateDigits(String^ digits, LINEDIGITMODE digitMode, long duration)
			{
				ThrowNotValid();
				CComBSTR bstrValue = (BSTR) Marshal::StringToBSTR(digits).ToPointer();
				TapiException::ThrowExceptionForHR(GetLegacyCallMediaControl2Itf()->GenerateDigits2(bstrValue, (Native::TAPI_DIGITMODE)digitMode, duration));
			}

			void GatherDigits(LINEDIGITMODE digitMode, long numDigits, String^ terminatingDigits, long firstDigitTimeout, long interDigitTimeout)
			{
				ThrowNotValid();
				CComBSTR bstrValue;
				if (!String::IsNullOrEmpty(terminatingDigits))
					bstrValue = (BSTR) Marshal::StringToBSTR(terminatingDigits).ToPointer();

				TapiException::ThrowExceptionForHR(GetLegacyCallMediaControl2Itf()->GatherDigits((Native::TAPI_DIGITMODE)digitMode, numDigits, bstrValue, firstDigitTimeout, interDigitTimeout));
			}

			array<byte>^ GetID(String^ deviceClass)
			{
				ThrowNotValid();
				array<byte>^ retData = nullptr;
				DWORD dwSize = 0; BYTE* lpdw = NULL;
				CComBSTR bstrName = (BSTR) Marshal::StringToBSTR(deviceClass).ToPointer();
				if (SUCCEEDED(GetLegacyCallMediaControlItf()->GetID(bstrName, &dwSize, &lpdw)))
				{
					if (dwSize > 0)
					{
						retData = gcnew array<byte>(dwSize);
						pin_ptr<byte> ptrTest = &retData[0];
						memcpy(ptrTest, lpdw, dwSize);
						ptrTest = nullptr; 
						CoTaskMemFree(lpdw);
					}
				}
				return retData;
			}

			void SetMediaTypes(TAPIMEDIATYPES mediaTypes)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(GetLegacyCallMediaControlItf()->SetMediaType((long)mediaTypes));
			}

			void MonitorMedia(TAPIMEDIATYPES mediaTypes)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(GetLegacyCallMediaControlItf()->MonitorMedia((long)mediaTypes));
			}

			void DetectTones(array<TDetectTone^>^ toneList)
			{
				ThrowNotValid();
				Native::TAPI_DETECTTONE* ptl = NULL;
				if (toneList != nullptr && toneList->Length > 0)
				{
					ptl = new Native::TAPI_DETECTTONE[toneList->Length];
					Native::TAPI_DETECTTONE* curr = ptl;
					for (int i = 0; i < toneList->Length; i++, curr++)
					{
						curr->dwAppSpecific = toneList[i]->AppSpecific;
						curr->dwDuration = toneList[i]->Duration;
						curr->dwFrequency1 = toneList[i][0];
						curr->dwFrequency2 = toneList[i][1];
						curr->dwFrequency3 = toneList[i][2];
					}
				}

				try 
				{
					TapiException::ThrowExceptionForHR(GetLegacyCallMediaControl2Itf()->DetectTones(ptl, toneList->Length));
				}
				finally
				{
					if (ptl != NULL)
						delete [] ptl;
				}
			}

			void GenerateTone(TAPI_TONEMODE tone, long duration)
			{
				ThrowNotValid();
				TapiException::ThrowExceptionForHR(GetLegacyCallMediaControl2Itf()->GenerateTone((Native::TAPI_TONEMODE)tone, duration));
			}

			void GenerateCustomTones(array<TCustomTone^>^ toneList, long duration)
			{
				ThrowNotValid();

				if (toneList == nullptr)
					throw gcnew ArgumentNullException("toneList");
				else if (toneList->Length == 0)
					throw gcnew ArgumentException("ToneList must have at least one entry");

				Native::TAPI_CUSTOMTONE* ptl = new Native::TAPI_CUSTOMTONE[toneList->Length];
				Native::TAPI_CUSTOMTONE* curr = ptl; int totalCount = 0;
				for (int i = 0; i < toneList->Length; i++)
				{
					if (toneList[i] != nullptr)
					{
						curr->dwFrequency = toneList[i]->Frequency;
						curr->dwCadenceOff = toneList[i]->CadenceOff; 
						curr->dwCadenceOn = toneList[i]->CadenceOn;
						curr->dwVolume = toneList[i]->Volume;
						totalCount++; curr++;
					}
				}

				try
				{
					if (totalCount == 0)
						throw gcnew ArgumentException("ToneList must have at least one entry");

					TapiException::ThrowExceptionForHR(GetLegacyCallMediaControl2Itf()->GenerateCustomTones(ptl, totalCount, duration));
				}
				finally
				{
					delete [] ptl;
				}
			}

			void DeviceSpecific(array<byte>^ data);

			void SelectDefaultTerminals();

			TTerminal^ RequestTerminal(String^ terminalClass, TAPIMEDIATYPES mediaType, TERMINAL_DIRECTION direction)
			{
				CComPtr<Native::ITBasicCallControl2> cci = GetBasicCallControl2Itf();
				if (cci != NULL)
				{
					CComBSTR bstrName;
					if (!String::IsNullOrEmpty(terminalClass))
						bstrName = (BSTR) Marshal::StringToBSTR(terminalClass).ToPointer();
					CComPtr<Native::ITTerminal> pitf;
					if (SUCCEEDED(cci->RequestTerminal(bstrName, (long)mediaType, (Native::TERMINAL_DIRECTION)direction, &pitf)))
					{
						if (pitf != NULL)
							return TTerminal::CreateTerminal(pitf);
					}
				}
				return nullptr;
			}

			TTerminal^ FindTerminal(TAPIMEDIATYPES mediaType, TERMINAL_DIRECTION direction);

			virtual String^ ToString() override
			{
				if (IsValid())
					return String::Format("TCall: {0} {1}", this->CallInfo[CALLINFO_LONG::CIL_CALLID], this->CallState);
				return __super::ToString();
			}
		};
	}
}