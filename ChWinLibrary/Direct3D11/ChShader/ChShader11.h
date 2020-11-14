#ifndef Ch_D3D11_Shader_h
#define Ch_D3D11_Shader_h

#include"../ChShaderObject/ChShaderObject11.h"

namespace ChD3D11
{
	class Mesh11;
	class Texture11;
	class Sprite11;
	class PolygonBoard11;

	using VSObject = ShaderObject11;
	using PSObject = ShaderObject11;

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

			ChVec3 Dif = ChVec3(1.0f);
			float Len = 1.0f;
			ChVec3_11 Pos = ChVec3_11();
			int Flg = 1;
		};

		struct TmpPLight
		{

			ChVec3 Dif = ChVec3(1.0f);
			ChVec3_11 Pos = ChVec3_11();
			float Len = 1.0f;
		};


	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//��������ChLibrary�̓����Ă���DirectoryPath��I��//
		void Init(ID3D11Device* _d
			, ID3D11DeviceContext* _DC
			, IDXGISwapChain* _SC
			, const float& _WindWidth = 1280.0f
			, const float& _WindHeight = 720.0f);

	protected:

		void InitShader();

	public:

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�`�悳���郌���_�[�^�[�Q�b�g��o�^����//
		void SetRenderTarget(ChPtr::Shared<Texture11> _Tex);

		inline void SetBackColor(const ChVec4& _Color)
		{
			if (!*this)return;
			if (DrawFlg)return;

			BackColor = _Color;
		}

		//�`��Ώۂ��o�b�N�o�b�t�@�ɂ���//
		inline void SetBackBuffer()
		{
			if (!*this)return;
			if (DrawFlg)return;

			RenderTargets.clear();
		}

		//�`�������ۂɗ��p����J�����O�^�C�v���Z�b�g//
		inline void SetCullMode(const D3D11_CULL_MODE _CULL)
		{
			if (!*this)return;
			if (DrawFlg)return;

			Cull = _CULL;

			RasteriserUpdate = true;
		}

		//�`�������ۂɗ��p����t�B���^�C�v���Z�b�g//
		inline void SetFilMode(const D3D11_FILL_MODE _Fill)
		{
			if (!*this)return;
			if (DrawFlg)return;

			Fill = _Fill;

			RasteriserUpdate = true;
		}

		//�����ʂ��g�p���邩�ۂ��̃t���O//
		inline void SetFogFlg(ChStd::Bool _Flg) 
		{
			if (!*this)return;
			if (DrawFlg)return;

			FogFlg = _Flg; 
		}

		//Wind�T�C�Y�̐ݒ�//
		inline void SetWindSize(const float _w, const float _h)
		{
			if (!*this)return;
			if (DrawFlg)return;

			WindSize.w = _w;
			WindSize.h = _h;
		}

		inline void SetWindSize(const ChStd::FPOINT& _Size)
		{
			if (!*this)return;
			if (DrawFlg)return;

			WindSize = _Size;
		}

		//���g�̗p�ӂ������C�g�̋�����\���e�N�X�`���𗘗p���邽�߂̃t���O//
		inline void SetLightPowTexFlg(const ChStd::Bool _Flg)
		{
			if (!*this)return;
			if (DrawFlg)return;

			if (MyLightTex == nullptr)return;
			UseMyLightTex = _Flg;
		}

		inline void SetViewMat(const ChMat_11& _ViewMat)
		{

			if (!*this)return;
			if (DrawFlg)return;

			BDObject.ViewMat = _ViewMat;

			BDUpdateFlg = true;

		}

		inline void SetProjMat(const ChMat_11& _ProjMat)
		{

			if (!*this)return;
			if (DrawFlg)return;

			BDObject.ProjMat = _ProjMat;

			BDUpdateFlg = true;

		}

		inline void SetWindSize(const ChVec2& _WindSize)
		{

			if (!*this)return;
			if (DrawFlg)return;

			BDObject.WindSize = _WindSize;

			BDUpdateFlg = true;

		}

		//inline void SetCamPos(const ChVec3_11& _Pos) { CamPos = _Pos; }

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

		inline D3D11_CULL_MODE GetCullMode()
		{
			return Cull;
		}

		inline D3D11_FILL_MODE GetFillMode()
		{
			return Fill;
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

		//�`��ΏۂƂȂ�摜�Q�̓o�^����������//
		inline void ClearRenderTargets()
		{
			RenderTargets.clear();
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
			Mesh11& _Mesh
			, const ChMat_11& _Mat = ChMat_11());

		//ToonShader�`��//
		void DrawToons(
			Mesh11& _Mesh
			, const ChStd::COLOR1f& _Color
			, const ChMat_11& _Mat = ChMat_11()
			, const float _Size = 1.0f);

		///////////////////////////////////////////////////////////////////////////////////
		//�|���S���`��Q//

		void Draw(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, PolygonBoard11& _Polygon
			, const ChMat_11& _Mat = ChMat_11());

		//�~�`�Ŏw��͈͂�`��//
		void DrawToCircleParsec(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, PolygonBoard11& _Polygon
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		//�l�p�`�Ŏw��͈͂�`��//
		void DrawSquareParsec(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, PolygonBoard11& _Polygon
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////
		//Sprite�`��Q//

		//�ʏ�`��//
		void Draw(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, Sprite11& _Sprite
			, const ChMat_11& _Mat = ChMat_11());

		//�~�`�Ŏw��͈͂�`��//
		void DrawToCircleParsec(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, Sprite11& _Sprite
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		//�l�p�`�Ŏw��͈͂�`��//
		void DrawSquareParsec(
			ChPtr::Shared<ChD3D11::Texture11>& _Tex
			, Sprite11& _Sprite
			, const ChVec2& _StartLine
			, const float _DrawDot
			, const ChMat_11& _Mat = ChMat_11());

		///////////////////////////////////////////////////////////////////////////////////

		void CreateLightPowTex(const std::string& _LightPowTexName);

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		//�����_�[�^�[�Q�b�g�p�t���O//
		inline void SetRTDraw(const ChStd::Bool _Flg) { RTDrawFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�`��f�[�^�̏�����//
		void SetDrawDatas();

		///////////////////////////////////////////////////////////////////////////////////

		void MakeBlurFuncNum();

		///////////////////////////////////////////////////////////////////////////////////

		void SetLightFunction();

		///////////////////////////////////////////////////////////////////////////////////

		void BaseDataUpdate();

		///////////////////////////////////////////////////////////////////////////////////

		//3D���f���`��p�V�F�[�_�[//
		VSObject BVModel;
		PSObject BPModel;
		VSObject PoVTex;
		//ToonSharder�p�V�F�[�_�[//
		VSObject CVModel;
		PSObject CPModel;

		//�|���S���Ȃǃe�N�X�`���P�̕`��p�V�F�[�_�[//
		VSObject SpVTex;
		PSObject BPTex;


		ChStd::Bool AllCreateFlg = false;

		//�`��p//
		ID3D11RenderTargetView* BBTargetView = nullptr;
		ChPtr::Shared<ChD3D11::Texture11>DSBuffer = nullptr;

		//�M���m�J�����p//
		ChPtr::Shared<ChD3D11::Texture11> Temperature = nullptr;
		ChPtr::Shared<ChD3D11::Texture11> TemperaturePowerMap = nullptr;
		//�Î��J�����p//
		ChPtr::Shared<ChD3D11::Texture11> NightVision = nullptr;
		ChPtr::Shared<ChD3D11::Texture11> NightVisionPowerMap = nullptr;

		//ShadowMap�����p//
		ChPtr::Shared<ChD3D11::Texture11> DepthShadowTexture = nullptr;

		//���f���̉摜���Ȃ��ꍇ�ɃZ�b�g����//
		ChPtr::Shared<ChD3D11::Texture11>WhiteTex = nullptr;

		//���f���̖@���}�b�v���Ȃ��ꍇ�Ɏg�p����摜//
		ChPtr::Shared<ChD3D11::Texture11>NormalTex = nullptr;

		//���C�g�̋�����\���摜���//
		ChPtr::Shared<ChD3D11::Texture11>LightEffectTex = nullptr;


		ChStd::Bool LightUseFlg = false;

		//�`��Ώۂɐݒ肷��摜�Q//
		std::vector<ID3D11RenderTargetView*>RenderTargets;
		ID3D11RenderTargetView** TmpView = nullptr;

		//��p���C�g//
		LambertLight Light = LambertLight();

		//��p�|�C���g���C�g//
		PointLights PosLight = PointLights();

		ID3D11Device* Device = nullptr;
		ID3D11DeviceContext* DC = nullptr;
		IDXGISwapChain* Window = nullptr;

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
		ChStd::FPOINT WindSize;

		//�`���Ƀo�b�N�o�b�t�@���������铙�̃t���O�����g//
		DXGI_SWAP_EFFECT BufferDatas = DXGI_SWAP_EFFECT_DISCARD;

		//�J�����O�^�C�v//
		D3D11_CULL_MODE Cull = D3D11_CULL_MODE::D3D11_CULL_NONE;

		//�ʕ`��^�C�v//
		D3D11_FILL_MODE Fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;


		ID3D11RasterizerState* Rasteriser = nullptr;

		ChStd::Bool RasteriserUpdate = false;

		//�w�i�F//
		ChVec4 BackColor=ChVec4(1.0f,1.0f,1.0f,1.0f);



		struct BaseDatas
		{
			//�r���[�ϊ��s��//
			ChMat_11 ViewMat;
			//�ˉe�ϊ��s��//
			ChMat_11 ProjMat;
			//��ʃT�C�Y//
			ChVec4 WindSize;
		};

		struct CharaDatas
		{
			//���f���s��//
			ChMat_11 ModelMat;
			//�X�L�����b�V���p�s��//
			ChMat_11 SkinWeightMat[1000];

		};

		struct PolygonDatas
		{

			//���f���s��//
			ChMat_11 ModelMat;
			//�X�v���C�g�x�[�X�F//
			ChVec4 BaseColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		};

		ChStd::Bool BDUpdateFlg = true;

		BaseDatas BDObject;
		ConstantBuffer BaseData = nullptr;
		
		CharaDatas CDObject;
		ConstantBuffer CharaData = nullptr;

		PolygonDatas PDObject;
		ConstantBuffer PolygonData = nullptr;

		D3D11_VIEWPORT ViewPort;

		///////////////////////////////////////////////////////////////////////////////////

	public:

		static inline ShaderController& GetIns()
		{
			static ShaderController Ins;
			return Ins;
		}

	protected:

		ShaderController() {}

		~ShaderController() { Release(); }

	};

	static const std::function<ShaderController& ()>Shader = ShaderController::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08