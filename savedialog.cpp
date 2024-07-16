#include"savedialog.h"
#include<QRadioButton>
#include<QGroupBox>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QButtonGroup>
#include<QLineEdit>
#include<QLabel>
#include<QMessageBox>

saveDialog::saveDialog(QWidget* parent):QWidget(parent)
{
    QVBoxLayout* vlayout = new QVBoxLayout;
    QHBoxLayout* hlayout = new QHBoxLayout;

    okBtn = new QPushButton(QStringLiteral("确定"));
    cancelBtn = new QPushButton(QStringLiteral("取消"));

    radioGroup = new QButtonGroup();
    radio1 = new QRadioButton(QStringLiteral("原始大小(1x1)"),this);
    radio2 = new QRadioButton(QStringLiteral("4倍大小(2x2)"),this);
    radio3 = new QRadioButton(QStringLiteral("9倍大小(3x3)"),this);

    radio1->setChecked(true);
    radioGroup->addButton(radio1,1);
    radioGroup->addButton(radio2,2);
    radioGroup->addButton(radio3,3);

    hlayout->addWidget(okBtn);
    hlayout->addWidget(cancelBtn);

    vlayout->addWidget(radio1);
    vlayout->addWidget(radio2);
    vlayout->addWidget(radio3);
    vlayout->addLayout(hlayout);

    connect(okBtn,SIGNAL(clicked()),this,SLOT(saveFile()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));

    setLayout(vlayout);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(QStringLiteral("保存设置"));
}

void saveDialog::saveFile()
{
    emit(save(radioGroup->checkedId()));
    close();
}
