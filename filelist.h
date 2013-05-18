#ifndef FILELIST_H
#define FILELIST_H

#include "qt_windows.h"
//#include "qwindowdefs_win.h"
//#include <shellapi.h>

#include <QWidget>
#include <QVBoxLayout>
#include <QDir>
#include <QListWidget>
#include <QLabel>
#include <QFileIconProvider>
#include <QMenu>
#include <QProcess>
#include <QPushButton>
class Filelist : public QWidget
{
    Q_OBJECT
public:
    explicit Filelist(QDir &dir,QWidget *parent = 0);
    QLabel * label;
    QWidget * vwidget;
    QPushButton* button;
    QString nativepath;
    int genWin32ShellExecute(QString AppFullPath,
                             QString Verb,
                             QString Params,
                             bool ShowAppWindow,
                             bool WaitToFinish);

    int count;
private:
    QListWidget* list;
signals:

public slots:
    void contextMenuRequested(const QPoint&pos);
    void itemOpen();
    void itemRemove();
    void cleanall();

};

#endif // FILELIST_H
