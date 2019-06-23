#ifndef BACKUP_H
#define BACKUP_H

#include <QMessageBox>
#include <QDate>
#include <QTime>
#include "text_zeilenweise.h"
#include "ordner.h"
#include "textfunktionen.h"
#include "umwandeln.h"

class backup
{
public:
    backup();
    void set_ziel(QString z);
    void set_quellen(text_zeilenweise q);
    void start();

private:
    QString ziel;
    text_zeilenweise quellen;
    text_zeilenweise balt;  //altes = vorhandenes Backup

    QString qtoz(QString q);//wandelt Quellpfad in Zielpfad um
};

#endif // BACKUP_H
