#ifndef NET_IOSOCKETDATA_H_
#define NET_IOSOCKETDATA_H_
#include <vector>

class IOSocketData
{
public:
	IOSocketData();
	virtual ~IOSocketData(void);
public:
	void pushMessage(const char *data);

	// �Ƿ��Ѿ������������
	bool IsRecvEnd()const;

	// ������յ�����
	void onData(const char *data, size_t count);

	// ���õ�ǰ�İ������ݳ���
	void setCurPackageLenght(const size_t lenght){m_curPacketageLenght += lenght;}

private:
	void clear();
protected:
	std::vector<std::string> m_data;

	// ��Э�鳤��
	size_t m_lenght;

	// ����Э���
	int m_protoCol;

	// �Ƿ�����������
	bool m_IsRecvEnd;

	// ��ǰ���յ��İ����ݳ���
	size_t m_curPacketageLenght;

	// �ְ�������
	size_t m_count;
};


#endif //NET_WORK_H_