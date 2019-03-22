#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QList>
#include <QVariant>
#include "QRCodeGenerator.h"
#include "ExcelBase.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QScopedPointer<ExcelBase> m_xls;
    QList< QList<QVariant> > m_datas;
    void updateQRImage(QString encodeString);
   void setScale(int scale);
    CQR_Encode qrEncode;
    bool successfulEncoding;
     int encodeImageSize;
};

#endif // MAINWINDOW_H
