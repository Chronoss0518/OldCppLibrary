
#include"../../BaseIncluder/ChBase.h"

#include"ChBitBool.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBitBoolƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void BitBool::SetBitFlg(const unsigned char _argsNum, const ChStd::Bool _flg)
{
	if (_argsNum > flgs.size() * 8)return;
	unsigned char tmp = 0;
	unsigned char flgNum = GetFlgNum(_argsNum);
	tmp = 0xff - flgNum;
	flgs[_argsNum / 8] &= tmp;

	if(_flg)flgs[_argsNum / 8] += flgNum;

}


void BitBool::SetBitTrue(const unsigned char _argsNum)
{
	if (GetBitFlg(_argsNum))return;

	flgs[_argsNum / 8] += GetFlgNum(_argsNum);

}


void BitBool::SetBitFalse(const unsigned char _argsNum)
{
	if (!GetBitFlg(_argsNum))return;

	flgs[_argsNum / 8]-= GetFlgNum(_argsNum);



}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool BitBool::GetBitFlg(const unsigned char _argsNum)
{
	if (_argsNum >  flgs.size() * 8)return false;

	return (flgs[static_cast<size_t>(_argsNum / 8)] & GetFlgNum(_argsNum)) > 0;
}
