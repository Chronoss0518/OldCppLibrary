#ifndef Ch_D3D9_DiSo_h
#define Ch_D3D9_DiSo_h

struct ChMainSound9;
struct ChSubSound9;

//※受け取り物//-----------------------------------------------------------------------------
// File: WavRead.h
//
// Desc: Support for loading and playing Wave files using DirectSound sound
//       buffers.
//
// Copyright (c) 1999 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Name: class CWaveSoundRead
// Desc: A class to read in sound data from a Wave file
//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////

//(改良必)//
//大元のサウンドの名前とは別にストップ用のNoを持っておく//
class ChDirectSound9 :public ChCp::Initializer,public ChCp::Releaser
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	//InitAndRelease//

	void Init(
		HWND _hWnd);

	void Release()override;

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	//リスナーの位置情報更新用//
	void SetListenerPos(const ChVec3_9 *_pos)
	{
		listenerPos = (ChVec3_9*)_pos;
	}

	//使用するディレクトリのパスをセット//
	void SetUseDirectory(
		const std::string _soundDirectoryName
		, const std::string _useSoundDirectory);

	//先に登録してあるDirectoryを利用してBGMをセット//
	void SetBGMSound(
		const std::string _soundName
		, const std::string _soundFilePath
		, const std::string _useSoundDirectory);

	//先に登録してあるDirectoryを利用してSEをセット//
	ChStd::DataNo SetSESound(
		const std::string _soundFilePath
		, const std::string _useSoundDirectory);

	//セットされたBGMのHzを変更//
	inline void SetHzForBGM(const std::string _soundName
		, const DWORD _hz);

	//セットされたBGMのVolumeを変更//
	inline void SetVolumeForBGM(const std::string _soundName
		, const long _volume);

	//セットされたBGMのHzを読み込んだ際のサイズに戻す//
	inline void SetBaseHzForBGM(const std::string _soundName);

	//セットされたBGMのVolumeを読み込んだ際のサイズに戻す//
	inline void SetBaseVolumeForBGM(const std::string _soundName);

	//セットされたSEのHzを変更//
	inline void SetHzForSE(const ChStd::DataNo _soundNo
		, const DWORD _hz);

	//セットされたSEのVolumeを変更//
	inline void SetVolumeForSE(const ChStd::DataNo _soundNo
		, const long _volume);

	//セットされたSEのHzを読み込んだ際のサイズに戻す//
	inline void SetBaseHzForSE(const ChStd::DataNo _soundNo);

	//セットされたSEのVolumeを読み込んだ際のサイズに戻す//
	inline void SetBaseVolumeForSE(const ChStd::DataNo _soundNo);

	///////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	//止まっている一時使用のSEを解放//
	void Update();

	///////////////////////////////////////////////////////////////////////////////////

	//セットされたBGMをすべて解放//
	void ClearBGM();

	///////////////////////////////////////////////////////////////////////////////////

	//登録時に保持した数値でSEデータを解放する//
	void ClearSE(const ChStd::DataNo _soundNo);

	///////////////////////////////////////////////////////////////////////////////////

	//セットされたBGMをすべて解放//
	void ClearSE();

	///////////////////////////////////////////////////////////////////////////////////

	//セットされたBGMを再生//
	void PlayBGM(const std::string _soundName);

	///////////////////////////////////////////////////////////////////////////////////

	//登録時に保持した数値でSEを再生する//
	void PlaySE(const ChStd::DataNo _soundNo);

	//直接SEを再生する(Updateメソッドを設置する必要がある)//
	void PlaySE(
		const std::string _soundName
		, const std::string _useSoundDirectory
		, const ChVec3_9* _soundPos);

	///////////////////////////////////////////////////////////////////////////////////

	//現在再生しているBGMを止める//
	void StopBGM();

	///////////////////////////////////////////////////////////////////////////////////

	//登録時に保持した数値でSEを止める//
	void StopSE(const ChStd::DataNo _soundNo);

	///////////////////////////////////////////////////////////////////////////////////

protected:

	//UserData//
	std::map<std::string, std::string> directoryPathList;
	
	LPDIRECTSOUND3DLISTENER8 lpSListener;//リスナー(聞く人)//
	LPDIRECTSOUNDBUFFER primary;
	LPDIRECTSOUND8 lpDS;
	ChVec3_9* listenerPos;
	const float listenerBaseLen = 0.3f;

	const ChStd::DataNo maxSE = 10000;

	ChStd::DataNo seNo = 1;
	
	std::map<std::string, ChPtr::Shared<ChMainSound9>>mainSoundList;
	std::map<ChStd::DataNo, ChPtr::Shared<ChSubSound9>>subSoundList;

	std::vector<ChPtr::Shared<ChSubSound9>>playSubSoundList;

	std::string mainSoundName = "";

	///////////////////////////////////////////////////////////////////////////////////

	void CreatePrimaryBuffer(HWND _hWnd);

	///////////////////////////////////////////////////////////////////////////////////

	//音楽読み込み用関数//
	void LoadSound(
		LPDIRECTSOUNDBUFFER8 &_lpSound
		, LPDIRECTSOUND3DBUFFER8 &_lp3DSound
		, std::string _soundFileName);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChDirectSound9() {};

	~ChDirectSound9() { Release(); };

	public:

	static ChDirectSound9& GetIns()
	{
		static ChDirectSound9 ins;
		return ins;
	}

};

#define ChDSound9 ChDirectSound9::GetIns()

#endif