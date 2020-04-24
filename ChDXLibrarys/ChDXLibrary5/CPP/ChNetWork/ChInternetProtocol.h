
#ifndef Ch_CPP_IP_h
#define Ch_CPP_IP_h

#ifdef _WIN32

#include<Windows.h>
#include<winsock.h>

using socklen_t = int;

#elif __linux__

#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet>

#define closesocket(sock) close(sock)
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
using SOCKET = int;

#endif


#include"ChNetWork.h"
#include"ChSockBase.h"

namespace ChCpp
{

	class NetWork;

	class IP_TCP :public NetWorkBase::InternetProtocol
	{
	public:

		///////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual ChStd::Bool Init(NetWorkBase::SockBase* _Base)override;

		///////////////////////////////////////////////////////////////////////////////
		//CommunityFunction//

		 ChStd::Bool Send(
			const std::string& _Str)override;

		 ChStd::Bool Receve()override;

		 std::string TargetSend(
			const SOCKET& _TargetSocket
			, const std::string& _Str);

		 std::string TargetReceve(
			const SOCKET& _TargetSocket);
	};

	class IP_UDP :public NetWorkBase::InternetProtocol
	{
	public:

		///////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual ChStd::Bool Init(NetWorkBase::SockBase* _Base)override;

		///////////////////////////////////////////////////////////////////////////////
		//CommunityFunction//

		ChStd::Bool Send(
			const std::string& _Str)override;

		ChStd::Bool Receve()override;

		virtual ChStd::Bool CustomSend();

	};

}

#endif