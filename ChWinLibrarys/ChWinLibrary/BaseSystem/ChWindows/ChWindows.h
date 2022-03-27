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

	using ChWinProc = std::function<ChStd::Bool(
		HWND _hWnd
		, UINT _uMsg
		, WPARAM _wParam
		, LPARAM _lParam)>;

	//Windows�ō쐬���ꂽWind��Windows�Ɋւ�����o�͂Ȃǂ��Ǘ������A//
	//WIndows�S�̂̊Ǘ��N���X//
	class Windows :public BaseSystem,public ChCpp::ChCp::Releaser
	{
	public:

		Windows() {};

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
		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetWinProcedure(const ChWinProc& _Proce)
		{
			WinProcs = _Proce;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Wind�n���h���̎擾//
		inline HWND GethWnd(void) const { return hWnd; }

		//���b�Z�[�W�̒l��Ԃ��֐�//
		inline const LPMSG GetReturnMassage(void) const { return const_cast<const LPMSG>(&msg); }

		unsigned long GetNowTime()override { return timeGetTime(); }

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

		//WindMassage���m�F����֐�//
		ChStd::Bool IsUpdate();

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

		friend ChWin::WindObject;

		friend LRESULT CALLBACK WndProc(
			HWND _hWnd
			, UINT _uMsg
			, WPARAM _wParam
			, LPARAM _lParam);

		static ChWinProc ImGuiProc;

	protected:

		ChWinProc WinProcs;

		///////////////////////////////////////////////////////////////////////////////////

		//Windows�ł̃L�[�S�̂��`�F�b�N���邽�߂̊֐�//
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