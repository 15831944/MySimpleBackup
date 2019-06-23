#include "backup.h"

backup::backup()
{

}

void backup::set_ziel(QString z)
{
    ziel = z;
}

void backup::set_quellen(text_zeilenweise q)
{
    quellen = q;
}

QString backup::qtoz(QString q)
{
    q.replace(QDir::separator(), "_#_");
    return q;
}

void backup::start()
{
    //zuo       Ziel-Unter-Ordner
    //quellen   Oiginal-Quellpfade
    //qkopie    mit qtoz umgewandelte Quellpfade

    //vorhandene Hauptverzeichnisse des Backupverzeichnisses ermitteln
    ordner o;
    o.set_pfad(ziel);
    text_zeilenweise zuo; //Ziel-Unter-Ordner
    zuo.set_text(o.get_unterordner());

    //Archivorner im Backupverzeichnis erstellen:
    QString archiv = "Archiv";
    QString adirpfad;
    adirpfad = ziel;
    adirpfad += QDir::separator();
    adirpfad += archiv;
    QDir adir(adirpfad);
    adir.mkpath(adirpfad);
    uint index = tz_contains(zuo, adirpfad);
    zuo.zeile_loeschen(index);

    QString jetzt;
    jetzt  = int_to_qstring(QDate::currentDate().year());
    jetzt += "_";
    jetzt += int_to_qstring(QDate::currentDate().month());
    jetzt += "_";
    jetzt += int_to_qstring(QDate::currentDate().day());
    jetzt += "__";
    jetzt += int_to_qstring(QTime::currentTime().hour());
    jetzt += "_";
    jetzt += int_to_qstring(QTime::currentTime().minute());
    jetzt += "_";
    jetzt += int_to_qstring(QTime::currentTime().second());
    QString aordner;    //Archiv-Ordner
    aordner  = ziel;
    aordner += QDir::separator();
    aordner += archiv;
    aordner += QDir::separator();
    aordner += jetzt;
    QDir ao(aordner);
    ao.mkdir(aordner);

    //Namen der Hauptverzeichnisse des Backups definieren:
    text_zeilenweise qkopie;
    for(uint i=1; i<=quellen.zeilenanzahl();i++)
    {
        QString q = quellen.zeile(i);
        qkopie.zeile_anhaengen(qtoz(q));
    }

    //Hauptverzeichnisse des Backups erstellen:
    for(uint i=1; i<=qkopie.zeilenanzahl() ;i++)
    {
        uint index = tz_contains(zuo, qkopie.zeile(i));
        if(index == 0)//nicht enthalten
        {
            QString tmp = ziel;
            tmp += QDir::separator();
            tmp += qkopie.zeile(i);
            QDir d(tmp);
            d.mkpath(tmp);
        }
    }

    //Alle Ordner außer den Hauptverzeichnissen in das Archiv verschieben:
    text_zeilenweise alteOrdner = zuo;
    for(uint i=1; i<=qkopie.zeilenanzahl() ;i++)
    {
        QString tmp = ziel;
        tmp += QDir::separator();
        tmp += qkopie.zeile(i);
        uint index = tz_contains(alteOrdner, tmp);
        if(index != 0)//enthalten
        {
            alteOrdner.zeile_ersaetzen(index, "void");
        }
    }
    for(uint i=1; i<=alteOrdner.zeilenanzahl() ;i++)
    {
        QString pfad = alteOrdner.zeile(i);
        if(pfad != "void")
        {
            ordner o;
            o.set_pfad(pfad);
            o.verschieben(aordner);
        }
    }

    //nächste Schritte:
    //...

}
