
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
			//�`�����N�f�[�^�̃T�C�Y//
			unsigned long Length;
			//�`�����N�^�C�v//
			const unsigned char CType[5] = { 'I','H','D','R','\0' };
			//�摜�̕�//
			unsigned long CWData;
			//�摜�̍���//
			unsigned long CHData;
			//�r�b�g�[�x//
			unsigned char BD;
			//�J���[�^�C�v//
			unsigned char ColType;
			//���k��@//
			unsigned char Zips;
			//�t�B���^�[//
			unsigned char Fillter;
			//�C���^�[���[�X��@//
			unsigned char Interlase;
			//CType��CData�����ƂɌv�Z�����//
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