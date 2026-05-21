#include "databasemanager.h"

#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager()
{

}

bool DatabaseManager::conectar()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("inventario.db");

    if(db.open())
    {
        qDebug() << "Base de datos conectada";
        return true;
    }

    qDebug() << "Error al conectar";

    return false;
}

void DatabaseManager::crearTabla()
{
    QSqlQuery query;

    query.exec(
        "CREATE TABLE IF NOT EXISTS articulos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nombre TEXT,"
        "tipo TEXT,"
        "cantidad INTEGER,"
        "ubicacion TEXT,"
        "fecha TEXT)"
        );
}

bool DatabaseManager::insertarArticulo(
    QString nombre,
    QString tipo,
    int cantidad,
    QString ubicacion,
    QString fecha
    )
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO articulos "
        "(nombre, tipo, cantidad, ubicacion, fecha) "
        "VALUES (:nombre, :tipo, :cantidad, :ubicacion, :fecha)"
        );

    query.bindValue(":nombre", nombre);
    query.bindValue(":tipo", tipo);
    query.bindValue(":cantidad", cantidad);
    query.bindValue(":ubicacion", ubicacion);
    query.bindValue(":fecha", fecha);

    return query.exec();
}

QSqlQuery DatabaseManager::obtenerArticulos()
{
    QSqlQuery query;

    query.exec("SELECT * FROM articulos");

    return query;
}

QSqlQuery DatabaseManager::buscarArticulos(QString texto)
{
    QSqlQuery query;

    query.prepare(
        "SELECT * FROM articulos "
        "WHERE nombre LIKE :texto "
        "OR tipo LIKE :texto "
        "OR ubicacion LIKE :texto"
        );

    query.bindValue(":texto", "%" + texto + "%");

    query.exec();

    return query;
}

bool DatabaseManager::eliminarArticulo(int id)
{
    QSqlQuery query;

    query.prepare(
        "DELETE FROM articulos WHERE id = :id"
        );

    query.bindValue(":id", id);

    return query.exec();
}

bool DatabaseManager::actualizarArticulo(
    int id,
    QString nombre,
    QString tipo,
    int cantidad,
    QString ubicacion,
    QString fecha
    )
{
    QSqlQuery query;

    query.prepare(
        "UPDATE articulos SET "
        "nombre = :nombre, "
        "tipo = :tipo, "
        "cantidad = :cantidad, "
        "ubicacion = :ubicacion, "
        "fecha = :fecha "
        "WHERE id = :id"
        );

    query.bindValue(":id", id);
    query.bindValue(":nombre", nombre);
    query.bindValue(":tipo", tipo);
    query.bindValue(":cantidad", cantidad);
    query.bindValue(":ubicacion", ubicacion);
    query.bindValue(":fecha", fecha);

    return query.exec();
}