
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9anim.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include"../../ChGameIncludeFile.h"

#include"../ChSound/ChBaseDSound9.h"
#include"ChSoundManager9.h"

using namespace ChSound;

///////////////////////////////////////////////////////////////////////////////////////
//ChSoundManagerメソッド
///////////////////////////////////////////////////////////////////////////////////////

void SoundManager8::Init(const HWND _hWin)
{
	LPDIRECTSOUNDBUFFER Tmp = nullptr;

	DirectSoundCreate8(nullptr, &SoundDevice, nullptr);

	if (SoundDevice == nullptr)return;

	SoundDevice->SetCooperativeLevel(_hWin, DSSCL_NORMAL);

	DSBUFFERDESC TmpB;
	WAVEFORMATEX wf;

	wf = SetWaveFormat();

	ZeroMemory(&Tmp, sizeof(DSBUFFERDESC));

	TmpB.dwSize = sizeof(DSBUFFERDESC);
	TmpB.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	TmpB.dwBufferBytes = 0;
	TmpB.dwReserved = 0;
	TmpB.lpwfxFormat = &wf;
	TmpB.guid3DAlgorithm = GUID_NULL;

	SoundDevice->CreateSoundBuffer(&TmpB, &Tmp, NULL);

	Tmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&MainBuffer);

	Tmp->Release();

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

