#ifndef DIALOG_SEICHERN_LADEN_H
#define DIALOG_SEICHERN_LADEN_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Dialog_seichern_laden;
}

class Dialog_seichern_laden : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_seichern_laden(QWidget *parent = 0);
    ~Dialog_seichern_laden();
    void set_mode_save();
    void set_mode_load();

private slots:
    void on_btn_clicked();

private:
    Ui::Dialog_seichern_laden *ui;
    QString mode;
};

#endif // DIALOG_SEICHERN_LADEN_H
