
#ifndef Ch_CPP_MuTh_h
#define Ch_CPP_MuTh_h

namespace std
{
	class thread;
}

namespace ChCpp
{
	//void(void)の関数用マルチスレッドを実行するクラス//
	class ChMultiThread
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		ChMultiThread() {}

		ChMultiThread(const std::function<void(void)> _Func);

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//マルチスレッドで動かしたい関数をセットする//
		void Init(const std::function<void(void)> _Func);

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//マルチスレッドで動いている関数が終わったかの判定//
		ChStd::Bool IsEndFunc() { return EndFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//マルチスレッドで動いている関数が終わるまで待つ//
		void Join();

	protected:

		void Function();

		std::thread Thread;

		std::function<void(void)> Func = nullptr;

		ChStd::Bool EndFlg = false;

	};


}

#endif