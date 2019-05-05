#include "dialog_seichern_laden.h"
#include "ui_dialog_seichern_laden.h"

Dialog_seichern_laden::Dialog_seichern_laden(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_seichern_laden)
{
    ui->setupUi(this);
    konfig = NULL;
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
    if(konfig == NULL)
    {
        QMessageBox mb;
        mb.setText("Zeiger auf konfig ist NULL!");
        mb.exec();
        this->close();
    }else
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
                konfig->rename(ui->lineEdit->text());
                emit signal_saved();
                this->close();
            }
        }else if(mode == "load")
        {
            if(ui->lineEdit->text().isEmpty())
            {
                QMessageBox mb;
                mb.setText(tr("Bitte wählen Sie eine Konfiguration aus!"));
                mb.exec();
            }else
            {
                konfig->set_inifile(ui->lineEdit->text());
                emit signal_changed();
                this->close();
            }
        }else
        {
            QMessageBox mb;
            mb.setText("Modus unbekannt!");
            mb.exec();
        }
    }
}

void Dialog_seichern_laden::set_config(config *c)
{
    konfig = c;
}

void Dialog_seichern_laden::update_listwidget()
{
    if(konfig == NULL)
    {
        QMessageBox mb;
        mb.setText("Zeiger auf konfig ist NULL!");
        mb.exec();
        this->close();
    }else
    {
        QDir programmordner(konfig->get_configfolderpath());
        QStringList ordnerinhalt;
        ordnerinhalt = programmordner.entryList(QDir::Files);
        text_zeilenweise tzconf;
        for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
        {
            QString name = *it;
            if(name.contains(".conf"))
            {
                tzconf.zeile_anhaengen(name);
            }
        }
        ui->listWidget->clear();
        for(uint i=1; i<=tzconf.zeilenanzahl() ;i++)
        {
            ui->listWidget->addItem(tzconf.zeile(i));
        }
    }
}

void Dialog_seichern_laden::showEvent(QShowEvent *event)
{
    update_listwidget();
    QDialog::showEvent(event);
}

void Dialog_seichern_laden::on_listWidget_currentRowChanged()
{
    if(mode == "save" || mode == "load")
    {
        ui->lineEdit->setText(ui->listWidget->currentItem()->text());
    }
}






