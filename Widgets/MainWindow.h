/**
 * @file MainWindow.h
 * @brief 定义程序的主窗口
 * @author Shhyrule
 * @version 1.0.1
 * @date 2026-07-18
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class YSettingWidget;
class YDABWidget;
class YGameCoverWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class YMainWindowClass; };
QT_END_NAMESPACE

//定义程序的主窗口，主要功能包括切换右侧页面
class YMainWindow : public QMainWindow
{
    Q_OBJECT 

private:
    Ui::YMainWindowClass *ui;

    YGameCoverWidget* GCWidget;
    YDABWidget* DABWidget;
    YSettingWidget* SettingWidget;

private:
    enum EWindowMode {
        COVER_MODE,
        DAB_MODE,
        SETTING_MODE,
    };

private slots:
    //隐藏模式切换侧边栏按钮按下时触发
    void _on_buttonHide_clicked();
    //显示模式切换侧边栏按钮按下时触发
    void _on_buttonShow_clicked();
    //设置按钮按下时触发
    void _on_settingButton_clicked();
    void _on_modeListWidget_itemClicked(QListWidgetItem* item);

private:
    //设置靠左左边栏的可见性
    void SetLeftLayoutVisible(bool new_value);
    //设置靠右左边栏的可见性
    void SetRightLayoutVisible(bool new_value);

    void TurnToMode(const int& new_mode);

public:
    YMainWindow(QWidget* parent = nullptr);
    ~YMainWindow();
};
