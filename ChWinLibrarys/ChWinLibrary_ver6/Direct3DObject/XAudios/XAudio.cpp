#include<Windows.h>

#include<xaudio2.h>
#include<mfapi.h>
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <stdio.h>
#include <mferror.h>
#include<mfreadwrite.h>

#pragma comment(lib,"xaudio2.lib")
#pragma comment(lib,"mfplat.lib")
#pragma comment(lib,"mfreadwrite.lib")
#pragma comment(lib,"mfuuid.lib")

#include"../../ChBaseLibrary.h"

#include"ChXAudio.h"

using namespace ChD3D;

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::SetVolume(const float _Volume)
{
	if (!*this)return;
	Voice->SetVolume(_Volume);
}

///////////////////////////////////////////////////////////////////////////////////

float AudioObject::GetVolume()
{
	float outVol = 0.0f;

	if (!*this)return outVol;

	Voice->GetVolume(&outVol);

	return outVol;
}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Play()
{
	if (!*this)return;

	Voice->Start(0);

}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Pause()
{

	if (!*this)return;

	Voice->Stop();
	
}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Stop()
{
	if (!*this)return;

	Voice->Stop();

	Voice->FlushSourceBuffers();

	Voice->SubmitSourceBuffer(XAudioManager().AudioDatas[FileName][0]);
	Voice->SubmitSourceBuffer(XAudioManager().AudioDatas[FileName][1]);

	NowPos = 1;

}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Release()
{
	if (!*this)return;

	Voice->DestroyVoice();

	Voice = nullptr;

	auto& Audios = XAudioManager().Audios;

	auto Thiss = std::find(Audios.begin(), Audios.end(), this);

	Audios.erase(Thiss);

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void XAudio2Manager::Init()
{
	if (*this)return;

	XAudio2Create(&audio, 0, XAUDIO2_DEFAULT_PROCESSOR);

	if (audio == nullptr)return;

	audio->CreateMasteringVoice(&audioMV);

	SetInitFlg(true);

	MFStartup(MF_VERSION);

	(void)CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void XAudio2Manager::Release()
{

	if (!*this)return;

	for (auto&& data : AudioDatas)
	{
		for (auto&& buffer : data.second)
		{
			delete buffer;
		}
	}

	for (auto&& aObject : Audios)
	{
		aObject->Release();
	}

	if (ChPtr::NotNullCheck(audioMV)) { audioMV->DestroyVoice(); audioMV = nullptr; };
	if (ChPtr::NotNullCheck(audio)) { audio->Release(); audio = nullptr; };

	MFShutdown();

	SetInitFlg(false);

}

///////////////////////////////////////////////////////////////////////////////////

void XAudio2Manager::CreateSound(AudioObject* _Object, const std::string& _FileName)
{

	if (ChPtr::NullCheck(_Object))return;

	IMFSourceReader* Reader;
	MFCreateSourceReaderFromURL(
		ChStr::ToWString(_FileName).c_str(),
		nullptr,
		&Reader);

	if (ChPtr::NullCheck(Reader))
	{
		

		return;
	}


	IMFMediaType* MType;
	MFCreateMediaType(&MType);

	MType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	MType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

	Reader->SetCurrentMediaType((MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, MType);

	MType->Release();

	Reader->GetCurrentMediaType((MF_SOURCE_READER_FIRST_AUDIO_STREAM), &MType);

	WAVEFORMATEX* WaveFormat;

	{

		UINT32 size = 0;

		MFCreateWaveFormatExFromMFMediaType(MType, &WaveFormat, &size);

	}

	DWORD StreamFlg = 0;
	LONGLONG StreamLen = 0;

	std::vector<XAUDIO2_BUFFER*> FileDatas;

	while (true)
	{
		IMFSample* sample;

		Reader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &StreamFlg, &StreamLen, &sample);


		if (ChPtr::NullCheck(sample))break;

		IMFMediaBuffer* mediaBuffer;

		sample->ConvertToContiguousBuffer(&mediaBuffer);

		BYTE* Data;

		DWORD MaxStreamLen;
		DWORD CurrentLen;

		mediaBuffer->GetMaxLength(&MaxStreamLen);
		mediaBuffer->GetCurrentLength(&CurrentLen);

		mediaBuffer->Lock(&Data, &MaxStreamLen, &CurrentLen);

		auto FileData = new ChXAUDIO2_BUFFER();

		for (DWORD i = 0; i < MaxStreamLen; i++)
		{
			FileData->AudioDataVector.push_back(Data[i]);
		}

		FileData->AudioBytes = MaxStreamLen;
		FileData->pAudioData = &FileData->AudioDataVector[0];
		FileData->Flags = XAUDIO2_END_OF_STREAM;

		FileDatas.push_back(FileData);

		mediaBuffer->Unlock();

		mediaBuffer->Release();

		sample->Release();


	}

	audio->CreateSourceVoice(&_Object->Voice, WaveFormat);

	_Object->Voice->SubmitSourceBuffer(FileDatas[0]);
	_Object->Voice->SubmitSourceBuffer(FileDatas[1]);

	_Object->FileName = _FileName;
	AudioDatas[_Object->FileName] = FileDatas;
	_Object->SetInitFlg(true);

	Audios.push_back(_Object);

	CoTaskMemFree(WaveFormat);

	MType->Release();

	Reader->Release();

}

///////////////////////////////////////////////////////////////////////////////////

void XAudio2Manager::Update()
{

	for (auto&& audio : Audios)
	{

		audio->LoopEndPos = audio->LoopEndPos >= AudioDatas[audio->FileName].size() ? AudioDatas[audio->FileName].size() : audio->LoopEndPos;

		audio->LoopStartPos = audio->LoopStartPos >= audio->LoopEndPos ? 0 : audio->LoopStartPos;


		XAUDIO2_VOICE_STATE State;
		audio->Voice->GetState(&State);

		if (State.BuffersQueued >= 2)continue;
		ChStd::Bool LoopFlg = false;
		unsigned long NowPos = 0;
		NowPos = audio->NowPos + 1 >= audio->LoopEndPos ? audio->LoopStartPos : audio->NowPos + 1;
		
		if (NowPos <= 0)LoopFlg = true;

		if (!audio->LoopFlg && LoopFlg)continue;

		audio->NowPos = NowPos;

		audio->Voice->SubmitSourceBuffer(AudioDatas[audio->FileName][NowPos]);

	}
}