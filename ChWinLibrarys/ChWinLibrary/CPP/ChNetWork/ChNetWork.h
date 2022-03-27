
#ifndef Ch_CPP_NWork_h
#define Ch_CPP_NWork_h

#ifdef _WIN32

#include<Windows.h>
#include<winsock.h>
#pragma comment(lib,"wsock32.lib")

using socklen_t = int;

#elif _WIN64


#include<Windows.h>
#include<winsock.h>
#pragma comment(lib,"wsock32.lib")

using socklen_t = int;

#else

#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet>

#define closesocket(sock) close(sock)
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
using SOCKET = int;

#endif

namespace ChCpp
{
	class NetWork;
	class Server;
	class Client;

	class IP_TCP;
	class IP_UDP;

	class NetWorkBase
	{
	public:

		friend NetWork;

		friend Server;
		friend Client;

		friend IP_TCP;
		friend IP_UDP;

	private:
		
		class InternetProtocol;

		class SockBase :public ChCp::Initializer,public ChCp::Releaser
		{
		public:

			friend InternetProtocol;


			///////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			virtual void Init(const unsigned short _Port_No = 49152) = 0;

			virtual void Release()override
			{
				if (!(*this))return;
				closesocket(BaseSock);
				SetInitFlg(false);
			}

			virtual ChStd::Bool InitPropaty(const int _MaxLinkCount) = 0;

			///////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			///////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			const SOCKET GetBaseSocket() const { return BaseSock; }

			const sockaddr* GetAddr() { return reinterpret_cast<sockaddr*>(&Addr); }

			///////////////////////////////////////////////////////////////////////////////
			//UpdateFunction//

			virtual void Update() {};

			///////////////////////////////////////////////////////////////////////////////

			virtual void Link() = 0;

		protected:

			SOCKET BaseSock{ 0 };

			sockaddr_in Addr{ 0 };

		};

		class InternetProtocol :public ChCpp::ChCp::Initializer
		{
		public:

			///////////////////////////////////////////////////////////////////////////////
			//ConstructerDestructer//

			virtual ~InternetProtocol() {}

			///////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			inline virtual ChStd::Bool Init(SockBase* _Base)
			{
				if (ChPtr::NullCheck(_Base))return false;
				TargetSocket = _Base;
				return true;
			}

			///////////////////////////////////////////////////////////////////////////////
			//CommunityFunction//

			virtual ChStd::Bool Send(
				const std::string& _Str) = 0;

			virtual ChStd::Bool Receve() = 0;

			inline virtual void Release()
			{
				if (!(*this))return;
				SetInitFlg(false);
			}

		protected:

			//SocketBaseからベースとなるソケットを取得//
			SOCKET& InsSocketFromSockBase(SockBase& _Sock)
			{
				return _Sock.BaseSock;
			}

			//InsSocketFromSockBaseの省略版//
			SOCKET& InsSocket(SockBase& _Sock)
			{
				return _Sock.BaseSock;
			}

			//SocketBaseからSockAddrを取得//
			sockaddr_in& InsSockAddrFromSockBase_In(SockBase& _Sock)
			{
				return _Sock.Addr;
			}

			//InsSockAddrFromSockBaseの省略版//
			sockaddr_in& InsSockAddr_In(SockBase& _Sock)
			{
				return _Sock.Addr;
			}

			//SocketBaseからSockAddrを取得//
			sockaddr* InsSockAddrFromSockBase(SockBase& _Sock)
			{
				return reinterpret_cast<sockaddr*>(&_Sock.Addr);
			}

			//InsSockAddrFromSockBaseの省略版//
			sockaddr* InsSockAddr(SockBase& _Sock)
			{
				return reinterpret_cast<sockaddr*>(&_Sock.Addr);
			}

			std::vector<std::string>ReceveStrs;

		private:

			SockBase* TargetSocket = nullptr;

		};

	};

	class NetWork
	{
	public:

		///////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//
		template<class ip, class sock>
		auto Init(const int _MaxLinkCount = 1)->typename std::enable_if
			<
			std::is_base_of<NetWorkBase::InternetProtocol, ip>::value &&
			(std::is_base_of<Server, sock>::value
				|| std::is_same<Server, sock>::value)
			, void
			>::type
		{
			if (_MaxLinkCount <= 0)return;

			WinInit();

			Sock = new sock();

			Sock->Init();

			IP = new ip();

			if (!IP->Init(Sock))
			{
				return;
			}




		}

		template<class ip, class sock>
		auto Init()->typename std::enable_if
			<
			std::is_base_of<NetWorkBase::InternetProtocol, ip>::value &&
			(std::is_base_of<Client, sock>::value
				|| std::is_same<Client, sock>::value)
			, void
			>::type
		{

			WinInit();

			Sock = new sock();

			Sock->Init();

			IP = new ip();

			if (!IP->Init(Sock))
			{
				return;
			}



		}

		void Release();

		///////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		///////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		template<class sock>
		auto GetSock()->typename std::enable_if
			<std::is_base_of<NetWorkBase::SockBase, sock>::value, sock*>
			::type
		{ return dynamic_cast<sock*>(Sock); }

		template<class ip>
		auto GetIP()->typename std::enable_if
			<std::is_base_of<NetWorkBase::InternetProtocol, ip>::value, ip*>
			::type 
		{ return dynamic_cast<ip*>(IP); }

		///////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

	protected:

		inline ChStd::Bool WinInit()
		{

#ifdef _WIN32
			//WisSockVer//
			WORD wVerReq = MAKEWORD(1, 1);
			//ライブラリの詳細情報を受け取る//
			WSADATA wsadata{ 0 };
			{
				if (WSAStartup(wVerReq, &wsadata) != 0)
				{
					//生成されないためエラーが起きる//
					//throw "WSAStartup()";
					return false;
				}
			}
#endif

			return true;
		}

		inline void WinRelease()
		{

#ifdef _WIN32
			WSACleanup();
#endif

		}

	private:

		NetWorkBase::InternetProtocol* IP;
		NetWorkBase::SockBase* Sock;

	};

}


#endif