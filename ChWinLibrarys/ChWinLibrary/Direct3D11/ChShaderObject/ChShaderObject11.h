#ifndef Ch_D3D11_SObject_h
#define Ch_D3D11_SObject_h

namespace ChD3D11
{

	enum class ShaderType
	{
		Vertex, Pixel, Geometry, Compute, Domain
	};

	class ShaderObject11:public ChCpp::ChCp::Initializer,public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Init(ID3D11Device* _Device);

		virtual void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//CreateFunction//

		virtual void CreateVertexShader(
			const D3D11_INPUT_ELEMENT_DESC* _Desc
			, const unsigned long _DescNum
			, const void* _Binary
			, const unsigned long _BinarySize
		);

		//VertexShader用//
		virtual void CreatePixelShader(
			const void* _Binary
			, const unsigned long _BinarySize
		);

		//VertexShader用//
		virtual void CreateGeometryShader(
			const void* _Binary
			, const unsigned long _BinarySize
		);

		//VertexShader用//
		virtual void CreateComputeShader(
			const void* _Binary
			, const unsigned long _BinarySize
		);

		//VertexShader用//
		virtual void CreateDomainShader(
			const void* _Binary
			, const unsigned long _BinarySize
		);

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction/

		void SetShader(
			ID3D11DeviceContext* _DC
		);

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		
		std::map<ShaderType, std::function<void(ID3D11DeviceContext*)>>GetShaderSetter()
		{
			return ShaderSetter;
		}

	private:

		ShaderType Type = ShaderType::Vertex;

		ID3D11DeviceChild* Shader = nullptr;

		ID3D11InputLayout* LInput = nullptr;

		ID3D11Device* Device = nullptr;

		std::map<ShaderType, std::function<void(ID3D11DeviceContext*)>>ShaderSetter
		{
			{
				ShaderType::Vertex,
				[&](ID3D11DeviceContext* _DC)
				{
					auto Tmp = static_cast<ID3D11VertexShader*>(Shader);

					_DC->IASetInputLayout(LInput);

					_DC->VSSetShader(Tmp, nullptr, 0);
				}
			},
			{
				ShaderType::Pixel,
				[&](ID3D11DeviceContext* _DC)
				{
					auto Tmp = static_cast<ID3D11PixelShader*>(Shader);

					_DC->PSSetShader(Tmp, nullptr, 0);
				}
			},
			{
				ShaderType::Geometry,
				[&](ID3D11DeviceContext* _DC)
				{
					auto Tmp = static_cast<ID3D11GeometryShader*>(Shader);

					_DC->GSSetShader(Tmp, nullptr, 0);
				}
			},
			{
				ShaderType::Compute,
				[&](ID3D11DeviceContext* _DC)
				{
					auto Tmp = static_cast<ID3D11ComputeShader*>(Shader);

					_DC->CSSetShader(Tmp, nullptr, 0);
				}
			},
			{
				ShaderType::Domain,
				[&](ID3D11DeviceContext* _DC)
				{
					auto Tmp = static_cast<ID3D11DomainShader*>(Shader);

					_DC->DSSetShader(Tmp, nullptr, 0);
				}
			}
		};


	};

}


#endif