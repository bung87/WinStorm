#include "filelist.h"

Filelist::Filelist(QDir &dir,QWidget *parent) :
    QWidget(parent)
{
    count=0;
    QString dirpath=dir.absolutePath();
    nativepath=QDir::toNativeSeparators(dirpath);

    list=new QListWidget(this);
    list->setStyleSheet("border:none;");
    vwidget = new QWidget(this);
    vwidget->setMinimumHeight(50);
    vwidget->setObjectName("main");
    QHBoxLayout* vlayout= new QHBoxLayout();
    vwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    vwidget->setLayout(vlayout);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0,0,0,0);
    label = new QLabel();
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignTop);
    label->setMinimumHeight(40);
    vlayout->addWidget(label);
    button=new QPushButton(this);
    button->setObjectName("button");
    button->setFlat(true);
    button->setMinimumHeight(30);
//    button->setLayoutDirection(Qt::RightToLeft);

    button->setMinimumWidth(120);
    button->setMaximumWidth(120);

    button->setStyleSheet("QPushButton{margin:0 10px 5px auto;border:1px solid #ccc;border-color:#ccc #ccc #bbb #ddd;border-radius:3px;}QPushButton#button:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 248, 248), stop:1 rgb(221, 221, 221))}QPushButton:enabled{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:1 rgb(221, 221, 221));}QPushButton#button:hover:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(221, 221, 221), stop:1 rgb(200, 200, 200));}");

    list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(list,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuRequested(const QPoint&)));


    QVBoxLayout* layout= new QVBoxLayout();

    if(dir.exists() && dir.entryInfoList().count()>0){
        foreach(QFileInfo entry_info, dir.entryInfoList())
                {
                    QString target;
                    if(entry_info.isFile())
                     {
                        if(entry_info.isSymLink())
                           { target=entry_info.symLinkTarget();}
                               else{
                        target=entry_info.absoluteFilePath();
                        }

                    }else{
                        target=entry_info.symLinkTarget();
                    }

                        QFileInfo fileInfo(target);
                        QFileIconProvider seekIcon;
                        QIcon icon =seekIcon.icon(fileInfo);
                        QMap <QString,QVariant> map;
                        QVariant v1(target);
                        QVariant v2(entry_info.absoluteFilePath());
                        map["target"]=v1;
                        map["lnk"]=v2;
                        QVariant var(map);
                        QListWidgetItem* item=new QListWidgetItem(icon,entry_info.fileName(),list);
                        item->setData(Qt::UserRole,var);
                        list->addItem(item);
                        ++count;

                }

    }
    if(count==0){
        button->setText(tr("没有记录"));

        disconnect(button,SIGNAL(clicked()),this,SLOT(cleanall()));

    }else{
         button->setText(tr("Clean"));
         connect(button,SIGNAL(clicked()),this,SLOT(cleanall()));

    }
     vlayout->addWidget(button);
     layout->setMargin(0);
     layout->setSpacing(0);
     layout->setContentsMargins(0,0,0,0);
     layout->addWidget(vwidget);
     layout->addWidget(list);
     this->setLayout(layout);

}
void Filelist::cleanall()
{

    QString AppToExec = "cmd.exe";
    QString AppParams = "/c del /a /f /q \"%1\"";
    if (0 != this->genWin32ShellExecute(AppToExec,
                                  "open",    // default verb: "open" or "exec"
                                  AppParams.arg(nativepath),
                                  false, //show
                                  false)) // wait to finish
    {

    }else{
        delete this;
    }
}
void Filelist::contextMenuRequested(const QPoint&)
{

    QMenu* popMenu = new QMenu(this);
    QAction *act_o= popMenu->addAction(tr("Open"));
    connect(act_o,SIGNAL(triggered()),this,SLOT(itemOpen()));
    QAction *act_d= popMenu->addAction(tr("Delete"));
    connect(act_d,SIGNAL(triggered()),this,SLOT(itemRemove()));
    popMenu->exec(QCursor::pos());

}

void Filelist::itemOpen()
{
    QVariant var=list->currentIndex().data(Qt::UserRole);
    QString path=var.toMap().value("target").toString();
    QString filepath=path.replace("/","\\");

    QString program = "explorer.exe";
         QProcess process;
         process.startDetached(program,QStringList(filepath));
         process.close();
}
int Filelist::genWin32ShellExecute(QString AppFullPath,
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

void Filelist::itemRemove()
{
    QListWidgetItem *item=list->currentItem();
    QVariant var=item->data(Qt::UserRole);
    QString path=QDir::toNativeSeparators(var.toMap().value("lnk").toString());

    QString AppToExec = "cmd.exe";
    // Put any required parameters of App2.exe to AppParams string
    QString AppParams = "/c del /a /f \"%1\"";
    if (0 != this->genWin32ShellExecute(AppToExec,
                                  "open",    // default verb: "open" or "exec"
                                  AppParams.arg(path),
                                  false, // run hidden
                                  false)) // wait to finish
    {

    }else{
         list->takeItem(list->currentRow());
    }
}
