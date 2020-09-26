#ifndef Ch_D3D11_Shader_h
#define Ch_D3D11_Shader_h

#include"../ChVertexData11.h"

namespace ChCpp
{
	class ModelObject;
}

namespace ChD3D11
{
	class Texture11;
	enum class CULL { NONE, CW, CCW };

	//��Light��Shader����BaseLight��PointLight�𗘗p���Ă�������//
	//�Ǝ��ō\�z���Ă���Shader�N���X//
	class ShaderController :public ChCpp::ChCp::InitPack
	{

	protected:

		struct LambertLight
		{
			ChStd::COLOR1f Dif = ChStd::COLOR1f(1.0f, 1.0f, 1.0f, 1.0f);
			ChVec3_11 Dir = ChVec3_11(0.0f, -1.0f, 0.0f);
			float AmbPow = 0.3f;
		};

		struct PointLight
		{
			PointLight() {}

			ChVec3 Dif = ChVec3(1.0f);
			float Len = 1.0f;
			ChVec3_11 Pos = ChVec3_11();
			bool Flg;
		};

		struct Material
		{
			ChStd::COLOR1f Dif;
			ChVec3 SpeCol;
			float SpePow;
			ChVec4 Amb;
		};

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//��������ChLibrary�̓����Ă���DirectoryPath��I��//
		void Init(const ID3D11Device* _d
			, const float& _WindWidth = 1280.0f
			, const float& _WindHeight = 720.0f);

	protected:

		inline void InitShader()
		{
//
//			{
//#include"ModelBVS.inc"
//
//
//				Device->CreateVertexShader((DWORD*)ModelBVS, &BVModel);
//			}
//
//			{
//#include"ModelBPS.inc"
//
//
//				Device->CreatePixelShader((DWORD*)ModelBPS, &BPModel);
//			}
//
//			{
//#include"ModelOLVS.inc"
//
//
//				Device->CreateVertexShader((DWORD*)ModelOLVS, &CVModel);
//			}
//
//			{
//#include"ModelCPS.inc"
//
//
//				Device->CreatePixelShader((DWORD*)ModelCPS, &CPModel);
//			}
//
//			{
//#include"SpTexVS.inc"
//
//
//				Device->CreateVertexShader((DWORD*)SpTexVS, &SpVTex);
//			}
//
//			{
//#include"PoTexVS.inc"
//
//				Device->CreateVertexShader((DWORD*)PoTexVS, &PoVTex);
//			}
//
//			{
//#include"TexPS.inc"
//
//				Device->CreatePixelShader((DWORD*)TexPS, &BPTex);
//			}

		}
	public:

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�`�������ۂɗ��p����J�����O�^�C�v���Z�b�g//
		inline void SetCullMode(const CULL _CULL)
		{
			Cull = _CULL;
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

		inline void SetCamPos(const ChVec3_11& _Pos) { CamPos = _Pos; }

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

		inline CULL GetCullMode()
		{
			return Cull;
		}

		inline ChStd::FPOINT GetWindSize()
		{
			return WindSize;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		void IsLight(const ChStd::Bool _Flg);

		//�`��\�m�F�֐�//
		inline ChStd::Bool IsDraw()
		{
			return DrawFlg;
		}

		inline ChStd::Bool IsRTDraw() { return RTDrawFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�`��J�n�O�ɌĂԊ֐�//
		//ChTex::RenderTargetManager9::SetRT//
		//ChTex::RenderTargetList9::SetRT�Ƃ͕��p�ł��܂���//
		void DrawStart(const ChStd::COLOR1f& _BackColor = ChStd::COLOR1f(255, 255, 255, 255));

		///////////////////////////////////////////////////////////////////////////////////

		//�`��I�����ɌĂԊ֐�//
		//ChTex::RenderTargetManager9::ReturnRT//
		//ChTex::RenderTargetList9::ReturnRT�Ƃ͕��p�ł��܂���//
		void DrawEnd();

		///////////////////////////////////////////////////////////////////////////////////

		//Mesh�`��p�֐�//
		void DrawMesh(
			const ChPtr::Shared<ChCpp::ModelObject> _Mesh
			, const ChMat_11& _Mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////

		//Mesh�`��p�֐�//
		void DrawMeshContour(
			const ChPtr::Shared<ChCpp::ModelObject> _Mesh
			, const ChStd::COLOR1f& _Color
			, const ChMat_11& _Mat = ChMat_11()
			, const float _Size = 1.0f);

		///////////////////////////////////////////////////////////////////////////////////

		//�|���S���`��//
		void DrawPolygonBoard(
			const ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, const VertexData& _Vertex
			, const ChMat_11& _Mat = ChMat_11()
			, const unsigned int _TriangleCount = 2);

		///////////////////////////////////////////////////////////////////////////////////

		//�X�v���C�g�`��//
		void DrawSprite(
			const ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, const ChMat_11& _Mat = ChMat_11()
			, const SpriteData& _SpData = SpriteData(ChStd::FPOINT(0.0f, 0.0f), WindSize));

		///////////////////////////////////////////////////////////////////////////////////

		void CreateLightPowTex(const std::string& _LightPowTexName);

		///////////////////////////////////////////////////////////////////////////////////


	protected:

		//�����_�[�^�[�Q�b�g�p�t���O//
		inline void SetRTDraw(const ChStd::Bool _Flg) { RTDrawFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�`��f�[�^�̏�����//
		void SetDrawDatas(const ChStd::COLOR1f&
			_BackColor);

		///////////////////////////////////////////////////////////////////////////////////

		struct TmpPLight
		{

			ChVec3 Dif = ChVec3(1.0f);
			ChVec3_11 Pos = ChVec3_11();
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
		Material SetMateData(Material& _Mate);

		///////////////////////////////////////////////////////////////////////////////////

		void SetLightFunction();

		///////////////////////////////////////////////////////////////////////////////////

		//3D���f���`��p�V�F�[�_�[//
		ID3D11VertexShader* BVModel = nullptr;
		ID3D11PixelShader* BPModel = nullptr;
		ID3D11VertexShader* CVModel = nullptr;
		ID3D11PixelShader* CPModel = nullptr;

		//�|���S���Ȃǃe�N�X�`���P�̕`��p�V�F�[�_�[//
		ID3D11VertexShader* SpVTex = nullptr;
		ID3D11VertexShader* PoVTex = nullptr;
		ID3D11PixelShader* BPTex = nullptr;

		ChStd::Bool AllCreateFlg = false;

		//���_���ύX�p//
		D3D11_INPUT_ELEMENT_DESC* TVerDec = nullptr;
		D3D11_INPUT_ELEMENT_DESC* MVerDec = nullptr;

		//���f���̉摜���Ȃ��ꍇ�ɃZ�b�g����//
		ChPtr::Shared<ChD3D11::Texture11>WhiteTex = nullptr;

		//���f���̖@���}�b�v���Ȃ��ꍇ�Ɏg�p����摜//
		ChPtr::Shared<ChD3D11::Texture11>NormalTex = nullptr;

		//���C�g�̋�����\���摜���//
		ChPtr::Shared<ChD3D11::Texture11>LightEffectTex = nullptr;

		//�ЂƂO�̕`��ۑ��p//
		ChPtr::Shared<ChD3D11::Texture11>BeforeTex = nullptr;

		ChStd::Bool LightUseFlg = false;

		//��p���C�g//
		LambertLight Light = LambertLight();

		//��p�|�C���g���C�g//
		PointLights PosLight = PointLights();

		ChVec3_11 CamPos = ChVec3_11();

		ID3D11Device* Device = nullptr;
		ID3D11DeviceContext* DC = nullptr;

		//AmbTex = nullptr;

		//���C�g�̋�����ݒ肷��摜//
		ChPtr::Shared<ChD3D11::Texture11>MyLightTex = nullptr;

		ChStd::Bool UseMyLightTex = false;

		//�`��\�t���O//
		ChStd::Bool DrawFlg = false;
		ChStd::Bool RTDrawFlg = false;

		//�t�H�O�`��t���O//
		ChStd::Bool FogFlg = false;

		//�E�B���h�T�C�Y//
		static ChStd::FPOINT WindSize;

		//�J�����O�^�C�v//
		CULL Cull = CULL::NONE;

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

	static const std::function<ShaderController& ()>Shader = ShaderController::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08