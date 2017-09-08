// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#define _WIN32_DCOM
#include <windows.h>
#include <atlbase.h>
#include <atlsafe.h>
#include <vcclr.h>
#include <control.h>
#include <uuids.h>

namespace JulMar {
	namespace Tapi3 {
		namespace Native {
#include <tapi3.h>
#include <Tapi3Err.h>
#include "NativeCode.h"
		}}}

