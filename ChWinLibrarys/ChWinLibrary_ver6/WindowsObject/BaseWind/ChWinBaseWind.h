#ifdef _WINDOWS_

#ifndef Ch_Win_BObj_h
#define Ch_Win_BObj_h

#include"../../BaseIncluder/ChBase.h"
#include"ChWinBaseWind.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{
	struct CPOINT :public POINT
	{
		CPOINT&operator =(const POINT& _Pos)
		{
			x = _Pos.x;
			y = _Pos.y;
			return *this;
		}

		CPOINT operator + (const POINT& _Pos)const
		{
			CPOINT Tmp = *this;
			Tmp.x = _Pos.x;
			Tmp.y = _Pos.y;
			return Tmp;
		}
	};


	 void ObjUpdate(const WPARAM& _wParam);

	 void WindMoveUpdate(const HWND _hWnd, LPARAM _lParam);

	 void WindSizeUpdate(const HWND _hWnd, LPARAM _lParam);

	typedef class WindObject :public ChCpp::ChCp::Initializer,public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline WindObject() {};

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const HWND& _hWnd);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline const HWND GethWnd()const { return HIns; }

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//移動させないためのフラグ//
		inline void SetNoMoveFlg(const ChStd::Bool _Flg) { NotCMoveFlg = _Flg; }

		//サイズ変更させないためのフラグ//
		inline void SetNoSizeFlg(const ChStd::Bool _Flg) { NotCSizeFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////////

		void Move(const int _x
			, const int _y
			, const int _w
			, const int _h);

		void Move(const int _x
			, const int _y);

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void Update(const WPARAM& _wParam)
		{
			UpdateWindow(HIns);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		void ReSize(
			const int _w
			, const int _h);

		///////////////////////////////////////////////////////////////////////////////////////

		friend void ObjUpdate(const WPARAM& _wParam);

		friend void WindMoveUpdate(const HWND _hWnd, LPARAM _lParam);

		friend void WindSizeUpdate(const HWND _hWnd, LPARAM _lParam);

	protected:

		static std::string ClassName;

		HWND HIns = nullptr;

		DWORD MyID = 0;

		HWND HOwn = nullptr;

		ChStd::Bool NotCSizeFlg = false;
		ChStd::Bool NotCMoveFlg = false;


		ChStd::Bool StartMoveFlg = false;

		void RegisterObj();
		
		long x{ 0 };
		long y{ 0 };
		long w{ 0 };
		long h{ 0 };

	private:

		static std::map<unsigned long, WindObject*>ObjList;

	}WindObj;
}

#endif

#endif