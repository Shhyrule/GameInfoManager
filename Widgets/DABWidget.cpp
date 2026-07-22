// SPDX-License-Identifier: MIT

#include "DABWidget.h"
#include <QPushButton>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include "../Delegate/DeleteButtonDelegate.h"

void YDABWidget::AddRecordToView(const FDogABRecord& new_record)
{
	QList<QStandardItem*> row;

	QDate date = new_record.date;
	auto date_item = new QStandardItem(date.toString());
	date_item->setData(date, Qt::EditRole);
	date_item->setData(new_record.id, Qt::UserRole + 1);
	row.append(date_item);
	
	QString type_string = new_record.record_type == ERecordType::EXPORT_TYPE ? tr("支出") : tr("收入");
	auto type_item = new QStandardItem();
	type_item->setData(new_record.record_type, Qt::EditRole);
	type_item->setData(type_string, Qt::DisplayRole);
	row.append(type_item);

	float num = new_record.num;
	auto num_item = new QStandardItem();
	num_item->setData(num, Qt::EditRole);
	num_item->setData(QString::number(num, 'f', 2), Qt::DisplayRole);
	row.append(num_item);

	float real_num = new_record.real_num;
	auto real_num_item = new QStandardItem();
	real_num_item->setData(real_num, Qt::EditRole);
	real_num_item->setData(QString::number(real_num, 'f', 2), Qt::DisplayRole);
	row.append(real_num_item);

	float discount = real_num / num;
	auto discount_item = new QStandardItem();
	discount_item->setData(discount, Qt::EditRole);
	discount_item->setData(QString::number(discount, 'f', 2), Qt::DisplayRole);
	row.append(discount_item);
	
	data_model->appendRow(row);
	UpdateHistoryInfo();
}

void YDABWidget::UpdateHistoryInfo()
{
	//设置支出相关历史信息
	float cost = data.GetHistoryExportCost(), real_cost = data.GetHistoryRealCost();
	QString export_line = tr("历史支出%1元，实际支出%2元，省钱%3")
		.arg(cost, 0, 'f', 2)
		.arg(real_cost, 0, 'f', 2)
		.arg(cost - real_cost, 0, 'f', 2);
	ui.ExportLabel->setText(export_line);

	//设置收入相关历史信息
	float remaining = data.GetRemaining();
	if (remaining < 0.01) {
		ui.ImportLabel->setText(tr("无余额"));
	}
	else {
		QString import_line = tr("余额%1元，折扣%2")
			.arg(remaining, 0, 'f', 2)
			.arg(data.GetCurDiscount(), 0, 'f', 2);
		ui.ImportLabel->setText(import_line);
	}
}

YDABWidget::YDABWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//将日期编辑器按钮的值设到今天
	QDate cur_date = QDate::currentDate();
	ui.ExportDateEdit->setDate(cur_date);
	ui.ImportDateEdit->setDate(cur_date);

	//创建数据库并尝试加载
	data_manager.CreateTables();
	data_manager.LoadDABData(data);

	//创建源数据并设置表头
	data_model = new QStandardItemModel;
	data_model->setColumnCount(6);
	data_model->setHorizontalHeaderLabels({
		tr("日期"),
		tr("类型"),
		tr("金额"),
		tr("实际花费"),
		tr("折扣"),
		"",
		});

	//创建代理数据
	proxy_model = new QSortFilterProxyModel(this);
	proxy_model->setSourceModel(data_model);
	proxy_model->setSortRole(Qt::EditRole);

	//初始化TableView
	QTableView* table = ui.RecordTableView;
	table->setModel(proxy_model);
	auto head_view = table->horizontalHeader();
	head_view->setSectionResizeMode(QHeaderView::Stretch);
	table->setSortingEnabled(true);
	table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QTableView::SelectRows);

	//为tableview添加删除键代理
	delete_button_delegate = new YDeleteButtonDelegate(this);
	table->setItemDelegateForColumn(5, delete_button_delegate);
	
	//加载历史记录到页面
	auto records = data.GetRecords();
	for (const auto& r : records) {
		AddRecordToView(r);
	}

	connect(ui.PushButtonAddImport, &QPushButton::clicked,this, &YDABWidget::_on_buttonImport_clicked);
	connect(ui.PushButtonAddExport, &QPushButton::clicked, this, &YDABWidget::_on_buttonExport_clicked);
	connect(ui.PushButtonRefresh, &QPushButton::clicked, this, &YDABWidget::_on_buttonRefresh_clicked);
	connect(delete_button_delegate, &YDeleteButtonDelegate::clicked, this, &YDABWidget::_on_buttonDelete_clicked);
}

YDABWidget::~YDABWidget()
{
	data_manager.SaveDABData(data);
}

void YDABWidget::_on_buttonImport_clicked() {
	QDate date = ui.ImportDateEdit->date();
	float import_num = ui.ImportSpinBox->value();
	float cost = ui.RealImportSpinBox->value();
	FDogABRecord new_record = data.AddImport(date, import_num, cost);
	data_manager.AddRecord(new_record);
	AddRecordToView(new_record);
}

void YDABWidget::_on_buttonExport_clicked()
{
	QDate date = ui.ExportDateEdit->date();
	float export_num = ui.ExportSpinBox->value();
	FDogABRecord new_record = data.AddExport(date, export_num);
	data_manager.AddRecord(new_record);
	AddRecordToView(new_record);
}

void YDABWidget::_on_buttonRefresh_clicked()
{
	data_model->clear();
	data_model->setHorizontalHeaderLabels({
		tr("日期"),
		tr("类型"),
		tr("金额"),
		tr("实际花费"),
		tr("折扣"),
		"",
		});
	auto records = data.GetRecords();
	for (const auto& r : records) {
		AddRecordToView(r);
	}
}

void YDABWidget::_on_buttonDelete_clicked(const QModelIndex& index)
{
	auto reply = QMessageBox::question(
		this,
		tr("警告"),
		tr("确认删除？此操作无法撤销"),
		QMessageBox::Yes | QMessageBox::No
	);
	if (reply == QMessageBox::No) {
		return;
	}

	QModelIndex data_index = proxy_model->mapToSource(index);
	int row = data_index.row();
	int id = data_model->data(data_model->index(data_index.row(), 0), Qt::UserRole + 1).toInt();
	data_manager.EraseRecord(id);
	data.EraseRecord(id);
	data_model->removeRow(row);
}

void YDABWidget::closeEvent(QCloseEvent* event)
{
	data_manager.SaveDABData(data);
}
