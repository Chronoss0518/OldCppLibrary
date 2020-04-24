
#include"../../ChGameIncludeFile.h"
#include"ChBitBool.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBitBoolƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////


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
	if (_ArgsNum >  Flg.size() * 8)return ChStd::False;

	return (Flg[static_cast<size_t>(_ArgsNum / 8)] & GetFlgNum(_ArgsNum)) > 0;
}
