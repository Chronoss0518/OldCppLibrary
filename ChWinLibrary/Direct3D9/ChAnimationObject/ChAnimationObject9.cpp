
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../../BaseSystem/ChBaseSystem/ChBaseSystem.h"
#include"../../BaseSystem/ChWindows/ChWindows.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../../BaseSystem/ChWindows/ChWindows.h"
#include"ChAnimationObject9.h"

using namespace ChSystem;

///////////////////////////////////////////////////////////////////////////////////////
//ChAnimationObject9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChAniObj9::SetAnimationFunction(
	const std::function<void()>& _Func
	, const size_t _AniFrameNum)
{
	if (_AniFrameNum > AniList.size()) {

		//ChSystem::ErrerMessage("関数がセットできませんでした", "警告");

		AniList[_AniFrameNum]->FrameFunc = _Func;

		return;
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ChAniObj9::SetAniObject(
	const ChVec3_9& _Pos
	, const ChVec3_9& _Sca
	, const ChQua_9& _Rot)
{
	auto Ani = ChPtr::Make_S<AniObject>();

	Ani->Pos = _Pos;
	Ani->Sca = _Sca;
	Ani->Rot = _Rot;

	AniList.push_back(Ani);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChAniObj9::SetAniObject(const ChMat_9& _Mat)
{
	auto TmpMat = _Mat;

	auto Ani = ChPtr::Make_S<AniObject>();

	Ani->Pos = TmpMat;

	Ani->Rot = TmpMat;

	Ani->Sca = TmpMat.GetScaleSize();

	AniList.push_back(Ani);

}

///////////////////////////////////////////////////////////////////////////////////////

ChMat_9 ChAniObj9::Update()
{
	if (!AniPlayFlg)return LastPlayMat;

	if (NowFrame + 1 >= AniList.size())
	{
		Stop();
		return  LastPlayMat;
	}

	AniObject SAni, EAni, NAni;

	SAni = *AniList[NowFrame];

	if (NowFrame < 0 && ChPtr::NotNullCheck(TmpStartMat))
	{

		auto TmpMat = *TmpStartMat;
		SAni.Pos = TmpMat;
		SAni.Rot = TmpMat;
		SAni.Sca = TmpMat.GetScaleSize();

	}

	EAni = *AniList[NowFrame + 1];

	NAni.Lerp(SAni, EAni, NowTime);

	NowTime += OneFrameTime;

	if (NowTime > 1.0f)
	{
		NowTime -= 1.0f;
		NowFrame++;
		FuncFlg = false;
	}

	LastPlayMat.Identity();
	LastPlayMat.Scaling(NAni.Sca);
	LastPlayMat *= NAni.Rot;
	LastPlayMat = NAni.Pos;



	if (FuncFlg)return LastPlayMat;
	if (NAni.FrameFunc == nullptr)return LastPlayMat;

	NAni.FrameFunc();

	FuncFlg = true;

	return LastPlayMat;

}

///////////////////////////////////////////////////////////////////////////////////////
//ChAnimationSupporter9メソッド
///////////////////////////////////////////////////////////////////////////////////////

const std::string ChAnimationSupporter9::AnimationCheck = "AnimationSet Global {";

const std::string ChAnimationSupporter9::Animation = "Animation {";

const std::string ChAnimationSupporter9::AniKey = "AnimationKey {";

void ChAnimationSupporter9::CreateFunction()
{
	if (CFlg)return;

	Creaters[".x"] =
		[this](const std::string& _FileName)
	{

		std::string Datas;
		{
			ChFIO::File File;
			File.FileOpen(_FileName);
			File.FileRead(Datas);
			File.FileClose();
		}

		std::map<std::string, ChPtr::Shared<ChAnimationObject9>>Animations;

		if (Datas.find(AnimationCheck) == std::string::npos)return std::move(Animations);

		size_t FPos = 0;
		std::vector<ChPtr::Shared<ChVec3_9>>PosList;
		std::vector<ChPtr::Shared<ChVec3_9>>SclList;
		std::vector<ChPtr::Shared<ChQua_9>>RotList;

		while ((FPos = Datas.find(Animation, FPos)) != std::string::npos)
		{
			if (Datas.find(AniKey, FPos) == std::string::npos)break;


			FPos += Animation.length();
			std::string BoneName;

			BoneName = Datas.substr(Datas.find("{", FPos) + 1, Datas.find("}", FPos) - Datas.find("{", FPos) - 1);



			{

				ChCpp::BitBool BreakFlg;

				while (1)
				{
					size_t TmpPos = Datas.find(AniKey, FPos);
					if (TmpPos == std::string::npos)break;
					TmpPos += AniKey.length();

					FPos = Datas.find(";", TmpPos);
					std::string Test;
					Test = Datas.substr(FPos - 2, 2);
					int Tmp = std::atoi(Datas.substr(FPos - 2, 2).c_str());

					switch (Tmp)
					{
					case 0:

						RotList = (Create4D(Datas, FPos, false));
						for (auto&& Qua : RotList)
						{
							Qua->w *= -1.0f;
						}
						BreakFlg.SetBitTrue(0);
						break;
					case 1:

						SclList = (Create3D(Datas, FPos, false));
						BreakFlg.SetBitTrue(1);
						break;
					case 2:

						PosList = (Create3D(Datas, FPos, false));
						BreakFlg.SetBitTrue(2);

						break;
					default:
						break;
					}

					if (BreakFlg.GetBitFlg(0)
						&& BreakFlg.GetBitFlg(1)
						&& BreakFlg.GetBitFlg(2))break;

				}
			}

			size_t Min = RotList.size(), Max = RotList.size();

			if (Max < SclList.size())Max = SclList.size();
			if (Max < PosList.size())Max = PosList.size();


			if (Min > SclList.size())Min = SclList.size();
			if (Min < PosList.size())Min = PosList.size();

			for (size_t Cnt = 0; Cnt < Max - Min; Cnt++)
			{
				if (RotList.size() < Max)
				{
					auto Rot = ChPtr::Make_S<ChQua_9>();
					if (RotList.size() > 0)
					{
						*Rot = *RotList[RotList.size() - 1];

					}
					RotList.push_back(Rot);
				}
				if (SclList.size() < Max)
				{
					auto Scl = ChPtr::Make_S<ChVec3_9>();
					if (SclList.size() > 0)
					{
						*Scl = *SclList[SclList.size() - 1];
					}
					SclList.push_back(Scl);
				}
				if (PosList.size() < Max)
				{
					auto Pos = ChPtr::Make_S<ChVec3_9>();
					if (PosList.size() > 0)
					{
						*Pos = *PosList[PosList.size() - 1];
					}
					*Pos = *PosList[PosList.size() - 1];
					PosList.push_back(Pos);
				}
			}


			auto Ani = ChPtr::Make_S<ChAnimationObject9>();

			for (size_t Cnt = 0; Cnt < Max; Cnt++)
			{
				Ani->SetAniObject
				(
					*PosList[Cnt]
					, *SclList[Cnt]
					, *RotList[Cnt]
				);

			}


			Animations[BoneName] = Ani;

		}


		return (Animations);
		//SizeTest//

	};



	CFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<ChQua_9>>
ChAnimationSupporter9::Create4D(const std::string& _Str, size_t& _FPos, const ChStd::Bool _RFlg)
{

	std::vector<ChPtr::Shared<ChQua_9>> TmpQua;
	std::string CutStart = ";4;";
	std::string CutEnd = ";;";
	std::string End = ";;;";

	size_t TmpFPos = 0;
	while (_Str.find(End, _FPos - 1) >= _FPos)
	{

		if ((TmpFPos = _Str.find(CutStart, _FPos)) >= _Str.find(End, _FPos))break;
		_FPos = TmpFPos;
		_FPos += CutStart.length();

		auto Qua = ChPtr::Make_S<ChQua_9>();

		{
			ChQua TmpQua;
			TmpQua.Deserialize(_Str, _FPos);
			*Qua = TmpQua;
		}

		if (_RFlg)*Qua *= -1.0f;
		_FPos = _Str.find(CutEnd, _FPos);

		TmpQua.push_back(Qua);


	}

	_FPos = _Str.find(End, _FPos);

	return TmpQua;


}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<ChVec3_9>>
ChAnimationSupporter9::Create3D(const std::string& _Str, size_t& _FPos, const ChStd::Bool _RFlg)
{
	std::vector<ChPtr::Shared<ChVec3_9>> TmpVec;
	std::string CutStart = ";3;";
	std::string CutEnd = ";;";
	std::string End = ";;;";

	size_t TmpFPos = 0;
	while (_Str.find(End, _FPos - 1) >= _FPos)
	{

		if ((TmpFPos = _Str.find(CutStart, _FPos)) >= _Str.find(End, _FPos))break;
		_FPos = TmpFPos;
		_FPos += CutStart.length();

		auto Vec = ChPtr::Make_S<ChVec3_9>();

		{
			ChVec3 TmpVec;
			TmpVec.Deserialize(_Str, _FPos);
			*Vec = TmpVec;
		}

		if (_RFlg)*Vec *= -1.0f;
		TmpVec.push_back(Vec);
		_FPos = _Str.find(CutEnd, _FPos);
	}

	return TmpVec;

}
