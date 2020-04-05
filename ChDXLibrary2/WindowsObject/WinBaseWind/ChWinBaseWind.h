#ifdef _WINDOWS_

#ifndef Ch_Win_BObj_h
#define Ch_Win_BObj_h

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{
	void ObjUpdate(const WPARAM _wParam);

	typedef class WindObject :public ChCpp::ChCp::InitPack
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		WindObject() {};

		virtual ~WindObject() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const HWND& _ParentHndl);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		const HWND GethWnd()const { return HIns; }

		///////////////////////////////////////////////////////////////////////////////////////

		void Move(const int _x
			, const int _y
			, const int _w
			, const int _h);

		void Move(const int _x
			, const int _y);

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void Update() {};

		///////////////////////////////////////////////////////////////////////////////////////

		void ReSize(
			const int _w
			, const int _h);

		///////////////////////////////////////////////////////////////////////////////////////

		friend void ObjUpdate(const WPARAM _wParam);

	protected:

		static std::string ClassName;

		HWND HIns = nullptr;

		DWORD MyID = 0;

		HWND HOwn = nullptr;

		void RegisterObj();
		
		int x;
		int y;
		int w;
		int h;

	private:

		static std::vector<WindObject*>ObjList;

	}WindObj;
}

#endif

#endif