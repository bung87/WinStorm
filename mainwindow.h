#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "appdata.h"
#include <QMainWindow>
#include <QDir>
#include <QListWidget>
//#include <QtSql>
#include <QProgressDialog>
#include <QToolBar>
#include <QStatusBar>
#include <QGroupBox>
#include "titlebar.h"
#include "chrome.h"
#include "firefox.h"
#include "filelist.h"
#include <QDir>
#include <QLabel>
#include <QSettings>
#include <QBitmap>
#include <QPainter>
#include <QMessageBox>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QProgressDialog *progressDlg;
    explicit MainWindow(QWidget *parent = 0 ,Qt::WindowFlags flags = 0);
    bool testproces(QString p);
    ~MainWindow();
private slots:
    void on_privacy_clicked();
    void on_cache_clicked();
    void cleanall(const QString &path);

protected:
    void resizeEvent ( QResizeEvent * );

private:
     QLabel * f_label;
              QLabel * c_label;
    QSignalMapper *signalMapper;
    QWidget * qWidget;
    QTabWidget*  tabWidget;
    QStatusBar* statusBar;
    bool privacy_enabled;
    bool cache_enabled;
    int genWin32ShellExecute(QString AppFullPath,
                             QString Verb,
                             QString Params,
                             bool ShowAppWindow,
                             bool WaitToFinish);

//    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
