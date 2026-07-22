// SPDX-License-Identifier: MIT

#include "MainWindow.h"

#include "DABWidget.h"
#include "SettingWidget.h"
#include "GameCoverWidget.h"
#include "../DataStruct/SettingInfo.h"
#include "../Database/SettingManager.h"

YMainWindow::YMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::YMainWindowClass())
{
    ui->setupUi(this);

    //隐藏右侧左边栏
    SetRightLayoutVisible(false);

    //加载设置文件
    FSettingInfo setting;
    YSettingManager().LoadSettings(setting);

    //初始化设置窗口
    SettingWidget = new YSettingWidget(this);
    ui->StackedWidget->addWidget(SettingWidget);

    //初始化GC窗口
    if (setting.gc_widget_visible) {
        auto gc_item = new QListWidgetItem();
        gc_item->setText(tr("游戏封面管理"));
        gc_item->setData(Qt::UserRole + 1, EWindowMode::COVER_MODE);
        ui->ModeListWidget->addItem(gc_item);
        GCWidget = new YGameCoverWidget(this);
        ui->StackedWidget->addWidget(GCWidget);
    }

    //初始化DAB窗口
    if (setting.dab_widget_visible) {
        auto dab_item = new QListWidgetItem();
        dab_item->setText(tr("DAB"));
        dab_item->setData(Qt::UserRole + 1, EWindowMode::DAB_MODE);
        ui->ModeListWidget->addItem(dab_item);
        DABWidget = new YDABWidget(this);
        ui->StackedWidget->addWidget(DABWidget);
    }

    //根据设置文件选择初始窗口
    TurnToMode(setting.default_window_id);

    connect(ui->PushButtonHideList, &QPushButton::clicked, this, &YMainWindow::_on_buttonHide_clicked);
    connect(ui->PushButtonShowList, &QPushButton::clicked, this, &YMainWindow::_on_buttonShow_clicked);
    connect(ui->LeftSettingPushButton, &QPushButton::clicked, this, &YMainWindow::_on_settingButton_clicked);
    connect(ui->RightSettingPushButton, &QPushButton::clicked, this, &YMainWindow::_on_settingButton_clicked);
    connect(ui->ModeListWidget, &QListWidget::itemClicked, this, &YMainWindow::_on_modeListWidget_itemClicked);
}

YMainWindow::~YMainWindow()
{
    delete ui;
}

void YMainWindow::_on_buttonHide_clicked() 
{
    SetLeftLayoutVisible(false);
    SetRightLayoutVisible(true);
}

void YMainWindow::_on_buttonShow_clicked()
{
    SetLeftLayoutVisible(true);
    SetRightLayoutVisible(false);
}

void YMainWindow::_on_settingButton_clicked()
{
    ui->StackedWidget->setCurrentWidget(SettingWidget);
}

void YMainWindow::_on_modeListWidget_itemClicked(QListWidgetItem* item)
{
    TurnToMode(item->data(Qt::UserRole + 1).toInt());
}

void YMainWindow::SetLeftLayoutVisible(bool new_value)
{
    ui->PushButtonHideList->setVisible(new_value);
    ui->LeftSettingPushButton->setVisible(new_value);
    ui->ModeListWidget->setVisible(new_value);
}

void YMainWindow::SetRightLayoutVisible(bool new_value)
{
    ui->PushButtonShowList->setVisible(new_value);
    ui->RightSettingPushButton->setVisible(new_value);
}

void YMainWindow::TurnToMode(const int& new_mode)
{
    switch (new_mode) {
    case EWindowMode::DAB_MODE:
        ui->StackedWidget->setCurrentWidget(DABWidget);
        break;
    case EWindowMode::COVER_MODE:
        ui->StackedWidget->setCurrentWidget(GCWidget);
        break;
    }
}


