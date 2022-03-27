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

	//���X�i�[�̈ʒu���X�V�p//
	void SetListenerPos(const ChVec3_9 *_pos)
	{
		listenerPos = (ChVec3_9*)_pos;
	}

	//�g�p����f�B���N�g���̃p�X���Z�b�g//
	void SetUseDirectory(
		const std::string _soundDirectoryName
		, const std::string _useSoundDirectory);

	//��ɓo�^���Ă���Directory�𗘗p����BGM���Z�b�g//
	void SetBGMSound(
		const std::string _soundName
		, const std::string _soundFilePath
		, const std::string _useSoundDirectory);

	//��ɓo�^���Ă���Directory�𗘗p����SE���Z�b�g//
	ChStd::DataNo SetSESound(
		const std::string _soundFilePath
		, const std::string _useSoundDirectory);

	//�Z�b�g���ꂽBGM��Hz��ύX//
	inline void SetHzForBGM(const std::string _soundName
		, const DWORD _hz);

	//�Z�b�g���ꂽBGM��Volume��ύX//
	inline void SetVolumeForBGM(const std::string _soundName
		, const long _volume);

	//�Z�b�g���ꂽBGM��Hz��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	inline void SetBaseHzForBGM(const std::string _soundName);

	//�Z�b�g���ꂽBGM��Volume��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	inline void SetBaseVolumeForBGM(const std::string _soundName);

	//�Z�b�g���ꂽSE��Hz��ύX//
	inline void SetHzForSE(const ChStd::DataNo _soundNo
		, const DWORD _hz);

	//�Z�b�g���ꂽSE��Volume��ύX//
	inline void SetVolumeForSE(const ChStd::DataNo _soundNo
		, const long _volume);

	//�Z�b�g���ꂽSE��Hz��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	inline void SetBaseHzForSE(const ChStd::DataNo _soundNo);

	//�Z�b�g���ꂽSE��Volume��ǂݍ��񂾍ۂ̃T�C�Y�ɖ߂�//
	inline void SetBaseVolumeForSE(const ChStd::DataNo _soundNo);

	///////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	//�~�܂��Ă���ꎞ�g�p��SE�����//
	void Update();

	///////////////////////////////////////////////////////////////////////////////////

	//�Z�b�g���ꂽBGM�����ׂĉ��//
	void ClearBGM();

	///////////////////////////////////////////////////////////////////////////////////

	//�o�^���ɕێ��������l��SE�f�[�^���������//
	void ClearSE(const ChStd::DataNo _soundNo);

	///////////////////////////////////////////////////////////////////////////////////

	//�Z�b�g���ꂽBGM�����ׂĉ��//
	void ClearSE();

	///////////////////////////////////////////////////////////////////////////////////

	//�Z�b�g���ꂽBGM���Đ�//
	void PlayBGM(const std::string _soundName);

	///////////////////////////////////////////////////////////////////////////////////

	//�o�^���ɕێ��������l��SE���Đ�����//
	void PlaySE(const ChStd::DataNo _soundNo);

	//����SE���Đ�����(Update���\�b�h��ݒu����K�v������)//
	void PlaySE(
		const std::string _soundName
		, const std::string _useSoundDirectory
		, const ChVec3_9* _soundPos);

	///////////////////////////////////////////////////////////////////////////////////

	//���ݍĐ����Ă���BGM���~�߂�//
	void StopBGM();

	///////////////////////////////////////////////////////////////////////////////////

	//�o�^���ɕێ��������l��SE���~�߂�//
	void StopSE(const ChStd::DataNo _soundNo);

	///////////////////////////////////////////////////////////////////////////////////

protected:

	//UserData//
	std::map<std::string, std::string> directoryPathList;
	
	LPDIRECTSOUND3DLISTENER8 lpSListener;//���X�i�[(�����l)//
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

	//���y�ǂݍ��ݗp�֐�//
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