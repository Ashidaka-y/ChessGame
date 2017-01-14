#include "DispatchHandler.h"

using namespace std;
DispatchHandler *DispatchHandler::m_instances = nullptr;
DispatchHandler::DispatchHandler()
{
	//cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread(std::bind(&DispatchHandler::update));
}

DispatchHandler::~DispatchHandler()
{
	if (m_instances)
	{
		delete m_instances;
		m_instances = nullptr;
	}
}

DispatchHandler *DispatchHandler::getInstance()
{
	if (!m_instances)
	{
		m_instances = new DispatchHandler();
	}

	return m_instances;
}

// ÿ֡�������Ϣ
void DispatchHandler::update()
{
	// û����Ϣ���ݴ���
	if (m_dispatchs.empty())
	{
		return ;
	}

	auto dispatch = m_dispatchMaps;

	// �ȴ��������Ϣ����,ÿ��ֻ�����һ��
	auto dispatchs = m_dispatchs.begin();
	auto data = *dispatchs;
	for (auto it = m_dispatchMaps.begin(); it != m_dispatchMaps.end(); ++it)
	{
		if (it->first != data.m_cmd)
		{
			continue;
		}
		std::vector<DispatchData> &dispatch = it->second;
		for (auto itt = dispatch.begin(); itt != dispatch.end();++itt)
		{
			auto dispatchhandler = *itt;
			if (dispatchhandler.m_func)
			{
				dispatchhandler.m_func(data.m_cmd, data.m_data, data.m_lenght);
			}
		}
		// ���������Ϣ���ݷַ���Ĵ���
		if (data.m_endCallBack)
		{
			data.m_endCallBack();
		}

		// ȥ�����������Ϣ������Ϣ
		m_dispatchs.erase(dispatchs);
		return ;
	}
}

// ��Ӵ�����Ϣ
void DispatchHandler::postDispatchHandler(int cmd, void *data,size_t lenght,const ccDispatchEndCallBack &endCallBack)
{
	Dispatch dispatch;
	dispatch.m_cmd = cmd;
	dispatch.m_data = data;
	dispatch.m_lenght = lenght;
	dispatch.m_endCallBack = endCallBack;
	m_dispatchs.push_back(dispatch);
}

std::vector<DispatchHandler::Dispatch> DispatchHandler::getDispatchs(int cmd)
{
	std::vector<DispatchHandler::Dispatch> dispatchs;
	for (auto it = m_dispatchs.begin(); it != m_dispatchs.end(); ++it)
	{
		auto dispatch = *it;
		if (dispatch.m_cmd == cmd)
		{
			dispatchs.push_back(dispatch);
		}
	}

	return dispatchs;
}

// �����Ϣ����
int DispatchHandler::addDispatchHandler(const int cmd,const ccDispatchCallBack &dispatch)
{
	DispatchData data;
	data.m_cmd = cmd;
	data.m_func = dispatch;
	return addDispatchHandler(cmd,data);
}

int DispatchHandler::addDispatchHandler(int cmd, DispatchData& dispatch)
{
	if (checkHandler(cmd))
	{
		auto datas = getHandler(cmd);
		dispatch.m_order = datas.size()+1;
		datas.push_back(dispatch);
	}
	else
	{
		dispatch.m_order  = 1;
		std::vector<DispatchData> datas;
		datas.push_back(dispatch);
		m_dispatchMaps.insert(make_pair(cmd,datas));
	}

	return dispatch.m_order;
}

// ɾ����Ϣ����
void DispatchHandler::removeDispatchHandler(int cmd)
{
	auto it = m_dispatchMaps.begin();
	for (; it != m_dispatchMaps.end();)
	{
		auto key = it->first;
		if (key == cmd)
		{
			it = m_dispatchMaps.erase(it);
		}
		else
		{
			++it;
		}
	}
}

// ɾ����Ϣ����
void DispatchHandler::removeDispatchHandler(int cmd,int order)
{
	auto it = m_dispatchMaps.begin();
	for (; it != m_dispatchMaps.end();)
	{
		auto key = it->first;
		auto dispatchs = it->second;
		if (key == cmd)
		{
			for (auto itt = dispatchs.begin(); itt != dispatchs.end();)
			{
				auto dispatch = *itt;
				if (dispatch.m_order == order)
				{
					dispatchs.erase(itt);
					return ;
				}
			}
		}
		else
		{
			++it;
		}
	}
}

// ��⵱ǰ�Ƿ��ж�Ӧ������Ĳ���
bool DispatchHandler::checkHandler(int cmd)
{
	auto it = m_dispatchMaps.begin();
	for (;it != m_dispatchMaps.end(); ++it)
	{
		auto key = it->first;
		if (key == cmd)
		{
			return true;
		}
	}
	return false;
}

// ��ȡ��Ϣ����
std::vector<DispatchHandler::DispatchData> &DispatchHandler::getHandler(int cmd)
{
	auto it = m_dispatchMaps.begin();
	for (;it != m_dispatchMaps.end(); ++it)
	{
		auto key = it->first;
		if (key == cmd)
		{
			return it->second;
		}
	}

	return std::vector<DispatchData>();
}