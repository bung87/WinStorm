#include "appdata.h"
#include <QSettings>

appdata::appdata(QString path,QString name,QString namefilter,QObject *parent) :
    QObject(parent)
{
    if(name.isEmpty()){

      settings=new QSettings(QSettings::IniFormat, QSettings::UserScope,path,"application");
        path= QFileInfo(settings->fileName()).absolutePath() + "/";
        QDir dir (path);
        dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::System);
        if(!namefilter.isEmpty()){
           QStringList  filters=namefilter.split(",");
           // QStringList filters("*.lnk");
            dir.setNameFilters(filters);
        }
        DataPath=path;
        DataDir=dir;

    }else{
        settings=new QSettings(QSettings::IniFormat, QSettings::UserScope,path,name);

        DataPath= QFileInfo(settings->fileName()).absolutePath() + "/"+name;

        QFileInfo info(DataPath);
 DataDir=info.absoluteDir();
    }

}
