#ifndef QUELLEN_H
#define QUELLEN_H

#include "text_zeilenweise.h"
#include "textfunktionen.h"
#include <QMessageBox>

class quellen
{
public:
    quellen();
    quellen(QString q);
    quellen(text_zeilenweise q);
    bool add(QString pfad);
    bool del(QString pfad);
    text_zeilenweise get();
    void clear();

private:
    text_zeilenweise pfade;
};

#endif // QUELLEN_H
