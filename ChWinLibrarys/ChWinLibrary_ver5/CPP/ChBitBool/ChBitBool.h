#ifndef Ch_CPP_BiBo_h
#define Ch_CPP_BiBo_h

namespace ChCpp
{

	 class BitBool
	{
	public:


		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BitBool()
		{
			flgs.resize(1);
		}

		BitBool(const unsigned char _size)
		{
			SetSize(_size);
		}

		virtual ~BitBool()
		{
			flgs.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�������̓A�h���X���̈�ԏ������r�b�g���琔�������l�����//
		//��)�A�h���X�ʒu��1000��,�I���ӏ�1001�Ԃ̏ꍇ��1��I��//
		void SetBitFlg(const unsigned char _argsNum,const ChStd::Bool _flg);

		//�����őI�����ꂽ�ʒu�̃r�b�g��true���Z�b�g����//
		//�������̓A�h���X���̈�ԏ������r�b�g���琔�������l�����//
		//��)�A�h���X�ʒu��1000��,�I���ӏ�1001�Ԃ̏ꍇ��1��I��//
		void SetBitTrue(const unsigned char _argsNum);

		//�����őI�����ꂽ�ʒu�̃r�b�g��false���Z�b�g����//
		//�������̓A�h���X���̈�ԏ������r�b�g���琔�������l�����//
		//��)�A�h���X�ʒu��1000��,�I���ӏ�1001�Ԃ̏ꍇ��1��I��//
		void SetBitFalse(const unsigned char _argsNum);

		inline void SetAllDownFlg()
		{
			for (auto&& flg : flgs)
			{
				flg = 0;
			}
		}

		//1�o�C�g���ƂŃt���O����ύX����//
		//(1�ȉ��ɂ͂Ȃ�Ȃ�)//
		inline void SetSize(const unsigned char _byteCount)
		{
			if (_byteCount <= 0)return;
			flgs.resize(_byteCount);
		}

		//////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�����őI�����ꂽ���l�̃r�b�g�̒l�ɂ����//
		//ChStd::True��ChStd::False��Ԃ�//
		ChStd::Bool GetBitFlg(const unsigned char _argsNum);

		//�g�p�\�T�C�Y//
		inline unsigned long  GetSize()
		{
			return static_cast<unsigned long>(flgs.size() * 8);
		}

		//�t���O���̎w��ł�True�̌��擾//
		inline unsigned long GetTrueCnt(const unsigned long& _cnt)
		{

			unsigned char cnt = 0;

			for (unsigned char i = 0; i < _cnt; i++)
			{
				if (!GetBitFlg(i))continue;
				cnt++;
			}

			return cnt;
		}

		inline unsigned long GetTrueCnt()
		{
			return GetTrueCnt(flgs.size() * 8);

		}

	protected:

		inline unsigned char GetFlgNum(const unsigned char _argsNum)
		{
			unsigned char num = 1;

			num = num << ((_argsNum % 8));

			return num;
		}

		std::vector<unsigned char> flgs = { 0 };

	};
}


#endif