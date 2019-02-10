#ifndef TEXTFUNKTIONEN_H
#define TEXTFUNKTIONEN_H

#include <QString>

QString selektiereEintrag(QString text, QString beginntMit, QString endetMit);
QString text_links(const QString text, const QString trenntext);
QString text_rechts(const QString text, const QString trenntext);
QString text_mitte(const QString text, const QString textDavor, const QString textDanach);

#endif // TEXTFUNKTIONEN_H
