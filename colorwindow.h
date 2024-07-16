#ifndef COLORWINDOW_H
#define COLORWINDOW_H
#include<QWidget>
#include<QToolButton>
class QGroupBox;
class colorWindow:public QWidget
{
    Q_OBJECT
private:
    int chosenId;
    QToolButton* currentColorBtn;
    QString style[10];
    QString pngstyle[10];
    QToolButton* colorBtn[10];
    QGroupBox *btnGroup;
    QGroupBox *chosenColorGroup;
public:
    colorWindow(QWidget* parent = 0);
private slots:
    void changeColor(int);
};


#endif // COLORWINDOW_H
