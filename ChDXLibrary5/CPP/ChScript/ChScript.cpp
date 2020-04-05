
#include"../../ChInclude/ChGameBI.h"

#include"ChScript.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////
//ChScriptControllerÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

void ScriptController::SetScript(
	const std::function<void()> _Update
	, const std::function<void()> _Draw
	, const std::function<void()> _Enter
	, const std::function<void()> _Exit)
{
	auto TmpScr = ChPtr::Make_S<ChScript>();

	TmpScr->Update = _Update;
	TmpScr->Draw = _Draw;
	TmpScr->Enter = _Enter;
	TmpScr->Exit = _Exit;

	TmpScr->MyNum = ScriptList.size();

	ScriptList.push_back(TmpScr);

	if (NowScript.lock() != nullptr)return;

	ChangeScript(0);

	Chenge();
}
