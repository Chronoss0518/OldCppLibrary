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

		LPDIRECTSOUNDBUFFER8 sound;
		LPDIRECTSOUND3DBUFFER8 dSound;
		DWORD hz;
		long vol;

	protected:


	}BGM8;

	typedef class SoundEffect8 :public BaseDSound8
	{
	public:

		LPDIRECTSOUNDBUFFER8 sound;
		LPDIRECTSOUND3DBUFFER8 dSound;
		DWORD hz;
		long vol;


	protected:
	}SE8;

}


#endif
