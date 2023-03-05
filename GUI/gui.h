#ifndef GUI_H
#define GUI_H

#include <QGridLayout>
#include <QSplitter>
#include <QWidget>

#include "bottomPanel.h"
#include "fileBar.h"
#include "sidePanel.h"
#include "statusBar.h"
#include "view.h"

class GUI : public QWidget {
    Q_OBJECT
public:
    explicit GUI(QWidget *parent = nullptr);
private:
    QGridLayout *gridLayout;
    QSplitter *hSplitter;
    QSplitter *vSplitter;
    BottomPanel *bottomPanel;
    FileBar *fileBar;
    SidePanel *sidePanel;
    StatusBar *statusBar;
    View *view;
public slots:
signals:
};


#endif //GUI_H
