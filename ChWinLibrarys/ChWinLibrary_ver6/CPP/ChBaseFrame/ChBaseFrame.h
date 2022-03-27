#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

#include"../../BaseIncluder/ChBase.h"

namespace ChCpp
{
	class BaseFrame;

	//BaseFrame�Ǘ��p�N���X//
	class BaseFrameList:public ChCpp::ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//����t���[�����Z�b�g//
		//BaseFrame���p�����Ă�����̂̂݃Z�b�g�ł���//
		template<class T>
		void SetFrame(typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, const std::string&>::type _UseFrameName)
		{
			if (FrameList.find(_UseFrameName) != FrameList.end())
			{
				//ChSystem::ErrerMessage("���̃t���[���͂��łɓo�^����Ă��܂�", "�x��");

				return;
			}

			FrameList[_UseFrameName]
				= []()-> ChPtr::Shared<BaseFrame>
			{
				return ChPtr::Make_S<T>(); 
			};

			if (NowFrame != nullptr)return;

			ChengeFrame(_UseFrameName);

			Chenges();
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

	private:

		friend BaseFrame;

		///////////////////////////////////////////////////////////////////////////////////

		void ChengeFrame(const std::string& _FrameName);

		void Chenges();

		std::map<std::string, std::function<ChPtr::Shared<BaseFrame>()>>FrameList;

		ChPtr::Shared<BaseFrame>NextFrame = nullptr;

		ChPtr::Shared<BaseFrame>NowFrame;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BaseFrameList() { SetInitFlg(true); }

		~BaseFrameList() { SetInitFlg(false); }

	public:

		static BaseFrameList& GetIns()
		{
			static BaseFrameList Ins;
			return Ins;
		}

	};

	static const std::function<BaseFrameList&()>FrameList = BaseFrameList::GetIns;

	//�Q�[���V�[�����ȈՓI�������s�����߂̃N���X//
	//�K�v�ɉ����Ĉȉ��̊֐����I�[�o�[���C�h����//
	//void Init(),void Release(),void Frame()//
	class BaseFrame:public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//
		virtual inline void Init() {};

		virtual inline void Release()override {};

		///////////////////////////////////////////////////////////////////////////////////

		virtual void Frame() = 0;

		friend BaseFrameList;

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BaseFrame() {};

		virtual ~BaseFrame() { Release(); };

		//�o�^����Ă���t���[���Ɉړ�����//
		void ChangeFrame(const std::string& _FrameName)
		{
			FrameList().ChengeFrame(_FrameName);
		}

	private:

	};
}


#endif