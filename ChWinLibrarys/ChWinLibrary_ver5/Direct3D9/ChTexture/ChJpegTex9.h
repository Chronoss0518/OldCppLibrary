
#ifndef Ch_D3D9_TJpeg_h
#define Ch_D3D9_TJpeg_h

#include"ChBaseTexture9.h"

namespace ChTex
{

	class JpegTex :public BaseTexture9
	{
	protected:

		///////////////////////////////////////////////////////////////////////////////////

		void OpenFile(const std::string& _fileName)override;

		///////////////////////////////////////////////////////////////////////////////////

		struct S_SOF
		{
			//マーカー識別子//
			const unsigned char MType[3] = { 0xff,0xc0,'\0' };
			//セグメントの長さ//	
			unsigned short S_Len;
			//サンプルの精度//
			unsigned char Sample;
			//画像の高さ//
			unsigned short TexHeight;
			//画像の幅//
			unsigned short TexWidht;
			//構成要素数//
			unsigned char TypeCnt;

			S_SOF()
			{
				S_Len = 0;
				Sample = 0;
				TexHeight = 0;
				TexWidht = 0;
				TypeCnt = 0;
			}

		};

		///////////////////////////////////////////////////////////////////////////////////

		S_SOF SetSegment(const std::string& _str);

	};
}


#endif
