#include "SettingManager.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

YSettingManager::YSettingManager()
{
}

bool YSettingManager::LoadSettings(FSettingInfo& info)
{
	QFile file(GetFilePath());
	if (!file.exists()) {
		return false;
	}

	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "Failed to open setting file for reading";
		return false;
	}

	QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
	file.close();

	if (obj.contains("DefaultWindowId"))
		info.default_window_id = obj["DefaultWindowId"].toInt();
	if (obj.contains("DABWidgetVisible"))
		info.dab_widget_visible = obj["DABWidgetVisible"].toBool();

	return true;
}

bool YSettingManager::SaveSettings(const FSettingInfo& info)
{
	QJsonObject obj;
	obj["DefaultWindowId"] = info.default_window_id;
	obj["DABWidgetVisible"] = info.dab_widget_visible;

	QString dataDir = QCoreApplication::applicationDirPath();
	QDir dir(dataDir);
	if (!dir.exists()) {
		dir.mkpath(".");
	}

	QFile file(dataDir + "/setting.json");
	if (!file.open(QIODevice::WriteOnly)) {
		qDebug() << "Failed to open setting file for writing";
		return false;
	}

	file.write(QJsonDocument(obj).toJson());
	file.close();
	return true;
}

QString YSettingManager::GetFilePath() const
{
	return QCoreApplication::applicationDirPath() + "/data/setting.json";
}
