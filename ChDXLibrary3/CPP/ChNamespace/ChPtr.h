#ifndef Ch_CPP_Ptr_h
#define Ch_CPP_Ptr_h

#include<memory>
#include"ChStd.h"

//ChLibrary�ŗ��p����|�C���^�ɑ΂��ė��p����֐��A�ϐ��Q�̂܂Ƃ܂�//
namespace ChPtr
{

	//SharedPtr�̊ȗ���//
	template<class T>
	using Shared = std::shared_ptr<T>;

	//UniquePtr�̊ȗ���//
	template<class T>
	using Unique = std::unique_ptr<T>;

	//WeakPtr�̊ȗ���//
	template<class T>
	using Weak = std::weak_ptr<T>;

	//SharedPtr�p�_�E���L���X�g//
	template<class C, class C2>
	inline Shared<C> SharedSafeCast(const Shared<C2> _SPtr)
	{
		return std::dynamic_pointer_cast<C, C2>(_SPtr);
	}

	//*Ptr�p�_�E���L���X�g//
	template<class C, class C2>
	inline C* SafeCast(const C2*_Ptr)
	{
		auto Ptr = const_cast<C2*>(_Ptr);

		return dynamic_cast<C*>(Ptr);
	}

	//�N���X��NULL�܂���nullptr�����`�F�b�N����֐�//
	template<class C>
	inline auto NullCheck(const C _Class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type
	{
		if (_Class == NULL || _Class == nullptr)return ChStd::True;
		return ChStd::False;
	}

	//�N���X��NULL��nullptr�̂ǂ���ł��Ȃ������`�F�b�N����֐�//
	template<class C>
	inline auto NotNullCheck(const C _Class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type

	{
		if (_Class != NULL && _Class != nullptr)return ChStd::True;
		return ChStd::False;
	}
	//�N���X�����S�ɏ�������֐�//
	template<class C>
	inline auto SafeRelease(C& _Class)->typename 
		std::enable_if<std::is_pointer<C>::value, void>::type

	{
		if (NullCheck(_Class))return;
		unsigned long i = sizeof(_Class);
		i = sizeof(_Class[0]);
		if (sizeof(_Class) <= sizeof(_Class[0]))delete _Class;
		else delete[] _Class;

		_Class = nullptr;
	}

	//make_shared��Z�k���邽�߂̊֐�//
	template<class T, class... _Types>
	inline Shared<T> Make_S(_Types&&... _Args)
	{
		return std::make_shared<T>(_Args...);
	}

	//make_unique��Z�k���邽�߂̊֐�//
	template<class T, class... _Types>
	inline Unique<T> Make_U(_Types&&... _Args)
	{
		return std::make_unique<T>(_Args...);
	}

	//move_ptr��Z�k���邽�߂̊֐�//
	template<class T>
	inline T Move(T _Obj)
	{
		return std::move_ptr<T>(_Obj);
	}

	//�����������S�ɉ������֐�//
	//
	template<class T>
	inline void MemoryRelease(
		T* _ReleaseMemory 
		, const unsigned long _Num = 1)
	{
		if (_Num <= 0)return;

		if (_Num <= 1)
		{
			delete _ReleaseMemory;
		}
		else
		{
			delete[] _ReleaseMemory;
		}
		_ReleaseMemory = nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	template<class T = int>
	class Ptr
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//Operator//

		T& operator *()
		{
			return *Instance;
		}

		T* const operator ->()
		{
			return Instance;
		}

		operator const T*()const
		{
			return Instance;
		}

		operator bool()const
		{
			return ChPtr::NotNullCheck(Instance);
		}

		template<class CC
			=std::enable_if<std::is_base_of<T,CC>::value>::type>
		Ptr<T>& operator=(Ptr<CC> _Obj)
		{
			this->Instance = _Obj->Instance;
			this->LookCnt = _Obj->LookCnt;

			LookCnt++;

			return *this;
		}


		std::nullptr_t operator=(std::nullptr_t _Nulls)
		{
			if (!*this)return nullptr;
			*LookCnt -= 1;
			if (*LookCnt > 0)return nullptr;

			delete Instance;
			Instance = nullptr;

			delete LookCnt;
			LookCnt = nullptr;

			return nullptr;
		}


		~Ptr<T>()
		{
			Release();
		}

		template<
			class CC
			= std::enable_if<std::is_base_of<T, CC>::value, CC>::type
			, class... _Types>
		void Makes
			(_Types&&... _Args)
		{
			Release();
			Instance = nullptr;
			LookCnt = nullptr;

			Instance = new CC(_Args...);
			LookCnt = new unsigned long(1);
		}

		void Release()
		{
			if (!*this)return;
			*this = nullptr;
		}

	private:

		T* Instance;
		unsigned long* LookCnt;

	};


}

#endif
