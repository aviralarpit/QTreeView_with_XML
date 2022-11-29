#ifndef DOMITEM_H
#define DOMITEM_H
#include <QDomNode>
#include <QHash>
#include<QVariant>
//! [0]
class DomItem
{
public:
    DomItem(const QDomNode &node, int row, DomItem *parent = nullptr);
    ~DomItem();
    DomItem *child(int i);
    DomItem *parent();
    QDomNode node() const;
    int row() const;
     QVariant data(int column) const;
    bool isChecked() const { return checked; }
    void setChecked( bool set ) { checked = set; }

private:
    QDomNode domNode;
    QHash<int, DomItem *> childItems;
    DomItem *parentItem;
    int rowNumber;
    bool checked;
     QList<QVariant> itemData;
};
//! [0]
#endif // DOMITEM_H
