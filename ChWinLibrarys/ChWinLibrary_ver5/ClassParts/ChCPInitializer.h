
#ifndef Ch_CPP_CP_Init_h
#define Ch_CPP_CP_Init_h

namespace ChCp
{
	//�p�����ė��p����//
	//���������������Ă��邩�m�F�ł���悤�ɂȂ�//
	//������������Ƃ���SetInitFlg(true);��//
	//�������Ƃ��ɂ�SetInitFlg(false);���ĂԎ�//
	class Initializer
	{
	protected:

		///////////////////////////////////////////////////////////////////////////////////

		//������(Initialize)����ۂɌĂԂ��Ƃ�K�{�Ƃ���֐�//
		//Initialize�����Ƃ������������ɍs�����Ƃ��Ȃ����ߕK�v�Ƃ��Ă���//
		inline void SetInitFlg(const ChStd::Bool _flg) { initFlg = _flg; }

		///////////////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////////////////

		inline explicit operator bool()const { return initFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		inline ChStd::Bool IsInit() { return initFlg; }

		///////////////////////////////////////////////////////////////////////////////////

	protected:


		///////////////////////////////////////////////////////////////////////////////////
		//ConstructorDestructor//
		Initializer() {}


	private:

		ChStd::Bool initFlg = false;

	};



}
#endif