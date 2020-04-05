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

		//引数で選択された位置のビットをtrueをセットする//
		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitTrue(const unsigned char _ArgsNum);

		//引数で選択された位置のビットをfalseをセットする//
		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitFalse(const unsigned char _ArgsNum);

		inline void SetAllDownFlg()
		{
			for (auto&& flg : Flg)
			{
				flg = 0;
			}
		}

		//1バイトごとでフラグ数を変更する//
		//(1以下にはならない)//
		inline void SetSize(const unsigned char _ByteCount)
		{
			if (_ByteCount <= 0)return;
			Flg.resize(_ByteCount);
		}

		//////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//引数で選択された数値のビットの値によって//
		//ChStd::TrueかChStd::Falseを返す//
		ChStd::Bool GetBitFlg(const unsigned char _ArgsNum);

		//使用可能サイズ//
		inline unsigned long  GetSize()
		{
			return static_cast<unsigned long>(Flg.size() * 8);
		}

		//フラグ数の指定でのTrueの個数取得//
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