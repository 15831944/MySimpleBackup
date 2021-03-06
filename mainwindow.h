#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include "mydef.h"
#include "textfunktionen.h"
#include "quellen.h"
#include "dialog_seichern_laden.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_ziel_root_clicked();
    void on_pushButton_ziel_clicked();
    void on_lineEdit_ziel_root_editingFinished();
    void on_actionInfo_triggered();
    void on_pushButton_quell_add_clicked();
    void on_pushButton_quell_del_clicked();

    void on_actionspeichern_triggered();

    void on_actionladen_triggered();

private:
    Ui::MainWindow *ui;

    void setup();
    void schreibe_ini();
    void info();
    void update_quellenlistwidget();

    QString ziel_root;
    QString ziel;
    quellen q;
};

#endif // MAINWINDOW_H
