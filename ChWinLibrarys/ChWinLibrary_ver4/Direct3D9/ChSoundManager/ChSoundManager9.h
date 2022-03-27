
#ifndef Ch_D3D9_SoMa_h
#define Ch_D3D9_SoMa_h

#ifdef _WINDOWS_


namespace ChSystem
{
	class Windows;
}

#endif //_WINDOWS_

namespace ChSound
{

	typedef class BackGroundMusic8 BGM8;
	typedef class SoundEffect8 SE8;

	class SoundManager8:public ChCpp::ChCp::Initializer
	{
	public:

		void Init(const HWND _hWin);

		void Release()
		{
			SetInitFlg(false);
		}

	protected:

		WAVEFORMATEX SetWaveFormat();

		SoundManager8(){}

		~SoundManager8()
		{
			SoundDevice->Release();
			SoundDevice = nullptr;
		}

		LPDIRECTSOUND8 SoundDevice = nullptr;
		LPDIRECTSOUNDBUFFER8 MainBuffer = nullptr;
		LPDIRECTSOUND3DLISTENER8 lpSListener = nullptr;//リスナー(聞く人)//

		std::map<std::string, ChPtr::Shared<BGM8>>MusicList;

		std::map<std::string, ChPtr::Shared<SE8>>SEList;



	};

}

#endif
