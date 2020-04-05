#ifndef Ch_Game_MeMa_h
#define Ch_Game_MeMa_h

namespace ChCpp
{
	//ポインターで使用するメモリ全体を管理するクラス//
	class MemoryManager:public ChCpp::ChCp::InitPack
	{
	public:

		///////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init(unsigned long _UseByteSize = 100)
		{
			if (_UseByteSize <= 0)return;
			UseMemorySize = new char[_UseByteSize];
			UseFlg = true;

			SetInitFlg(true);
		}

		inline void Release()
		{
			if (!UseFlg)return;

			ChPtr::MemoryRelease(UseMemorySize);

			UseFlg = false;

			SetInitFlg(false);
		}

		///////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetMemorySize(unsigned long _UseByteSize)
		{
			if (_UseByteSize <= 0)return;

			ChPtr::MemoryRelease(UseMemorySize);

			UseMemorySize = new char[_UseByteSize];
		}

		///////////////////////////////////////////////////////////////////////////////
		//オブジェクトのインスタンス化//

		template<typename T, typename ...TT>
		inline T* New(T* _Obj, TT... _value)
		{


		};

		///////////////////////////////////////////////////////////////////////////////
		//オブジェクトのメモリ開放//

		template<typename T>
		inline void* Delete(T* _Obj)
		{

		};


	private:

		char *UseMemorySize;
		unsigned long NowUseMemory = 0;
		ChStd::Bool UseFlg = false;

		///////////////////////////////////////////////////////////////////////////////

		void MemoryMove();

		///////////////////////////////////////////////////////////////////////////////

		void MemoryCopy();

		///////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline MemoryManager() {}

		inline ~MemoryManager()
		{
			Release();
		}

	public:

		///////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline static MemoryManager& GetIns()
		{
			static MemoryManager Ins;
			return Ins;
		}

	};
	static const std::function<MemoryManager&()>MemManager = MemoryManager::GetIns;
}

#endif