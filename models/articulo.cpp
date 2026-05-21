#include "articulo.h"

Articulo::Articulo()
{

}

Articulo::Articulo(
    QString nombre,
    QString tipo,
    int cantidad,
    QString ubicacion,
    QString fecha
    )
{
    this->nombre = nombre;
    this->tipo = tipo;
    this->cantidad = cantidad;
    this->ubicacion = ubicacion;
    this->fecha = fecha;
}

QString Articulo::getNombre()
{
    return nombre;
}

QString Articulo::getTipo()
{
    return tipo;
}

int Articulo::getCantidad()
{
    return cantidad;
}

QString Articulo::getUbicacion()
{
    return ubicacion;
}

QString Articulo::getFecha()
{
    return fecha;
}