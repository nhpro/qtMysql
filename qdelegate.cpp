#include "qdelegate.h"

#include <QLineEdit>
#include <QComboBox>

QDelegate::QDelegate(QObject *parent)
    : QItemDelegate(parent)
{
    deleteType = "QLineEdit";
    deleteValue.append("");
}

QWidget *QDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    QWidget *editor = new QWidget(parent);

    if (deleteType == "QLineEdit") {
        QLineEdit *txt = new QLineEdit(parent);
        txt->setText(deleteValue.at(0));
        txt->setStyleSheet("border-radius:0px;");
        editor = txt;
    } else if (deleteType == "QComboBox") {
        QComboBox *cbox = new QComboBox(parent);
        cbox->addItems(deleteValue);
        cbox->setStyleSheet("border-radius:0px;");
        editor = cbox;
    }

    editor->installEventFilter(const_cast<QDelegate *>(this));
    return editor;
}

void QDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index).toString();

    if (deleteType == "QLineEdit") {
        QLineEdit *txt = static_cast<QLineEdit *>(editor);
        txt->setText(str);
    } else if (deleteType == "QComoBox") {
        QComboBox *cbox = static_cast<QComboBox *>(editor);
        cbox->setCurrentIndex(cbox->findText(str));
    }
}

void QDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index)const
{
    if (deleteType == "QLineEdit") {
        QLineEdit *txt = static_cast<QLineEdit *>(editor);
        QString str = txt->text();
        model->setData(index, str);
    } else if (deleteType == "QComboBox") {
        QComboBox *cbox = static_cast<QComboBox *>(editor);
        QString str = cbox->currentText();
        model->setData(index, str);
    }
}

void QDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
