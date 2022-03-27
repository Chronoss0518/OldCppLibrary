#ifndef Ch_D3D11_SObject_h
#define Ch_D3D11_SObject_h

namespace ChD3D11
{
	class ShaderObject11:public ChCpp::ChCp::Initializer,public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction/

		virtual void SetShader(
			ID3D11DeviceContext* _DC
		) = 0;

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		//VertexShader用//
		void CreateVertexShader(
			ID3D11Device* _Device
			, ID3D11InputLayout** _LInput
			, const D3D11_INPUT_ELEMENT_DESC* _Desc
			, const unsigned long _DescNum
			, const void* _Binary
			, const unsigned long _BinarySize
		);

		//PixelShader用//
		void CreatePixelShader(
			ID3D11Device* _Device
			, const void* _Binary
			, const unsigned long _BinarySize
		);

		//VertexShader用//
		void CreateGeometryShader(
			ID3D11Device* _Device
			, const void* _Binary
			, const unsigned long _BinarySize
		);

		//VertexShader用//
		void CreateComputeShader(
			ID3D11Device* _Device
			, const void* _Binary
			, const unsigned long _BinarySize
		);

		//VertexShader用//
		void CreateDomainShader(
			ID3D11Device* _Device
			, const void* _Binary
			, const unsigned long _BinarySize
		);

		///////////////////////////////////////////////////////////////////////////////////

		void SetVertexShader(
			ID3D11DeviceContext* _DC
			, ID3D11InputLayout* _LInput);

		void SetPixelShader(
			ID3D11DeviceContext* _DC);

		void SetGeometryShader(
			ID3D11DeviceContext* _DC);

		void SetComputeShader(
			ID3D11DeviceContext* _DC);

		void SetDomainShader(
			ID3D11DeviceContext* _DC);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		ID3D11DeviceChild* Shader = nullptr;

	};

	class VertexShader11 final :public ShaderObject11
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			ID3D11Device* _Device
			, const D3D11_INPUT_ELEMENT_DESC* _Desc
			, const unsigned long _DescNum
			, const void* _Binary
			, const unsigned long _BinarySize);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction/

		inline void SetShader(ID3D11DeviceContext* _DC)override
		{
			SetVertexShader(_DC, LInput);
		}

		///////////////////////////////////////////////////////////////////////////////////

	private:

		ID3D11InputLayout* LInput = nullptr;


	};

	class PixelShader11 final :public ShaderObject11
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init(
			ID3D11Device* _Device
			, const void* _Binary
			, const unsigned long _BinarySize)
		{
			CreatePixelShader(_Device, _Binary, _BinarySize);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction/

		inline void SetShader(ID3D11DeviceContext* _DC)override
		{
			SetPixelShader(_DC);
		}

		///////////////////////////////////////////////////////////////////////////////////
	};

	class GeometryShader11 final :public ShaderObject11
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init(
			ID3D11Device* _Device
			, const void* _Binary
			, const unsigned long _BinarySize)
		{
			CreateGeometryShader(_Device, _Binary, _BinarySize);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction/

		inline void SetShader(ID3D11DeviceContext* _DC)override
		{
			SetGeometryShader(_DC);
		}

		///////////////////////////////////////////////////////////////////////////////////
	};

	class ComputeShader11 final :public ShaderObject11
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init(
			ID3D11Device* _Device
			, const void* _Binary
			, const unsigned long _BinarySize)
		{
			CreateComputeShader(_Device, _Binary, _BinarySize);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction/

		inline void SetShader(ID3D11DeviceContext* _DC)override
		{
			SetComputeShader(_DC);
		}

		///////////////////////////////////////////////////////////////////////////////////
	};

	class DomainShader11 final :public ShaderObject11
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init(
			ID3D11Device* _Device
			, const void* _Binary
			, const unsigned long _BinarySize)
		{
			CreateDomainShader(_Device, _Binary, _BinarySize);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction/

		inline void SetShader(ID3D11DeviceContext* _DC)override
		{
			SetDomainShader(_DC);
		}

		///////////////////////////////////////////////////////////////////////////////////
	};

}


#endif