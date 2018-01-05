#ifndef LIZUSNODECONFIGDIALOG_H
#define LIZUSNODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class LizusNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class LizusNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LizusNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:19700", QString privkey="MASTERNODEPRIVKEY");
    ~LizusNodeConfigDialog();

private:
    Ui::LizusNodeConfigDialog *ui;
};

#endif // LIZUSNODECONFIGDIALOG_H
