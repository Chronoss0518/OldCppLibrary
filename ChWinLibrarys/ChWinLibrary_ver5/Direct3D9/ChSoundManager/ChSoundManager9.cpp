
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChSound/ChBaseDSound9.h"
#include"ChSoundManager9.h"

using namespace ChSound;

///////////////////////////////////////////////////////////////////////////////////////
//ChSoundManager���\�b�h
///////////////////////////////////////////////////////////////////////////////////////

void SoundManager8::Init(const HWND _hWin)
{
	LPDIRECTSOUNDBUFFER tmp = nullptr;

	DirectSoundCreate8(nullptr, &soundDevice, nullptr);

	if (soundDevice == nullptr)return;

	soundDevice->SetCooperativeLevel(_hWin, DSSCL_NORMAL);

	DSBUFFERDESC tmpB;
	WAVEFORMATEX wf;

	wf = SetWaveFormat();

	tmpB.dwSize = sizeof(DSBUFFERDESC);
	tmpB.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	tmpB.dwBufferBytes = 0;
	tmpB.dwReserved = 0;
	tmpB.lpwfxFormat = &wf;
	tmpB.guid3DAlgorithm = GUID_NULL;

	soundDevice->CreateSoundBuffer(&tmpB, &tmp, NULL);

	tmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&mainBuffer);

	tmp->Release();

	SetInitFlg(true);

}

WAVEFORMATEX SoundManager8::SetWaveFormat()
{

	// �v���C�}���E�o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
	WAVEFORMATEX wf;
	ZeroMemory(&wf, sizeof(WAVEFORMATEX));
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;		// �Q�`�����l���i�X�e���I�j
	wf.nSamplesPerSec = 88200;	// �T���v�����O�E���[�g�@44.1kHz
	wf.nBlockAlign = 4;
	wf.wBitsPerSample = 16;		// 16�r�b�g
	wf.nAvgBytesPerSec = wf.nChannels * wf.wBitsPerSample / 8;
	return wf;

}

