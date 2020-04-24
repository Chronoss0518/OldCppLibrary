#ifndef Ch_CPP_Cmp_Base_h
#define Ch_CPP_Cmp_Base_h

namespace ChCpp
{
	namespace Cmp
	{
		 typedef class BaseCompressor
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			
			//���k�֐�//
			virtual std::string Press(const std::string& _PressBase) = 0;

			///////////////////////////////////////////////////////////////////////////////////

			//�𓀊֐�//
			virtual std::string Thaw(const std::string& _ThawBase) = 0;

			///////////////////////////////////////////////////////////////////////////////////

		}BaseComp;

		 class Compressor :public ChCpp::ChCp::InitPack
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			template<class T>
			inline auto Init()
				->typename std::enable_if<std::is_base_of<BaseCompressor, T>::value, void>::type
			{
				if (*this)return;

				compressor.Makes<T>();

				SetInitFlg(true);
			}

			template<class T>
			inline auto Init()
				->typename std::enable_if<!std::is_base_of<BaseCompressor, T>::value, void>::type
			{
				return;
			}

			inline void Release()
			{

				compressor = nullptr;

				SetInitFlg(false);
			}

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			template<class T>
			inline auto SetCompressor()
				->typename std::enable_if<std::is_base_of<BaseCompressor,T>::value,void>::type
			{
				if (!*this)return;
				Release();

				compressor.Makes<T>();

				SetInitFlg(true);
			}

			template<class T>
			inline auto SetCompressor()
				->typename std::enable_if<!std::is_base_of<BaseCompressor, T>::value, void>::type
			{
				return;
			}

			///////////////////////////////////////////////////////////////////////////////////

			//���k�֐�//
			inline std::string Press(const std::string& _PressBase)
			{
				if (!*this)return "";
				if (!compressor)return "";
				if (_PressBase.size() <= 0)return "";

				return compressor->Press(_PressBase);

			}

			///////////////////////////////////////////////////////////////////////////////////

			//�𓀊֐�//
			inline std::string Thaw(const std::string& _ThawBase)
			{
				if (!*this)return "";
				if (!compressor)return "";
				if (_ThawBase.size() <= 0)return "";

				return compressor->Press(_ThawBase);

			}

		private:

			ChPtr::CPtr<BaseComp>compressor = nullptr;
		};

	}
}

#endif
