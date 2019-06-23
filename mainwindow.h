#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDir>
#include <QMessageBox>
#include <QFile>
#include "mydef.h"
#include "textfunktionen.h"
#include "config.h"
#include "dialog_seichern_laden.h"
#include "backup.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void update_quellenlistwidget(text_zeilenweise quellen);
    void update_lineedit_ziel(QString msg);
    void update_lineedit_ziel_root(QString msg);
    void update_windowtitle();
    void slot_konfigfile_changed();

private slots:
    void on_pushButton_ziel_root_clicked();
    void on_pushButton_ziel_clicked();
    void on_lineEdit_ziel_root_editingFinished();
    void on_actionInfo_triggered();
    void on_pushButton_quell_add_clicked();
    void on_pushButton_quell_del_clicked();
    void on_actionspeichern_triggered();
    void on_actionladen_triggered();
    void on_pushButton_start_clicked();

private:
    Ui::MainWindow *ui;
    QString folder; //Pfad zum Programmordner
    QString ini;//Pfad zum globalen ini-file
    config konfig;//Klasse für Verwaltung einer Konfiguration
    QString konfig_aktuell;//zuletzt verwendetet/geladene Konfiguration
    backup b;

    void setup();
    void schreibe_ini();
    void info();



};

#endif // MAINWINDOW_H
