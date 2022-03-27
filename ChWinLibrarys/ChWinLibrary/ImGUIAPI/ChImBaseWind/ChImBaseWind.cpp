
#include"../../ImGUILibrary/imgui.h"
#include"../../ImGUILibrary/imconfig.h"

#include"../../BaseIncluder/ChBase.h"
#include"../../CPP/ChBitBool/ChBitBool.h"

#include"ChImBaseWind.h"


ChStd::Bool ChImGui::BaseWind::BaseInitFlgment = false;

///////////////////////////////////////////////////////////////////////////////////
//BaseWindメソッド
///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::ImGuiFlagBase::Init()
{
	if (*this)return;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	SetInitFlg(true);
	BaseWind::BaseInitFlgment = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::ImGuiFlagBase::Release()
{
	if (!*this)return;

	SetInitFlg(false);

	if (WinRelease)WinRelease();

	if (D3D11Release)D3D11Release();

	if (D3D9Release)D3D9Release();

	ImGui::DestroyContext();
	BaseWind::BaseInitFlgment = false;
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::ImGuiFlagBase::DrawSetting()
{
	if (DrawSettingFlg)return;

	if (D3D11DrawSetting)D3D11DrawSetting();

	if (D3D9DrawSetting)D3D9DrawSetting();

	if (WinDrawSetting)WinDrawSetting();

	ImGui::NewFrame();

	DrawSettingFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::ImGuiFlagBase::Draw()
{
	if (!DrawSettingFlg)return;

	DrawSettingFlg = false;

	ImGui::EndFrame();

	ImGui::Render();

	if (D3D11Draw)
	{
		D3D11Draw();
		return;

	}

	if (D3D9Draw)
	{
		D3D9Draw();
		return;
	}

}

///////////////////////////////////////////////////////////////////////////////////
//BaseWindメソッド
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::SetWindSize(
	const ImVec2& _Vec
	, const ChStd::Bool _NotReSize)
{
	if (!IsBaseInit())return;

	WSize = _Vec;
	if (!_NotReSize)return;
	WFlg |= ImGuiWindowFlags_NoResize;
	RSizeFlg = _NotReSize;
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::SetWindSize(
	const ChVec2& _Vec
	, const ChStd::Bool _NotReSize)
{

	if (!IsBaseInit())return;

	SetWindSize(ImVec2(_Vec.x, _Vec.y), _NotReSize);


}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::SetWindSize(
	const float _w
	, const float _h
	, const ChStd::Bool _NotReSize)
{

	if (!IsBaseInit())return;

	SetWindSize(ImVec2(_w, _h), _NotReSize);
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::SetWindPos(
	const ImVec2& _Vec
	, const ChStd::Bool _NotMove)
{

	if (!IsBaseInit())return;

	WPos = _Vec;
	if (!_NotMove)return;
	WFlg |= ImGuiWindowFlags_NoMove;
	RMoveFlg = _NotMove;
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::SetWindPos(
	const ChVec2& _Vec
	, const ChStd::Bool _NotMove)
{

	if (!IsBaseInit())return;


	SetWindPos(ImVec2(_Vec.x, _Vec.y), _NotMove);

}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::SetWindPos(
	const float _w
	, const float _h
	, const ChStd::Bool _NotMove)
{

	if (!IsBaseInit())return;

	SetWindPos(ImVec2(_w, _h), _NotMove);
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChImGui::BaseWind::IsOpenButton(
	const std::string& _ButtonName
	, const ChStd::Bool _SameLineFlg
	, const std::string& _SubName)
{

	if (!GetFlgManager().IsWindOpen())return false;

	std::string ButtonName = _ButtonName;

	if (_SubName.length() > 0)ButtonName += "##" + _SubName;

	if (_SameLineFlg)ImGui::SameLine();

	return ImGui::Button(ButtonName.c_str());

}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChImGui::BaseWind::IsBaseInit()
{
	return BaseInitFlgment;
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::InputText(
	std::string& _Text
	, const std::string& _Label
	, const unsigned long _MaxTextNum)
{

	if (!IsBaseInit())return;
	if (!GetFlgManager().IsWindOpen())return;

	char* Tmp = new char[_MaxTextNum];

	memcpy(Tmp, _Text.c_str(), _Text.size() + 1);

	ImGui::InputText(_Label.c_str(), Tmp, _MaxTextNum);

	_Text = Tmp;

	delete[] Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::DragFloat(
	float& _Val
	, const std::string& _Label
	, const float _Min
	, const float _Max
	, const float _Speed)
{

	if (!GetFlgManager().IsWindOpen())return;

	ImGui::DragFloat(
		_Label.c_str()
		, &_Val
		, _Speed
		, _Min
		, _Max);

}

void ChImGui::BaseWind::SliderFloat(
	float& _Val
	, const std::string& _Label
	, const float _Min
	, const float _Max)
{

	if (!GetFlgManager().IsWindOpen())return;

	ImGui::SliderFloat(
		_Label.c_str()
		, &_Val
		, _Min
		, _Max);
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::DragVector2(
	float& _x
	, float& _y
	, const std::string& _Label
	, const float _Min
	, const float _Max
	, const float _Speed)
{

	if (!IsBaseInit())return;
	if (!GetFlgManager().IsWindOpen())return;

	float Tmp[2]{ _x,_y };

	ImGui::DragFloat2(
		_Label.c_str()
		, Tmp
		, _Speed
		, _Min
		, _Max);

	_x = Tmp[0];
	_y = Tmp[1];
}

void ChImGui::BaseWind::SliderVector2(
	float& _x
	, float& _y
	, const std::string& _Label
	, const float _Min
	, const float _Max)
{

	if (!IsBaseInit())return;
	if (!GetFlgManager().IsWindOpen())return;

	float Tmp[2]{ _x,_y };

	ImGui::SliderFloat2(
		_Label.c_str()
		, Tmp
		, _Min
		, _Max);

	_x = Tmp[0];
	_y = Tmp[1];
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::DragVector3(
	float& _x
	, float& _y
	, float& _z
	, const std::string& _Label
	, const float _Min
	, const float _Max
	, const float _Speed)
{
	if (!IsBaseInit())return;
	if (!GetFlgManager().IsWindOpen())return;


	float Tmp[3]{ _x,_y,_z };

	ImGui::DragFloat3(
		_Label.c_str()
		, Tmp
		, _Speed
		, _Min
		, _Max);

	_x = Tmp[0];
	_y = Tmp[1];
	_z = Tmp[2];

}

void ChImGui::BaseWind::SliderVector3(
	float& _x
	, float& _y
	, float& _z
	, const std::string& _Label
	, const float _Min
	, const float _Max)
{
	if (!IsBaseInit())return;
	if (!GetFlgManager().IsWindOpen())return;



	float Tmp[3]{ _x,_y,_z };

	ImGui::SliderFloat3(
		_Label.c_str()
		, Tmp
		, _Min
		, _Max);

	_x = Tmp[0];
	_y = Tmp[1];
	_z = Tmp[2];
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::DragVector4(
	float& _x
	, float& _y
	, float& _z
	, float& _w
	, const std::string& _Label
	, const float _Min
	, const float _Max
	, const float _Speed)
{

	if (!IsBaseInit())return;
	if (!GetFlgManager().IsWindOpen())return;

	float Tmp[4]{ _x,_y,_z,_w };

	ImGui::DragFloat4(
		_Label.c_str()
		, Tmp
		, _Speed
		, _Min
		, _Max);

	_x = Tmp[0];
	_y = Tmp[1];
	_z = Tmp[2];
	_w = Tmp[3];
}

void ChImGui::BaseWind::SliderVector4(
	float& _x
	, float& _y
	, float& _z
	, float& _w
	, const std::string& _Label
	, const float _Min
	, const float _Max)
{
	if (!IsBaseInit())return;
	if (!GetFlgManager().IsWindOpen())return;


	float Tmp[4]{ _x,_y,_z,_w };

	ImGui::SliderFloat3(
		_Label.c_str()
		, Tmp
		, _Min
		, _Max);

	_x = Tmp[0];
	_y = Tmp[1];
	_z = Tmp[2];
	_w = Tmp[3];
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::EditColor(
	float& _a
	, float& _r
	, float& _g
	, float& _b
	, const std::string& _Label)
{
	if (!IsBaseInit())return;
	if (!GetFlgManager().IsWindOpen())return;

	float Tmp[4] = { _a, _r,_g,_b };

	ImGui::ColorEdit4(_Label.c_str(), Tmp);

	_a = Tmp[0];
	_r = Tmp[1];
	_g = Tmp[2];
	_b = Tmp[3];

}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::WindBegin(const std::string& _WindName)
{
	if (!IsBaseInit())return;
	if (IsIOpen())return;

	GetFlgManager().DrawSetting();

	ImGuiWindowFlags TmpFlg = WFlg;

	ChStd::Bool TmpOnceFlg = false;

	if (WSize.x > 0 && WSize.y > 0 && !OnceFlg)
	{
		ImGuiCond STest = ImGuiCond_Once;

		if (RSizeFlg)
		{
			STest = ImGuiCond_Always;
			TmpOnceFlg = true;
		}
		ImGui::SetNextWindowSize(WSize, STest);

	}

	if (WPos.x >= 0 && WPos.y >= 0 && !OnceFlg)
	{

		ImGuiCond MTest = ImGuiCond_Once;

		if (RSizeFlg) 
		{
			MTest = ImGuiCond_Always;
			TmpOnceFlg = true;
		}

		ImGui::SetNextWindowPos(WPos, MTest);

	}

	if (TmpOnceFlg)OnceFlg = true;

	ImGui::Begin(_WindName.c_str(), nullptr, TmpFlg);

	GetFlgManager().SetWindOpen(true);
	SetIOpenFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::WindEnd()
{
	if (!IsBaseInit())return;
	if (!GetFlgManager().IsWindOpen())return;
	if (!IsIOpen())return;


	ImGui::End();

	GetFlgManager().SetWindOpen(false);
	SetIOpenFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::CreateJapaneseLangage()
{

}

///////////////////////////////////////////////////////////////////////////////////

void ChImGui::BaseWind::Draw()
{

	if (!IsBaseInit())return;
	if (GetFlgManager().IsWindOpen())return;

	GetFlgManager().Draw();

}

///////////////////////////////////////////////////////////////////////////////////

ChImGui::ImGuiWindObject::ImGuiWindObject(const std::string& _WindName)
{
	if (!IsBaseInit())return;
	if (GetFlgManager().IsWindOpen())return;

	WindBegin(_WindName);
}

///////////////////////////////////////////////////////////////////////////////////

ChImGui::ImGuiWindObject::ImGuiWindObject(
	const std::string& _WindName
	, const BaseWind& _Wind)
{
	if (!IsBaseInit())return;
	if (GetFlgManager().IsWindOpen())return;
	BaseWind Tmp = _Wind;

	(BaseWind)*this = Tmp;

	WindBegin(_WindName);
}
