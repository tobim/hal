#include "vcd_viewer/wave_tree_model.h"
#include "netlist_simulator_controller/wave_data.h"
#include <QApplication>
#include <QFont>
#include <QMimeData>
#include <QDebug>
#include <QAction>
#include <stdlib.h>

namespace hal {

    const char* WaveTreeModel::sStateColor[3] = {"#707071", "#102080", "#802010"};


    WaveTreeModel::WaveTreeModel(WaveDataList *wdlist, QObject *obj)
        : QAbstractItemModel(obj), mWaveDataList(wdlist),
          mCursorPosition(0), mIgnoreSignals(false)
    {

        mRoot = new WaveDataRoot(mWaveDataList);

        /*
        for (int i=100; i<104; i++)
            mRoot->append(new WaveTreeItem( i, QString("item%1").arg(i) ));

        for (int i=0; i<3; i++)
        {
            WaveTreeGroup* wtg = new WaveTreeGroup(i+1, QString("group%1").arg(i+1));
            for (int j=0; j<4; j++)
                wtg->append(new WaveTreeItem( (i+1)*10+j, QString("gitem%1").arg((i+1)*10+j) ));
            mRoot->append(wtg);
        }
        for (int i=104; i<108; i++)
            mRoot->append(new WaveTreeItem( i, QString("item%1").arg(i) ));
            */
    }

    WaveData *WaveTreeModel::item(const QModelIndex& index) const
    {
        if (!index.isValid()) return nullptr;
        WaveDataGroup* grp = static_cast<WaveDataGroup*>(index.internalPointer());
        if (!grp) return mRoot;
        return grp->childAt(index.row());
    }

    QModelIndex WaveTreeModel::index(int row, int column, const QModelIndex &parent) const
    {
        WaveData* wd = item(parent);
        if (!wd) return createIndex(row,0,mRoot);
        WaveDataGroup* grp = dynamic_cast<WaveDataGroup*>(wd);
        if (!grp || row >= grp->size()) return QModelIndex();
        return createIndex(row,column,grp);
    }

    QModelIndexList WaveTreeModel::indexes(const WaveData* wd) const
    {
        QModelIndexList retval;
        int rootRow = 0;
        for (WaveData* rootChild : mRoot->children())
        {
            if (rootChild == wd)
                retval.append(createIndex(rootRow,0,mRoot));
            else
            {
                WaveDataGroup* grp = dynamic_cast<WaveDataGroup*>(rootChild);
                if (grp)
                {
                    int groupRow = 0;
                    for (const WaveData* grpChild : grp->children())
                    {
                        if (grpChild == wd)
                            retval.append(createIndex(groupRow,0,grp));
                        groupRow++;
                    }
                }
            }
            rootRow++;
        }
        return retval;
    }

    QModelIndexList WaveTreeModel::indexes(const QSet<u32>& netIds) const
    {
        QModelIndexList retval;
        int rootRow = 0;
        for (WaveData* rootChild : mRoot->children())
        {
            WaveDataGroup* grp = dynamic_cast<WaveDataGroup*>(rootChild);
            if (grp)
            {
                int groupRow = 0;
                for (const WaveData* grpChild : grp->children())
                {
                    if (netIds.contains(grpChild->id()))
                        for (int icol=0; icol<3; icol++)
                            retval.append(createIndex(groupRow,0,grp));
                    groupRow++;
                }
            }
            else
            {
                if (netIds.contains(rootChild->id()))
                    for (int icol=0; icol<3; icol++)
                        retval.append(createIndex(rootRow,0,mRoot));
            }
            rootRow++;
        }
        return retval;
    }

    void WaveTreeModel::handleGroupAdded(int grpId)
    {
        if (mIgnoreSignals) return;
        WaveDataGroup* grp = mWaveDataList->mDataGroups.value(grpId);
        if (!grp) return;
        insertGroup(createIndex(mRoot->size(),0,mRoot),grp);
    }

    void WaveTreeModel::handleWaveAdded(int iwave)
    {
        WaveData* wd = mWaveDataList->at(iwave);
        insertItem(mRoot->size(),createIndex(0,0,nullptr),wd);
    }

    void WaveTreeModel::handleWaveMovedToGroup(int iwave, WaveDataGroup* grp)
    {
        WaveData* wd = mWaveDataList->at(iwave);
        for (QModelIndex inx : indexes(wd))
        {
            if (inx.internalPointer() == grp) continue;
            removeItem(inx.row(),inx.parent());
        }
        Q_EMIT triggerReorder();
    }

    QVariant WaveTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (orientation != Qt::Horizontal) return QVariant();
        if (role == Qt::SizeHintRole)
            return QSize(400,28);
        if (role != Qt::DisplayRole) return QVariant();
        switch (section)
        {
        case 0: return "Name";
        case 1: return "ID";
        case 2: return "Value";
        }
        return QVariant();
    }

    QVariant WaveTreeModel::data(const QModelIndex &index, int role) const
    {
        switch (role)
        {
        case Qt::FontRole:
        {
            QFont font = qApp->font();
            if (!isLeaveItem(index) || index.column() == 2)
            {
                font.setPixelSize(14);
                font.setBold(true);
            }
            return font;
        }
        case Qt::SizeHintRole:
            return QSize(400,28);
        case Qt::TextAlignmentRole:
            if (!index.column())
                return Qt::AlignLeft;
            return Qt::AlignRight;
        case Qt::ForegroundRole:
            if (index.column() != 2) return QVariant();
            return QColor(Qt::white);
        case Qt::BackgroundRole:
        {
            if (index.column() != 2) return QVariant();
            WaveData* wd = item(index);
            int v = wd->intValue(mCursorPosition);
            if (v<-1) v=-1;
            if (v>1) v=1;
            return QColor(sStateColor[v+1]);
        }
        case Qt::DisplayRole:
        {
            WaveData* wd = item(index);
            if (!wd) return QVariant();
            switch (index.column())
            {
            case 0:
                return wd->name();
            case 1:
                if (wd->id() < 1)
                    return QString();
                return QString::number(wd->id());
            case 2:
                return wd->strValue(mCursorPosition);
            }
        }
        default:
                break;
        }

        return QVariant();
    }

    int WaveTreeModel::waveIndex(const QModelIndex& index) const
    {
         WaveData* wd = item(index);
         if (!wd) return -1;
         if (dynamic_cast<WaveDataGroup*>(wd)) return -1;
         return mWaveDataList->waveIndexByNetId(wd->id());
    }

    int WaveTreeModel::groupId(const QModelIndex& grpIndex) const
    {
        WaveDataGroup* grp = dynamic_cast<WaveDataGroup*>(item(grpIndex));
        if (!grp) return -1;
        return grp->id();
    }

    QString WaveTreeModel::netName(const QModelIndex &index) const
    {
        WaveData* wd = item(index);
        if (!wd) return QString();
        return wd->name();
    }

    int WaveTreeModel::rowCount(const QModelIndex &parent) const
    {
        if (!parent.isValid())
            return mRoot->size();
        WaveData* wd = item(parent);
        if (!wd) return 0;
        WaveDataGroup* grp = dynamic_cast<WaveDataGroup*>(wd);
        if (!grp) return 0;
        return grp->size();
    }

    int WaveTreeModel::columnCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);
        return 3;
    }

    QModelIndex WaveTreeModel::parent(const QModelIndex &child) const
    {
        if (!child.isValid()) return QModelIndex();
        WaveDataGroup* grp = static_cast<WaveDataGroup*>(child.internalPointer());
        if (!grp) return QModelIndex();
        if (grp == mRoot)
            return createIndex(0,0,nullptr);

        int n = mRoot->size();
        for (int i=0; i<n; i++)
        {
            if (mRoot->childAt(i) == grp)
            {
                return createIndex(i,0,mRoot);
            }
        }
        return QModelIndex();
    }

    Qt::DropActions WaveTreeModel::supportedDragActions() const
    {
        return Qt::MoveAction | Qt::CopyAction;
    }

    Qt::ItemFlags WaveTreeModel::flags(const QModelIndex &index) const
    {
        Qt::ItemFlags retval = Qt::ItemIsDropEnabled | Qt:: ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        if (!index.isValid()) return retval;
        if (item(index)->bits()>1) return retval;
        if (isLeaveItem(index)) return retval | Qt::ItemIsDragEnabled | Qt::ItemNeverHasChildren;
        return retval;
    }

    void WaveTreeModel::dropRow(const QModelIndex& parentTo, int row)
    {
        QModelIndex parentFrom = mDragIndex.parent();
        int targetRow = (parentTo == parentFrom && mDragIndex.row() < row) ? row-1 : row;
        QModelIndex targetIndex = parentTo;
        if (parentTo.internalPointer() == mDragIndex.internalPointer() && mDragIndex.row() < parentTo.row())
            targetIndex = createIndex(parentTo.row()-1,0,parentTo.internalPointer());
        WaveData* wd = removeItem(mDragIndex.row(),parentFrom);
        if (!wd) return;
        insertItem(targetRow,targetIndex,wd);
        Q_EMIT triggerReorder();
    }

    void WaveTreeModel::handleCursorMoved(float xpos)
    {
        mCursorPosition = xpos;
        QModelIndex i0 = createIndex(0,2,mRoot);
        QModelIndex i1 = createIndex(mRoot->size()-1,2,mRoot);
        Q_EMIT dataChanged(i0,i1);
    }

    void WaveTreeModel::handleUpdateValueFormat()
    {
        QModelIndex i0 = createIndex(0,2,mRoot);
        QModelIndex i1 = createIndex(mRoot->size()-1,2,mRoot);
        Q_EMIT dataChanged(i0,i1);
    }

    bool WaveTreeModel::dropMimeData(const QMimeData *mimeData, Qt::DropAction action, int row, int column, const QModelIndex &dropParent)
    {
        Q_UNUSED(action);
        Q_UNUSED(column);
        if (!dropParent.isValid()) return false;
        if (!mimeData->formats().contains("application/x-qabstractitemmodeldatalist")) return false;
        if (isLeaveItem(dropParent))
        {
            WaveData* wd = item(dropParent);
            WaveDataGroup* grp = static_cast<WaveDataGroup*>(dropParent.internalPointer());
            int n=grp->size();
            for (int i=0; i<n; i++)
                if (grp->childAt(i) == wd)
                {
                    dropRow(dropParent.parent(),i+1);
                    return true;
                }
            return false;
        }
        if (dropParent.internalPointer() == mRoot)
        {
            dropRow(dropParent,row);
            return true;
        }
        return false;
    }

    bool WaveTreeModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
    {
        Q_UNUSED(action);
        Q_UNUSED(row);
        Q_UNUSED(column);
        if (!parent.isValid()) return false;
        if (!data->formats().contains("application/x-qabstractitemmodeldatalist")) return false;
        if (isLeaveItem(parent)) return true;
        if (parent.internalPointer() == mRoot) return true;
        return false;
    }

    bool WaveTreeModel::isLeaveItem(const QModelIndex &index) const
    {
        WaveData* wd = item(index);
        if (!wd) return false;
        return dynamic_cast<WaveDataGroup*>(wd)==nullptr;
    }

    bool WaveTreeModel::insertItem(int row, const QModelIndex &parent, WaveData *wd)
    {
        if (!parent.isValid()) return false;
        WaveDataGroup* grp = dynamic_cast<WaveDataGroup*>(item(parent));
        if (!grp) return false;
        if (row < 0) row = 0;
      //  beginInsertRows(parent,row,row);
        beginResetModel();
        if (row > grp->size()) row = grp->size();
        grp->insert(row,wd);
      //  endInsertRows();
        endResetModel();
        Q_EMIT inserted(index(row,0,parent));
//        Q_EMIT indexInserted(itm->waveIndex(),false);
        invalidateParent(parent);
        if (grp != mRoot) grp->recalcData();
        return true;
    }

    void WaveTreeModel::invalidateParent(const QModelIndex &parentRow)
    {
        QModelIndex parentValueInx = createIndex(parentRow.row(),2,parentRow.internalPointer());
        Q_EMIT dataChanged(parentValueInx,parentValueInx);
    }

    WaveData *WaveTreeModel::removeItem(int row, const QModelIndex &parent)
    {
        if (!parent.isValid()) return nullptr;
        WaveDataGroup* grp = dynamic_cast<WaveDataGroup*>(item(parent));
        if (!grp) return nullptr;
        beginRemoveRows(parent,row,row);
        WaveData* wd = grp->removeAt(row);
        endRemoveRows();
        invalidateParent(parent);
        grp->recalcData();
        int iwave = mWaveDataList->waveIndexByNetId(wd->id());
        Q_EMIT indexRemoved(iwave,false);
        return mWaveDataList->at(iwave);
    }

    void WaveTreeModel::removeGroup(const QModelIndex& groupIndex)
    {
        if (groupIndex.internalPointer() != mRoot) return;
        int irow = groupIndex.row();
        WaveDataGroup* grp = dynamic_cast<WaveDataGroup*>(mRoot->childAt(irow));
        mWaveDataList->removeGroup(grp->id());
    }

    void WaveTreeModel::handleGroupAboutToBeRemoved(WaveDataGroup* grp)
    {
        if (!grp) return;
        int irow = mRoot->childIndex(grp);
        if (irow<0) return;
        beginResetModel();
        mRoot->removeAt(irow);
        if (!grp->isEmpty())
        {
            int n = grp->size() - 1;
            for (int i=n; i>=0; i--)
                mRoot->insert(irow,grp->childAt(i));
        }
        endResetModel();
        Q_EMIT indexRemoved(grp->id(),true);
        Q_EMIT triggerReorder();
    }

    void WaveTreeModel::insertGroup(const QModelIndex &groupIndex, WaveDataGroup* grp)
    {
         if (groupIndex.internalPointer() != mRoot) return;
         mIgnoreSignals = true;
         if (!grp) grp = new WaveDataGroup(mWaveDataList);
         beginResetModel();
         insertItem(groupIndex.row(),groupIndex.parent(),grp);
         endResetModel();
         mIgnoreSignals = false;
         grp->recalcData();
    }

    // ---- WaveDataRoot

    QSet<int> WaveTreeModel::waveDataIndexSet() const
    {
        QSet<int> retval;
        for (const WaveData* wd : mRoot->children())
        {
            const WaveDataGroup* grp = dynamic_cast<const WaveDataGroup*>(wd);
            if (grp)
            {
                for (const WaveData* wdGrp : grp->children())
                {
                    int iwave = mWaveDataList->waveIndexByNetId(wdGrp->id());
                    if (iwave >= 0) retval.insert(iwave);
                }
            }
            else
            {
                int iwave = mWaveDataList->waveIndexByNetId(wd->id());
                if (iwave >= 0) retval.insert(iwave);
            }
        }
        return retval;
    }

}
