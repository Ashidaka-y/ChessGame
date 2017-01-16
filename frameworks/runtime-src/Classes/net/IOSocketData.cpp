#include "IOSocketData.h"

#if CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM
#include <WinSock2.h>
#else
#endif

IOSocketData::IOSocketData()
{
	clear();
}
IOSocketData::~IOSocketData(void)
{

}




void IOSocketData::pushMessage(const char *data)
{
	m_data.push_back(data);

	if (m_IsRecvEnd)
	{
		onData(data,0);
	}
	else
	{
		++m_count;
		onData(NULL,m_count);
	}
}

// �Ƿ��Ѿ������������
bool IOSocketData::IsRecvEnd()const
{
	return m_IsRecvEnd;
}

// ������յ�����
void IOSocketData::onData(const char *data, size_t count)
{
	if (count == 0)
	{
		// ��Ϣ����
		memcpy(&m_lenght, data, 4);
		// ��С���ֽ���ת��
		m_lenght = htonl(m_lenght);
		// Э���
		memcpy(&m_protoCol, data + 4, 4);
		// ��С���ֽ���ת��
		m_protoCol = htonl(m_protoCol);
	}


	// ������յ���ֻ�Ƿְ������
	if (m_curPacketageLenght < m_lenght)
	{
		m_IsRecvEnd = false;
		return ;
	}

	// ������������İ������
	std::string actionData(*m_data.begin());
	// ȡ��ʵ������
	actionData.substr(8);
	for (int i = 1; i <= count; ++i)
	{
		// �ӵ�һ�����е��������ȡ������
		actionData.append(m_data[i]);
	}

	// �ַ��������ݵ����߳̽��д���

	// ����������
	clear();
}

void IOSocketData::clear()
{
	m_lenght = 0;
	m_curPacketageLenght = 0;
	m_IsRecvEnd = true;
	m_count = 0;
	m_protoCol = 0;
}