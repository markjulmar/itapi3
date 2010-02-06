// TapiBase.h
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
		namespace Internal
		{
			class ConversionFunctions
			{
			public:
				static System::Guid FromGUID(const GUID& guid) 
				{
					return Guid( guid.Data1, guid.Data2, guid.Data3, 
						guid.Data4[ 0 ], guid.Data4[ 1 ], 
						guid.Data4[ 2 ], guid.Data4[ 3 ], 
						guid.Data4[ 4 ], guid.Data4[ 5 ], 
						guid.Data4[ 6 ], guid.Data4[ 7 ] );
				}

				static GUID ToGUID(System::Guid% guid ) 
				{
					array<Byte>^ guidData = guid.ToByteArray();
					pin_ptr<Byte> data = &(guidData[ 0 ]);
					return *(_GUID *)data;
				}
			};

			public ref class TapiBase abstract
			{
			protected:
				IUnknown* _p;
				TapiBase(IUnknown* p) : _p(p) 
				{ 
					if (_p != NULL)
						_p->AddRef(); 
				}	
			public:
				~TapiBase() 
				{
					// The base class IDisposable does nothing.
					// Descendant classes expose an IDisposable _if_ it makes
					// sense - i.e. TAddress doesn't dispose of the ITAddress interface
					// until the library is shutdown because the library itself holds
					// references to that object.
				}
				Object^ QueryInterface(Type^ t)
				{
					return Marshal::GetTypedObjectForIUnknown(IntPtr(_p), t);
				}
			protected public:
				void ThrowNotValid() 
				{ 
					if (!IsValid())
					{
						TapiException::TraceOut(System::Diagnostics::TraceEventType::Warning, "{0} object accessed after disposable", this->GetType());
						throw gcnew ObjectDisposedException(String::Format("{0} has been disposed", this->GetType())); 
					}
				}
				
				bool IsValid() { return _p != NULL; }
				
				bool Compare(IUnknown* p)
				{
					if (_p == NULL || p == NULL) 
						return false;

					CComPtr<IUnknown> spunk1, spunk2;
					p->QueryInterface(IID_IUnknown, (void**)&spunk1);
					_p->QueryInterface(IID_IUnknown, (void**)&spunk2);
					return (spunk1 == spunk2);
				}
				
				virtual void Release(bool /*isFinalizer*/)
				{
					if (_p != NULL)
					{
						try { _p->Release(); } catch (...) {}
						_p = NULL;
					}
				}
			private:
				!TapiBase()
				{
					Release(true);
				}
			protected:
				template<class T, bool throwError>
				CComPtr<T> CastToInterface()
				{
					ThrowNotValid();

					CComPtr<T> p;
					HRESULT hr = _p->QueryInterface(__uuidof(p), (void**)&p);
					if (FAILED(hr))
					{
						TapiException::TraceOut(TraceEventType::Warning, 
							"Attempt to cast {0} object to {1} failed hr=0x{2:X}",
							this->GetType(), T::typeid, hr);
					}
					if (throwError)
						TapiException::ThrowExceptionForHR(hr);
					return p;
				}
			};
		}
	}
}
