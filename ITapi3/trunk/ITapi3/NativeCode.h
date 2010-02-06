// NativeCode.h
//
// This file contains the native classes which are used to interact with the COM
// TAPI3 infrastructure.
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

// Declare global events
delegate void TapiEventHandlerDelegate(TAPI_EVENT te, IDispatch* pEvent);

////////////////////////////////////////////////////////////////////////////
// TapiEventHandler - This class is used to forward TAPI events to a 
// known destination in the managed world; very simple COM object implementation
class TapiEventHandler : ITTAPIEventNotification
{
private:
	gcroot<TapiEventHandlerDelegate^> _cb;
	long _refCount;

public:
	TapiEventHandler(TapiEventHandlerDelegate^ cb) : _cb(cb), _refCount(1) {/* */}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject)
	{
		if (riid == IID_IUnknown || riid == IID_ITTAPIEventNotification)
		{
			*ppvObject = static_cast<IUnknown*>(this);
		}
		else
		{
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}
		static_cast<IUnknown*>(*ppvObject)->AddRef();
		return S_OK;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef() 
	{ 
		return InterlockedIncrement(&_refCount); 
	}
	
	virtual ULONG STDMETHODCALLTYPE Release() 
	{ 
		long currCount = InterlockedDecrement(&_refCount);
		if (currCount == 0) 
		{
			delete this;
			return 0;
		}
		return currCount;
	}

	virtual HRESULT STDMETHODCALLTYPE Event(TAPI_EVENT TapiEvent, IDispatch *pEvent)
	{
		try 
		{
			_cb->Invoke(TapiEvent, pEvent);
		}
		catch (...)
		{
		}
		return S_OK;
	}
};
