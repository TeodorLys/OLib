#include "oaudio.h"
#include <audiopolicy.h>
#include <mmdeviceapi.h>
#include <stdio.h>

namespace olib {

#define SAFE_RELEASE(punk)  \
              if ((punk) != nullptr)  \
                { (punk)->Release(); (punk) = nullptr; }

	int oaudio::count() {
		int c = 0;
		IAudioSessionEnumerator* pEnum = 0;
		IAudioSessionManager2* pSez = 0;
		create_session_manager(&pSez);
		pSez->GetSessionEnumerator(&pEnum);

		pEnum->GetCount(&c);

		SAFE_RELEASE(pEnum);
		SAFE_RELEASE(pSez);
		CoUninitialize();
		return c;
	}

	/*
	PRIVATE
	*/
	long oaudio::enumerate_audio_session(int idx) {
		HRESULT hr = 0;
		ISimpleAudioVolume *controller;
		if (p_sessionenum == nullptr) {
			create_session_manager(&p_session);
			p_session->GetSessionEnumerator(&p_sessionenum);
		}
		hr = p_sessionenum->GetSession(idx, &p_sessioncontrol);
		/*
		TODO: Free some stuff?
		*/
		if (hr != S_OK) {
			return hr;
		}
		hr = p_sessioncontrol->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&controller);
		if (hr != S_OK) {
			return hr;
		}
		SAFE_RELEASE(p_session);
		SAFE_RELEASE(p_sessionenum);
	}

	long oaudio::create_session_manager(IAudioSessionManager2** ppSessionManager) {
		HRESULT hr = S_OK;

		IMMDevice* pDevice = NULL;
		IMMDeviceEnumerator* pEnumerator = NULL;
		IAudioSessionManager2* pSessionManager = NULL;
		hr = CoInitialize(pEnumerator);
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);

		if (hr != S_OK) {
			SAFE_RELEASE(pDevice);
			SAFE_RELEASE(pEnumerator);
			SAFE_RELEASE(pSessionManager);
			return hr;
		}

		hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
		if (hr != S_OK) {
			SAFE_RELEASE(pDevice);
			SAFE_RELEASE(pEnumerator);
			SAFE_RELEASE(pSessionManager);
			return hr;
		}
		hr = pDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&pSessionManager);
		if (hr != S_OK) {
			SAFE_RELEASE(pDevice);
			SAFE_RELEASE(pEnumerator);
			SAFE_RELEASE(pSessionManager);
			return hr;
		}

		*(ppSessionManager) = pSessionManager;
		(*ppSessionManager)->AddRef();

		SAFE_RELEASE(pDevice);
		SAFE_RELEASE(pEnumerator);
		SAFE_RELEASE(pSessionManager);
		return hr;
	}
	/*//*/
}