#include "chrome.h"

Chrome::Chrome(QWidget *parent) :
    QWidget(parent)
{
    history=new appdata("../local/Google/Chrome/User Data/Default/","History");
    favicons=new appdata("../local/Google/Chrome/User Data/Default/","Favicons");
    QString favDBpath=favicons->DataPath;
    favDB = QSqlDatabase::addDatabase("QSQLITE","chromefav");
    favDB.setDatabaseName(favDBpath);
    favDB.open();
    QString historyDBpath=history->DataPath;
    historyDB = QSqlDatabase::addDatabase("QSQLITE","chrome");
    historyDB.setDatabaseName(historyDBpath);
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
    label->setMinimumHeight(20);
    label->setMinimumWidth(500);
    QString maincss("QWidget#main{background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:0.96 rgb(254, 255, 229), stop:0.98 rgb(255, 255, 255),stop:1 rgb(254, 255, 229))  }");
    vwidget->setStyleSheet(maincss);
    button=new QPushButton(this);
    button->setObjectName("button");
    button->setMinimumHeight(30);
    button->setMinimumWidth(120);
    button->setStyleSheet("QPushButton{margin:0 10px 5px auto;border:1px solid #ccc;border-color:#ccc #ccc #bbb #ddd;border-radius:3px;}QPushButton#button:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 248, 248), stop:1 rgb(221, 221, 221))}QPushButton:enabled{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:1 rgb(221, 221, 221));}QPushButton#button:hover:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(221, 221, 221), stop:1 rgb(200, 200, 200));}");

    layout->addWidget(vwidget);
    layout->addWidget(listWidget);
    this->setLayout(layout);
    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap icon(":/base/chrome");
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
//    vlayout->addWidget(view, 0, 0,2,0,(Qt::AlignLeft|Qt::AlignTop));
//    vlayout->addWidget(label, 0, 1,2,0,(Qt::AlignLeft|Qt::AlignTop));
//    vlayout->addWidget(button, 1, 1);
    vlayout->addWidget(view);
    vlayout->addWidget(label);
    vlayout->addWidget(button);
    if(!testproces()){
            makeList();
        }else{
           label->setText(QString(tr("Chrome is running,click \"yes\" to close it automatically")));
           button->setText(tr("yes"));
           button->adjustSize();
           connect(button,SIGNAL(clicked()),this,SLOT(killAndMakeList()));
        }
}

void Chrome::killAndMakeList(){

//    animation->start(QAbstractAnimation::DeleteWhenStopped);
    QProcess process;
    process.start(QString("taskkill  /f  /im  %1").arg("chrome.exe"));
     process.waitForFinished(-1);
     process.close();
     makeList();
QString maincss("QWidget#main{background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:0.96 rgb(232, 241, 252), stop:0.98 rgb(255, 255, 255),stop:1 rgb(232, 241, 252)) %1 }");
label->setText(QString(tr("%1 records")).arg(count));
button->setText(tr("Clean"));
vwidget->setStyleSheet(maincss.arg(""));
}
void Chrome::animationEnd(){
//    QPropertyAnimation *ani = qobject_cast<QPropertyAnimation *>(QObject::sender());
//   vwidget->hide();
}
void Chrome::makeList(){
    if(favDB.isOpen()==false){
         favDB.open();
    }
    QSqlQuery query2("SELECT icon_mapping.icon_id,icon_mapping.page_url,favicon_bitmaps.image_data FROM icon_mapping,favicon_bitmaps WHERE favicon_bitmaps.icon_id = icon_mapping.icon_id",favDB);

    if(query2.exec()==false){
        qDebug()<<query2.lastError();
    }
    QHash <QString,QVariant> hash;
    while(query2.next()){
       QString url=query2.value(1).toString();
       QUrl u(url);
       QString host=u.host();
       hash.insert(host,query2.value(2));
       QString iconid=host+"icon";
       hash.insert(iconid,query2.value(0));
    }
    query2.finish();
    favDB.close();

    if(historyDB.isOpen()==false){
         historyDB.open();
    }

    QSqlQuery query1("SELECT urls.id, urls.title, urls.url FROM urls WHERE urls.hidden=0 ORDER BY urls.id DESC",historyDB);
    query1.exec();
    while(query1.next()){
        QMap <QString,QVariant> map;
        QVariant urls_id;
//        QVariant visits_id;
        QVariant urls_title;
        QVariant urls_url;
        urls_id=query1.value(0);
        urls_title=query1.value(1);
        urls_url=query1.value(2);
//        visits_id=query1.value(3);
           QString k=urls_url.toString();
           QUrl u(k);
           QString d=u.host();
           QString icon_id=hash.value(d+"icon").toString();
            QByteArray iconbit;
            iconbit=hash.value(d).toByteArray();
            map["id"]=urls_id;
            map["title"]=urls_title;
            map["url"]=urls_url;
            map["icon_id"]=icon_id;
            QVariant var(map);
            QPixmap pixmap(16,16);
            pixmap.loadFromData(iconbit);
            QString text;
            if (urls_title.toString().isEmpty()){
                text=urls_url.toString();
            }else{
                text=urls_title.toString();
            }
        QListWidgetItem* item=new QListWidgetItem(QIcon(pixmap),text,listWidget);
        item->setData(Qt::UserRole,var);
        item->setToolTip(urls_title.toString());
        listWidget->addItem(item);
 }
    count=listWidget->count();
    QString maincss("QWidget#main{background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:0.96 rgb(232, 241, 252), stop:0.98 rgb(255, 255, 255),stop:1 rgb(232, 241, 252)) %1 }");
    label->setText(QString(tr("%1files")).arg(count));
    vwidget->setStyleSheet(maincss.arg(""));
    if(count==0){
        button->setText(tr("not found"));
        button->adjustSize();
        disconnect(button,SIGNAL(clicked()),this,SLOT(itemRemoveAll()));
        connect(button,SIGNAL(clicked()),this,SLOT(rebuildList()));
    }else{
         button->setText(tr("Clean"));
         connect(button,SIGNAL(clicked()),this,SLOT(itemRemoveAll()));
         button->adjustSize();
    }
    query1.finish();
    historyDB.close();

}
void Chrome::contextMenuRequested(const QPoint&)
{

    QMenu* popMenu = new QMenu(this);
    QAction *act_o= popMenu->addAction("open");
    connect(act_o,SIGNAL(triggered()),this,SLOT(itemOpen()));
    QAction *act_d= popMenu->addAction("delete");
    connect(act_d,SIGNAL(triggered()),this,SLOT(itemRemove()));
    popMenu->exec(QCursor::pos());
}

void Chrome::itemOpen()
{
QVariant var=listWidget->currentIndex().data(Qt::UserRole);
QString url=var.toMap().value("url").toString();
QString program = "explorer.exe";
     QProcess process;
     process.startDetached(program,QStringList(url));
     process.close();
}

void Chrome::itemRemove()
{
QListWidgetItem *item=listWidget->currentItem();
QVariant var=item->data(Qt::UserRole);
QString id=var.toMap().value("id").toString();
QString url=var.toMap().value("url").toString();
QString icon_id=var.toMap().value("icon_id").toString();
//QString favion_id=var.toMap().value("favion_id").toString();
if(historyDB.isOpen()==false){
     historyDB.open();
}
if(favDB.isOpen()==false){
     favDB.open();
}
QSqlQuery query(historyDB);
bool ok1=query.exec("DELETE FROM visits WHERE url="+id);
bool ok2=query.exec("DELETE FROM urls WHERE id="+id );
query.finish();
    if(ok1 && ok2){
   listWidget->takeItem(listWidget->currentRow());
    }
    QSqlQuery query2(favDB);
    QString querystr("DELETE FROM icon_mapping,favicons,favicon_bitmaps WHERE icon_mapping.icon_id=%1 OR favicons.id=%1 OR favicon_bitmaps.icon_id=%1");
    bool ok4=query2.exec( querystr.arg(icon_id));
    query2.finish();
    historyDB.close();
    favDB.close();
}
void Chrome::itemRemoveAll(){
    QDir local_dir;
     local_dir=history->DataDir;
     local_dir.setNameFilters(QStringList()<<"History*"<<"Favicons*"<<"Visited Links"<<"Top Sites");
       foreach(QFileInfo entry_info, local_dir.entryInfoList()){
           QFile sqlitefile;
           sqlitefile.setFileName(entry_info.absoluteFilePath());
           sqlitefile.remove();
       }
       delete this;
}
bool Chrome::testproces(QString p)
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
void Chrome::rebuildList(){
    makeList();
}
