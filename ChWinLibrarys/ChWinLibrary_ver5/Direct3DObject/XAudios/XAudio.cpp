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
	voice->SetVolume(_Volume);
}

///////////////////////////////////////////////////////////////////////////////////

float AudioObject::GetVolume()
{
	float outVol = 0.0f;

	if (!*this)return outVol;

	voice->GetVolume(&outVol);

	return outVol;
}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Play()
{
	if (!*this)return;

	voice->Start(0);

}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Pause()
{

	if (!*this)return;

	voice->Stop();
	
}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Stop()
{
	if (!*this)return;

	voice->Stop();

	voice->FlushSourceBuffers();

	voice->SubmitSourceBuffer(XAudioManager().audioDatas[fileName][0]);
	voice->SubmitSourceBuffer(XAudioManager().audioDatas[fileName][1]);

	nowPos = 1;

}

///////////////////////////////////////////////////////////////////////////////////

void AudioObject::Release()
{
	if (!*this)return;

	voice->DestroyVoice();

	voice = nullptr;

	auto& audios = XAudioManager().audios;

	auto thiss = std::find(audios.begin(), audios.end(), this);

	audios.erase(thiss);

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

	for (auto&& data : audioDatas)
	{
		for (auto&& buffer : data.second)
		{
			delete buffer;
		}
	}

	for (auto&& aObject : audios)
	{
		aObject->Release();
	}

	if (ChPtr::NotNullCheck(audioMV)) { audioMV->DestroyVoice(); audioMV = nullptr; };
	if (ChPtr::NotNullCheck(audio)) { audio->Release(); audio = nullptr; };

	MFShutdown();

	SetInitFlg(false);

}

///////////////////////////////////////////////////////////////////////////////////

void XAudio2Manager::CreateSound(AudioObject* _Object, const std::string& _fileName)
{

	if (ChPtr::NullCheck(_Object))return;

	IMFSourceReader* reader;
	MFCreateSourceReaderFromURL(
		ChStr::UTF8ToWString(_fileName).c_str(),
		nullptr,
		&reader);

	if (ChPtr::NullCheck(reader))
	{
		

		return;
	}


	IMFMediaType* mType;
	MFCreateMediaType(&mType);

	mType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	mType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

	reader->SetCurrentMediaType((MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, mType);

	mType->Release();

	reader->GetCurrentMediaType((MF_SOURCE_READER_FIRST_AUDIO_STREAM), &mType);

	WAVEFORMATEX* waveFormat;

	{

		UINT32 size = 0;

		MFCreateWaveFormatExFromMFMediaType(mType, &waveFormat, &size);

	}

	DWORD streamFlg = 0;
	LONGLONG streamLen = 0;

	std::vector<XAUDIO2_BUFFER*> fileDatas;

	while (true)
	{
		IMFSample* sample;

		reader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &streamFlg, &streamLen, &sample);


		if (ChPtr::NullCheck(sample))break;

		IMFMediaBuffer* mediaBuffer;

		sample->ConvertToContiguousBuffer(&mediaBuffer);

		BYTE* Data;

		DWORD maxStreamLen;
		DWORD currentLen;

		mediaBuffer->GetMaxLength(&maxStreamLen);
		mediaBuffer->GetCurrentLength(&currentLen);

		mediaBuffer->Lock(&Data, &maxStreamLen, &currentLen);

		auto fileData = new ChXAUDIO2_BUFFER();

		for (DWORD i = 0; i < maxStreamLen; i++)
		{
			fileData->audioDataVector.push_back(Data[i]);
		}

		fileData->AudioBytes = maxStreamLen;
		fileData->pAudioData = &fileData->audioDataVector[0];
		fileData->Flags = XAUDIO2_END_OF_STREAM;

		fileDatas.push_back(fileData);

		mediaBuffer->Unlock();

		mediaBuffer->Release();

		sample->Release();


	}

	audio->CreateSourceVoice(&_Object->voice, waveFormat);

	_Object->voice->SubmitSourceBuffer(fileDatas[0]);
	_Object->voice->SubmitSourceBuffer(fileDatas[1]);

	_Object->fileName = _fileName;
	audioDatas[_Object->fileName] = fileDatas;
	_Object->SetInitFlg(true);

	audios.push_back(_Object);

	CoTaskMemFree(waveFormat);

	mType->Release();

	reader->Release();

}

///////////////////////////////////////////////////////////////////////////////////

void XAudio2Manager::Update()
{

	for (auto&& audio : audios)
	{

		audio->loopEndPos = audio->loopEndPos >= audioDatas[audio->fileName].size() ? audioDatas[audio->fileName].size() : audio->loopEndPos;

		audio->loopStartPos = audio->loopStartPos >= audio->loopEndPos ? 0 : audio->loopStartPos;


		XAUDIO2_VOICE_STATE state;
		audio->voice->GetState(&state);

		if (state.BuffersQueued >= 2)continue;
		ChStd::Bool loopFlg = false;
		unsigned long nowPos = 0;
		nowPos = audio->nowPos + 1 >= audio->loopEndPos ? audio->loopStartPos : audio->nowPos + 1;
		
		if (nowPos <= 0)loopFlg = true;

		if (!audio->loopFlg && loopFlg)continue;

		audio->nowPos = nowPos;

		audio->voice->SubmitSourceBuffer(audioDatas[audio->fileName][nowPos]);

	}
}