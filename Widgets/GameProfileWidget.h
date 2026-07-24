#pragma once

#include <QWidget>
#include "ui_GameProfileWidget.h"

class YGameProfileWidget : public QWidget
{
	Q_OBJECT

public:
	YGameProfileWidget(QWidget *parent = nullptr);
	~YGameProfileWidget();

private:
	Ui::YGameProfileWidgetClass ui;
};
