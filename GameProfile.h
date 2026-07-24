/**
 * @file GameProfile.h
 * @brief 定义了游戏简介的数据类
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-24
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <QString>
#include <QList>

enum EGamePlatform {
	STEAM,
	PLAYSTATION,
	NINTENDO,
	XBOX,
	EPIC,
};

class FGameProfile {
	QString game_name;
	EGamePlatform platform;
	QList<QString> tags;
};