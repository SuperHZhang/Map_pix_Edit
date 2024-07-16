#ifndef NEWDIALOG_H
#define NEWDIALOG_H
#include<QWidget>
class QButtonGroup;
class QPushButton;
class QRadioButton;
class QLineEdit;
class QLabel;
class newDialog : public QWidget
{
    Q_OBJECT
private:
    QButtonGroup* radioGroup;
    QRadioButton* radio16;
    QRadioButton* radio32;
    QRadioButton* radio48;
    QRadioButton* radio64;
    QRadioButton* radioRandom;
    QPushButton* okBtn;
    QPushButton* cancelBtn;
    QLineEdit* startEdit;
    QLineEdit* finishEdit;
    QLabel* label1;
    QLabel* label2;
public:
    newDialog(QWidget* parent = 0);
private slots:
    void newFile();
    void radioChange();
signals:
    void sendIndex(int,int);
};

#endif // NEWDIALOG_H
