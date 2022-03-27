#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

#include"../../BaseIncluder/ChBase.h"

namespace ChCpp
{
	class BaseFrame;

	//BaseFrame管理用クラス//
	class BaseFrameList:public ChCpp::ChCp::InitPack
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//自作フレームをセット//
		//BaseFrameを継承しているもののみセットできる//
		template<class T>
		void SetFrame(typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, const std::string&>::type _UseFrameName)
		{
			if (FrameList.find(_UseFrameName) != FrameList.end())
			{
				//ChSystem::ErrerMessage("このフレームはすでに登録されています", "警告");

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

	//ゲームシーンを簡易的生成を行うためのクラス//
	//必要に応じて以下の関数をオーバーライドする//
	//void Init(),void Release(),void Frame()//
	class BaseFrame
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//
		virtual inline void Init() {};

		virtual inline void Release() {};

		///////////////////////////////////////////////////////////////////////////////////

		virtual void Frame() = 0;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//
		BaseFrame() {};

		virtual ~BaseFrame() { Release(); };

		friend BaseFrameList;

	protected:

		//登録されているフレームに移動する//
		void ChangeFrame(const std::string& _FrameName)
		{
			FrameList().ChengeFrame(_FrameName);
		}

	private:

	};
}


#endif