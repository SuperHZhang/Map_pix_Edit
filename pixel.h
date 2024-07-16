#ifndef PIXEL_H
#define PIXEL_H

#include <QObject>
#include "button.h"
#include "paint.h"
#include "colorwindow.h"
class Button;
class QWidget;
class QHBoxLayout;
class QVBoxLayout;
class QImage;
class QMenu;
class QMenuBar;
class QAction;
class QToolBar;
class QGroupBox;
class QPixmap;
class QPushButton;
class QPicture;
class QMainWindow;
class QDockWidget;
class pixel : public QObject
{
    Q_OBJECT

private:
    QString filename;

    //主窗口
    QMainWindow* mainWindow;
    QWidget* window;
    //菜单栏
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* showMenu;
    QImage* img;
    QMenuBar* menuBar;
    QAction* actionNew;
    QAction* actionSave;
    QAction* actionOpen;
    QAction* actionUndo;
    QAction* actionRedo;
    QAction* actionShowGrid;

    //工具栏

    QToolBar* toolBar;
    QAction* newTool;
    QAction* saveTool;

    //左边的状态栏
    QWidget* leftWidget;
    Button*leftToolBar;
    Button* drawRectBtn;
    Button* drawPixelBtn;
    Button* colorBtn;
    Button* drawFullRectBtn;
    Button* drawLineBtn;
    Button* drawCircleBtn;
    Button* drawFullCircleBtn;
    Button* eraseBtn;
    Button* getColorBtn;
    void setLeftTool();

    //画板
    paintWindow* paint;
    //颜色
    colorWindow* color;

    //图像显示
    QDockWidget* dock1;

    void setLayout();
    void createMenu();
    void createTool();
    void createPixmap();
    void createColorGroup();
    void updateIcon(int);
    Button *createButton(QString &str1,QString &str2,QString &str3);
public:
    pixel(QObject *parent = 0);
    ~pixel();
public slots:
    bool save();
    void open();
    void undo();
    void redo();
    void drawRect();
    void fillColor();
    void drawPixel();
    void drawFullRect();
    void drawLine();
    void drawCircle();
    void drawFullCircle();
    void erase();
    void showGrid();
    void newFile();
    void updateImg();
    void getColor();
    void saveImg(int);
};

#endif // PIXEL_H
