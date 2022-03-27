#ifndef Ch_CPP_Script_h
#define Ch_CPP_Script_h

namespace ChCpp
{

	//�X�N���v�g�S�̂��Ǘ�����N���X//
	//������e�n�ɔz�u���ė��p����//
	typedef class ScriptController:public ChCp::Releaser
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()override
		{
			scriptList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�o�^���Ă���Script���Z�b�g����B//
		void SetScript(
			const std::function<void()> _update
			, const std::function<void()> _draw = []() {}
			, const std::function<void()> _enter = []() {}
		, const std::function<void()> _exit = []() {});

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		unsigned long GetNowScriptNum()
		{

			if (nowScript.lock() == nullptr)return ULONG_MAX;

			return nowScript.lock()->myNum;

		}

		///////////////////////////////////////////////////////////////////////////////////

		void ChangeScript(const unsigned long _scriptNo = ULONG_MAX)
		{

			unsigned long tmp = 0;
			if (nowScript.lock() != nullptr)
			{
				tmp = nowScript.lock()->myNum + 1;
			}

			if (scriptList.size() > _scriptNo)tmp = _scriptNo;
			if (scriptList.size() <= tmp)tmp = nowScript.lock()->myNum;

			nowScript = scriptList[tmp];

		}

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update()
		{
			if (nowScript.lock() == nullptr)return;
			nowScript.lock()->update();
			Chenge();
		}

		///////////////////////////////////////////////////////////////////////////////////

		void Draw()
		{

			if (nowScript.lock() == nullptr)return;
			nowScript.lock()->draw();
			Chenge();
		}

		///////////////////////////////////////////////////////////////////////////////////

		void ClearScript()
		{
			scriptList.clear();
		}

	protected:

		void Chenge()
		{
			if (nextScript == nullptr)return;

			if (nowScript.lock() != nullptr)
			{
				nowScript.lock()->exit();
			}

			nowScript = nextScript;

			nowScript.lock()->enter();

			nextScript = nullptr;
		}

		struct ChScript
		{

			///////////////////////////////////////////////////////////////////////////////////
			//ConstructerDestructer//


			std::function<void()>enter = []() {};

			std::function<void()>update = []() {};

			std::function<void()>draw = []() {};

			std::function<void()>exit = []() {};

			unsigned long myNum = 0;

		};

		std::vector<ChPtr::Shared<ChScript>> scriptList;

		ChPtr::Shared<ChScript> nextScript = nullptr;

		ChPtr::Weak<ChScript>nowScript;

	}ChScCon;


}


#endif
