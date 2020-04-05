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
			Flg.resize(1);
		}

		BitBool(const unsigned char _Size)
		{
			SetSize(_Size);
		}

		virtual ~BitBool()
		{
			Flg.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�����őI�����ꂽ�ʒu�̃r�b�g��true���Z�b�g����//
		//�������̓A�h���X���̈�ԏ������r�b�g���琔�������l�����//
		//��)�A�h���X�ʒu��1000��,�I���ӏ�1001�Ԃ̏ꍇ��1��I��//
		void SetBitTrue(const unsigned char _ArgsNum);

		//�����őI�����ꂽ�ʒu�̃r�b�g��false���Z�b�g����//
		//�������̓A�h���X���̈�ԏ������r�b�g���琔�������l�����//
		//��)�A�h���X�ʒu��1000��,�I���ӏ�1001�Ԃ̏ꍇ��1��I��//
		void SetBitFalse(const unsigned char _ArgsNum);

		inline void SetAllDownFlg()
		{
			for (auto&& flg : Flg)
			{
				flg = 0;
			}
		}

		//1�o�C�g���ƂŃt���O����ύX����//
		//(1�ȉ��ɂ͂Ȃ�Ȃ�)//
		inline void SetSize(const unsigned char _ByteCount)
		{
			if (_ByteCount <= 0)return;
			Flg.resize(_ByteCount);
		}

		//////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�����őI�����ꂽ���l�̃r�b�g�̒l�ɂ����//
		//ChStd::True��ChStd::False��Ԃ�//
		ChStd::Bool GetBitFlg(const unsigned char _ArgsNum);

		//�g�p�\�T�C�Y//
		inline unsigned long  GetSize()
		{
			return static_cast<unsigned long>(Flg.size() * 8);
		}

		//�t���O���̎w��ł�True�̌��擾//
		inline unsigned long GetTrueCnt(const unsigned long& _Cnt)
		{

			unsigned char Cnt = 0;

			for (unsigned char i = 0; i < _Cnt; i++)
			{
				if (!GetBitFlg(i))continue;
				Cnt++;
			}

			return Cnt;
		}

		inline unsigned long GetTrueCnt()
		{
			return GetTrueCnt(Flg.size() * 8);

		}

	protected:

		inline unsigned char GetFlgNum(const unsigned char _ArgsNum)
		{
			unsigned char Num = 1;

			Num = Num << ((_ArgsNum % 8));

			return Num;
		}

		std::vector<unsigned char> Flg = { 0 };

	};
}


#endif