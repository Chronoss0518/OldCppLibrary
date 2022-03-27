#ifndef Ch_CPP_Ptr_h
#define Ch_CPP_Ptr_h

#ifndef MEMORY_
#include<memory>
#endif

#ifndef Ch_CPP_Std_h
#include"ChStd.h"
#endif

//ChLibraryで利用するポインタに対して利用する関数、変数群のまとまり//
namespace ChPtr
{

	//SharedPtrの簡略版//
	template<class T>
	using Shared = std::shared_ptr<T>;

	//UniquePtrの簡略版//
	template<class T>
	using Unique = std::unique_ptr<T>;

	//WeakPtrの簡略版//
	template<class T>
	using Weak = std::weak_ptr<T>;

	//SharedPtr用ダウンキャスト//
	template<class C, class C2>
	static inline Shared<C> SharedSafeCast(Shared<C2> _sPtr)
	{
		return std::dynamic_pointer_cast<C, C2>(_sPtr);
	}

	//*Ptr用ダウンキャスト//
	template<class C, class C2>
	static inline C* SafeCast(C2*_ptr)
	{
		return dynamic_cast<C*>(_ptr);
	}

	//クラスがNULLまたはnullptrかをチェックする関数//
	template<class C>
	static inline auto NullCheck(const C _class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type
	{
		if (_class == NULL) return true;
		if (_class == nullptr)return true;
		return false;
	}

	//クラスがNULLとnullptrのどちらでもないかをチェックする関数//
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

	//make_sharedを短縮するための関数//
	template<class T, class... _Types>
	static inline Shared<T> Make_S(_Types&&... _args)
	{
		return std::make_shared<T>(_args...);
	}

	//make_uniqueを短縮するための関数//
	template<class T, class... _Types>
	static inline Unique<T> Make_U(_Types&&... _args)
	{
		return std::make_unique<T>(_args...);
	}

	//move_ptrを短縮するための関数//
	template<class T>
	static inline T Move(T _obj)
	{
		return std::move<T>(_obj);
	}

	///////////////////////////////////////////////////////////////////////////////////////


}

#endif
