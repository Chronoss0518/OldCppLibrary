#ifndef Ch_CPP_XMesh_h
#define Ch_CPP_XMesh_h

#include"ChModelCreater.h"

namespace ChCpp
{
	class CMXFile :public ModelCreater
	{
	protected:

		struct XVertex;
		struct XMaterial;
		struct XFace;
		struct XSkinWeight;
		struct XMesh;
		struct XFrame;

		struct BaseType
		{
			virtual void Desirialise(
				const std::string& _Text
				, const size_t& _Start
				, const std::string& _EndChar) = 0;

			virtual std::string Serialise() = 0;
		};

		struct TemplateRange
		{
			size_t Bigen = 0;
			size_t End = 0;
			std::vector<ChPtr::Shared<TemplateRange>> Nest;
		};

		//モデルデータの読み込み口//
		void CreateMesh(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////

		//ChModelへ変換//
		void XModelToChModel(
			ChPtr::Shared<BaseModel>& _ChModel
			,const ChPtr::Shared<XFrame>& _XModel);

		void XFrameToChFrame(
			ChPtr::Shared<BaseModel::Frame>& _ChFrame
			, const ChPtr::Shared<XFrame>& _XFrame);

		///////////////////////////////////////////////////////////////////////////////////////

		void OutMeshFile(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		ChStd::Bool SetFrame(
			ChPtr::Shared<XFrame>& _Frames
			, const ChPtr::Shared<TemplateRange>& _TargetTemplate
			, const std::string& _Text);

		ChStd::Bool SetFremeTransformMatrix(
			ChPtr::Shared<XFrame>& _Frames
			, const ChPtr::Shared<TemplateRange>& _TargetTemplate
			, const std::string& _Text);
		
		ChStd::Bool SetMesh(
			ChPtr::Shared<XFrame>& _Frames
			, const ChPtr::Shared<TemplateRange>& _TargetTemplate
			, const std::string& _Text);

		ChStd::Bool SetMeshNormal(
			ChPtr::Shared<XFrame>& _Frames
			, const ChPtr::Shared<TemplateRange>& _TargetTemplate
			, const std::string& _Text);

		ChStd::Bool SetMeshTextureCoords(
			ChPtr::Shared<XFrame>& _Frames
			, const ChPtr::Shared<TemplateRange>& _TargetTemplate
			, const std::string& _Text);

		ChStd::Bool SetMeshMaterialList(
			ChPtr::Shared<XFrame>& _Frames
			, const ChPtr::Shared<TemplateRange>& _TargetTemplate
			, const std::string& _Text);

		ChStd::Bool SetMaterial(
			ChPtr::Shared<XFrame>& _Frames
			, const ChPtr::Shared<TemplateRange>& _TargetTemplate
			, const std::string& _Text);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		template<class T>
		auto GetArrayValues(
			const std::string& _Text
			, const size_t& _StartPos = 0
			, const std::string& _CutChar = ","
			, const std::string& _EndChar = ";"
		)->typename std::enable_if
			<std::is_base_of<BaseType, T>::value
			, std::vector<ChPtr::Shared<T>>>::type
		{

			std::vector<ChPtr::Shared<T>> Out;

			std::string UseText = "";

			{
				size_t tmpEnd = _Text.find(_EndChar, _StartPos);
				tmpEnd += _EndChar.length();

				UseText = _Text.substr(_StartPos, tmpEnd - _StartPos);
			
			}

			size_t TmpPos = 0;
			TmpPos = UseText.find(";");

			if (TmpPos >= UseText.size())return Out;

			unsigned long ArrayCount = 0;

			ArrayCount = ChStd::GetIntegialFromText<unsigned long>(UseText, UseText.find("\n"),TmpPos);

			if (ArrayCount <= 0)return Out;

			for (unsigned long i = 0; i < ArrayCount; i++)
			{
				
				size_t SPos = TmpPos + 1;

				TmpPos = UseText.find(_CutChar, SPos);
				std::string tmpEnd = _CutChar;

				if (i >= ArrayCount - 1)
				{
					TmpPos = UseText.find(_EndChar, SPos);
					tmpEnd = _EndChar;
				}

				if (TmpPos >= std::string::npos)
				{
					Out.clear();
					return Out;
				}


				ChPtr::Shared<BaseType> Value = ChPtr::Make_S<T>();

				Value->Desirialise(UseText, SPos, tmpEnd);

				Out.push_back(ChPtr::SharedSafeCast<T>(Value));

				TmpPos += _EndChar.length();

			}

			return Out;

		}

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		ChStd::Bool IsTags(
			size_t& _OutTagPos
			, const std::string& _TagName
			, const ChPtr::Shared<TemplateRange> _LookTemplate
			, const std::string& _Text);

		inline ChStd::Bool IsTags(
			const std::string& _TagName
			, const ChPtr::Shared<TemplateRange> _LookTemplate
			, const std::string& _Text)
		{

			size_t Tmp;

			return IsTags(Tmp, _TagName, _LookTemplate, _Text);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//TmplateCreate//

		void LoadToTemplates(
			ChPtr::Shared<TemplateRange>& _Templates
			, const size_t& _Offset
			, const std::string& _Text);

		void SetToTemplate(
			ChPtr::Shared<TemplateRange>& _Tmp
			, size_t& _BCnt
			, size_t& _ECnt
			, const std::vector<size_t>& _STemplateTags
			, const std::vector<size_t>& _ETemplateTags);

		///////////////////////////////////////////////////////////////////////////////////////
		//XfileStructers//

		struct XVertex
		{
			ChVec3 Pos;
			ChVec3 Normal;
			ChVec2 UVPos;
		};

		struct XMaterial
		{
			std::string MaterialName;

			ChVec4 Diffuse;
			float SpecularPower;
			ChVec3 Specular;
			ChVec3 Ambient;

			std::vector<std::string>TetureNameList;

		};

		struct XFace
		{
			std::vector<unsigned long> VertexNos;
			unsigned long MateNo = 0;
		};

		struct XSkinWeight
		{
			std::string ArmatureName;
			std::map<unsigned long, float> WeightPow;
			ChLMat OffsetMatrix;
		};

		struct XMesh
		{
			std::vector<ChPtr::Shared<XVertex>>VertexList;
			std::vector<ChPtr::Shared<XMaterial>>MaterialList;
			std::vector<ChPtr::Shared<XFace>>FaceList;
			std::vector<ChPtr::Shared<XSkinWeight>>SkinWeightDatas;
		};

		struct XFrame
		{
			std::string FName;
			ChPtr::Shared<XMesh> Meshs;
			std::vector<ChPtr::Shared<XFrame>>Next;
			ChLMat frameMatrix;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		//XFileBaseTypes//

		struct XDWORD : public BaseType
		{
			void Desirialise(
				const std::string& _Text
				, const size_t& _Start
				, const std::string& _EndChar)override
			{

				size_t Tmp = _Text.find(_EndChar, _Start);

				value = ChStd::GetIntegialFromText<unsigned long>(_Text, _Start, Tmp);
			}

			std::string Serialise()override
			{

				return "";
			}

			unsigned long value;
		};

		struct XCHAR : public BaseType
		{
			void Desirialise(
				const std::string& _Text
				, const size_t& _Start
				, const std::string& _EndChar)override
			{

				size_t Tmp = _Text.find(_EndChar, _Start);

				value = ChStd::GetIntegialFromText<unsigned char>(_Text, _Start, Tmp);
			}

			std::string Serialise()override
			{

				return "";
			}

			unsigned char value;
		};

		struct XFLOAT : public BaseType
		{
			void Desirialise(
				const std::string& _Text
				, const size_t& _Start
				, const std::string& _EndChar)override
			{

				size_t Tmp = _Text.find(_EndChar, _Start);

				value = ChStd::GetFloatingFromText<float>(_Text, _Start, Tmp);
			}

			std::string Serialise()override
			{

				return "";
			}

			float value;
		};

		struct XVECTOR : public BaseType
		{
			void Desirialise(
				const std::string& _Text
				, const size_t& _Start
				, const std::string& _EndChar)override
			{
				value.Deserialize(_Text, _Start,";", _EndChar);
			}

			std::string Serialise()override
			{
				return "";
			}

			ChVec3 value;

		};

		struct XCOODS2D : public BaseType
		{
			void Desirialise(
				const std::string& _Text
				, const size_t& _Start
				, const std::string& _EndChar)override
			{
				value.Deserialize(_Text, _Start, ";", _EndChar);
			}

			std::string Serialise()override
			{
					return "";
			}

			ChVec2 value;

		};

		struct XMESHFACE : public BaseType
		{
			void Desirialise(
				const std::string& _Text
				, const size_t& _Start
				, const std::string& _EndChar)override
			{


				size_t End = _Text.find(_EndChar, _Start);

				std::string UseText = _Text.substr(_Start, End - _Start);


				size_t TmpPos = 0;
				TmpPos = UseText.find(";");

				if (TmpPos >= End)return;

				unsigned long ArrayCount = 0;

				ArrayCount = ChStd::GetIntegialFromText<unsigned long>(UseText, 0, TmpPos);

				if (ArrayCount <= 0)return;

				for (unsigned long i = 0; i < ArrayCount; i++)
				{

					size_t SPos = TmpPos + 1;
					TmpPos = UseText.find(",", SPos + 1);

					if (i >= ArrayCount - 1)
					{
						TmpPos = UseText.find(";", SPos);
					}

					if (TmpPos >= std::string::npos)
					{
						TmpPos = UseText.size() - 2;
					}

					unsigned long Value;

					Value = ChStd::GetIntegialFromText<unsigned long>(UseText, SPos, TmpPos);

					value.push_back(Value);

				}

			}

			std::string Serialise()override
			{

				return "";
			}

			std::vector<unsigned long> value;

		};

		struct ColorRGBA : public BaseType
		{
			void Desirialise(
				const std::string& _Text
				, const size_t& _Start
				, const std::string& _EndChar)override
			{
				value.Deserialize(_Text, _Start, ";", _EndChar);
			}

			std::string Serialise()override
			{
				return "";
			}

			ChVec4 value;

		};

		struct ColorRGB : public BaseType
		{
			void Desirialise(
				const std::string& _Text
				, const size_t& _Start
				, const std::string& _EndChar)override
			{
				value.Deserialize(_Text, _Start, ";", _EndChar);
			}

			std::string Serialise()override
			{
				return "";
			}

			ChVec3 value;

		};


		///////////////////////////////////////////////////////////////////////////////////////
		
		ChStd::Bool exceptionFlg = false;

		///////////////////////////////////////////////////////////////////////////////////////
		//XFileTemplateNames//

		const std::string FrameTags = "Frame ";

		const std::string FrameTransformMatrixTags = "FrameTransformMatrix ";

		const std::string MeshTags = "Mesh ";

		const std::string NormalTags = "MeshNormals ";

		const std::string MaterialListTags = "MeshMaterialList ";

		const std::string MaterialTags = "Material ";

		const std::string SkinWeightsTags = "SkinWeights ";

		const std::string UVTags = "MeshTextureCoords ";

		const std::string TextureFilenameTag = "TextureFilename ";
	};

}

#endif