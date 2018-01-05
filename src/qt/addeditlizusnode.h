#ifndef ADDEDITLIZUSNODE_H
#define ADDEDITLIZUSNODE_H

#include <QDialog>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace Ui {
class AddEditLizusNode;
}


class AddEditLizusNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditLizusNode(QWidget *parent = 0);
    ~AddEditLizusNode();

protected:

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_AddEditAddressPasteButton_clicked();
    void on_AddEditPrivkeyPasteButton_clicked();
    void on_AddEditTxhashPasteButton_clicked();

signals:

private:
    Ui::AddEditLizusNode *ui;
};

#endif // ADDEDITLIZUSNODE_H
