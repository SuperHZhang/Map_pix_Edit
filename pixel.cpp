#include "pixel.h"
#include"newdialog.h"
#include"savedialog.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>
#include<QImage>
#include<QLabel>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QToolBar>
#include<QPixmap>
#include<QString>
#include<QGroupBox>
#include<QGridLayout>
//#include<QPicture>
#include<QPushButton>
#include<QFileDialog>
#include<QDockWidget>
#include<QMainWindow>
#include<QMessageBox>
#include<QApplication>
//#include"colorbar.h"
pixel::pixel(QObject *parent)
    : QObject(parent)
{
    setLayout();
}

void pixel::setLayout()
{
    window = new QWidget;
    mainWindow = new QMainWindow;
    QVBoxLayout* vlayout = new QVBoxLayout;
    QVBoxLayout* vlayout1 = new QVBoxLayout;
    QVBoxLayout* vlayout2 = new QVBoxLayout;
    QHBoxLayout* hlayout = new QHBoxLayout;
    QHBoxLayout* hlayout1 = new QHBoxLayout;

    QDockWidget* dock = new QDockWidget(QStringLiteral("工具栏"),window);

    //设置paint窗口处于中央
    paint = new paintWindow;

    vlayout2->addStretch();
    vlayout2->addWidget(paint);
    vlayout2->addStretch();

    hlayout1->addStretch();
    hlayout1->addLayout(vlayout2);
    hlayout1->addStretch();

    dock1 = new QDockWidget(QStringLiteral("图像"),window);

    createMenu();
    createTool();
    setLeftTool();
    createColorGroup();
    dock->setWidget(leftWidget);
    dock1->setWidget(paint->getImage());
    vlayout->addWidget(menuBar);
    vlayout->addWidget(toolBar);

    toolBar->setStyleSheet("background-color:rgb(220,220,220);");

    vlayout1->addWidget(color);
    hlayout->addLayout(hlayout1);
    hlayout->addLayout(vlayout1);
    vlayout->addLayout(hlayout);
    mainWindow->addDockWidget(Qt::LeftDockWidgetArea,dock);
    mainWindow->addDockWidget(Qt::RightDockWidgetArea,dock1);

    //connect(paint,SIGNAL(changeImg()),this,SLOT(updateImg()));
    //connect(paint,SIGNAL(changeColor(QColor)),color,SLOT(changeColor(QColor)));

    window->setLayout(vlayout);
    window->resize(800,700);
    mainWindow->setCentralWidget(window);
    mainWindow->show();
}

void pixel::createMenu()
{
    menuBar = new QMenuBar();
    menuBar->setFixedHeight(28);
    fileMenu = menuBar->addMenu(QStringLiteral("文件"));
    editMenu = menuBar->addMenu(QStringLiteral("编辑"));
    showMenu = menuBar->addMenu(QStringLiteral("显示"));
    actionNew = fileMenu->addAction(QIcon("I:/DL/Map_pix_Edit/res/new.png"),QStringLiteral("&新建"));
    actionOpen = fileMenu->addAction(QIcon("I:/DL/Map_pix_Edit/res/open.png"),QStringLiteral("&打开"));
    actionSave = fileMenu->addAction(QIcon("I:/DL/Map_pix_Edit/res/save.png"),QStringLiteral("&保存"));
    actionUndo = editMenu->addAction(QIcon("I:/DL/Map_pix_Edit/res/undo.png"),QStringLiteral("&撤销"));
    actionRedo = editMenu->addAction(QIcon("I:/DL/Map_pix_Edit/res/redo.png"),QStringLiteral("&重做"));
    actionShowGrid = showMenu->addAction(QIcon("I:/DL/Map_pix_Edit/res/grid.png"),QStringLiteral("&显示网格"));

    actionNew->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    actionUndo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    actionRedo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));

    connect(actionSave, SIGNAL(triggered()),this, SLOT(save()));
    connect(actionUndo,SIGNAL(triggered()),this,SLOT(undo()));
    connect(actionRedo,SIGNAL(triggered()),this,SLOT(redo()));
    connect(actionShowGrid,SIGNAL(triggered()),this,SLOT(showGrid()));
    connect(actionNew,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(actionOpen,SIGNAL(triggered()),this,SLOT(open()));
}

void pixel::open()
{
    QString name = QFileDialog::getOpenFileName(window,
        tr("Choose Image"),
        "",
        tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF")); //选择路径
    if(name.isEmpty())
    {
        return;
    }
    else
    {
        QImage* img = new QImage();
        if(! ( img->load(name) ) ) //加载图像
        {
            QMessageBox msg(QMessageBox::Warning, "error", QStringLiteral("打开图像失败"),
                                 QMessageBox::Yes, NULL);
            msg.exec();
            delete img;
            return;
        }
        else{
            if(img->width()<150&&img->height()<150){
                paint->newImage(img);
                delete img;
                return;
            }
            else{
                QMessageBox msg(QMessageBox::Warning, "error", QStringLiteral("图片过大"),
                                     QMessageBox::Yes, NULL);
                msg.exec();
                delete img;
                return;
            }
        }
    }
}

bool pixel::save()
{
    filename = QFileDialog::getSaveFileName(window,
        tr("Save Image"),
        "",
        tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF")); //选择路径
    if(filename.isEmpty())
    {
        return false;
    }
    else
    {
        saveDialog* dialog = new saveDialog();
        dialog->show();
        connect(dialog,SIGNAL(save(int)),this,SLOT(saveImg(int)));
        return true;
    }
}

void pixel::saveImg(int size)
{
    paint->saveImage(filename,size);
}

void pixel::undo()
{
    //paint->undo();
}

void pixel::redo()
{
    //paint->redo();
}

void pixel::createTool()
{
    toolBar = new QToolBar(tr("&文件"));
    toolBar->addSeparator();

    toolBar->addAction(actionNew);
    toolBar->addAction(actionOpen);
    toolBar->addAction(actionSave);
    toolBar->addAction(actionUndo);
    toolBar->addAction(actionRedo);
    toolBar->addAction(actionShowGrid);
}

void pixel::setLeftTool()
{
    leftWidget = new QWidget();
    leftWidget->setStyleSheet("background-color:rgb(230,230,230);");
    QString str[] = {
        "I:/DL/Map_pix_Edit/res/rect.png","I:/DL/Map_pix_Edit/res/pixel.png","I:/DL/Map_pix_Edit/res/color.png","I:/DL/Map_pix_Edit/res/fullrect.png",
        "I:/DL/Map_pix_Edit/res/line.png","I:/DL/Map_pix_Edit/res/circle.png","I:/DL/Map_pix_Edit/res/fullcircle.png","I:/DL/Map_pix_Edit/res/erase.png","I:/DL/Map_pix_Edit/res/getcolor.png"
    };
    QString str1[] = {
        "I:/DL/Map_pix_Edit/res/rect1.png","I:/DL/Map_pix_Edit/res/pixel1.png","I:/DL/Map_pix_Edit/res/color1.png","I:/DL/Map_pix_Edit/res/fullrect1.png",
        "I:/DL/Map_pix_Edit/res/line1.png","I:/DL/Map_pix_Edit/res/circle1.png","I:/DL/Map_pix_Edit/res/fullcircle1.png","erase1.png","I:/DL/Map_pix_Edit/res/getcolor1.png"
    };
    drawRectBtn = new Button(str[0],str1[0],str1[0]);
    drawPixelBtn = new Button(str[1],str1[1],str1[1]);
    colorBtn = new Button(str[2],str1[2],str1[2]);
    drawFullRectBtn = new Button(str[3],str1[3],str1[3]);
    drawLineBtn = new Button(str[4],str1[4],str1[4]);
    drawCircleBtn = new Button(str[5],str1[5],str1[5]);
    drawFullCircleBtn = new Button(str[6],str1[6],str1[6]);
    eraseBtn = new Button(str[7],str1[7],str1[7]);
    getColorBtn = new Button(str[8],str1[8],str1[8]);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(drawRectBtn);
    vlayout->addWidget(drawPixelBtn);
    vlayout->addWidget(colorBtn);
    vlayout->addWidget(drawFullRectBtn);
    vlayout->addWidget(drawLineBtn);
    vlayout->addWidget(drawCircleBtn);
    vlayout->addWidget(drawFullCircleBtn);
    vlayout->addWidget(eraseBtn);
    vlayout->addWidget(getColorBtn);
    vlayout->addStretch();
    leftWidget->setLayout(vlayout);

    drawPixelBtn->setPressImg();

    connect(drawRectBtn, SIGNAL(clicked()),this, SLOT(drawRect()));
    connect(drawPixelBtn, SIGNAL(clicked()),this, SLOT(drawPixel()));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(fillColor()));
    connect(drawFullRectBtn,SIGNAL(clicked()),this,SLOT(drawFullRect()));
    connect(drawLineBtn,SIGNAL(clicked()),this,SLOT(drawLine()));
    connect(drawCircleBtn,SIGNAL(clicked()),this,SLOT(drawCircle()));
    connect(drawFullCircleBtn,SIGNAL(clicked()),this,SLOT(drawFullCircle()));
    connect(eraseBtn,SIGNAL(clicked()),this,SLOT(erase()));
    connect(getColorBtn,SIGNAL(clicked()),this,SLOT(getColor()));
}

void pixel::newFile()
{
    QMessageBox msg(QMessageBox::Warning, "warning", QStringLiteral("是否保存当前图像？"),QMessageBox::Yes | QMessageBox::No, NULL);
    if(msg.exec()==QMessageBox::Yes)
    {
        if(!save())return;
    }
    newDialog* dialog = new newDialog;
    connect(dialog,SIGNAL(sendIndex(int,int)),paint,SLOT(changeSize(int,int)));
    dialog->show();
}

void pixel::updateIcon(int id)
{
    drawRectBtn->setReleaseImg();
    drawPixelBtn->setReleaseImg();
    colorBtn->setReleaseImg();
    drawFullRectBtn->setReleaseImg();
    drawLineBtn->setReleaseImg();
    drawCircleBtn->setReleaseImg();
    drawFullCircleBtn->setReleaseImg();
    eraseBtn->setReleaseImg();
    getColorBtn->setReleaseImg();

    switch(id){
        case 1:drawRectBtn->setPressImg();
        break;
        case 2:drawPixelBtn->setPressImg();
        break;
        case 3:colorBtn->setPressImg();
        break;
        case 4:drawFullRectBtn->setPressImg();
        break;
        case 5:drawLineBtn->setPressImg();
        break;
        case 6:drawCircleBtn->setPressImg();
        break;
        case 7:drawFullCircleBtn->setPressImg();
        break;
        case 8:eraseBtn->setPressImg();
        break;
        case 9:getColorBtn->setPressImg();
        break;
        default:
        break;
    }
}

void pixel::drawRect()
{
    paint->drawRect();
    updateIcon(1);
}

void pixel::drawPixel()
{
    paint->drawPixel();
    updateIcon(2);
}

void pixel::fillColor()
{
    //paint->fillColor();
    updateIcon(3);
}

void pixel::drawFullRect()
{
    paint->drawFullRect();
    updateIcon(4);
}

void pixel::drawLine()
{
    paint->drawLine();
    updateIcon(5);
}

void pixel::drawCircle()
{
    paint->drawCircle();
    updateIcon(6);
}

void pixel::drawFullCircle()
{
    paint->drawFullCircle();
    updateIcon(7);
}

void pixel::erase()
{
    paint->erase();
    updateIcon(8);
}

void pixel::getColor()
{
    paint->getColor();
    updateIcon(9);
}

void pixel::showGrid()
{
    paint->showGrid();
}

void pixel::createColorGroup()
{
    color = new colorWindow();
}

void pixel::updateImg()
{
    dock1->setWidget(paint->getImage());
}

pixel::~pixel()
{

}
