/**
 * @file DatabaseManager.h
 * @brief 定义数据库单例类
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-18
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <QSqlDatabase>

class YDatabaseManager
{
public:
	//获取数据库单例
	static YDatabaseManager& GetInstance();

	//获取数据库类
	QSqlDatabase GetDatabase() const;
	//判断是否打开
	bool IsOpen() const;

private:
	YDatabaseManager();
	~YDatabaseManager();

	YDatabaseManager(const YDatabaseManager&) = delete;
	YDatabaseManager& operator=(const YDatabaseManager&) = delete;

	bool InitDatabase();

	QSqlDatabase m_database;
};
