#include "config.h"
#include "ui_config.h"

config::config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);
    inifilepath = "";
    ziel_root   = QDir::homePath();
    ziel_root  += QDir::separator();
    ziel_root  += "MySimpleBackup";
    ziel        = OHNE_ANGABE;
    q.clear();
}

config::~config()
{
    delete ui;
}


void config::set_inifilepath(QString path)
{
    write_ini();
    inifilepath = path;
    read_ini();
    emit signal_configname_changed();
}

void config::read_ini()
{
    if(!inifilepath.isEmpty())
    {
        QFile file(inifilepath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString msg;
            msg += "Fehler beim Zugriff auf die Datei \"";
            msg += inifilepath;
            msg += "\"!";
            QMessageBox::warning(this,"Fehler",msg,QMessageBox::Ok);
        }else
        {
            q.clear();
            while(!file.atEnd())
            {
                QString zeile = QLatin1String(  file.readLine()  );
                if(zeile.contains("ziel_root:"))
                {
                    ziel_root = text_mitte(zeile, "ziel_root:", "\n");
                    emit signal_update_ziel_root(ziel_root);
                }else if(zeile.contains("ziel:"))
                {
                    ziel = text_mitte(zeile, "ziel:", "\n");
                    emit signal_update_ziel(ziel);
                }else if(zeile.contains("quelle:"))
                {
                    q.add(text_mitte(zeile, "quelle:", "\n"));
                }
            }
            emit signal_update_quellen(q.get());//update_quellenlistwidget();
        }
        file.close();
    }
}

void config::write_ini()
{
    if(!inifilepath.isEmpty())
    {
        QFile file(inifilepath);
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
}

void config::add_quelle()
{
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Quellordner"), QDir::homePath());
    if(!tmp.isEmpty())
    {
        if(q.add(tmp))
        {
            emit signal_update_quellen(q.get());//update_quellenlistwidget();
            write_ini();
        }else
        {
            QMessageBox mb;
            mb.setText("Quelle oder Teilpfad der Quelle bereits eingetragen!");
            mb.exec();
        }
    }
}

void config::del_quelle(QString s)
{
    if(q.del(s))
    {
        emit signal_update_quellen(q.get());//update_quellenlistwidget();
        write_ini();
    }else
    {
        QMessageBox mb;
        mb.setText("Quelle konnte nicht entfernt werden!");
        mb.exec();
    }
}

void config::set_ziel()
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
    emit signal_update_ziel(ziel);
    write_ini();
}

void config::set_ziel_root()
{
    if(ziel_root.isEmpty())
    {
        ziel_root = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Ziel-Wurzelverzeichnis"), ziel_root);
    if(!tmp.isEmpty())
    {
        ziel_root = tmp;
        emit signal_update_ziel_root(ziel_root);
        write_ini();
    }
}
void config::set_ziel_root(QString zr)
{
    if(!QDir(zr).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + zr + "\" nicht gefunden!",QMessageBox::Ok);
    }else
    {
        ziel_root = zr;
    }
    emit signal_update_ziel_root(ziel_root);
}

text_zeilenweise config::get_quellen()
{
    return q.get();
}

void config::rename(QString newname)
{
    write_ini();
    QString name = get_configfolderpath();
    name += QDir::separator();
    name += newname;
    if(!newname.contains(".conf"))
    {
        name += ".conf";
    }
    inifilepath = name;
    write_ini();
    emit signal_configname_changed();
}

QString config::get_configfolderpath()
{
    QFileInfo info(inifilepath);
    return info.absolutePath();
}

QString config::get_configname()
{
    QFileInfo info(inifilepath);
    return info.fileName();
}

void config::set_inifile(QString name)
{
    QString path = get_configfolderpath();
    path += QDir::separator();
    path += name;
    if(!path.contains(".conf"))
    {
        path += ".conf";
    }
    set_inifilepath(path);
}







