#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent):
QWidget(parent)
{

// this->setStyleSheet("TitleBar{margin:0 1px;border:1px solid #ccc;border-width:0 1px 0 1px}");
          minimize = new QToolButton(this);

          minimize->setObjectName("minimize");
          minimize->setToolTip("最小化");
          maximize = new QToolButton(this);
          maximize->setObjectName("maximize");
          close= new QToolButton(this);
          close->setObjectName("closebtn");

         minimize->setToolTip("最小化");
          maximize->setToolTip("最大化");
           close->setToolTip("关闭");
          QIcon icon_cls;
              icon_cls.addFile(":/base/close.png", QSize(), QIcon::Normal, QIcon::Off);	// Normal
              icon_cls.addFile(":/base/close.png", QSize(), QIcon::Active, QIcon::Off);	//rollover
              icon_cls.addFile(":/base/close.png", QSize(), QIcon::Active, QIcon::On);		//pushed/On
              //disabled is already implemented
           close->setIcon(icon_cls);

           QIcon icon_max;
               icon_max.addFile(":/base/max.png", QSize(), QIcon::Normal, QIcon::Off);	// Normal
               icon_max.addFile(":/base/max.png", QSize(), QIcon::Active, QIcon::Off);	//rollover
               icon_max.addFile(":/base/max.png", QSize(), QIcon::Active, QIcon::On);		//pushed/On
               //disabled is already implemented
            maximize->setIcon(icon_max);

            QIcon icon_min;
                icon_min.addFile(":/base/min.png", QSize(), QIcon::Normal, QIcon::Off);	// Normal
                icon_min.addFile(":/base/min.png", QSize(), QIcon::Active, QIcon::Off);	//rollover
                icon_min.addFile(":/base/min.png", QSize(), QIcon::Active, QIcon::On);		//pushed/On
                //disabled is already implemented
             minimize->setIcon(icon_min);

         minimize->setAutoRaise(true);
         maximize->setAutoRaise(true);
         close->setAutoRaise(true);
         QString s1;
         s1="margin-top:1px;background-color:transparent;";
         QString s2;
         s2="border:1px solid rgb(119,213,252);border-bottom:none;background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(37, 184, 241,255), stop:1 rgba(79, 192,240, 0));";
         minimize->setStyleSheet(QString("#minimize:enabled{%1}").arg(s1)+QString("QToolButton#minimize:hover{%1}").arg(s2));
         maximize->setStyleSheet(QString("#maximize:enabled{%1}").arg(s1)+QString("QToolButton#maximize:hover{%1}").arg(s2));
//         this->setStyleSheet(slt2.arg(s2)+slt1.arg(s1));
         close->setStyleSheet("#closebtn:enabled{margin-top:1px;border-top-right-radius:3px;background:transparent;}");
         close->setStyleSheet("QToolButton#closebtn:hover{margin-top:1px;border-top-right-radius:3px;border:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(209, 4, 4), stop:1 rgba(232, 10, 10,0));border-bottom:none;background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(209, 4, 4), stop:1 rgba(232, 10, 10,0));}");

        minimize->setMinimumHeight(20);
        maximize->setMinimumHeight(20);
        close->setMinimumHeight(20);

        minimize->setMinimumWidth(28);
        maximize->setMinimumWidth(28);

        close->setMinimumWidth(32);
        con=new QToolButton(this);
        con->setIcon(QIcon(":/base/icon"));
        con->setAutoRaise(true);
        con->setStyleSheet("background:none;border:none;margin-left:2px;");

        QLabel *label = new QLabel(this);
        label->setText("WinStorm");
        parent->setWindowTitle("WinStorm");
        parent->setWindowIcon(QIcon(":base/icon"));
        label->setStyleSheet("margin-left:5px;");
        QHBoxLayout *hbox = new QHBoxLayout(this);

        QFrame* line1=new QFrame(this);
        line1->setObjectName("line1");
        line1->setLineWidth(0);
        line1->setFrameShape(QFrame::VLine);
        line1->setMidLineWidth(0);
        line1->setFrameShadow(QFrame::Plain);
        QLinearGradient gradient(0, 0, 1, 30);
        gradient.setColorAt(0, QColor(115, 167, 191));

        gradient.setColorAt(1, QColor(126, 190,227));

        QPalette palette;
        palette.setBrush(line1->backgroundRole(), QBrush(gradient));
        line1->setPalette(palette);
        QString normal;
        normal="margin-top:1px;border:none;background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(115, 167, 191,255), stop:1 rgba(126, 190,227, 125));";
        QString hover;
        hover="background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(74, 122, 146,255), stop:1 rgba(126, 190,227, 0));";
        line1->setStyleSheet(QString("#line1{%1}").arg(normal));

        QFrame* line2=new QFrame(this);
        line2->setObjectName("line2");

        line2->setStyleSheet(QString("#line2{%1}").arg(normal));
        line2->setLineWidth(0);
        line2->setFrameShape(QFrame::VLine);
        line2->setMidLineWidth(0);
        line2->setFrameShadow(QFrame::Plain);
        QFrame* line3=new QFrame(this);
        line3->setObjectName("line3");
        line3->setLineWidth(0);
        line3->setFrameShape(QFrame::VLine);
        line3->setFrameShadow(QFrame::Plain);
        line3->setMidLineWidth(0);
        line3->setStyleSheet(QString("#line3{%1}").arg(normal));
        line1->setFixedWidth(1);
        line2->setFixedWidth(1);
        line3->setFixedWidth(1);
        hbox->addWidget(con);
        hbox->addWidget(label);
        hbox->addWidget(line1);
        hbox->addWidget(minimize);
        hbox->addWidget(line2);
        hbox->addWidget(maximize);
        hbox->addWidget(line3);
        hbox->addWidget(close);
        hbox->setMargin(0);
        hbox->setSpacing(0);
        hbox->setContentsMargins(0,0,0,0);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        maxNormal = false;
        connect(con,SIGNAL(clicked()),this,SLOT(icon_Clicked()));
        connect(close, SIGNAL( clicked() ), parent, SLOT(close() ) );
        connect(minimize, SIGNAL( clicked() ), this, SLOT(showSmall() ) );
        connect(maximize, SIGNAL( clicked() ), this, SLOT(showMaxRestore() ) );
        delayTimer = new QTimer( this );
        connect( delayTimer, SIGNAL( timeout() ), this, SLOT( handleSingleClick() ) );
}
void TitleBar::showSmall()
{
    nativeParentWidget()->showMinimized();
}

void TitleBar::showMaxRestore()
{
    if (maxNormal) {
        nativeParentWidget()->showNormal();
        maxNormal = !maxNormal;
//        maximize->setIcon(maxPix);
    } else {
        nativeParentWidget()->showMaximized();
        maxNormal = !maxNormal;
//        maximize->setIcon(restorePix);
    }
}
void TitleBar::handleSingleClick()
{

    if(count==4){
       this->mouseDoubleClickEvent();
    }else{
         count=0;
    }

}
void TitleBar::mouseDoubleClickEvent()
{
    delayTimer->stop();
    count=0;
    if (maxNormal) {
        nativeParentWidget()->showNormal();
        maxNormal = !maxNormal;
//        maximize->setIcon(maxPix);
    } else {
        nativeParentWidget()->showMaximized();
        maxNormal = !maxNormal;
//        maximize->setIcon(restorePix);
    }

}

void TitleBar::mousePressEvent(QMouseEvent *e)
{
    delayTimer->start(200);
    count+=1;
    startPos = e->globalPos();
    clickPos = mapToParent(e->pos());
//    this->setCursor(Qt::OpenHandCursor);

}
void TitleBar::mouseMoveEvent(QMouseEvent *e)
{
    if (maxNormal)
        return;
//    this->setCursor(Qt::ClosedHandCursor);
    nativeParentWidget()->move(e->globalPos() - clickPos);
}
void TitleBar::mouseReleaseEvent(QMouseEvent *e)
{
    count+=1;
    this->setCursor(Qt::ArrowCursor);
}
void TitleBar::aboutThis(){
    QMessageBox::StandardButton reply;
    QMessageBox::about(this,"about","bung写于2013年3月23日，感谢工藤君的帮助以及Qt社区\n 联系方式:zh.bung@gmail.com");
}
void TitleBar::icon_Clicked(){

//    QToolButton *button = static_cast<QToolButton *>(QObject::sender());
    QMenu* popMenu = new QMenu(this);
     QAction *act_5= popMenu->addAction(tr("about"));
    QAction *act_3= popMenu->addAction(tr("normal"));
    connect(act_5,SIGNAL(triggered()),this,SLOT(aboutThis()));
    connect(act_3,SIGNAL(triggered()),nativeParentWidget(),SLOT(showNormal()));

    QAction *act_1= popMenu->addAction(tr("min"));
    connect(act_1,SIGNAL(triggered()),nativeParentWidget(),SLOT(showMinimized()));
    QAction *act_2= popMenu->addAction(tr("max"));
   connect(act_2,SIGNAL(triggered()),nativeParentWidget(),SLOT(showMaximized()));
popMenu->addSeparator();
   QAction *act_4= popMenu->addAction(tr("Close"));
   connect(act_4,SIGNAL(triggered()),nativeParentWidget(),SLOT(close()));
   switch (nativeParentWidget()->windowState()) {
   case Qt::WindowNoState:
       act_3->setEnabled(false);
       break;
    case Qt::WindowMinimized:
//       qDebug()<<"WindowMinimized";
       break;
    case Qt::WindowMaximized:
        act_3->setEnabled(true);
//        qDebug()<<"WindowMaximized";
       break;
   case Qt::WindowFullScreen:
//        qDebug()<<"WindowFullScreen";
       break;
   case Qt::WindowActive:
//        qDebug()<<"WindowActive";
       break;
   default:
        act_3->setEnabled(false);
       break;
   }
   QPoint point(0,20);
    popMenu->exec(con->mapToGlobal(con->pos())+point);
}
