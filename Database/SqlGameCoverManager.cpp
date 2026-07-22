// SPDX-License-Identifier: MIT

#include "SqlGameCoverManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

YSqlGameCoverManager::YSqlGameCoverManager()
{
	m_database = YDatabaseManager::GetInstance().GetDatabase();
}

bool YSqlGameCoverManager::CreateTable()
{
	QSqlQuery query(m_database);

	if (!query.exec(
		"CREATE TABLE IF NOT EXISTS GameCover ("
		"    GCname TEXT PRIMARY KEY,"
		"    GCfileName TEXT"
		")")) {
		qDebug() << "Failed to create GameCover table:" << query.lastError().text();
		return false;
	}

	return true;
}

FGameCoverInfo YSqlGameCoverManager::GetCover(const QString& name)
{
	FGameCoverInfo info;

	QSqlQuery query(m_database);
	query.prepare("SELECT * FROM GameCover WHERE GCname = ?");
	query.addBindValue(name);

	if (!query.exec() || !query.next()) {
		return info;
	}

	info.name = query.value("GCname").toString();
	info.file_name = query.value("GCfileName").toString();
	return info;
}

bool YSqlGameCoverManager::SetCover(const FGameCoverInfo& cover)
{
	QSqlQuery query(m_database);
	query.prepare(
		"INSERT OR REPLACE INTO GameCover (GCname, GCfileName) VALUES (?, ?)");
	query.addBindValue(cover.name);
	query.addBindValue(cover.file_name);

	if (!query.exec()) {
		qDebug() << "Failed to set cover:" << query.lastError().text();
		return false;
	}

	return true;
}

bool YSqlGameCoverManager::RemoveCover(const QString& name)
{
	QSqlQuery query(m_database);
	query.prepare("DELETE FROM GameCover WHERE GCname = ?");
	query.addBindValue(name);

	if (!query.exec()) {
		qDebug() << "Failed to remove cover:" << query.lastError().text();
		return false;
	}

	return true;
}

QList<FGameCoverInfo> YSqlGameCoverManager::GetCovers()
{
	QList<FGameCoverInfo> list;

	QSqlQuery query(m_database);
	if (!query.exec("SELECT * FROM GameCover")) {
		qDebug() << "Failed to get covers:" << query.lastError().text();
		return list;
	}

	while (query.next()) {
		FGameCoverInfo info;
		info.name = query.value("GCname").toString();
		info.file_name = query.value("GCfileName").toString();
		list.append(info);
	}

	return list;
}
