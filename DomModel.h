#ifndef DOMMODEL_H
#define DOMMODEL_H

#include <QAbstractItemModel>
#include<QDomDocument>
#include <QModelIndex>
#include<QAbstractItemView>
#include <QCheckBox>
class DomItem;

//! [0]
class DomModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit DomModel(const QDomDocument &document, QObject *parent = nullptr);
    ~DomModel();
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QModelIndex rootIndex() const;
private:
    QDomDocument domDocument;
    DomItem *rootItem;
};
//! [0]
#endif // DOMMODEL_H
