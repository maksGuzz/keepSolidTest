#ifndef TREEITEM_H
#define TREEITEM_H


#include <QList>
#include <QVariant>

class TreeItem
{
public:
    explicit TreeItem(const QString &data, TreeItem *parentItem = 0);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QString data(int column) const;
    int row() const;
    TreeItem *parentItem();

private:
    QList<TreeItem*> m_childItems;
    QString m_itemData;
    TreeItem *m_parentItem;
};


#endif // TREEITEM_H