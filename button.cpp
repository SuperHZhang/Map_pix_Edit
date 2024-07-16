#include"button.h"
#include<QPixmap>

Button::Button(QWidget *parent)
: QToolButton(parent)
{
    setDown(false);
    setFocusPolicy(Qt::NoFocus);
}

Button::Button(QString &str1,QString &str2,QString &str3)
{
    QPixmap img1,img2,img3;
    img1.load(str1);
    img2.load(str2);
    img3.load(str3);
    setFixedSize(img1.width()/4*3,img1.height()/4*3);
    SetButtonIcons(img1,img2,img3);
    setStyleSheet("border:0px 0px 0px 0px;");
    setIconSize(QSize(img1.width()/4*3,img1.height()/4*3));
}

Button::~Button()
{

}

void Button::setPressImg()
{
    setIcon(m_PressedIcon);
}

void Button::setReleaseImg()
{
    setIcon(m_NormalIcon);
}

void Button::SetButtonIcons(const QIcon &normal,
    const QIcon &focus, const QIcon &pressed)
{
    m_NormalIcon = normal;
    m_FocusIcon = focus;
    m_PressedIcon = pressed;
    setIcon(m_NormalIcon);
}
