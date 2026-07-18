/**
 * @file SettingWidget.h
 * @brief 定义设置窗口
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-18
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <QWidget>
#include "ui_SettingWidget.h"

class YSettingWidget : public QWidget
{
	Q_OBJECT

public:
	YSettingWidget(QWidget *parent = nullptr);
	~YSettingWidget();

private:
	Ui::YSettingWidgetClass ui;
};
