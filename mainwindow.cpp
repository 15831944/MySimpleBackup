#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ziel_root   = QDir::homePath();
    ziel_root  += QDir::separator();
    ziel_root  += "MySimpleBackup";
    ziel        = OHNE_ANGABE;
    q.clear();
    setup();
    on_actionInfo_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup()
{
    bool inifile_gefunden = false;
    QDir programmordner("./");
    QStringList ordnerinhalt;
    ordnerinhalt = programmordner.entryList(QDir::Files);
    for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
    {
        QString name = *it;
        if(name.contains(INIFILE))
        {
            inifile_gefunden = true;
        }
    }

    if(inifile_gefunden == false)
    {
        QFile file(INIFILE);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
        }else
        {
            file.write("ziel_root:");
            file.write(ziel_root.toUtf8());
            file.write("\n");

            file.write("ziel:");
            file.write(ziel.toUtf8());
            file.write("\n");
        }
        file.close();
    }else
    {
        QFile file(INIFILE);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
        }else
        {
            q.clear();
            while(!file.atEnd())
            {
                QString zeile = QLatin1String(  file.readLine()  );
                if(zeile.contains("ziel_root:"))
                {
                    ziel_root = text_mitte(zeile, "ziel_root:", "\n");
                    ui->lineEdit_ziel_root->setText(ziel_root);
                }else if(zeile.contains("ziel:"))
                {
                    ziel = text_mitte(zeile, "ziel:", "\n");
                    ui->lineEdit_ziel->setText(ziel);
                }else if(zeile.contains("quelle:"))
                {
                    q.add(text_mitte(zeile, "quelle:", "\n"));
                }
            }
            update_quellenlistwidget();
        }
        file.close();
    }

    ui->lineEdit_ziel_root->setText(ziel_root);
    ui->lineEdit_ziel->setText(ziel);
}

void MainWindow::schreibe_ini()
{
    QFile file(INIFILE);
    file.remove();
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
    }else
    {
        file.write("ziel_root:");
        file.write(ziel_root.toUtf8());
        file.write("\n");

        file.write("ziel:");
        file.write(ziel.toUtf8());
        file.write("\n");

        text_zeilenweise tz = q.get();
        for(uint i=1; i<=tz.zeilenanzahl() ;i++)
        {
            file.write("quelle:");
            file.write(tz.zeile(i).toUtf8());
            file.write("\n");
        }
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
    if(ziel_root.isEmpty())
    {
        ziel_root = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Ziel-Wurzelverzeichnis"), ziel_root);
    if(!tmp.isEmpty())
    {
        ziel_root = tmp;
        ui->lineEdit_ziel_root->setText(ziel_root);
        schreibe_ini();
    }
}

void MainWindow::on_pushButton_ziel_clicked()
{
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Ziel-Wurzelverzeichnis"), ziel_root);
    if(tmp.isEmpty())
    {
        tmp = OHNE_ANGABE;
    }else
    {
        if(tmp.contains(ziel_root))
        {
            QString li = ziel_root + QDir::separator();
            tmp = text_rechts(tmp, li);
        }else
        {
            QMessageBox mb;
            mb.setText("Zielordner befindet sich nicht im Wurzelverzeichnis!");
            mb.exec();
            tmp = OHNE_ANGABE;
        }
    }
    ziel = tmp;
    ui->lineEdit_ziel->setText(ziel);
    schreibe_ini();
}

void MainWindow::on_lineEdit_ziel_root_editingFinished()
{
    QString eingabe = ui->lineEdit_ziel_root->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_ziel_root->setText(ziel_root);
    }else
    {
        ziel_root = eingabe;
    }
}

//------------------------------------------------------------Quellen:
void MainWindow::update_quellenlistwidget()
{
    ui->listWidget_quell->clear();
    text_zeilenweise tz = q.get();
    for(uint i = 1; i<=tz.zeilenanzahl() ;i++)
    {
        ui->listWidget_quell->addItem(tz.zeile(i));
    }
}

void MainWindow::on_pushButton_quell_add_clicked()
{
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Quellordner"), QDir::homePath());
    if(!tmp.isEmpty())
    {
        if(q.add(tmp))
        {
            update_quellenlistwidget();
            schreibe_ini();
        }else
        {
            QMessageBox mb;
            mb.setText("Quelle oder Teilpfad der Quelle bereits eingetragen!");
            mb.exec();
        }
    }
}

void MainWindow::on_pushButton_quell_del_clicked()
{
    if(ui->listWidget_quell->currentIndex().isValid() &&\
       ui->listWidget_quell->currentItem()->isSelected())
    {
        QString tmp = q.get().zeile(ui->listWidget_quell->currentRow()+1);
        if(q.del(tmp))
        {
            update_quellenlistwidget();
            schreibe_ini();
        }else
        {
            QMessageBox mb;
            mb.setText("Quelle konnte nicht entfernt werden!");
            mb.exec();
        }
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
    d.exec();
}

void MainWindow::on_actionladen_triggered()
{
    Dialog_seichern_laden d;
    d.set_mode_load();
    d.exec();;
}
