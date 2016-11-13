#ifndef QDELEGATE_H
#define QDELEGATE_H

#include <QItemDelegate>


class QDelegate : public QItemDelegate
{
    Q_OBJECT
private:
    QString deleteType;         //委托类型
    QStringList deleteValue;    //委托值
public:
    explicit QDelegate(QObject *parent = 0);

    //设置委托类型
    void SetDeleteType(QString deleteType) {
        this->deleteType = deleteType;
    }

    //设计委托值
    void SetDeleteValue(QStringList deleteValue) {
        this->deleteValue = deleteValue;
    }
protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index)const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index)const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index)const;
};

#endif // QDELEGATE_H
