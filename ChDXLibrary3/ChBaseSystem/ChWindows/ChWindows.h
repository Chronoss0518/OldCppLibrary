#ifdef _WINDOWS_

#ifndef Ch_Game_Windows_h
#define Ch_Game_Windows_h

#include"../ChBaseSystem/ChBaseSystem.h"
#include"../../WindowsObject/BaseWind/ChWinBaseWind.h"

namespace ChSystem
{
	LRESULT CALLBACK WndProc(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam);

	//Windows�ō쐬���ꂽWind��Windows�Ɋւ�����o�͂Ȃǂ��Ǘ������A//
	//WIndows�S�̂̊Ǘ��N���X//
	//��SingletonClass//
	//��������(�g�p�\�ł͂��邪�p���s��)//
	class Windows :public BaseSystem
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//Wind�̐���//
		void Init(const std::string& _APPName
			, const std::string& _WindClassName
			, const unsigned int _WindWidth
			, const unsigned int _WindHeight
			, const HINSTANCE _hInst
			, const int _nCmdShow);

		//Wind�̉��//
		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Wind�n���h���̎擾//
		inline const HWND GethWnd(void) const { return hWnd; }

		//���b�Z�[�W�̒l��Ԃ��֐�//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		unsigned long GetTime() { return timeGetTime(); }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�W���̃J�[�\����������悤�ɂ��邩�̃t���O//
		inline void IsCursollShou(const ChStd::Bool _f) { ShowCursor(_f); }

		//�L�[���������ۂ̃`�F�b�N���s���֐�//
		ChStd::Bool IsPushKey(const int _Key)override;

		//�L�[���������ۂɒ��������܂񂾂̃`�F�b�N���s���֐�//
		ChStd::Bool IsPushKeyNoHold(const int _Key)override;

		//�|�[�Y�����ǂ����𔻒f����֐��B//
		//�������̓|�[�Y�ֈڍs����{�^��//
		//�߂�l��True�������ꍇ�̓|�[�Y��//
		ChStd::Bool IsPause(const int _Key)override;

		//�`�F�b�N���b�Z�[�W�{�b�N�X�p�֐�//
		ChStd::Bool IsMessage(
			const std::string& _MainStr
			, const std::string& _SubStr);

		///////////////////////////////////////////////////////////////////////////////////

		void ErrerMessage(
			const std::string& _MainStr
			, const std::string& _SubStr)override
		{
			WMessage(_MainStr, _SubStr);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//���b�Z�[�W�{�b�N�X�p�֐�//
		inline void WMessage(
			const std::string& _MainStr
			, const std::string& _SubStr)
		{
			if (ChPtr::NullCheck(hWnd))return;

			MessageBox(
				hWnd
				, &_MainStr[0]
				, &_SubStr[0]
				, MB_OK);

		}

		///////////////////////////////////////////////////////////////////////////////////

		//WindMassage���m�F����֐�//
		ChStd::Bool CheckWinMessage();

		friend ChWin::WindObject;

		friend LRESULT CALLBACK WndProc(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

	protected:


		///////////////////////////////////////////////////////////////////////////////////

		//Windows�ł̃L�[�S�̂��`�F�b�N���邽�߂̊֐�//
		void SetKeyCode();

		virtual ChStd::Bool WindProc(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

		///////////////////////////////////////////////////////////////////////////////////

		ChStd::Bool IsKeyUpdate;

		std::string ClassName = "";


		HWND hWnd = nullptr;
		MSG msg;


	private:

		std::string WPP = "WinParam";

		std::map<unsigned int
			, std::function<ChStd::Bool(HWND _hWnd
				, WPARAM _wParam
				, LPARAM _lParam)>>WMFunction;

		void WMInit();

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//SetSingleton
		///////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////
		//WindowMassages//

		virtual ChStd::Bool OnActivate(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnChar(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnCharToItem(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnChildActivate(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnClear(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnClose(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnCommand(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnCreate(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnDeleteItem(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnDestroy(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnEnable(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnFontChange(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnKeyDown(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnKeyUp(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnLButtonDBClick(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnLButtonDown(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnLButtonUp(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnMButtonDBClick(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnMButtonDown(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnMButtonUp(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnMenuChar(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnMenuSelect(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnMouseMove(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnMouseWheel(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnMove(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnNCDestroy(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnNCHitTest(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnPaint(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnPaste(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnQuit(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnRButtonDBClick(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnRButtonDown(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnRButtonUp(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnSize(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnSysChar(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnSysCommand(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnSysKeyDown(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnSysKeyUp(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);

		virtual ChStd::Bool OnTimer(HWND _hWnd
			, WPARAM _wParam
			, LPARAM _lParam);


		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructor//

		Windows() {};

		~Windows() {};

	public:

		//�V���O���g���Ǘ��p//
		static Windows& GetIns()
		{
			static Windows Ins;
			return Ins;
		}

	};

	static const std::function<Windows&()> WinAPI = Windows::GetIns;


}

#endif
//CopyRight Chronoss0518 2018/08

#endif