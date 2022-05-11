#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtnn.h"
#include <QDebug>
#include <QPalette>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("../untitled/Image/icon.jpg"));
    this->setWindowTitle(("李鹏博"));
    //设置按钮颜色
//    QPalette pal = (ui->openAction)->palette();
//    pal.setColor(QPalette::ButtonText, Qt::red);
//    al.setColor(QPalette::Button, Qt::green);
//    ui->openAction->setPalette(pal);

    this->m_image=new int[256];
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_openAction_clicked()
{
    //读取图片的路径
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("Select image:"),
        "D:\\Documents\\Pictures", tr("Images (*.png *.bmp *.jpg *.gif)"));
    if (filename.isEmpty()) {
        return ;
    }
    //读取的图片
    QImage image;
    if (!image.load(filename)) {
        QMessageBox::information(this, tr("Error"), tr("Open file error"));
        return ;
    }

//    QPixmap pixmap = QPixmap::fromImage(image); //

//    ui->imageLabel->setPixmap(pixmap);
//    ui->imageLabel->resize(pixmap.size());
//    qDebug() << "filname: " << filename;
//    ui->imageLabel->setScaledContents(true);

    setWindowTitle(QFileInfo(filename).fileName() + tr(" - imageViewer"));



    QImage imagegry = image.convertToFormat(QImage::Format_Grayscale8);

//    for(int j = 0;j < image.width();j++)
//        {
//            for(int k = 0;k < image.height();k++)
//            {
//                //uchar gryColor = (qBlue(image.pixel(j,k))*299)/1000 + (qRed(image.pixel(j,k))*587)/1000 + (qGreen(image.pixel(j,k))*114)/1000;
//                uchar gryColor = (qBlue(image.pixel(j,k))*114)/1000 + (qRed(image.pixel(j,k))*299)/1000 + (qGreen(image.pixel(j,k))*587)/1000;
//                QColor vRGB = image.pixel(j,k);
//                vRGB.setRed(gryColor);
//                vRGB.setGreen(gryColor);
//                vRGB.setBlue(gryColor);
//                vRGB.setAlpha(255);
//                imagegry.setPixelColor(j,k,vRGB);

//                if(gryColor > 128)
//                {
//                    gryColor = 0xff;
//                }
//                else
//                {
//                    gryColor = 0x00;
//                }

//                vRGB.setRed(gryColor);
//                vRGB.setGreen(gryColor);
//                vRGB.setBlue(gryColor);
//                vRGB.setAlpha(255);
//                image.setPixelColor(j,k,vRGB);
//            }
//        }

    QPixmap pixmap = QPixmap::fromImage(imagegry); //
    qDebug() << "filname: " << pixmap;

    ui->imageLabel->setPixmap(pixmap);
    ui->imageLabel->resize(pixmap.size());
//    ui->imageLabel->move(90,90);
    ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size(), Qt::IgnoreAspectRatio     , Qt::SmoothTransformation));
//    ui->imageLabel->setAlignment(Qt::AlignHCenter);
    //顺便将图片搞成int数组
    unsigned char *pData=imagegry.bits();
    for(int i=0;i<16*16;i+=1)
    {
        if (pData[i]<128){
            pData[i]=0;
            m_image[i]=-1;
        }
        else{
            pData[i]=1;
            m_image[i]=1;
        }
        if (i%16 == 0)
            cout<<endl;
        cout<<int((m_image[i]))<<" ";



    }

}

void MainWindow::on_changeAction_clicked()
{
    int image_class;
    image_class=qtnn(this->m_image);
    ui->dataEdit->setText(QString::number(image_class));


}
