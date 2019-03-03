#include "quellen.h"

quellen::quellen()
{

}

quellen::quellen(QString q)
{
    pfade.set_text(q);
}

quellen::quellen(text_zeilenweise q)
{
    pfade = q;
}

bool quellen::add(QString pfad)
{
    bool bekannt = false;
    for(uint i=1; i<=pfade.zeilenanzahl() ;i++)
    {
        QString zeile = pfade.zeile(i);
        if(pfad == zeile)
        {
            bekannt = true;
            break;
        }else if(pfad.contains(zeile))
        {
            if(text_links(zeile, pfad).length() == 0)
            {//ist Unterverzeichnis einer bekannten Quelle
                bekannt = true;
                break;
            }
        }else if(zeile.contains(pfad))
        {
            if(text_links(pfad, zeile).length() == 0)
            {//ein Unterverzeichnis der neuen Quelle ist bereits in der Liste
                bekannt = true;
                break;
            }
        }
    }
    if(!bekannt)
    {
        pfade.zeile_anhaengen(pfad);
        return true;//Erfolg
    }else
    {
        return false;//Misserfolg
    }
}

bool quellen::del(QString pfad)
{
    for(uint i=1; i<=pfade.zeilenanzahl() ;i++)
    {
        if(pfad == pfade.zeile(i))
        {
            pfade.zeile_loeschen(i);
            return true; //Erfolg
        }
    }
    return false;//Misserfolg
}

text_zeilenweise quellen::get()
{
    return pfade;
}

void quellen::clear()
{
    pfade.clear();
}
