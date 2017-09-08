// TAddressTranslationInfo.h
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
		public enum struct LINETRANSLATERESULTS
		{
			Canonical = LINETRANSLATERESULT_CANONICAL,     
			International = LINETRANSLATERESULT_INTERNATIONAL, 
			LongDistance = LINETRANSLATERESULT_LONGDISTANCE,  
			Local = LINETRANSLATERESULT_LOCAL,         
			InTollList = LINETRANSLATERESULT_INTOLLLIST,    
			NotInTollList = LINETRANSLATERESULT_NOTINTOLLLIST, 
			DialBilling = LINETRANSLATERESULT_DIALBILLING,   
			DialQuiet = LINETRANSLATERESULT_DIALQUIET,     
			DialDialTone = LINETRANSLATERESULT_DIALDIALTONE,  
			DialPrompt = LINETRANSLATERESULT_DIALPROMPT,    
			VoiceDetect = LINETRANSLATERESULT_VOICEDETECT,   
			NoTranslation = LINETRANSLATERESULT_NOTRANSLATION 
		};

		public ref class TAddressTranslationInfo sealed
		{
		private:
			String^ _dialString;
			String^ _displayString;
			long _countryCode;
			long _destCountryCode;
			long _result;

		protected public:
			TAddressTranslationInfo(Native::ITAddressTranslationInfo* pItf)
			{
				CComBSTR bstrValue;
				if (SUCCEEDED(pItf->get_DialableString(&bstrValue)))
					_dialString = gcnew String((wchar_t*)bstrValue);
				else
					_dialString = String::Empty;
				bstrValue.Empty();
				if (SUCCEEDED(pItf->get_DisplayableString(&bstrValue)))
					_displayString = gcnew String((wchar_t*)bstrValue);
				else
					_displayString = String::Empty;
				long lValue;
				if (SUCCEEDED(pItf->get_CurrentCountryCode(&lValue)))
					_countryCode = lValue;
				if (SUCCEEDED(pItf->get_DestinationCountryCode(&lValue)))
					_destCountryCode = lValue;
				if (SUCCEEDED(pItf->get_TranslationResults(&lValue)))
					_result = lValue;
			}
		public:
			property String^ DialableString
			{
				String^ get() { return _dialString; }
			}
			property String^ DisplayableString
			{
				String^ get() { return _displayString; }
			}
			property long CurrentCountryCode
			{
				long get() { return _countryCode; }
			}
			property long DestinationCountryCode
			{
				long get() { return _destCountryCode; }
			}
			property LINETRANSLATERESULTS TranslationResults
			{
				LINETRANSLATERESULTS get() { return (LINETRANSLATERESULTS) _result; }
			}
		};
	}
}