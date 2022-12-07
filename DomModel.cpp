/*
******************************************************************************
* License Information: Accord Global Technology Solutions Private Limited.
* 72 & 73, Krishna Reddy Colony, Domlur layout
* Bangalore - 560071, INDIA
* Licensed software and all rights reserved.
******************************************************************************
* File:
*
* Description:
*
* Compiler:
*
* Compiler options:
*
* Pragma:
*
* H/W platform:
*
* Portability:
*
* Author(s):            Arpit K @ AGTSPL
*
* Classes:
*
* References:
*
* Version History:
* <Version Number> <Author> <date> <defect Number> <Modification made
* and reason
* for modification>
* 1.1
*****************************************************************************/


#include "DomModel.h"
#include "DOMItem.h"
//#include "mainwindow.h"
#include <QtXml>


//! [0]
DomModel::DomModel(const QDomDocument &document, QObject *parent)
    : QAbstractItemModel(parent),
      domDocument(document),
      rootItem(new DomItem(domDocument, 0))
{
}
//! [0]

//! [1]
DomModel::~DomModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int DomModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}
//! [2]



QVariant DomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    DomItem *item = static_cast<DomItem*>(index.internalPointer());
    const QDomNode node = item->node();

    if ( role == Qt::CheckStateRole && (index.column() == 0) && hasChildren(index) )
    {
        return static_cast< int >( item->isChecked() ? Qt::Checked : Qt::Unchecked );
    }
    if (role == Qt::FontRole && item->isChecked()) {
            QFont font;
            font.setBold(true);
            return font;
    }
    if (role != Qt::DisplayRole)
        return QVariant();

    switch (index.column()) {
        case 0:
            return node.nodeName();
        case 1:
        {
            const QDomNamedNodeMap attributeMap = node.attributes();
            QStringList attributes;
            for (int i = 0; i < attributeMap.count(); ++i) {
                QDomNode attribute = attributeMap.item(i);
                attributes << attribute.nodeName() + "=\""
                              + attribute.nodeValue() + '"';
            }
            return attributes.join(' ');
        }
        case 2:
            return node.nodeValue().split('\n').join(' ');
        default:
            break;

    }

    return item->data(index.column());
}


Qt::ItemFlags DomModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if ( index.column() == 0 )
        flags |= Qt::ItemIsUserCheckable;
    return flags;
}
//! [6]
QVariant DomModel::headerData(int section, Qt::Orientation orientation,
                              int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Attributes");
            case 2:
                return tr("Value");
            default:
                break;
        }
    }
    return QVariant();
}
//! [6]

//! [7]
QModelIndex DomModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    DomItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<DomItem*>(parent.internalPointer());
//! [7]

//! [8]
    DomItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}
//! [8]

//! [9]
QModelIndex DomModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
    DomItem *parentItem = childItem->parent();

    if (!parentItem || parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
//! [9]

//! [10]
int DomModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    DomItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<DomItem*>(parent.internalPointer());

    return parentItem->node().childNodes().count();
}
//! [10]
//!
bool DomModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    DomItem *item = static_cast<DomItem*>(index.internalPointer());

    if (index.column() == 0 ){
        if (role == Qt::EditRole) {
            return false;
        }
        if (role == Qt::CheckStateRole) {
            item->setChecked(value.toBool());
            emit dataChanged(index, index);
            return true;
        }
    }
    return QAbstractItemModel::setData(index, value, role);
}
