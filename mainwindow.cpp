#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "reports/exportcsv.h"

#include <QTableWidgetItem>
#include <QMessageBox>
#include <QSqlQuery>
#include <QBrush>
#include <QColor>
#include <QFileDialog>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db.conectar();

    ui->tablaArticulos->setColumnCount(6);

    QStringList titulos;

    titulos << "ID"
            << "Nombre"
            << "Tipo"
            << "Cantidad"
            << "Ubicacion"
            << "Fecha";

    ui->tablaArticulos->setHorizontalHeaderLabels(titulos);

    ui->tablaArticulos->horizontalHeader()
        ->setStretchLastSection(true);

    ui->tablaArticulos->setSelectionBehavior(
        QAbstractItemView::SelectRows
        );

    ui->tablaArticulos->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );

    ui->tablaArticulos->setAlternatingRowColors(false);

    this->setWindowTitle("Gestor de Inventario");

    this->resize(1100, 700);

    this->setStyleSheet(
        "QMainWindow {"
        "background-color: #1e1e1e;"
        "}"

        "QLineEdit, QSpinBox, QDateEdit {"
        "background-color: #2d2d2d;"
        "color: white;"
        "border: 1px solid #555;"
        "padding: 5px;"
        "border-radius: 5px;"
        "}"

        "QPushButton {"
        "background-color: #0078d7;"
        "color: white;"
        "padding: 6px;"
        "border-radius: 6px;"
        "font-weight: bold;"
        "}"

        "QPushButton:hover {"
        "background-color: #2893ff;"
        "}"

        "QTableWidget {"
        "background-color: #2b2b2b;"
        "color: white;"
        "gridline-color: #444;"
        "selection-background-color: #0078d7;"
        "}"

        "QTableWidget::item {"
        "background-color: #2b2b2b;"
        "}"

        "QHeaderView::section {"
        "background-color: #444;"
        "color: white;"
        "padding: 5px;"
        "font-weight: bold;"
        "}"
        );

    cargarTabla();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarTabla()
{
    ui->tablaArticulos->setRowCount(0);

    QSqlQuery query = db.obtenerArticulos();

    int fila = 0;

    while(query.next())
    {
        ui->tablaArticulos->insertRow(fila);

        int cantidad = query.value("cantidad").toInt();

        QTableWidgetItem *itemId =
            new QTableWidgetItem(query.value("id").toString());

        QTableWidgetItem *itemNombre =
            new QTableWidgetItem(query.value("nombre").toString());

        QTableWidgetItem *itemTipo =
            new QTableWidgetItem(query.value("tipo").toString());

        QTableWidgetItem *itemCantidad =
            new QTableWidgetItem(QString::number(cantidad));

        QTableWidgetItem *itemUbicacion =
            new QTableWidgetItem(query.value("ubicacion").toString());

        QTableWidgetItem *itemFecha =
            new QTableWidgetItem(query.value("fecha").toString());

        if(cantidad <= 5)
        {
            itemCantidad->setBackground(QBrush(QColor(255, 100, 100)));

            itemCantidad->setText(
                QString::number(cantidad) + " ⚠ STOCK BAJO"
                );
        }

        ui->tablaArticulos->setItem(fila, 0, itemId);
        ui->tablaArticulos->setItem(fila, 1, itemNombre);
        ui->tablaArticulos->setItem(fila, 2, itemTipo);
        ui->tablaArticulos->setItem(fila, 3, itemCantidad);
        ui->tablaArticulos->setItem(fila, 4, itemUbicacion);
        ui->tablaArticulos->setItem(fila, 5, itemFecha);

        fila++;
    }
}

void MainWindow::on_btnAgregar_clicked()
{
    QString nombre = ui->txtNombre->text();
    QString tipo = ui->txtTipo->text();
    int cantidad = ui->spinCantidad->value();
    QString ubicacion = ui->txtUbicacion->text();
    QString fecha = ui->dateFecha->date().toString("yyyy-MM-dd");

    bool ok = db.insertarArticulo(
        nombre,
        tipo,
        cantidad,
        ubicacion,
        fecha
        );

    if(ok)
    {
        QMessageBox::information(
            this,
            "Correcto",
            "Articulo agregado"
            );

        cargarTabla();

        ui->txtNombre->clear();
        ui->txtTipo->clear();
        ui->spinCantidad->setValue(0);
        ui->txtUbicacion->clear();
    }
    else
    {
        QMessageBox::critical(
            this,
            "Error",
            "No se pudo agregar"
            );
    }
}

void MainWindow::on_txtBuscar_textChanged(const QString &arg1)
{
    ui->tablaArticulos->setRowCount(0);

    QSqlQuery query = db.buscarArticulos(arg1);

    int fila = 0;

    while(query.next())
    {
        ui->tablaArticulos->insertRow(fila);

        int cantidad = query.value("cantidad").toInt();

        QTableWidgetItem *itemId =
            new QTableWidgetItem(query.value("id").toString());

        QTableWidgetItem *itemNombre =
            new QTableWidgetItem(query.value("nombre").toString());

        QTableWidgetItem *itemTipo =
            new QTableWidgetItem(query.value("tipo").toString());

        QTableWidgetItem *itemCantidad =
            new QTableWidgetItem(QString::number(cantidad));

        QTableWidgetItem *itemUbicacion =
            new QTableWidgetItem(query.value("ubicacion").toString());

        QTableWidgetItem *itemFecha =
            new QTableWidgetItem(query.value("fecha").toString());

        if(cantidad <= 5)
        {
            itemCantidad->setBackground(QBrush(QColor(255, 100, 100)));

            itemCantidad->setText(
                QString::number(cantidad) + " ⚠ STOCK BAJO"
                );
        }

        ui->tablaArticulos->setItem(fila, 0, itemId);
        ui->tablaArticulos->setItem(fila, 1, itemNombre);
        ui->tablaArticulos->setItem(fila, 2, itemTipo);
        ui->tablaArticulos->setItem(fila, 3, itemCantidad);
        ui->tablaArticulos->setItem(fila, 4, itemUbicacion);
        ui->tablaArticulos->setItem(fila, 5, itemFecha);

        fila++;
    }
}

void MainWindow::on_btnEliminar_clicked()
{
    int fila = ui->tablaArticulos->currentRow();

    if(fila < 0)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Seleccione un articulo"
            );

        return;
    }

    int id = ui->tablaArticulos
                 ->item(fila, 0)
                 ->text()
                 .toInt();

    bool ok = db.eliminarArticulo(id);

    if(ok)
    {
        QMessageBox::information(
            this,
            "Correcto",
            "Articulo eliminado"
            );

        cargarTabla();
    }
    else
    {
        QMessageBox::critical(
            this,
            "Error",
            "No se pudo eliminar"
            );
    }
}

void MainWindow::on_btnExportar_clicked()
{
    QString ruta = QFileDialog::getSaveFileName(
        this,
        "Guardar CSV",
        "",
        "CSV (*.csv)"
        );

    if(ruta.isEmpty())
    {
        return;
    }

    bool ok = ExportCSV::exportar(ruta);

    if(ok)
    {
        QMessageBox::information(
            this,
            "Correcto",
            "CSV exportado"
            );
    }
    else
    {
        QMessageBox::critical(
            this,
            "Error",
            "No se pudo exportar"
            );
    }
}

void MainWindow::on_tablaArticulos_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    idSeleccionado = ui->tablaArticulos
                         ->item(row, 0)
                         ->text()
                         .toInt();

    ui->txtNombre->setText(
        ui->tablaArticulos->item(row, 1)->text()
        );

    ui->txtTipo->setText(
        ui->tablaArticulos->item(row, 2)->text()
        );

    QString cantidadTexto =
        ui->tablaArticulos->item(row, 3)->text();

    cantidadTexto.remove(" ⚠ STOCK BAJO");

    ui->spinCantidad->setValue(
        cantidadTexto.toInt()
        );

    ui->txtUbicacion->setText(
        ui->tablaArticulos->item(row, 4)->text()
        );
}

void MainWindow::on_btnEditar_clicked()
{
    if(idSeleccionado == -1)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Seleccione un articulo"
            );

        return;
    }

    QString nombre = ui->txtNombre->text();
    QString tipo = ui->txtTipo->text();
    int cantidad = ui->spinCantidad->value();
    QString ubicacion = ui->txtUbicacion->text();
    QString fecha = ui->dateFecha->date().toString("yyyy-MM-dd");

    bool ok = db.actualizarArticulo(
        idSeleccionado,
        nombre,
        tipo,
        cantidad,
        ubicacion,
        fecha
        );

    if(ok)
    {
        QMessageBox::information(
            this,
            "Correcto",
            "Articulo actualizado"
            );

        cargarTabla();
    }
    else
    {
        QMessageBox::critical(
            this,
            "Error",
            "No se pudo actualizar"
            );
    }
}