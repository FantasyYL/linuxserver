#ifndef _TCP_SERVER_H_ 
#define _TCP_SERVER_H_

#include "CallBacks.h"
#include "TcpConnection.h"

#include <map>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

class Acceptor;
class EventLoop;
class EventLoopThreadPool;

class TcpServer
	: private boost::noncopyable
{
	typedef std::map<std::string, TcpConnectionPtr> ConnectionMap;

public:
	TcpServer(EventLoop* pEventLoop, const InetAddress& rListenAddr);
	~TcpServer();

	void				SetThreadNum(int nNumThread);;

	void				Start();

	void				SetConnectionCallBack(const ConnectionCallBack& rConnCallBack) {
		m_ConnCallBack = rConnCallBack;
	}
	void				SetMessageCallBack(const MessageCallBack& rMsgCallBack) {
		m_MsgCallBack = rMsgCallBack;
	}
	void				SetWriteCompleteCallBack(const WriteCompleteCallBack& rWriteCompleteCallBack) {
		m_WriteCompleteCallBack = rWriteCompleteCallBack;
	}

private:
	// �����̰߳�ȫ
	void				newConnection(int nSockFd, const InetAddress& rPeerAddr);
	// �̰߳�ȫ
	void				removeConnection(const TcpConnectionPtr& pTcpConn);
	// �����̰߳�ȫ
	void				removeConnectionInLoop(const TcpConnectionPtr& pTcpConn);

private:
	EventLoop*			m_pEventLoop;
	const std::string	m_strName;
	boost::scoped_ptr<Acceptor> m_pAcceptor;
	boost::scoped_ptr<EventLoopThreadPool> m_pThreadPool;

	ConnectionCallBack	m_ConnCallBack;
	MessageCallBack		m_MsgCallBack;
	WriteCompleteCallBack m_WriteCompleteCallBack;
	bool				m_bStared;

	// ������loop�߳�
	int					m_nNextConnId;
	ConnectionMap		m_mpConnection;

};

#endif // _TCP_SERVER_H_
