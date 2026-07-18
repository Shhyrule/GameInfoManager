/**
 * @file DogAccountBook.h
 * @brief 定义了DAB相关的数据类
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-18
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <QList>
#include <QDate>

//DAB类型的枚举
enum ERecordType {
	//支出类型
	EXPORT_TYPE,
	//收入类型
	IMPORT_TYPE,

};

//定义了DAB单条记录的数据结构
struct FDogABRecord {
	//记录的id
	int id;
	//记录的日期
	QDate date;
	//记录的类型
	ERecordType record_type;
	//记录的金额数量，对支出是实际价格，对收入是steam钱包中的实际收入
	float num;
	//记录的实际金额，对支出是考虑倒余额折扣实际的花费，对收入是倒余额的实际花费
	float real_num;
};

//定义了DAB数据类
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