#include "mainwindow.h"

#include <QApplication>

#include "database/databasemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseManager db;

    db.conectar();
    db.crearTabla();

    MainWindow w;
    w.show();

    return a.exec();
}