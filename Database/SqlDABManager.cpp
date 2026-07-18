// SPDX-License-Identifier: MIT

#include "SqlDABManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

YSqlDABManager::YSqlDABManager()
{
	m_database = YDatabaseManager::GetInstance().GetDatabase();
}

bool YSqlDABManager::CreateTables()
{
	QSqlQuery query(m_database);

	if (!query.exec(
		"CREATE TABLE IF NOT EXISTS DABRecord ("
		"    id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"    date TEXT,"
		"    record_type INTEGER,"
		"    num REAL,"
		"    real_num REAL"
		")")) {
		qDebug() << "Failed to create DABRecord table:" << query.lastError().text();
		return false;
	}

	return true;
}

bool YSqlDABManager::SaveDABData(const FDogAccountBook& dab)
{
	QJsonObject obj;
	obj["HistoryImport"] = dab.history_import;
	obj["HistoryImportCost"] = dab.history_import_cost;
	obj["HistoryExport"] = dab.history_export;
	obj["HistoryRealCost"] = dab.history_real_cost;
	obj["Remaining"] = dab.remaining;
	obj["RemainingDiscount"] = dab.remaining_discount;
	obj["MaxId"] = dab.max_id;
	obj["MaxDate"] = dab.max_date.toString(Qt::ISODate);

	QString dataDir = QCoreApplication::applicationDirPath() + "/data";
	QDir dir(dataDir);
	if (!dir.exists()) {
		dir.mkpath(".");
	}

	QFile file(dataDir + "/dab.json");
	if (!file.open(QIODevice::WriteOnly)) {
		qDebug() << "Failed to open JSON file for writing";
		return false;
	}

	file.write(QJsonDocument(obj).toJson());
	file.close();

	QSqlQuery query(m_database);
	for (const FDogABRecord& r : dab.records) {
		query.prepare("UPDATE DABRecord SET real_num = ? WHERE id = ?");
		query.addBindValue(r.real_num);
		query.addBindValue(r.id);
		if (!query.exec()) {
			qDebug() << "Failed to sync real_num:" << query.lastError().text();
		}
	}

	return true;
}

bool YSqlDABManager::LoadDABData(FDogAccountBook& dab)
{
	QString dataDir = QCoreApplication::applicationDirPath() + "/data";
	QFile file(dataDir + "/dab.json");
	if (!file.exists()) {
		return false;
	}

	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "Failed to open JSON file for reading";
		return false;
	}

	QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
	file.close();

	dab.history_import = static_cast<float>(obj["HistoryImport"].toDouble());
	dab.history_import_cost = static_cast<float>(obj["HistoryImportCost"].toDouble());
	dab.history_export = static_cast<float>(obj["HistoryExport"].toDouble());
	dab.history_real_cost = static_cast<float>(obj["HistoryRealCost"].toDouble());
	dab.remaining = static_cast<float>(obj["Remaining"].toDouble());
	dab.remaining_discount = static_cast<float>(obj["RemainingDiscount"].toDouble());

	QSqlQuery query(m_database);
	if (!query.exec("SELECT * FROM DABRecord ORDER BY date")) {
		qDebug() << "Failed to load records:" << query.lastError().text();
		return false;
	}

	int max_id = 0;
	QDate max_date(1, 1, 1);

	while (query.next()) {
		FDogABRecord record;
		record.id = query.value("id").toInt();
		record.date = QDate::fromString(query.value("date").toString(), Qt::ISODate);
		record.record_type = static_cast<ERecordType>(query.value("record_type").toInt());
		record.num = query.value("num").toFloat();
		record.real_num = query.value("real_num").toFloat();

		if (record.id > max_id) max_id = record.id;
		if (record.date > max_date) max_date = record.date;

		dab.records.append(record);
	}

	dab.max_id = max_id;
	dab.max_date = max_date;

	return true;
}

bool YSqlDABManager::AddRecord(const FDogABRecord& record)
{
	QSqlQuery query(m_database);
	if (!query.prepare(
		"INSERT INTO DABRecord (date, record_type, num, real_num)"
		" VALUES (?, ?, ?, ?)")) {
		qDebug() << "Failed to prepare add record:" << query.lastError().text();
		return false;
	}

	query.addBindValue(record.date.toString(Qt::ISODate));
	query.addBindValue(static_cast<int>(record.record_type));
	query.addBindValue(record.num);
	query.addBindValue(record.real_num);

	if (!query.exec()) {
		qDebug() << "Failed to execute add record:" << query.lastError().text();
		return false;
	}

	return true;
}

bool YSqlDABManager::EraseRecord(int id)
{
	QSqlQuery query(m_database);
	if (!query.prepare("DELETE FROM DABRecord WHERE id=?")) {
		qDebug() << "Failed to prepare erase record:" << query.lastError().text();
		return false;
	}

	query.addBindValue(id);

	if (!query.exec()) {
		qDebug() << "Failed to execute erase record:" << query.lastError().text();
		return false;
	}

	return true;
}
