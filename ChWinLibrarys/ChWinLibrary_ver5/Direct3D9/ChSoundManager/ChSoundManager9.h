
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

	class SoundManager8:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		void Init(const HWND _hWin);

		inline void Release()override
		{
			if (ChPtr::NotNullCheck(soundDevice))
			{
				soundDevice->Release();
				soundDevice = nullptr;
			}
			SetInitFlg(false);
		}

	protected:

		WAVEFORMATEX SetWaveFormat();

		SoundManager8(){}


		LPDIRECTSOUND8 soundDevice = nullptr;
		LPDIRECTSOUNDBUFFER8 mainBuffer = nullptr;
		LPDIRECTSOUND3DLISTENER8 lpSListener = nullptr;//リスナー(聞く人)//

		std::map<std::string, ChPtr::Shared<BGM8>>musicList;

		std::map<std::string, ChPtr::Shared<SE8>>seList;



	};

}

#endif
