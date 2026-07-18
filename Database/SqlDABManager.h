/**
 * @file SqlDABManager.h
 * @brief 定义与DAB相关的文件存取类
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-18
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "DatabaseManager.h"
#include "../DataStruct/DogAccountBook.h"
#include <QSqlDatabase>

//与FDogAccountBook有关的文件存取类
class YSqlDABManager
{
public:
	YSqlDABManager();

	//第一次使用DAB文件存取时使用，创建DAB相关的表
	bool CreateTables();

	//保存DAB的核心数据
	bool SaveDABData(const FDogAccountBook& dab);
	//加载DAB的核心数据与各条记录
	bool LoadDABData(FDogAccountBook& dab);

	//给数据库添加记录
	bool AddRecord(const FDogABRecord& record);
	//删除数据库中的指定记录
	bool EraseRecord(int id);

private:
	QSqlDatabase m_database;
};
