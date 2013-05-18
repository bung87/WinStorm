#ifndef TITLEBAR_H
#define TITLEBAR_H
#include <QObject>
#include <QtGui>
 #include <QToolButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLinearGradient>
#include <QMenu>
#include <QMessageBox>
class TitleBar : public  QWidget
{
    Q_OBJECT
public:
   explicit TitleBar(QWidget *parent = 0);
public slots:
    void aboutThis();
    void handleSingleClick();
    void showSmall();
    void showMaxRestore();
    void icon_Clicked();
protected:
    void mouseDoubleClickEvent();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
     QToolButton *con;
    int count;
    QTimer*  delayTimer;
    QToolButton *minimize;
    QToolButton *maximize;
    QToolButton *close;
    QPixmap restorePix, maxPix;
    bool maxNormal;
    QPoint startPos;
    QPoint clickPos;
};

#endif // TITLEBAR_H
