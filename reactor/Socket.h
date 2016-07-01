#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <boost/noncopyable.hpp>

class InetAddress;

class Socket
	//: private boost::noncopyable
{
public:
	explicit Socket(int nSockFd);

	~Socket();

	int				GetFd() const;

	void			Bind(const InetAddress& rAddr);
	void			Listen();
	int				Accpet(InetAddress* pPeerAddr);

	/*
		��bind֮ǰ����
		����˿�æ��TCP״̬λ��TIME_WAIT���������ö˿ڡ�
		����˿�æ����TCP״̬λ������״̬�����ö˿�ʱ���ɵõ�һ��������Ϣ��ָ��"��ַ�Ѿ�ʹ����"��
		�����ķ������ֹͣ�������������������׽�������ʹ��ͬһ�˿ڣ���ʱ SO_REUSEADDR ѡ��ǳ�����
	*/
	void			SetReuseAddr(bool bOn);

	void			ShutDownWrite();

	// Nagle's algorithm
	void			SetTcpNoDelay(bool bOn);

private:
	const int		m_nSockFd;

};

#endif // _SOCKET_H_
