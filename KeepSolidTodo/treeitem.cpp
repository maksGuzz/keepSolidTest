#include <QStringList>

#include "treeitem.h"

TreeItem::TreeItem(const QString &data, TreeItem *parent)
{
    m_parentItem = parent;
    m_itemData = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return 1;
}

QString TreeItem::data(int column) const
{
    return m_itemData;
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

void TreeItem::setMetaData(const QVariantMap &metadata)
{
    m_metadata = metadata;
}

QVariantMap TreeItem::getMetaData() const
{
    return m_metadata;
}

void TreeItem::setType(int type)
{
    m_type = type;
}

int TreeItem::getType() const
{
    return m_type;
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

