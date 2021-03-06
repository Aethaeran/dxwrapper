/**
* Copyright (C) 2018 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#include "d3d9.h"
#include "d3d9External.h"

#define INITUALIZE_WRAPPED_PROC(procName, unused) \
	FARPROC procName ## _out = (FARPROC)*(d3d9::procName);

namespace D3d9Wrapper
{
	VISIT_PROCS_D3D9(INITUALIZE_WRAPPED_PROC);
	FARPROC DebugSetMute_out = (FARPROC)*(ShardProcs::DebugSetMute);
}

void UpdateVSyncParameter(D3DPRESENT_PARAMETERS* params)
{
	if (Config.EnableVSync && params && params->PresentationInterval == D3DPRESENT_INTERVAL_IMMEDIATE)
	{
		params->PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	}
}

using namespace D3d9Wrapper;

HRESULT WINAPI d9_Direct3DShaderValidatorCreate9()
{
	if (!Wrapper::ValidProcAddress(Direct3DShaderValidatorCreate9_out))
	{
		return E_NOTIMPL;
	}
	return ((Direct3DShaderValidatorCreate9Proc)Direct3DShaderValidatorCreate9_out)();
}

HRESULT WINAPI d9_PSGPError()
{
	if (!Wrapper::ValidProcAddress(PSGPError_out))
	{
		return E_NOTIMPL;
	}
	return ((PSGPErrorProc)PSGPError_out)();
}

HRESULT WINAPI d9_PSGPSampleTexture()
{
	if (!Wrapper::ValidProcAddress(PSGPSampleTexture_out))
	{
		return E_NOTIMPL;
	}
	return ((PSGPSampleTextureProc)PSGPSampleTexture_out)();
}

int WINAPI d9_D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName)
{
	if (!Wrapper::ValidProcAddress(D3DPERF_BeginEvent_out))
	{
		return NULL;
	}
	return ((D3DPERF_BeginEventProc)D3DPERF_BeginEvent_out)(col, wszName);
}

int WINAPI d9_D3DPERF_EndEvent()
{
	if (!Wrapper::ValidProcAddress(D3DPERF_EndEvent_out))
	{
		return NULL;
	}
	return ((D3DPERF_EndEventProc)D3DPERF_EndEvent_out)();
}

DWORD WINAPI d9_D3DPERF_GetStatus()
{
	if (!Wrapper::ValidProcAddress(D3DPERF_GetStatus_out))
	{
		return NULL;
	}
	return ((D3DPERF_GetStatusProc)D3DPERF_GetStatus_out)();
}

BOOL WINAPI d9_D3DPERF_QueryRepeatFrame()
{
	if (!Wrapper::ValidProcAddress(D3DPERF_QueryRepeatFrame_out))
	{
		return false;
	}
	return ((D3DPERF_QueryRepeatFrameProc)D3DPERF_QueryRepeatFrame_out)();
}

void WINAPI d9_D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wszName)
{
	if (!Wrapper::ValidProcAddress(D3DPERF_SetMarker_out))
	{
		return;
	}
	return ((D3DPERF_SetMarkerProc)D3DPERF_SetMarker_out)(col, wszName);
}

void WINAPI d9_D3DPERF_SetOptions(DWORD dwOptions)
{
	if (!Wrapper::ValidProcAddress(D3DPERF_SetOptions_out))
	{
		return;
	}
	return ((D3DPERF_SetOptionsProc)D3DPERF_SetOptions_out)(dwOptions);
}

void WINAPI d9_D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wszName)
{
	if (!Wrapper::ValidProcAddress(D3DPERF_SetRegion_out))
	{
		return;
	}
	return ((D3DPERF_SetRegionProc)D3DPERF_SetRegion_out)(col, wszName);
}

HRESULT WINAPI d9_DebugSetLevel(DWORD dw1)
{
	if (!Wrapper::ValidProcAddress(DebugSetLevel_out))
	{
		return E_NOTIMPL;
	}
	return ((DebugSetLevelProc)DebugSetLevel_out)(dw1);
}

void WINAPI d9_DebugSetMute()
{
	if (!Wrapper::ValidProcAddress(DebugSetMute_out))
	{
		return;
	}
	return ((DebugSetMuteProc)DebugSetMute_out)();
}

void WINAPI d9_Direct3D9EnableMaximizedWindowedModeShim()
{
	if (!Wrapper::ValidProcAddress(Direct3D9EnableMaximizedWindowedModeShim_out))
	{
		return;
	}
	return ((Direct3D9EnableMaximizedWindowedModeShimProc)Direct3D9EnableMaximizedWindowedModeShim_out)();
}

IDirect3D9 *WINAPI d9_Direct3DCreate9(UINT SDKVersion)
{
	if (!Wrapper::ValidProcAddress(Direct3DCreate9_out))
	{
		return nullptr;
	}

	IDirect3D9 *pD3D9 = ((Direct3DCreate9Proc)Direct3DCreate9_out)(SDKVersion);

	if (pD3D9)
	{
		return new m_IDirect3D9(pD3D9);
	}

	return nullptr;
}

HRESULT WINAPI d9_Direct3DCreate9Ex(UINT SDKVersion, IDirect3D9Ex **ppD3D)
{
	if (!Wrapper::ValidProcAddress(Direct3DCreate9Ex_out))
	{
		return E_NOTIMPL;
	}

	HRESULT hr = ((Direct3DCreate9ExProc)Direct3DCreate9Ex_out)(SDKVersion, ppD3D);

	if (SUCCEEDED(hr) && ppD3D)
	{
		*ppD3D = new m_IDirect3D9Ex(*ppD3D);
	}

	return hr;
}
