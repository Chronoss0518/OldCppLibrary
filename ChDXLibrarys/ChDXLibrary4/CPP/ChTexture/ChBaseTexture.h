#ifndef Ch_CPP_Tex_h
#define Ch_CPP_Tex_h

namespace ChTex
{
	typedef class BaseTexture:public ChCpp::ChCp::InitPack
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BaseTexture() {}

		virtual ~BaseTexture() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetBaseColor(const ChStd::COLOR255& _Col) { Col = _Col; }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�I�������ӏ��̐F�擾//
		ChStd::COLOR1f GetColor(
			const unsigned int _Width
			, const unsigned int _Height);

		float GetSclXSize()const { return ScalingX; }

		float GetSclYSize()const { return ScalingY; }

		unsigned int GetOriginalWidth()const { return OWidth; }

		unsigned int GetOriginalHeight()const { return OHeight; }

		ChStd::COLOR255 GetBaseColor()const { return Col; }

		///////////////////////////////////////////////////////////////////////////////////
		//InsFunction//

		float&  InsSclXSize() { return ScalingX; }

		float&  InsSclYSize() { return ScalingY; }

		unsigned int& InsOriginalWidth() { return OWidth; }

		unsigned int& InsOriginalHeight() { return OHeight; }

		ChStd::COLOR255& InsBaseColor() { return Col; }

	protected:

		//�I�������ӏ��̐F�擾//
		virtual ChStd::COLOR1f GetBitColor(
			const unsigned int _Width
			, const unsigned int _Height);

		float ScalingX = 1.0f;
		float ScalingY = 1.0f;
		unsigned int OWidth;	//�I���W�i���T�C�Y�̉���//
		unsigned int OHeight;	//�I���W�i���T�C�Y�̏c��//
		ChStd::COLOR255 Col{ 255,255,255,255 };	//�F�ʊ�{�F//

		std::string TextureName;

	}Texture;

}

#endif