#pragma once

#include "pvzclass.h"

class Mod
{
public:
	std::string MOD_TITLE;
	std::string MOD_AUTHOR;
	std::string MOD_VERSION;
	std::string MOD_DESCRIPTION;
	// ģ�鱻����ʱ����һ��
	virtual void onLoad() = 0;
	// ��������ᱻ����ѭ������
	// ÿ��������ģ��� update ��ִ��һ�Σ��ͻ�����ִ����һ��
	// ����ִ�м����ģ��� update Ч��֮���й�
	virtual void update() = 0;
};

