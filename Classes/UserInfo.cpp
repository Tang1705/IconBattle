#include  "UserInfo.h"
#include "platform/CCFileUtils.h"

USING_NS_CC;

UserInfo* UserInfo::instance = nullptr;

UserInfo* UserInfo::getInstance()
{
	if (instance == nullptr) instance = new UserInfo;
	return instance;
}

void UserInfo::init()
{
	if (FileUtils::getInstance()->isFileExist("userinfo.ini"))
	{
		const auto userInfo = FileUtils::getInstance()->getStringFromFile("userinfo.ini");

		//���û���Ϣ���Ƶ�char[]�Ա�strtok()����������Ϣ
		char temp[200];
		strcpy(temp, userInfo.c_str());

		auto *split = "\t";

		//��\t�ָ��������ļ���Ϣ
		auto i = 0;
		auto tempStr = strtok(temp, split);
		while (tempStr != nullptr)
		{
			string toStr = tempStr;
			

		}

	}
}
