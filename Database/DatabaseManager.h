#pragma once

#include <QSqlDatabase>

class YDatabaseManager
{
public:
	static YDatabaseManager& GetInstance();

	QSqlDatabase GetDatabase() const;
	bool IsOpen() const;

private:
	YDatabaseManager();
	~YDatabaseManager();

	YDatabaseManager(const YDatabaseManager&) = delete;
	YDatabaseManager& operator=(const YDatabaseManager&) = delete;

	bool InitDatabase();

	QSqlDatabase m_database;
};
