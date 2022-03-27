#include"../../BaseIncluder/ChBase.h"
#include"ChNetWork.h"
#include"ChSockBase.h"
#include"ChInternetProtocol.h"

namespace ChCpp
{
	///////////////////////////////////////////////////////////////////////////////
	//Server���\�b�h//
	///////////////////////////////////////////////////////////////////////////////

	void Server::Init(const unsigned short _Port_No)
	{

		//�A�h���X�t�@�~���̎w��
		Addr.sin_family = AF_INET;

		//�T�[�o��IP�A�h���X
		//htonl:�l�b�g���[�N�o�C�g�I�[�_�[����z�X�g�o�C�g�I�[�_�[�֕ϊ�����//
		Addr.sin_addr.s_addr = htonl(INADDR_ANY);

		//�T�[�o�̃|�[�g�ԍ�//
		//htons:�z�X�g�o�C�g�I�[�_�[����l�b�g���[�N�o�C�g�I�[�_�[�֕ϊ�����//
		Addr.sin_port = htons(_Port_No);
	}

	void Server::Release()
	{

	}

	///////////////////////////////////////////////////////////////////////////////

	void Server::SetLinkSocket(const std::vector<SOCKET>& _LinksSock)
	{
		if (_LinksSock.empty())return;

		if (!LinkSock.empty())
		{
			LinkSock.clear();
		}

		LinkSock = _LinksSock;

	}

	///////////////////////////////////////////////////////////////////////////////

	void Server::Update()
	{

	}

	///////////////////////////////////////////////////////////////////////////////

	void Server::Link()
	{

	}


	///////////////////////////////////////////////////////////////////////////////
	//Client���\�b�h//
	///////////////////////////////////////////////////////////////////////////////

	void Client::Release()
	{

	}

	///////////////////////////////////////////////////////////////////////////////

	void Client::Link()
	{

	}

	///////////////////////////////////////////////////////////////////////////////
	//IP_TCP���\�b�h//
	///////////////////////////////////////////////////////////////////////////////

	ChStd::Bool IP_TCP::Init(NetWorkBase::SockBase* _Base)
	{

		InternetProtocol::Init(_Base);

		SOCKET Test;

		Test = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (Test == SOCKET_ERROR)
		{
			ChFIO::OutToErrorText(
				"NetWorkProgrammError"
				, "�\�P�b�g�̐���(socket())�Ɏ��s���܂����B"
				, ChFIO::OTEAddType::AfterFirst);

			return false;
		}

		InsSocket(*_Base);


		Test = bind(InsSocket(
			*_Base)
			, InsSockAddr(*_Base)
			, sizeof(InsSockAddr_In(*_Base)));


		if (Test == SOCKET_ERROR)
		{
			ChFIO::OutToErrorText(
				"NetWorkProgrammError"
				, "�R�Â�(bind())�Ɏ��s���܂����B"
				, ChFIO::OTEAddType::AfterFirst);

			return false;
		}


		return true;
	}

	///////////////////////////////////////////////////////////////////////////////

	ChStd::Bool IP_TCP::Send(
		const std::string& _Str)
	{
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////

	ChStd::Bool IP_TCP::Receve()
	{

		return true;
	}

	///////////////////////////////////////////////////////////////////////////////

	std::string IP_TCP::TargetSend(
		const SOCKET& _TargetSocket
		, const std::string& _Str)
	{

		return "";
	}

	///////////////////////////////////////////////////////////////////////////////

	std::string IP_TCP::TargetReceve(
		const SOCKET& _TargetSocket)
	{

		return "";
	}

	///////////////////////////////////////////////////////////////////////////////
	//IP_UDP���\�b�h//
	///////////////////////////////////////////////////////////////////////////////


	ChStd::Bool IP_UDP::Init(NetWorkBase::SockBase* _Base)
	{

		InternetProtocol::Init(_Base);



		SetInitFlg(true);
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////

	ChStd::Bool IP_UDP::Send(const std::string& _Str)
	{

		return true;
	}

	///////////////////////////////////////////////////////////////////////////////

	ChStd::Bool IP_UDP::Receve()
	{

		return true;
	}

}