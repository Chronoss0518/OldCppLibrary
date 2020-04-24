#ifndef Ch_CPP_Float_h
#define Ch_CPP_Float_h

namespace ChStd
{

	class Float
	{
	public:

		Float& operator =(const float _cm)
		{
			Float Tmp;

			Tmp.Base = _cm;

			if (_cm > Max)
			{
				Tmp.Base = Max;
			}

			if (_cm < Min)
			{
				Tmp.Base = Min;
			}

			return Tmp;
		}

		Float& operator =(const Float _cm)
		{
			Float Tmp;

			Tmp.Base = _cm.Base;

			return Tmp;
		}

	protected:

		float Base = 0.0f;

		float Max = FLT_MAX;
		float Min = FLT_MIN;

	};
}

#endif