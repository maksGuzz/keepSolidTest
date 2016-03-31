#include "treemodel.h"
#include "treeitem.h"

#include <QStringList>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "sendrcvjob.h"

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    rootItem = new TreeItem("ROOT");//placeholder, invisible in the treeview
    m_seq = 0;
    //m_authToken = "17c82f04-2d6f-42db-92d2-343b80fc0a50";
}


TreeModel::~TreeModel()
{
    delete rootItem;
}


TreeItem* TreeModel::setupModelData(const QString &lines, TreeItem *parent)
{
    if(parent==NULL)
    {
        parent = rootItem;
    }

    TreeItem *nti = new TreeItem(lines,parent);
    parent->appendChild(nti);

    emit layoutChanged();

    return nti;
}

SendRcvJob* TreeModel::prepareRequest()
{
    qDebug() << "getWGList";
    rpc::Request *rq = new rpc::Request();

    rq->set_is_debug(true);
    rq->set_message_type(RPC_WORKGROUPS_LIST);
    rq->set_service_type(1);

    rpc::WorkGroupsListRequest *wglrq = new rpc::WorkGroupsListRequest();
    wglrq->set_filter(rpc::ALL_ENTRIES);
    wglrq->set_session_id(m_authToken.toStdString());

    rq->set_allocated_workgroups_list(wglrq);

    qDebug() << rq->DebugString().c_str();

    SendRcvJob *j = new SendRcvJob();
    j->createRequest(QByteArray::fromStdString(rq->SerializeAsString()));
    j->m_seqSend = m_seq;

    return j;
}

void TreeModel::dataQuery()
{
    emit getData(prepareRequest());
}

void TreeModel::slJobFinished(SendRcvJob *job)
{
    qDebug() << "slJobFinished";
    if(!job)
    {
        m_seq = 0;
        qDebug() << "something wrong.. JOB is NULL || connection closed";
        return;
    }
    if(job->m_response.size()) // assume data ready
    {
        if(job->m_hasSeqNumRcvd)
        {
            m_seq = job->m_seqRcvd +1;
        }
        qDebug() << job->m_response;
        rpc::Response resp;
        if(!resp.ParseFromString(job->m_response.toStdString()))
        {
            qDebug() << "parsing error";
            delete job;
            return;
        }
        //qDebug() << resp.DebugString().c_str();
        //resp.ParseFromArray(job->m_response.data(), job->m_response.size());

        QString s = QString::fromStdString(resp.DebugString());
        qDebug() << s;
        if(resp.error_code() == 401)
        {
            emit sigGetToken();
        }
        else if(resp.error_code() == 200)
        {
            // cleanup
            /*delete rootItem;
            rootItem = new TreeItem("ROOT");
            resetInternalData();
            emit layoutChanged();*/
            //parse
            if(resp.has_workgroups_list())
            {
                QMap<QString, QVariantMap> lists, tasks;
                rpc::WorkGroupsListResponse list = resp.workgroups_list();
                int sz = list.workgroup_info_list_size();
                for(int i = 0; i< sz; ++i)
                {
                    rpc::WorkGroupInfo info = list.workgroup_info_list(i);

                    QJsonDocument d = QJsonDocument::fromJson(info.workgroup_metadata().c_str());

                    if(!d.isObject())
                    {
                        qDebug() << "something wrong with json ((";
                        continue;
                    }
                    QVariantMap metadata = d.object().toVariantMap();
                    //QString token = respmap.value("session", QString("")).toString();
                    QString wgname = QString::fromStdString(info.workgroup_name());

                    if(info.workgroup_type() == 1001)//task
                    {
                        tasks[wgname] = metadata;
                    }
                    else if(info.workgroup_type() == 1002)//task list
                    {
                        // check if list is empty
                        if(lists.contains(wgname)) // then append
                        {
                            QVariantMap meta = lists[wgname];
                            QVariantList tl = meta.value("tasks",QVariantList()).toList();
                            QVariantList tl1 = metadata.value("tasks",QVariantList()).toList();
                            tl<<tl1;
                            meta["tasks"] = tl;
                            lists[wgname] = meta;
                        }
                        else
                        {
                            lists[wgname] = metadata;
                        }

                    }
                }
                //iterate over lists and append tasks
                foreach (QVariantMap t, lists)
                {
                    QString name = t.value("title", QString()).toString();
                    if(name.isEmpty())
                    {
                        continue;
                    }
                    TreeItem *i = setupModelData( name );
                    i->setType(1002);
                    QVariantList tl = t.value("tasks",QVariantList()).toList();
                    foreach (QVariant t, tl)
                    {
                        QString tid = t.toString();
                        if(tid.isEmpty())
                        {
                            continue;
                        }
                        if(!tasks.contains(tid))
                        {
                            continue;
                        }
                        QVariantMap task = tasks[tid];
                        QString tn = task.value("title",QString()).toString();
                        TreeItem *t1 = setupModelData( tn, i );
                        t1->setType(1001);
                        t1->setMetaData(task);
                    }
                }
            }
            else
            {
                qDebug() << "workGroupList is empty";
            }


        }
        else qDebug() << "UNHANDLED response";
    }
    delete job;
}

void TreeModel::setAuthToken(const QString &token)
{
    qDebug() << "setAuthToken" << token;
    m_authToken = token;
    dataQuery();
}

void TreeModel::activated(const QModelIndex &index)
{
    qDebug() << "=========ACTIVATED!===========" << index.data();
    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    QVariantMap meta = item->getMetaData();
    if(item->getType() == 1002)//list
    {
        qDebug() << "tasklist, only add new task";
        meta.insert("type",QVariant(1002));
    }
    else
    {
        qDebug() << "task. parse and show. can delete, edit...";
        meta.insert("type",QVariant(1001));
    }

    qDebug() << meta;
    emit setInfo(meta);
}


int TreeModel::columnCount(const QModelIndex &index) const
{
    int val;
    if (index.isValid())
        val = static_cast<TreeItem*>(index.internalPointer())->columnCount();
    else
        val = rootItem->columnCount();
    return val;
}


int TreeModel::rowCount(const QModelIndex &index) const
{
    int val;
    TreeItem *parentItem;
    if (index.column() > 0)
        return 0;

    if (!index.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(index.internalPointer());

    val = parentItem->childCount();
    return val;
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}


Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}


QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &index) const
{
    if (!hasIndex(row, column, index))
    {
        return QModelIndex();
    }

    TreeItem *parentItem;

    if (!index.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(index.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}


QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());

    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
    {
        return QModelIndex();
    }
    if(parentItem==NULL)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}


