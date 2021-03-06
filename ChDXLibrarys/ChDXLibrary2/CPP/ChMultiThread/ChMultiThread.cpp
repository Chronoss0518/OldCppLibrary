
#include"../../ChGameIncludeFile.h"
#include<thread>
#include"ChMultiThread.h"

using namespace ChCpp;

ChMultiThread::ChMultiThread(const std::function<void(void)> _Func)
{
	Init(_Func);
}

void ChMultiThread::Init(const std::function<void(void)> _Func)
{
	if (Thread.joinable())
	{
		Thread.detach();
	}
	Func = _Func;

	EndFlg = false;

	std::thread Tmp([this] {Function(); });

	Thread.swap(Tmp);

}

void ChMultiThread::Join()
{
	if (EndFlg)return;
	Thread.join();
}

void ChMultiThread::Function()
{
	Func();

	EndFlg = true;
}
