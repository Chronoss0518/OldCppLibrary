#ifndef Ch_CPP_ColObj_h
#define Ch_CPP_ColObj_h

#include"../ChBitBool/ChBitBool.h"

namespace ChCpp
{
	class BoxCollider;
	class SphereCollider;

	class BaseCollider;

	struct HitData
	{
		BaseCollider* HitObject;
		ChVec3 HitVector;

	};

	class BaseCollider:public ChCp::Releaser
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPos(const ChVec3& _Pos) { Pos = _Pos; }

		void SetIfIsHitObject(BaseCollider* _Obj);

		void SetTypeName(const std::string& _TName) { TypeName = _TName; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChVec3 GetPos() { return Pos; }

		std::string GetTypeName() { return TypeName; }

		virtual float GetMaxLen() = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void StartUp(){}

		///////////////////////////////////////////////////////////////////////////////////////

		void Update();

		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void EndStep(){}

		///////////////////////////////////////////////////////////////////////////////////////

		//ColliderManagerへ追加する//
		void AddColliders();

		///////////////////////////////////////////////////////////////////////////////////////

		template<class Colllider = BoxCollider>
		void HitTestFunction(typename std::enable_if<std::is_base_of<BaseCollider, Colllider>::value
			&& !std::is_same<BaseCollider, Colllider>::value
			, BaseCollider>::type* _Col)
		{
			auto Col = dynamic_cast<Colllider*>(_Col);

			if (ChPtr::NullCheck(Col))return;

			auto Obj = HitTest(Col);

			if (ChPtr::NullCheck(Obj))return;

		}

	protected:

		virtual BaseCollider* HitTest(BoxCollider* _Box) = 0;

		virtual BaseCollider* HitTest(SphereCollider* _Sphere) = 0;

		virtual ChVec3 HitVector(BoxCollider* _Col) = 0;

		virtual ChVec3 HitVector(SphereCollider* _Col) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		BaseCollider(){}

	private:

		std::vector<BaseCollider*>HitTestObjects;
		
		std::string TypeName = "";

		ChVec3 Pos;
		
	};

	class ColliderManager
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////

		void AddCollider(BaseCollider* _CObj) 
		{
			if (ChPtr::NullCheck(_CObj))return;

			Collisions.push_back(_CObj); 
		}

		///////////////////////////////////////////////////////////////////////////////////////

		void Update();

		///////////////////////////////////////////////////////////////////////////////////////

	private:

		std::vector<BaseCollider*>Collisions;

		ColliderManager() {};
		~ColliderManager() {}

	public:

		inline static ColliderManager& GetIns()
		{
			static ColliderManager Ins;
			return Ins;
		}

	};

	static auto ColManager = ColliderManager::GetIns;

	class BoxCollider:public BaseCollider
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//中央からのx,y,z方向を表した数値//
		inline void SetSizeVec(const ChVec3& _Vec) { SizeVector = _Vec; }

		inline void SetRotVec(const ChVec3& _Rot) { RotationData = _Rot; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		virtual float GetMaxLen()override
		{
			return SizeVector.Len();
		}

		//中央からのx,y,z方向を表した数値//
		virtual ChVec3 GetSizeVec() { return SizeVector; }

		virtual ChVec3 GetRotVec() { return RotationData; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		virtual BaseCollider* HitTest(BoxCollider* _Box)override;

		virtual ChVec3 HitVector(BoxCollider* _Col)override;

		virtual BaseCollider* HitTest(SphereCollider* _Sphere)override;

		virtual ChVec3 HitVector(SphereCollider* _Col)override;

		///////////////////////////////////////////////////////////////////////////////////////

	private:


		//中央からのx,y,z方向を表した数値//
		ChVec3 SizeVector;

		ChVec3 RotationData;

	};

	class SphereCollider :public BaseCollider
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetLen(const float _Len) { Len = _Len; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		virtual float GetMaxLen()override
		{
			return Len;
		}

		inline float GetLen() { return Len; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		virtual BaseCollider* HitTest(BoxCollider* _Box)override;

		virtual ChVec3 HitVector(BoxCollider* _Col)override;

		virtual BaseCollider* HitTest(SphereCollider* _Sphere)override;

		virtual ChVec3 HitVector(SphereCollider* _Col)override;

		///////////////////////////////////////////////////////////////////////////////////////

	private:

		float Len = 0.0f;

	};


}

#endif