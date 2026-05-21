#ifndef EXPORTCSV_H
#define EXPORTCSV_H

#include <QString>

class ExportCSV
{
public:
    ExportCSV();

    static bool exportar(QString ruta);
};

#endif // EXPORTCSV_H