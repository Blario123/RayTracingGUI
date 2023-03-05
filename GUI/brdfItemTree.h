#ifndef BRDFITEMTREE_H
#define BRDFITEMTREE_H

#include <QTreeWidget>

#include "brdf.h"

class BRDFItemTree : public QTreeWidget {
    Q_OBJECT
public:
    explicit BRDFItemTree(QWidget *parent = nullptr);
    ~BRDFItemTree() override = default;
public slots:
    void setList(QList<BRDF> &);
    void addItem(QTreeWidgetItem *);
    void delItem();
signals:
    void deleteAt(int);
};

#endif //BRDFITEMTREE_H
