// ITapi3.cpp
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

#include "stdafx.h"
#include "TapiException.h"
#include "TapiBase.h"
#include "TStream.h"
#include "events.h"
#include "TFileTrack.h"
#include "TCallHub.h"
#include "TCall.h"
#include "TAddress.h"
#include "TPhone.h"
#include "ttapi.h"
#include <initguid.h>
#include <uuids.h>

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;
using namespace JulMar::Tapi3;

//
// General Information about an assembly is controlled through the following
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
//
[assembly:AssemblyTitleAttribute("ITapi3")];
[assembly:AssemblyDescriptionAttribute("TAPI 3.x .NET wrapper")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("JulMar Technology, Inc.")];
[assembly:AssemblyProductAttribute("ITapi3")];
[assembly:AssemblyCopyrightAttribute("Copyright (c) JulMar Technology, Inc. 2006-2010")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];
[assembly:AssemblyVersionAttribute("1.0.0.3")];
[assembly:ComVisible(false)];
[assembly:CLSCompliantAttribute(true)];
[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiObjectEventArgs::TapiObjectEventArgs
//
// Constructor for the TapiObjectEventArgs event argument structure
//
TapiObjectEventArgs::TapiObjectEventArgs(TTapi^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITTAPIObjectEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		Native::TAPIOBJECT_EVENT evt;
		pevt->get_Event(&evt);
		_evt = (TAPIOBJECT_EVENT) evt;

		CComPtr<Native::ITAddress> piaddr;
		HRESULT hr = pevt->get_Address(&piaddr);
		if (SUCCEEDED(hr))
			_addr = TAddress::CreateAddress(owner, piaddr);
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITTAPIObjectEvent::get_Address failed hr=0x{0:X}", hr);
			_addr = nullptr;
		}

		// See if we can get an ITTAPIObjectEvent2 from it (TAPI3.1)
		CComPtr<Native::ITTAPIObjectEvent2> pev2;
		if (SUCCEEDED(piDispatch->QueryInterface(Native::IID_ITTAPIObjectEvent2, (void**)&pev2)) && pev2 != NULL)
		{
			CComPtr<Native::ITPhone> piphone;
			hr = pev2->get_Phone(&piphone);
			if (SUCCEEDED(hr))
				_phone = TPhone::CreatePhone(owner, piphone);
			else
			{
				TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITTAPIObjectEvent2::get_Phone failed hr=0x{0:X}", hr);
				_phone = nullptr;
			}
		}
	}

}// TapiObjectEventArgs::TapiObjectEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiAddressChangedEventArgs::TapiAddressChangedEventArgs
//
// Constructor for the TapiAddressChangedEventArgs event argument structure
//
TapiAddressChangedEventArgs::TapiAddressChangedEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	_address = owner;
	CComQIPtr<Native::ITAddressEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		Native::ADDRESS_EVENT evt;
		pevt->get_Event(&evt);
		_evt = (ADDRESS_EVENT) evt;

		CComPtr<Native::ITTerminal> piTerm;
		HRESULT hr = pevt->get_Terminal(&piTerm);
		if (SUCCEEDED(hr))
			_terminal = owner->FindTerminalByInterface(piTerm);
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITAddressEvent::get_Terminal failed hr=0x{0:X}", hr);
			_terminal = nullptr;
		}
	}

}// TapiAddressChangedEventArgs::TapiAddressChangedEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiCallNotificationEventArgs::TapiCallNotificationEventArgs
//
// Constructor for the TapiCallNotificationEventArgs
//
TapiCallNotificationEventArgs::TapiCallNotificationEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITCallNotificationEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		Native::CALL_NOTIFICATION_EVENT evt;
		pevt->get_Event(&evt);
		_evt = (CALL_NOTIFICATION_EVENT) evt;

		CComPtr<Native::ITCallInfo> piCall;
		HRESULT hr = pevt->get_Call(&piCall);
		if (SUCCEEDED(hr))
			_call = TCall::CreateCallAppearance(owner, piCall);
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITCallNotificationEvent::get_Call failed hr=0x{0:X}", hr);
			_call = nullptr;
		}
	}

}// TapiCallNotificationEventArgs::TapiCallNotificationEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiCallMediaEventArgs::TapiCallMediaEventArgs
//
// Constructor for the TapiCallMediaEventArgs
//
TapiCallMediaEventArgs::TapiCallMediaEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITCallMediaEvent> pevt(piDispatch);

	CComPtr<Native::ITCallInfo> piCall;
	if (SUCCEEDED(pevt->get_Call(&piCall)))
		_call = TCall::CreateCallAppearance(owner, piCall);
	else
		_call = nullptr;

	Native::CALL_MEDIA_EVENT evt;
	pevt->get_Event(&evt);
	_event = (CALL_MEDIA_EVENT) evt;

	Native::CALL_MEDIA_EVENT_CAUSE cause;
	pevt->get_Cause(&cause);
	_cause = (CALL_MEDIA_EVENT_CAUSE) cause;

	CComPtr<Native::ITStream> piStm;
	HRESULT hr = pevt->get_Stream(&piStm);
	if (SUCCEEDED(hr))
		_stm = TStream::CreateStream(piStm);
	else
	{
		TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITCallMediaEvent::get_Stream failed hr=0x{0:X}", hr);
		_stm = nullptr;
	}

	CComPtr<Native::ITTerminal> piTerm;
	hr = pevt->get_Terminal(&piTerm);
	if (SUCCEEDED(hr))
	{
		if (piTerm == NULL && _stm != nullptr)
			_terminal = _stm->FindTerminal(_stm->MediaType, _stm->Direction);
		else
			_terminal = TTerminal::CreateTerminal(piTerm);
	}
	else
	{
		TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITCallMediaEvent::get_Terminal failed hr=0x{0:X}", hr);
		_terminal = nullptr;
	}

	HRESULT hrErr;
	hr = pevt->get_Error(&hrErr);
	if (SUCCEEDED(hr) && FAILED(hrErr))
		_err = gcnew TapiException(hrErr);
	else
		_err = nullptr;

}// TapiCallMediaEventArgs::TapiCallMediaEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiCallStateEventArgs::TapiCallStateEventArgs
//
// Constructor for the TapiCallStateEventArgs
//
TapiCallStateEventArgs::TapiCallStateEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITCallStateEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		Native::CALL_STATE state;
		pevt->get_State(&state);
		_cs = (CALL_STATE) state;

		Native::CALL_STATE_EVENT_CAUSE cause;
		pevt->get_Cause(&cause);
		_ce = (CALL_STATE_EVENT_CAUSE) cause;

		CComPtr<Native::ITCallInfo> piCall;
		HRESULT hr = pevt->get_Call(&piCall);
		if (SUCCEEDED(hr))
			_call = TCall::CreateCallAppearance(owner, piCall);
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITCallStateEvent::get_Call failed hr=0x{0:X}", hr);
			_call = nullptr;
		}
	}

}// TapiCallStateEventArgs::TapiCallStateEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiPhoneEventArgs::TapiPhoneEventArgs
//
// PhoneEvent structure
//
TapiPhoneEventArgs::TapiPhoneEventArgs(TTapi^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITPhoneEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		CComPtr<Native::ITPhone> piPhone;
		HRESULT hr = pevt->get_Phone(&piPhone);
		if (SUCCEEDED(hr))
			_phone = TPhone::CreatePhone(owner, piPhone);
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITPhoneEvent::get_Phone failed hr=0x{0:X}", hr);
			_phone = nullptr;
		}

		Native::PHONE_EVENT evt;
		pevt->get_Event(&evt);
		_event = (PHONE_EVENT) evt;

		Native::PHONE_BUTTON_STATE state;
		pevt->get_ButtonState(&state);
		_buttonState = (PHONE_BUTTON_STATE) state;

		Native::PHONE_HOOK_SWITCH_STATE hstate;
		pevt->get_HookSwitchState(&hstate);
		_hsState = (PHONE_HOOK_SWITCH_STATE) hstate;

		Native::PHONE_HOOK_SWITCH_DEVICE dev;
		pevt->get_HookSwitchDevice(&dev);
		_hsDevice = (PHONE_HOOK_SWITCH_DEVICE) dev;

		long lValue;
		pevt->get_RingMode(&lValue);
		_ringMode = lValue;

		pevt->get_ButtonLampId(&lValue);
		_lampId = lValue;

		CComBSTR bstrValue;
		if (SUCCEEDED(pevt->get_NumberGathered(&bstrValue)))
			_number = gcnew String((wchar_t*)bstrValue);
		else
			_number = String::Empty;

		_call = nullptr;

		CComPtr<Native::ITCallInfo> piCall;
		hr = pevt->get_Call(&piCall);
		if (SUCCEEDED(hr))
		{
			CComPtr<Native::ITAddress> piAddr;
			piCall->get_Address(&piAddr);
			if (piAddr != NULL)
			{
				TAddress^ addr = TAddress::CreateAddress(owner, piAddr);
				_call = TCall::CreateCallAppearance(addr, piCall);
			}
		}
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITPhoneEvent::get_Call failed hr=0x{0:X}", hr);
		}
	}

}// TapiPhoneEventArgs::TapiPhoneEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiPhoneDeviceSpecificEventArgs::TapiPhoneDeviceSpecificEventArgs
//
// PhoneEvent dev-specific structure
//
TapiPhoneDeviceSpecificEventArgs::TapiPhoneDeviceSpecificEventArgs(TTapi^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITPhoneDeviceSpecificEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		CComPtr<Native::ITPhone> piphone;
		HRESULT hr = pevt->get_Phone(&piphone);
		if (SUCCEEDED(hr))
			_phone = TPhone::CreatePhone(owner, piphone);
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITPhoneDeviceSpecificEvent::get_Phone failed hr=0x{0:X}", hr);
			_phone = nullptr;
		}

		long value;
		if (SUCCEEDED(pevt->get_lParam1(&value)))
			_lParam1 = value;
		else
			_lParam1 = 0;
		if (SUCCEEDED(pevt->get_lParam2(&value)))
			_lParam2 = value;
		else
			_lParam2 = 0;
		if (SUCCEEDED(pevt->get_lParam3(&value)))
			_lParam3 = value;
		else
			_lParam3 = 0;
	}

}// TapiPhoneDeviceSpecificEventArgs::TapiPhoneDeviceSpecificEventArgsv

/////////////////////////////////////////////////////////////////////////////////////////////
// TAddress::Monitor
//
// Registers for Monitor privileges with an address
//
void TAddress::Monitor(TAPIMEDIATYPES supportedMediaTypes)
{
	if (_notify != -1)
		throw gcnew InvalidOperationException("The address is already open");
	_notify = _owner->RegisterCallNotifications(GetAddressItf(), VARIANT_TRUE, VARIANT_FALSE, (long)supportedMediaTypes);

}// TAddress::Monitor

/////////////////////////////////////////////////////////////////////////////////////////////
// TAddress::Open
//
// Registers for owner privileges with an address
//
void TAddress::Open(TAPIMEDIATYPES supportedMediaTypes)
{
	if (_notify != -1)
		throw gcnew InvalidOperationException("The address is already open");
	_notify = _owner->RegisterCallNotifications(GetAddressItf(), VARIANT_FALSE, VARIANT_TRUE, (long)supportedMediaTypes);

}// TAddress::Open

/////////////////////////////////////////////////////////////////////////////////////////////
// TAddress::OpenAndMonitor
//
// Registers for owner privileges with an address
//
void TAddress::OpenAndMonitor(TAPIMEDIATYPES supportedMediaTypes)
{
	if (_notify != -1)
		throw gcnew InvalidOperationException("The address is already open");
	_notify = _owner->RegisterCallNotifications(GetAddressItf(), VARIANT_TRUE, VARIANT_TRUE, (long)supportedMediaTypes);

}// TAddress::OpenAndMonitor

/////////////////////////////////////////////////////////////////////////////////////////////
// TAddress::Close
//
// Stops notifications for an address
//
void TAddress::Close()
{
	if (_notify != -1)
	{
		_owner->UnregisterNotifications(_notify);
		_notify = -1;
	}

}// TAddress::Close

/////////////////////////////////////////////////////////////////////////////////////////////
// TAddress::SetCallHubTracking
//
// Starts/Stops call hub tracking
//
void TAddress::SetCallHubTracking(bool onoff)
{
	_owner->SetCallHubTracking(GetAddressItf(), (onoff) ? VARIANT_TRUE : VARIANT_FALSE);

}// TAddress::SetCallHubTracking

/////////////////////////////////////////////////////////////////////////////////////////////
// TCallHub::EnumerateCalls
//
// Enumerate the calls in a call hub
//
array<TCall^>^ TCallHub::EnumerateCalls()
{
	List<TCall^>^ retList = gcnew List<TCall^>();
	try 
	{
		CComPtr<Native::IEnumCall> iePtr;
		TapiException::ThrowExceptionForHR(GetCallHubItf()->EnumerateCalls(&iePtr));
		CComPtr<Native::ITCallInfo> callInfo;
		while (iePtr->Next(1, &callInfo, NULL) == S_OK)
		{
			CComPtr<Native::ITAddress> piaddr;
			HRESULT hr = callInfo->get_Address(&piaddr);
			if (SUCCEEDED(hr))
			{
				retList->Add(TCall::CreateCallAppearance(_owner->FindInterface<TAddress^>(piaddr), callInfo));
				piaddr = NULL;
			}
			callInfo = NULL;
		}
	}
	catch (Exception^)
	{

	}
	return retList->ToArray();

}// TCallHub::EnumerateCalls

/////////////////////////////////////////////////////////////////////////////////////////////
// TCall::GetCallHub
//
// Retrieve the call hub for a call
//
TCallHub^ TCall::GetCallHub()
{
	Native::ITCallHub* ch;
	HRESULT hr = GetCallInfoItf()->get_CallHub(&ch);
	if (SUCCEEDED(hr) && ch != NULL)
		return TCallHub::CreateCallHub(_owner->GetOwner(), ch);
	return nullptr;

}// TCall::GetCallHub

/////////////////////////////////////////////////////////////////////////////////////////////
// TCall::CreateCallAppearance
//
// Creates a new call appearance
//
TCall^ TCall::CreateCallAppearance(TAddress^ addr, IUnknown* p)
{
	if (p == NULL || addr == nullptr)
		return nullptr;

	TCall^ existingCall = TTapi::FindInterface<TCall^>(p);
	if (existingCall == nullptr)
	{
		existingCall = gcnew TCall(addr, p);
		TTapi::AddInterface(existingCall);
	}
	return existingCall;

}// TCall::CreateCallAppearance

/////////////////////////////////////////////////////////////////////////////////////////////
// TCallHub::CreateCallHub
//
// Creates a new call hub
//
TCallHub^ TCallHub::CreateCallHub(TTapi^ owner, IUnknown* p)
{
	if (p == NULL)
		return nullptr;

	TCallHub^ existingHub = TTapi::FindInterface<TCallHub^>(p);
	if (existingHub == nullptr)
	{
		existingHub = gcnew TCallHub(owner, p);
		TTapi::AddInterface(existingHub);
	}
	return existingHub;

}// TCallHub::CreateCallHub

/////////////////////////////////////////////////////////////////////////////////////////////
// TPhone::CreatePhone
//
// Creates a new address object
//
TPhone^ TPhone::CreatePhone(TTapi^ owner, IUnknown* p)
{
	if (p == NULL)
		return nullptr;

	TPhone^ existingPhone = TTapi::FindInterface<TPhone^>(p);
	if (existingPhone == nullptr)
	{
		existingPhone = gcnew TPhone(owner, p);
		TTapi::AddInterface(existingPhone);
	}
	return existingPhone;

}// TPhone::CreatePhone

/////////////////////////////////////////////////////////////////////////////////////////////
// TAddress::CreateAddress
//
// Creates a new address object
//
TAddress^ TAddress::CreateAddress(TTapi^ owner, IUnknown* p)
{
	if (p == NULL)
		return nullptr;

	TAddress^ existingAddr = TTapi::FindInterface<TAddress^>(p);
	if (existingAddr == nullptr)
	{
		existingAddr = gcnew TAddress(owner, p);
		TTapi::AddInterface(existingAddr);
	}
	return existingAddr;

}// TAddress::CreateAddress

/////////////////////////////////////////////////////////////////////////////////////////////
// TTerminal::CreateTerminal
//
// Creates a new address object
//
TTerminal^ TTerminal::CreateTerminal(IUnknown* p)
{
	if (p == NULL)
		return nullptr;

	TTerminal^ existingTerm = TTapi::FindInterface<TTerminal^>(p);
	if (existingTerm == nullptr)
	{
		existingTerm = gcnew TTerminal(p);
		TTapi::AddInterface(existingTerm);
	}
	return existingTerm;

}// TTerminal::CreateTerminal

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiCallHubEventArgs::TapiCallHubEventArgs
//
// TapiCallHubEventArgs constructor
//
TapiCallHubEventArgs::TapiCallHubEventArgs(TTapi^ tapiOb, TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITCallHubEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		CComPtr<Native::ITCallInfo> piCall;
		HRESULT hr = pevt->get_Call(&piCall);
		if (SUCCEEDED(hr))
			_call = TCall::CreateCallAppearance(owner, piCall);
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITCallHubEvent::get_Call failed hr=0x{0:X}", hr);
			_call = nullptr;
		}

		CComPtr<Native::ITCallHub> piHub;
		hr = pevt->get_CallHub(&piHub);
		if (SUCCEEDED(hr))
			_hub = TCallHub::CreateCallHub(tapiOb, piHub);
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITCallHubEvent::get_CallHub failed hr=0x{0:X}", hr);
			_hub = nullptr;
		}
	}

}// TapiCallHubEventArgs::TapiCallHubEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiCallInfoChangeEventArgs::TapiCallInfoChangeEventArgs
//
// TapiCallHubEventArgs constructor
//
TapiCallInfoChangeEventArgs::TapiCallInfoChangeEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITCallInfoChangeEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		CComPtr<Native::ITCallInfo> piCall;
		HRESULT hr = pevt->get_Call(&piCall);
		if (SUCCEEDED(hr))
			_call = TCall::CreateCallAppearance(owner, piCall);
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITCallInfoChangeEvent::get_Call failed hr=0x{0:X}", hr);
			_call = nullptr;
		}

		Native::CALLINFOCHANGE_CAUSE cause;
		if (SUCCEEDED(pevt->get_Cause(&cause)))
			_cause = (CALLINFOCHANGE_CAUSE) cause;
		else
			_cause = CALLINFOCHANGE_CAUSE::CIC_OTHER;
	}

}// TapiCallInfoChangeEventArgs::TapiCallInfoChangeEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiQOSEventArgs::TapiQOSEventArgs
//
// TapiQOSEventArgs constructor
//
TapiQOSEventArgs::TapiQOSEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITQOSEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		CComPtr<Native::ITCallInfo> piCall;
		HRESULT hr = pevt->get_Call(&piCall);
		if (SUCCEEDED(hr))
			_call = TCall::CreateCallAppearance(owner, piCall);
		else
		{
			TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITQOSEvent::get_Call failed hr=0x{0:X}", hr);
			_call = nullptr;
		}

		Native::QOS_EVENT evt;
		if (SUCCEEDED(pevt->get_Event(&evt)))
			_event = (QOS_EVENT) evt;
		else
			_event = QOS_EVENT::QE_NOQOS;

		long value;
		if (SUCCEEDED(pevt->get_MediaType(&value)))
			_media = (TAPIMEDIATYPES)value;
		else
			_media = TAPIMEDIATYPES::AUDIO;
	}

}// TapiQOSEventArgs::TapiQOSEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiTTSTerminalEventArgs::TapiTTSTerminalEventArgs
//
// Constructor for the TapiTSTerminalEventArgs
//
TapiTTSTerminalEventArgs::TapiTTSTerminalEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITTTSTerminalEvent> pevt(piDispatch);

	CComPtr<Native::ITCallInfo> piCall;
	HRESULT hr = pevt->get_Call(&piCall);
	if (SUCCEEDED(hr))
		_call = TCall::CreateCallAppearance(owner, piCall);
	else
	{
		TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITTTSTerminalEvent::get_Call failed hr=0x{0:X}", hr);
		_call = nullptr;
	}

	CComPtr<Native::ITTerminal> piTerm;
	hr = pevt->get_Terminal(&piTerm);
	if (SUCCEEDED(hr))
		_terminal = TTerminal::CreateTerminal(piTerm);
	else
	{
		TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITTTSTerminalEvent::get_Terminal failed hr=0x{0:X}", hr);
		_terminal = nullptr;
	}

	if (SUCCEEDED(pevt->get_Error(&hr)) && FAILED(hr))
		_error = gcnew TapiException(hr);
	else
		_error = nullptr;

}// TapiTTSTerminalEventArgs::TapiTTSTerminalEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiASRTerminalEventArgs::TapiASRTerminalEventArgs
//
// Constructor for the TapiASRTerminalEventArgs
//
TapiASRTerminalEventArgs::TapiASRTerminalEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITASRTerminalEvent> pevt(piDispatch);

	CComPtr<Native::ITCallInfo> piCall;
	HRESULT hr = pevt->get_Call(&piCall);
	if (SUCCEEDED(hr))
		_call = TCall::CreateCallAppearance(owner, piCall);
	else
	{
		TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITASRTerminalEvent::get_Call failed hr=0x{0:X}", hr);
		_call = nullptr;
	}

	CComPtr<Native::ITTerminal> piTerm;
	hr = pevt->get_Terminal(&piTerm);
	if (SUCCEEDED(hr))
		_terminal = TTerminal::CreateTerminal(piTerm);
	else
	{
		TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, "ITASRTerminalEvent::get_Terminal failed hr=0x{0:X}", hr);
		_terminal = nullptr;
	}

	if (SUCCEEDED(pevt->get_Error(&hr)) && FAILED(hr))
		_error = gcnew TapiException(hr);
	else
		_error = nullptr;

}// TapiASRTerminalEventArgs::TapiASRTerminalEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiAddressDeviceSpecificEventArgs::TapiAddressDeviceSpecificEventArgs
//
// Constructor for the TapiAddressDeviceSpecificEventArgs event argument structure
//
TapiAddressDeviceSpecificEventArgs::TapiAddressDeviceSpecificEventArgs(TTapi^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITAddressDeviceSpecificEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		CComPtr<Native::ITAddress> piaddr;
		if (SUCCEEDED(pevt->get_Address(&piaddr)))
			_addr = TAddress::CreateAddress(owner, piaddr);
		else
			_addr = nullptr;

		CComPtr<Native::ITCallInfo> piCall;
		if (SUCCEEDED(pevt->get_Call(&piCall)))
			_call = TCall::CreateCallAppearance(_addr, piCall);
		else
			_call = nullptr;

		long value;
		if (SUCCEEDED(pevt->get_lParam1(&value)))
			_lParam1 = value;
		else
			_lParam1 = 0;
		if (SUCCEEDED(pevt->get_lParam2(&value)))
			_lParam2 = value;
		else
			_lParam2 = 0;
		if (SUCCEEDED(pevt->get_lParam3(&value)))
			_lParam3 = value;
		else
			_lParam3 = 0;
	}

}// TapiAddressDeviceSpecificEventArgs::TapiAddressDeviceSpecificEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiToneTerminalEventArgs::TapiToneTerminalEventArgs
//
// Constructor for the TapiToneTerminalEventArgs
//
TapiToneTerminalEventArgs::TapiToneTerminalEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITToneTerminalEvent> pevt(piDispatch);

	CComPtr<Native::ITCallInfo> piCall;
	if (SUCCEEDED(pevt->get_Call(&piCall)))
		_call = TCall::CreateCallAppearance(owner, piCall);
	else
		_call = nullptr;

	CComPtr<Native::ITTerminal> piTerm;
	if (SUCCEEDED(pevt->get_Terminal(&piTerm)))
		_terminal = TTerminal::CreateTerminal(piTerm);
	else
		_terminal = nullptr;

	HRESULT hr;
	if (SUCCEEDED(pevt->get_Error(&hr)) && FAILED(hr))
		_error = gcnew TapiException(hr);
	else
		_error = nullptr;

}// TapiToneTerminalEventArgs::TapiToneTerminalEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiDigitDetectionEventArgs::TapiDigitDetectionEventArgs
//
// Digit detection event args constructor
//
TapiDigitDetectionEventArgs::TapiDigitDetectionEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITDigitDetectionEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		CComPtr<Native::ITCallInfo> piCall;
		if (SUCCEEDED(pevt->get_Call(&piCall)))
			_call = TCall::CreateCallAppearance(owner, piCall);
		else
			_call = nullptr;

		unsigned char ch;
		if (SUCCEEDED(pevt->get_Digit(&ch)))
			_digit = (byte) ch;
		long l;

		if (SUCCEEDED(pevt->get_DigitMode(&l)))
			_mode = (LINEDIGITMODE) l;
		else
			_mode = LINEDIGITMODE::DTMF;

		if (SUCCEEDED(pevt->get_TickCount(&l)))
			_tickCount = l;
		else
			_tickCount = 0;
	}

}// TapiDigitDetectionEventArgs::TapiDigitDetectionEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiDigitGenerationEventArgs::TapiDigitGenerationEventArgs
//
// Digit detection event args constructor
//
TapiDigitGenerationEventArgs::TapiDigitGenerationEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITDigitGenerationEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		CComPtr<Native::ITCallInfo> piCall;
		if (SUCCEEDED(pevt->get_Call(&piCall)))
			_call = TCall::CreateCallAppearance(owner, piCall);
		else
			_call = nullptr;

		long l;
		if (SUCCEEDED(pevt->get_TickCount(&l)))
			_tickCount = l;
		else
			_tickCount = 0;
		if (SUCCEEDED(pevt->get_GenerationTermination(&l)))
			_term = (LINEGENERATETERMINATOR) l;
		else
			_term = LINEGENERATETERMINATOR::Done;
	}

}// TapiDigitGenerationEventArgs::TapiDigitGenerationEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiToneDetectionEventArgs::TapiToneDetectionEventArgs
//
// Constructor for the TapiToneDetectionEventArgs
//
TapiToneDetectionEventArgs::TapiToneDetectionEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITToneDetectionEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		CComPtr<Native::ITCallInfo> piCall;
		if (SUCCEEDED(pevt->get_Call(&piCall)))
			_call = TCall::CreateCallAppearance(owner, piCall);
		else
			_call = nullptr;

		long l;
		if (SUCCEEDED(pevt->get_TickCount(&l)))
			_tickCount = l;
		else
			_tickCount = 0;

		if (SUCCEEDED(pevt->get_AppSpecific(&l)))
			_appSpecific = l;
		else
			_appSpecific = 0;

		//if (SUCCEEDED(pevt->get_ToneListID(&l)))
		//	_index = l;
		//else
		//	_index = -1;
		_index = -1;
	}

}// TapiToneDetectionEventArgs::TapiToneDetectionEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiDigitsGatheredEventArgs::TapiDigitsGatheredEventArgs
//
// Constructor for the TapiDigitsGatheredEventArgs
//
TapiDigitsGatheredEventArgs::TapiDigitsGatheredEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITDigitsGatheredEvent> pevt(piDispatch);
	if (pevt != NULL)
	{
		CComPtr<Native::ITCallInfo> piCall;
		if (SUCCEEDED(pevt->get_Call(&piCall)))
			_call = TCall::CreateCallAppearance(owner, piCall);
		else
			_call = nullptr;

		long l;
		if (SUCCEEDED(pevt->get_TickCount(&l)))
			_tickCount = l;
		else
			_tickCount = 0;

		CComBSTR bstr;
		if (SUCCEEDED(pevt->get_Digits(&bstr)))
			_digits = gcnew String((wchar_t*)bstr);
		else
			_digits = String::Empty;

		Native::TAPI_GATHERTERM gt;
		if (SUCCEEDED(pevt->get_GatherTermination(&gt)))
			_term = (TAPI_GATHERTERM)gt;
		else
			_term = TAPI_GATHERTERM::TGT_CANCEL;
	}

}// TapiDigitsGatheredEventArgs::TapiDigitsGatheredEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TCall::SelectTerminalOnCall
//
// Select a terminal for the call
//
void TCall::SelectTerminalOnCall(TTerminal^ term)
{
	CComPtr<Native::ITTerminal> pi(term->GetTerminalItf());
	TapiException::ThrowExceptionForHR(GetBasicCallControl2Itf()->SelectTerminalOnCall(pi));

}// TCall::SelectTerminalOnCall

/////////////////////////////////////////////////////////////////////////////////////////////
// TCall::UnselectTerminalOnCall
//
// Un select a terminal for the call
//
void TCall::UnselectTerminalOnCall(TTerminal^ term)
{
	CComPtr<Native::ITTerminal> pi(term->GetTerminalItf());
	TapiException::ThrowExceptionForHR(GetBasicCallControl2Itf()->UnselectTerminalOnCall(pi));

}// TCall::UnselectTerminalOnCall

/////////////////////////////////////////////////////////////////////////////////////////////
// TStream::CreateStream
//
// Create a stream object
//
TStream^ TStream::CreateStream(IUnknown* p)
{
	TStream^ existingStm = TTapi::FindInterface<TStream^>(p);
	if (existingStm == nullptr)
	{
		existingStm = gcnew TStream(p);
		TTapi::AddInterface(existingStm);
	}
	return existingStm;

}// TStream::CreateStream

/////////////////////////////////////////////////////////////////////////////////////////////
// TapiFileTerminalEventArgs::TapiFileTerminalEventArgs
//
// Constructor for the TapiFileTerminalEventArgs
//
TapiFileTerminalEventArgs::TapiFileTerminalEventArgs(TAddress^ owner, IDispatch* piDispatch)
{
	CComQIPtr<Native::ITFileTerminalEvent> pevt(piDispatch);

	CComPtr<Native::ITCallInfo> piCall;
	if (SUCCEEDED(pevt->get_Call(&piCall)))
		_call = TCall::CreateCallAppearance(owner, piCall);
	else
		_call = nullptr;

	CComPtr<Native::ITTerminal> piTerm;
	if (SUCCEEDED(pevt->get_Terminal(&piTerm)))
		_terminal = TTerminal::CreateTerminal(piTerm);
	else
		_terminal = nullptr;

	HRESULT hr;
	if (SUCCEEDED(pevt->get_Error(&hr)) && FAILED(hr))
		_error = gcnew TapiException(hr);
	else
		_error = nullptr;

	Native::TERMINAL_MEDIA_STATE state;
	if (SUCCEEDED(pevt->get_State(&state)))
		_state = (TERMINAL_MEDIA_STATE) state;
	else
		_state = TERMINAL_MEDIA_STATE::TMS_IDLE;

	Native::FT_STATE_EVENT_CAUSE cause;
	if (SUCCEEDED(pevt->get_Cause(&cause)))
		_cause = (FT_STATE_EVENT_CAUSE) cause;
	else
		_cause = FT_STATE_EVENT_CAUSE::FTEC_NORMAL;

	CComPtr<Native::ITFileTrack> piFt;
	if (SUCCEEDED(pevt->get_Track(&piFt)))
		_track = gcnew TFileTrack(piFt);
	else
		_track = nullptr;

}// TapiFileTerminalEventArgs::TapiFileTerminalEventArgs

/////////////////////////////////////////////////////////////////////////////////////////////
// TFileTrack::TFileTrack
//
// Constructor for the TFileTrack
//
TFileTrack::TFileTrack(IUnknown* piDispatch) : Internal::TapiBase(piDispatch)
{
	CComPtr<Native::ITFileTrack> pevt = GetFileTrackItf();

	CComPtr<Native::ITTerminal> piTerm;
	if (SUCCEEDED(pevt->get_ControllingTerminal(&piTerm)))
		_terminal = TTerminal::CreateTerminal(piTerm);
	else
		_terminal = nullptr;

	Native::AM_MEDIA_TYPE* mt;
	if (SUCCEEDED(pevt->get_Format(&mt)))
		_fmt = gcnew AM_MEDIA_TYPE(mt);

}// TFileTrack::TFileTrack

/////////////////////////////////////////////////////////////////////////////////////////////
// TMediaFormat::CreateMediaFormat
//
// Function to create the known media formats.
//
TMediaFormat^ TMediaFormat::CreateMediaFormat(Guid guid, int cbSize, void* p)
{
	RegisterMediaTypeDelegate^ del;

	Monitor::Enter(_mediaTypes);
	try
	{
		if (_mediaTypes->ContainsKey(guid))
			del = _mediaTypes[guid];
	}
	finally
	{
		Monitor::Exit(_mediaTypes);
	}

	if (del != nullptr)
	{
		return del(guid, cbSize, IntPtr(p));
	}

	if (guid == TMediaFormat::FORMAT_WaveFormatEx)
	{
		TMediaFormat^ fmt = gcnew TAudioFormat();
		fmt->LoadStructure(cbSize, p);
		return fmt;
	}

	return nullptr;

}// TMediaFormat::CreateMediaFormat

/////////////////////////////////////////////////////////////////////////////////////////////
// TFileTrack::SetNewMediaFormat
//
// Change the audio format.
//
void TFileTrack::SetNewMediaFormat()
{
	if (_fmt != nullptr)
	{
		CComPtr<Native::ITFileTrack> pevt = GetFileTrackItf();

		Native::AM_MEDIA_TYPE MediaType;
		_fmt->Fill(MediaType);

		HRESULT hr = pevt->put_Format(&MediaType);
		if (MediaType.pbFormat != NULL)
			_fmt->MediaFormat->FreeStructure(MediaType.pbFormat);

		TapiException::ThrowExceptionForHR(hr);
	}

}// TFileTrack::SetNewAudioFormat

/////////////////////////////////////////////////////////////////////////////////////////////
// AM_MEDIA_TYPE::AM_MEDIA_TYPE
//
// Fill the native AM_MEDIA_TYPE structure
//
AM_MEDIA_TYPE::AM_MEDIA_TYPE(Native::AM_MEDIA_TYPE* mt)
{
	_majorType = Internal::ConversionFunctions::FromGUID(mt->majortype);
	_subType = Internal::ConversionFunctions::FromGUID(mt->subtype);
	_fixedSamples = mt->bFixedSizeSamples == TRUE ? true : false;
	_compression = mt->bTemporalCompression == TRUE ? true : false;
	_sampleSize = mt->lSampleSize;
	_formatType = Internal::ConversionFunctions::FromGUID(mt->formattype);

	TMediaFormat^ mfmt = TMediaFormat::CreateMediaFormat(Internal::ConversionFunctions::FromGUID(mt->formattype), mt->cbFormat, mt->pbFormat);
	if (mfmt == nullptr)
		throw gcnew NotSupportedException("The media format is not supported by JulMar.Tapi3");

	if (mt->cbFormat != 0)
	{
		CoTaskMemFree((PVOID)mt->pbFormat);
		mt->cbFormat = 0;
		mt->pbFormat = NULL;
	}
	if (mt->pUnk != NULL)
	{
		// Unnecessary because pUnk should not be used, but safest.
		mt->pUnk->Release();
		mt->pUnk = NULL;
	}
	CoTaskMemFree(mt);

}// AM_MEDIA_TYPE::AM_MEDIA_TYPE

/////////////////////////////////////////////////////////////////////////////////////////////
// AM_MEDIA_TYPE::Fill
//
// Fill the native AM_MEDIA_TYPE structure
//
void AM_MEDIA_TYPE::Fill(Native::AM_MEDIA_TYPE& MediaType)
{
	MediaType.majortype            = Internal::ConversionFunctions::ToGUID(MajorType);
	MediaType.subtype              = Internal::ConversionFunctions::ToGUID(SubType);
	MediaType.bFixedSizeSamples    = (FixedSizedSamples) ? TRUE : FALSE;
	MediaType.bTemporalCompression = (TemporalCompression) ? TRUE : FALSE;
	MediaType.lSampleSize          = SampleSize;
	MediaType.formattype           = Internal::ConversionFunctions::ToGUID(FormatType);
	MediaType.pUnk                 = NULL;

	if (_media != nullptr)
	{
		MediaType.cbFormat = _media->GetStructureSize();
		MediaType.pbFormat = (BYTE*) _media->GetStructure();
	}
	else
	{
		MediaType.cbFormat = 0;
		MediaType.pbFormat = NULL;
	}
}// AM_MEDIA_TYPE::Fill

/////////////////////////////////////////////////////////////////////////////////////////////
// TTerminal::GetMediaFormat
//
// Retrieves the AM_MEDIA_TYPE structure
//
AM_MEDIA_TYPE^ TTerminal::GetMediaFormat()
{
	Native::AM_MEDIA_TYPE* mt;
	TapiException::ThrowExceptionForHR(GetAMMediaFormatItf()->get_MediaFormat(&mt));
	return gcnew AM_MEDIA_TYPE(mt);

}//TTerminal::GetMediaFormat

/////////////////////////////////////////////////////////////////////////////////////////////
// TTerminal::SetMediaFormat
//
// Changes the media format
//
void TTerminal::SetMediaFormat(AM_MEDIA_TYPE^ value)
{
	if (value == nullptr)
		throw gcnew ArgumentNullException("MediaFormat");

	Native::AM_MEDIA_TYPE MediaType;
	value->Fill(MediaType);

	try 
	{
		TapiException::ThrowExceptionForHR(GetAMMediaFormatItf()->put_MediaFormat(&MediaType));
	}
	finally
	{
		if (MediaType.pbFormat != NULL)
			value->MediaFormat->FreeStructure(MediaType.pbFormat);
	}

}// TTerminal::SetMediaFormat

/////////////////////////////////////////////////////////////////////////////////////////////
// TCall::Release
//
// When the call is being released, remove it from our interfaces map
//
void TCall::Release(bool inFinalizer)
{
	__super::Release(inFinalizer);
	if (!inFinalizer)
		TTapi::RemoveInterface(this);

}// TCall::Release

/////////////////////////////////////////////////////////////////////////////////////////////
// TCall::DeviceSpecific
//
// Provide device-specific extensions for a given call
//
void TCall::DeviceSpecific(array<byte>^ data)
{
	CComPtr<Native::ITCallInfo> ci = GetCallInfoItf();
	_owner->DeviceSpecific(ci, data);

}// TCall::DeviceSpecific

/////////////////////////////////////////////////////////////////////////////////////////////
// TPhone::Release
//
// Release the phone interface
//
void TPhone::Release(bool inFinalizer)
{
	if (!inFinalizer)
	{
		Close();
		TTapi::RemoveInterface(this);
	}
	__super::Release(inFinalizer);

}// TPhone::Release

/////////////////////////////////////////////////////////////////////////////////////////////
// TAddress::EumeratePhones
//
// Enumerate the available phones from this address
//
array<TPhone^>^ TAddress::EnumeratePhones()
{
	List<TPhone^>^ retArr = gcnew List<TPhone^>();

	try 
	{
		CComPtr<Native::IEnumPhone> pePhone;
		if (SUCCEEDED(GetAddress2Itf()->EnumeratePhones(&pePhone)))
		{
			CComPtr<Native::ITPhone> pphone;
			while (pePhone->Next(1, &pphone, NULL) == S_OK)
			{
				retArr->Add(TPhone::CreatePhone(_owner, pphone));
				pphone = NULL;
			}
		}
	}
	catch (Exception^)
	{

	}
	return retArr->ToArray();

}// TAddress::EumeratePhones

/////////////////////////////////////////////////////////////////////////////////////////////
// TAddress::EnumeratePreferredPhones
//
// Enumerate the preferred phones for this address
//
array<TPhone^>^ TAddress::EnumeratePreferredPhones()
{
	List<TPhone^>^ retArr = gcnew List<TPhone^>();

	try 
	{
		CComPtr<Native::IEnumPhone> pePhone;
		if (SUCCEEDED(GetAddress2Itf()->EnumeratePreferredPhones(&pePhone)))
		{
			CComPtr<Native::ITPhone> pphone;
			while (pePhone->Next(1, &pphone, NULL) == S_OK)
			{
				retArr->Add(TPhone::CreatePhone(_owner, pphone));
				pphone = NULL;
			}
		}
	}
	catch (Exception^)
	{
	}

	return retArr->ToArray();

}// TAddress::EnumeratePreferredPhones

/////////////////////////////////////////////////////////////////////////////////////////////
// TAddress::GetPhoneFromTerminal
//
// Get a phone device for a given terminal (handset, speaker, etc.)
//
TPhone^ TAddress::GetPhoneFromTerminal(TTerminal^ terminal)
{
	CComPtr<Native::ITPhone> pphone;
	TapiException::ThrowExceptionForHR(GetAddress2Itf()->GetPhoneFromTerminal(terminal->GetTerminalItf(), &pphone));
	return TPhone::CreatePhone(_owner, pphone);

}// TAddress::GetPhoneFromTerminal

/////////////////////////////////////////////////////////////////////////////////////////////
// TCall::SelectDefaultTerminals
//
// Selects the default (most common) terminal set for a call.
//
void TCall::SelectDefaultTerminals()
{
	// Walk through the streams on the call
	for each (TStream^ stm in this->Streams)
	{
		TTerminal^ term;
		if (stm->MediaType == TAPIMEDIATYPES::VIDEO &&
			stm->Direction == TERMINAL_DIRECTION::TD_RENDER)
		{
			term = _owner->CreateTerminal(TTerminal::VideoWindowTerminal, TAPIMEDIATYPES::VIDEO, TERMINAL_DIRECTION::TD_RENDER);
		}
		else
		{
			term = _owner->GetDefaultStaticTerminal(stm->MediaType, stm->Direction);
		}

		if (term != nullptr)
			stm->SelectTerminal(term);
	}

}// TCall::SelectDefaultTerminals

/////////////////////////////////////////////////////////////////////////////////////////////
// TCall::FindTerminal
//
// Locate a terminal on the call
//
TTerminal^ TCall::FindTerminal(TAPIMEDIATYPES mediaType, TERMINAL_DIRECTION direction)
{
	for each (TStream^ stm in this->Streams)
	{
		if (stm->MediaType == mediaType &&
			stm->Direction == direction)
			return stm->FindTerminal(mediaType, direction);
	}

	return nullptr;

}// TCall::FindTerminal
