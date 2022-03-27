
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
			//�}�[�J�[���ʎq//
			const unsigned char MType[3] = { 0xff,0xc0,'\0' };
			//�Z�O�����g�̒���//	
			unsigned short S_Len;
			//�T���v���̐��x//
			unsigned char Sample;
			//�摜�̍���//
			unsigned short TexHeight;
			//�摜�̕�//
			unsigned short TexWidht;
			//�\���v�f��//
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
