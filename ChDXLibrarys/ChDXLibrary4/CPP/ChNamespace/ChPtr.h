#ifndef Ch_CPP_Ptr_h
#define Ch_CPP_Ptr_h

#include<memory>
#include"ChStd.h"

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
	static inline Shared<C> SharedSafeCast(const Shared<C2> _SPtr)
	{
		return std::dynamic_pointer_cast<C, C2>(_SPtr);
	}

	//*Ptr用ダウンキャスト//
	template<class C, class C2>
	static inline C* SafeCast(const C2*_Ptr)
	{
		auto Ptr = const_cast<C2*>(_Ptr);

		return dynamic_cast<C*>(Ptr);
	}

	//クラスがNULLまたはnullptrかをチェックする関数//
	template<class C>
	static inline auto NullCheck(const C _Class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type
	{
		if (_Class == NULL || _Class == nullptr)return ChStd::True;
		return ChStd::False;
	}

	//クラスがNULLとnullptrのどちらでもないかをチェックする関数//
	template<class C>
	static inline auto NotNullCheck(const C _Class)->typename
		std::enable_if<std::is_pointer<C>::value, ChStd::Bool>::type

	{
		if (_Class != NULL && _Class != nullptr)return ChStd::True;
		return ChStd::False;
	}
	//クラスを安全に消去する関数//
	template<class C>
	static inline auto SafeRelease(C& _Class)->typename
		std::enable_if<std::is_pointer<C>::value, void>::type

	{
		if (NullCheck(_Class))return;
		unsigned long i = sizeof(_Class);
		i = sizeof(_Class[0]);
		if (sizeof(_Class) <= sizeof(_Class[0]))delete _Class;
		else delete[] _Class;

		_Class = nullptr;
	}

	//make_sharedを短縮するための関数//
	template<class T, class... _Types>
	static inline Shared<T> Make_S(_Types&&... _Args)
	{
		return std::make_shared<T>(_Args...);
	}

	//make_uniqueを短縮するための関数//
	template<class T, class... _Types>
	static inline Unique<T> Make_U(_Types&&... _Args)
	{
		return std::make_unique<T>(_Args...);
	}

	//メモリを安全に解放する関数//
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

	template<class T = int>
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

		inline operator const T*()const
		{
			return Instance;
		}

		inline operator bool()const
		{
			return ChPtr::NotNullCheck(Instance);
		}

		template<class CC
			=std::enable_if<std::is_base_of<T,CC>::value>::type>
		inline CPtr<T>& operator=(CPtr<CC> _Obj)
		{
			Release();

			this->Instance = _Obj->Instance;
			this->LookCnt = _Obj->LookCnt;

			LookCnt++;

			return *this;
		}

		inline std::nullptr_t operator=(std::nullptr_t _Nulls)
		{
			if (!*this)return nullptr;
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

			return nullptr;
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		template<
			class CC
			= std::enable_if<std::is_base_of<T, CC>::value, CC>::type>
		inline CPtr<T>(const CPtr<CC>& _Ptr)
		{
			*this = _Ptr;
		}

		inline CPtr<T>(const std::nullptr_t& _Null) { *this = _Null; }

		inline CPtr<T>() {}

		inline ~CPtr<T>()
		{
			Release();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Release()
		{
			if (!*this)return;
			*this = nullptr;
		}

		///////////////////////////////////////////////////////////////////////////////////////

		template<
			class CC
			= std::enable_if<std::is_base_of<T, CC>::value, CC>::type
			, class... _Types>
		inline void Makes
			(_Types&&... _Args)
		{
			Release();

			Instance = nullptr;
			LookCnt = nullptr;

			Instance = new CC(_Args...);
			LookCnt = new unsigned long(1);
		}

	private:

		T* Instance;
		unsigned long* LookCnt;

	};


	///////////////////////////////////////////////////////////////////////////////////////

	template<class T, class... _Types>
	static inline CPtr<T>& MakeCPtr(_Types&&... _Args)
	{
		CPtr<T> Tmp;
		Tmp.Makes<T>(_Args);
		return Tmp;
	}

}

#endif
