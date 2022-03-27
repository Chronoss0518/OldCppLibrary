#ifndef Ch_CPP_Script_h
#define Ch_CPP_Script_h

namespace ChCpp
{

	//スクリプト全体を管理するクラス//
	//これを各地に配置して利用する//
	typedef class ScriptController
	{

	public:


		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		virtual ~ScriptController() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()
		{
			ScriptList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//登録しているScriptをセットする。//
		void SetScript(
			const std::function<void()> _Update
			, const std::function<void()> _Draw = []() {}
			, const std::function<void()> _Enter = []() {}
		, const std::function<void()> _Exit = []() {});

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		unsigned long GetNowScriptNum()
		{

			if (NowScript.lock() == nullptr)return ULONG_MAX;

			return NowScript.lock()->MyNum;

		}

		///////////////////////////////////////////////////////////////////////////////////

		void ChangeScript(const unsigned long _ScriptNo = ULONG_MAX)
		{

			unsigned long Tmp = 0;
			if (NowScript.lock() != nullptr)
			{
				Tmp = NowScript.lock()->MyNum + 1;
			}

			if (ScriptList.size() > _ScriptNo)Tmp = _ScriptNo;
			if (ScriptList.size() <= Tmp)Tmp = NowScript.lock()->MyNum;

			NextScript = ScriptList[Tmp];

		}

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update()
		{
			if (NowScript.lock() == nullptr)return;
			NowScript.lock()->Update();
			Chenge();
		}

		///////////////////////////////////////////////////////////////////////////////////

		void Draw()
		{

			if (NowScript.lock() == nullptr)return;
			NowScript.lock()->Draw();
			Chenge();
		}

		///////////////////////////////////////////////////////////////////////////////////

		void ClearScript()
		{
			ScriptList.clear();
		}

	protected:

		void Chenge()
		{
			if (NextScript == nullptr)return;

			if (NowScript.lock() != nullptr)
			{
				NowScript.lock()->Exit();
			}

			NowScript = NextScript;

			NowScript.lock()->Enter();

			NextScript = nullptr;
		}

		struct ChScript
		{

			///////////////////////////////////////////////////////////////////////////////////
			//ConstructerDestructer//


			std::function<void()>Enter = []() {};

			std::function<void()>Update = []() {};

			std::function<void()>Draw = []() {};

			std::function<void()>Exit = []() {};

			unsigned long MyNum = 0;

		};

		std::vector<ChPtr::Shared<ChScript>> ScriptList;

		ChPtr::Shared<ChScript> NextScript = nullptr;

		ChPtr::Weak<ChScript>NowScript;

	}ChScCon;


}


#endif
