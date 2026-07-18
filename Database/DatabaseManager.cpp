#include "DatabaseManager.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QSqlError>

YDatabaseManager::YDatabaseManager()
{
	InitDatabase();
}

YDatabaseManager::~YDatabaseManager()
{
	if (m_database.isOpen()) {
		m_database.close();
	}
}

YDatabaseManager& YDatabaseManager::GetInstance()
{
	static YDatabaseManager instance;
	return instance;
}

QSqlDatabase YDatabaseManager::GetDatabase() const
{
	return m_database;
}

bool YDatabaseManager::IsOpen() const
{
	return m_database.isOpen();
}

bool YDatabaseManager::InitDatabase()
{
	QString appDir = QCoreApplication::applicationDirPath();
	QString dataDir = appDir + "/data";
 QDir dir(dataDir);
	if (!dir.exists()) {
		dir.mkpath(".");
	}

	QString dbPath = dataDir + "/account.db";
	m_database = QSqlDatabase::addDatabase("QSQLITE");
	m_database.setDatabaseName(dbPath);

	if (!m_database.open()) {
		qDebug() << "Failed to open database:" << m_database.lastError().text();
		return false;
	}

	qDebug() << "Database opened:" << dbPath;
	return true;
}
