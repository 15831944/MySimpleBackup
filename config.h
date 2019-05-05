#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include "quellen.h"
#include "mydef.h"

namespace Ui {
class config;
}

class config : public QDialog
{
    Q_OBJECT

public:
    explicit config(QWidget *parent = 0);
    ~config();
    void add_quelle();
    void del_quelle(QString s);
    text_zeilenweise get_quellen();
    void set_inifilepath(QString path);
    void set_inifile(QString name);
    void set_ziel();
    void set_ziel_root();
    void set_ziel_root(QString zr);
    void rename(QString newname);
    QString get_configfolderpath();
    QString get_configname();

private:
    Ui::config *ui;
    void read_ini();
    void write_ini();
    QString inifilepath;
    QString ziel_root;
    QString ziel;
    quellen q;

signals:
    void signal_update_quellen(text_zeilenweise quellen);
    void signal_update_ziel(QString ziel);
    void signal_update_ziel_root(QString ziel_root);
    void signal_configname_changed();
};

#endif // CONFIG_H
