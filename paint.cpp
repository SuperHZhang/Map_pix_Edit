#include"paint.h"
#include<QPainter>
#include<QApplication>
#include<QLabel>

QString paintWindow::stylestr = "";

point::point(QString style,int i,int j,QString styleIn):
    x(i),y(j) {
    s = style;
    s_in = styleIn;
}

bool operator <(const point& a,const point& b)
{
    return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

bool operator ==(const point& a,const point& b)
{
    return a.x==b.x&&a.y==b.y;
}

point::point(){ }

paintWindow::paintWindow(QWidget *parent):
    QWidget(parent)
{
    setLayout(32,32);
}

void paintWindow::setLayout(int x,int y)
{
    XMAX = x;
    YMAX = y;
    margin = 10;
    if(x<50&&y<50)
        size = 10;
    else if(x<100&&y<100)
        size =8;
    else if(y<150&&y<150)
        size = 6;


    //img = new QImage(XMAX,YMAX,QImage::Format_ARGB32);
    //img->fill(QColor(0,0,0,0));
    //picture = new QLabel;
    //picture->setPixmap(QPixmap::fromImage(*img));
    state = DRAWPIXEL;
    isRelease = true;
    isShowGrid = false;
    setMouseTracking(true);
    setMinimumWidth(XMAX*size+2*margin);
    setMinimumHeight(YMAX*size+2*margin);
}

void paintWindow::changeSize(int x,int y)
{
    delete img;   
    delete picture;
    setLayout(x,y);
    emit(changeImg());
}

void paintWindow::newImage(QImage* image)
{
    delete picture;
    setLayout(image->width(),image->height());   
    update();
}

paintWindow::~paintWindow()
{

}

void paintWindow::drawOnScreenPixel()
{
    QPainter paint(this);
    //paint.setPen(Qt::NoPen);
    std::set<point>::iterator it;
    for(it=currentPressPoint.begin();it!=currentPressPoint.end();it++)
    {
        if(it->x>=0&&it->y>=0 && it->x<XMAX && it->y<YMAX)
        {
            if(it->s_in!= "")
            {
                QPixmap objPixmap;
                objPixmap.load(it->s);//加载图片
                if(objPixmap.isNull()){
                    return;
                }
                objPixmap.scaled(size,size);
                paint.setCompositionMode(QPainter::CompositionMode_Source);
                paint.drawPixmap(it->x*size+margin,it->y*size+margin,size,size,objPixmap);
                paint.setCompositionMode(QPainter::CompositionMode_SourceOver);
                objPixmap.load(it->s_in);//加载图片
                paint.drawPixmap(it->x*size+margin,it->y*size+margin,size,size,objPixmap);
            }
            else
            {
                //paint.setBrush(c);
                QPixmap objPixmap;
                objPixmap.load(it->s);//加载图片
                if(objPixmap.isNull()){
                    return;
                }
                objPixmap.scaled(size,size);
                paint.drawPixmap(it->x*size+margin,it->y*size+margin,size,size,objPixmap);
            }
        }
    }
}

void paintWindow::drawTmpPixel()
{
    QPainter paint(this);
    paint.setPen(Qt::NoPen);
    std::set<point>::iterator it;
    for(it=currentPoint.begin();it!=currentPoint.end();it++)
    {
        if(it->x>=0&&it->y>=0 && it->x<XMAX && it->y<YMAX)
        {
            //paint.setBrush(c);
            QPixmap objPixmap;
            objPixmap.load(stylestr);//加载图片
            if(objPixmap.isNull()){
                return;
            }
            objPixmap.scaled(size,size);
            paint.drawPixmap(it->x*size+margin,it->y*size+margin,size,size,objPixmap);
        }
    }
}

void paintWindow::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    for(int i=0;i<XMAX;i++){
        for(int j=0;j<YMAX;j++){
            paint.setPen(Qt::NoPen);
            paint.setBrush(QColor(222,222,222));
            paint.drawRect(size*i+margin, size*j+margin, size/2, size/2);
            paint.drawRect(size*i + size/2+margin, size*j+size/2+margin, size/2, size/2);
            paint.setBrush(QColor(255,255,255));
            paint.drawRect(size*i+size/2+margin, size*j+margin, size/2, size/2);
            paint.drawRect(size*i+margin, size*j+size/2+margin, size/2, size/2);
            if(isShowGrid)
            {
                paint.setPen(QColor(200,200,200));
                paint.setBrush(QColor(0,0,0,0));
                paint.drawRect(size*i+margin, size*j+margin, size, size);
            }
        }
    }
    if(state==ERASE){
        paint.setPen(Qt::NoPen);
        std::set<point>::iterator it;
        for(it=currentPoint.begin();it!=currentPoint.end();it++)
        {
            {
                QPixmap objPixmap;
                objPixmap.load(stylestr);//加载图片
                if(objPixmap.isNull())
                {
                    return;
                }
                objPixmap.scaled(size,size);
                paint.drawPixmap(it->x*size+margin,it->y*size+margin,size,size,objPixmap);
            }
        }
    }
    else{
        drawOnScreenPixel();
        drawTmpPixel();
    }
}

void paintWindow::updateImage()
{
    /*
    for(int i=0;i<XMAX;i++){
        for(int j=0;j<YMAX;j++){
            img->setPixelColor(i,j,map[i][j]);
        }
    }

    picture->setPixmap(QPixmap::fromImage(*img));
    */
}

void paintWindow::mouseMoveEvent(QMouseEvent *event)
{
    int j = (event->pos().y()-margin)/size;
    int i = (event->pos().x()-margin)/size;
    static int x1, y1;
    static int x2, y2;
    currentPoint.clear();
    if(event->pos().y()-margin<0||event->pos().x()-margin<0){
        update();
        return;
    }
    switch(state){
    case DRAWRECT:
        if(event->buttons()&Qt::LeftButton){
            if(isRelease){
                isRelease = false;
                x1 = i;
                y1 = j;
            }
            x2 = i;
            y2 = j;
            int minX = min(x1,x2);
            int minY = min(y1,y2);
            int maxX = max(x1,x2);
            int maxY = max(y1,y2);
            for(int k=minX;k<=maxX;k++){
                currentPoint.insert(point(stylestr,k,minY));
                currentPoint.insert(point(stylestr,k,maxY));
            }
            for(int k=minY+1;k<=maxY-1;k++){
                currentPoint.insert(point(stylestr,minX,k));
                currentPoint.insert(point(stylestr,maxX,k));
            }
        }
        break;
    case DRAWPIXEL:
        currentPoint.insert(point(stylestr,i,j));
        break;
    case DRAWFULLRECT:
        if(event->buttons()&Qt::LeftButton){
            if(isRelease){
                isRelease = false;
                x1 = i;
                y1 = j;
            }
            x2 = i;
            y2 = j;
            int minX = min(x1,x2);
            int minY = min(y1,y2);
            int maxX = max(x1,x2);
            int maxY = max(y1,y2);
            for(int k=minX;k<=maxX;k++){
                for(int t=minY;t<=maxY;t++){
                    currentPoint.insert(point(stylestr,k,t));
                }
            }
        }
        break;
    case DRAWLINE:
        if(event->buttons()&Qt::LeftButton){
            if(isRelease){
                isRelease = false;
                x1 = i;
                y1 = j;
            }
            x2 = i;
            y2 = j;
            bresenhamLine(x1,y1,x2,y2);
        }
        break;
    case DRAWCIRCLE:
        if(event->buttons()&Qt::LeftButton){
            if(isRelease){
                isRelease = false;
                x1 = i;
                y1 = j;
            }
            x2 = i;
            y2 = j;
            bresenhamCircle(x1,y1,abs(x2-x1));
        }
        break;
    case DRAWFULLCIRCLE:
        if(event->buttons()&Qt::LeftButton){
            if(isRelease){
                isRelease = false;
                x1 = i;
                y1 = j;
            }
            x2 = i;
            y2 = j;
            bresenhamFullCircle(x1,y1,abs(x2-x1));
        }
        break;
    case ERASE:
        QString str  = "I:/DL/Map_pix_Edit/res/background.png";
        currentPoint.insert(point(str,i,j));
        break;
    };
    update();
}

void paintWindow::mousePressEvent(QMouseEvent *event)
{
    static int count = 0;
    int j = (event->pos().y()-margin)/size;
    int i = (event->pos().x()-margin)/size;
    switch(state){
    case DRAWPIXEL:
        if(i>=0&&i<XMAX&&j>=0&&j<YMAX){
            std::set<point>::iterator it;
            for(it=currentPoint.begin();it!=currentPoint.end();it++)
            {
                if(it->x == i && it->y == j &&it->s != "")//如果不是空白区域
                {
                    currentPressPoint.erase(point(it->s,i,j));
                    currentPressPoint.insert(point(it->s,i,j,stylestr));
                }
                else//如果是空白区域
                {
                    currentPressPoint.insert(point(stylestr,i,j));
                }
            }
            update();
        }
        break;
    case FILLCOLOR:
        if(i>=0&&i<XMAX&&j>=0&&j<YMAX){
            //updateMap();
            seedFilling(i,j);
            update();
        }
        break;
    case GETCOLOR:
        if(i>=0&&i<XMAX&&j>=0&&j<YMAX){
            //emit(changeColor(map[i][j]));
        }
    }
}

void paintWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isRelease = true;
    std::set<point>::iterator it;
    switch(state){
    case ERASE:
        updateMap();       
        currentPoint.clear();
        currentPressPoint.clear();
        update();
        break;
    case DRAWRECT:
    case DRAWFULLRECT:
    case DRAWLINE:
    case DRAWCIRCLE:
    case DRAWFULLCIRCLE:
        updateMap();
        currentPoint.clear();
        currentPressPoint.clear();
        update();
        break;
    }
    updateImage();
}

void paintWindow::bresenhamLine(int x1,int y1,int x2,int y2)
{
    if(abs(x2-x1)<abs(y2-y1)){
        bresenhamLine(y1,x1,y2,x2,false);
    }
    else{
        bresenhamLine(x1,y1,x2,y2,true);
    }
}

void paintWindow::bresenhamLine(int x1,int y1,int x2,int y2,bool isDxBigger)
{
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int d = 2*dy - dx;
    for(int cx=x1,cy=y1;cx!=x2;cx+=(x2-x1>0?1:-1)){
        if(d<0){
            d += dy*2;
        }
        else{
            cy += (y2-y1)>0?1:-1;
            d += (dy - dx)*2;
        }
        if(isDxBigger)currentPoint.insert(point(stylestr,cx,cy));
        else currentPoint.insert(point(stylestr,cy,cx));
    }
    if(isDxBigger){
        currentPoint.insert(point(stylestr,x1,y1));
        currentPoint.insert(point(stylestr,x2,y2));
    }
    else{
        currentPoint.insert(point(stylestr,y1,x1));
        currentPoint.insert(point(stylestr,y2,x2));
    }
}

void paintWindow::bresenhamCircle(int xc,int yc,int r)
{
    int x = 0,y = r,p = 3 - 2*3;
    while(x<y){
        bresenhamCircle(xc,yc,x,y);
        if(p<0)p = p + 4*x + 6;
        else{
            p = p + 4*(x-y)+10;
            y--;
        }
        x++;
    }
    if(x==y){
        bresenhamCircle(xc,yc,x,y);
    }
}

void paintWindow::bresenhamFullCircle(int xc,int yc,int r)
{
    int x = 0,y = r,p = 3 - 2*3;
    while(x<y){
        for(int i=x;i<=y;i++){
            bresenhamCircle(xc,yc,x,i);
        }
        if(p<0)p = p + 4*x + 6;
        else{
            p = p + 4*(x-y)+10;
            y--;
        }
        x++;
    }
    if(x==y){
        bresenhamCircle(xc,yc,x,y);
    }
}


void paintWindow::bresenhamCircle(int xc,int yc,int x,int y)
{
    if(xc+x<XMAX&&yc+y<YMAX)currentPoint.insert(point(stylestr,xc+x,yc+y));
    if(xc-x>=0&&yc+y<YMAX)currentPoint.insert(point(stylestr,xc-x,yc+y));
    if(xc+x<XMAX&&yc-y>=0)currentPoint.insert(point(stylestr,xc+x,yc-y));
    if(xc-x>=0&&yc-y>=0)currentPoint.insert(point(stylestr,xc-x,yc-y));
    if(xc+y<XMAX&&yc+x<YMAX)currentPoint.insert(point(stylestr,xc+y,yc+x));
    if(xc-y>=0&&yc+x<YMAX)currentPoint.insert(point(stylestr,xc-y,yc+x));
    if(xc+y<XMAX&&yc-x>=0)currentPoint.insert(point(stylestr,xc+y,yc-x));
    if(xc-y>=0&&yc-x>=0)currentPoint.insert(point(stylestr,xc-y,yc-x));
}


QColor paintWindow::mixColor(const QColor& x,const QColor& y)
{
    float a1 = 1.0f*x.alpha()/255;
    float a2 = 1.0f*y.alpha()/255;
    int r,g,b,a;
    r = x.red()*a1*(1-a2)+y.red()*a2/(a1+a2-a1*a2);
    g = x.green()*a1*(1-a2)+y.green()*a2/(a1+a2-a1*a2);
    b = x.blue()*a1*(1-a2)+y.blue()*a2/(a1+a2-a1*a2);
    a = (1-(1-a1)*(1-a2))*255;
    return QColor(r,g,b,a);
}

void paintWindow::updateMap()
{
    /*
    for(int i=0;i<XMAX;i++)
    {
        for(int j=0;j<YMAX;j++)
        {
            map[i][j][(layer+1)%TIMES] = map[i][j][layer];
        }
    }
    layer = (layer+1)%TIMES;
    rear = layer;
    if(rear==front)front = (front+1)%TIMES;
    */
}

void paintWindow::seedFilling(int i,int j)
{
    int dx[] = {0,1,0,-1};
    int dy[] = {1,0,-1,0};

    for(int k=0;k<4;k++)
    {
        int x = i + dx[k];
        int y = j + dy[k];
        if(x<XMAX&&x>=0&&y<YMAX&&y>=0)
        {
            seedFilling(x,y);
        }
    }
}

void paintWindow::undo()
{
    /*
    if(layer!=front){
        layer = (layer+TIMES-1)%TIMES;
        update();
        updateImage();
    }
    */
}

void paintWindow::redo()
{
    /*
    if(layer!=rear){
        layer = (layer+1)%TIMES;
        update();
        updateImage();
    }
    */
}

void paintWindow::drawRect()
{
    state = DRAWRECT;
}

void paintWindow::drawPixel()
{
    state = DRAWPIXEL;
}

void paintWindow::fillColor()
{
    state = FILLCOLOR;
}

void paintWindow::drawFullRect()
{
    state = DRAWFULLRECT;
}

void paintWindow::drawLine()
{
    state = DRAWLINE;
}

void paintWindow::drawCircle()
{
    state = DRAWCIRCLE;
}

void paintWindow::drawFullCircle()
{
    state = DRAWFULLCIRCLE;
}

void paintWindow::erase()
{
    state = ERASE;
}

void paintWindow::getColor()
{
    state  = GETCOLOR;
}

void paintWindow::showGrid()
{
    isShowGrid==true?isShowGrid=false:isShowGrid=true;
    update();
}

QLabel* paintWindow::getImage()
{
    return NULL;
}

void paintWindow::saveImage(const QString &fileName,int s)
{
    /*
    QImage* img1;

    if(s==1){
        updateImage();
        img->save(fileName);
    }
    else if(s==2){
         img1 = new QImage(XMAX*2,YMAX*2,QImage::Format_ARGB32);
         for(int i=0;i<XMAX;i++){
             for(int j=0;j<YMAX;j++){
                 img1->setPixelColor(2*i,2*j,map[i][j][layer]);
                 img1->setPixelColor(2*i+1,2*j,map[i][j][layer]);
                 img1->setPixelColor(2*i,2*j+1,map[i][j][layer]);
                 img1->setPixelColor(2*i+1,2*j+1,map[i][j][layer]);
             }
         }
         img1->save(fileName);
    }
    else if(s==3){
        img1 = new QImage(XMAX*3,YMAX*3,QImage::Format_ARGB32);
        for(int i=0;i<XMAX;i++){
            for(int j=0;j<YMAX;j++){
                img1->setPixelColor(3*i,3*j,map[i][j][layer]);
                img1->setPixelColor(3*i+1,3*j,map[i][j][layer]);
                img1->setPixelColor(3*i,3*j+1,map[i][j][layer]);
                img1->setPixelColor(3*i+1,3*j+1,map[i][j][layer]);

                img1->setPixelColor(3*i+2,3*j,map[i][j][layer]);
                img1->setPixelColor(3*i+2,3*j+1,map[i][j][layer]);
                img1->setPixelColor(3*i+1,3*j+2,map[i][j][layer]);
                img1->setPixelColor(3*i,3*j+2,map[i][j][layer]);

                img1->setPixelColor(3*i+2,3*j+2,map[i][j][layer]);
            }
        }
        img1->save(fileName);
    }
    */
}
