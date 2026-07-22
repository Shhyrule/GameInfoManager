/**
 * @file SqlGameCoverManager.h
 * @brief 定义了游戏封面的读写类
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-22
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "DatabaseManager.h"
#include "../DataStruct/GameCoverInfo.h"
#include <QSqlDatabase>
#include <QList>

class YSqlGameCoverManager
{
public:
	YSqlGameCoverManager();

	bool CreateTable();

	FGameCoverInfo GetCover(const QString& name);
	bool SetCover(const FGameCoverInfo& cover);
	bool RemoveCover(const QString& name);
	QList<FGameCoverInfo> GetCovers();

private:
	QSqlDatabase m_database;
};
