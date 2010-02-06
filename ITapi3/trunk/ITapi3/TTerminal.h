// TTerminal.h
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
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace JulMar
{
	namespace Tapi3 
	{
		ref class AM_MEDIA_TYPE;

		[Flags]
		public enum struct TAPIMEDIATYPES
		{
			AUDIO = TAPIMEDIATYPE_AUDIO,
			VIDEO = TAPIMEDIATYPE_VIDEO,
			DATAMODEM = TAPIMEDIATYPE_DATAMODEM,
			G3FAX = TAPIMEDIATYPE_G3FAX,
			MULTITRACK = TAPIMEDIATYPE_MULTITRACK
		};

		public enum struct TERMINAL_DIRECTION
		{
			TD_CAPTURE	= 0,
			TD_RENDER	= ( TD_CAPTURE + 1 ) ,
			TD_BIDIRECTIONAL	= ( TD_RENDER + 1 ) ,
			TD_MULTITRACK_MIXED	= ( TD_BIDIRECTIONAL + 1 ) ,
			TD_NONE	= ( TD_MULTITRACK_MIXED + 1 ) 
		};

		public enum struct TERMINAL_MEDIA_STATE
		{
			TMS_IDLE	= 0,
			TMS_ACTIVE	= ( TMS_IDLE + 1 ) ,
			TMS_PAUSED	= ( TMS_ACTIVE + 1 ) ,
		};

		public enum struct TERMINAL_STATE
		{
			TS_INUSE	= 0,
			TS_NOTINUSE	= ( TS_INUSE + 1 ) 
		};

		public enum struct TERMINAL_TYPE
		{	
			TT_STATIC	= 0,
			TT_DYNAMIC	= ( TT_STATIC + 1 ) 
		};

		public ref class TTerminal sealed : Internal::TapiBase
		{
		private:
			TTerminal(IUnknown* p) : Internal::TapiBase(p) {/* */}

		protected public:
			static TTerminal^ CreateTerminal(IUnknown* p);
			CComPtr<Native::ITTerminal> GetTerminalItf() { return CastToInterface<Native::ITTerminal,true>(); }
			CComPtr<Native::ITAMMediaFormat> GetAMMediaFormatItf() { return CastToInterface<Native::ITAMMediaFormat,true>(); }
			CComPtr<Native::ITBasicAudioTerminal> GetBasicAudioItf() { return CastToInterface<Native::ITBasicAudioTerminal,true>(); }
			CComPtr<Native::ITAllocatorProperties> GetAllocatorItf() { return CastToInterface<Native::ITAllocatorProperties,true>(); }
			CComPtr<Native::ITMediaPlayback> GetMediaPlaybackItf() { return CastToInterface<Native::ITMediaPlayback,true>(); }
			CComPtr<Native::ITMediaRecord> GetMediaRecordItf() { return CastToInterface<Native::ITMediaRecord,true>(); }
			CComPtr<Native::ITMediaControl> GetMediaControlItf() { return CastToInterface<Native::ITMediaControl,true>(); }

		public:
			// Define common terminal types along with the wk guid
			static initonly String^ VideoWindowTerminal = "{F7438990-D6EB-11d0-82A6-00AA00B5CA1B}";		// Video window
			static initonly String^ VideoInputTerminal = "{AAF578EC-DC70-11d0-8ED3-00C04FB6809F}";		// Video input (camera) 
			static initonly String^ HandsetTerminal = "{AAF578EB-DC70-11d0-8ED3-00C04FB6809F}";			// Handset device 
			static initonly String^ HeadsetTerminal = "{AAF578ED-DC70-11d0-8ED3-00C04FB6809F}";			// Headset device 
			static initonly String^ SpeakerphoneTerminal = "{AAF578EE-DC70-11d0-8ED3-00C04FB6809F}";	// Speakerphone device 
			static initonly String^ MicrophoneTerminal = "{AAF578EF-DC70-11d0-8ED3-00C04FB6809F}";		// Microphone (sound card) 
			static initonly String^ SpeakersTerminal = "{AAF578F0-DC70-11d0-8ED3-00C04FB6809F}";		// Speakers (sound card) 
			static initonly String^ MediaStreamTerminal = "{E2F7AEF7-4971-11D1-A671-006097C9A2E8}";		// Media stream terminal 
			static initonly String^ FileRecordingTerminal = "{521F3D06-C3D0-4511-8617-86B9A783DA77}";	// File Recording terminal 
			static initonly String^ FileRecordingTrack = "{BF14A2E4-E88B-4ef5-9740-5AC5D022F8C9}";		// File Recording Track 
			static initonly String^ FilePlaybackTerminal = "{0CB9914C-79CD-47dc-ADB0-327F47CEFB20}";	// File Playback Terminal 

			~TTerminal()
			{
				Release(false);
			}

			virtual String^ ToString() override
			{
				return String::Format("TTerminal {0} {1} {2} {3}", Name, MediaType, Direction, State);
			}

			property String^ Name 
			{
				String^ get()
				{
					CComBSTR bstrName;
					if (SUCCEEDED(GetTerminalItf()->get_Name(&bstrName)))
						return gcnew String((wchar_t*)bstrName);
					return String::Empty;
				}
			}

			property TERMINAL_STATE State
			{
				TERMINAL_STATE get()
				{
					Native::TERMINAL_STATE lValue;
					if (SUCCEEDED(GetTerminalItf()->get_State(&lValue)))
						return (TERMINAL_STATE) lValue;
					return TERMINAL_STATE::TS_NOTINUSE;
				}
			}

			property TERMINAL_TYPE TerminalType
			{
				TERMINAL_TYPE get()
				{
					Native::TERMINAL_TYPE lValue;
					TapiException::ThrowExceptionForHR(GetTerminalItf()->get_TerminalType(&lValue));
					return (TERMINAL_TYPE) lValue;
				}
			}

			property String^ TerminalClass
			{
				String^ get()
				{
					CComBSTR bstrValue;
					TapiException::ThrowExceptionForHR(GetTerminalItf()->get_TerminalClass(&bstrValue));
					return gcnew String((wchar_t*)bstrValue);
				}
			}

			property TAPIMEDIATYPES MediaType
			{
				TAPIMEDIATYPES get()
				{
					long lValue;
					TapiException::ThrowExceptionForHR(GetTerminalItf()->get_MediaType(&lValue));
					return (TAPIMEDIATYPES)lValue;
				}
			}

			property AM_MEDIA_TYPE^ MediaFormat
			{
				AM_MEDIA_TYPE^ get()
				{
					return GetMediaFormat();
				}

				void set(AM_MEDIA_TYPE^ value)
				{
					SetMediaFormat(value);
				}
			}

			property TERMINAL_DIRECTION Direction
			{
				TERMINAL_DIRECTION get()
				{
					Native::TERMINAL_DIRECTION lValue;
					TapiException::ThrowExceptionForHR(GetTerminalItf()->get_Direction(&lValue));
					return (TERMINAL_DIRECTION)lValue;
				}
			}

			property long Volume
			{
				long get()
				{
					long volume;
					TapiException::ThrowExceptionForHR(GetBasicAudioItf()->get_Volume(&volume));
					return volume;
				}
				void set(long value)
				{
					TapiException::ThrowExceptionForHR(GetBasicAudioItf()->put_Volume(value));
				}
			}

			property long Balance
			{
				long get()
				{
					long balance;
					TapiException::ThrowExceptionForHR(GetBasicAudioItf()->get_Balance(&balance));
					return balance;
				}
				void set(long value)
				{
					TapiException::ThrowExceptionForHR(GetBasicAudioItf()->put_Balance(value));
				}
			}

			property unsigned long BufferSize
			{
				unsigned long get()
				{
					DWORD dwSize;
					TapiException::ThrowExceptionForHR(GetAllocatorItf()->GetBufferSize(&dwSize));
					return dwSize;
				}
				void set(unsigned long size)
				{
					TapiException::ThrowExceptionForHR(GetAllocatorItf()->SetBufferSize(size));
				}
			}

			property bool AllocateBuffers
			{
				bool get()
				{
					BOOL b;
					TapiException::ThrowExceptionForHR(GetAllocatorItf()->GetAllocateBuffers(&b));
					return (b == TRUE);
				}
				void set(bool value)
				{
					BOOL b = (value == true);
					TapiException::ThrowExceptionForHR(GetAllocatorItf()->SetAllocateBuffers(b));
				}
			}

			void GetAllocatorProperties(long% bufferCount, long% bufferSize, long% bufferAlignment, long% bufferPrefix)
			{
				Native::ALLOCATOR_PROPERTIES aProp;
				TapiException::ThrowExceptionForHR(GetAllocatorItf()->GetAllocatorProperties(&aProp));
				bufferCount = aProp.cBuffers;
				bufferSize = aProp.cbBuffer;
				bufferAlignment = aProp.cbAlign;
				bufferPrefix = aProp.cbPrefix;
			}

			void SetAllocatorProperties(long bufferCount, long bufferSize, long bufferAlignment, long bufferPrefix)
			{
				Native::ALLOCATOR_PROPERTIES aProp;
				aProp.cBuffers = bufferCount;
				aProp.cbBuffer = bufferSize;
				aProp.cbAlign = bufferAlignment;
				aProp.cbPrefix = bufferPrefix;
				TapiException::ThrowExceptionForHR(GetAllocatorItf()->SetAllocatorProperties(&aProp));
			}

			property array<String^>^ MediaPlayList
			{
				array<String^>^ get()
				{
					List<String^>^ retData = gcnew List<String^>();
					try 
					{
						VARIANT vt;
						VariantInit(&vt);

						TapiException::ThrowExceptionForHR(GetMediaPlaybackItf()->get_PlayList(&vt));

						// Expect a VT_ARRAY containing VT_BSTR types
						if (vt.vt & VT_ARRAY)
						{
							CComSafeArray<VARIANT> sa;
							sa.Attach(vt.parray);

							long count = sa.GetCount();
							for (long i = 0; i < count; i++)
							{
								BSTR bstr = sa.GetAt(i+1).bstrVal;
								retData->Add(gcnew String((wchar_t*)bstr));
							}
						}
					}
					catch (Exception^ ex)
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Error, ex->ToString());
					}
					return retData->ToArray();
				}

				void set(array<String^>^ fileList)
				{
					if (fileList == nullptr)
						throw gcnew ArgumentNullException("fileList");

					CComPtr<Native::ITMediaPlayback> imp = GetMediaPlaybackItf();

					// Allocate the array to hold the playlist.
					CComSafeArray<VARIANT> sa;
					sa.Create(fileList->Length, 1); long lIndex = 1;
					for each (String^ s in fileList)
						sa.SetAt(lIndex++, CComVariant(CComBSTR((BSTR)Marshal::StringToBSTR(s).ToPointer())));

					CComVariant vtIn(sa.m_psa);
					TapiException::ThrowExceptionForHR(imp->put_PlayList(vtIn));
				}
			}

			property String^ RecordFileName
			{
				String^ get()
				{
					CComBSTR bstrValue;
					TapiException::ThrowExceptionForHR(GetMediaRecordItf()->get_FileName(&bstrValue));
					return gcnew String((wchar_t*)bstrValue);
				}

				void set(String^ fileName)
				{
					CComBSTR bstrValue;
					if (!String::IsNullOrEmpty(fileName))
						bstrValue = (BSTR) Marshal::StringToBSTR(fileName).ToPointer();
					TapiException::ThrowExceptionForHR(GetMediaRecordItf()->put_FileName(bstrValue));
				}
			}
			
			property bool SupportsMediaControl
			{
				bool get() 
				{
					CComPtr<Native::ITMediaControl> p;
					return (SUCCEEDED(_p->QueryInterface(Native::IID_ITMediaControl, (void**)&p)));
				}
			}

			void Start()
			{
				TapiException::ThrowExceptionForHR(GetMediaControlItf()->Start());
			}

			void Stop()
			{
				TapiException::ThrowExceptionForHR(GetMediaControlItf()->Stop());
			}

			void Pause()
			{
				TapiException::ThrowExceptionForHR(GetMediaControlItf()->Pause());
			}

			property TERMINAL_MEDIA_STATE MediaState
			{
				TERMINAL_MEDIA_STATE get() 
				{
					Native::TERMINAL_MEDIA_STATE s;
					TapiException::ThrowExceptionForHR(GetMediaControlItf()->get_MediaState(&s));
					return (TERMINAL_MEDIA_STATE) s;
				}
			}

			private:
				AM_MEDIA_TYPE^ GetMediaFormat();
				void SetMediaFormat(AM_MEDIA_TYPE^ value);
		};
	}
}