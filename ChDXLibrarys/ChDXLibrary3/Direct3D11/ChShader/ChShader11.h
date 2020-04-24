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
}

namespace ChD3D9
{



	//��Light��Shader����BaseLight��PointLight�𗘗p���Ă�������//
	//�Ǝ��ō\�z���Ă���Shader�N���X//
	class ShaderController {

	protected:

		struct LambertLight
		{
			ChStd::COLOR1f Dif = ChStd::COLOR1f(1.0f, 1.0f, 1.0f, 1.0f);
			ChVec3_9 Dir = ChVec3_9(0.0f, -1.0f, 0.0f);
			float AmbPow = 0.3f;
		};

		struct PointLight
		{
			PointLight() {}

			ChVec3 Dif = ChVec3(1.0f);
			float Len = 1.0f;
			ChVec3_9 Pos = ChVec3_9();
			bool Flg;
		};

		struct Material
		{

			ChStd::COLOR1f Dif;
			ChVec3 SpeCol;
			float SpePow;
		};

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//��������ChLibrary�̓����Ă���DirectoryPath��I��//
		void Init(const LPDIRECT3DDEVICE9 _d
			, const D3DPRESENT_PARAMETERS Param
			, const float& _WindWidth = 1280.0f
			, const float& _WindHeight = 720.0f);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�`�������ۂɗ��p����J�����O�^�C�v���Z�b�g//
		inline void SetCullMode(const CULL _CULL)
		{
			Device->SetRenderState(D3DRS_CULLMODE, ChStd::EnumCast(_CULL));
		}

		//�����ʂ��g�p���邩�ۂ��̃t���O//
		inline void SetFogFlg(ChStd::Bool _Flg) { FogFlg = _Flg; }

		//Wind�T�C�Y�̐ݒ�//
		inline void SetWindSize(const float _w, const float _h)
		{
			WindSize.w = _w;
			WindSize.h = _h;
		}

		inline void SetWindSize(const ChStd::FPOINT& _Size)
		{
			WindSize = _Size;
		}

		//���g�̗p�ӂ������C�g�̋�����\���e�N�X�`���𗘗p���邽�߂̃t���O//
		inline void SetLightPowTexFlg(const ChStd::Bool _Flg)
		{
			if (MyLightTex == nullptr)return;
			UseMyLightTex = _Flg;
		}

		inline void SetCamPos(const ChVec3_9& _Pos) { CamPos = _Pos; }

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline LambertLight& GetLightInstanse() { return Light; }

		struct PointLights
		{
			PointLight Light[7];

			PointLight& operator[](int _Num)
			{
				return Light[_Num];
			}
		};

		inline PointLights& GetPointLightInstanse() { return PosLight; }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		void IsLight(const ChStd::Bool _Flg);

		//�`��\�m�F�֐�//
		inline ChStd::Bool IsDraw()
		{
			return DrawFlg;
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�`��J�n�O�ɌĂԊ֐�//
		void DrawStart(const D3DCOLOR& _BackColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		///////////////////////////////////////////////////////////////////////////////////

		//�`��I�����ɌĂԊ֐�//
		//�����_�[�^�[�Q�b�g���p�����ۂ�Flg��True�ɂ���//
		void DrawEnd(const ChStd::Bool& _RTFlg = false);

		///////////////////////////////////////////////////////////////////////////////////

		//Mesh�`��p�֐�//
		void DrawMesh(
			const ChPtr::Shared<ChMesh::Mesh9> _Mesh
			, const ChMat_9& _Mat = ChMat_9());

		///////////////////////////////////////////////////////////////////////////////////

		//�|���S���`��//
		void DrawPolygonBoard(
			const ChPtr::Shared<ChTex::Texture9>& _Tex
			, const VertexData& _Vertex
			, const ChMat_9& _Mat = ChMat_9()
			, const unsigned int _TriangleCount = 2);

		///////////////////////////////////////////////////////////////////////////////////

		//�X�v���C�g�`��//
		void DrawSprite(
			const ChPtr::Shared<ChTex::Texture9>& _Tex
			, const ChMat_9& _Mat = ChMat_9()
			, const SpriteData&_SpData = SpriteData(ChStd::FPOINT(0.0f, 0.0f), WindSize));

		///////////////////////////////////////////////////////////////////////////////////

		void CreateLightPowTex(const std::string& _LightPowTexName);

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		struct TmpPLight
		{
			
			ChVec3 Dif = ChVec3(1.0f);
			ChVec3_9 Pos = ChVec3_9();
			float Len = 1.0f;
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
		Material SetMateData(D3DMATERIAL9& _Mate);

		///////////////////////////////////////////////////////////////////////////////////

		void SetLightFunction();

		///////////////////////////////////////////////////////////////////////////////////

		//3D���f���`��p�V�F�[�_�[//
		LPDIRECT3DVERTEXSHADER9 BVModel = nullptr;
		LPDIRECT3DPIXELSHADER9 BPModel = nullptr;

		//�|���S���Ȃǃe�N�X�`���P�̕`��p�V�F�[�_�[//
		LPDIRECT3DVERTEXSHADER9 SpVTex = nullptr;
		LPDIRECT3DVERTEXSHADER9 PoVTex = nullptr;
		LPDIRECT3DPIXELSHADER9 BPTex = nullptr;

		LPD3DXCONSTANTTABLE PixelCnstant;
		LPD3DXCONSTANTTABLE VertexCnstant;

		ChStd::Bool AllCreateFlg = false;

		//�x�[�X�ƂȂ钸�_���//
		LPDIRECT3DVERTEXDECLARATION9 BaseDec = nullptr;

		//���_���ύX�p//
		LPDIRECT3DVERTEXDECLARATION9 TVerDec = nullptr;
		LPDIRECT3DVERTEXDECLARATION9 MVerDec = nullptr;

		//���f���̉摜���Ȃ��ꍇ�ɃZ�b�g����//
		ChPtr::Shared<ChTex::BaseTexture9>WhiteTex = nullptr;

		//���f���̖@���}�b�v���Ȃ��ꍇ�Ɏg�p����摜//
		ChPtr::Shared<ChTex::BaseTexture9>NormalTex = nullptr;

		//���C�g�̋�����\���摜���//
		ChPtr::Shared<ChTex::BaseTexture9>LightEffectTex = nullptr;

		//�ЂƂO�̕`��ۑ��p//
		ChPtr::Shared<ChTex::Texture9>BeforeTex = nullptr;

		ChStd::Bool LightUseFlg = false;

		ChStd::Bool SetLightFlg = false;

		//��p���C�g//
		LambertLight Light;

		//��p�|�C���g���C�g//
		PointLights PosLight;

		ChVec3_9 CamPos;

		LPDIRECT3DDEVICE9 Device;

		//Device�������p�p�����[�^//
		D3DPRESENT_PARAMETERS Param;

		LPDIRECT3DCUBETEXTURE9 AmbTex;

		//���C�g�̋�����ݒ肷��摜//
		ChPtr::Shared<ChTex::Texture9>MyLightTex = nullptr;

		ChStd::Bool UseMyLightTex = false;

		//�`��\�t���O//
		ChStd::Bool DrawFlg = false;

		//�`��\�t���O//
		ChStd::Bool FogFlg = false;

		//�E�B���h�T�C�Y//
		static ChStd::FPOINT WindSize;

		///////////////////////////////////////////////////////////////////////////////////

	public:

		static inline ShaderController& GetIns()
		{
			static ShaderController Ins;
			return Ins;
		}

	protected:

		ShaderController() {}

		~ShaderController() {}

	};

	static const std::function<ShaderController&()>Shader = ShaderController::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08