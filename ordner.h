#ifndef ORDNER_H
#define ORDNER_H

#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include "text_zeilenweise.h"
#include "textfunktionen.h"

class ordner
{
public:
    ordner();
    void set_pfad(QString pfad);
    QString get_inhaltsliste();
    QString get_unterordner();
    text_zeilenweise get_inhaltsliste_tz();
    bool verschieben(QString ziel);
    QString basisname();

private:
    QString pfad_root;

    QString inhaltsliste(QString root);
    QString unterordner(QString root);
};

#endif // ORDNER_H
