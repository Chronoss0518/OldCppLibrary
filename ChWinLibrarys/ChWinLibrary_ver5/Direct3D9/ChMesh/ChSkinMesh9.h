
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
				boneList.clear();
				boneNameList.clear();
				tAni.Release();
			}

			///////////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			//XFileよりアニメーションを取得//
			void SetAnimation(
				const std::string& _aniamtionName
				, const std::string& _xFileName);

			//外部で作成したアニメーションをセット//
			void SetAnimation(
				const std::string& _aniamtionName
				, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes)
			{
				animations[_aniamtionName] = _animes;

				if (startPlayAniCheck)return;
				startPlayAniCheck = true;
				nowPlayAniName = _aniamtionName;
			}

			//再生するアニメーションを変更//
			inline void SetPlayAniName(const std::string& _aniName)
			{
				if (animations.find(_aniName) == animations.end())return;


				for (auto&& anis : animations[nowPlayAniName])
				{
					anis.second->Stop();
				}
				nowPlayAniName = _aniName;
				for (auto&& anis : animations[nowPlayAniName])
				{
					anis.second->Play();
				}


			}

			//再生するアニメーションの終了フレーム数を変更//
			inline void SetAniTime(
				const std::string& _aniName
				, const float _playMaxTime)
			{
				if (animations.find(_aniName) == animations.end())
				{
					return;
				}

				for (auto&& anis : animations[_aniName])
				{
					anis.second->SetOneFrameTime(_playMaxTime);
				}
			}

			void SetSkin()override;

			///////////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline std::vector<ChPtr::Shared<std::string>> GetAniNameList()
			{
				std::vector<ChPtr::Shared<std::string>> tmpStr;
				for (auto&& anis : animations)
				{
					auto str = ChPtr::Make_S<std::string>();
					*str = anis.first;
					tmpStr.push_back(str);

				}

				return tmpStr;
			}

			ChMat_9 GetBoneMat(const std::string& _str)override
			{
				if (boneList.find(_str) == boneList.end())return ChMat_9();
				return boneList[_str]->baseMat;
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
					ChMat_9* updateMat;
					ChMat_9* offMat;
					float waitPow = 0.0f;

				};

				ChVec3_9 pos;
				std::vector<ChPtr::Shared<BonePow>>updateMat;
			};

			struct Bone
			{
				ChMat_9 baseMat;
				ChMat_9 updateMat;
				ChMat_9 offMat;
				std::string myName;
				ChPtr::Shared<Bone> offsetBone = nullptr;

			};

			std::string testName = "";

			std::vector<ChPtr::Shared<BoneVertex>>boneVertexList;

			//第一にアニメーション名//
			//第二にBone名を入れる。//
			using BoneAnimation = std::map<std::string, ChPtr::Shared<ChAnimationObject9>>;
			
			std::map<std::string, BoneAnimation> animations;

			std::string nowPlayAniName = "";
			ChStd::Bool startPlayAniCheck = false;

			std::map<std::string, ChPtr::Shared<Bone>> boneList;
			
			std::vector<std::string> boneNameList;

			ChAniObj9 tAni;

		};
	
}

#endif
