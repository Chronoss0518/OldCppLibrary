
#include"../../BaseIncluder/ChBase.h"

#include"ChScript.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////
//ChScriptControllerÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

void ScriptController::SetScript(
	const std::function<void()> _update
	, const std::function<void()> _draw
	, const std::function<void()> _enter
	, const std::function<void()> _exit)
{
	auto TmpScr = ChPtr::Make_S<ChScript>();

	TmpScr->update = _update;
	TmpScr->draw = _draw;
	TmpScr->enter = _enter;
	TmpScr->exit = _exit;

	TmpScr->myNum = scriptList.size();

	scriptList.push_back(TmpScr);

	if (nowScript.lock() != nullptr)return;

	ChangeScript(0);

	Chenge();
}
