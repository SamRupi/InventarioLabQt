#include "exportcsv.h"

#include <QFile>
#include <QTextStream>
#include <QSqlQuery>

ExportCSV::ExportCSV()
{

}

bool ExportCSV::exportar(QString ruta)
{
    QFile archivo(ruta);

    if(!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&archivo);

    out << "ID,Nombre,Tipo,Cantidad,Ubicacion,Fecha\n";

    QSqlQuery query;

    query.exec("SELECT * FROM articulos");

    while(query.next())
    {
        out << query.value("id").toString() << ",";
        out << query.value("nombre").toString() << ",";
        out << query.value("tipo").toString() << ",";
        out << query.value("cantidad").toString() << ",";
        out << query.value("ubicacion").toString() << ",";
        out << query.value("fecha").toString() << "\n";
    }

    archivo.close();

    return true;
}