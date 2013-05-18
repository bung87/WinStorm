#include "firefox.h"

Firefox::Firefox(QWidget *parent) :
    QWidget(parent)
{

    appdata* firefox=new appdata("Mozilla/Firefox","profiles");
    QSettings* setting=firefox->settings;
    setting->beginGroup("Profile0");
    QString profile=setting->value("Path").toString();
        setting->endGroup();
    QString filepath=firefox->DataDir.absolutePath()+"/"+profile;
    QString dbpath=filepath+"/"+"places.sqlite";
    historyDB = QSqlDatabase::addDatabase("QSQLITE","firefox");
    historyDB.setDatabaseName(dbpath);
    historyDB.open();

    QVBoxLayout* layout= new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    listWidget=new QListWidget(this);
    listWidget->setStyleSheet("border:none;");
    listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuRequested(const QPoint&)));
    vwidget = new QWidget(this);
    vwidget->setObjectName("main");
    QHBoxLayout* vlayout= new QHBoxLayout();
//    QGridLayout *vlayout = new QGridLayout();

    vwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    vwidget->setLayout(vlayout);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0,0,0,0);
    label = new QLabel();

    label->adjustSize();
    label->setWordWrap(true);
    label->setLayoutDirection(Qt::LeftToRight);
//    label->setAlignment(Qt::AlignTop);
    label->setMinimumHeight(20);
    label->setMinimumWidth(500);
//    vlayout->addWidget(label);
    QString maincss("QWidget#main{background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:0.96 rgb(254, 255, 229), stop:0.98 rgb(255, 255, 255),stop:1 rgb(254, 255, 229))  }");
    vwidget->setStyleSheet(maincss);
    button=new QPushButton(this);
    button->setObjectName("button");
    button->setMinimumHeight(30);
    button->setMinimumWidth(120);
    button->setMaximumWidth(120);
  button->setStyleSheet("QPushButton{margin:0 10px 5px auto;border:1px solid #ccc;border-color:#ccc #ccc #bbb #ddd;border-radius:3px;}QPushButton#button:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 248, 248), stop:1 rgb(221, 221, 221))}QPushButton:enabled{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:1 rgb(221, 221, 221));}QPushButton#button:hover:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(221, 221, 221), stop:1 rgb(200, 200, 200));}");

    layout->addWidget(vwidget);
    layout->addWidget(listWidget);
    this->setLayout(layout);
    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap icon(":/base/firefox");
    QGraphicsPixmapItem* item = scene->addPixmap(icon);

    animation = new QPropertyAnimation( vwidget, "geometry" );
    animation->setDuration( 500 );
    int Width = vwidget->width();
    int Height = vwidget->height();
    animation->setStartValue( QRect( 0, 0, Width, Height ) );
    animation->setEndValue( QRect(0, -Height, Width, Height ) );

    QGraphicsView* view = new QGraphicsView(vwidget);
    view->setStyleSheet("background: transparent;");
    view->setFrameShape(QFrame::NoFrame);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSceneRect(0,0,icon.width(),50);
    view->setMouseTracking(false);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setScene(scene);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    view->setMaximumHeight(50);
    vlayout->addWidget(view);
    vlayout->addWidget(label);
    vlayout->addWidget(button);
    if(!testproces()){
            makeList();
        }else{
           label->setText(QString(tr("Firefox is running,click \"yes\" to close it automatically")));
           button->setText("yes");
           button->adjustSize();
           connect(button,SIGNAL(clicked()),this,SLOT(killAndMakeList()));

        }

}
void Firefox::contextMenuRequested(const QPoint&)
{
    QMenu* popMenu = new QMenu(this);
    QAction *act_o= popMenu->addAction(tr("open"));
    connect(act_o,SIGNAL(triggered()),this,SLOT(itemOpen()));
    QAction *act_d= popMenu->addAction(tr("delete"));
    connect(act_d,SIGNAL(triggered()),this,SLOT(itemRemove()));
    popMenu->exec(QCursor::pos());

}
void Firefox::animationEnd(){
//    QPropertyAnimation *ani = qobject_cast<QPropertyAnimation *>(QObject::sender());
//   vwidget->hide();
}
void Firefox::killAndMakeList(){

//    animation->start(QAbstractAnimation::DeleteWhenStopped);
    QProcess process;
    process.start(QString("taskkill  /f  /im  %1").arg("firefox.exe"));
     process.waitForFinished(-1);
     process.close();
     makeList();

}
void Firefox::makeList(){
    if(historyDB.isOpen()==false){
        historyDB.open();
    }
    QSqlQuery query("SELECT p.id,p.title,p.url,f.data,p.favicon_id FROM moz_places p,moz_favicons f WHERE p.favicon_id=f.id ORDER BY p.id DESC",historyDB);
    query.exec();
    while(query.next()){
        QMap <QString,QVariant> map;
        QVariant vid;
        QVariant vtitle;
        QVariant vurl;
        QVariant vfavion_id;
        vid=query.value(0);
        vtitle=query.value(1);
        vurl=query.value(2);
        vfavion_id=query.value(4);
        QByteArray iconbit(query.value(3).toByteArray());
        map["id"]=vid;
        map["title"]=vtitle;
        map["url"]=vurl;
        map["favion_id"]=vfavion_id;
        QVariant var(map);

        QPixmap pixmap(16,16);
        pixmap.loadFromData(iconbit);
        QString text;
        if (vtitle.toString().isEmpty()){
            text=vurl.toString();
        }else{
            text=vtitle.toString();
        }
        QListWidgetItem* item=new QListWidgetItem(QIcon(pixmap),text,listWidget);
        item->setData(Qt::UserRole,var);
         item->setToolTip(vtitle.toString());
        listWidget->addItem(item);
 }
    count=listWidget->count();
    QString maincss("QWidget#main{background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:0.96 rgb(232, 241, 252), stop:0.98 rgb(255, 255, 255),stop:1 rgb(232, 241, 252)) %1 }");
    label->setText(QString(tr("%1 records")).arg(count));
    vwidget->setStyleSheet(maincss.arg(""));
    if(count==0){
        button->setText(tr("not found"));
        button->adjustSize();
        disconnect(button,SIGNAL(clicked()),this,SLOT(itemRemoveAll()));
        connect(button,SIGNAL(clicked()),this,SLOT(rebuildList()));

    }else{
         button->setText(tr("clean"));
         connect(button,SIGNAL(clicked()),this,SLOT(itemRemoveAll()));
         button->adjustSize();
    }
    query.finish();
    historyDB.close();
}
void Firefox::itemOpen()
{
QVariant var=listWidget->currentIndex().data(Qt::UserRole);
QString url=var.toMap().value("url").toString();
QString program = "explorer.exe";
     QProcess process;
     process.startDetached(program,QStringList(url));
     process.close();
}

void Firefox::itemRemove()
{
QListWidgetItem *item=listWidget->currentItem();
QVariant var=item->data(Qt::UserRole);
QString id=var.toMap().value("id").toString();
if(historyDB.isOpen()==false){
    historyDB.open();
}
QSqlQuery query(historyDB);
bool ok1=query.exec("DELETE FROM moz_places WHERE id="+id);
bool ok2=query.exec("DELETE FROM moz_favicons WHERE id="+id );
    if(ok1 && ok2){
    listWidget->takeItem(listWidget->currentRow());
    }
    query.finish();
    historyDB.close();
}
void Firefox::itemRemoveAll(){
    if(historyDB.isOpen()==false){
        historyDB.open();
    }
    QSqlQuery query(historyDB);
    query.exec("DELETE FROM moz_places");
    query.exec("DELETE FROM moz_favicons");
    query.exec("DELETE FROM sqlite_sequence WHERE name = 'moz_places'");
    query.exec("DELETE FROM sqlite_sequence WHERE name = 'moz_favicons'");
    delete this;
}
bool Firefox::testproces(QString p)
{
    QProcess process;
       QString cmd="tasklist";
       process.start(cmd);
   process.waitForFinished(-1);

   QByteArray out = process.readAllStandardOutput();
   process.close();
   QList<QByteArray> processes=out.split('\n');
   QStringList list;
   for (int i = 3; i < processes.size()-1; ++i) {
   QString temp=processes.value(i);
   list<< temp.split(QRegExp("\\s+"));
   }

   if(list.contains(p)){

           return true;

   }
   return false;
}
void Firefox::rebuildList(){
    makeList();
}
