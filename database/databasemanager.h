#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class DatabaseManager
{
private:
    QSqlDatabase db;

public:
    DatabaseManager();

    bool conectar();

    void crearTabla();

    bool insertarArticulo(
        QString nombre,
        QString tipo,
        int cantidad,
        QString ubicacion,
        QString fecha
        );

    QSqlQuery obtenerArticulos();

    QSqlQuery buscarArticulos(QString texto);

    bool eliminarArticulo(int id);

    bool actualizarArticulo(
        int id,
        QString nombre,
        QString tipo,
        int cantidad,
        QString ubicacion,
        QString fecha
        );
};

#endif // DATABASEMANAGER_H