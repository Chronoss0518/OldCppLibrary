#ifndef Ch_D3D9_DiSo_h
#define Ch_D3D9_DiSo_h

struct ChMainSound9;
struct ChSubSound9;

//���󂯎�蕨//-----------------------------------------------------------------------------
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

//(���ǕK)//
//�匳�̃T�E���h�̖��O�Ƃ͕ʂɃX�g�b�v�p��No�������Ă���//
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

	//���X�i�[�̈ʒu���X�V�p//
	void SetListenerPos(const ChVec3_9 *_Pos)
	{
		ListenerPos = (ChVec3_9*)_Pos;
	}

	//�g�p����f�B���N�g���̃p�X���Z�b�g//
	void SetUseDirectory(
		const std::string _SoundDirectoryName
		, const std::string _UseSoundDirectory);

	//��ɓo�^���Ă���Directory�𗘗p����BGM���Z�b�g//
	void SetBGMSound(
		const std::string _SoundName
		, const std::string _SoundFilePath
		, const std::string _UseSoundDirectory);

	//��ɓo�^���Ă���Directory�𗘗p����SE���Z�b�g//
	ChStd::DataNo SetSESound(
		const std::string _SoundFilePath
		, const std::string _UseSoundDirectory);

	//�Z�b�g���ꂽBGM��Hz��ύX//
	inline void SetHzForBGM(const std::string _SoundName
		, const DWORD _Hz);

	//�Z�b�g���ꂽBGM��Volume��ύX//
	inline void SetVolumeForBGM(const std::string _SoundName
		, const long _Volume);

	//�Z�b�g���ꂽBGM��Hz��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	inline void SetBaseHzForBGM(const std::string _SoundName);

	//�Z�b�g���ꂽBGM��Volume��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	inline void SetBaseVolumeForBGM(const std::string _SoundName);

	//�Z�b�g���ꂽSE��Hz��ύX//
	inline void SetHzForSE(const ChStd::DataNo _SoundNo
		, const DWORD _Hz);

	//�Z�b�g���ꂽSE��Volume��ύX//
	inline void SetVolumeForSE(const ChStd::DataNo _SoundNo
		, const long _Volume);

	//�Z�b�g���ꂽSE��Hz��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	inline void SetBaseHzForSE(const ChStd::DataNo _SoundNo);

	//�Z�b�g���ꂽSE��Volume��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	inline void SetBaseVolumeForSE(const ChStd::DataNo _SoundNo);

	///////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	//�~�܂��Ă���ꎞ�g�p��SE�����//
	void Update();

	///////////////////////////////////////////////////////////////////////////////////

	//�Z�b�g���ꂽBGM�����ׂĉ��//
	void ClearBGM();

	///////////////////////////////////////////////////////////////////////////////////

	//�o�^���ɕێ��������l��SE�f�[�^���������//
	void ClearSE(const ChStd::DataNo _SoundNo);

	///////////////////////////////////////////////////////////////////////////////////

	//�Z�b�g���ꂽBGM�����ׂĉ��//
	void ClearSE();

	///////////////////////////////////////////////////////////////////////////////////

	//�Z�b�g���ꂽBGM���Đ�//
	void PlayBGM(const std::string _SoundName);

	///////////////////////////////////////////////////////////////////////////////////

	//�o�^���ɕێ��������l��SE���Đ�����//
	void PlaySE(const ChStd::DataNo _SoundNo);

	//����SE���Đ�����(Update���\�b�h��ݒu����K�v������)//
	void PlaySE(
		const std::string _SoundName
		, const std::string _UseSoundDirectory
		, const ChVec3_9* _SoundPos);

	///////////////////////////////////////////////////////////////////////////////////

	//���ݍĐ����Ă���BGM���~�߂�//
	void StopBGM();

	///////////////////////////////////////////////////////////////////////////////////

	//�o�^���ɕێ��������l��SE���~�߂�//
	void StopSE(const ChStd::DataNo _SoundNo);

	///////////////////////////////////////////////////////////////////////////////////

protected:

	//UserData//
	std::map<std::string, std::string> DirectoryPathList;
	
	LPDIRECTSOUND3DLISTENER8 lpSListener;//���X�i�[(�����l)//
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

	//���y�ǂݍ��ݗp�֐�//
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