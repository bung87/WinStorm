#ifndef FIREFOX_H
#define FIREFOX_H

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
class Firefox : public QWidget
{
    Q_OBJECT
public:
    explicit Firefox(QWidget *parent = 0);
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
    bool testproces(QString p="firefox.exe");
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

#endif // FIREFOX_H
