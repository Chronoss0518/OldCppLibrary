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
class ChDirectSound9 
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	//InitAndRelease//

	void Init(
		HWND _hWnd);

	void Release();

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	//リスナーの位置情報更新用//
	void SetListenerPos(const ChVec3_9 *_Pos)
	{
		ListenerPos = (ChVec3_9*)_Pos;
	}

	//使用するディレクトリのパスをセット//
	void SetUseDirectory(
		const std::string _SoundDirectoryName
		, const std::string _UseSoundDirectory);

	//先に登録してあるDirectoryを利用してBGMをセット//
	void SetBGMSound(
		const std::string _SoundName
		, const std::string _SoundFilePath
		, const std::string _UseSoundDirectory);

	//先に登録してあるDirectoryを利用してSEをセット//
	ChStd::DataNo SetSESound(
		const std::string _SoundFilePath
		, const std::string _UseSoundDirectory);

	//セットされたBGMのHzを変更//
	inline void SetHzForBGM(const std::string _SoundName
		, const DWORD _Hz);

	//セットされたBGMのVolumeを変更//
	inline void SetVolumeForBGM(const std::string _SoundName
		, const long _Volume);

	//セットされたBGMのHzを読み込んだ際のサイズに戻す//
	inline void SetBaseHzForBGM(const std::string _SoundName);

	//セットされたBGMのVolumeを読み込んだ際のサイズに戻す//
	inline void SetBaseVolumeForBGM(const std::string _SoundName);

	//セットされたSEのHzを変更//
	inline void SetHzForSE(const ChStd::DataNo _SoundNo
		, const DWORD _Hz);

	//セットされたSEのVolumeを変更//
	inline void SetVolumeForSE(const ChStd::DataNo _SoundNo
		, const long _Volume);

	//セットされたSEのHzを読み込んだ際のサイズに戻す//
	inline void SetBaseHzForSE(const ChStd::DataNo _SoundNo);

	//セットされたSEのVolumeを読み込んだ際のサイズに戻す//
	inline void SetBaseVolumeForSE(const ChStd::DataNo _SoundNo);

	///////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	//止まっている一時使用のSEを解放//
	void Update();

	///////////////////////////////////////////////////////////////////////////////////

	//セットされたBGMをすべて解放//
	void ClearBGM();

	///////////////////////////////////////////////////////////////////////////////////

	//登録時に保持した数値でSEデータを解放する//
	void ClearSE(const ChStd::DataNo _SoundNo);

	///////////////////////////////////////////////////////////////////////////////////

	//セットされたBGMをすべて解放//
	void ClearSE();

	///////////////////////////////////////////////////////////////////////////////////

	//セットされたBGMを再生//
	void PlayBGM(const std::string _SoundName);

	///////////////////////////////////////////////////////////////////////////////////

	//登録時に保持した数値でSEを再生する//
	void PlaySE(const ChStd::DataNo _SoundNo);

	//直接SEを再生する(Updateメソッドを設置する必要がある)//
	void PlaySE(
		const std::string _SoundName
		, const std::string _UseSoundDirectory
		, const ChVec3_9* _SoundPos);

	///////////////////////////////////////////////////////////////////////////////////

	//現在再生しているBGMを止める//
	void StopBGM();

	///////////////////////////////////////////////////////////////////////////////////

	//登録時に保持した数値でSEを止める//
	void StopSE(const ChStd::DataNo _SoundNo);

	///////////////////////////////////////////////////////////////////////////////////

protected:

	//UserData//
	std::map<std::string, std::string> DirectoryPathList;
	
	LPDIRECTSOUND3DLISTENER8 lpSListener;//リスナー(聞く人)//
	LPDIRECTSOUNDBUFFER Primary;
	LPDIRECTSOUND8 LpDS;
	ChVec3_9* ListenerPos;
	const float ListenerBaseLen = 0.3f;

	const ChStd::DataNo MaxSE = 10000;

	ChStd::DataNo SENo = 1;
	
	std::map<std::string, ChPtr::Shared<ChMainSound9>>MainSoundList;
	std::map<ChStd::DataNo, ChPtr::Shared<ChSubSound9>>SubSoundList;

	std::vector<ChPtr::Shared<ChSubSound9>>PlaySubSoundList;

	std::string MainSoundName = "";

	///////////////////////////////////////////////////////////////////////////////////

	void CreatePrimaryBuffer(HWND _hWnd);

	///////////////////////////////////////////////////////////////////////////////////

	//音楽読み込み用関数//
	void LoadSound(
		LPDIRECTSOUNDBUFFER8 &_LpSound
		, LPDIRECTSOUND3DBUFFER8 &_Lp3DSound
		, std::string _SoundFileName);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChDirectSound9() {};

	~ChDirectSound9() { Release(); };

	private:

		ChStd::Bool InitFlg = false;

	public:

		inline ChStd::Bool IsInit() { return InitFlg; }

	static ChDirectSound9& GetIns()
	{
		static ChDirectSound9 Ins;
		return Ins;
	}

};

#define ChDSound9 ChDirectSound9::GetIns()

#endif