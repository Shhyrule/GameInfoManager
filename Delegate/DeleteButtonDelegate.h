/**
 * @file DeleteButtonDelegate.h
 * @brief 为view中的item定义了委托，可以绘制按钮
 * @author Shhyrule
 * @version 1.0.0
 * @date 2026-07-18
 *
 * 本项目采用 MIT 许可证。详细条款见 LICENSE 文件。
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <QStyledItemDelegate>

//绘制按钮的委托类
class YDeleteButtonDelegate : public QStyledItemDelegate {
	Q_OBJECT
public:
	YDeleteButtonDelegate(QWidget* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;
signals:
    void clicked(const QModelIndex& index);
};