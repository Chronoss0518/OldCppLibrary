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
typedef struct ChMainSound9
{
	LPDIRECTSOUNDBUFFER8 Sound;
	LPDIRECTSOUND3DBUFFER8 DSound;
	DWORD Hz;
	long Vol;

	ChMainSound9& operator = (const ChMainSound9& _cm)
	{
		*Sound = *_cm.Sound;
		*DSound = *_cm.DSound;
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	~ChMainSound9()
	{
		DWORD Flg;
		if (ChPtr::NullCheck(Sound) && ChPtr::NullCheck(DSound))return;
		Sound->GetStatus(&Flg);
		if ((Flg & DSBSTATUS_PLAYING) != 0)Sound->Stop();
		Sound->Release();
		DSound->Release();
	}

	///////////////////////////////////////////////////////////////////////////////////

}ChBGM9;

///////////////////////////////////////////////////////////////////////////////////

//SEクラス//
typedef struct ChSubSound9
{

	LPDIRECTSOUNDBUFFER8 Sound;
	LPDIRECTSOUND3DBUFFER8 DSound;
	DWORD Hz;
	long Vol;

	ChSubSound9& operator = (const ChSubSound9& _cm)
	{
		*Sound = *_cm.Sound;
		*DSound = *_cm.DSound;
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	~ChSubSound9()
	{
		DWORD Flg;
		if (ChPtr::NullCheck(Sound) && ChPtr::NullCheck(DSound))return;
		Sound->GetStatus(&Flg);
		if ((Flg & DSBSTATUS_PLAYING) != 0)Sound->Stop();
		Sound->Release();
		DSound->Release();
	}

	///////////////////////////////////////////////////////////////////////////////////

}ChSE9;

#endif