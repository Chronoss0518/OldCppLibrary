
#include"../../BaseIncluder/ChBase.h"

#include"ChBitBool.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBitBoolƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void BitBool::SetBitFlg(const unsigned char _ArgsNum, const ChStd::Bool _Flg)
{
	if (_ArgsNum > Flg.size() * 8)return;
	unsigned char tmp = 0;
	unsigned char FlgNum = GetFlgNum(_ArgsNum);
	tmp = 0xff - FlgNum;
	Flg[_ArgsNum / 8] &= tmp;

	if(_Flg)Flg[_ArgsNum / 8] += FlgNum;

}


void BitBool::SetBitTrue(const unsigned char _ArgsNum)
{
	if (GetBitFlg(_ArgsNum))return;

	Flg[_ArgsNum / 8] += GetFlgNum(_ArgsNum);

}


void BitBool::SetBitFalse(const unsigned char _ArgsNum)
{
	if (!GetBitFlg(_ArgsNum))return;

	Flg[_ArgsNum / 8]-= GetFlgNum(_ArgsNum);



}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool BitBool::GetBitFlg(const unsigned char _ArgsNum)
{
	if (_ArgsNum >  Flg.size() * 8)return false;

	return (Flg[static_cast<size_t>(_ArgsNum / 8)] & GetFlgNum(_ArgsNum)) > 0;
}
