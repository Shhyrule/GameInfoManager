#pragma once

#include <QList>
#include <QDate>

enum ERecordType {
	EXPORT_TYPE,
	IMPORT_TYPE,

};

struct FDogABRecord {
	int id;
	QDate date;
	ERecordType record_type;
	float num;
	float real_num;
};

class FDogAccountBook {
	friend class YSqlDABManager;
private:
	QList<FDogABRecord> records;

	float history_import = 0;
	float history_import_cost = 0;
	float history_export = 0;
	float history_real_cost = 0;
	float remaining = 0;
	float remaining_discount = 1;

	int max_id = 0;
	QDate max_date = QDate(1, 1, 1);
private:
	//当删除记录或者在今天之前添加记录时，刷新信息
	void refresh();

	void _on_export_added(FDogABRecord& record);
	void _on_import_added(const FDogABRecord& record);
public:
	//删除指定id对应的记录
	void EraseRecord(const int& id);
	//添加收入记录
	FDogABRecord AddImport(const QDate& date, float import, float cost);
	//添加支出记录
	FDogABRecord AddExport(const QDate& date, float export_num);

	//获取历史总花费
	float GetHistoryImportCost() const;
	//获取历史总支出
	float GetHistoryExportCost() const;
	//获取历史实际支出
	float GetHistoryRealCost() const;
	//获取历史折扣
	float GetHistoryDiscount() const;
	//获取余额
	float GetRemaining() const;
	//获取余额折扣
	float GetCurDiscount() const;
	//获取省钱量
	float GetCut() const;
	//获取所有记录
	QList<FDogABRecord> GetRecords() const;
};