#ifndef NET_WORK_H_
#define NET_WORK_H_


#if CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM
#include <WinSock2.h>
#else
#endif
#include <stdio.h>
#include <iostream>
#include <string>

#define MAX_RECV_BUF_COUNT	1024*1024

class NetWork
{
public:
	NetWork();
	virtual ~NetWork(void);
	static NetWork *getInstance();

	// ��ʼ������
	void connection(const char *Ip,const int port);

	bool sendData(const char *sendData);

	void recvData();

	// �����ر�����
	void close();
private:
	// ��ʼ����������
	bool initSocket();

	bool connectSocket();

	void destory();
private:
#if CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM
	SOCKET	_socket; 
#else
#endif

	// ͨ�õ�������������
	std::string m_ip;
	int			m_port;

	static NetWork *m_instance;
};


#define gNetWork NetWork::getInstance()


#endif //NET_WORK_H_