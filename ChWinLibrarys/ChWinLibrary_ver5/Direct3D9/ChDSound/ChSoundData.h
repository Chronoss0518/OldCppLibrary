#ifndef Ch_D3D9_SDDa_h
#define Ch_D3D9_SDDa_h


class CWaveSoundRead9
{
public:
	WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure//
	HMMIO         m_hmmioIn;     // MM I/O handle for the WAVE//
	MMCKINFO      m_ckIn;        // Multimedia RIFF chunk//
	MMCKINFO      m_ckInRiff;    // Use in opening a WAVE file//

	///////////////////////////////////////////////////////////////////////////////////

	HRESULT static ReadMMIO(
		HMMIO hmmioIn
		, MMCKINFO* pckInRIFF
		, WAVEFORMATEX** ppwfxInfo);

	///////////////////////////////////////////////////////////////////////////////////

	HRESULT static WaveOpenFile(
		const CHAR* strFileName
		, HMMIO* phmmioIn
		, WAVEFORMATEX** ppwfxInfo
		, MMCKINFO* pckInRIFF);

	///////////////////////////////////////////////////////////////////////////////////

	HRESULT static WaveStartDataRead(
		HMMIO* phmmioIn
		, MMCKINFO* pckIn
		, MMCKINFO* pckInRIFF);

	///////////////////////////////////////////////////////////////////////////////////

	HRESULT static WaveReadFile(
		HMMIO hmmioIn
		, UINT cbRead
		, BYTE* pbDest
		, MMCKINFO* pckIn, UINT* cbActualRead);

	///////////////////////////////////////////////////////////////////////////////////

public:
	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	CWaveSoundRead9();

	~CWaveSoundRead9();

	///////////////////////////////////////////////////////////////////////////////////

	HRESULT Open(const CHAR* strFilename);

	///////////////////////////////////////////////////////////////////////////////////

	HRESULT Reset();

	///////////////////////////////////////////////////////////////////////////////////

	HRESULT Read(UINT nSizeToRead, BYTE* pbData, UINT* pnSizeRead);

	///////////////////////////////////////////////////////////////////////////////////

	HRESULT Close();

};

//BGMクラス//
typedef struct ChMainSound9 : public ChCp::Releaser
{
	LPDIRECTSOUNDBUFFER8 sound;
	LPDIRECTSOUND3DBUFFER8 dSound;
	DWORD hz;
	long vol;

	ChMainSound9& operator = (const ChMainSound9& _cm)
	{
		*sound = *_cm.sound;
		*dSound = *_cm.dSound;
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//InitAndRelease//

	inline void Release()override
	{

		DWORD flg;
		if (ChPtr::NullCheck(sound) && ChPtr::NullCheck(dSound))return;
		sound->GetStatus(&flg);
		if ((flg & DSBSTATUS_PLAYING) != 0)sound->Stop();
		sound->Release();
		dSound->Release();
	}

	///////////////////////////////////////////////////////////////////////////////////

}ChBGM9;

///////////////////////////////////////////////////////////////////////////////////

//SEクラス//
typedef struct ChSubSound9:public ChCp::Releaser
{

	LPDIRECTSOUNDBUFFER8 sound;
	LPDIRECTSOUND3DBUFFER8 dSound;
	DWORD hz;
	long vol;

	ChSubSound9& operator = (const ChSubSound9& _cm)
	{
		*sound = *_cm.sound;
		*dSound = *_cm.dSound;
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//InitAndRelease//

	inline void Release()override
	{

		DWORD flg;
		if (ChPtr::NullCheck(sound) && ChPtr::NullCheck(dSound))return;
		sound->GetStatus(&flg);
		if ((flg & DSBSTATUS_PLAYING) != 0)sound->Stop();
		sound->Release();
		dSound->Release();
	}


	///////////////////////////////////////////////////////////////////////////////////

}ChSE9;

#endif