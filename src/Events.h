// Events.h
//
// This file contains all the EventArgs and enumerations for processing the events
// raised by the ITapi3 library. 
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

namespace JulMar
{
	namespace Tapi3 
	{
		ref class TTapi;
		ref class TAddress;
		ref class TTerminal;
		ref class TStream;
		ref class TCall;
		ref class TCallHub;
		ref class TFileTrack;
		ref class TPhone;

		/// <summary>
		/// The TAPIOBJECT_EVENT enum describes TAPI object events.
		/// </summary>
		public enum struct TAPIOBJECT_EVENT
		{
			TE_ADDRESSCREATE	= 0,
			TE_ADDRESSREMOVE	= ( TE_ADDRESSCREATE + 1 ) ,
			TE_REINIT	= ( TE_ADDRESSREMOVE + 1 ) ,
			TE_TRANSLATECHANGE	= ( TE_REINIT + 1 ) ,
			TE_ADDRESSCLOSE	= ( TE_TRANSLATECHANGE + 1 ) ,
			TE_PHONECREATE	= ( TE_ADDRESSCLOSE + 1 ) ,
			TE_PHONEREMOVE	= ( TE_PHONECREATE + 1 ) 
		};

		/// <summary>
		/// The TapiObjectEventArgs class is sent with each TE_TAPIOBJECT event.
		/// </summary>
		public ref class TapiObjectEventArgs : EventArgs
		{
		private:
			TAddress^ _addr;
			TPhone^ _phone;
			TAPIOBJECT_EVENT _evt;
		protected public:
			TapiObjectEventArgs(TTapi^ owner, IDispatch* pevt);
		public:
			/// <summary>
			/// The Address object
			/// </summary>
			property TAddress^ Address 
			{
				TAddress^ get() { return _addr; }
			}

			property TPhone^ Phone
			{
				TPhone^ get() { return _phone; }
			}

			/// <summary>
			/// The event being reported
			/// </summary>
			property TAPIOBJECT_EVENT Event
			{
				TAPIOBJECT_EVENT get() { return _evt; }
			}

			virtual String^ ToString() override
			{
				return String::Format("TapiObjectEventArgs: Evt={0}, Addr={1}, Phone={2}", _evt, _addr, _phone);
			}
		};

		/// <summary>
		/// The different ADDRESS level events which are reported with a TapiAddressChangedEventArgs structure
		/// </summary>
		public enum struct ADDRESS_EVENT
		{
			AE_STATE	= 0,
			AE_CAPSCHANGE	= ( AE_STATE + 1 ) ,
			AE_RINGING	= ( AE_CAPSCHANGE + 1 ) ,
			AE_CONFIGCHANGE	= ( AE_RINGING + 1 ) ,
			AE_FORWARD	= ( AE_CONFIGCHANGE + 1 ) ,
			AE_NEWTERMINAL	= ( AE_FORWARD + 1 ) ,
			AE_REMOVETERMINAL	= ( AE_NEWTERMINAL + 1 ) ,
			AE_MSGWAITON	= ( AE_REMOVETERMINAL + 1 ) ,
			AE_MSGWAITOFF	= ( AE_MSGWAITON + 1 ) ,
		};

		/// <summary>
		/// The event structure reported with a TE_ADDRESS event
		/// </summary>
		public ref class TapiAddressChangedEventArgs : EventArgs
		{
		private:
			TAddress^ _address;
			ADDRESS_EVENT _evt;
			TTerminal^ _terminal;
		protected public:
			TapiAddressChangedEventArgs(TAddress^ owner, IDispatch* piDispatch);
		public:
			/// <summary>
			/// The Address object
			/// </summary>
			property TAddress^ Address 
			{
				TAddress^ get() { return _address; }
			}

			/// <summary>
			/// The Terminal object (may be null)
			/// </summary>
			property TTerminal^ Terminal
			{
				TTerminal^ get() { return _terminal; }
			}

			/// <summary>
			/// The event being reported
			/// </summary>
			property ADDRESS_EVENT Event 
			{
				ADDRESS_EVENT get()	{ return _evt; }
			}

			virtual String^ ToString() override
			{
				return String::Format("TapiAddressChangedEventArgs: Evt={0}, Address={1}, Terminal={2}", _evt, _address, _terminal);
			}
		};

		/// <summary>
		/// The different events reported with a TapiCallNotificationEventArgs
		/// </summary>
		public enum struct CALL_NOTIFICATION_EVENT
		{
			CNE_OWNER	= 0,
			CNE_MONITOR	= ( CNE_OWNER + 1 ) ,
		};

		/// <summary>
		/// This event structure is passed with a TE_CALLNOTIFICATION event
		/// </summary>
		public ref class TapiCallNotificationEventArgs : EventArgs
		{
		private:
			CALL_NOTIFICATION_EVENT _evt;
			TCall^ _call;
		protected public:
			TapiCallNotificationEventArgs(TAddress^ owner, IDispatch* piDispatch);
		public:
			/// <summary>
			/// The new call being reported
			/// </summary>
			property TCall^ Call 
			{
				TCall^ get() { return _call; }
			}

			/// <summary>
			/// The ownership of the call
			/// </summary>
			property CALL_NOTIFICATION_EVENT Event
			{
				CALL_NOTIFICATION_EVENT get() { return _evt; }
			}

			virtual String^ ToString() override
			{
				return String::Format("TapiCallNotificationEventArgs: Event={0}, Call={1}", _evt, _call);
			}
		};

		/// <summary>
		/// The different call state event causes
		/// </summary>
		public enum struct CALL_STATE_EVENT_CAUSE
		{
			CEC_NONE	= 0,
			CEC_DISCONNECT_NORMAL	= ( CEC_NONE + 1 ) ,
			CEC_DISCONNECT_BUSY	= ( CEC_DISCONNECT_NORMAL + 1 ) ,
			CEC_DISCONNECT_BADADDRESS	= ( CEC_DISCONNECT_BUSY + 1 ) ,
			CEC_DISCONNECT_NOANSWER	= ( CEC_DISCONNECT_BADADDRESS + 1 ) ,
			CEC_DISCONNECT_CANCELLED	= ( CEC_DISCONNECT_NOANSWER + 1 ) ,
			CEC_DISCONNECT_REJECTED	= ( CEC_DISCONNECT_CANCELLED + 1 ) ,
			CEC_DISCONNECT_FAILED	= ( CEC_DISCONNECT_REJECTED + 1 ) ,
			CEC_DISCONNECT_BLOCKED	= ( CEC_DISCONNECT_FAILED + 1 ) 
		};

		/// <summary>
		/// The different call states that a call may be in
		/// </summary>
		public enum struct CALL_STATE
		{
			CS_UNKNOWN = -1,
			CS_IDLE	= 0,
			CS_INPROGRESS	= ( CS_IDLE + 1 ) ,
			CS_CONNECTED	= ( CS_INPROGRESS + 1 ) ,
			CS_DISCONNECTED	= ( CS_CONNECTED + 1 ) ,
			CS_OFFERING	= ( CS_DISCONNECTED + 1 ) ,
			CS_HOLD	= ( CS_OFFERING + 1 ) ,
			CS_QUEUED	= ( CS_HOLD + 1 )
		};

		/// <summary>
		/// The event structure reported with a TE_CALLSTATE event
		/// </summary>
		public ref class TapiCallStateEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			CALL_STATE _cs;
			CALL_STATE_EVENT_CAUSE _ce;
		protected public:
			TapiCallStateEventArgs(TAddress^ owner, IDispatch* pi);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiCallStateEventArgs: Call={0}, State={1}, Cause={2}", _call, _cs, _ce);
			}

			/// <summary>
			/// The call which has changed state
			/// </summary>
			property TCall^ Call 
			{
				TCall^ get() { return _call; }
			}

			/// <summary>
			/// The new status of the call
			/// </summary>
			property CALL_STATE State
			{
				CALL_STATE get() { return _cs; }
			}

			/// <summary>
			/// The cause for the call state change
			/// </summary>
			property CALL_STATE_EVENT_CAUSE Cause
			{
				CALL_STATE_EVENT_CAUSE get() { return _ce; }
			}
		};

		/// <summary>
		/// Different call media event types
		/// </summary>
		public enum struct CALL_MEDIA_EVENT
		{
			CME_NEW_STREAM	= 0,
			CME_STREAM_FAIL	= ( CME_NEW_STREAM + 1 ) ,
			CME_TERMINAL_FAIL	= ( CME_STREAM_FAIL + 1 ) ,
			CME_STREAM_NOT_USED	= ( CME_TERMINAL_FAIL + 1 ) ,
			CME_STREAM_ACTIVE	= ( CME_STREAM_NOT_USED + 1 ) ,
			CME_STREAM_INACTIVE	= ( CME_STREAM_ACTIVE + 1 ) ,
		};

		/// <summary>
		/// The call media event cause
		/// </summary>
		public enum struct CALL_MEDIA_EVENT_CAUSE
		{
			CMC_UNKNOWN	= 0,
			CMC_BAD_DEVICE	= ( CMC_UNKNOWN + 1 ) ,
			CMC_CONNECT_FAIL	= ( CMC_BAD_DEVICE + 1 ) ,
			CMC_LOCAL_REQUEST	= ( CMC_CONNECT_FAIL + 1 ) ,
			CMC_REMOTE_REQUEST	= ( CMC_LOCAL_REQUEST + 1 ) ,
			CMC_MEDIA_TIMEOUT	= ( CMC_REMOTE_REQUEST + 1 ) ,
			CMC_MEDIA_RECOVERED	= ( CMC_MEDIA_TIMEOUT + 1 ) ,
			CMC_QUALITY_OF_SERVICE	= ( CMC_MEDIA_RECOVERED + 1 ) 
		};

		/// <summary>
		/// This event argument structure is supplied with a TE_CALLMEDIA event
		/// </summary>
		public ref class TapiCallMediaEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			CALL_MEDIA_EVENT _event;
			CALL_MEDIA_EVENT_CAUSE _cause;
			TStream^ _stm;
			TTerminal^ _terminal;
			TapiException^ _err;
		protected public:
			TapiCallMediaEventArgs(TAddress^ owner, IDispatch* pi);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiCallMediaEventArgs: Event={0}, Call={1}, Cause={2}, Stream={3}, Terminal={4}, Err={5}", _event, _call, _cause, _stm, _terminal, _err);
			}

			/// <summary>
			/// The call associated with the media event (may be null)
			/// </summary>
			property TCall^ Call 
			{
				TCall^ get() { return _call; }
			}

			/// <summary>
			/// The terminal associated with the media event (may be null)
			/// </summary>
			property TTerminal^ Terminal 
			{
				TTerminal^ get() { return _terminal; }
			}

			/// <summary>
			/// The stream associated with the media event (may be null)
			/// </summary>
			property TStream^ Stream 
			{
				TStream^ get() { return _stm; }
			}

			/// <summary>
			/// Any error reported (may be null)
			/// </summary>
			property TapiException^ Error 
			{
				TapiException^ get() { return _err; }
			}

			/// <summary>
			/// The media event being reported
			/// </summary>
			property CALL_MEDIA_EVENT Event 
			{
				CALL_MEDIA_EVENT get() { return _event; }
			}

			/// <summary>
			/// The cause of the media event
			/// </summary>
			property CALL_MEDIA_EVENT_CAUSE Cause 
			{
				CALL_MEDIA_EVENT_CAUSE get() { return _cause; }
			}
		};

		/// <summary>
		/// This event argument structure is supplied with a CE_CALLHUB event
		/// </summary>
		public ref class TapiCallHubEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			TCallHub^ _hub;
		protected public:
			TapiCallHubEventArgs(TTapi^ tapiOb, TAddress^ owner, IDispatch* piDispatch);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiCallHubEventArgs: Call={0}, Hub={1}", _call, _hub);
			}

			/// <summary>
			/// The call associated with the hub (may be null)
			/// </summary>
			property TCall^ Call 
			{
				TCall^ get() { return _call; }
			}

			/// <summary>
			/// The call hub object
			/// </summary>
			property TCallHub^ CallHub
			{
				TCallHub^ get() { return _hub; }
			}
		};

		/// <summary>
		/// The different types of call information which may change
		/// </summary>
		public enum struct CALLINFOCHANGE_CAUSE
		{
			CIC_OTHER	= 0,
			CIC_DEVSPECIFIC	= ( CIC_OTHER + 1 ) ,
			CIC_BEARERMODE	= ( CIC_DEVSPECIFIC + 1 ) ,
			CIC_RATE	= ( CIC_BEARERMODE + 1 ) ,
			CIC_APPSPECIFIC	= ( CIC_RATE + 1 ) ,
			CIC_CALLID	= ( CIC_APPSPECIFIC + 1 ) ,
			CIC_RELATEDCALLID	= ( CIC_CALLID + 1 ) ,
			CIC_ORIGIN	= ( CIC_RELATEDCALLID + 1 ) ,
			CIC_REASON	= ( CIC_ORIGIN + 1 ) ,
			CIC_COMPLETIONID	= ( CIC_REASON + 1 ) ,
			CIC_NUMOWNERINCR	= ( CIC_COMPLETIONID + 1 ) ,
			CIC_NUMOWNERDECR	= ( CIC_NUMOWNERINCR + 1 ) ,
			CIC_NUMMONITORS	= ( CIC_NUMOWNERDECR + 1 ) ,
			CIC_TRUNK	= ( CIC_NUMMONITORS + 1 ) ,
			CIC_CALLERID	= ( CIC_TRUNK + 1 ) ,
			CIC_CALLEDID	= ( CIC_CALLERID + 1 ) ,
			CIC_CONNECTEDID	= ( CIC_CALLEDID + 1 ) ,
			CIC_REDIRECTIONID	= ( CIC_CONNECTEDID + 1 ) ,
			CIC_REDIRECTINGID	= ( CIC_REDIRECTIONID + 1 ) ,
			CIC_USERUSERINFO	= ( CIC_REDIRECTINGID + 1 ) ,
			CIC_HIGHLEVELCOMP	= ( CIC_USERUSERINFO + 1 ) ,
			CIC_LOWLEVELCOMP	= ( CIC_HIGHLEVELCOMP + 1 ) ,
			CIC_CHARGINGINFO	= ( CIC_LOWLEVELCOMP + 1 ) ,
			CIC_TREATMENT	= ( CIC_CHARGINGINFO + 1 ) ,
			CIC_CALLDATA	= ( CIC_TREATMENT + 1 ) ,
			CIC_PRIVILEGE	= ( CIC_CALLDATA + 1 ) ,
			CIC_MEDIATYPE	= ( CIC_PRIVILEGE + 1 ) ,
		};

		/// <summary>
		/// This event argument structure is passed with a CE_CALLINFO event
		/// </summary>
		public ref class TapiCallInfoChangeEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			CALLINFOCHANGE_CAUSE _cause;
		protected public:
			TapiCallInfoChangeEventArgs(TAddress^ owner, IDispatch* piDispatch);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiCallInfoChangeEventArgs: Call={0}, Cause={1}", _call, _cause);
			}

			/// <summary>
			/// The call which has changed
			/// </summary>
			property TCall^ Call 
			{
				TCall^ get() { return _call; }
			}

			/// <summary>
			/// The element in the call that has changed
			/// </summary>
			property CALLINFOCHANGE_CAUSE Cause
			{
				CALLINFOCHANGE_CAUSE get() { return _cause; }
			}
		};


		/// <summary>
		/// Describe different types of telephony requests that can be made from one application to another
		/// </summary>
		[Flags]
		public enum struct LINEREQUESTMODE
		{
			DROP = LINEREQUESTMODE_DROP,
			MAKECALL = LINEREQUESTMODE_MAKECALL,
			MEDIACALL = LINEREQUESTMODE_MEDIACALL
		};

		/// <summary>
		/// This structure details the assisted telephony requests and is passed with a TE_REQUEST event
		/// </summary>
		public ref class TapiRequestEventArgs : EventArgs
		{
		private:
			long _regInstance;
			long _mode;
			String^ _number;
			String^ _appName;
			String^ _calledParty;
			String^ _comment;
		protected public:
			TapiRequestEventArgs(IDispatch* piDispatch)
			{
				CComQIPtr<Native::ITRequestEvent> pevt = piDispatch;
				long lValue;
				if (SUCCEEDED(pevt->get_RegistrationInstance(&lValue)))
					_regInstance = lValue;
				if (SUCCEEDED(pevt->get_RequestMode(&lValue)))
					_mode = lValue;
				CComBSTR bstrValue;
				if (SUCCEEDED(pevt->get_DestAddress(&bstrValue)))
					_number = gcnew String((wchar_t*)bstrValue);
				bstrValue.Empty();
				if (SUCCEEDED(pevt->get_AppName(&bstrValue)))
					_appName = gcnew String((wchar_t*)bstrValue);
				bstrValue.Empty();
				if (SUCCEEDED(pevt->get_CalledParty(&bstrValue)))
					_calledParty = gcnew String((wchar_t*)bstrValue);
				bstrValue.Empty();
				if (SUCCEEDED(pevt->get_Comment(&bstrValue)))
					_comment = gcnew String((wchar_t*)bstrValue);
				bstrValue.Empty();
			}
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiRequestEventArgs: App={0}, Number={1}", _appName, _number);
			}

			/// <summary>
			/// The registration instance
			/// </summary>
			property long RegistrationInstance
			{
				long get() { return _regInstance; }
			}

			/// <summary>
			/// The LINEREQUESTMODE_xxx identifier
			/// </summary>
			property LINEREQUESTMODE RequestMode
			{
				LINEREQUESTMODE get() { return (LINEREQUESTMODE)_mode; }
			}

			/// <summary>
			/// 
			/// </summary>
			property String^ DestAddress
			{
				String^ get() { return _number; }
			}

			/// <summary>
			/// 
			/// </summary>
			property String^ AppName
			{
				String^ get() { return _appName; }
			}

			/// <summary>
			/// 
			/// </summary>
			property String^ CalledParty
			{
				String^ get() { return _calledParty; }
			}

			/// <summary>
			/// 
			/// </summary>
			property String^ Comment
			{
				String^ get() { return _comment; }
			}
		};

		[Flags]
		public enum struct LINEDIGITMODE
		{
			DTMF = LINEDIGITMODE_DTMF,
			DTMFEND = LINEDIGITMODE_DTMFEND,
			PULSE = LINEDIGITMODE_PULSE
		};

		public ref class TapiDigitDetectionEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			byte _digit;
			LINEDIGITMODE _mode;
			long _tickCount;
		protected public:
			TapiDigitDetectionEventArgs(TAddress^ addr, IDispatch* p);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiDigitDetectionEventArgs: Call={0}, Digit={1}, Mode={2}", _call, _digit, _mode);
			}

			property TCall^ Call
			{
				TCall^ get() { return _call; }
			}
			property byte Digit 
			{
				byte get() { return _digit; }
			}
			property LINEDIGITMODE DigitMode 
			{
				LINEDIGITMODE get() { return _mode; }
			}
			property long TickCount
			{
				long get() { return _tickCount; }
			}
		};

		public enum struct LINEGENERATETERMINATOR
		{
			Cancel = LINEGENERATETERM_CANCEL,
			Done = LINEGENERATETERM_DONE
		};

		public ref class TapiDigitGenerationEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			long _tickCount;
			LINEGENERATETERMINATOR _term;
		protected public:
			TapiDigitGenerationEventArgs(TAddress^ addr, IDispatch* p);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiDigitGenerationEventArgs: Call={0}, Term={1}", _call, _term);
			}

			property TCall^ Call
			{
				TCall^ get() { return _call; }
			}
			property long TickCount
			{
				long get() { return _tickCount; }
			}
			property LINEGENERATETERMINATOR GenerationTermination
			{
				LINEGENERATETERMINATOR get() { return _term; }
			}
		};

		public enum struct TAPI_TONEMODE
		{	
			TTM_RINGBACK	= 0x2,
			TTM_BUSY	= 0x4,
			TTM_BEEP	= 0x8,
			TTM_BILLING	= 0x10
		};

		public ref class TCustomTone
		{
		private:
			long _frequency;
			long _cadenceOn;
			long _cadenceOff;
			long _volume;
		public:
			virtual String^ ToString() override
			{
				return String::Format("TCustomTone: Freq={0}, on={1}, off={2}, vol={3}", _frequency, _cadenceOn, _cadenceOff, _volume);
			}

			TCustomTone(long frequency, long cadenceOn, long cadenceOff, long volume) :
				_frequency(frequency), _cadenceOff(cadenceOff), _cadenceOn(cadenceOn), _volume(volume) {/* */}
			
			property long Frequency
			{
				long get() { return _frequency; }
				void set(long value) { _frequency = value; }
			}
			property long CadenceOn
			{
				long get() { return _cadenceOn; }
				void set(long value) { _cadenceOn = value; }
			}
			property long CadenceOff
			{
				long get() { return _cadenceOff; }
				void set(long value) { _cadenceOff = value; }
			}
			property long Volume
			{
				long get() { return _volume; }
				void set(long value) { _volume = value; }
			}
		};

		public ref class TDetectTone
		{
		private:
			long _appSpecific;
			long _duration;
			long _frequency1;
			long _frequency2;
			long _frequency3;

		public:
			virtual String^ ToString() override
			{
				return String::Format("TDetectTone: Duration={0}, 1={1}, 2={2}, 3={3}", _duration, _frequency1, _frequency2, _frequency3);
			}

			TDetectTone(long appSpecific, long duration, long frequency1) :
				_appSpecific(appSpecific), _duration(duration), _frequency1(frequency1), _frequency2(0), _frequency3(0) {/* */}
			TDetectTone(long appSpecific, long duration, long frequency1, long frequency2) :
				_appSpecific(appSpecific), _duration(duration), _frequency1(frequency1), _frequency2(frequency2), _frequency3(0) {/* */}
			TDetectTone(long appSpecific, long duration, long frequency1, long frequency2, long frequency3) :
				_appSpecific(appSpecific), _duration(duration), _frequency1(frequency1), _frequency2(frequency2), _frequency3(frequency3) {/* */}
			
			property long AppSpecific
			{
				long get() { return _appSpecific; }
				void set(long value) { _appSpecific = value; }
			}
			property long Duration
			{
				long get() { return _duration; }
				void set(long value) { _duration = value; }
			}
			property long default[int]
			{
				long get(int index) 
				{ 
					switch (index)
					{
						case 0: return _frequency1;
						case 1: return _frequency2;
						case 2: return _frequency3;
					}
					throw gcnew IndexOutOfRangeException();	
				}

				void set(int index, long value) 
				{ 
					switch (index)
					{
						case 0: _frequency1 = value; break;
						case 1: _frequency2 = value; break;
						case 2: _frequency3 = value; break;
						default: throw gcnew IndexOutOfRangeException();	
					}
				}
			}
		};

		public ref class TapiToneDetectionEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			long _appSpecific;
			long _tickCount;
			int _index;
		protected public:
			TapiToneDetectionEventArgs(TAddress^ owner, IDispatch* piDispatch);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiToneDetectionEventArgs: Call={0}, AppSpecific={2}", _call, _appSpecific);
			}

			property TCall^ Call
			{
				TCall^ get() { return _call; }
			}
			property long TickCount
			{
				long get() { return _tickCount; }
			}
			property long AppSpecific
			{
				long get() { return _appSpecific; }
			}
			property int ToneListID
			{
				int get() { return _index; }
			}
		};

		public enum struct TAPI_GATHERTERM
		{
			TGT_BUFFERFULL	= 0x1,
			TGT_TERMDIGIT	= 0x2,
			TGT_FIRSTTIMEOUT = 0x4,
			TGT_INTERTIMEOUT = 0x8,
			TGT_CANCEL	= 0x10
		};

		public ref class TapiDigitsGatheredEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			String^ _digits;
			long _tickCount;
			TAPI_GATHERTERM _term;
		protected public:
			TapiDigitsGatheredEventArgs(TAddress^ owner, IDispatch* piDispatch);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiDigitsGatheredEventArgs: Call={0}, Digits={2}, Term={3}", _call, _digits, _term);
			}

			property TCall^ Call
			{
				TCall^ get() { return _call; }
			}
			property long TickCount
			{
				long get() { return _tickCount; }
			}
			property String^ Digits
			{
				String^ get() { return _digits; }
			}
			property TAPI_GATHERTERM GatherTermination
			{
				TAPI_GATHERTERM get() { return _term; }
			}
		};
	
		public enum struct QOS_EVENT
		{
			QE_NOQOS	= 1,
			QE_ADMISSIONFAILURE	= 2,
			QE_POLICYFAILURE	= 3,
			QE_GENERICERROR	= 4,
		};

		public ref class TapiQOSEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			QOS_EVENT _event;
			TAPIMEDIATYPES _media;
		protected public:
			TapiQOSEventArgs(TAddress^ owner, IDispatch* piDispatch);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiQOSEventArgs: Event={0}, Call={2}, Media={3}", _event, _call, _media);
			}

			property TCall^ Call
			{
				TCall^ get() { return _call; }
			}
			property QOS_EVENT Event 
			{
				QOS_EVENT get() { return _event; }
			}
			property TAPIMEDIATYPES MediaType 
			{
				TAPIMEDIATYPES get() { return _media; }
			}
		};

		public ref class TapiTTSTerminalEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			TTerminal^ _terminal;
			TapiException^ _error;
		protected public:
			TapiTTSTerminalEventArgs(TAddress^ owner, IDispatch* piDispatch);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiTTSTerminalEventArgs: Call={0}, Terminal={2}, Error={3}", _call, _terminal, _error);
			}

			property TCall^ Call 
			{
				TCall^ get() { return _call; }
			}

			property TTerminal^ Terminal 
			{
				TTerminal^ get() { return _terminal; }
			}

			property TapiException^ Error 
			{
				TapiException^ get() { return _error; }
			}
		};

		public ref class TapiASRTerminalEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			TTerminal^ _terminal;
			TapiException^ _error;
		protected public:
			TapiASRTerminalEventArgs(TAddress^ owner, IDispatch* piDispatch);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiASRTerminalEventArgs: Call={0}, Terminal={2}, Error={3}", _call, _terminal, _error);
			}

			property TCall^ Call 
			{
				TCall^ get() { return _call; }
			}

			property TTerminal^ Terminal 
			{
				TTerminal^ get() { return _terminal; }
			}

			property TapiException^ Error 
			{
				TapiException^ get() { return _error; }
			}
		};

		public enum struct FT_STATE_EVENT_CAUSE
		{
			FTEC_NORMAL	= 0,
			FTEC_END_OF_FILE	= ( FTEC_NORMAL + 1 ) ,
			FTEC_READ_ERROR	= ( FTEC_END_OF_FILE + 1 ) ,
			FTEC_WRITE_ERROR	= ( FTEC_READ_ERROR + 1 ) 
		};

		public ref class TapiFileTerminalEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			TTerminal^ _terminal;
			TapiException^ _error;
			TERMINAL_MEDIA_STATE _state;
			FT_STATE_EVENT_CAUSE _cause;
			TFileTrack^ _track;

		protected public:
			TapiFileTerminalEventArgs(TAddress^ owner, IDispatch* piDispatch);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiFileTerminalEventArgs: Call={0},Terminal={1}, Error={2}, State={3}, Cause={4}, FileTrack={5}", _call, _terminal, _error, _state, _cause, _track);
			}

			property TCall^ Call 
			{
				TCall^ get() { return _call; }
			}

			property TFileTrack^ Track 
			{
				TFileTrack^ get() { return _track; }
			}

			property FT_STATE_EVENT_CAUSE Cause 
			{
				FT_STATE_EVENT_CAUSE get() { return _cause; }
			}

			property TERMINAL_MEDIA_STATE State
			{
				TERMINAL_MEDIA_STATE get() { return _state; }
			}

			property TTerminal^ Terminal 
			{
				TTerminal^ get() { return _terminal; }
			}

			property TapiException^ Error 
			{
				TapiException^ get() { return _error; }
			}
		};

		public ref class TapiToneTerminalEventArgs : EventArgs
		{
		private:
			TCall^ _call;
			TTerminal^ _terminal;
			TapiException^ _error;
		protected public:
			TapiToneTerminalEventArgs(TAddress^ owner, IDispatch* piDispatch);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiToneTerminalEventArgs: Call={0}, Terminal={2}, Error={3}", _call, _terminal, _error);
			}

			property TCall^ Call 
			{
				TCall^ get() { return _call; }
			}

			property TTerminal^ Terminal 
			{
				TTerminal^ get() { return _terminal; }
			}

			property TapiException^ Error 
			{
				TapiException^ get() { return _error; }
			}
		};

		public ref class TapiDeviceSpecificEventArgs : EventArgs
		{
		private:
			Object^ _ob;
		protected public:
			TapiDeviceSpecificEventArgs(IDispatch* pevt)
			{
				_ob = Marshal::GetObjectForIUnknown(IntPtr((void*)pevt));
			}
		public:
			property Object^ DeviceSpecificObject
			{
				Object^ get() { return _ob; }
			}
		};

		public ref class TapiAddressDeviceSpecificEventArgs : EventArgs
		{
		private:
			TAddress^ _addr;
			TCall^ _call;
			long _lParam1;
			long _lParam2;
			long _lParam3;

		protected public:
			TapiAddressDeviceSpecificEventArgs(TTapi^ owner, IDispatch* pevt);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiAddressDeviceSpecificEventArgs: Address={0}, Call={2}, 1={3}, 2={4}, 3={5}", _addr, _call, _lParam1, _lParam2, _lParam3);
			}

			property TAddress^ Address 
			{
				TAddress^ get()	{ return _addr; }
			}
			property TCall^ Call
			{
				TCall^ get() { return _call; }
			}
			property long lParam1
			{
				long get() { return _lParam1; }
			}
			property long lParam2
			{
				long get() { return _lParam2; }
			}
			property long lParam3
			{
				long get() { return _lParam3; }
			}
		};

		public enum struct PHONE_EVENT
		{
			PE_DISPLAY	= 0,
			PE_LAMPMODE	= ( PE_DISPLAY + 1 ) ,
			PE_RINGMODE	= ( PE_LAMPMODE + 1 ) ,
			PE_RINGVOLUME	= ( PE_RINGMODE + 1 ) ,
			PE_HOOKSWITCH	= ( PE_RINGVOLUME + 1 ) ,
			PE_CAPSCHANGE	= ( PE_HOOKSWITCH + 1 ) ,
			PE_BUTTON	= ( PE_CAPSCHANGE + 1 ) ,
			PE_CLOSE	= ( PE_BUTTON + 1 ) ,
			PE_NUMBERGATHERED	= ( PE_CLOSE + 1 ) ,
			PE_DIALING	= ( PE_NUMBERGATHERED + 1 ) ,
			PE_ANSWER	= ( PE_DIALING + 1 ) ,
			PE_DISCONNECT	= ( PE_ANSWER + 1 ) ,
		};

		public enum struct PHONE_HOOK_SWITCH_DEVICE
		{	
			PHSD_HANDSET	= 0x1,
			PHSD_SPEAKERPHONE	= 0x2,
			PHSD_HEADSET	= 0x4
		};

		public enum struct PHONE_HOOK_SWITCH_STATE
		{	
			PHSS_ONHOOK	= 0x1,
			PHSS_OFFHOOK_MIC_ONLY	= 0x2,
			PHSS_OFFHOOK_SPEAKER_ONLY	= 0x4,
			PHSS_OFFHOOK	= 0x8
		};

		public enum struct PHONE_BUTTON_STATE
		{	
			PBS_UP	= 0x1,
			PBS_DOWN	= 0x2,
			PBS_UNKNOWN	= 0x4,
			PBS_UNAVAIL	= 0x8
		};

		public ref class TapiPhoneEventArgs : EventArgs
		{
		private:
			TPhone^ _phone;
			PHONE_EVENT _event;
			PHONE_BUTTON_STATE _buttonState;
			PHONE_HOOK_SWITCH_STATE _hsState;
			PHONE_HOOK_SWITCH_DEVICE _hsDevice;
			long _ringMode;
			long _lampId;
			String^ _number;
			TCall^ _call;
		protected private:
			TapiPhoneEventArgs(TTapi^ owner, IDispatch* piDispatch);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiPhoneEventArgs: Phone={0},  Event={2}", _phone, _event);
			}

			property TPhone^ Phone
			{
				TPhone^ get() { return _phone; }
			}
			property PHONE_EVENT Event 
			{
				PHONE_EVENT get() { return _event; }
			}
			property PHONE_BUTTON_STATE ButtonState 
			{
				PHONE_BUTTON_STATE get() { return _buttonState; }
			}
			property PHONE_HOOK_SWITCH_STATE HookSwitchState
			{
				PHONE_HOOK_SWITCH_STATE get() { return _hsState; }
			}
			property PHONE_HOOK_SWITCH_DEVICE HookSwitchDevice
			{
				PHONE_HOOK_SWITCH_DEVICE get() { return _hsDevice; }
			}
			property long RingMode 
			{
				long get() { return _ringMode; }
			}
			property long ButtonLampId 
			{
				long get() { return _lampId; }
			}
			property String^ NumberGathered 
			{
				String^ get() { return _number; }
			}
			property TCall^ Call 
			{
				TCall^ get() { return _call; }
			}
		};

		public ref class TapiPhoneDeviceSpecificEventArgs : EventArgs
		{
			TPhone^ _phone;
			long _lParam1;
			long _lParam2;
			long _lParam3;

		protected public:
			TapiPhoneDeviceSpecificEventArgs(TTapi^ owner, IDispatch* pevt);
		public:
			virtual String^ ToString() override
			{
				return String::Format("TapiPhoneDeviceSpecificEventArgs: Phone={0}, 1={1}, 2={2}, 3={3}", _phone, _lParam1, _lParam2, _lParam3);
			}

			property TPhone^ Phone
			{
				TPhone^ get()	{ return _phone; }
			}
			property long lParam1
			{
				long get() { return _lParam1; }
			}
			property long lParam2
			{
				long get() { return _lParam2; }
			}
			property long lParam3
			{
				long get() { return _lParam3; }
			}
		};

	}
}