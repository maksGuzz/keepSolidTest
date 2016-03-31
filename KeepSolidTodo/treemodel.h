#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "../pbs_compiled/message.pb.h"

class TreeItem;
struct SendRcvJob;

class TreeModel : public QAbstractItemModel
{
Q_OBJECT

public:
    explicit TreeModel(QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &index = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &index = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &index = QModelIndex()) const Q_DECL_OVERRIDE;


    TreeItem *setupModelData(const QString &lines, TreeItem *parent=0);
    SendRcvJob *prepareRequest();
    void dataQuery();

signals:
    void getData(SendRcvJob *job);
    void sigGetToken();
    void setInfo(QVariantMap meta);

public slots:
    void slJobFinished(SendRcvJob *job);
    void setAuthToken(const QString &token);
    void activated(const QModelIndex & index);

private:
    TreeItem *rootItem;
    QString m_authToken;
    quint64 m_seq;
};

#endif // TREEMODEL_H
