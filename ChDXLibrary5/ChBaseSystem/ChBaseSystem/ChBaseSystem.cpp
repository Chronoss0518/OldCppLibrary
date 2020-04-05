
#include"../../ChInclude/ChGameBI.h"
#include"../../CPP/ChBitBool/ChBitBool.h"
#include"ChBaseSystem.h"

using namespace ChSystem;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseSystem ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////


ChStd::Bool BaseSystem::IsPushKey(const int _Key)
{
	if (!System->IsUseSystemButtons())return 0;
	return ButtonList.GetBitFlg(_Key);
}

ChStd::Bool BaseSystem::IsPushKeyNoHold(const int _Key)
{
	return ButtonList.GetBitFlg(_Key);
}

ChStd::Bool BaseSystem::IsPause(const int _Key)
{
	return false;
}
