#ifndef Ch_D3D9_Shader_h
#define Ch_D3D9_Shader_h

#include"../ChVertexData9.h"

namespace ChMesh
{
	typedef class BaseMesh9 Mesh9;
}

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	class RenderTargetList9;
	class RenderTargetManager9;
}

namespace ChD3D9
{



	//��Light��Shader����BaseLight��PointLight�𗘗p���Ă�������//
	//�Ǝ��ō\�z���Ă���Shader�N���X//
	class ShaderController:public ChCp::Initializer,public ChCp::Releaser
	{

	protected:

		struct LambertLight
		{
			ChVec4 dif = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
			ChVec3_9 dir = ChVec3_9(0.0f, -1.0f, 0.0f);
			float ambPow = 0.3f;
		};

		struct PointLight
		{
			PointLight() {}

			ChVec3 dif = ChVec3(1.0f);
			float len = 1.0f;
			ChVec3_9 pos = ChVec3_9();
			bool flg;
		};

		struct Material
		{
			ChVec4 dif;
			ChVec3 speCol;
			float spePow;
		};

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//��������ChLibrary�̓����Ă���DirectoryPath��I��//
		void Init(const LPDIRECT3DDEVICE9 _d
			, const D3DPRESENT_PARAMETERS& param
			, const float& _windWidth = 1280.0f
			, const float& _windHeight = 720.0f);

	protected:

		void InitShader();

	public:

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�`�������ۂɗ��p����J�����O�^�C�v���Z�b�g//
		inline void SetCullMode(const CULL _cull)
		{
			cull = _cull;
			device->SetRenderState(D3DRS_CULLMODE, ChStd::EnumCast(_cull));
		}

		//�����ʂ��g�p���邩�ۂ��̃t���O//
		inline void SetFogFlg(ChStd::Bool _flg) { fogFlg = _flg; }

		//Wind�T�C�Y�̐ݒ�//
		inline void SetWindSize(const float _w, const float _h)
		{
			windSize.w = _w;
			windSize.h = _h;
		}

		inline void SetWindSize(const ChVec4& _Size)
		{
			windSize = _Size;
		}

		//���g�̗p�ӂ������C�g�̋�����\���e�N�X�`���𗘗p���邽�߂̃t���O//
		inline void SetLightPowTexFlg(const ChStd::Bool _Flg)
		{
			if (myLightTex == nullptr)return;
			useMyLightTex = _Flg;
		}

		inline void SetCamPos(const ChVec3_9& _pos) { camPos = _pos; }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline LambertLight& GetLightInstanse() { return light; }

		struct PointLights
		{
			PointLight light[7];

			PointLight& operator[](int _Num)
			{
				return light[_Num];
			}
		};

		inline PointLights& GetPointLightInstanse() { return posLight; }

		inline CULL GetCullMode()
		{
			return cull;
		}

		inline ChVec2 GetWindSize()
		{
			return windSize;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		void IsLight(const ChStd::Bool _flg);

		//�`��\�m�F�֐�//
		inline ChStd::Bool IsDraw()
		{
			return drawFlg;
		}

		inline ChStd::Bool IsRTDraw() { return rtDrawFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�`��J�n�O�ɌĂԊ֐�//
		//ChTex::RenderTargetManager9::SetRT//
		//ChTex::RenderTargetList9::SetRT�Ƃ͕��p�ł��܂���//
		void DrawStart(const D3DCOLOR& _backColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		///////////////////////////////////////////////////////////////////////////////////

		//�`��I�����ɌĂԊ֐�//
		//ChTex::RenderTargetManager9::ReturnRT//
		//ChTex::RenderTargetList9::ReturnRT�Ƃ͕��p�ł��܂���//
		void DrawEnd();

		///////////////////////////////////////////////////////////////////////////////////

		//Mesh�`��p�֐�//
		void DrawMesh(
			const ChPtr::Shared<ChMesh::Mesh9> _mesh
			, const ChMat_9& _mat = ChMat_9());

		///////////////////////////////////////////////////////////////////////////////////

		//Mesh�`��p�֐�//
		void DrawMeshContour(
			const ChPtr::Shared<ChMesh::Mesh9> _mesh
			, const ChVec4& _color
			, const ChMat_9& _mat = ChMat_9()
			, const float _size = 1.0f);

		///////////////////////////////////////////////////////////////////////////////////

		//�|���S���`��//
		void DrawPolygonBoard(
			const ChPtr::Shared<ChTex::Texture9>& _tex
			, const VertexData& _vertex
			, const ChMat_9& _mat = ChMat_9()
			, const unsigned int _triangleCount = 2);

		///////////////////////////////////////////////////////////////////////////////////

		//�X�v���C�g�`��//
		void DrawSprite(
			const ChPtr::Shared<ChTex::Texture9>& _tex
			, const ChMat_9& _mat = ChMat_9()
			, const SpriteData&_spData = SpriteData(ChVec2(0.0f, 0.0f), windSize));

		///////////////////////////////////////////////////////////////////////////////////

		void CreateLightPowTex(const std::string& _lightPowTexName);

		///////////////////////////////////////////////////////////////////////////////////

		friend ChTex::RenderTargetList9;
		friend ChTex::RenderTargetManager9;

	protected:

		//�����_�[�^�[�Q�b�g�p�t���O//
		inline void SetRTDraw(const ChStd::Bool _flg) { rtDrawFlg = _flg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�`��f�[�^�̏�����//
		void SetDrawDatas(const D3DCOLOR&
			_backColor);

		///////////////////////////////////////////////////////////////////////////////////

		struct TmpPLight
		{
			
			ChVec3 dif = ChVec3(1.0f);
			ChVec3_9 pos = ChVec3_9();
			float len = 1.0f;
		};

		void MakeBlurFuncNum();

		///////////////////////////////////////////////////////////////////////////////////

		//���F�̉摜�����֐�//
		void MakeWhiteTexture();

		///////////////////////////////////////////////////////////////////////////////////

		//���C�g�̋�����\���e�N�X�`���̐���//
		void MakeLightingPowTexture();

		///////////////////////////////////////////////////////////////////////////////////

		//�@���}�b�v�����p�֐�//
		void MakeNormalMapTexture();

		///////////////////////////////////////////////////////////////////////////////////

		//�W���}�e���A�����玩�g�̎g���}�e���A���^�ւ̕ύX//
		Material SetMateData(D3DMATERIAL9& _mate);

		///////////////////////////////////////////////////////////////////////////////////

		void SetLightFunction();

		///////////////////////////////////////////////////////////////////////////////////

		//3D���f���`��p�V�F�[�_�[//
		LPDIRECT3DVERTEXSHADER9 bVModel = nullptr;
		LPDIRECT3DPIXELSHADER9 bPModel = nullptr;
		LPDIRECT3DVERTEXSHADER9 cVModel = nullptr;
		LPDIRECT3DPIXELSHADER9 cPModel = nullptr;

		//�|���S���Ȃǃe�N�X�`���P�̕`��p�V�F�[�_�[//
		LPDIRECT3DVERTEXSHADER9 spVTex = nullptr;
		LPDIRECT3DVERTEXSHADER9 poVTex = nullptr;
		LPDIRECT3DPIXELSHADER9 bPTex = nullptr;

		LPD3DXCONSTANTTABLE pixelCnstant = nullptr;
		LPD3DXCONSTANTTABLE vertexCnstant = nullptr;

		ChStd::Bool allCreateFlg = false;

		//�x�[�X�ƂȂ钸�_���//
		LPDIRECT3DVERTEXDECLARATION9 baseDec = nullptr;

		//���_���ύX�p//
		LPDIRECT3DVERTEXDECLARATION9 tVerDec = nullptr;
		LPDIRECT3DVERTEXDECLARATION9 mVerDec = nullptr;

		//���f���̉摜���Ȃ��ꍇ�ɃZ�b�g����//
		ChPtr::Shared<ChTex::BaseTexture9>whiteTex = nullptr;

		//���f���̖@���}�b�v���Ȃ��ꍇ�Ɏg�p����摜//
		ChPtr::Shared<ChTex::BaseTexture9>normalTex = nullptr;

		//���C�g�̋�����\���摜���//
		ChPtr::Shared<ChTex::BaseTexture9>lightEffectTex = nullptr;

		//�ЂƂO�̕`��ۑ��p//
		ChPtr::Shared<ChTex::Texture9>beforeTex = nullptr;

		ChStd::Bool lightUseFlg = false;

		//��p���C�g//
		LambertLight light = LambertLight();

		//��p�|�C���g���C�g//
		PointLights posLight = PointLights();

		ChVec3_9 camPos = ChVec3_9();

		LPDIRECT3DDEVICE9 device = nullptr;

		//Device�������p�p�����[�^//
		D3DPRESENT_PARAMETERS param{ 0 };

		LPDIRECT3DCUBETEXTURE9 ambTex = nullptr;

		//���C�g�̋�����ݒ肷��摜//
		ChPtr::Shared<ChTex::Texture9>myLightTex = nullptr;

		ChStd::Bool useMyLightTex = false;

		//�`��\�t���O//
		ChStd::Bool drawFlg = false;
		ChStd::Bool rtDrawFlg = false;

		//�t�H�O�`��t���O//
		ChStd::Bool fogFlg = false;

		//�E�B���h�T�C�Y//
		static ChVec2 windSize;

		//�J�����O�^�C�v//
		CULL cull = CULL::NONE;

		///////////////////////////////////////////////////////////////////////////////////

	public:

		static inline ShaderController& GetIns()
		{
			static ShaderController ins;
			return ins;
		}

	protected:

		ShaderController() {}

	};

	static const std::function<ShaderController&()>Shader = ShaderController::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08