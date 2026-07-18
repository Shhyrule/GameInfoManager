#pragma once

#include <QString>

#include "../DataStruct/SettingInfo.h"

class YSettingManager
{
public:
	YSettingManager();

	bool LoadSettings(FSettingInfo& info);
	bool SaveSettings(const FSettingInfo& info);

private:
	QString GetFilePath() const;
};
