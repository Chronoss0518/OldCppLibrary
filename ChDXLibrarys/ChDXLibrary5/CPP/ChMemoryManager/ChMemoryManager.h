#ifndef Ch_Game_MeMa_h
#define Ch_Game_MeMa_h

namespace ChCpp
{

	//�|�C���^�[�Ŏg�p���郁�����S�̂��Ǘ�����N���X//
	//�Z�b�g�ł���N���X��\���̂ɂ�//
	//�R���X�g���N�^�[���̈�����K�v�Ƃ��Ȃ����̂̂ݗ��p�ł���//
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