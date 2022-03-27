
#ifndef Ch_CPP_MuTh_h
#define Ch_CPP_MuTh_h

namespace std
{
	class thread;
}

namespace ChCpp
{
	//void(void)�̊֐��p�}���`�X���b�h�����s����N���X//
	class ChMultiThread
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		ChMultiThread() {}

		ChMultiThread(const std::function<void(void)> _Func);

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//�}���`�X���b�h�œ����������֐����Z�b�g����//
		void Init(const std::function<void(void)> _Func);

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�}���`�X���b�h�œ����Ă���֐����I��������̔���//
		ChStd::Bool IsEndFunc() { return EndFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�}���`�X���b�h�œ����Ă���֐����I���܂ő҂�//
		void Join();

	protected:

		void Function();

		std::thread Thread;

		std::function<void(void)> Func = nullptr;

		ChStd::Bool EndFlg = false;

	};


}

#endif