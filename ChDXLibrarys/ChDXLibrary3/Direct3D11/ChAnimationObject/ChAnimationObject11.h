
#ifndef Ch_D3D9_AnCon_h
#define Ch_D3D9_AnCon_h

class ChAnimationSupporter9;

typedef class ChAnimationObject9
{
public:
	///////////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChAnimationObject9() {}

	~ChAnimationObject9() { Release(); };

	///////////////////////////////////////////////////////////////////////////////////////
	//InitAndRelease//

	inline void Release()
	{
		AniList.clear();
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	void SetAnimationFunction(
		const std::function<void()>& _Func
		, const size_t _AniFrameNum);

	//現在の行列からアニメーションへ移行する//
	void SetStartMat(const ChMat_9& _StartMat)
	{
		TmpStartMat = (ChMat_9*)&_StartMat;
	}

	void SetOneFrameTime(const float _FTime)
	{
		OneFrameTime = 1.0f / _FTime;
	}

	void SetAniObject(
		const ChVec3_9& _Pos
		, const ChVec3_9& _Sca
		, const ChQua_9& _Rot);

	void SetAniObject(const ChMat_9& _Mat);

	///////////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	size_t GetAniCnt() { return AniList.size(); }

	//現在の初期行列//
	ChMat_9 GetNowStartMat()
	{
		ChMat_9 TmpAni;
		if (NowFrame >= AniList.size())TmpAni;
		TmpAni.Scaling(AniList[NowFrame]->Sca);
		TmpAni *= AniList[NowFrame]->Rot;
		TmpAni = AniList[NowFrame]->Pos;
		return TmpAni;
	}

	//最初期行列//
	ChMat_9 GetFirstMat()
	{
		ChMat_9 TmpAni;
		if (NowFrame >= AniList.size())TmpAni;
		TmpAni.Scaling(AniList[0]->Sca);
		TmpAni *= AniList[0]->Rot;
		TmpAni = AniList[0]->Pos;
		return TmpAni;
	}



	///////////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	ChMat_9 Update();

	///////////////////////////////////////////////////////////////////////////////////////

	void Play(const size_t _StartFrame = -1)
	{
		if (AniList.size() < 2)return;

		if (NowFrame + 1 >= AniList.size())
		{
			NowFrame = 0;
			if (_StartFrame >= 0
				&& _StartFrame + 1 < AniList.size())NowFrame = _StartFrame;
		}

		NowTime = 0.0f;
		AniPlayFlg = true;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Pause()
	{
		AniPlayFlg = false;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Stop()
	{
		AniPlayFlg = false;
		NowTime = 0.0f;
		NowFrame = 0;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	friend ChAnimationSupporter9;

private:

	struct AniObject
	{
		AniObject()
		{
			Sca = 1.0f;
		}

		void Lerp(const AniObject _SAni, const AniObject _EAni,const float NowTime)
		{
			Pos.Lerp(_SAni.Pos, _EAni.Pos, NowTime);

			Sca.Lerp(_SAni.Sca, _EAni.Sca, NowTime);

			Rot.Lerp(_SAni.Rot, _EAni.Rot, NowTime);

		}

		ChVec3_9 Pos;
		ChVec3_9 Sca;
		ChQua_9 Rot;
		std::function<void()>FrameFunc = nullptr;
	};

	enum class Flg
	{
		UseFunc, AniPlay
	};

	ChCpp::BitBool Flgs;

	std::map<std::string, std::function<std::string(const std::string& _FileName)>>OpenFuncList;


	ChMat_9* TmpStartMat;


	ChMat_9 LastPlayMat;

	ChStd::Bool FuncFlg = false;
	//1フレーム間の進む時間//
	float OneFrameTime = 1.0f / 60.0f;

	ChStd::Bool AniPlayFlg = true;

	float NowTime = 0.0f;
	size_t NowFrame = 0;
	std::vector<ChPtr::Shared<AniObject>> AniList;

}ChAniObj9;

class ChAnimationSupporter9
{
public:

	inline std::map < std::string, ChPtr::Shared<ChAnimationObject9>>
		CreateKeyFrame(const std::string& _FileName)
	{
		if (!CFlg)
		{
			CreateFunction();
			CFlg = true;
		}

		std::string TmpType = _FileName;
		size_t Tmp = TmpType.rfind(".");

		TmpType = TmpType.substr(Tmp);

		return (Creaters[TmpType](_FileName));

	}



private:

	static const std::string AnimationCheck;

	static const std::string Animation;

	static const std::string AniKey;

	void CreateFunction();

	std::vector<ChPtr::Shared<ChQua_9>>Create4D
	(const std::string& _Str, size_t& _FPos ,const ChStd::Bool _RFlg);

	std::vector<ChPtr::Shared<ChVec3_9>> Create3D
	(const std::string& _Str, size_t& _FPos, const ChStd::Bool _RFlg);


	std::map<std::string, std::function
		<std::map<std::string, ChPtr::Shared<ChAnimationObject9>>(const std::string&)>>Creaters;
	ChStd::Bool CFlg = false;

	ChAnimationSupporter9() {}

public:

	static ChAnimationSupporter9& GetIns()
	{
		static ChAnimationSupporter9 Ins;
		return Ins;
	}

};

const static std::function<ChAnimationSupporter9&(void)> ChANiSupport = ChAnimationSupporter9::GetIns;

#endif
