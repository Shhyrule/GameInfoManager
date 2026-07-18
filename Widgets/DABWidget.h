/**
 * @file DABWidget.h
 * @brief 定义DAB相关的窗口
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-18
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <QWidget>
#include "../Database/SqlDABManager.h"
#include "../DataStruct/DogAccountBook.h"
#include "ui_DABWidget.h"

class YSqlDABManager;
class QStandardItemModel;
class QSortFilterProxyModel;
class YDeleteButtonDelegate;

//DAB相关的窗口
class YDABWidget : public QWidget
{
	Q_OBJECT

private:
	void AddRecordToView(const FDogABRecord& new_record);
	void UpdateHistoryInfo();
public:
	YDABWidget(QWidget *parent = nullptr);
	~YDABWidget();
private slots:
	//在收入的确认按钮按下时触发
	void _on_buttonImport_clicked();
	//在支出的确认按钮按下时触发
	void _on_buttonExport_clicked();
	//刷新键按下时触发，因为添加或者删除的时候不会动态更新export的实际值，所以需要刷新键
	void _on_buttonRefresh_clicked();
	//表格的删除键按下时触发，删除相应的行
	void _on_buttonDelete_clicked(const QModelIndex &index);
protected:
	virtual void closeEvent(QCloseEvent* event) override;
private:
	YSqlDABManager data_manager;
	FDogAccountBook data;
	QStandardItemModel* data_model;
	QSortFilterProxyModel* proxy_model;
	YDeleteButtonDelegate* delete_button_delegate;

	Ui::YDABWidgetClass ui;
};
