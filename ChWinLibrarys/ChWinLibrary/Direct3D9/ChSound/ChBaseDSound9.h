#ifndef Ch_D3D9_BSo_h
#define Ch_D3D9_BSo_h

namespace ChSound
{

	class BaseDSound8
	{
	public:

		void Play();

	protected:

		

	};


	typedef class BackGroundMusic8 :public BaseDSound8
	{
	public:

		LPDIRECTSOUNDBUFFER8 Sound;
		LPDIRECTSOUND3DBUFFER8 DSound;
		DWORD Hz;
		long Vol;

	protected:


	}BGM8;

	typedef class SoundEffect8 :public BaseDSound8
	{
	public:

		LPDIRECTSOUNDBUFFER8 Sound;
		LPDIRECTSOUND3DBUFFER8 DSound;
		DWORD Hz;
		long Vol;


	protected:
	}SE8;

}


#endif
