#include "ordner.h"

ordner::ordner()
{

}

void ordner::set_pfad(QString pfad)
{
    QFileInfo i(pfad);
    if(i.isDir())
    {
        pfad_root = pfad;
    }
}

QString ordner::get_inhaltsliste()
{
    return inhaltsliste(pfad_root);
}

text_zeilenweise ordner::get_inhaltsliste_tz()
{
    text_zeilenweise tz;
    tz.set_text(get_inhaltsliste());
    return tz;
}

QString ordner::inhaltsliste(QString root)
{
    QString msg;
    if(!root.isEmpty())
    {
        QDir myfolder(root);
        QStringList ordnerinhalt;
        ordnerinhalt = myfolder.entryList();
        text_zeilenweise tz;
        for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
        {
            QString name = *it;
            if(name != "." && name != "..")
            {
                QString name_mit_pfad = root;
                name_mit_pfad += QDir::separator();
                name_mit_pfad += name;
                QFileInfo i(name_mit_pfad);
                if(!i.isDir())
                {
                    tz.zeile_anhaengen(name_mit_pfad);
                }else
                {
                    tz.zeile_anhaengen(name_mit_pfad);
                    QString newroot = root;
                    newroot += QDir::separator();
                    newroot += name;
                    tz.zeilen_anhaengen(inhaltsliste(newroot));
                }
            }
        }
        msg = tz.get_text();
    }
    return msg;
}

QString ordner::get_unterordner()
{
    return unterordner(pfad_root);
}

QString ordner::unterordner(QString root)
{
    QString msg;
    if(!root.isEmpty())
    {
        QDir myfolder(root);
        QStringList ordnerinhalt;
        ordnerinhalt = myfolder.entryList(QDir::Dirs);
        text_zeilenweise tz;
        for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
        {
            QString name = *it;
            if(name != "." && name != "..")
            {
                QString name_mit_pfad = root;
                name_mit_pfad += QDir::separator();
                name_mit_pfad += name;
                tz.zeile_anhaengen(name_mit_pfad);
            }
        }
        msg = tz.get_text();
    }
    return msg;
}

bool ordner::verschieben(QString ziel)
{
    bool alles_ok = true;

    text_zeilenweise tz_alt;
    tz_alt = get_inhaltsliste_tz();

    text_zeilenweise tz_neu;
    for(uint i=1; i<= tz_alt.zeilenanzahl();i++)
    {
        QString alt, neu;
        alt = tz_alt.zeile(i);
        neu = alt;
        neu.replace(pfad_root, ziel + QDir::separator() + basisname() );
        tz_neu.zeile_anhaengen(neu);
    }

    text_zeilenweise tz_alt_file, tz_alt_folder;
    text_zeilenweise tz_neu_file, tz_neu_folder;
    for(uint i=1; i<= tz_alt.zeilenanzahl();i++)
    {
        QFileInfo info(tz_alt.zeile(i));
        if(info.isDir())
        {
            tz_alt_folder.zeile_anhaengen(tz_alt.zeile(i));
            tz_neu_folder.zeile_anhaengen(tz_neu.zeile(i));
        }else
        {
            tz_alt_file.zeile_anhaengen(tz_alt.zeile(i));
            tz_neu_file.zeile_anhaengen(tz_neu.zeile(i));
        }
    }
    for(uint i=1; i<=tz_neu_folder.zeilenanzahl() ;i++)
    {
        QDir d(tz_neu_folder.zeile(i));
        if( d.mkpath(tz_neu_folder.zeile(i)) == false)
        {
            alles_ok = false;
        }
    }
    if(alles_ok == true)
    {
        for(uint i=1; i<=tz_alt_file.zeilenanzahl() ;i++)
        {
            QString neu = tz_neu_file.zeile(i);
            QString alt = tz_alt_file.zeile(i);
            if(neu.isEmpty())
            {
                continue;
            }
            if(QFile::exists(neu))
            {
                QFile::remove(neu);
            }
            if(QFile::rename(alt, neu) == false)
            {
                alles_ok = false;
            }
        }
    }
    if(alles_ok == true)
    {
        QDir d(pfad_root);
        d.removeRecursively();
        set_pfad(ziel + QDir::separator() + basisname());
    }
    return alles_ok;
}

QString ordner::basisname()
{
    QString msg;
    if(!pfad_root.isEmpty())
    {
        QFileInfo info(pfad_root);
        msg = info.baseName();
    }
    return msg;
}
