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
	static inline Shared<C> SharedSafeCast(Shared<C2> _sPtr)
	{
		return std::dynamic_pointer_cast<C, C2>(_sPtr);
	}

	//*Ptr�p�_�E���L���X�g//
	template<class C, class C2>
	static inline C* SafeCast(C2*_ptr)
	{
		return dynamic_cast<C*>(_ptr);
	}

	//�N���X��NULL�܂���nullptr�����`�F�b�N����֐�//
	template<class C>
	static inline auto NullCheck(const C _class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type
	{
		if (_class == NULL) return true;
		if (_class == nullptr)return true;
		return false;
	}

	//�N���X��NULL��nullptr�̂ǂ���ł��Ȃ������`�F�b�N����֐�//
	template<class C>
	static inline auto NotNullCheck(const C _class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type
	{
		if (_class != NULL)
		{
			if (_class != nullptr)return true;
		}

		return false;
	}

	//make_shared��Z�k���邽�߂̊֐�//
	template<class T, class... _Types>
	static inline Shared<T> Make_S(_Types&&... _args)
	{
		return std::make_shared<T>(_args...);
	}

	//make_unique��Z�k���邽�߂̊֐�//
	template<class T, class... _Types>
	static inline Unique<T> Make_U(_Types&&... _args)
	{
		return std::make_unique<T>(_args...);
	}

	//move_ptr��Z�k���邽�߂̊֐�//
	template<class T>
	static inline T Move(T _obj)
	{
		return std::move<T>(_obj);
	}

	///////////////////////////////////////////////////////////////////////////////////////


}

#endif
