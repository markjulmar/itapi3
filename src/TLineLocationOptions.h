// TLineLocationOptions.h
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
		[Flags]
		public enum struct LINELOCATIONOPTIONS
		{
			None = 0,
			PulseDial = LINELOCATIONOPTION_PULSEDIAL
		};

		[Flags]
		public enum struct LINETRANSLATEOPTIONS
		{
			None = 0,
			CardOverride = LINETRANSLATEOPTION_CARDOVERRIDE,
			CancelCallWaiting = LINETRANSLATEOPTION_CANCELCALLWAITING,
			ForceLocal = LINETRANSLATEOPTION_FORCELOCAL,
			ForceLD = LINETRANSLATEOPTION_FORCELD
		};

		public ref class TLocationInfo sealed 
		{
		private:
			long _permLocId;
			long _countryCode;
			long _countryId;
			LINELOCATIONOPTIONS _options;
			long _preferredCardId;
			String^ _name;
			String^ _cityCode;
			String^ _localAccessCode;
			String^ _longDistAccessCode;
			String^ _tollPrefixList;
			String^ _cancelCallWaiting;
		protected public:
			TLocationInfo(Native::ITLocationInfo* pitf)
			{
				long lValue;
				if (SUCCEEDED(pitf->get_PermanentLocationID(&lValue)))
					_permLocId = lValue;
				if (SUCCEEDED(pitf->get_CountryCode(&lValue)))
					_countryCode = lValue;
				if (SUCCEEDED(pitf->get_CountryID(&lValue)))
					_countryId = lValue;
				if (SUCCEEDED(pitf->get_Options(&lValue)))
					_options = (LINELOCATIONOPTIONS) lValue;
				if (SUCCEEDED(pitf->get_PreferredCardID(&lValue)))
					_preferredCardId = lValue;
				CComBSTR bstrValue;
				if (SUCCEEDED(pitf->get_LocationName(&bstrValue)))
					_name = gcnew String((wchar_t*)bstrValue);
				else
					_name = String::Empty;
				bstrValue.Empty();
				if (SUCCEEDED(pitf->get_CityCode(&bstrValue)))
					_cityCode = gcnew String((wchar_t*)bstrValue);
				else
					_cityCode = String::Empty;
				bstrValue.Empty();
				if (SUCCEEDED(pitf->get_LongDistanceAccessCode(&bstrValue)))
					_longDistAccessCode = gcnew String((wchar_t*)bstrValue);
				else
					_longDistAccessCode = String::Empty;
				bstrValue.Empty();
				if (SUCCEEDED(pitf->get_LocalAccessCode(&bstrValue)))
					_localAccessCode = gcnew String((wchar_t*)bstrValue);
				else
					_localAccessCode = String::Empty;
				bstrValue.Empty();
				if (SUCCEEDED(pitf->get_TollPrefixList(&bstrValue)))
					_tollPrefixList = gcnew String((wchar_t*)bstrValue);
				else
					_tollPrefixList = String::Empty;
				bstrValue.Empty();
				if (SUCCEEDED(pitf->get_CancelCallWaitingCode(&bstrValue)))
					_cancelCallWaiting = gcnew String((wchar_t*)bstrValue);
				else
					_cancelCallWaiting = String::Empty;
				bstrValue.Empty();
			}
		public:
			property long PermanentLocationID
			{
				long get() { return _permLocId; }
			}
			property long CountryCode
			{
				long get() { return _countryCode; }
			}
			property long CountryID
			{
				long get() { return _countryId; }
			}
			property LINELOCATIONOPTIONS Options
			{
				LINELOCATIONOPTIONS get() { return _options; }
			}
			property long PreferredCardID
			{
				long get() { return _preferredCardId; }
			}
			property String^ LocationName
			{
				String^ get() { return _name; }
			}
			property String^ CityCode
			{
				String^ get() { return _cityCode; }
			}
			property String^ LocalAccessCode
			{
				String^ get() { return _localAccessCode; }
			}
			property String^ LongDistanceAccessCode
			{
				String^ get() { return _longDistAccessCode; }
			}
			property String^ TollPrefixList
			{
				String^ get() { return _tollPrefixList; }
			}
			property String^ CancelCallWaitingCode
			{
				String^ get() { return _cancelCallWaiting; }
			}
		};

		public ref class TCallingCard sealed 
		{
		private:
			long _permCardId;
			long _digitCount;
			LINETRANSLATEOPTIONS _options;
			String^ _name;
			String^ _sameAreaRule;
			String^ _ldRule;
			String^ _intlRule;
		protected public:
			TCallingCard(Native::ITCallingCard* pitf)
			{
				long lValue;
				if (SUCCEEDED(pitf->get_PermanentCardID(&lValue)))
					_permCardId = lValue;
				if (SUCCEEDED(pitf->get_NumberOfDigits(&lValue)))
					_digitCount = lValue;
				if (SUCCEEDED(pitf->get_Options(&lValue)))
					_options = (LINETRANSLATEOPTIONS) lValue;
				CComBSTR bstrValue;
				if (SUCCEEDED(pitf->get_CardName(&bstrValue)))
					_name = gcnew String((wchar_t*)bstrValue);
				else
					_name = String::Empty;
				bstrValue.Empty();
				if (SUCCEEDED(pitf->get_SameAreaDialingRule(&bstrValue)))
					_sameAreaRule = gcnew String((wchar_t*)bstrValue);
				else
					_sameAreaRule = String::Empty;
				bstrValue.Empty();
				if (SUCCEEDED(pitf->get_LongDistanceDialingRule(&bstrValue)))
					_ldRule = gcnew String((wchar_t*)bstrValue);
				else
					_ldRule = String::Empty;
				bstrValue.Empty();
				if (SUCCEEDED(pitf->get_InternationalDialingRule(&bstrValue)))
					_intlRule = gcnew String((wchar_t*)bstrValue);
				else
					_intlRule = String::Empty;
				bstrValue.Empty();
			}
		public:
			property long PermanentCardID
			{
				long get() {return _permCardId;}
			}
			property long NumberOfDigits
			{
				long get() {return _digitCount;}
			}
			property LINETRANSLATEOPTIONS Options
			{
				LINETRANSLATEOPTIONS get() {return _options;}
			}
			property String^ CardName
			{
				String^ get() {return _name;}
			}
			property String^ SameAreaDialingRule
			{
				String^ get() {return _sameAreaRule;}
			}
			property String^ LongDistanceDialingRule
			{
				String^ get() {return _ldRule;}
			}
			property String^ InternationalDialingRulee
			{
				String^ get() {return _intlRule;}
			}
		};
	}
}

