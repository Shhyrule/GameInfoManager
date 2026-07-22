/**
 * @file SettingManager.h
 * @brief 定义设置的读写类
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-18
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

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
