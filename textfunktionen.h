#ifndef TEXTFUNKTIONEN_H
#define TEXTFUNKTIONEN_H

#include <QString>
#include "text_zeilenweise.h"

QString selektiereEintrag(QString text, QString beginntMit, QString endetMit);
QString text_links(const QString text, const QString trenntext);
QString text_rechts(const QString text, const QString trenntext);
QString text_mitte(const QString text, const QString textDavor, const QString textDanach);

uint tz_contains(text_zeilenweise tz, QString s);

#endif // TEXTFUNKTIONEN_H
