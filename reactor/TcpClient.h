#ifndef _TCP_CLIENT_H_ 
#define _TCP_CLIENT_H_

#include "TcpConnection.h"
#include "../thread/Mutex.h"

#include <boost/noncopyable.hpp>

class Connector;

typedef boost::shared_ptr<Connector> ConnectorPtr;

class TcpClient
	: private boost::noncopyable
{
public:
	TcpClient(EventLoop* pEvtLoop, const InetAddress& rServerAddr);
	~TcpClient();

	void				Connect();
	void				DisConnect();
	void				Stop();

	TcpConnectionPtr	GetTcpConnection() const {
		MutexLockGuard lock(m_Mutex);
		return m_pTcpConnection;
	}

	void				EnableRetry() {
		m_bRetry = true;
	}

	// ���̰߳�ȫ
	void				SetConnectionCallBack(const ConnectionCallBack& rCallBack) {
		m_ConnectionCallBack = rCallBack;
	}
	// ���̰߳�ȫ
	void				SetMessageCallBack(const MessageCallBack& rCallBack) {
		m_MessageCallBack = rCallBack;
	}
	// ���̰߳�ȫ
	void				SetWriteCompleteCallBack(const WriteCompleteCallBack& rCallBack) {
		m_WriteCompleteCallBack = m_WriteCompleteCallBack;
	}

private:
	// ���̰߳�ȫ
	void				newConnection(int nSockFd);
	// ���̰߳�ȫ
	void				removeConnection(const TcpConnectionPtr& pTcpConn);

private:
	EventLoop*			m_pEventLoop;
	ConnectorPtr		m_pConnector;
	ConnectionCallBack	m_ConnectionCallBack;
	MessageCallBack		m_MessageCallBack;
	WriteCompleteCallBack m_WriteCompleteCallBack;

	bool				m_bRetry;
	bool				m_bConnect;
	int					m_nNextConnId;
	
	mutable	MutexLock	m_Mutex;
	TcpConnectionPtr	m_pTcpConnection;

};

#endif // _TCP_CLIENT_H_
