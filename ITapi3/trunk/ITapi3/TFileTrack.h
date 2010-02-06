// TFileTrack.h
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

#include <uuids.h>

using namespace System;
using namespace System::Runtime::InteropServices;

#ifndef STATIC_GUID
#define STATIC_GUID(G) static initonly Guid G = Internal::ConversionFunctions::FromGUID(::G)
#endif

namespace JulMar
{
	namespace Tapi3
	{
		ref class TTerminal;
		ref class TMediaFormat;

		public delegate TMediaFormat^ RegisterMediaTypeDelegate(Guid guid, int cbSize, IntPtr data);

		public enum struct WAVE_FORMATS
		{
			UNKNOWN                    = 0x0000 /* Microsoft Corporation */,
			PCM                        = 0x0001 /* Microsoft Corporation */,
			ADPCM                      = 0x0002 /* Microsoft Corporation */,
			IEEE_FLOAT                 = 0x0003 /* Microsoft Corporation */,
			VSELP                      = 0x0004 /* Compaq Computer Corp. */,
			IBM_CVSD                   = 0x0005 /* IBM Corporation */,
			ALAW                       = 0x0006 /* Microsoft Corporation */,
			MULAW                      = 0x0007 /* Microsoft Corporation */,
			DTS                        = 0x0008 /* Microsoft Corporation */,
			DRM                        = 0x0009 /* Microsoft Corporation */,
			WMAVOICE9                  = 0x000A /* Microsoft Corporation */,
			WMAVOICE10                 = 0x000B /* Microsoft Corporation */,
			OKI_ADPCM                  = 0x0010 /* OKI */,
			DVI_ADPCM                  = 0x0011 /* Intel Corporation */,
			IMA_ADPCM                  = DVI_ADPCM /*  Intel Corporation */,
			MEDIASPACE_ADPCM           = 0x0012 /* Videologic */,
			SIERRA_ADPCM               = 0x0013 /* Sierra Semiconductor Corp */,
			G723_ADPCM                 = 0x0014 /* Antex Electronics Corporation */,
			DIGISTD                    = 0x0015 /* DSP Solutions, Inc. */,
			DIGIFIX                    = 0x0016 /* DSP Solutions, Inc. */,
			DIALOGIC_OKI_ADPCM         = 0x0017 /* Dialogic Corporation */,
			MEDIAVISION_ADPCM          = 0x0018 /* Media Vision, Inc. */,
			CU_CODEC                   = 0x0019 /* Hewlett-Packard Company */,
			YAMAHA_ADPCM               = 0x0020 /* Yamaha Corporation of America */,
			SONARC                     = 0x0021 /* Speech Compression */,
			DSPGROUP_TRUESPEECH        = 0x0022 /* DSP Group, Inc */,
			ECHOSC1                    = 0x0023 /* Echo Speech Corporation */,
			AUDIOFILE_AF36             = 0x0024 /* Virtual Music, Inc. */,
			APTX                       = 0x0025 /* Audio Processing Technology */,
			AUDIOFILE_AF10             = 0x0026 /* Virtual Music, Inc. */,
			PROSODY_1612               = 0x0027 /* Aculab plc */,
			LRC                        = 0x0028 /* Merging Technologies S.A. */,
			DOLBY_AC2                  = 0x0030 /* Dolby Laboratories */,
			GSM610                     = 0x0031 /* Microsoft Corporation */,
			MSNAUDIO                   = 0x0032 /* Microsoft Corporation */,
			ANTEX_ADPCME               = 0x0033 /* Antex Electronics Corporation */,
			CONTROL_RES_VQLPC          = 0x0034 /* Control Resources Limited */,
			DIGIREAL                   = 0x0035 /* DSP Solutions, Inc. */,
			DIGIADPCM                  = 0x0036 /* DSP Solutions, Inc. */,
			CONTROL_RES_CR10           = 0x0037 /* Control Resources Limited */,
			NMS_VBXADPCM               = 0x0038 /* Natural MicroSystems */,
			CS_IMAADPCM                = 0x0039 /* Crystal Semiconductor IMA ADPCM */,
			ECHOSC3                    = 0x003A /* Echo Speech Corporation */,
			ROCKWELL_ADPCM             = 0x003B /* Rockwell International */,
			ROCKWELL_DIGITALK          = 0x003C /* Rockwell International */,
			XEBEC                      = 0x003D /* Xebec Multimedia Solutions Limited */,
			G721_ADPCM                 = 0x0040 /* Antex Electronics Corporation */,
			G728_CELP                  = 0x0041 /* Antex Electronics Corporation */,
			MSG723                     = 0x0042 /* Microsoft Corporation */,
			MPEG                       = 0x0050 /* Microsoft Corporation */,
			RT24                       = 0x0052 /* InSoft, Inc. */,
			PAC                        = 0x0053 /* InSoft, Inc. */,
			MPEGLAYER3                 = 0x0055 /* ISO/MPEG Layer3 Format Tag */,
			LUCENT_G723                = 0x0059 /* Lucent Technologies */,
			CIRRUS                     = 0x0060 /* Cirrus Logic */,
			ESPCM                      = 0x0061 /* ESS Technology */,
			VOXWARE                    = 0x0062 /* Voxware Inc */,
			CANOPUS_ATRAC              = 0x0063 /* Canopus, co., Ltd. */,
			G726_ADPCM                 = 0x0064 /* APICOM */,
			G722_ADPCM                 = 0x0065 /* APICOM */,
			DSAT_DISPLAY               = 0x0067 /* Microsoft Corporation */,
			VOXWARE_BYTE_ALIGNED       = 0x0069 /* Voxware Inc */,
			VOXWARE_AC8                = 0x0070 /* Voxware Inc */,
			VOXWARE_AC10               = 0x0071 /* Voxware Inc */,
			VOXWARE_AC16               = 0x0072 /* Voxware Inc */,
			VOXWARE_AC20               = 0x0073 /* Voxware Inc */,
			VOXWARE_RT24               = 0x0074 /* Voxware Inc */,
			VOXWARE_RT29               = 0x0075 /* Voxware Inc */,
			VOXWARE_RT29HW             = 0x0076 /* Voxware Inc */,
			VOXWARE_VR12               = 0x0077 /* Voxware Inc */,
			VOXWARE_VR18               = 0x0078 /* Voxware Inc */,
			VOXWARE_TQ40               = 0x0079 /* Voxware Inc */,
			SOFTSOUND                  = 0x0080 /* Softsound, Ltd. */,
			VOXWARE_TQ60               = 0x0081 /* Voxware Inc */,
			MSRT24                     = 0x0082 /* Microsoft Corporation */,
			G729A                      = 0x0083 /* AT&T Labs, Inc. */,
			MVI_MVI2                   = 0x0084 /* Motion Pixels */,
			DF_G726                    = 0x0085 /* DataFusion Systems (Pty) (Ltd) */,
			DF_GSM610                  = 0x0086 /* DataFusion Systems (Pty) (Ltd) */,
			ISIAUDIO                   = 0x0088 /* Iterated Systems, Inc. */,
			ONLIVE                     = 0x0089 /* OnLive! Technologies, Inc. */,
			SBC24                      = 0x0091 /* Siemens Business Communications Sys */,
			DOLBY_AC3_SPDIF            = 0x0092 /* Sonic Foundry */,
			MEDIASONIC_G723            = 0x0093 /* MediaSonic */,
			PROSODY_8KBPS              = 0x0094 /* Aculab plc */,
			ZYXEL_ADPCM                = 0x0097 /* ZyXEL Communications, Inc. */,
			PHILIPS_LPCBB              = 0x0098 /* Philips Speech Processing */,
			PACKED                     = 0x0099 /* Studer Professional Audio AG */,
			MALDEN_PHONYTALK           = 0x00A0 /* Malden Electronics Ltd. */,
			RHETOREX_ADPCM             = 0x0100 /* Rhetorex Inc. */,
			IRAT                       = 0x0101 /* BeCubed Software Inc. */,
			VIVO_G723                  = 0x0111 /* Vivo Software */,
			VIVO_SIREN                 = 0x0112 /* Vivo Software */,
			DIGITAL_G723               = 0x0123 /* Digital Equipment Corporation */,
			SANYO_LD_ADPCM             = 0x0125 /* Sanyo Electric Co., Ltd. */,
			SIPROLAB_ACEPLNET          = 0x0130 /* Sipro Lab Telecom Inc. */,
			SIPROLAB_ACELP4800         = 0x0131 /* Sipro Lab Telecom Inc. */,
			SIPROLAB_ACELP8V3          = 0x0132 /* Sipro Lab Telecom Inc. */,
			SIPROLAB_G729              = 0x0133 /* Sipro Lab Telecom Inc. */,
			SIPROLAB_G729A             = 0x0134 /* Sipro Lab Telecom Inc. */,
			SIPROLAB_KELVIN            = 0x0135 /* Sipro Lab Telecom Inc. */,
			G726ADPCM                  = 0x0140 /* Dictaphone Corporation */,
			QUALCOMM_PUREVOICE         = 0x0150 /* Qualcomm, Inc. */,
			QUALCOMM_HALFRATE          = 0x0151 /* Qualcomm, Inc. */,
			TUBGSM                     = 0x0155 /* Ring Zero Systems, Inc. */,
			MSAUDIO1                   = 0x0160 /* Microsoft Corporation */,
			WMAUDIO2                   = 0x0161 /* Microsoft Corporation */,
			WMAUDIO3                   = 0x0162 /* Microsoft Corporation */,
			WMAUDIO_LOSSLESS           = 0x0163 /* Microsoft Corporation */,
			WMASPDIF                   = 0x0164 /* Microsoft Corporation */,
			UNISYS_NAP_ADPCM           = 0x0170 /* Unisys Corp. */,
			UNISYS_NAP_ULAW            = 0x0171 /* Unisys Corp. */,
			UNISYS_NAP_ALAW            = 0x0172 /* Unisys Corp. */,
			UNISYS_NAP_16K             = 0x0173 /* Unisys Corp. */,
			CREATIVE_ADPCM             = 0x0200 /* Creative Labs, Inc */,
			CREATIVE_FASTSPEECH8       = 0x0202 /* Creative Labs, Inc */,
			CREATIVE_FASTSPEECH10      = 0x0203 /* Creative Labs, Inc */,
			UHER_ADPCM                 = 0x0210 /* UHER informatic GmbH */,
			QUARTERDECK                = 0x0220 /* Quarterdeck Corporation */,
			ILINK_VC                   = 0x0230 /* I-link Worldwide */,
			RAW_SPORT                  = 0x0240 /* Aureal Semiconductor */,
			ESST_AC3                   = 0x0241 /* ESS Technology, Inc. */,
			GENERIC_PASSTHRU           = 0x0249,
			IPI_HSX                    = 0x0250 /* Interactive Products, Inc. */,
			IPI_RPELP                  = 0x0251 /* Interactive Products, Inc. */,
			CS2                        = 0x0260 /* Consistent Software */,
			SONY_SCX                   = 0x0270 /* Sony Corp. */,
			FM_TOWNS_SND               = 0x0300 /* Fujitsu Corp. */,
			BTV_DIGITAL                = 0x0400 /* Brooktree Corporation */,
			QDESIGN_MUSIC              = 0x0450 /* QDesign Corporation */,
			VME_VMPCM                  = 0x0680 /* AT&T Labs, Inc. */,
			TPC                        = 0x0681 /* AT&T Labs, Inc. */,
			OLIGSM                     = 0x1000 /* Ing C. Olivetti & C., S.p.A. */,
			OLIADPCM                   = 0x1001 /* Ing C. Olivetti & C., S.p.A. */,
			OLICELP                    = 0x1002 /* Ing C. Olivetti & C., S.p.A. */,
			OLISBC                     = 0x1003 /* Ing C. Olivetti & C., S.p.A. */,
			OLIOPR                     = 0x1004 /* Ing C. Olivetti & C., S.p.A. */,
			LH_CODEC                   = 0x1100 /* Lernout & Hauspie */,
			NORRIS                     = 0x1400 /* Norris Communications, Inc. */,
			SOUNDSPACE_MUSICOMPRESS    = 0x1500 /* AT&T Labs, Inc. */,
			MPEG_ADTS_AAC              = 0x1600 /* Microsoft Corporation */,
			MPEG_RAW_AAC               = 0x1601 /* Microsoft Corporation */,
			DVM                        = 0x2000 /* FAST Multimedia AG */
		};

		public ref class TMediaFormat abstract : ICloneable
		{
		public:
			STATIC_GUID(MEDIATYPE_Video);
			STATIC_GUID(MEDIATYPE_Audio);
			STATIC_GUID(MEDIATYPE_Text);
			STATIC_GUID(MEDIATYPE_File);
			
			STATIC_GUID(MEDIASUBTYPE_PCM);
			STATIC_GUID(MEDIASUBTYPE_WAVE);
			STATIC_GUID(MEDIASUBTYPE_Avi);
			STATIC_GUID(MEDIASUBTYPE_MPEG1Video);

			STATIC_GUID(FORMAT_None);
			STATIC_GUID(FORMAT_VideoInfo);
			STATIC_GUID(FORMAT_VideoInfo2);
			STATIC_GUID(FORMAT_WaveFormatEx);
			STATIC_GUID(FORMAT_MPEGVideo);
			STATIC_GUID(FORMAT_MPEG2Video);
		private:
			static Dictionary<Guid, RegisterMediaTypeDelegate^>^ _mediaTypes = gcnew Dictionary<Guid, RegisterMediaTypeDelegate^>();
		protected public:
			virtual void LoadStructure(int cbSize, void* ip) abstract = 0;
			virtual void* GetStructure() abstract = 0;
			virtual long GetStructureSize() abstract = 0;
			virtual void FreeStructure(void* p) abstract = 0;
			static TMediaFormat^ CreateMediaFormat(Guid guid, int cbSize, void* p);
		public:
			virtual Object^ Clone() abstract = 0;
			
			static void UnregisterMediaType(Guid guid)
			{
				Monitor::Enter(_mediaTypes);
				try
				{
					_mediaTypes->Remove(guid);
				}
				finally
				{
					Monitor::Exit(_mediaTypes);
				}
			}

			static void RegisterMediaType(Guid guid, RegisterMediaTypeDelegate^ del)
			{
				Monitor::Enter(_mediaTypes);
				try
				{
					_mediaTypes[guid] = del;
				}
				finally
				{
					Monitor::Exit(_mediaTypes);
				}
			}
		};

		public ref class TAudioFormat : TMediaFormat, ICloneable
		{
		private:
			long _fmt;
			long _channels;
			long _sps;
			long _abs;
			long _align;
			long _bps;
			array<byte>^ _extraData;

		protected public:
			virtual void LoadStructure(int cbSize, void* ip) override
			{
				if (cbSize < sizeof(WAVEFORMATEX))
					throw gcnew ArgumentException("Structure is not the expected size");

				WAVEFORMATEX* p = (WAVEFORMATEX*) ip;
				_fmt = p->wFormatTag;
				_channels = p->nChannels;
				_sps = p->nSamplesPerSec;
				_abs = p->nAvgBytesPerSec;
				_align = p->nBlockAlign;
				_bps = p->wBitsPerSample;
				if (p->cbSize > 0)
				{
					_extraData = gcnew array<byte>(p->cbSize);
					cli::interior_ptr<byte> pd = &(_extraData[0]);
					cli::interior_ptr<byte> pe = pd + p->cbSize;
					BYTE* pb = (BYTE*)p + sizeof(WAVEFORMATEX);
					while (pd < pe) {
						*pd = *pb;
						pb++; pd++;
					}
				}

			}
			virtual void FreeStructure(void* p) override { free(p); }
			virtual long GetStructureSize() override
			{
				int size = sizeof(WAVEFORMATEX);
				int extraInfo = (_extraData != nullptr) ? _extraData->Length : 0;
				return size + extraInfo;
			}
			virtual void* GetStructure() override
			{
				int size = sizeof(WAVEFORMATEX);
				int extraInfo = (_extraData != nullptr) ? _extraData->Length : 0;

				WAVEFORMATEX* p = (WAVEFORMATEX*) malloc(size + extraInfo);
				p->cbSize = (WORD) extraInfo;
				p->nAvgBytesPerSec = _abs;
				p->nBlockAlign = (WORD) _align;
				p->nChannels = (WORD) _channels;
				p->nSamplesPerSec = _sps;
				p->wBitsPerSample = (WORD) _bps;
				p->wFormatTag = (WORD) _fmt;

				if (extraInfo > 0)
				{
					cli::interior_ptr<byte> pb = &(_extraData[0]);
					cli::interior_ptr<byte> pe = pb + extraInfo;
					BYTE* pd = (BYTE*)p + sizeof(WAVEFORMATEX);
					while (pb < pe) {
						*pd = *pb;
						pb++; pd++;
					}
				}
				return p;
			}
		public:
			TAudioFormat() {/* */}
			TAudioFormat(long wavFormat, long channels, long samplesPerSecond, long avgBytesPerSecond, long blockAlign, long bitsPerSample)
				: _fmt(wavFormat), _channels(channels), _sps(samplesPerSecond), _abs(avgBytesPerSecond), _align(blockAlign), 
					_bps(bitsPerSample), _extraData(nullptr) {/* */}
			TAudioFormat(long wavFormat, long channels, long samplesPerSecond, long avgBytesPerSecond, long blockAlign, long bitsPerSample, array<byte>^ extraData)
				: _fmt(wavFormat), _channels(channels), _sps(samplesPerSecond), _abs(avgBytesPerSecond), _align(blockAlign), 
					_bps(bitsPerSample), _extraData(extraData) {/* */}

			virtual Object^ Clone() override
			{
				return gcnew TAudioFormat(_fmt, _channels, _sps, _abs, _align, _bps, (_extraData != nullptr) ? (array<byte>^)_extraData->Clone() : nullptr);
			}

			property long FormatTag
			{
				long get() { return _fmt; }
				void set(long value) { _fmt = value; }
			}
			property long Channels
			{
				long get() { return _channels; }
				void set(long value) { _channels = value; }
			}
			property long SamplesPerSec
			{
				long get() { return _sps; }
				void set(long value) { _sps = value; }
			}
			property long AvgBytesPerSec
			{
				long get() { return _abs; }
				void set(long value) { _abs = value; }
			}
			property long BlockAlign
			{
				long get() { return _align; }
				void set(long value) { _align = value; }
			}
			property long BitsPerSample
			{
				long get() { return _bps; }
				void set(long value) { _bps = value; }
			}
			property array<byte>^ FormatSpecificData
			{
				array<byte>^ get() { return (array<byte>^)_extraData->Clone(); }
				void set(array<byte>^ value) { _extraData = (array<byte>^)value->Clone(); }
			}
		};

		public ref class AM_MEDIA_TYPE : ICloneable
		{
		private:
			Guid _majorType;
			Guid _subType;
			bool _fixedSamples;
			bool _compression;
			long _sampleSize;
			Guid _formatType;
			TMediaFormat^ _media;
		protected public:
			AM_MEDIA_TYPE(Native::AM_MEDIA_TYPE* p);
			void Fill(Native::AM_MEDIA_TYPE& MediaType);
		public:
			AM_MEDIA_TYPE(Guid majorType, Guid subStype, bool fixedSamples, bool compression, long sampleSize, Guid formatType, TMediaFormat^ mediaFormat) :
				_majorType(majorType), _subType(subStype), _fixedSamples(fixedSamples), _compression(compression), _sampleSize(sampleSize),
				_formatType(formatType)
			{
				if (mediaFormat != nullptr)
					_media = (TMediaFormat^) mediaFormat->Clone();
				else
					_media = nullptr;
			}

			virtual Object^ Clone()
			{
				return gcnew AM_MEDIA_TYPE(_majorType, _subType, _fixedSamples, _compression, _sampleSize, _formatType, _media);
			}

			property Guid MajorType 
			{
				Guid get() { return _majorType; }
				void set(Guid guid)  { _majorType = guid; }
			}

			property Guid SubType 
			{
				Guid get() { return _subType; }
				void set(Guid guid)  { _subType = guid; }
			}

			property bool FixedSizedSamples 
			{
				bool get() { return _fixedSamples; }
				void set(bool b) { _fixedSamples = b; }
			}

			property bool TemporalCompression
			{
				bool get() { return _compression; }
				void set(bool value) { _compression = value; }
			}

			property long SampleSize
			{
				long get() { return _sampleSize; }
				void set(long value) { _sampleSize = value; }
			}

			property Guid FormatType 
			{
				Guid get() { return _formatType; }
				void set(Guid guid)  { _formatType = guid; }
			}

			property TMediaFormat^ MediaFormat
			{
				TMediaFormat^ get() { return (_media != nullptr) ? (TMediaFormat^)_media->Clone() : nullptr; }
				void set(TMediaFormat^ value)
				{
					if (value != nullptr)
						_media = (TMediaFormat^) value->Clone();
					else
						_media = nullptr;
				}
			}
		};

		public ref class TFileTrack : Internal::TapiBase
		{
		private:
			TTerminal^ _terminal;
			AM_MEDIA_TYPE^ _fmt;

		protected public:
			TFileTrack(IUnknown* piDispatch);
			CComPtr<Native::ITFileTrack> GetFileTrackItf() { return CastToInterface<Native::ITFileTrack,true>(); }
		public:
			~TFileTrack()
			{
				Release(false);
			}
			property TTerminal^ Terminal 
			{
				TTerminal^ get() { return _terminal; }
			}
			property AM_MEDIA_TYPE^ Format 
			{
				AM_MEDIA_TYPE^ get() { return (AM_MEDIA_TYPE^) _fmt->Clone(); }
				void set(AM_MEDIA_TYPE^ fmt) 
				{ 
					if (fmt == nullptr) 
						throw gcnew ArgumentNullException("fmt");
					_fmt = (AM_MEDIA_TYPE^)fmt->Clone(); 
					SetNewMediaFormat(); 
				}
			}
		private:
			void SetNewMediaFormat();
		};
	}
}