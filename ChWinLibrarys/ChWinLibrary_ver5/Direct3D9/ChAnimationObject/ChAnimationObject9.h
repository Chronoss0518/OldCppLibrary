
#ifndef Ch_D3D9_AnCon_h
#define Ch_D3D9_AnCon_h

class ChAnimationSupporter9;

typedef class ChAnimationObject9:public ChCp::Releaser
{
public:

	///////////////////////////////////////////////////////////////////////////////////////
	//InitAndRelease//

	inline void Release()override
	{
		aniList.clear();
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	void SetAnimationFunction(
		const std::function<void()>& _func
		, const size_t _aniFrameNum);

	//現在の行列からアニメーションへ移行する//
	void SetStartMat(const ChMat_9& _startMat)
	{
		tmpStartMat = (ChMat_9*)&_startMat;
	}

	void SetOneFrameTime(const float _fps)
	{
		oneFrameTime = 1.0f / _fps;
	}

	void SetAniObject(
		const ChVec3_9& _pos
		, const ChVec3_9& _sca
		, const ChQua_9& _rot);

	void SetAniObject(const ChMat_9& _mat);

	///////////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	size_t GetAniCnt() { return aniList.size(); }

	//現在の初期行列//
	ChMat_9 GetNowStartMat()
	{
		ChMat_9 tmpAni;
		if (nowFrame >= aniList.size())tmpAni;
		tmpAni.Scaling(aniList[nowFrame]->sca);
		tmpAni *= aniList[nowFrame]->rot;
		tmpAni = aniList[nowFrame]->pos;
		return tmpAni;
	}

	//最初期行列//
	ChMat_9 GetFirstMat()
	{
		ChMat_9 tmpAni;
		if (nowFrame >= aniList.size())tmpAni;
		tmpAni.Scaling(aniList[0]->sca);
		tmpAni *= aniList[0]->rot;
		tmpAni = aniList[0]->pos;
		return tmpAni;
	}



	///////////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	ChMat_9 Update();

	///////////////////////////////////////////////////////////////////////////////////////

	void Play(const size_t _startFrame = -1)
	{
		if (aniList.size() < 2)return;

		if (nowFrame + 1 >= aniList.size())
		{
			nowFrame = 0;
			if (_startFrame >= 0
				&& _startFrame + 1 < aniList.size())nowFrame = _startFrame;
		}

		nowTime = 0.0f;
		aniPlayFlg = true;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Pause()
	{
		aniPlayFlg = false;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Stop()
	{
		aniPlayFlg = false;
		nowTime = 0.0f;
		nowFrame = 0;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	friend ChAnimationSupporter9;

private:

	struct AniObject
	{
		AniObject()
		{
			sca = 1.0f;
		}

		void Lerp(const AniObject _sAni, const AniObject _eAni,const float nowTime)
		{
			pos.Lerp(_sAni.pos, _eAni.pos, nowTime);

			sca.Lerp(_sAni.sca, _eAni.sca, nowTime);

			rot.Lerp(_sAni.rot, _eAni.rot, nowTime);

		}

		ChVec3_9 pos;
		ChVec3_9 sca;
		ChQua_9 rot;
		std::function<void()>frameFunc = nullptr;
	};

	enum class Flg
	{
		UseFunc, AniPlay
	};

	ChCpp::BitBool flgs;

	std::map<std::string, std::function<std::string(const std::string& _FileName)>>openFuncList;


	ChMat_9* tmpStartMat;


	ChMat_9 lastPlayMat;

	ChStd::Bool funcFlg = false;
	//1フレーム間の進む時間//
	float oneFrameTime = 1.0f / 60.0f;

	ChStd::Bool aniPlayFlg = true;

	float nowTime = 0.0f;
	size_t nowFrame = 0;
	std::vector<ChPtr::Shared<AniObject>> aniList;

}ChAniObj9;

class ChAnimationSupporter9
{
public:

	inline std::map < std::string, ChPtr::Shared<ChAnimationObject9>>
		CreateKeyFrame(const std::string& _fileName)
	{
		if (!cFlg)
		{
			CreateFunction();
			cFlg = true;
		}

		std::string tmpType = _fileName;
		size_t tmp = tmpType.rfind(".");

		tmpType = tmpType.substr(tmp);

		return (creaters[tmpType](_fileName));

	}



private:

	static const std::string animationCheck;

	static const std::string animation;

	static const std::string aniKey;

	void CreateFunction();

	std::vector<ChPtr::Shared<ChQua_9>>Create4D
	(const std::string& _str, size_t& _fPos ,const ChStd::Bool _rFlg);

	std::vector<ChPtr::Shared<ChVec3_9>> Create3D
	(const std::string& _str, size_t& _fPos, const ChStd::Bool _rFlg);


	std::map<std::string, std::function
		<std::map<std::string, ChPtr::Shared<ChAnimationObject9>>(const std::string&)>>creaters;
	ChStd::Bool cFlg = false;

	ChAnimationSupporter9() {}

public:

	static ChAnimationSupporter9& GetIns()
	{
		static ChAnimationSupporter9 ins;
		return ins;
	}

};

const static std::function<ChAnimationSupporter9&(void)> ChANiSupport = ChAnimationSupporter9::GetIns;

#endif
