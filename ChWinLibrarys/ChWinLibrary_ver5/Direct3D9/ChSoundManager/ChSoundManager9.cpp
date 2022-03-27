
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChSound/ChBaseDSound9.h"
#include"ChSoundManager9.h"

using namespace ChSound;

///////////////////////////////////////////////////////////////////////////////////////
//ChSoundManagerメソッド
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

	// プライマリ・バッファのWaveフォーマットを設定
	WAVEFORMATEX wf;
	ZeroMemory(&wf, sizeof(WAVEFORMATEX));
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;		// ２チャンネル（ステレオ）
	wf.nSamplesPerSec = 88200;	// サンプリング・レート　44.1kHz
	wf.nBlockAlign = 4;
	wf.wBitsPerSample = 16;		// 16ビット
	wf.nAvgBytesPerSec = wf.nChannels * wf.wBitsPerSample / 8;
	return wf;

}

