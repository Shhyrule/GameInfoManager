/**
 * @file MainWindow.h
 * @brief 定义程序的主窗口
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-18
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class YMainWindowClass; };
QT_END_NAMESPACE

//定义程序的主窗口，主要功能包括切换右侧页面
class YMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    YMainWindow(QWidget *parent = nullptr);
    ~YMainWindow();

private:
    Ui::YMainWindowClass *ui;
};
