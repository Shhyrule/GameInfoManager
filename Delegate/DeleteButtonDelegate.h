#pragma once

#include <QStyledItemDelegate>

class YDeleteButtonDelegate : public QStyledItemDelegate {
	Q_OBJECT
private:
    QMargins margin = QMargins(3, 1, 3, 1);
public:
	YDeleteButtonDelegate(QWidget* parent = nullptr);

    void SetMargin(const QMargins& new_margin);
    QMargins GetMargin() const;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;
signals:
    void clicked(const QModelIndex& index);
};