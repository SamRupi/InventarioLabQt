#ifndef ARTICULO_H
#define ARTICULO_H

#include <QString>

class Articulo
{
private:
    int id;
    QString nombre;
    QString tipo;
    int cantidad;
    QString ubicacion;
    QString fecha;

public:
    Articulo();

    Articulo(
        QString nombre,
        QString tipo,
        int cantidad,
        QString ubicacion,
        QString fecha
        );

    QString getNombre();
    QString getTipo();
    int getCantidad();
    QString getUbicacion();
    QString getFecha();
};

#endif