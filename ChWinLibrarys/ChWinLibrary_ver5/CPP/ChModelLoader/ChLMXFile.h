#ifndef Ch_CPP_XMesh_h
#define Ch_CPP_XMesh_h

#ifndef Ch_CPP_MLoader_h
#include"ChModelLoader.h"
#endif


namespace ChCpp
{

	namespace ModelLoader
	{

		class XFile :public ModelLoaderBase
		{
		protected:

			struct XFileModelFrame
			{

				struct XVertex
				{
					ChVec3 pos;
					ChVec3 normal;
					ChVec2 uvPos;
				};

				struct XMaterial
				{
					std::string materialName;

					ChVec4 diffuse;
					float specularPower = 0.0f;
					ChVec3 specular;
					ChVec3 ambient;

					std::vector<std::string>textureNameList;

				};

				struct XFace
				{
					std::vector<unsigned long> vertexNos;
					unsigned long mateNo = 0;
				};

				struct XSkinWeights
				{
					std::string targetFrameName = "";

					std::map<unsigned long, float>weitPow;

					ChLMat boneOffset;

				};
				struct XMesh
				{
					std::vector<ChPtr::Shared<XVertex>>vertexList;
					std::vector<ChPtr::Shared<XMaterial>>materialList;
					std::vector<ChPtr::Shared<XFace>>faceList;
				};

				struct XFrame
				{
					std::string fName;
					ChPtr::Shared<XMesh> mesh;
					std::vector<ChPtr::Shared<XFrame>>next;
					std::vector<ChPtr::Shared<XSkinWeights>>skinWeightDatas;
					ChLMat frameMatrix;
				};


				ChPtr::Shared<XFrame> modelData = nullptr;
				std::string modelName;

			};

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
				size_t begin = 0;
				size_t end = 0;
				std::vector<ChPtr::Shared<TemplateRange>> nest;
			};

			//モデルデータの読み込み口//
			void CreateModel(const std::string& _filePath)override;

			///////////////////////////////////////////////////////////////////////////////////////

			//ChModelへ変換//
			void XFrameToChFrame(
				ChPtr::Shared<ModelFrame::Frame>& _chFrame
				, const ChPtr::Shared<XFileModelFrame::XFrame>& _xFrame);

			///////////////////////////////////////////////////////////////////////////////////////

			void OutModelFile(const std::string& _filePath)override;

			///////////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			ChStd::Bool SetFrame(
				ChPtr::Shared<XFileModelFrame::XFrame>& _frames
				, const ChPtr::Shared<TemplateRange>& _targetTemplate
				, const std::string& _text);

			ChStd::Bool SetFremeTransformMatrix(
				ChPtr::Shared<XFileModelFrame::XFrame>& _frames
				, const ChPtr::Shared<TemplateRange>& _targetTemplate
				, const std::string& _text);

			ChStd::Bool SetMesh(
				ChPtr::Shared<XFileModelFrame::XFrame>& _frames
				, const ChPtr::Shared<TemplateRange>& _targetTemplate
				, const std::string& _text);

			ChStd::Bool SetMeshNormal(
				ChPtr::Shared<XFileModelFrame::XFrame>& _frames
				, const ChPtr::Shared<TemplateRange>& _targetTemplate
				, const std::string& _text);

			ChStd::Bool SetMeshTextureCoords(
				ChPtr::Shared<XFileModelFrame::XFrame>& _frames
				, const ChPtr::Shared<TemplateRange>& _targetTemplate
				, const std::string& _text);

			ChStd::Bool SetMeshMaterialList(
				ChPtr::Shared<XFileModelFrame::XFrame>& _frames
				, const ChPtr::Shared<TemplateRange>& _targetTemplate
				, const std::string& _text);

			ChStd::Bool SetMaterial(
				ChPtr::Shared<XFileModelFrame::XFrame>& _frames
				, const ChPtr::Shared<TemplateRange>& _targetTemplate
				, const std::string& _text);

			ChStd::Bool SetSkinWeights(
				ChPtr::Shared<XFileModelFrame::XFrame>& _frames
				, const ChPtr::Shared<TemplateRange>& _targetTemplate
				, const std::string& _text);

			///////////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			template<class T>
			auto GetArrayValues(
				const std::string& _text
				, const size_t& _startPos = 0
				, const std::string& _cutChar = ","
				, const std::string& _endChar = ";"
			)->typename std::enable_if
				<std::is_base_of<BaseType, T>::value
				, std::vector<ChPtr::Shared<T>>>::type
			{

				std::vector<ChPtr::Shared<T>> out;

				std::string useText = "";

				{
					size_t tmpEnd = _text.find(_endChar, _startPos);
					tmpEnd += _endChar.length();

					useText = _text.substr(_startPos, tmpEnd - _startPos);

				}

				size_t tmpPos = 0;
				tmpPos = useText.find(";");

				if (tmpPos >= useText.size())return out;

				unsigned long arrayCount = 0;

				arrayCount = ChStr::GetIntegialFromText<unsigned long>(useText, useText.find("\n"), tmpPos);

				if (arrayCount <= 0)return out;

				for (unsigned long i = 0; i < arrayCount; i++)
				{

					size_t sPos = tmpPos + 1;

					tmpPos = useText.find(_cutChar, sPos);
					std::string tmpEnd = _cutChar;

					if (i >= arrayCount - 1)
					{
						tmpPos = useText.find(_endChar, sPos);
						tmpEnd = _endChar;
					}

					if (tmpPos >= std::string::npos)
					{
						out.clear();
						return out;
					}


					ChPtr::Shared<BaseType> value = ChPtr::Make_S<T>();

					value->Desirialise(useText, sPos, tmpEnd);

					out.push_back(ChPtr::SharedSafeCast<T>(value));

					tmpPos += _endChar.length();

				}

				return out;

			}

			template<class T>
			auto GetArrayValuesNC(
				const std::string& _text
				, const size_t& _startPos = 0
				, const std::string& _cutChar = ","
				, const std::string& _endChar = ";"
			)->typename std::enable_if
				<std::is_base_of<BaseType, T>::value
				, std::vector<ChPtr::Shared<T>>>::type
			{

				std::vector<ChPtr::Shared<T>> out;

				std::string useText = "";

				{
					size_t tmpEnd = _text.find(_endChar, _startPos);
					tmpEnd += _endChar.length();

					useText = _text.substr(_startPos, tmpEnd - _startPos);

				}

				size_t tmpPos = 0;

				if (tmpPos >= useText.size())return out;

				while (tmpPos <= useText.size())
				{

					size_t sPos = tmpPos + 1;

					tmpPos = useText.find(_cutChar, sPos);
					std::string tmpEnd = _cutChar;

					if (tmpPos >= useText.size())
					{
						tmpPos = useText.find(_endChar, sPos);
						tmpEnd = _endChar;
					}


					ChPtr::Shared<BaseType> value = ChPtr::Make_S<T>();

					value->Desirialise(useText, sPos, tmpEnd);

					out.push_back(ChPtr::SharedSafeCast<T>(value));

					tmpPos += _endChar.length();

					if (tmpEnd == ";")break;

				}


				return out;

			}

			///////////////////////////////////////////////////////////////////////////////////////
			//IsFunction//

			ChStd::Bool IsTags(
				size_t& _outTagPos
				, const std::string& _tagName
				, const ChPtr::Shared<TemplateRange> _lookTemplate
				, const std::string& _text);

			inline ChStd::Bool IsTags(
				const std::string& _tagName
				, const ChPtr::Shared<TemplateRange> _lookTemplate
				, const std::string& _text)
			{

				size_t tmp;

				return IsTags(tmp, _tagName, _lookTemplate, _text);
			}

			///////////////////////////////////////////////////////////////////////////////////////
			//TmplateCreate//

			void LoadToTemplates(
				ChPtr::Shared<TemplateRange>& _templates
				, const size_t& _offset
				, const std::string& _text);

			void SetToTemplate(
				ChPtr::Shared<TemplateRange>& _tmp
				, size_t& _bCnt
				, size_t& _eCnt
				, const std::vector<size_t>& _sTemplateTags
				, const std::vector<size_t>& _eTemplateTags);


			///////////////////////////////////////////////////////////////////////////////////////
			//XFileBaseTypes//

			struct XDWORD : public BaseType
			{
				void Desirialise(
					const std::string& _text
					, const size_t& _start
					, const std::string& _endChar)override
				{

					size_t Tmp = _text.find(_endChar, _start);

					value = ChStr::GetIntegialFromText<unsigned long>(_text, _start, Tmp);
				}

				std::string Serialise()override
				{

					return "";
				}

				unsigned long value = 0;
			};

			struct XCHAR : public BaseType
			{
				void Desirialise(
					const std::string& _text
					, const size_t& _start
					, const std::string& _endChar)override
				{

					size_t Tmp = _text.find(_endChar, _start);

					value = ChStr::GetIntegialFromText<unsigned char>(_text, _start, Tmp);
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
					const std::string& _text
					, const size_t& _start
					, const std::string& _endChar)override
				{

					size_t tmp = _text.find(_endChar, _start);

					value = ChStr::GetFloatingFromText<float>(_text, _start, tmp);
				}

				std::string Serialise()override
				{

					return "";
				}

				float value = 0.0f;
			};

			struct XVECTOR : public BaseType
			{
				void Desirialise(
					const std::string& _text
					, const size_t& _start
					, const std::string& _endChar)override
				{
					value.Deserialize(_text, _start, ";", _endChar);
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
					const std::string& _text
					, const size_t& _start
					, const std::string& _endChar)override
				{
					value.Deserialize(_text, _start, ";", _endChar);
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
					const std::string& _text
					, const size_t& _start
					, const std::string& _endChar)override
				{


					size_t end = _text.find(_endChar, _start);

					std::string useText = _text.substr(_start, end - _start);


					size_t tmpPos = 0;
					tmpPos = useText.find(";");

					if (tmpPos >= end)return;

					unsigned long arrayCount = 0;

					arrayCount = ChStr::GetIntegialFromText<unsigned long>(useText, 0, tmpPos);

					if (arrayCount <= 0)return;

					for (unsigned long i = 0; i < arrayCount; i++)
					{

						size_t sPos = tmpPos + 1;
						tmpPos = useText.find(",", sPos + 1);

						if (i >= arrayCount - 1)
						{
							tmpPos = useText.find(";", sPos);
						}

						if (tmpPos >= std::string::npos)
						{
							tmpPos = useText.size();
						}

						unsigned long Value;

						Value = ChStr::GetIntegialFromText<unsigned long>(useText, sPos, tmpPos);

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
					const std::string& _text
					, const size_t& _start
					, const std::string& _endChar)override
				{
					value.Deserialize(_text, _start, ";", _endChar);
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
					const std::string& _text
					, const size_t& _start
					, const std::string& _endChar)override
				{
					value.Deserialize(_text, _start, ";", _endChar);
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

			const std::string frameTags = "Frame ";

			const std::string frameTransformMatrixTags = "FrameTransformMatrix ";

			const std::string meshTags = "Mesh ";

			const std::string normalTags = "MeshNormals ";

			const std::string materialListTags = "MeshMaterialList ";

			const std::string materialTags = "Material ";

			const std::string skinWeightsTags = "SkinWeights ";

			const std::string uvTags = "MeshTextureCoords ";

			const std::string textureFileNameTag = "TextureFilename ";

			const std::string skinWeightsTag = "SkinWeights ";
		};

	}

}

#endif