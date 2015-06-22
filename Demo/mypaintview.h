#ifndef MYPAINTVIEW_H
#define MYPAINTVIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPushButton>
#include <QColorDialog>

#include "mphandler.h"
#include "mpbrush.h"
#include "mpsurface.h"
#include "mptile.h"


class MypaintView : public QGraphicsView
{
    Q_OBJECT

public:
    MypaintView();
    ~MypaintView();

private:

    QGraphicsScene              m_scene;
    QColor                      m_color;
    bool                        using_tablet;

protected:
    virtual void tabletEvent       ( QTabletEvent *event );
    virtual void mouseMoveEvent    ( QMouseEvent * event );
    virtual void mousePressEvent   ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent * event );

public slots:
//    void BrushSelected      (const QByteArray& content);
    void btnChgColorPressed();

    void onNewTile(MPSurface *surface, MPTile *tile);
    void onUpdateTile(MPSurface *surface, MPTile *tile);

};

#endif // MYPAINTVIEW_H
