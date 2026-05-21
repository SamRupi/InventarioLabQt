#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "database/databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnAgregar_clicked();

    void on_txtBuscar_textChanged(const QString &arg1);

    void on_btnEliminar_clicked();

    void on_btnExportar_clicked();

    void on_btnEditar_clicked();

    void on_tablaArticulos_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    DatabaseManager db;

    void cargarTabla();

    int idSeleccionado = -1;
};

#endif // MAINWINDOW_H