#pragma once

#include "DatabaseManager.h"
#include "../DataStruct/DogAccountBook.h"
#include <QSqlDatabase>

class YSqlDABManager
{
public:
	YSqlDABManager();

	bool CreateTables();

	bool SaveDABData(const FDogAccountBook& dab);
	bool LoadDABData(FDogAccountBook& dab);

	bool AddRecord(const FDogABRecord& record);
	bool EraseRecord(int id);

private:
	QSqlDatabase m_database;
};
