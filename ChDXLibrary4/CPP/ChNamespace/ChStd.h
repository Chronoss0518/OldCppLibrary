#ifndef Ch_CPP_Std_h
#define Ch_CPP_Std_h



namespace ChSystem
{
	//���ݎ����擾�̂��߂Ɏg�p//
	unsigned long GetTime();
}

//ChLibrary�̃x�[�X�ƂȂ�֐��A�ϐ��Q�̂܂Ƃ܂�//
namespace ChStd
{

	//X�t�@�C���ȂǑ����̃I�u�W�F�N�g�𗘗p����ۂɎ��ʎq�Ƃ��ė��p����B//
	typedef unsigned short DataNo;

	using Bool = unsigned char;

	static const Bool True = true;
	static const Bool False = false;


	//Windows�Ŏg�p����鑊�΃p�X�E��΃p�X�̍ő啶����//
	static const unsigned short W_MaxPathLen = 258;

	struct COLOR255;
	struct COLOR1f;

	///////////////////////////////////////////////////////////////////////////////////////
	//MyAddStruct
	///////////////////////////////////////////////////////////////////////////////////////

	//Windows���Œ�`����Ă���POINT��float��//
	struct FPOINT
	{

		inline FPOINT& operator =(const FPOINT _Pos)
		{
			x = _Pos.x;
			y = _Pos.y;
			return *this;
		}

		inline FPOINT& operator +=(const FPOINT _Pos)
		{
			x += _Pos.x;
			y += _Pos.y;
			return *this;
		}

		inline FPOINT& operator -=(const FPOINT _Pos)
		{
			x -= _Pos.x;
			y -= _Pos.y;
			return *this;
		}

		inline FPOINT& operator *=(const FPOINT _Pos)
		{
			x *= _Pos.x;
			y *= _Pos.y;
			return *this;
		}

		inline FPOINT& operator /=(const FPOINT _Pos)
		{
			if (_Pos.x != 0.0f)x /= _Pos.x;
			if (_Pos.y != 0.0f)y /= _Pos.y;
			return *this;
		}

		inline FPOINT operator +(const FPOINT _Pos)const
		{
			FPOINT Tmp = *this;
			Tmp += _Pos;
			return Tmp;
		}

		inline FPOINT operator -(const FPOINT _Pos)const
		{
			FPOINT Tmp = *this;

			Tmp -= _Pos;
			return Tmp;
		}

		inline FPOINT operator *(const FPOINT _Pos)const
		{
			FPOINT Tmp = *this;

			Tmp *= _Pos;
			return Tmp;
		}

		inline FPOINT operator /(const FPOINT _Pos)const
		{
			FPOINT Tmp = *this;

			Tmp /= _Pos;
			return Tmp;
		}

		inline FPOINT operator =(const float _Num)const
		{
			FPOINT Tmp = *this;

			Tmp.x = _Num;
			Tmp.y = _Num;
			return Tmp;
		}

		inline FPOINT operator + (const float _Num)const
		{
			FPOINT Tmp = *this;

			Tmp.x += _Num;
			Tmp.y += _Num;
			return Tmp;
		}

		inline FPOINT operator - (const float _Num)const
		{
			FPOINT Tmp = *this;

			Tmp.x -= _Num;
			Tmp.y -= _Num;
			return Tmp;
		}

		inline FPOINT operator * (const float _Num)const
		{
			FPOINT Tmp = *this;

			Tmp.x *= _Num;
			Tmp.y *= _Num;
			return Tmp;
		}

		inline FPOINT operator /=(const float _Num)const
		{
			FPOINT Tmp = *this;

			if (_Num == 0.0f)return Tmp;
			Tmp.x /= _Num;
			Tmp.y /= _Num;
			return Tmp;
		}

		inline FPOINT() { x = y = 0.0f; };

		inline FPOINT(const float _x, const float _y)
		{
			x = _x;
			y = _y;
		};

		union
		{
			struct { float x, y; };
			struct { float w, h; };
		};


	};

	///////////////////////////////////////////////////////////////////////////////////

	//Windows���Œ�`����Ă���RECT��float��//
	struct FRECT
	{
		inline FRECT() { x = y = w = h = 0.0f; }

		inline FRECT(
			const float _x
			, const float _y
			, const float _w
			, const float _h)
		{
			x = _x;
			y = _y;
			w = _w;
			h = _h;
		}

		float x;
		float y;
		float w;
		float h;
	};

	///////////////////////////////////////////////////////////////////////////////////

	struct COLOR1f;
	struct COLOR255;

	//�F���`����ۂɎg�p�����ϐ��B��{�I�ɍő吔�l��1.0f//
	//�Œᐔ�l�͌Œ��0.0f//
	struct COLOR1f
	{
		inline COLOR1f& operator= (const float _Num)
		{
			a = r = g = b = _Num;
			return *this;
		}

		inline COLOR1f& operator=(const COLOR255&);

		inline COLOR1f& operator= (const COLOR1f& _Col)
		{
			a = _Col.a;
			r = _Col.r;
			g = _Col.g;
			b = _Col.b;
			return *this;
		}

		inline COLOR1f() { a = r = g = b = 0.0f; };

		inline COLOR1f(
			const float _a
			, const float _r
			, const float _g
			, const float _b)
		{
			a = _a;
			r = _r;
			g = _g;
			b = _b;
		}

		inline COLOR1f(
			const float _Num)
		{
			a = r = g = b = _Num;
		}

		float r;
		float g;
		float b;
		float a;
	};

	///////////////////////////////////////////////////////////////////////////////////

	//�F���`����ۂɎg�p�����ϐ��B��{�I�ɍő吔�l��255//
	//�Œᐔ�l�͌Œ��0//
	struct COLOR255
	{
		inline COLOR255& operator= (const unsigned char _Num)
		{
			a = r = g = b = _Num;
			return *this;
		}

		inline COLOR255& operator=(const COLOR1f&);

		inline COLOR255& operator= (const COLOR255& _Col)
		{
			a = _Col.a;
			r = _Col.r;
			g = _Col.g;
			b = _Col.b;
			return *this;
		}

		inline COLOR255() { a = r = g = b = 0; };

		inline COLOR255(
			const unsigned char _a
			, const unsigned char _r
			, const unsigned char _g
			, const unsigned char _b)
		{
			a = _a;
			r = _r;
			g = _g;
			b = _b;
		}

		inline COLOR255(
			const unsigned char _Num)
		{
			a = r = g = b = _Num;
		}

		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

	};



	inline COLOR1f& COLOR1f::operator=(const COLOR255& _Col)
	{

		a = static_cast<unsigned char>(_Col.a / 255.0f);
		r = static_cast<unsigned char>(_Col.r / 255.0f);
		g = static_cast<unsigned char>(_Col.g / 255.0f);
		b = static_cast<unsigned char>(_Col.b / 255.0f);

		return *this;

	}

	inline COLOR255& COLOR255::operator=(const COLOR1f& _Col)
	{

		a = static_cast<unsigned char>(_Col.a * 255.0f);
		r = static_cast<unsigned char>(_Col.r * 255.0f);
		g = static_cast<unsigned char>(_Col.g * 255.0f);
		b = static_cast<unsigned char>(_Col.b * 255.0f);

		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//AllFunction
	///////////////////////////////////////////////////////////////////////////////////////

	//Windows���2�i���ő包���̈ʒu//
	const static unsigned char W_MaxCharBit = 0x80;
	const static unsigned short W_MaxShortBit = 0x8000;
	const static unsigned int W_MaxIntBit = 0x80000000;
	const static unsigned long W_MaxLongBit = 0x80000000;
	const static unsigned long long W_MaxLLongBit = 0x8000000000000000;

	//���Ԏ擾��Z�k�����֐�//
	static inline unsigned long GetTime()
	{
#ifdef _WINDOWS_
		return timeGetTime();
#endif
		return 0;
	}

	//�v���Z�X�̎��s����//
	static inline unsigned long GetClock()
	{
		return static_cast<unsigned long>(std::clock());
	}

	//�J�n���Ɏg�p���A�����_���Ȓl���Z�b�g����//
	static inline void SetRand(const unsigned long _UseNo) { srand(_UseNo); }

	//SetRand�g�p��rand�֐�����l�����o��//
	static inline unsigned short GetRand(const unsigned short _Max)
	{
		return(rand() + (GetTime() % 2)) % _Max;
	}

	//��������o�C�i���f�[�^�ɂ���//
	//�����^�ɕϊ�����//
	template<typename T>
	static inline void StrBinaryToNum(
		T &_SetData
		, const std::string& _Str
		, const size_t& _SPos = 0)
	{
		_SetData = 0;
		for (unsigned char i = 0; i < sizeof(T); i++)
		{
			unsigned char Test = _Str[_SPos + i];
			if (Test <= 0)continue;
			_SetData += (T)(Test << 8 * ((sizeof(T) - 1) - i));
		}

	}

	//�p�x��0����360�ȓ��Ɏ��܂��Ă��邩//
	//��)-5�������ꍇ��355�ւƒu�������//
	static inline void CheckOverDegree(float& _Degree)
	{
		if (_Degree > 360.0f)_Degree -= 360.0f;
		if (_Degree < 0.0f)_Degree += 360.0f;
	}

	//FPS�����p�֐��B//
	//�w�肵��1�t���[���̃^�C���𒴂���Ɩ߂�l��True���A��//
	static inline Bool FPSProcess(const unsigned long _FPS)
	{
		static unsigned long FPSTime;
		unsigned long TmpTime = GetTime();
		if (TmpTime - FPSTime < 1000 / _FPS)return False;
		FPSTime = TmpTime;
		return True;
	}

	//�N���X�����擾����֐�//
	template<class T = int>
	static inline std::string GetTypeName()
	{
		std::string TmpStr = typeid(T).name();


		size_t Tmp = TmpStr.find(" ");
		if (Tmp == std::string::npos)Tmp = 0;
		else Tmp += 1;

		return &TmpStr[Tmp];
	}

	//EnumClass�����^�փL���X�g���邽�߂̃N���X//
	template<typename Enum>
	static inline auto EnumCast(Enum _Enum)->typename std::enable_if
		<std::is_enum<Enum>::value, typename std::underlying_type< Enum >::type>::type
	{
		return static_cast<typename std::underlying_type<Enum>::type>(_Enum);
	}

	template<typename Enum>
	static inline auto EnumCast(Enum _Enum)->typename std::enable_if
		<!std::is_enum<Enum>::value, int>::type
	{
		return 0;
	}

	template<class T>
	static inline void All0Memory(T* _Val)
	{
		void *Tmp = _Val;

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			* (static_cast<char*>(Tmp) + i) = 0;
		}
	}

	static inline void RemoveToESChar(std::string& _Str)
	{
		size_t TmpPos = 0;
		while ((TmpPos = _Str.find("\t")) != _Str.npos)
		{
			_Str.replace(TmpPos, TmpPos + 1, "");
		}
		while ((TmpPos = _Str.find(" ")) != _Str.npos)
		{
			_Str.replace(TmpPos, TmpPos + 1, "");
		}
		while ((TmpPos = _Str.find("\n")) != _Str.npos)
		{
			_Str.replace(TmpPos, TmpPos + 1, "");
		}
	}
	
	
}

#endif