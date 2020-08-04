#ifndef Ch_CPP_Ptr_h
#define Ch_CPP_Ptr_h

#ifndef MEMORY_
#include<memory>
#endif

#ifndef Ch_CPP_Std_h
#include"ChStd.h"
#endif

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
	static inline Shared<C> SharedSafeCast(Shared<C2> _SPtr)
	{
		return std::dynamic_pointer_cast<C, C2>(_SPtr);
	}

	//*Ptr�p�_�E���L���X�g//
	template<class C, class C2>
	static inline C* SafeCast(C2*_Ptr)
	{
		auto Ptr = const_cast<C2*>(_Ptr);

		return dynamic_cast<C*>(Ptr);
	}

	//�N���X��NULL�܂���nullptr�����`�F�b�N����֐�//
	template<class C>
	static inline auto NullCheck(const C _Class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type
	{
		if (_Class == NULL || _Class == nullptr)return ChStd::True;
		return ChStd::False;
	}

	//�N���X��NULL��nullptr�̂ǂ���ł��Ȃ������`�F�b�N����֐�//
	template<class C>
	static inline auto NotNullCheck(const C _Class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type
	{
		if (_Class != NULL && _Class != nullptr)return ChStd::True;
		return ChStd::False;
	}

	//make_shared��Z�k���邽�߂̊֐�//
	template<class T, class... _Types>
	static inline Shared<T> Make_S(_Types&&... _Args)
	{
		return std::make_shared<T>(_Args...);
	}

	//make_unique��Z�k���邽�߂̊֐�//
	template<class T, class... _Types>
	static inline Unique<T> Make_U(_Types&&... _Args)
	{
		return std::make_unique<T>(_Args...);
	}

	//move_ptr��Z�k���邽�߂̊֐�//
	template<class T>
	static inline T Move(T _Obj)
	{
		return std::move<T>(_Obj);
	}

	//�����������S�ɉ������֐�//
	//
	template<class T>
	static inline void MemoryRelease(
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

	template<class T>
	class CPtr
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//Operator//

		inline T& operator *()
		{
			return *Instance;
		}

		inline T* const operator ->()
		{
			return Instance;
		}

		inline T const * const operator ->()const
		{
			return Instance;
		}

		inline operator bool()const
		{
			return ChPtr::NotNullCheck(Instance);
		}

		template<class CC>
		inline CPtr<typename std::enable_if<std::is_base_of<T,CC>::value,T>::type>& operator=(CPtr<CC> _Obj)
		{
			Release();

			Instance = _Obj->Instance;
			LookCnt = _Obj->LookCnt;

			if (!*this)return *this;

			LookCnt++;

			return *this;
		}

		inline CPtr<T> operator=(const std::nullptr_t _Nulls)
		{
			if (!*this)return *this;
			*LookCnt -= 1;
			if (*LookCnt > 0)
			{
				Instance = nullptr;
				return nullptr;
			}

			delete Instance;
			Instance = nullptr;

			delete LookCnt;
			LookCnt = nullptr;

			return *this;
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		template<class CC>
		inline CPtr<T>(
			const CPtr
			<typename std::enable_if
			<std::is_base_of<T, CC>::value, CC>::type>
			& _Ptr)
		{
			*this = _Ptr;
		}

		template<class CC, class... _Types>
		inline CPtr<T>(_Types&&... _Args)
		{
			Release();

			Instance = nullptr;
			LookCnt = nullptr;

			Instance = new CC(_Args...);
			LookCnt = new unsigned long(1);
		}

		inline CPtr<T>(const  CPtr<T>& _Null) { *this = _Null; }

		inline CPtr<T>(const std::nullptr_t& _Null) { Release(); }

		inline CPtr<T>() { Release(); }

		inline ~CPtr<T>()
		{
			Release();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Release()
		{
			if (!*this)return;
			(*this) = nullptr;
		}

		///////////////////////////////////////////////////////////////////////////////////////

		template<class CC = T, class... _Types>
		inline auto Makes
			(_Types&&... _Args)->typename std::enable_if<std::is_base_of<T, CC>::value, void>::type
		{
			Release();

			Instance = nullptr;
			LookCnt = nullptr;

			Instance = new CC(_Args...);
			LookCnt = new unsigned long(1);
		}

	private:

		T* Instance = nullptr;
		unsigned long* LookCnt = nullptr;

	};


	///////////////////////////////////////////////////////////////////////////////////////

	template<class T, class... _Types>
	static inline CPtr<T> Make_CPtr(_Types&&... _Args)
	{
		CPtr<T> Tmp = CPtr<T>(_Args...);
		return Tmp;
	}

	template<class T,class B>
	static inline CPtr<T>&
		Dynamic_CPtr
		(typename std::enable_if
			<std::is_base_of<B, T>::value, CPtr<B>>::type& _Base
		)
	{
		CPtr<T> Tmp;
		Tmp = _Base;
		Tmp->Instance = nullptr;
		Tmp->Instance = dynamic_cast<T>(_Base->Instance);
		if (Tmp->Instance == nullptr)Tmp.Release();
		return Tmp;
	}


}

#endif
