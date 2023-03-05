#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>

class View : public QWidget {
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    ~View() override = default;
    void resizeEvent(QResizeEvent *) override;
private:
    QGridLayout *layout;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QImage *image;
public slots:
    void renderImage();
signals:
    void sizeChanged(int, int);
};

#endif //VIEW_H
