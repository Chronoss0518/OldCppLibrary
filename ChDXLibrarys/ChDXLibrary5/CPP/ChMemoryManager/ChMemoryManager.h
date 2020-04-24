#ifndef Ch_Game_MeMa_h
#define Ch_Game_MeMa_h

namespace ChCpp
{

	//ポインターで使用するメモリ全体を管理するクラス//
	//セットできるクラスや構造体には//
	//コンストラクター時の引数を必要としないもののみ利用できる//
	 class MemoryManager:public ChCpp::ChCp::InitPack
	{
	public:

		///////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init(unsigned long _UseByteSize = 0xffffffffUL)
		{
			Release();

			if (_UseByteSize <= 0)return;

			PoolSize = _UseByteSize;

			Pool = new char[PoolSize];

			SetInitFlg(true);

		}

		inline void Release()
		{
			if (!*this)return;

			if (PoolSize <= 0)return;

			if (PoolSize == 1)delete Pool;
			if (PoolSize > 1)delete[] Pool;

			SetInitFlg(false);
		}

		///////////////////////////////////////////////////////////////////////////////
		//SetFunction//


	private:

		char* Pool = nullptr;
		unsigned long PoolSize = 0;



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