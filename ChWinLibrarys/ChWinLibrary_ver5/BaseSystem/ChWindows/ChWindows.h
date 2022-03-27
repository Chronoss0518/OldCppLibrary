#ifdef _WINDOWS_

#ifndef Ch_Game_Windows_h
#define Ch_Game_Windows_h

#include"../ChBaseSystem/ChBaseSystem.h"
#include"../../WindowsObject/BaseWind/ChWinBaseWind.h"

namespace ChWin
{

	class WindObject;
}

namespace ChSystem
{
	LRESULT CALLBACK WndProc(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam);

	using ChWinProc = std::function<ChStd::Bool(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam)>;

	//Windowsで作成されたWindとWindowsに関する入出力などを管理した、//
	//WIndows全体の管理クラス//
	class Windows :public BaseSystem,public ChCp::Releaser
	{
	public:

		Windows() {};

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//Windの生成//
		void Init(const std::string& _aPPName
			, const std::string& _windClassName
			, const unsigned int _windWidth
			, const unsigned int _windHeight
			, const HINSTANCE _hInst
			, const int _nCmdShow);

		//Windの解放//
		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetWinProcedure(const ChWinProc& _proce)
		{
			WinProcs = _proce;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Windハンドルの取得//
		inline HWND GethWnd(void) const { return hWnd; }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		unsigned long GetNowTime()override { return timeGetTime(); }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//標準のカーソルの表示フラグ//
		inline void IsCursollShou(const ChStd::Bool _f) { ShowCursor(_f); }

		//キーを押した際のチェックを行う関数//
		ChStd::Bool IsPushKey(const int _key)override;

		//キーを押した際に長押しを含んだのチェックを行う関数//
		ChStd::Bool IsPushKeyNoHold(const int _key)override;

		//ポーズ中かどうかを判断する関数。//
		//第一引数はポーズへ移行するボタン//
		//戻り値がTrueだった場合はポーズ中//
		ChStd::Bool IsPause(const int _key)override;

		//チェックメッセージボックス用関数//
		ChStd::Bool IsMessage(
			const std::string& _mainStr
			, const std::string& _subStr);

		//WindMassageを確認する関数//
		ChStd::Bool IsUpdate();

		///////////////////////////////////////////////////////////////////////////////////

		void ErrerMessage(
			const std::string& _mainStr
			, const std::string& _subStr)override
		{
			WMessage(_mainStr, _subStr);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//メッセージボックス用関数//
		inline void WMessage(
			const std::string& _mainStr
			, const std::string& _subStr)
		{
			if (ChPtr::NullCheck(hWnd))return;

			MessageBox(
				hWnd
				, &_mainStr[0]
				, &_subStr[0]
				, MB_OK);

		}

		///////////////////////////////////////////////////////////////////////////////////

		friend ChWin::WindObject;

		friend LRESULT CALLBACK ChSystem::WndProc(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

		static ChWinProc ImGuiProc;

	protected:

		ChWinProc WinProcs;

		///////////////////////////////////////////////////////////////////////////////////

		//Windowsでのキー全体をチェックするための関数//
		void SetKeyCode();

		///////////////////////////////////////////////////////////////////////////////////

		ChStd::Bool isKeyUpdate;

		std::string className = "";


		HWND hWnd = nullptr;
		MSG msg{ 0 };


	private:

		std::string WPP = "WinParam";

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//SetSingleton
		///////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructor//

	public:

	};

	static inline void ToRelativePath(std::string&_path)
	{

		if (_path.find(":\\") == _path.npos && _path.find(":/") == _path.npos)return;

		std::string tmp;


		{

			char* tmp2 = nullptr;
			tmp2 = new char[256];

			GetCurrentDirectory(256, tmp2);
			tmp = tmp2;

			delete[] tmp2;

		}

		std::string SetCutChar = "/";
		{

			std::string OutCutChar = "\\";

			while (1)
			{
				size_t tmpLen = tmp.find(OutCutChar, 0);
				if (tmpLen == tmp.npos)break;
				tmp.replace(tmpLen, OutCutChar.size(), SetCutChar);

			}
			while (1)
			{
				size_t tmpLen = _path.find(OutCutChar, 0);
				if (tmpLen == _path.npos)break;
				_path.replace(tmpLen, OutCutChar.size(), SetCutChar);

			}

			std::string tmpBackChar = "";


			while (1)
			{
				size_t tmpLen = _path.find(tmp);

				if (tmpLen != _path.npos)break;

				tmpLen = tmp.rfind(SetCutChar, tmp.length());

				tmp.replace(tmpLen, tmp.length() - tmpLen, "");

				tmpBackChar += "../";

			}



			_path.replace(0, tmp.length() + 1, "");

			_path = tmpBackChar + _path;



		}

	}
}

#endif
//CopyRight Chronoss0518 2018/08

#endif