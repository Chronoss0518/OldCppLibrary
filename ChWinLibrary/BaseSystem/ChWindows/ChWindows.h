#ifdef _WINDOWS_

#ifndef Ch_Game_Windows_h
#define Ch_Game_Windows_h

#include"../ChBaseSystem/ChBaseSystem.h"
#include"../../WindowsObject/BaseWind/ChWinBaseWind.h"

namespace ChWin
{

	std::map<int, std::string> GetWindowsKeyName();

	class WindObject;
}

namespace ChSystem
{
	LRESULT CALLBACK WndProc(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam);


	//Windowsで作成されたWindとWindowsに関する入出力などを管理した、//
	//WIndows全体の管理クラス//
	//※SingletonClass//
	//※改装中(使用可能ではあるが継承不可)//
	class Windows :public BaseSystem
	{
	public:

		Windows() {};

		~Windows() {};

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//Windの生成//
		void Init(const std::string& _APPName
			, const std::string& _WindClassName
			, const unsigned int _WindWidth
			, const unsigned int _WindHeight
			, const HINSTANCE _hInst
			, const int _nCmdShow);

		//Windの解放//
		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Windハンドルの取得//
		inline const HWND GethWnd(void) const { return hWnd; }

		//メッセージの値を返す関数//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		unsigned long GetTime() { return timeGetTime(); }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//標準のカーソルを見えるようにするかのフラグ//
		inline void IsCursollShou(const ChStd::Bool _f) { ShowCursor(_f); }

		//キーを押した際のチェックを行う関数//
		ChStd::Bool IsPushKey(const int _Key)override;

		//キーを押した際に長押しを含んだのチェックを行う関数//
		ChStd::Bool IsPushKeyNoHold(const int _Key)override;

		//ポーズ中かどうかを判断する関数。//
		//第一引数はポーズへ移行するボタン//
		//戻り値がTrueだった場合はポーズ中//
		ChStd::Bool IsPause(const int _Key)override;

		//チェックメッセージボックス用関数//
		ChStd::Bool IsMessage(
			const std::string& _MainStr
			, const std::string& _SubStr);

		//WindMassageを確認する関数//
		ChStd::Bool IsUpdate();

		///////////////////////////////////////////////////////////////////////////////////

		void ErrerMessage(
			const std::string& _MainStr
			, const std::string& _SubStr)override
		{
			WMessage(_MainStr, _SubStr);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//メッセージボックス用関数//
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

		friend ChWin::WindObject;

		friend LRESULT CALLBACK WndProc(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

		static std::function<ChStd::Bool(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam)>ImGuiProc;

	protected:


		virtual ChStd::Bool WndProcs(
			const HWND _hWnd
			, const UINT _uMsg
			, const WPARAM _wParam
			, const LPARAM _lParam);

		///////////////////////////////////////////////////////////////////////////////////

		//Windowsでのキー全体をチェックするための関数//
		void SetKeyCode();

		///////////////////////////////////////////////////////////////////////////////////

		ChStd::Bool IsKeyUpdate;

		std::string ClassName = "";


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

	static inline void ToRelativePath(std::string&_Path)
	{

		if (_Path.find(":\\") == _Path.npos && _Path.find(":/") == _Path.npos)return;

		std::string Tmp;


		{

			char* Tmp2 = nullptr;
			Tmp2 = new char[256];

			GetCurrentDirectory(256, Tmp2);
			Tmp = Tmp2;

			delete[] Tmp2;

		}

		std::string SetCutChar = "/";
		{

			std::string OutCutChar = "\\";

			while (1)
			{
				size_t TmpLen = Tmp.find(OutCutChar, 0);
				if (TmpLen == Tmp.npos)break;
				Tmp.replace(TmpLen, OutCutChar.size(), SetCutChar);

			}
			while (1)
			{
				size_t TmpLen = _Path.find(OutCutChar, 0);
				if (TmpLen == _Path.npos)break;
				_Path.replace(TmpLen, OutCutChar.size(), SetCutChar);

			}

			std::string TmpBackChar = "";


			while (1)
			{
				size_t TmpLen = _Path.find(Tmp);

				if (TmpLen != _Path.npos)break;

				TmpLen = Tmp.rfind(SetCutChar, Tmp.length());

				Tmp.replace(TmpLen, Tmp.length() - TmpLen, "");

				TmpBackChar += "../";

			}



			_Path.replace(0, Tmp.length() + 1, "");

			_Path = TmpBackChar + _Path;



		}

	}
}

#endif
//CopyRight Chronoss0518 2018/08

#endif