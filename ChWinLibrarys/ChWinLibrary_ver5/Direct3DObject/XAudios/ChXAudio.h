#ifndef Ch_CPP_D3DOBJ_XAudio2_h
#define Ch_CPP_D3DOBJ_XAudio2_h

namespace ChD3D
{
	class XAudio2Manager;


	class AudioObject :public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetLoopFlg(const ChStd::Bool _Flg) { loopFlg = _Flg; }

		void SetLoopStartPos(const unsigned long _pos) { loopStartPos = _pos; }

		void SetLoopEndPos(const unsigned long _pos) { loopEndPos = _pos; }

		void SetPlayTime(const unsigned long _Time) { nowPos = _Time; }

		void SetVolume(const float _Volume);



		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		unsigned long GetLoopStartPos() { return loopStartPos; }

		unsigned long GetLoopEndPos() { return loopEndPos; }

		unsigned long GetPlayTime() { return nowPos; }

		float GetVolume();

		///////////////////////////////////////////////////////////////////////////////////

		void Play();

		///////////////////////////////////////////////////////////////////////////////////

		void Pause();

		///////////////////////////////////////////////////////////////////////////////////

		void Stop();

		///////////////////////////////////////////////////////////////////////////////////

		friend XAudio2Manager;
	private:

		IXAudio2SourceVoice* voice = nullptr;
		std::string fileName = "";
		ChStd::Bool loopFlg = false;
		unsigned long nowPos = 1;
		unsigned long loopStartPos = 0;
		unsigned long loopEndPos = -1;

	};


	class X3DAudioObject :public AudioObject
	{

	public :

		friend XAudio2Manager;

	private:

		ChVec3 pos;

	};

	struct ChXAUDIO2_BUFFER :public XAUDIO2_BUFFER
	{

		std::vector<unsigned char> audioDataVector;
	};

	class XAudio2Manager:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPos(const ChVec3& _pos)
		{
			pos = _pos;
		}

		inline void SetDir(const ChVec3& _dir)
		{
			dir = _dir;
		}

		///////////////////////////////////////////////////////////////////////////////////

		void CreateSound(AudioObject* _object,const std::string& _str);

		///////////////////////////////////////////////////////////////////////////////////

		void Update();

		///////////////////////////////////////////////////////////////////////////////////

		friend AudioObject;
		friend X3DAudioObject;

	private:

		XAudio2Manager(){}
		
		std::map<std::string, std::vector<XAUDIO2_BUFFER*>>audioDatas;

		std::vector<AudioObject*>audios;
		IXAudio2* audio = nullptr;
		IXAudio2MasteringVoice* audioMV = nullptr;

		ChVec3 pos;
		ChVec3 dir;

	public:

		static XAudio2Manager& GetIns()
		{
			static XAudio2Manager ins;
			return ins;
		}

	};

	static std::function<XAudio2Manager& ()>XAudioManager = XAudio2Manager::GetIns;


}

#endif