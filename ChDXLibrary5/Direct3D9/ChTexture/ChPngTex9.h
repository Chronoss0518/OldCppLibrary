
#ifndef Ch_D3D9_TPng_h
#define Ch_D3D9_TPng_h

#include"ChBaseTexture9.h"

namespace ChTex
{

	class PngTex9 :public BaseTexture9
	{
	public:

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		void OpenFile(const std::string& _FileName)override;

		///////////////////////////////////////////////////////////////////////////////////

		struct CIHDR
		{
			//チャンクデータのサイズ//
			unsigned long Length;
			//チャンクタイプ//
			const unsigned char CType[5] = { 'I','H','D','R','\0' };
			//画像の幅//
			unsigned long CWData;
			//画像の高さ//
			unsigned long CHData;
			//ビット深度//
			unsigned char BD;
			//カラータイプ//
			unsigned char ColType;
			//圧縮手法//
			unsigned char Zips;
			//フィルター//
			unsigned char Fillter;
			//インターレース手法//
			unsigned char Interlase;
			//CTypeとCDataをもとに計算される//
			unsigned long CRC;

			CIHDR()
			{
				Length = 0;
				CWData = 0;
				CHData = 0;
				BD = 0;
				ColType = 0;
				Zips = 0;
				Fillter = 0;
				Interlase = 0;
				CRC = 0;
			}
		};

		///////////////////////////////////////////////////////////////////////////////////

		CIHDR SetChank(const std::string& _Str);


	};
}

#endif