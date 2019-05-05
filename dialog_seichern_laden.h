#ifndef DIALOG_SEICHERN_LADEN_H
#define DIALOG_SEICHERN_LADEN_H

#include <QDialog>
#include <QMessageBox>
#include "config.h"

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
    void set_config(config *c);

private slots:
    void on_btn_clicked();
    void on_listWidget_currentRowChanged();

private:
    Ui::Dialog_seichern_laden *ui;
    QString mode;
    config *konfig;

    void update_listwidget();

protected:
    virtual void showEvent(QShowEvent *event);

signals:
    void signal_saved();
    void signal_changed();

};

#endif // DIALOG_SEICHERN_LADEN_H
