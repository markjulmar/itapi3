// TPhone.h
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
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

namespace JulMar
{
	namespace Tapi3
	{
		ref class TTapi;

		public enum struct PHONE_PRIVILEGE
		{
			PP_OWNER	= 0,
			PP_MONITOR	= ( PP_OWNER + 1 ) 
		};

		public enum struct PHONE_LAMP_MODE
		{	
			LM_DUMMY	= 0x1,
			LM_OFF	= 0x2,
			LM_STEADY	= 0x4,
			LM_WINK	= 0x8,
			LM_FLASH	= 0x10,
			LM_FLUTTER	= 0x20,
			LM_BROKENFLUTTER	= 0x40,
			LM_UNKNOWN	= 0x80
		};

		public enum struct PHONECAPS_LONG
		{	
			PCL_HOOKSWITCHES	= 0,
			PCL_HANDSETHOOKSWITCHMODES	= ( PCL_HOOKSWITCHES + 1 ) ,
			PCL_HEADSETHOOKSWITCHMODES	= ( PCL_HANDSETHOOKSWITCHMODES + 1 ) ,
			PCL_SPEAKERPHONEHOOKSWITCHMODES	= ( PCL_HEADSETHOOKSWITCHMODES + 1 ) ,
			PCL_DISPLAYNUMROWS	= ( PCL_SPEAKERPHONEHOOKSWITCHMODES + 1 ) ,
			PCL_DISPLAYNUMCOLUMNS	= ( PCL_DISPLAYNUMROWS + 1 ) ,
			PCL_NUMRINGMODES	= ( PCL_DISPLAYNUMCOLUMNS + 1 ) ,
			PCL_NUMBUTTONLAMPS	= ( PCL_NUMRINGMODES + 1 ) ,
			PCL_GENERICPHONE	= ( PCL_NUMBUTTONLAMPS + 1 ) 
		};

		public enum struct PHONECAPS_STRING
		{	
			PCS_PHONENAME	= 0,
			PCS_PHONEINFO	= ( PCS_PHONENAME + 1 ) ,
			PCS_PROVIDERINFO	= ( PCS_PHONEINFO + 1 ) 
		};

		public enum struct PHONECAPS_BUFFER
		{	
			PCB_DEVSPECIFICBUFFER	= 0
		};

		public enum struct PHONE_BUTTON_MODE
		{	
			PBM_DUMMY	= 0,
			PBM_CALL	= ( PBM_DUMMY + 1 ) ,
			PBM_FEATURE	= ( PBM_CALL + 1 ) ,
			PBM_KEYPAD	= ( PBM_FEATURE + 1 ) ,
			PBM_LOCAL	= ( PBM_KEYPAD + 1 ) ,
			PBM_DISPLAY	= ( PBM_LOCAL + 1 ) 
		};

		public enum struct PHONE_BUTTON_FUNCTION
		{	
			PBF_UNKNOWN	= 0,
			PBF_CONFERENCE	= ( PBF_UNKNOWN + 1 ) ,
			PBF_TRANSFER	= ( PBF_CONFERENCE + 1 ) ,
			PBF_DROP	= ( PBF_TRANSFER + 1 ) ,
			PBF_HOLD	= ( PBF_DROP + 1 ) ,
			PBF_RECALL	= ( PBF_HOLD + 1 ) ,
			PBF_DISCONNECT	= ( PBF_RECALL + 1 ) ,
			PBF_CONNECT	= ( PBF_DISCONNECT + 1 ) ,
			PBF_MSGWAITON	= ( PBF_CONNECT + 1 ) ,
			PBF_MSGWAITOFF	= ( PBF_MSGWAITON + 1 ) ,
			PBF_SELECTRING	= ( PBF_MSGWAITOFF + 1 ) ,
			PBF_ABBREVDIAL	= ( PBF_SELECTRING + 1 ) ,
			PBF_FORWARD	= ( PBF_ABBREVDIAL + 1 ) ,
			PBF_PICKUP	= ( PBF_FORWARD + 1 ) ,
			PBF_RINGAGAIN	= ( PBF_PICKUP + 1 ) ,
			PBF_PARK	= ( PBF_RINGAGAIN + 1 ) ,
			PBF_REJECT	= ( PBF_PARK + 1 ) ,
			PBF_REDIRECT	= ( PBF_REJECT + 1 ) ,
			PBF_MUTE	= ( PBF_REDIRECT + 1 ) ,
			PBF_VOLUMEUP	= ( PBF_MUTE + 1 ) ,
			PBF_VOLUMEDOWN	= ( PBF_VOLUMEUP + 1 ) ,
			PBF_SPEAKERON	= ( PBF_VOLUMEDOWN + 1 ) ,
			PBF_SPEAKEROFF	= ( PBF_SPEAKERON + 1 ) ,
			PBF_FLASH	= ( PBF_SPEAKEROFF + 1 ) ,
			PBF_DATAON	= ( PBF_FLASH + 1 ) ,
			PBF_DATAOFF	= ( PBF_DATAON + 1 ) ,
			PBF_DONOTDISTURB	= ( PBF_DATAOFF + 1 ) ,
			PBF_INTERCOM	= ( PBF_DONOTDISTURB + 1 ) ,
			PBF_BRIDGEDAPP	= ( PBF_INTERCOM + 1 ) ,
			PBF_BUSY	= ( PBF_BRIDGEDAPP + 1 ) ,
			PBF_CALLAPP	= ( PBF_BUSY + 1 ) ,
			PBF_DATETIME	= ( PBF_CALLAPP + 1 ) ,
			PBF_DIRECTORY	= ( PBF_DATETIME + 1 ) ,
			PBF_COVER	= ( PBF_DIRECTORY + 1 ) ,
			PBF_CALLID	= ( PBF_COVER + 1 ) ,
			PBF_LASTNUM	= ( PBF_CALLID + 1 ) ,
			PBF_NIGHTSRV	= ( PBF_LASTNUM + 1 ) ,
			PBF_SENDCALLS	= ( PBF_NIGHTSRV + 1 ) ,
			PBF_MSGINDICATOR	= ( PBF_SENDCALLS + 1 ) ,
			PBF_REPDIAL	= ( PBF_MSGINDICATOR + 1 ) ,
			PBF_SETREPDIAL	= ( PBF_REPDIAL + 1 ) ,
			PBF_SYSTEMSPEED	= ( PBF_SETREPDIAL + 1 ) ,
			PBF_STATIONSPEED	= ( PBF_SYSTEMSPEED + 1 ) ,
			PBF_CAMPON	= ( PBF_STATIONSPEED + 1 ) ,
			PBF_SAVEREPEAT	= ( PBF_CAMPON + 1 ) ,
			PBF_QUEUECALL	= ( PBF_SAVEREPEAT + 1 ) ,
			PBF_NONE	= ( PBF_QUEUECALL + 1 ) ,
			PBF_SEND	= ( PBF_NONE + 1 ) 
		};

		public enum struct PHONE_TONE
		{	
			PT_KEYPADZERO	= 0,
			PT_KEYPADONE	= ( PT_KEYPADZERO + 1 ) ,
			PT_KEYPADTWO	= ( PT_KEYPADONE + 1 ) ,
			PT_KEYPADTHREE	= ( PT_KEYPADTWO + 1 ) ,
			PT_KEYPADFOUR	= ( PT_KEYPADTHREE + 1 ) ,
			PT_KEYPADFIVE	= ( PT_KEYPADFOUR + 1 ) ,
			PT_KEYPADSIX	= ( PT_KEYPADFIVE + 1 ) ,
			PT_KEYPADSEVEN	= ( PT_KEYPADSIX + 1 ) ,
			PT_KEYPADEIGHT	= ( PT_KEYPADSEVEN + 1 ) ,
			PT_KEYPADNINE	= ( PT_KEYPADEIGHT + 1 ) ,
			PT_KEYPADSTAR	= ( PT_KEYPADNINE + 1 ) ,
			PT_KEYPADPOUND	= ( PT_KEYPADSTAR + 1 ) ,
			PT_KEYPADA	= ( PT_KEYPADPOUND + 1 ) ,
			PT_KEYPADB	= ( PT_KEYPADA + 1 ) ,
			PT_KEYPADC	= ( PT_KEYPADB + 1 ) ,
			PT_KEYPADD	= ( PT_KEYPADC + 1 ) ,
			PT_NORMALDIALTONE	= ( PT_KEYPADD + 1 ) ,
			PT_EXTERNALDIALTONE	= ( PT_NORMALDIALTONE + 1 ) ,
			PT_BUSY	= ( PT_EXTERNALDIALTONE + 1 ) ,
			PT_RINGBACK	= ( PT_BUSY + 1 ) ,
			PT_ERRORTONE	= ( PT_RINGBACK + 1 ) ,
			PT_SILENCE	= ( PT_ERRORTONE + 1 ) 
		};

		public ref class TPhone sealed : Internal::TapiBase
		{
		private:
			TTapi^ _owner;

			TPhone(TTapi^ owner, IUnknown* p) : Internal::TapiBase(p) 
			{
				_owner = owner;
			}

		protected public:
			static TPhone^ CreatePhone(TTapi^ owner, IUnknown* p);
			CComPtr<Native::ITPhone> GetPhoneItf() { return CastToInterface<Native::ITPhone,true>(); }

		public:
			~TPhone()
			{
				Release(false);
			}

			virtual void Release(bool inFinalizer) override;

			void Open(PHONE_PRIVILEGE privilege)
			{
				TapiException::ThrowExceptionForHR(GetPhoneItf()->Open((Native::PHONE_PRIVILEGE)privilege));
			}

			void Close()
			{
				GetPhoneItf()->Close();
			}

			property array<TAddress^>^ Addresses
			{
				array<TAddress^>^ get()
				{
					List<TAddress^>^ retData = gcnew List<TAddress^>();
					try
					{
						CComPtr<Native::IEnumAddress> peAddr;
						if (SUCCEEDED(GetPhoneItf()->EnumerateAddresses(&peAddr)))
						{
							CComPtr<Native::ITAddress> paddr;
							while (peAddr->Next(1, &paddr, NULL) == S_OK)
							{
								retData->Add(TAddress::CreateAddress(_owner, paddr));
								paddr = NULL;
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

			property long PhoneCapability[PHONECAPS_LONG]
			{
				long get(PHONECAPS_LONG cap)
				{
					long lValue;
					TapiException::ThrowExceptionForHR(this->GetPhoneItf()->get_PhoneCapsLong((Native::PHONECAPS_LONG)cap, &lValue));
					return lValue;
				}
			}

			property String^ PhoneCapability[PHONECAPS_STRING]
			{
				String^ get(PHONECAPS_STRING cap)
				{
					CComBSTR bstrValue;
					TapiException::ThrowExceptionForHR(this->GetPhoneItf()->get_PhoneCapsString((Native::PHONECAPS_STRING)cap, &bstrValue));
					return gcnew String((wchar_t*)bstrValue);
				}
			}

			array<TTerminal^>^ GetTerminals(TAddress^ addr)
			{
				List<TTerminal^>^ retList = gcnew List<TTerminal^>();

				CComPtr<Native::IEnumTerminal> iePtr;
				TapiException::ThrowExceptionForHR(GetPhoneItf()->EnumerateTerminals(addr->GetAddressItf(), &iePtr));
				CComPtr<Native::ITTerminal> termInfo;
				while (iePtr->Next(1, &termInfo, NULL) == S_OK)
				{
					retList->Add(TTerminal::CreateTerminal(termInfo));
					termInfo = NULL;
				}

				return retList->ToArray();
			}

			property PHONE_BUTTON_MODE ButtonMode[long] 
			{
				PHONE_BUTTON_MODE get(long buttonId) 
				{
					Native::PHONE_BUTTON_MODE value;
					TapiException::ThrowExceptionForHR(GetPhoneItf()->get_ButtonMode(buttonId, &value));
					return (PHONE_BUTTON_MODE) value;
				}

				void set(long buttonId, PHONE_BUTTON_MODE value)
				{
					TapiException::ThrowExceptionForHR(GetPhoneItf()->put_ButtonMode(buttonId, (Native::PHONE_BUTTON_MODE)value));
				}
			}
			
			property PHONE_BUTTON_FUNCTION ButtonFunction[long] 
			{
				PHONE_BUTTON_FUNCTION get(long buttonId) 
				{
					Native::PHONE_BUTTON_FUNCTION value;
					TapiException::ThrowExceptionForHR(GetPhoneItf()->get_ButtonFunction(buttonId, &value));
					return (PHONE_BUTTON_FUNCTION) value;
				}

				void set(long buttonId, PHONE_BUTTON_FUNCTION value)
				{
					TapiException::ThrowExceptionForHR(GetPhoneItf()->put_ButtonFunction(buttonId, (Native::PHONE_BUTTON_FUNCTION)value));
				}
			}

			property String^ ButtonText[long] 
			{
				String^ get(long buttonId) 
				{
					CComBSTR bstrValue;
					TapiException::ThrowExceptionForHR(GetPhoneItf()->get_ButtonText(buttonId, &bstrValue));
					return gcnew String((wchar_t*)bstrValue);
				}

				void set(long buttonId, String^ value)
				{
					CComBSTR bstrValue;
					if (!String::IsNullOrEmpty(value))
						bstrValue = (BSTR) Marshal::StringToBSTR(value).ToPointer();
					TapiException::ThrowExceptionForHR(GetPhoneItf()->put_ButtonText(buttonId, bstrValue));
				}
			}

			property PHONE_BUTTON_STATE ButtonState[long] 
			{
				PHONE_BUTTON_STATE get(long buttonId) 
				{
					Native::PHONE_BUTTON_STATE value;
					TapiException::ThrowExceptionForHR(GetPhoneItf()->get_ButtonState(buttonId, &value));
					return (PHONE_BUTTON_STATE) value;
				}
			}

			property PHONE_HOOK_SWITCH_STATE HookSwitchState[PHONE_HOOK_SWITCH_DEVICE] 
			{
				PHONE_HOOK_SWITCH_STATE get(PHONE_HOOK_SWITCH_DEVICE id) 
				{
					Native::PHONE_HOOK_SWITCH_STATE value;
					TapiException::ThrowExceptionForHR(GetPhoneItf()->get_HookSwitchState((Native::PHONE_HOOK_SWITCH_DEVICE)id, &value));
					return (PHONE_HOOK_SWITCH_STATE) value;
				}

				void set(PHONE_HOOK_SWITCH_DEVICE id, PHONE_HOOK_SWITCH_STATE value)
				{
					TapiException::ThrowExceptionForHR(GetPhoneItf()->put_HookSwitchState((Native::PHONE_HOOK_SWITCH_DEVICE)id, (Native::PHONE_HOOK_SWITCH_STATE)value));
				}
			}

			property long RingMode
			{
				long get()
				{
					long value;
					TapiException::ThrowExceptionForHR(GetPhoneItf()->get_RingMode(&value));
					return value;
				}

				void set(long value)
				{
					TapiException::ThrowExceptionForHR(GetPhoneItf()->put_RingMode(value));
				}
			}

			property long RingVolume
			{
				long get()
				{
					long value;
					TapiException::ThrowExceptionForHR(GetPhoneItf()->get_RingVolume(&value));
					return value;
				}

				void set(long value)
				{
					TapiException::ThrowExceptionForHR(GetPhoneItf()->put_RingVolume(value));
				}
			}

			property PHONE_PRIVILEGE Privilege
			{
				PHONE_PRIVILEGE get()
				{
					Native::PHONE_PRIVILEGE value;
					TapiException::ThrowExceptionForHR(GetPhoneItf()->get_Privilege(&value));
					return (PHONE_PRIVILEGE) value;
				}
			}

			array<byte>^ GetPhoneCapsBuffer(PHONECAPS_BUFFER id)
			{
				array<byte>^ retData = nullptr;
				BYTE* lpdw;
				DWORD dwSize = 0; 

				if (SUCCEEDED(GetPhoneItf()->GetPhoneCapsBuffer((Native::PHONECAPS_BUFFER)id, &dwSize, &lpdw)))
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

			property PHONE_LAMP_MODE LampMode[long] 
			{
				PHONE_LAMP_MODE get(long buttonId) 
				{
					Native::PHONE_LAMP_MODE value;
					TapiException::ThrowExceptionForHR(GetPhoneItf()->get_LampMode(buttonId, &value));
					return (PHONE_LAMP_MODE) value;
				}
			}

			property String^ Display
			{
				String^ get()
				{
					CComBSTR bstrValue;
					TapiException::ThrowExceptionForHR(GetPhoneItf()->get_Display(&bstrValue));
					return gcnew String((wchar_t*)bstrValue);
				}
			}

			void SetDisplay(long row, long col, String^ line)
			{
				CComBSTR bstrValue;
				if (!String::IsNullOrEmpty(line))
					bstrValue = (BSTR) Marshal::StringToBSTR(line).ToPointer();
				TapiException::ThrowExceptionForHR(GetPhoneItf()->SetDisplay(row, col, bstrValue));
			}

			property array<TAddress^>^ PreferredAddresses
			{
				array<TAddress^>^ get()
				{
					List<TAddress^>^ retData = gcnew List<TAddress^>();

					try
					{
						CComPtr<Native::IEnumAddress> peAddr;
						if (SUCCEEDED(GetPhoneItf()->EnumeratePreferredAddresses(&peAddr)))
						{
							CComPtr<Native::ITAddress> paddr;
							while (peAddr->Next(1, &paddr, NULL) == S_OK)
							{
								retData->Add(TAddress::CreateAddress(_owner, paddr));
								paddr = NULL;
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

			void DeviceSpecific(array<byte>^ data)
			{
				CHeapPtr<byte, CComAllocator> lpdw;
				DWORD dwSize = data->Length;
				if (dwSize > 0)
				{
					lpdw.Allocate(dwSize);
					pin_ptr<byte> srcData = &data[0];
					memcpy_s(lpdw, dwSize, srcData, dwSize);
				}

				TapiException::ThrowExceptionForHR(GetPhoneItf()->DeviceSpecific(lpdw, dwSize));
			}

			long NegotiateExtVersion(long lowVersion, long hiVersion)
			{
				long rVersion;
				TapiException::ThrowExceptionForHR(GetPhoneItf()->NegotiateExtVersion(lowVersion, hiVersion, &rVersion));
				return rVersion;
			}

		};
	}
}