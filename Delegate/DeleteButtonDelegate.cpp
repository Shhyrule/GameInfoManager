#include "DeleteButtonDelegate.h"

#include <QStyleOptionButton>
#include <QApplication>
#include <QMouseEvent>

YDeleteButtonDelegate::YDeleteButtonDelegate(QWidget* parent):QStyledItemDelegate(parent)
{
}

void YDeleteButtonDelegate::SetMargin(const QMargins& new_margin)
{
	margin = new_margin;
}

QMargins YDeleteButtonDelegate::GetMargin() const
{
	return margin;
}

void YDeleteButtonDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QStyleOptionButton sob;
	sob.rect = option.rect.adjusted(margin.left(), margin.top(), -margin.right(), -margin.bottom());
	sob.text = QString::fromLocal8Bit("É¾³ý");
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
		QRect rect = option.rect.adjusted(margin.left(), margin.top(), -margin.right(), -margin.bottom());
		if (rect.contains(mouse_event->pos())) {
			emit clicked(index);
			return true;
		}
	}
	return QStyledItemDelegate::editorEvent(event, model, option, index);
}

