#pragma once
/*Forward declaration*/
class IAudioSessionManager2;
class IAudioSessionEnumerator;
class IAudioSessionControl;
/*//*/

namespace olib {
	class oaudio {
	private:
		IAudioSessionManager2* p_session = 0;
		IAudioSessionEnumerator* p_sessionenum = 0;
		IAudioSessionControl* p_sessioncontrol = 0;
	public:
		/*
		How many active sessions there are.
		*/
		int count();
	private:
		long enumerate_audio_session(int idx);
		long create_session_manager(IAudioSessionManager2** ppSessionManager);
	};
}