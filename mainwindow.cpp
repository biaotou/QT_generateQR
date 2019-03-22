
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMouseEvent>
#include <QScrollArea>
#include <QImageWriter>
#include <QScrollBar>
#include <QSettings>
#include <QApplication>
#include <QDebug>
#include <QAxObject>
//#include <QAxWidget>
#include "QVariantListListModel.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  ,m_xls(NULL)
{
    ui->setupUi(this);
    QVariantListListModel* md = new QVariantListListModel(this);
    ui->tableView->setModel(md);
    md->setVariantListListPtr(&m_datas);
}


MainWindow::~MainWindow()
{
    delete ui;
}
/*显示二维码*/
void MainWindow::updateQRImage(QString encodeString)
{
    int levelIndex = 1;
    int versionIndex = 0;
    bool bExtent = true;
    int maskIndex = -1;

    successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, encodeString.toUtf8().data() );
    if ( !successfulEncoding )
    {
        ui->image_label->clear();
        ui->image_label->setText( tr("没有数据") );
        return;
    }

    int qrImageSize = qrEncode.m_nSymbleSize;


    encodeImageSize = qrImageSize + ( QR_MARGIN * 2 );
    QImage encodeImage( encodeImageSize, encodeImageSize, QImage::Format_Mono );
    encodeImage.fill( 1 );

    for ( int i = 0; i < qrImageSize; i++ )
        for ( int j = 0; j < qrImageSize; j++ )
            if ( qrEncode.m_byModuleData[i][j] )
                encodeImage.setPixel( i + QR_MARGIN, j + QR_MARGIN, 0 );

    ui->image_label->setPixmap( QPixmap::fromImage( encodeImage ) );
    setScale(7);

}

/*设置图片大小*/
void MainWindow::setScale(int scale)
{
    if ( successfulEncoding )
    {
        int scale_size = encodeImageSize * scale;

        const QPixmap & scale_image = ui->image_label->pixmap()->scaled( scale_size, scale_size );
        ui->image_label->setPixmap( scale_image );


    }
}
void MainWindow::on_pushButton_clicked()
{
  QString  QR_Data=ui->textEdit->toPlainText();
  updateQRImage(QR_Data);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString xlsFile = QFileDialog::getOpenFileName(this,QString(),QString(),"excel(*.xls *.xlsx)");
     if(xlsFile.isEmpty())
       {
         return;
     }
     if(m_xls.isNull())
     {
         m_xls.reset(new ExcelBase);
     }
     m_xls->open(xlsFile);
     m_xls->setCurrentSheet(1);
     m_xls->readAll(m_datas);
     QVariantListListModel* md = qobject_cast<QVariantListListModel*>(ui->tableView->model());
     if(md)
     {
         md->updateData();
     }
     qDebug()<<"open over";
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

  //  ui->label->setText(index.data().toString());
    ui->label_2->setText(index.data().toString() );
    updateQRImage(index.data().toString());
}
