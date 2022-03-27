#ifndef Ch_D3D11_Shader_h
#define Ch_D3D11_Shader_h

#include"../ChShaderObject/ChShaderObject11.h"
#include"../ChShaderParts/ChShaderParts11.h"

namespace ChD3D11
{
	class DirectX3D11;

	class Mesh11;
	class Texture11;
	class Sprite11;
	class PolygonBoard11;

	using DLight = ShaderParts::ChLightHeader::DirectionalLight;
	using PLight = ShaderParts::ChLightHeader::PointLight;

	//��Light��Shader����BaseLight��PointLight�𗘗p���Ă�������//
	//�Ǝ��ō\�z���Ă���Shader�N���X//
	class ShaderController11 final :public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//


		void Init(
			DirectX3D11& _chDevice
			, const ChVec2& _windSize);

		void Init(
			DirectX3D11& _chDevice
			, const float& _windWitdh
			, const float& _windHeight);

		void Init(ID3D11Device* _d
			, ID3D11DeviceContext* _dc
			, IDXGISwapChain* _sc
			, const ChVec2& _windSize);

		void Init(ID3D11Device* _d
			, ID3D11DeviceContext* _dc
			, IDXGISwapChain* _sc
			, const float& _windWitdh
			, const float& _windHeight);

	protected:

		void InitShader();

	public:

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�`�悳���郌���_�[�^�[�Q�b�g��o�^����//
		void SetRenderTarget(Texture11& _tex);

		inline void SetBackColor(const ChVec4& _color)
		{
			if (!*this)return;
			if (drawFlg)return;

			backColor = _color;
		}

		//�`��Ώۂ��o�b�N�o�b�t�@�ɂ���//
		inline void SetBackBuffer()
		{
			if (!*this)return;
			if (drawFlg)return;

			renderTargets.clear();
		}

		//�`�������ۂɗ��p����J�����O�^�C�v���Z�b�g//
		inline void SetCullMode(const D3D11_CULL_MODE _cull)
		{
			if (!*this)return;
			if (drawFlg)return;

			cull = _cull;

			rasteriserUpdate = true;
		}

		//�`�������ۂɗ��p����t�B���^�C�v���Z�b�g//
		inline void SetFilMode(const D3D11_FILL_MODE _fill)
		{
			if (!*this)return;
			if (drawFlg)return;

			fill = _fill;

			rasteriserUpdate = true;
		}

		//�����ʂ��g�p���邩�ۂ��̃t���O//
		inline void SetFogFlg(ChStd::Bool _flg)
		{
			if (!*this)return;
			if (drawFlg)return;

			fogFlg = _flg;
		}

		inline void SetViewMat(const ChMat_11& _viewMat)
		{

			if (!*this)return;
			if (drawFlg)return;

			bdObject.viewMat = _viewMat;

			bdUpdateFlg = true;

		}

		inline void SetProjMat(const ChMat_11& _projMat)
		{

			if (!*this)return;
			if (drawFlg)return;

			bdObject.projMat = _projMat;

			bdUpdateFlg = true;

		}

		inline void SetWindPos(const ChVec2& _pos)
		{

			if (!*this)return;
			if (drawFlg)return;

			view.SetWindPos(_pos);

		}

		inline void SetWindSize(const ChVec2& _size)
		{

			if (!*this)return;
			if (drawFlg)return;

			view.SetWindSize(_size);
		}

		inline void SetLightDiffuse(const ChVec3& _dif)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetLightDiffuse(_dif);
		}

		inline void SetUseLightFlg(const ChStd::Bool& _flg)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetUseLightFlg(_flg);
		}

		inline void SetLightDir(const ChVec3& _dir)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetLightDir(_dir);
		}

		inline void SetLightAmbientPow(const float _amb)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetLightAmbientPow(_amb);
		}

		inline void SetPLightPos(const ChVec3& _pos, const unsigned long _no = 0)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetPLightPos(_pos, _no);
		}

		inline void SetPLightLen(const float _len, const unsigned long _no = 0)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetPLightLen(_len, _no);
		}

		inline void SetPLightDiffuse(const ChVec3& _dif, const unsigned long _no = 0)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetPLightDiffuse(_dif, _no);
		}

		inline void SetPLightUseFlg(const ChStd::Bool& _flg, const unsigned long _no = 0)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetPLightUseFlg(_flg, _no);
		}

		inline void SetCamPos(const ChVec3& _camPos)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetCamPos(_camPos);
		}

		inline void SetLightData(const ShaderParts::ChLightHeader::LightData& _ld)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetLightData(_ld);
		}

		inline void SetImportLightPowMap(ChPtr::Shared<Texture11>& _lightPowMap)
		{
			if (!*this)return;
			if (drawFlg)return;

			lightDatas.SetImportLightPowMap(_lightPowMap);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline D3D11_CULL_MODE GetCullMode() { return cull; }

		inline D3D11_FILL_MODE GetFillMode() { return fill; }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		void IsLight(const ChStd::Bool _flg);

		//�`��\�m�F�֐�//
		inline ChStd::Bool IsDraw() { return drawFlg; }

		inline ChStd::Bool IsRTDraw() { return rtDrawFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�`��ΏۂƂȂ�摜�Q�̓o�^����������//
		inline void ClearRenderTargets()
		{
			renderTargets.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�`��J�n�O�ɌĂԊ֐�//
		void DrawStart();

		///////////////////////////////////////////////////////////////////////////////////

		//�`��I�����ɌĂԊ֐�//
		void DrawEnd();

		///////////////////////////////////////////////////////////////////////////////////
		//Mesh�`��Q//

		void Draw(
			Mesh11& _mesh
			, const ChMat_11& _mat = ChMat_11());

		//OutLine�`��//
		void DrawOutLine(
			Mesh11& _mesh
			, const ChVec4& _color
			, const ChMat_11& _mat = ChMat_11()
			, const float _size = 1.0f);

		///////////////////////////////////////////////////////////////////////////////////
		//�|���S���`��Q//

		void Draw(
			Texture11& _tex
			, PolygonBoard11& _polygon
			, const ChMat_11& _mat = ChMat_11());

		//�~�`�Ŏw��͈͂�`��//
		void DrawToCircleParsec(
			Texture11& _tex
			, PolygonBoard11& _polygon
			, const ChVec2& _startLine
			, const float _drawRad
			, const ChMat_11& _mat = ChMat_11());

		//�l�p�`�Ŏw��͈͂�`��//
		void DrawSquareParsec(
			Texture11& _tex
			, PolygonBoard11& _polygon
			, const ChVec2& _startLine
			, const float _drawRad
			, const ChMat_11& _mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////
		//Sprite�`��Q//

		//�ʏ�`��//
		void Draw(
			Texture11& _tex
			, Sprite11& _sprite
			, const ChMat_11& _mat = ChMat_11());

		//�~�`�Ŏw��͈͂�`��//
		void DrawToCircleParsec(
			Texture11& _tex
			, Sprite11& _sprite
			, const ChVec2& _startLine
			, const float _drawRad
			, const ChMat_11& _mat = ChMat_11());

		//�l�p�`�Ŏw��͈͂�`��//
		void DrawSquareParsec(
			Texture11& _tex
			, Sprite11& _sprite
			, const ChVec2& _startLine
			, const float _drawRad
			, const ChMat_11& _mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		//�����_�[�^�[�Q�b�g�p�t���O//
		inline void SetRTDraw(const ChStd::Bool _Flg) { rtDrawFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�`��f�[�^�̏�����//
		void SetDrawDatas();

		///////////////////////////////////////////////////////////////////////////////////

		void BaseDataUpdate();

		///////////////////////////////////////////////////////////////////////////////////

		//3D���f���`��p�V�F�[�_�[//
		VertexShader11 bvModel;
		PixelShader11 bpModel;
		VertexShader11 pvTex;


		//�|���S���Ȃǃe�N�X�`���P�̕`��p�V�F�[�_�[//
		VertexShader11 spvTex;
		PixelShader11 bpTex;

		//ShadowMap�����p//
		Texture11 depthShadowTex;

		//���f���̉摜���Ȃ��ꍇ�ɃZ�b�g����//
		Texture11 whiteTex;

		//���f���̖@���}�b�v���Ȃ��ꍇ�Ɏg�p����摜//
		Texture11 normalTex;

		//�`��Ώۂɐݒ肷��摜�Q//
		std::vector<ID3D11RenderTargetView*>renderTargets;
		ID3D11RenderTargetView** tmpView = nullptr;

		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* dc = nullptr;

		//DepthStencilBuffer�p//
		Texture11 dsBuffer;

		ShaderParts::DrawWindow window;

		ShaderParts::ViewPort view;
		
		ShaderParts::ChLightHeader lightDatas;

		//�`��\�t���O//
		ChStd::Bool drawFlg = false;
		ChStd::Bool rtDrawFlg = false;

		//�t�H�O�`��t���O//
		ChStd::Bool fogFlg = false;

		//�J�����O�^�C�v//
		D3D11_CULL_MODE cull = D3D11_CULL_MODE::D3D11_CULL_NONE;

		//�ʕ`��^�C�v//
		D3D11_FILL_MODE fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		ID3D11RasterizerState* rasteriser = nullptr;

		ChStd::Bool rasteriserUpdate = false;

		//�w�i�F//
		ChVec4 backColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		struct BaseDatas
		{
			//�r���[�ϊ��s��//
			ChMat_11 viewMat;
			//�ˉe�ϊ��s��//
			ChMat_11 projMat;
			//��ʃT�C�Y//
			ChVec4 windSize;
		};

		struct CharaDatas
		{
			//���f���s��//
			ChMat_11 modelMat;

		};

		struct PolygonDatas
		{
			//���f���s��//
			ChMat_11 modelMat;
			//�X�v���C�g�x�[�X�F//
			ChVec4 baseColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		};

		struct BoneDatas
		{
			//�X�L�����b�V���p�s��//
			ChMat_11 skinWeightMat[1000];
		};

		ChStd::Bool bdUpdateFlg = true;

		BaseDatas bdObject;
		ConstantBuffer baseData = nullptr;

		CharaDatas cdObject;
		ConstantBuffer charaData = nullptr;

		PolygonDatas pdObject;
		ConstantBuffer polygonData = nullptr;

		BoneDatas bodObject;
		ConstantBuffer boneData = nullptr;

		///////////////////////////////////////////////////////////////////////////////////

		Texture11 out3D;
		Texture11 out2D;

		Sprite11 outSprite;

	public:

		static inline ShaderController11& GetIns()
		{
			static ShaderController11 ins;
			return ins;
		}

	private:

		ShaderController11() {}

	};

	static const std::function<ShaderController11& ()>Shader11 = ShaderController11::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08