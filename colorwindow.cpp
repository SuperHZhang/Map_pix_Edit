#include"colorwindow.h"
#include"paint.h"
#include"button.h"
//#include"colorbar.h"
//#include<QGridLayout>
#include<QVBoxLayout>
#include<QGroupBox>
#include<QSignalMapper>
#include<QColorDialog>

colorWindow::colorWindow(QWidget* parent)
    :QWidget(parent)
{
    QVBoxLayout* vlayout = new QVBoxLayout();
    QGridLayout* glayout = new QGridLayout();
    QGridLayout* glayout1 = new QGridLayout();
    QSignalMapper* signalMapper[10];
    QString str0 = "I:/DL/Map_pix_Edit/res/choose.png";
    Button* chooseNewColorBtn = new Button(str0,str0,str0);
    chooseNewColorBtn->setStyleSheet("border:1px solid #d1d1d1;");
    currentColorBtn = new QToolButton();
    btnGroup = new QGroupBox;
    chosenColorGroup = new QGroupBox;

    //connect(chooseNewColorBtn,SIGNAL(clicked(bool)),this,SLOT(colorDialog()));
    /*
    QString str[]  =   {"border:1px solid #d1d1d1;background-color:rgb(255,50,50);",
                        "border:1px solid #d1d1d1;background-color:rgb(255,125,50);",
                        "border:1px solid #d1d1d1;background-color:rgb(255,50,255);",
                        "border:1px solid #d1d1d1;background-color:rgb(255,255,50);",
                        "border:1px solid #d1d1d1;background-color:rgb(50,255,50);",
                        "border:1px solid #d1d1d1;background-color:rgb(50,50,255);",
                        "border:1px solid #d1d1d1;background-color:rgb(50,255,255);",
                        "border:1px solid #d1d1d1;background-color:rgb(255,255,255);",
                        "border:1px solid #d1d1d1;background-color:rgb(50,50,50);",
                        "border:1px solid #d1d1d1;background-color:rgb(156,156,156);"};
    */
    QString str[]  =   {"border:1px solid #d1d1d1;border-image:url(I:/DL/Map_pix_Edit/res/desert.png);",
                        "border:1px solid #d1d1d1;border-image:url(I:/DL/Map_pix_Edit/res/forest.png);",
                        "border:1px solid #d1d1d1;border-image:url(I:/DL/Map_pix_Edit/res/ice.png);",
                        "border:1px solid #d1d1d1;border-image:url(I:/DL/Map_pix_Edit/res/river.png);",
                        "border:1px solid #d1d1d1;border-image:url(I:/DL/Map_pix_Edit/res/graytank.png);",
                        "border:1px solid #d1d1d1;border-image:url(I:/DL/Map_pix_Edit/res/greentank.png);",
                        "border:1px solid #d1d1d1;border-image:url(I:/DL/Map_pix_Edit/res/redtank.png);",
                        "border:1px solid #d1d1d1;border-image:url(I:/DL/Map_pix_Edit/res/yellowtank.png);",
                        "border:1px solid #d1d1d1;border-image:url(I:/DL/Map_pix_Edit/res/desert.png);",
                        "border:1px solid #d1d1d1;border-image:url(I:/DL/Map_pix_Edit/res/desert.png);"};

    QString Pngstr[] = {"I:/DL/Map_pix_Edit/res/desert.png",
                        "I:/DL/Map_pix_Edit/res/forest.png",
                        "I:/DL/Map_pix_Edit/res/ice.png",
                        "I:/DL/Map_pix_Edit/res/river.png",
                        "I:/DL/Map_pix_Edit/res/graytank.png",
                        "I:/DL/Map_pix_Edit/res/greentank.png",
                        "I:/DL/Map_pix_Edit/res/redtank.png",
                        "I:/DL/Map_pix_Edit/res/yellowtank.png",
                        "I:/DL/Map_pix_Edit/res/desert.png",
                        "I:/DL/Map_pix_Edit/res/desert.png"};

    for(int i=0;i<10;i++){
        style[i] = str[i];
        pngstyle[i] = Pngstr[i];
        signalMapper[i] = new QSignalMapper();
        colorBtn[i] = new QToolButton();
        colorBtn[i]->setStyleSheet(style[i]);
        connect(colorBtn[i],SIGNAL(clicked()),signalMapper[i],SLOT(map()));
        signalMapper[i]->setMapping(colorBtn[i],i);
        connect(signalMapper[i],SIGNAL(mapped(int)),this,SLOT(changeColor(int)));
        glayout->addWidget(colorBtn[i],i/2,i%2);
    }

    currentColorBtn->setStyleSheet(style[0]);
    glayout1->addWidget(currentColorBtn,0,0,1,1);
    glayout1->addWidget(chooseNewColorBtn,0,1,1,1);
    chosenColorGroup->setLayout(glayout1);
    btnGroup->setLayout(glayout);
    vlayout->addWidget(chosenColorGroup);
    vlayout->addWidget(btnGroup);
    vlayout->addStretch();
    setLayout(vlayout);
    setMaximumWidth(100);
}

void colorWindow::changeColor(int id)
{
    int num[10][3] = {
        255,50,50,255,125,50,255,50,255,255,255,50,50,255,50,50,50,255,50,255,255,
        255,255,255,50,50,50,156,156,156
    };
    currentColorBtn->setStyleSheet(style[id]);
    paintWindow::stylestr = pngstyle[id];
}
