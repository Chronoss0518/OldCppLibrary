
#include"../../BaseIncluder/ChBase.h"

#include<thread>
#include"ChMultiThread.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////
//ChMUltThreadÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////

ChMultiThread::ChMultiThread(const std::function<void(void)> _func)
{
	Init(_func);
}

void ChMultiThread::Init(const std::function<void(void)> _func)
{
	if (thread.joinable())
	{
		thread.detach();
	}
	func = _func;

	endFlg = false;

	std::thread Tmp([this] {Function(); });

	thread.swap(Tmp);

}

void ChMultiThread::Join()
{
	if (endFlg)return;
	thread.join();
}

void ChMultiThread::Function()
{
	func();

	endFlg = true;
}
