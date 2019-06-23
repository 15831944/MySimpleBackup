#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    folder  = QDir::homePath();
    folder += QDir::separator();
    folder += ".MySimpleBackup";
    ini  = folder;
    ini += QDir::separator();
    ini += "MySimpleBackup_ini.txt";
    QDir d(folder);
    d.mkpath(folder);    

    connect(&konfig, SIGNAL(signal_update_quellen(text_zeilenweise)),\
            this, SLOT(update_quellenlistwidget(text_zeilenweise)));
    connect(&konfig, SIGNAL(signal_update_ziel(QString)),\
            this, SLOT(update_lineedit_ziel(QString)));
    connect(&konfig, SIGNAL(signal_update_ziel_root(QString)),\
            this, SLOT(update_lineedit_ziel_root(QString)));

    setup();
    on_actionInfo_triggered();
    update_windowtitle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup()
{
    bool inifile_gefunden = false;
    QDir programmordner(folder);
    QStringList ordnerinhalt;
    ordnerinhalt = programmordner.entryList(QDir::Files);
    for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
    {
        QString name = *it;
        QFileInfo finfo(ini);
        if(name.contains(finfo.fileName()))
        {
            inifile_gefunden = true;
        }
    }

    if(inifile_gefunden == false)
    {
        QFile file(ini);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff auf ini-file!",QMessageBox::Ok);
        }else
        {

            konfig_aktuell  = folder;
            konfig_aktuell += QDir::separator();
            konfig_aktuell += "default.conf";
            schreibe_ini();
        }
        file.close();
    }else
    {
        QFile file(ini);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff auf ini-file!",QMessageBox::Ok);
        }else
        {
            while(!file.atEnd())
            {
                QString zeile = QLatin1String(  file.readLine()  );
                if(zeile.contains("konfig:"))
                {
                    konfig_aktuell = text_mitte(zeile, "konfig:", "\n");
                }
            }
        }
        file.close();
    }
    konfig.set_inifilepath(konfig_aktuell);
}

void MainWindow::schreibe_ini()
{
    QFile file(ini);
    file.remove();
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff auf ini-file!",QMessageBox::Ok);
    }else
    {
        file.write("konfig:");
        file.write(konfig_aktuell.toUtf8());
        file.write("\n");
        konfig.set_inifilepath(konfig_aktuell);
    }
    file.close();
}

void MainWindow::info()
{
    QString msg;
    msg += "MySinpleBackup\n";
    msg += "Autor: Oliver Schuft\n";

    ui->plainTextEdit->setPlainText(msg);
}
//------------------------------------------------------------Ziel:
void MainWindow::on_pushButton_ziel_root_clicked()
{
    konfig.set_ziel_root();
}
void MainWindow::on_pushButton_ziel_clicked()
{
    konfig.set_ziel();
}
void MainWindow::on_lineEdit_ziel_root_editingFinished()
{
    konfig.set_ziel_root(ui->lineEdit_ziel_root->text());
}
void MainWindow::update_lineedit_ziel(QString msg)
{
    ui->lineEdit_ziel->setText(msg);
}
void MainWindow::update_lineedit_ziel_root(QString msg)
{
    ui->lineEdit_ziel_root->setText(msg);
}

//------------------------------------------------------------Quellen:
void MainWindow::update_quellenlistwidget(text_zeilenweise quellen)
{
    ui->listWidget_quell->clear();
    for(uint i = 1; i<=quellen.zeilenanzahl() ;i++)
    {
        ui->listWidget_quell->addItem(quellen.zeile(i));
    }
}
void MainWindow::on_pushButton_quell_add_clicked()
{
    konfig.add_quelle();
}
void MainWindow::on_pushButton_quell_del_clicked()
{
    if(ui->listWidget_quell->currentIndex().isValid() &&\
       ui->listWidget_quell->currentItem()->isSelected())
    {
        text_zeilenweise tz = konfig.get_quellen();
        konfig.del_quelle(tz.zeile(ui->listWidget_quell->currentRow()+1));
    }
}

//------------------------------------------------------------

void MainWindow::on_actionInfo_triggered()
{
    info();
}

void MainWindow::on_actionspeichern_triggered()
{
    Dialog_seichern_laden d;
    d.set_mode_save();
    d.set_config(&konfig);
    connect(&d, SIGNAL(signal_saved()), this, SLOT(slot_konfigfile_changed()));
    d.exec();
}

void MainWindow::on_actionladen_triggered()
{
    Dialog_seichern_laden d;
    d.set_mode_load();
    d.set_config(&konfig);
    connect(&d, SIGNAL(signal_changed()), this, SLOT(slot_konfigfile_changed()));
    d.exec();;
}

void MainWindow::update_windowtitle()
{
    QString title = "MySimpleBackup (";
    title += konfig.get_configname();
    title += ")";
    this->setWindowTitle(title);
}

void MainWindow::slot_konfigfile_changed()
{
    konfig_aktuell  = folder;
    konfig_aktuell += QDir::separator();
    konfig_aktuell += konfig.get_configname();
    schreibe_ini();
    update_windowtitle();
}

void MainWindow::on_pushButton_start_clicked()
{
    b.set_ziel(konfig.get_ziel_komplett());
    b.set_quellen(konfig.get_quellen());
    b.start();
}
