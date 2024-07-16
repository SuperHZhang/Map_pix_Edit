#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H
#include<QWidget>
class QButtonGroup;
class QPushButton;
class QRadioButton;
class QLineEdit;
class QLabel;
class saveDialog : public QWidget
{
    Q_OBJECT
private:
    QButtonGroup* radioGroup;
    QRadioButton* radio1;
    QRadioButton* radio2;
    QRadioButton* radio3;
    QPushButton* okBtn;
    QPushButton* cancelBtn;
public:
    saveDialog(QWidget* parent = 0);
private slots:
    void saveFile();
signals:
    void save(int);
};
#endif // SAVEDIALOG_H
