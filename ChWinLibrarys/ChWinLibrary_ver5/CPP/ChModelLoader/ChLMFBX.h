#ifndef Ch_CPP_FBXMesh_h
#define Ch_CPP_FBXMesh_h

#ifndef Ch_CPP_MLoader_h
#include"ChModelLoader.h"
#endif


namespace ChCpp
{

	namespace ModelLoader
	{

		class FBX :public ModelLoaderBase
		{
		protected:

			///////////////////////////////////////////////////////////////////////////////////////

			//モデルデータの読み込み口//
			void CreateModel(const std::string& _filePath)override;

			///////////////////////////////////////////////////////////////////////////////////////

			void OutModelFile(const std::string& _filePath)override;

			///////////////////////////////////////////////////////////////////////////////////////

			unsigned long filePos = 0;
			ChStd::Bool errorFlg = false;

			struct BaseType
			{

			};

			struct FBXFloatingByte4 :public BaseType
			{
				float value;
			};

			struct FBXFloatingByte8 :public BaseType
			{
				double value;
			};

			struct FBXIntegerByte2 :public BaseType
			{
				short value;
			};

			struct FBXIntegerByte4 :public BaseType
			{
				long value;
			};

			struct FBXIntegerByte8 :public BaseType
			{
				long value;
			};

			struct FBXIntegerByte1 :public BaseType
			{
				unsigned char value;
			};

			struct FBXString :public BaseType
			{
				std::string value;
			};

			struct FBXBinary :public BaseType
			{
				std::vector<char> value;
			};

			//Binarys//
			struct SpecialDataRecode
			{
				unsigned long length = 0;

				ChPtr::Shared<BaseType> value = nullptr;

			};

			struct ArrayListDataRecord
			{
				unsigned long arrayLen = 0;
				unsigned long encoding = 0;
				unsigned long conpressedLength = 0;

				std::vector<ChPtr::Shared<BaseType>> values;

			};

			struct PropertyRecord
			{
				char type = 0;

				union
				{
					ChPtr::Shared<BaseType> value = nullptr;

					ChPtr::Shared<ArrayListDataRecord> arrayData;
					ChPtr::Shared<SpecialDataRecode> specialData;
				};

				PropertyRecord(){}
				~PropertyRecord() {};
			};

			struct Node
			{
				unsigned long endOffset = 0;
				unsigned long numProperty = 0;
				unsigned long propertyListLen = 0;
				unsigned char nameLen = 0;
				std::string name = "";
				std::vector<ChPtr::Shared<PropertyRecord>> propertys;
				std::vector<ChPtr::Shared<Node>> childNode;
			};

			//Texts//

			struct Objects
			{
				std::string propetyName = "";
				std::string propertyValue = "";
				std::vector<Objects*> childObject;
			};

			void LoadFBXBinary(const std::string& _filePath);

			void BuildBinary(Node& _node,const std::vector<char>& _binarys);
			
			void CreatePropetyRecord(PropertyRecord& _recode, const std::vector<char>& _binarys);

			void CreateArrayRecord(ArrayListDataRecord& _recode, const std::vector<char>& _binarys,const char _type);

			void CreateSpecialTypeRecord(SpecialDataRecode& _recode, const std::vector<char>& _binarys, const char _type);

			void LoadFBXText(const std::string& _filePath);

			void BuildObjects(Objects& _obj);

			template<typename T = unsigned char,class FBXBaseType = FBXIntegerByte1>
			void MakeBaseType(PropertyRecord& _recode,const std::vector<char>& _binarys,unsigned long& _filePos)
			{
				auto tmp = ChPtr::Make_S<FBXBaseType>();

				tmp->value = ChStd::BinaryToNumWithLittleEndian<T>(_binarys, _filePos);

				_filePos += sizeof(T);

				_recode.value = tmp;

			}

			template<typename T = unsigned char, class FBXBaseType = FBXIntegerByte1>
			void MakeArrayType(ArrayListDataRecord& _recode, const std::vector<char>& _binarys, unsigned long& _filePos)
			{
				if (_recode.encoding == 0)
				{
					for (unsigned long i = 0; i < _recode.arrayLen; i++)
					{
						auto tmp = ChPtr::Make_S<FBXBaseType>();

						tmp->value = ChStd::BinaryToNumWithLittleEndian<T>(_binarys, filePos);

						_recode.values.push_back(tmp);

						filePos += sizeof(T);
					}
					return;

				}


				std::vector<char>encordingData;

				for (unsigned long i = 0; i < _recode.conpressedLength; i++)
				{
					
					encordingData.push_back(ChStd::BinaryToNumWithLittleEndian<char>(_binarys, filePos));


				}

				filePos += _recode.conpressedLength;
			}

			template<class FBXBaseType = FBXBinary>
			ChPtr::Shared<BaseType> MakeSpecialType(unsigned long _len,const std::vector<char>& _binarys, unsigned long& _filePos)
			{
				auto tmp = ChPtr::Make_S<FBXBaseType>();

				for (unsigned long i = 0; i < _len; i++)
				{
					tmp->value.push_back(_binarys[i + filePos]);
				}
				_filePos += _len;

				return tmp;

			}

			ChStd::Bool IsNullRecode(const std::vector<char>& _binarys, unsigned long& _filePos)
			{
				for (unsigned char i = 0; i < 13; i++)
				{
					if (_binarys[(13 - i) + _filePos] != '\0')continue;
					return false;
				}
				_filePos += 13;
				return true;
			}

			const char prefix[21] = { (char)0x4b,(char)0x61,(char)0x79,(char)0x64,(char)0x61,(char)0x72,(char)0x61,(char)0x20,(char)0x46,(char)0x42,(char)0x58,(char)0x20,(char)0x42,(char)0x69,(char)0x6e,(char)0x61,(char)0x72,(char)0x79,(char)0x20,(char)0x20,(char)0x00 };

			ChStd::Bool binaryFlg = false;

		};

	}

}

#endif