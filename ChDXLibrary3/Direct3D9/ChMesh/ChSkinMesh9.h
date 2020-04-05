
#ifndef Ch_D3D9_SkMe_h
#define Ch_D3D9_SkMe_h

#include"ChBaseMesh9.h"

typedef class ChAnimationObject9 ChAniObj9;

namespace ChMesh
{

		class SkinMesh9 :public BaseMesh9
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////////
			//ConstructerDestructer//

			virtual ~SkinMesh9()
			{
				BoneList.clear();
				BoneNameList.clear();
				TAni.Release();
			}

			///////////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			//XFileよりアニメーションを取得//
			void SetAnimation(
				const std::string& _AniamtionName
				, const std::string& _XFileName);

			//外部で作成したアニメーションをセット//
			void SetAnimation(
				const std::string& _AniamtionName
				, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _Animes)
			{
				Animations[_AniamtionName] = _Animes;

				if (StartPlayAniCheck)return;
				StartPlayAniCheck = true;
				NowPlayAniName = _AniamtionName;
			}

			//再生するアニメーションを変更//
			inline void SetPlayAniName(const std::string& _AniName)
			{
				if (Animations.find(_AniName) == Animations.end())return;


				for (auto&& Anis : Animations[NowPlayAniName])
				{
					Anis.second->Stop();
				}
				NowPlayAniName = _AniName;
				for (auto&& Anis : Animations[NowPlayAniName])
				{
					Anis.second->Play();
				}


			}

			//再生するアニメーションの終了フレーム数を変更//
			inline void SetAniTime(
				const std::string& _AniName
				, const float _PlayMaxTime)
			{
				if (Animations.find(_AniName) == Animations.end())
				{
					return;
				}

				for (auto&& Anis : Animations[_AniName])
				{
					Anis.second->SetOneFrameTime(_PlayMaxTime);
				}
			}

			void SetSkin()override;

			///////////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline std::vector<ChPtr::Shared<std::string>> GetAniNameList()
			{
				std::vector<ChPtr::Shared<std::string>> TmpStr;
				for (auto&& Anis : Animations)
				{
					auto Str = ChPtr::Make_S<std::string>();
					*Str = Anis.first;
					TmpStr.push_back(Str);

				}

				return TmpStr;
			}

			ChMat_9 GetBoneMat(const std::string& _Str)override
			{
				if (BoneList.find(_Str) == BoneList.end())return ChMat_9();
				return BoneList[_Str]->BaseMat;
			}

			///////////////////////////////////////////////////////////////////////////////////////

			friend MeshManager9;
			friend MeshList9;


		protected:


			///////////////////////////////////////////////////////////////////////////////////////
			
			void SetOffsetVertex()override;

			///////////////////////////////////////////////////////////////////////////////////////

			struct BoneVertex
			{
				struct BonePow
				{
					ChMat_9* EndUpdateMat;
					float WaitPow = 0.0f;

				};

				ChVec3_9 Pos;
				std::vector<ChPtr::Shared<BonePow>>UpdateMat;
			};

			struct Bone
			{
				ChMat_9 BaseMat;
				ChMat_9 UpdateMat;
				ChMat_9 EndUpdateMat;
				ChMat_9 OffMat;
				std::string MyName;
				ChPtr::Shared<Bone> OffsetBone = nullptr;

			};

			std::string TestName = "";

			std::vector<ChPtr::Shared<BoneVertex>>BoneVertexList;

			//第一にアニメーション名//
			//第二にBone名を入れる。//
			using BoneAnimation = std::map<std::string, ChPtr::Shared<ChAnimationObject9>>;
			
			std::map<std::string, BoneAnimation> Animations;

			std::string NowPlayAniName = "";
			ChStd::Bool StartPlayAniCheck = false;

			std::map<std::string, ChPtr::Shared<Bone>> BoneList;
			
			std::vector<std::string> BoneNameList;

			ChAniObj9 TAni;

		};
	
}

#endif
