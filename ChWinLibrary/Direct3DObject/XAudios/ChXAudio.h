#ifndef Ch_CPP_D3DOBJ_XAudio2_h
#define Ch_CPP_D3DOBJ_XAudio2_h

namespace ChD3D
{
	class XAudio2Manager;


	class AudioObject :public ChCpp::ChCp::Initializer,public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetLoopFlg(const ChStd::Bool _Flg) { LoopFlg = _Flg; }

		void SetLoopStartPos(const unsigned long _Pos) { LoopStartPos = _Pos; }

		void SetLoopEndPos(const unsigned long _Pos) { LoopEndPos = _Pos; }

		void SetPlayTime(const unsigned long _Time) { NowPos = _Time; }

		void SetVolume(const float _Volume);



		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		unsigned long GetLoopStartPos() { return LoopStartPos; }

		unsigned long GetLoopEndPos() { return LoopEndPos; }

		unsigned long GetPlayTime() { return NowPos; }

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

		IXAudio2SourceVoice* Voice = nullptr;
		std::string FileName = "";
		ChStd::Bool LoopFlg = false;
		unsigned long NowPos = 1;
		unsigned long LoopStartPos = 0;
		unsigned long LoopEndPos = -1;

	};


	class X3DAudioObject :public AudioObject
	{

	public :



		friend XAudio2Manager;

	private:

		ChVec3 Pos;

	};

	struct ChXAUDIO2_BUFFER :public XAUDIO2_BUFFER
	{

		std::vector<unsigned char> AudioDataVector;
	};

	class XAudio2Manager:public ChCpp::ChCp::Initializer,public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPos(const ChVec3& _Pos)
		{
			Pos = _Pos;
		}

		inline void SetDir(const ChVec3& _Dir)
		{
			Dir = _Dir;
		}

		///////////////////////////////////////////////////////////////////////////////////

		void CreateSound(AudioObject* _Object,const std::string& _Str);

		///////////////////////////////////////////////////////////////////////////////////

		void Update();

		///////////////////////////////////////////////////////////////////////////////////

		friend AudioObject;
		friend X3DAudioObject;

	private:

		XAudio2Manager(){}
		
		std::map<std::string, std::vector<XAUDIO2_BUFFER*>>AudioDatas;

		std::vector<AudioObject*>Audios;
		IXAudio2* audio = nullptr;
		IXAudio2MasteringVoice* audioMV = nullptr;

		ChVec3 Pos;
		ChVec3 Dir;

	public:

		static XAudio2Manager& GetIns()
		{
			static XAudio2Manager Ins;
			return Ins;
		}

	};

	static std::function<XAudio2Manager& ()>XAudioManager = XAudio2Manager::GetIns;


}

#endif