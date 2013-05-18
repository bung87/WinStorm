#ifndef CHROME_H
#define CHROME_H

#include <QWidget>
#include <QVBoxLayout>
#include "appdata.h"
#include <QtSql>
#include <QListWidget>
#include <QMenu>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
class Chrome : public QWidget
{
    Q_OBJECT
public:
    explicit Chrome(QWidget *parent = 0);
    void makeList();
    int count;
    appdata* history;
    appdata* favicons;
    QLabel * label;
    QWidget * vwidget;
    QPushButton* button;
private:
    QListWidget* listWidget;
    QPropertyAnimation* animation;
    QSqlDatabase favDB;
    QSqlDatabase historyDB;
    bool testproces(QString p="chrome.exe");
signals:

public slots:
    void contextMenuRequested(const QPoint&pos);
    void itemOpen();
    void itemRemove();
    void itemRemoveAll();
    void killAndMakeList();
    void animationEnd();
    void rebuildList();
};

#endif // CHROME_H
