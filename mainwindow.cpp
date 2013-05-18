#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent,Qt::WindowFlags f) :
    QMainWindow(parent,f= Qt::FramelessWindowHint)
{
    privacy_enabled=false;
    cache_enabled=false;
    TitleBar* titlebar = new TitleBar(this);
    QToolBar * toolbar = new QToolBar(this);
    titlebar->setObjectName("titlebar");
    toolbar->setObjectName("toolbar");
    this->setWhatsThis("111");

    statusBar = new QStatusBar(this);
    statusBar->setStyleSheet("QStatusBar{border:1px solid #555;background:#e6edf4;border-top:none;}");
    statusBar->setMinimumHeight(30);
    QLabel* copyrights=new QLabel(statusBar);
this->setStatusBar(statusBar);
//    copyrights->setText(tr("bung写于2013年3月23日"));
    copyrights->setMinimumHeight(30);
    copyrights->setLayoutDirection(Qt::RightToLeft);
    toolbar->setStyleSheet("QToolBar{margin:10px}");
    QToolButton* privacy=new QToolButton();
    privacy->setText(tr("Privacy"));
    privacy->setIcon(QIcon(":/base/foot"));
    privacy->setIconSize(QSize(50,50));
    privacy->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    privacy->setObjectName("privacy");
    privacy->setMinimumWidth(65);
//    privacy->setStyleSheet("");
    privacy->setMinimumHeight(66);
    QString normal;
    normal="border:1px solid #ccc;border-radius:5px;margin-top:1px;border:none;background:transparent;";
    QString hover;
    hover="color:#54839f;background:url(:/base/btn_bg) no-repeat";
    privacy->setStyleSheet(QString("#privacy:enabled{%1}").arg(normal)+QString("#privacy:hover{%1}").arg(hover)+"QToolButton#privacy:pressed{background:transparent url(:/base/btn_pressed)}");
//    privacy->setIconSize(QSize(60,60));
    privacy->setAutoRaise(true);
    toolbar->addWidget(privacy);

    QToolButton* clean=new QToolButton();
    clean->setText(tr("Cache"));
    clean->setIcon(QIcon(":/base/folder"));
    clean->setIconSize(QSize(50,50));
    clean->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    clean->setObjectName("clean");
    clean->setMinimumWidth(65);
    clean->setMinimumHeight(66);
   clean->setStyleSheet(QString("#clean:enabled{%1}").arg(normal)+QString("#clean:hover{%1}").arg(hover)+"QToolButton#clean:pressed{background:transparent url(:/base/btn_pressed)}");
    clean->setAutoRaise(true);
    toolbar->addWidget(clean);

    connect(privacy,SIGNAL(clicked()),this,SLOT(on_privacy_clicked()));
    connect(clean,SIGNAL(clicked()),this,SLOT(on_cache_clicked()));
   QVBoxLayout* mainlayout=new QVBoxLayout();
    QVBoxLayout* vlayout= new QVBoxLayout();//titlebar's layout
    vlayout->setMargin(0);
    vlayout->setContentsMargins(0,1,0,0);
    vlayout->setSpacing(0);
    vlayout->addWidget(titlebar);
    vlayout->addWidget(toolbar);
    QWidget * vwidget = new QWidget();//titlebar's wrapper
    vwidget->setObjectName("vwidget");
    vwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    vwidget->setStyleSheet("#vwidget{margin:1px 1px 0 1px;border:1px solid rgba(255,255,255,100);border-width:1px 1px 0 1px;border-top-left-radius:3px;border-top-right-radius:3px;}");
    vwidget->setLayout(vlayout);



    this->setMinimumWidth(800);
    this->setMinimumHeight(600);

    int w=this->size().width();
    int h=this->size().height();
    QLinearGradient gradient(0, 0, 0, h);
    //blue
//    gradient.setColorAt(0, QColor(140, 203, 242));
//    gradient.setColorAt(0.2, QColor(87, 169, 219));
//    gradient.setColorAt(1, QColor(198, 222, 237));

    gradient.setColorAt(0, QColor(197, 225, 250));
//    gradient.setColorAt(0.2, QColor(87, 169, 219));
    gradient.setColorAt(1, QColor(180, 215, 250));
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(gradient));
//  palette.setBrush(this->backgroundRole(), QBrush(QPixmap(":/base/bg.png")));
    this->setPalette(palette);

    QBitmap objBitmap(this->size());
    QPainter painter(&objBitmap);
    painter.fillRect(this->rect(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    painter.drawRoundedRect(this->rect(),3,3);
    this->setMask(objBitmap);
    tabWidget = new QTabWidget(this);
    tabWidget->setObjectName("maintab");
//    tabWidget->tabBar()->setStyleSheet("QTabBar{margin:0 1px;border:1px solid #E8F1FC;border-width:0 1px 0 1px;}");
    tabWidget->setStyleSheet("QTabWidget::pane{margin:0 1px;padding:0;border:1px solid #E8F1FC;border-top:none;background-color:#fff;}QTabWidget{border:none;}");
    tabWidget->tabBar()->setStyleSheet("QTabBar::tab{margin:0 3px;padding:2px 10px;background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(232, 241, 252), stop:1 rgb(255, 255, 255));border:1px solid #B8C2CE;border-top-left-radius:3px;border-top-right-radius:3px;}QTabBar::tab:selected { background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(232, 241, 252), stop:0.2 rgb(255, 255, 255), stop:1 rgb(255, 255, 255));border-bottom: none; }");

    qWidget=new QWidget(this);
    tabWidget->hide();
    mainlayout->setSpacing(0);
    mainlayout->setContentsMargins(0,0,0,0);
    mainlayout->addWidget(vwidget);
    mainlayout->addWidget(qWidget);
    mainlayout->addWidget(tabWidget);
//    mainlayout->addWidget(statusBar);
    this->setStyleSheet("MainWindow{background:transparent;border:1px solid #555;border-radius:3px;}");

    QWidget * q = new QWidget();
    q->setObjectName("central");
    q->setStyleSheet("#central{background:transparent;border:1px solid #555;border-bottom:1px solid #e6edf4;border-top-left-radius:3px;border-top-right-radius:3px;}");
    q->setLayout(mainlayout);
    setCentralWidget(q);
    privacy->click();

}

MainWindow::~MainWindow()
{
//    delete ui;
}

bool MainWindow::testproces(QString p)
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
//       QMessageBox::StandardButton reply;
//       reply=QMessageBox::question(this,"提示",QString("%1正在运行").arg(p),QMessageBox::Ok | QMessageBox::No);
//       if(reply==QMessageBox::Ok){
//           QProcess process;
//            process.start(QString("taskkill  /f  /im  %1").arg(p));
//            process.waitForFinished(-1);
//            process.close();
//            return false;
//       }else{
           return true;
//       }

   }
   return false;


}
void MainWindow::resizeEvent ( QResizeEvent * ){
    QBitmap objBitmap(this->size());
    QPainter painter(&objBitmap);
    painter.fillRect(this->rect(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    painter.drawRoundedRect(this->rect(),3,3);
    this->setMask(objBitmap);
}
void MainWindow::on_privacy_clicked(){
    qWidget->hide();
    tabWidget->show();
    if(privacy_enabled) return;
//    statuBar->
            progressDlg=new QProgressDialog(this);
            QFont font("ZYSong18030",12);
            progressDlg->setFont(font);
            progressDlg->setWindowModality(Qt::WindowModal);
            progressDlg->setMinimumDuration(5);
            progressDlg->setWindowTitle(tr("please wait"));
            progressDlg->setLabelText(tr("Loading..."));
            progressDlg->setCancelButtonText(tr("取消"));
            progressDlg->setRange(0,100);

    appdata* recentfile=new appdata("Microsoft/Windows/Recent/","","*.lnk");
    progressDlg->setValue(5);
    QDir dir_recentfile=recentfile->DataDir;
    appdata* jumplistdata=new appdata("Microsoft/Windows/Recent/Automaticdestinations/");
    progressDlg->setValue(10);
    QDir dir_jumplist=jumplistdata->DataDir;
    QString maincss("QWidget#main{background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:0.96 rgb(232, 241, 252), stop:0.98 rgb(255, 255, 255),stop:1 rgb(232, 241, 252)) %1 }");
    Filelist* recent_file=new Filelist(dir_recentfile);
    progressDlg->setValue(15);
        recent_file->vwidget->setStyleSheet(maincss.arg(" url(:/base/recent) no-repeat"));
        progressDlg->setValue(16);
        recent_file->label->setText("“最近使用的项目”虽然可以方便我们打开使用过的文件，但是它同时也暴露了我们的隐私，别人可以通过这个来知道我们曾经使用过哪些文件，所以有时候需要来清空它。");
        progressDlg->setValue(17);
        recent_file->label->setStyleSheet("QLabel{padding-left:80px;}");
        progressDlg->setValue(18);
        tabWidget->addTab(recent_file,QIcon(":/base/recent"),tr("recent files"));
        progressDlg->setValue(19);
    progressDlg->setValue(20);

    Filelist* jumplist=new Filelist(dir_jumplist);
     progressDlg->setValue(25);
    jumplist->label->setText("跳转列表 (Jump List) 是 Windows 7 中的新增功能，可帮助您快速访问常用的文档、图片、歌曲或网站。 您只需右键单击 Windows 7 任务栏上的程序按钮即可打开跳转列表 (Jump List)。 （您还可以通过在“开始”菜单上单击程序名称旁的箭头，来访问跳转列表");
     progressDlg->setValue(26);
    jumplist->vwidget->setStyleSheet(maincss.arg(" url(:/base/startmenu) no-repeat"));
    progressDlg->setValue(27);
    jumplist->label->setStyleSheet("QLabel{padding-left:80px;}");
    progressDlg->setValue(28);
    tabWidget->addTab(jumplist,QIcon(":/base/startmenu"),tr("Jump List"));
    progressDlg->setValue(29);
//progressDlg->setValue(60);
    QString path = "HKEY_LOCAL_MACHINE\\Software";
    QSettings *settings = new QSettings( path, QSettings::NativeFormat);
    progressDlg->setValue(30);
//    progressDlg->setValue(70);
    QStringList apps = settings->allKeys();
    if(apps.filter("Google Chrome",Qt::CaseInsensitive).size()){
        Chrome* chrome_history=new Chrome();
progressDlg->setValue(60);
        tabWidget->addTab(chrome_history,QIcon(":/base/chrome"),tr("Chrome"));
        progressDlg->setValue(70);
    }
//    progressDlg->setValue(80);
    if(apps.filter("Firefox",Qt::CaseInsensitive).size()){
          Firefox* firefox=new Firefox();
    progressDlg->setValue(80);
            tabWidget->addTab(firefox,QIcon(":/base/firefox"),tr("Firefox"));
            progressDlg->setValue(90);
        }
        tabWidget->show();
        privacy_enabled=true;
        progressDlg->setValue(100);
}
void MainWindow::on_cache_clicked(){

    tabWidget->hide();
    qWidget->show();
    if (cache_enabled) return;
     appdata* chrome_cache=new appdata("../local/Google/Chrome/User Data/Default/Cache");
 qint64 size = 0, sizeTotal = 0;
  foreach(QFileInfo fi, chrome_cache->DataDir.entryInfoList())
    {
      size =  fi.size();

      sizeTotal = sizeTotal + size;
  }


    appdata* firefox=new appdata("Mozilla/Firefox","profiles");
    QSettings* setting=firefox->settings;
    setting->beginGroup("Profile0");
    QString profile=setting->value("Path").toString();
    setting->endGroup();

    appdata* firefox_cache=new appdata("../local/Mozilla/Firefox/"+profile+"/Cache");

    qint64 size2 = 0, sizeTotal2 = 0;
     foreach(QFileInfo fi, firefox_cache->DataDir.entryInfoList())
       {
         if(fi.isDir()){
            foreach(QFileInfo fi2, fi.dir().entryInfoList()){
                size2+=fi2.size();
            }
         }else{
              size2 =  fi.size();
         }

         sizeTotal2 = sizeTotal2 + size2;
         size2=0;
     }
 QString btnStyle("QPushButton{margin:0 10px 5px auto;border:1px solid #ccc;border-color:#ccc #ccc #bbb #ddd;border-radius:3px;}QPushButton#c_btn:hover,QPushButton#f_btn:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 248, 248), stop:1 rgb(221, 221, 221))}QPushButton:enabled{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:1 rgb(221, 221, 221));}QPushButton#button:hover:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(221, 221, 221), stop:1 rgb(200, 200, 200));}");
    QGridLayout *glayout=new QGridLayout();
//    glayout->setMargin(0);
//    glayout->setSpacing(0);
//    glayout->setContentsMargins(0,0,0,0);
    QGroupBox *c_box=new QGroupBox();
    QGroupBox * f_box=new QGroupBox();
    c_box->setFixedHeight(80);
    f_box->setFixedHeight(80);
    c_box->setFlat(true);
    f_box->setFlat(true);
    c_box->setStyleSheet("QGroupBox{background:rgba(255,255,255,0.5) url(:/base/chrome) no-repeat}");
    f_box->setStyleSheet("QGroupBox{background:rgba(255,255,255,0.5) url(:/base/firefox) no-repeat}");

    QString sizeTotalstr;
    QString sizeTotalstr2;
    if(sizeTotal>1024){
        sizeTotal=sizeTotal/1024;
        sizeTotalstr=QString::number(sizeTotal)+"KB";
        if(sizeTotal>1024){
            sizeTotal=sizeTotal/1024;
            sizeTotalstr=QString::number(sizeTotal)+"MB";
        }
    }else{
        sizeTotalstr=QString::number(sizeTotal)+"Byte";
    }

    if(sizeTotal2>1024){
        sizeTotal2=sizeTotal2/1024;
        sizeTotalstr2=QString::number(sizeTotal2)+"KB";
        if(sizeTotal2>1024){
            sizeTotal2=sizeTotal2/1024;
            sizeTotalstr2=QString::number(sizeTotal2)+"MB";
        }
    }else{
        sizeTotalstr2=QString::number(sizeTotal2)+"Byte";
    }
    c_label=new QLabel(c_box);
    c_label->setText(sizeTotalstr);
    c_label->setGeometry(QRect(100,10,100,30));
    f_label=new QLabel(f_box);
    f_label->setText(sizeTotalstr2);
    f_label->setGeometry(QRect(100,10,100,30));
    QPushButton* c_btn=new QPushButton(c_box);

//    c_btn->setIcon(QIcon(":/base/chrome"));
    c_btn->setText(tr("clean"));
    QPushButton* f_btn=new QPushButton(f_box);
    f_btn->setObjectName("f_btn");
    c_btn->setObjectName("c_btn");
//    f_btn->setIcon(QIcon(":/base/firefox"));

    f_btn->setText(tr("clean"));
    c_btn->setMinimumHeight(30);
    c_btn->setMinimumWidth(120);
    f_btn->setMinimumHeight(30);
    f_btn->setMinimumWidth(120);
    c_btn->setGeometry(200,10,100,30);
    f_btn->setGeometry(200,10,100,30);
    c_btn->setStyleSheet(btnStyle);
    f_btn->setStyleSheet(btnStyle);
    signalMapper= new QSignalMapper(this);

    connect(signalMapper, SIGNAL(mapped(const QString&)),
          this, SLOT(cleanall(const QString&)));

    connect( c_btn, SIGNAL( clicked() ), signalMapper, SLOT( map() ) );
    connect( f_btn, SIGNAL( clicked() ), signalMapper, SLOT( map() ) );
    QString s1=chrome_cache->DataPath;
    QString s2=firefox_cache->DataPath;

    signalMapper->setMapping( c_btn,s1+",chrome.exe");
    signalMapper->setMapping( f_btn, s2+",firefox.exe");

    glayout->addWidget(c_box,0,0);
    glayout->addWidget(f_box,0,1);

//    glayout->addWidget(c_box,1,0);
//    glayout->addWidget(f_box,1,1);
    qWidget->setLayout(glayout);
    qWidget->adjustSize();
    qWidget->show();
    cache_enabled=true;
}
void MainWindow::cleanall(const QString &str)
{
    QStringList list;
    list=str.split(",");
    QString path=list.at(0);
    QString name=list.at(1);
    if(name=="chrome.exe"){
        c_label->setText("0Byte");
    }else{
        f_label->setText("0Byte");
    }
    if(testproces(name)){
               QMessageBox::StandardButton reply;
               reply=QMessageBox::question(this,"提示",QString("%1正在运行,是否立即关闭？").arg(name),QMessageBox::Ok | QMessageBox::No);
               if(reply==QMessageBox::Ok){
                   QProcess process;
                    process.start(QString("taskkill  /f  /im  %1").arg(name));
                    process.waitForFinished(-1);
                    process.close();
               }
    }
    QString nativepath=QDir::toNativeSeparators(path);
    QString AppToExec = "cmd.exe";
    QString AppParams = "/c rd /s /q  \"%1\"";
    if (0 != genWin32ShellExecute(AppToExec,
                                  "open",    // default verb: "open" or "exec"
                                  AppParams.arg(nativepath),
                                  false, //show
                                  false)) // wait to finish
    {

    }else{
//        delete this;
    }
}
int MainWindow::genWin32ShellExecute(QString AppFullPath,
                         QString Verb,
                         QString Params,
                         bool ShowAppWindow,
                         bool WaitToFinish)
{
    int Result = 0;

    // Setup the required structure
    SHELLEXECUTEINFO ShExecInfo;
    memset(&ShExecInfo, 0, sizeof(SHELLEXECUTEINFO));
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    if (Verb.length() > 0)
        ShExecInfo.lpVerb = reinterpret_cast<const WCHAR *>(Verb.utf16());
    ShExecInfo.lpFile = NULL;
    if (AppFullPath.length() > 0)
        ShExecInfo.lpFile = reinterpret_cast<const WCHAR *>(AppFullPath.utf16());
    ShExecInfo.lpParameters = NULL;
    if (Params.length() > 0)
        ShExecInfo.lpParameters = reinterpret_cast<const WCHAR *>(Params.utf16());
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = (ShowAppWindow ? SW_SHOW : SW_HIDE);
    ShExecInfo.hInstApp = NULL;

    // Spawn the process
    if (ShellExecuteEx(&ShExecInfo) == FALSE)
    {
        Result = -1; // Failed to execute process
    } else if (WaitToFinish)
    {
        WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
    }

    return Result;
}
