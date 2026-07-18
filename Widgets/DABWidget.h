#pragma once

#include <QWidget>
#include "../Database/SqlDABManager.h"
#include "../DataStruct/DogAccountBook.h"
#include "ui_DABWidget.h"

class YSqlDABManager;
class QStandardItemModel;
class QSortFilterProxyModel;
class YDeleteButtonDelegate;

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
	void _on_buttonImport_clicked();
	void _on_buttonExport_clicked();
	//因为添加或者删除的时候不会动态更新export的实际值，所以需要刷新键
	void _on_buttonRefresh_clicked();

	void _on_buttonDelete_clicked(const QModelIndex &index);
protected:
	virtual void closeEvent(QCloseEvent* event) override;
private:
	float remaining = 0;

	YSqlDABManager data_manager;
	FDogAccountBook data;
	QStandardItemModel* data_model;
	QSortFilterProxyModel* proxy_model;
	YDeleteButtonDelegate* delete_button_delegate;

	Ui::YDABWidgetClass ui;
};
