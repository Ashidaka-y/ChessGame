#ifndef DISPATCH_HANDLER_H__
#define DISPATCH_HANDLER_H__
#include <iostream>
#include <map>
#include <vector>
#include "cocos2d.h"

typedef std::function<void(int cmd, void *data, size_t lenght)> ccDispatchCallBack;
typedef std::function<void(void)> ccDispatchEndCallBack;

typedef void (*SEL_DispatchEvent)();

struct DispatchData
{
	int m_cmd;
	int m_order;
	ccDispatchCallBack m_func;
};

struct Dispatch
{
	int m_cmd;
	void *m_data;
	size_t m_lenght;
	ccDispatchEndCallBack m_endCallBack;
};

#define DISPATCHHANDLER_LUA_FILE_NAME	"DispatchConfig"
class DispatchHandler
{
public:
public:
	DispatchHandler();
	virtual ~DispatchHandler();

	static DispatchHandler *getInstance();

	// �����Ϣ����
	int addDispatchHandler(const int cmd,const ccDispatchCallBack &dispatch);

	// �����Ϣ����
	int addDispatchHandlerByData(int cmd,const DispatchData *dispatch);

	// ��Ӵ�����Ϣ
	void postDispatchHandler(int cmd, void *data,size_t lenght,const ccDispatchEndCallBack &endCallBack = nullptr);

	// ɾ��cmd������Ϣ����
	void removeDispatchHandler(int cmd);

	// ɾ��cmd�еı��Ϊorder����Ϣ����
	void removeDispatchHandler(int cmd,int order);

public:
	// ÿ֡�������Ϣ
	void update(float dt);
protected:
	// ��⵱ǰ�Ƿ��ж�Ӧ������Ĳ���
	bool checkHandler(int cmd);

	// ��ȡ��Ϣ����
	std::vector<DispatchData> &getHandler(int cmd);



	std::vector<Dispatch> getDispatchs(int cmd);
private:
	// ��Ϣ����
	std::map<int , std::vector<DispatchData>> m_dispatchMaps;

	// �ȴ�����������б�
	std::vector<Dispatch> m_dispatchs;

	static DispatchHandler *m_instances;
};

#define gDispatchhandler DispatchHandler::getInstance()

#endif // DISPATCH_HANDLER_H__