// SPDX-License-Identifier: MIT

#include "DeleteButtonDelegate.h"

#include <QStyleOptionButton>
#include <QApplication>
#include <QMouseEvent>

YDeleteButtonDelegate::YDeleteButtonDelegate(QWidget* parent):QStyledItemDelegate(parent)
{
}

void YDeleteButtonDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QStyleOptionButton sob;
	sob.rect = option.rect.adjusted(3, 1, -3, -1);
	sob.text = tr("删除");
	sob.state = QStyle::State_Enabled;

	if (option.state & QStyle::State_MouseOver) {
		sob.state |= QStyle::State_MouseOver;
	}
	if(option.state & QStyle::State_Sunken) {
		sob.state |= QStyle::State_Sunken;
	}

	QApplication::style()->drawControl(QStyle::CE_PushButton, &sob, painter);
}

bool YDeleteButtonDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
	if (event->type() == QEvent::MouseButtonRelease) {
		auto mouse_event = static_cast<QMouseEvent*>(event);
		QRect rect = option.rect.adjusted(3, 1, -3, -1);
		if (rect.contains(mouse_event->pos())) {
			emit clicked(index);
			return true;
		}
	}
	return QStyledItemDelegate::editorEvent(event, model, option, index);
}

