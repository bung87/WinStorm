#ifndef APPDATA_H
#define APPDATA_H

#include <QObject>
#include <QDir>
#include <QSettings>
class appdata : public QObject
{
    Q_OBJECT

public:
    explicit appdata(QString path="",QString name="",QString namefilter=NULL,QObject *parent = 0);
  //  QString path(QString path="");
    QString DataPath;
    QDir DataDir;
    QSettings* settings;
signals:

public slots:

};

#endif // APPDATA_H
