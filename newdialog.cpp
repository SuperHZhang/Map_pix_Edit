#include"newdialog.h"
#include<QRadioButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QButtonGroup>
#include<QLineEdit>
#include<QLabel>
#include<QMessageBox>

newDialog::newDialog(QWidget* parent):QWidget(parent)
{
    QVBoxLayout* vlayout = new QVBoxLayout;
    QVBoxLayout* vlayout1 = new QVBoxLayout;
    QHBoxLayout* hlayout = new QHBoxLayout;
    QHBoxLayout* hlayout1 = new QHBoxLayout;
    startEdit = new QLineEdit();
    finishEdit = new QLineEdit();
    label1 = new QLabel(QStringLiteral("宽度："));
    label2 = new QLabel(QStringLiteral("高度："));


    startEdit->setEnabled(false);
    finishEdit->setEnabled(false);
    okBtn = new QPushButton(QStringLiteral("确定"));
    cancelBtn = new QPushButton(QStringLiteral("取消"));

    radioGroup = new QButtonGroup();
    radio16 = new QRadioButton("16x16",this);
    radio32 = new QRadioButton("32x32",this);
    radio48 = new QRadioButton("48x48",this);
    radio64 = new QRadioButton("64x64",this);
    radioRandom = new QRadioButton(QStringLiteral("自定义"),this);

    radio32->setChecked(true);
    radioGroup->addButton(radio16,1);
    radioGroup->addButton(radio32,2);
    radioGroup->addButton(radio48,3);
    radioGroup->addButton(radio64,4);
    radioGroup->addButton(radioRandom,5);

    vlayout1->addWidget(radio16);
    vlayout1->addWidget(radio32);
    vlayout1->addWidget(radio48);
    vlayout1->addWidget(radio64);
    vlayout1->addWidget(radioRandom);

    hlayout1->addLayout(vlayout1);
    hlayout1->addWidget(label1);
    hlayout1->addWidget(startEdit);
    hlayout1->addWidget(label2);
    hlayout1->addWidget(finishEdit);

    hlayout->addWidget(okBtn);
    hlayout->addWidget(cancelBtn);

    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout);

    connect(radio16, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(radio32, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(radio48, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(radio64, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(radioRandom, SIGNAL(clicked(bool)), this, SLOT(radioChange()));

    connect(okBtn,SIGNAL(clicked()),this,SLOT(newFile()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));

    setLayout(vlayout);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(QStringLiteral("新建"));
}

void newDialog::radioChange()
{
    int id = radioGroup->checkedId();
    if(id==5){
        startEdit->setEnabled(true);
        finishEdit->setEnabled(true);
    }
    else{
        startEdit->setEnabled(false);
        finishEdit->setEnabled(false);
    }
}

void newDialog::newFile()
{
    int id = radioGroup->checkedId();
    if(id>=1&&id<=4){
        int num = id*16;
        emit(sendIndex(num,num));
    }
    else{
        int num1 = startEdit->text().toInt();
        int num2 = finishEdit->text().toInt();
        if(num1<150&&num2<150&&num1>0&&num2>0){
            emit(sendIndex(num1,num2));
        }
        else{
            QMessageBox msg(QMessageBox::Warning, "warning", QStringLiteral("指定大小超过限制/不符规范"),
                                 QMessageBox::Yes, NULL);
            msg.exec();
        }
    }
    close();
}
