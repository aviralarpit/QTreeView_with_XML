#include "DOMItem.h"
#include<QCheckBox>
#include <QtXml>

//! [0]
DomItem::DomItem(const QDomNode &node, int row, DomItem *parent)
    : domNode(node),
//! [0]
      // Record the item's location within its parent.
//! [1]
      parentItem(parent),
      rowNumber(row)
{}
//! [1]

//! [2]
DomItem::~DomItem()
{
    qDeleteAll(childItems);
}
//! [2]

//! [3]
QDomNode DomItem::node() const
{
    return domNode;
}
//! [3]

//! [4]
DomItem *DomItem::parent()
{
    return parentItem;
}
//! [4]

//! [5]
DomItem *DomItem::child(int i)
{
    DomItem *childItem = childItems.value(i);
    if (childItem)
        return childItem;

    // if child does not yet exist, create it
    if (i >= 0 && i < domNode.childNodes().count()) {
        QDomNode childNode = domNode.childNodes().item(i);
        childItem = new DomItem(childNode, i, this);
        childItems[i] = childItem;
    }
    return childItem;
}
//! [5]

//! [6]
int DomItem::row() const
{
    return rowNumber;
}
//! [6]
QVariant DomItem::data(int column) const
{
    return itemData.value(column);
}
