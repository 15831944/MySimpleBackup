#include "dialog_seichern_laden.h"
#include "ui_dialog_seichern_laden.h"

Dialog_seichern_laden::Dialog_seichern_laden(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_seichern_laden)
{
    ui->setupUi(this);
}

Dialog_seichern_laden::~Dialog_seichern_laden()
{
    delete ui;
}

void Dialog_seichern_laden::set_mode_save()
{
    mode = "save";
    this->setWindowTitle("Konfiguration speichern");
    ui->btn->setText("Speichern");
    ui->lineEdit->setEnabled(true);
}

void Dialog_seichern_laden::set_mode_load()
{
    mode = "load";
    this->setWindowTitle("Konfiguration laden");
    ui->btn->setText("Laden");
    ui->lineEdit->setEnabled(false);
}

void Dialog_seichern_laden::on_btn_clicked()
{
    if(mode == "save")
    {
        if(ui->lineEdit->text().isEmpty())
        {
            QMessageBox mb;
            mb.setText("Bitte geben Sie einen Namen ein!");
            mb.exec();
        }else
        {

        }
    }else if(mode == "load")
    {

    }else
    {
        QMessageBox mb;
        mb.setText("Modus unbekannt!");
        mb.exec();
    }
}
