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

		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitFlg(const unsigned char _argsNum,const ChStd::Bool _flg);

		//引数で選択された位置のビットをtrueをセットする//
		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitTrue(const unsigned char _argsNum);

		//引数で選択された位置のビットをfalseをセットする//
		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitFalse(const unsigned char _argsNum);

		inline void SetAllDownFlg()
		{
			for (auto&& flg : flgs)
			{
				flg = 0;
			}
		}

		//1バイトごとでフラグ数を変更する//
		//(1以下にはならない)//
		inline void SetSize(const unsigned char _byteCount)
		{
			if (_byteCount <= 0)return;
			flgs.resize(_byteCount);
		}

		//////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//引数で選択された数値のビットの値によって//
		//ChStd::TrueかChStd::Falseを返す//
		ChStd::Bool GetBitFlg(const unsigned char _argsNum);

		//使用可能サイズ//
		inline unsigned long  GetSize()
		{
			return static_cast<unsigned long>(flgs.size() * 8);
		}

		//フラグ数の指定でのTrueの個数取得//
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