#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

#include"../../BaseIncluder/ChBase.h"

namespace ChCpp
{
	class BaseFrame;

	//BaseFrame管理用クラス//
	class BaseFrameList:public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//自作フレームをセット//
		//BaseFrameを継承しているもののみセットできる//
		template<class T>
		void SetFrame(typename std::enable_if
			<std::is_base_of<BaseFrame, T>::value, const std::string&>::type _useFrameName)
		{
			if (frameList.find(_useFrameName) != frameList.end())
			{
				//ChSystem::ErrerMessage("このフレームはすでに登録されています", "警告");

				return;
			}

			frameList[_useFrameName]
				= []()-> ChPtr::Shared<BaseFrame>
			{
				return ChPtr::Make_S<T>(); 
			};

			if (nowFrame != nullptr)return;

			ChengeFrame(_useFrameName);

			Chenges();
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

	private:

		friend BaseFrame;

		///////////////////////////////////////////////////////////////////////////////////

		void ChengeFrame(const std::string& _frameName);

		void Chenges();

		std::map<std::string, std::function<ChPtr::Shared<BaseFrame>()>>frameList;

		ChPtr::Shared<BaseFrame>nextFrame = nullptr;

		ChPtr::Shared<BaseFrame>nowFrame;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BaseFrameList() { SetInitFlg(true); }

		~BaseFrameList() { SetInitFlg(false); }

	public:

		static BaseFrameList& GetIns()
		{
			static BaseFrameList ins;
			return ins;
		}

	};

	static const std::function<BaseFrameList&()>FrameList = BaseFrameList::GetIns;

	//ゲームシーンを簡易的生成を行うためのクラス//
	//必要に応じて以下の関数をオーバーライドする//
	//void Init(),void Release(),void Frame()//
	class BaseFrame:public ChCp::Releaser
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

		//登録されているフレームに移動する//
		void ChangeFrame(const std::string& _frameName)
		{
			FrameList().ChengeFrame(_frameName);
		}

	private:

	};
}


#endif