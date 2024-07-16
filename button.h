#ifndef BUTTON
#define BUTTON
#include<QToolButton>

class Button : public QToolButton
{
    Q_OBJECT
private:
    QIcon m_NormalIcon;
    QIcon m_FocusIcon;
    QIcon m_PressedIcon;
protected:
public:

    void setPressImg();
    void setReleaseImg();
    Button(QWidget *parent = 0);
    Button(QString &str1,QString &str2,QString &str3);
    virtual ~Button();
    void SetButtonIcons(const QIcon &normal,
        const QIcon &focus = QIcon(),
        const QIcon &pressed = QIcon() );
};

#endif // BUTTON
