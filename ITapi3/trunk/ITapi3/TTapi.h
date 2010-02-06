// TTapi.h
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
using namespace System::Runtime::InteropServices::ComTypes;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;
using namespace System::Security::Permissions;
using namespace System::Drawing;
using namespace System::Diagnostics;

#define DEFINE_EVENT(_E,_NAME,_DESC) \
private: static initonly Object^ _event##_NAME = gcnew Object();\
public:\
	[Description(_DESC)]\
	event EventHandler<_E^>^ _NAME {\
	void add(EventHandler<_E^>^ handler)	{ __super::Events->AddHandler(_event##_NAME, handler);  _activeEvents |= Native::_NAME; AdjustRequestedEvents(); }\
	void remove(EventHandler<_E^>^ handler) { __super::Events->RemoveHandler(_event##_NAME, handler); }\
	void raise(Object^ sender, _E^ e) { EventHandler<_E^>^ handler = (EventHandler<_E^>^)__super::Events[_event##_NAME];\
		if (handler != nullptr) handler->Invoke(sender, e);	}\
}

namespace JulMar
{
	namespace Tapi3 
	{
		ref class TAddress;
		ref class TapiObjectEventArgs;

		ref struct TapiRequest 
		{
			Native::TAPI_EVENT te;
			EventArgs^ ea;

			TapiRequest(Native::TAPI_EVENT te_, EventArgs^ ea_) : te(te_), ea(ea_) {/* */}
		};

		[Description("Telephony Component"), DefaultEvent("TE_CALLNOTIFICATION"), 
			HostProtection(SecurityAction::LinkDemand, SharedState=true),
			ToolboxBitmap(TTapi::typeid)]
		public ref class TTapi sealed : System::ComponentModel::Component
		{
		// Class data
		private:
			Native::ITTAPI* _p;
			List<TAddress^>^ _addr;
			long _adviseCode;
			static List<WeakReference^>^ _interfaces;
			bool _shutdown;
			bool _autoDestroyCalls;
			AsyncOperation^ _asyncOp;
			long _activeEvents;

		// Events
		DEFINE_EVENT(TapiObjectEventArgs, TE_TAPIOBJECT,"Reports changes in TAPI");
		DEFINE_EVENT(TapiRequestEventArgs, TE_REQUEST,"Request object notifications");
		DEFINE_EVENT(TapiAddressChangedEventArgs,TE_ADDRESS,"Reports Address object changes");
		DEFINE_EVENT(TapiCallNotificationEventArgs, TE_CALLNOTIFICATION,"Reports new call notifications");
		DEFINE_EVENT(TapiCallStateEventArgs, TE_CALLSTATE,"Call state change notifications");
		DEFINE_EVENT(TapiCallMediaEventArgs, TE_CALLMEDIA,"Call media notifications");
		DEFINE_EVENT(TapiCallHubEventArgs, TE_CALLHUB,"Call Hub notifications");
		DEFINE_EVENT(TapiCallInfoChangeEventArgs, TE_CALLINFOCHANGE,"Reports call information change notifications");
		DEFINE_EVENT(TapiDigitDetectionEventArgs, TE_DIGITEVENT,"Raised when digits are detected");
		DEFINE_EVENT(TapiDigitGenerationEventArgs, TE_GENERATEEVENT,"Raised when digits are generated");
		DEFINE_EVENT(TapiToneDetectionEventArgs, TE_TONEEVENT,"Raised when tones are detected");
		DEFINE_EVENT(TapiDigitsGatheredEventArgs, TE_GATHERDIGITS,"Raised when digits are gathered");
		DEFINE_EVENT(TapiQOSEventArgs, TE_QOSEVENT,"QOS events");
		DEFINE_EVENT(TapiTTSTerminalEventArgs, TE_TTSTERMINAL,"Events occurring on TTS terminals");
		DEFINE_EVENT(TapiASRTerminalEventArgs, TE_ASRTERMINAL,"Events occurring on ASR terminals");
		DEFINE_EVENT(TapiToneTerminalEventArgs,TE_TONETERMINAL,"Events occurring on tone terminals");
		DEFINE_EVENT(TapiFileTerminalEventArgs, TE_FILETERMINAL,"Events occurring on file-based terminals");
		DEFINE_EVENT(TapiAddressDeviceSpecificEventArgs, TE_ADDRESSDEVSPECIFIC,"Device specific events");
		DEFINE_EVENT(TapiDeviceSpecificEventArgs, TE_PRIVATE,"Device specific events");
		DEFINE_EVENT(TapiPhoneEventArgs, TE_PHONEEVENT,"Events occurring on phone devices");
		DEFINE_EVENT(TapiPhoneDeviceSpecificEventArgs, TE_PHONEDEVSPECIFIC ,"Device specific events");

		// Destructor/Finalizer
		private:
			static TTapi()
			{
				_interfaces = gcnew List<WeakReference^>();
			}

		protected public:
			CComPtr<Native::ITTAPI2> GetTapi2Itf() 
			{ 
				CComPtr<Native::ITTAPI2> p;
				_p->QueryInterface(Native::IID_ITTAPI2, (void**)&p);
				return p;
			}

		// Constructor/Methods
		public:
			TTapi() : _p(0)
			{
				_addr = gcnew List<TAddress^>();
				_autoDestroyCalls = true;
				_activeEvents = Native::TE_TAPIOBJECT | Native::TE_ADDRESS;
			}

			~TTapi()
			{
				Shutdown();
			}

			int Initialize()
			{
				if (_p != NULL)
					throw gcnew TapiException("TAPI has already been initialized");

				_shutdown = false;

				TapiException::TraceOut(System::Diagnostics::TraceEventType::Verbose, 
					"Creating ITTAPI instance");

				void* p;
				HRESULT hr = CoCreateInstance(Native::CLSID_TAPI, NULL, CLSCTX_INPROC_SERVER, Native::IID_ITTAPI, &p);
				if (SUCCEEDED(hr))
				{
					_p = static_cast<Native::ITTAPI*>(p);
					_asyncOp = AsyncOperationManager::CreateOperation(nullptr);

					hr = _p->Initialize();
					if (FAILED(hr)) 
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, 
							"ITTapi::Initialize hr=0x{0:X}", hr);

						_p->Release();
						_p = NULL;
					}
					else
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Verbose, 
							"Hooking up connection sink to ITTAPI interface");

						// Get the connection point container interface pointer from the TAPI object.
						CComPtr<::IConnectionPointContainer> pCPC;
						TapiException::ThrowExceptionForHR(_p->QueryInterface(IID_IConnectionPointContainer,(void**)&pCPC));

						// Get the ITTAPIEventNotification interface pointer from the container.
						CComPtr<::IConnectionPoint> pCP;
						TapiException::ThrowExceptionForHR(pCPC->FindConnectionPoint(Native::IID_ITTAPIEventNotification, &pCP));
						pCPC.Release();

						// Create a private event notification object.
						Native::TapiEventHandler* pTE = new Native::TapiEventHandler(gcnew Native::TapiEventHandlerDelegate(this, &TTapi::TapiEventHandlerFunc));

						// Call the advise method to give TAPI the IUnknown pointer for the event handler.
						long lAdvise;
						TapiException::ThrowExceptionForHR(pCP->Advise((IUnknown*)pTE, (ULONG*)&lAdvise));
						pCP.Release();
						_adviseCode = lAdvise;

						// Register for all events
						TapiException::ThrowExceptionForHR(AdjustRequestedEvents());

						// Grab all the available addresses and wrap them.
						CComPtr<Native::IEnumAddress> peAddr;
						if (SUCCEEDED(_p->EnumerateAddresses(&peAddr)))
						{
							int countFull = 0; CComPtr<Native::ITAddress> paddr;
							while (peAddr->Next(1, &paddr, NULL) == S_OK)
							{
								_addr->Add(TAddress::CreateAddress(this, paddr));
								paddr = NULL;
								countFull++;
							}
							return static_cast<int>(countFull);
						}
					}
				}

				TapiException::ThrowExceptionForHR(hr);
				return 0;
			}

			property array<TAddress^>^ Addresses
			{
				array<TAddress^>^ get()
				{
					try
					{
						Monitor::Enter(_addr);
						return _addr->ToArray();
					}
					finally
					{
						Monitor::Exit(_addr);	
					}
				}
			}

			[Description("Determines whether TCall objects are disposed when they disconnect."),
				Category("Behavior"), DefaultValue(true)]
			property bool AutoDestroyCalls
			{
				bool get() { return _autoDestroyCalls; }
				void set(bool value) { _autoDestroyCalls = value; }
			}

			property array<TCallHub^>^ CallHubs
			{
				array<TCallHub^>^ get()
				{
					List<TCallHub^>^ retData = gcnew List<TCallHub^>();
					try 
					{
						CComPtr<Native::IEnumCallHub> peHub;
						if (SUCCEEDED(_p->EnumerateCallHubs(&peHub)))
						{
							CComPtr<Native::ITCallHub> pHub;
							while (peHub->Next(1, &pHub, NULL) == S_OK)
								retData->Add(TCallHub::CreateCallHub(this, pHub));
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retData->ToArray();
				}
			}

			void RegisterRequestRecipient(long registrationInstance, long lRequestMode, bool onoff)
			{
				TapiException::ThrowExceptionForHR(_p->RegisterRequestRecipient(registrationInstance, lRequestMode, (onoff) ? VARIANT_TRUE : VARIANT_FALSE));
			}

			void SetAssistedTelephonyPriority(String^ appName, bool priority)
			{
				CComBSTR bstrName = (BSTR) Marshal::StringToBSTR(appName).ToPointer();
				TapiException::ThrowExceptionForHR(_p->SetAssistedTelephonyPriority(bstrName, (priority) ? VARIANT_TRUE : VARIANT_FALSE));
			}

			void SetApplicationPriority(String^ fileName, TAPIMEDIATYPES mediaTypes, bool priority)
			{
				CComBSTR bstrName = (BSTR) Marshal::StringToBSTR(fileName).ToPointer();
				TapiException::ThrowExceptionForHR(_p->SetApplicationPriority(bstrName, (long)mediaTypes, (priority) ? VARIANT_TRUE : VARIANT_FALSE));
			}

			void Shutdown()
			{
				_shutdown = true;
				_addr->Clear();
				_asyncOp = nullptr;

				if (_p != NULL)
				{
					TTapi::ReleaseAllInterfaces();

					if (_adviseCode != 0)
					{
						CComQIPtr<::IConnectionPointContainer> pCPC(_p);
						if (pCPC != NULL)
						{
							CComPtr<::IConnectionPoint> pCP;
							if (SUCCEEDED(pCPC->FindConnectionPoint(Native::IID_ITTAPIEventNotification, &pCP)))
								pCP->Unadvise(_adviseCode);
						}
					}

					HRESULT hr = _p->Shutdown();
					TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, 
						"ITTapi::Shutdown hr=0x{0:X}", hr);
					
					_p->Release();
					_p = NULL;
				}
			}

			property array<TPhone^>^ Phones
			{
				array<TPhone^>^ get()
				{
					List<TPhone^>^ retArr = gcnew List<TPhone^>();
					try 
					{
						CComPtr<Native::ITTAPI2> pi = GetTapi2Itf();
						if (pi)
						{
							CComPtr<Native::IEnumPhone> pePhone;
							if (SUCCEEDED(pi->EnumeratePhones(&pePhone)))
							{
								CComPtr<Native::ITPhone> pphone;
								while (pePhone->Next(1, &pphone, NULL) == S_OK)
								{
									retArr->Add(TPhone::CreatePhone(this, pphone));
									pphone = NULL;
								}
							}
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retArr->ToArray();
				}
			}

		private:
			EventArgs^ CollectEventArgsFromIDispatch(Native::TAPI_EVENT te, IDispatch* pEvent)
			{
				switch (te)
				{
				case Native::TE_TAPIOBJECT:
					return gcnew TapiObjectEventArgs(this, pEvent);

				case Native::TE_ADDRESS:
					{
						CComQIPtr<Native::ITAddressEvent> ae = pEvent;
						CComPtr<Native::ITAddress> piaddr;
						if (SUCCEEDED(ae->get_Address(&piaddr)))
						{
							TAddress^ addr = TTapi::FindInterface<TAddress^>(piaddr);
							return gcnew TapiAddressChangedEventArgs(addr, pEvent);
						}
					}
					break;

				case Native::TE_CALLNOTIFICATION:
					return gcnew TapiCallNotificationEventArgs(GetAddressByCall<Native::ITCallNotificationEvent>(pEvent), pEvent);

				case Native::TE_CALLSTATE:
					return gcnew TapiCallStateEventArgs(GetAddressByCall<Native::ITCallStateEvent>(pEvent), pEvent);

				case Native::TE_CALLMEDIA:
					return gcnew TapiCallMediaEventArgs(GetAddressByCall<Native::ITCallMediaEvent>(pEvent), pEvent);
					break;

				case Native::TE_CALLHUB:
					return gcnew TapiCallHubEventArgs(this, GetAddressByCall<Native::ITCallHubEvent>(pEvent), pEvent);

				case Native::TE_CALLINFOCHANGE:
					return gcnew TapiCallInfoChangeEventArgs(GetAddressByCall<Native::ITCallInfoChangeEvent>(pEvent), pEvent);

				case Native::TE_REQUEST:
					return gcnew TapiRequestEventArgs(pEvent);

				case Native::TE_QOSEVENT:
					return gcnew TapiQOSEventArgs(GetAddressByCall<Native::ITQOSEvent>(pEvent), pEvent);

				case Native::TE_DIGITEVENT:
					return gcnew TapiDigitDetectionEventArgs(GetAddressByCall<Native::ITDigitDetectionEvent >(pEvent), pEvent);

				case Native::TE_GENERATEEVENT:
					return gcnew TapiDigitGenerationEventArgs(GetAddressByCall<Native::ITDigitGenerationEvent>(pEvent), pEvent);

				case Native::TE_TONEEVENT:
					return gcnew TapiToneDetectionEventArgs(GetAddressByCall<Native::ITToneDetectionEvent>(pEvent), pEvent);

				case Native::TE_GATHERDIGITS:
					return gcnew TapiDigitsGatheredEventArgs(GetAddressByCall<Native::ITDigitsGatheredEvent>(pEvent), pEvent);

				case Native::TE_TTSTERMINAL:
					return gcnew TapiTTSTerminalEventArgs(GetAddressByCall<Native::ITTTSTerminalEvent>(pEvent),pEvent);

				case Native::TE_ASRTERMINAL:
					return gcnew TapiASRTerminalEventArgs(GetAddressByCall<Native::ITASRTerminalEvent>(pEvent),pEvent);

				case Native::TE_TONETERMINAL:
					return gcnew TapiToneTerminalEventArgs(GetAddressByCall<Native::ITToneTerminalEvent>(pEvent),pEvent);

				case Native::TE_FILETERMINAL:
					return gcnew TapiFileTerminalEventArgs(GetAddressByCall<Native::ITFileTerminalEvent>(pEvent),pEvent);

				case Native::TE_ADDRESSDEVSPECIFIC:
					return gcnew TapiAddressDeviceSpecificEventArgs(this, pEvent);

				case Native::TE_PRIVATE:
					return gcnew TapiDeviceSpecificEventArgs(pEvent);
					break;

				case Native::TE_AGENT:
				case Native::TE_AGENTSESSION:
				case Native::TE_AGENTHANDLER:
				case Native::TE_ACDGROUP:
				case Native::TE_QUEUE:
					//TODO:
					break;

				case Native::TE_PHONEEVENT:
				case Native::TE_PHONEDEVSPECIFIC:
					//TODO:
					break;

				default:
					break;
				}
				return nullptr;
			}
				
			void TapiEventHandlerFunc(Native::TAPI_EVENT te, IDispatch* pEvent)
			{
				TapiException::TraceOut(System::Diagnostics::TraceEventType::Verbose,
					"TAPIEVENT: 0x{0:X} IDispatch=0x{1:X}", (long)te, (long)pEvent);

				if (!_shutdown)
				{
					if (_asyncOp != nullptr)
					{
						try 
						{
							_asyncOp->Post(gcnew SendOrPostCallback(this, &TTapi::ThreadedProcessTapiMessage), 
								gcnew TapiRequest(te, CollectEventArgsFromIDispatch(te, pEvent)));
						}
						catch (...)
						{
						}
					}
				}
			}

			void ThreadedProcessTapiMessage(Object^ o)
			{
				TapiRequest^ req = (TapiRequest^) o;
				try 
				{
					ProcessTapiMessage(req->te, req->ea);
				}
				catch(Exception^ ex)
				{
					TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
				}
			}

			void ProcessTapiMessage(Native::TAPI_EVENT te, EventArgs^ ea)
			{
				TapiException::TraceOut(System::Diagnostics::TraceEventType::Verbose,
					"Processing {0}", ea->ToString());

				switch (te)
				{
				case Native::TE_TAPIOBJECT:
					this->TE_TAPIOBJECT(this, (TapiObjectEventArgs^)ea);
					break;

				case Native::TE_ADDRESS:
					this->TE_ADDRESS(this, (TapiAddressChangedEventArgs^)ea);
					break;

				case Native::TE_CALLNOTIFICATION:
					this->TE_CALLNOTIFICATION(this, (TapiCallNotificationEventArgs^)ea);
					break;

				case Native::TE_CALLSTATE:
					{
						TapiCallStateEventArgs^ cea = (TapiCallStateEventArgs^) ea;
						try 
						{
							this->TE_CALLSTATE(this, cea);
						}
						finally
						{
							if (_autoDestroyCalls && cea != nullptr && cea->State == CALL_STATE::CS_DISCONNECTED)
								cea->Call->~TCall();
						}
					}
					break;

				case Native::TE_CALLMEDIA:
					this->TE_CALLMEDIA(this, (TapiCallMediaEventArgs^)ea);
					break;

				case Native::TE_CALLHUB:
					this->TE_CALLHUB(this, (TapiCallHubEventArgs^)ea);
					break;

				case Native::TE_CALLINFOCHANGE:
					this->TE_CALLINFOCHANGE(this, (TapiCallInfoChangeEventArgs^)ea);
					break;

				case Native::TE_REQUEST:
					this->TE_REQUEST(this, (TapiRequestEventArgs^)ea);
					break;

				case Native::TE_QOSEVENT:
					this->TE_QOSEVENT(this, (TapiQOSEventArgs^)ea);
					break;

				case Native::TE_DIGITEVENT:
					this->TE_DIGITEVENT(this, (TapiDigitDetectionEventArgs^)ea);
					break;

				case Native::TE_GENERATEEVENT:
					this->TE_GENERATEEVENT(this, (TapiDigitGenerationEventArgs^)ea);
					break;

				case Native::TE_TONEEVENT:
					this->TE_TONEEVENT(this, (TapiToneDetectionEventArgs^)ea);
					break;

				case Native::TE_GATHERDIGITS:
					this->TE_GATHERDIGITS(this, (TapiDigitsGatheredEventArgs^)ea);
					break;

				case Native::TE_TTSTERMINAL:
					this->TE_TTSTERMINAL(this, (TapiTTSTerminalEventArgs^)ea);
					break;

				case Native::TE_ASRTERMINAL:
					this->TE_ASRTERMINAL(this, (TapiASRTerminalEventArgs^)ea);
					break;

				case Native::TE_TONETERMINAL:
					this->TE_TONETERMINAL(this, (TapiToneTerminalEventArgs^)ea);
					break;

				case Native::TE_FILETERMINAL:
					this->TE_FILETERMINAL(this, (TapiFileTerminalEventArgs^)ea);
					break;

				case Native::TE_ADDRESSDEVSPECIFIC:
					this->TE_ADDRESSDEVSPECIFIC(this, (TapiAddressDeviceSpecificEventArgs^)ea);
					break;

				case Native::TE_PRIVATE:
					this->TE_PRIVATE(this, (TapiDeviceSpecificEventArgs^)ea);
					break;

				case Native::TE_AGENT:
				case Native::TE_AGENTSESSION:
				case Native::TE_AGENTHANDLER:
				case Native::TE_ACDGROUP:
				case Native::TE_QUEUE:
					//TODO:
					break;

				case Native::TE_PHONEEVENT:
				case Native::TE_PHONEDEVSPECIFIC:
					//TODO:
					break;

				default:
					break;
				}
			}

		protected public:
			long RegisterCallNotifications(Native::ITAddress* pitf, VARIANT_BOOL vbMonitor, VARIANT_BOOL vbOwner, long supportedMediaTypes)
			{
				long lCode;
				TapiException::ThrowExceptionForHR(
					_p->RegisterCallNotifications(pitf, vbMonitor, vbOwner, supportedMediaTypes, 
												 _adviseCode, &lCode));
				return lCode;
			}

			void UnregisterNotifications(long id)
			{
				_p->UnregisterNotifications(id);
			}

			void SetCallHubTracking(Native::ITAddress* paddr, VARIANT_BOOL vb)
			{
				//  Create a SAFEARRAY for the address
				CComSafeArray<IDispatch*> sa;
				CComPtr<IDispatch> pi = paddr;
				sa.Add(pi);

				CComVariant var(sa);
				TapiException::ThrowExceptionForHR(_p->SetCallHubTracking(var, vb));
			}

			static void AddInterface(Internal::TapiBase^ o)
			{
				Monitor::Enter(_interfaces);
				try
				{
					_interfaces->Add(gcnew WeakReference(o));
				}
				finally
				{
					Monitor::Exit(_interfaces);
				}
			}

			static void RemoveInterface(Internal::TapiBase^ o)
			{
				Monitor::Enter(_interfaces);
				try
				{
					for (int i = 0; i < _interfaces->Count; i++)
					{
						WeakReference^ wr = _interfaces[i];
						if (wr->IsAlive &&
							wr->Target == o)
						{
							_interfaces->RemoveAt(i);
							break;
						}
					}
				}
				finally
				{
					Monitor::Exit(_interfaces);
				}
			}

			generic<typename T> where T : ref class, Internal::TapiBase
			static T FindInterface(IUnknown* p)
			{
				array<WeakReference^>^ arrEntries;
				Monitor::Enter(_interfaces);
				try
				{
					arrEntries = _interfaces->ToArray();
				}
				finally
				{
					Monitor::Exit(_interfaces);
				}

				for each (WeakReference^ wr in arrEntries)
				{
					if (wr->IsAlive)
					{
						Internal::TapiBase^ tb = (Internal::TapiBase^) wr->Target;
						if (tb->Compare(p))
							return (T)tb;
					}
					else
					{
						try
						{
							Monitor::Enter(_interfaces);
							_interfaces->Remove(wr);
						}
						finally
						{
							Monitor::Exit(_interfaces);
						}
					}
				}
				return T();

			}

			static void ReleaseAllInterfaces()
			{
				array<WeakReference^>^ arr = nullptr;

				Monitor::Enter(_interfaces);
				try
				{
					arr = _interfaces->ToArray();
					_interfaces->Clear();
				}
				finally
				{
					Monitor::Exit(_interfaces);
				}

				for each (WeakReference^ wr in arr)
				{
					if (wr->IsAlive)
					{
						Internal::TapiBase^ tb = (Internal::TapiBase^) wr->Target;
						tb->Release(false);
					}
				}
			}
		private:
			HRESULT AdjustRequestedEvents()
			{
				if (!_shutdown && _p != NULL)
				{
					HRESULT hr = _p->put_EventFilter(_activeEvents);
					TapiException::TraceOut(System::Diagnostics::TraceEventType::Information, 
						"ITTapi::put_EventFilter(0x{0:X}) hr=0x{1:X}", _activeEvents, hr);
					return hr;
				}
				
				return E_FAIL;
			}

			template<class T>
			TAddress^ GetAddressByCall(IDispatch* pEvent)
			{
				CComQIPtr<T> piCE = pEvent;
				CComPtr<Native::ITCallInfo> piCall;
				if (SUCCEEDED(piCE->get_Call(&piCall)) && piCall != NULL)
				{
					CComPtr<Native::ITAddress> piAddr;
					if (SUCCEEDED(piCall->get_Address(&piAddr)) && piAddr != NULL)
						return FindInterface<TAddress^>(piAddr);
				}
				return nullptr;
			}
		};
	}
}
