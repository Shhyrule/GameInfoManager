/**
 * @file GameCoverWidget.h
 * @brief 定义了管理游戏封面的窗口
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-22
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <QWidget>
#include "ui_GameCoverWidget.h"

class YGameCoverWidget : public QWidget
{
	Q_OBJECT

public:
	YGameCoverWidget(QWidget *parent = nullptr);
	~YGameCoverWidget();

private:
	Ui::YGameCoverWidgetClass ui;
};
