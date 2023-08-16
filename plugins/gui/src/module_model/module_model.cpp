#include "gui/module_model/module_model.h"

#include "gui/module_model/module_item.h"

#include "gui/gui_globals.h"
#include "gui/gui_utils/graphics.h"
//#include "gui/ModuleModel/ModuleItem.h"
#include "gui/selection_details_widget/selection_details_icon_provider.h"

#include "hal_core/netlist/gate.h"
#include "hal_core/netlist/net.h"

namespace hal
{
    ModuleTreeItem::ModuleTreeItem(const u32 id, const TreeItemType type):
        mParent(nullptr),
        mId(id),
        mType(type),
        mHighlighted(false)
    {
        switch(type)
        {
        case TreeItemType::Module:
            mName = QString::fromStdString(gNetlist->get_module_by_id(id)->get_name());
            mColor = gNetlistRelay->getModuleColor(id);
            break;
        case TreeItemType::Gate:
            mName = QString::fromStdString(gNetlist->get_gate_by_id(id)->get_name());
            break;
        case TreeItemType::Net:
            mName = QString::fromStdString(gNetlist->get_net_by_id(id)->get_name());
            break;
        }
    }

    ModuleTreeItem::TreeItemType ModuleTreeItem::getType() const{
        return mType;
    }


    u32 ModuleTreeItem::id() const
    {
        return mId;
    }

    QVariant ModuleTreeItem::data(int column) const
    {
        // DEBUG CODE, USE STYLED DELEGATES OR SOMETHING
        if(column == 0)
            return mName;
        else if (column == 1)
            return mId;
        else if(column == 2)
        {
            switch(mType)
            {
                case TreeItemType::Module:
                {
                    Module* module = gNetlist->get_module_by_id(mId);
                    if(!module)
                        return QVariant();
                    return QString::fromStdString(module->get_type());
                }
                case TreeItemType::Gate:
                    Gate* gate = gNetlist->get_gate_by_id(mId);
                    if(!gate)
                        return QVariant();
                    return QString::fromStdString(gate->get_type()->get_name());
            }
        }
        return QVariant();
    }

    bool ModuleTreeItem::highlighted() const
    {
        return mHighlighted;
    }

    int ModuleTreeItem::row() const
    {
        if (mParent)
            return mParent->mChildItems.indexOf(const_cast<ModuleTreeItem*>(this));
        else
            return 0;
    }

    const ModuleTreeItem* ModuleTreeItem::constParent() const
    {
        return mParent;
    }

    void ModuleTreeItem::appendExistingChildIfAny(const QMap<u32,ModuleTreeItem*>& moduleMap)
    {
        if(mType != TreeItemType::Module) // only module can have children
            return;

        Module* m = gNetlist->get_module_by_id(mId);
        Q_ASSERT(m);
        for (Module* subm : m->get_submodules())
        {
            auto it = moduleMap.find(subm->get_id());
            if (it != moduleMap.constEnd())
            {
                ModuleTreeItem* childItem = it.value();
                appendChild(childItem);
                childItem->setParent(this);
            }
        }
    }

    int ModuleTreeItem::childCount() const
    {
        return mChildItems.count();
    }

    ModuleTreeItem* ModuleTreeItem::parent()
    {
        return mParent;
    }

    void ModuleTreeItem::setName(const QString& name)
    {
        mName = name;
    }

    void ModuleTreeItem::setColor(const QColor& color)
    {
        mColor = color;
    }

    QColor ModuleTreeItem::color() const
    {
        return mColor;
    }

    ModuleModel::ModuleModel(QObject* parent) : BaseTreeModel(parent)
    {
        setHeaderLabels(QStringList() << "Name" << "ID" << "Type");

    }


    QVariant ModuleModel::data(const QModelIndex& index, int role) const
    {
        if (!index.isValid())
            return QVariant();

        //ModuleItem* item = static_cast<ModuleItem*>(index.internalPointer());
        ModuleTreeItem* item = static_cast<ModuleTreeItem*>(getItemFromIndex(index));

        if (!item)
            return QVariant();

        switch (role)
        {
            case Qt::DecorationRole:
            {
                if (index.column() == 0)
                {
                    switch(item->getType()){
                        case ModuleTreeItem::TreeItemType::Module:
                            return QIcon(*SelectionDetailsIconProvider::instance()->getIcon(SelectionDetailsIconProvider::ModuleIcon, item->id()));
                        case ModuleTreeItem::TreeItemType::Gate:
                            return QIcon(*SelectionDetailsIconProvider::instance()->getIcon(SelectionDetailsIconProvider::GateIcon, item->id()));
                        case ModuleTreeItem::TreeItemType::Net:
                            return QIcon(*SelectionDetailsIconProvider::instance()->getIcon(SelectionDetailsIconProvider::NetIcon, item->id()));
                    }
                }
                break;
            }
            case Qt::DisplayRole:
            {
                return item->data(index.column());
            }
            case Qt::ForegroundRole:
            {
                if (item->highlighted())
                    return QColor(QColor(255, 221, 0));    // USE STYLESHEETS
                else
                    return QColor(QColor(255, 255, 255));    // USE STYLESHEETS
            }
            default:
                return QVariant();
        }
        return QVariant();
    }



    ModuleTreeItem* ModuleModel::getItem(const QModelIndex& index) const
    {
        if (index.isValid())
            return static_cast<ModuleTreeItem*>(index.internalPointer());
        else
            return nullptr;
    }

    QModelIndex ModuleModel::getIndex(const ModuleTreeItem* const item) const
    {
        assert(item);

        QVector<int> row_numbers;
        const ModuleTreeItem* current_item = item;

        while (current_item != mTopModuleItem)
        {
            row_numbers.append(current_item->row());
            current_item = current_item->constParent();
        }

        QModelIndex model_index = index(0, 0, QModelIndex());

        for (QVector<int>::const_reverse_iterator i = row_numbers.crbegin(); i != row_numbers.crend(); ++i)
            model_index = index(*i, 0, model_index);

        return model_index;
    }

    void ModuleModel::init()
    {
        setModuleColor(1, QColor(96, 110, 112));
        ModuleTreeItem* item = new ModuleTreeItem(1);
        mModuleMap.insert(1, item);

        beginInsertRows(index(0, 0, QModelIndex()), 0, 0);
        mTopModuleItem = item;
        endInsertRows();

        // This is broken because it can attempt to insert a child before its parent
        // which will cause an assertion failure and then crash

        // std::set<Module*> s = gNetlist->get_modules();
        // s.erase(gNetlist->get_top_module());
        // for (Module* m : s)
        //     addModule(m->get_id(), m->get_parent_module()->get_id());

        // This works

        // recursively insert modules
        Module* m = gNetlist->get_top_module();
        QSet<u32> added_nets;
        addRecursively(m->get_submodules(), added_nets);
        // add remaining gates and modules
        for(auto g : m->get_gates())
            addGate(g->get_id(), 1);
        for(auto n : m->get_internal_nets()){
            int size = added_nets.size();
            added_nets.insert(n->get_id());
            if(added_nets.size() > size)
                addNet(n->get_id(), m->get_id());
        }
    }

    void ModuleModel::clear()
    {
        beginResetModel();

        mTopModuleItem = nullptr;

        for (ModuleTreeItem* m : mModuleMap)
            delete m;
        for (ModuleTreeItem* g : mGateMap)
            delete g;
        for (ModuleTreeItem* n : mNetMap)
            delete n;

        mModuleMap.clear();
        mGateMap.clear();
        mNetMap.clear();
        mModuleColors.clear();

        endResetModel();
    }

    void ModuleModel::addModule(u32 id, u32 parent_module)
    {
        assert(gNetlist->get_module_by_id(id));
        assert(gNetlist->get_module_by_id(parent_module));
        assert(!mModuleMap.contains(id));
        assert(mModuleMap.contains(parent_module));

        ModuleTreeItem* item   = new ModuleTreeItem(id);
        item->appendExistingChildIfAny(mModuleMap);
        ModuleTreeItem* parent = mModuleMap.value(parent_module);

        item->setParent(parent);
        mModuleMap.insert(id, item);

        QModelIndex index = getIndex(parent);

        int row = parent->childCount();
        mIsModifying = true;
        beginInsertRows(index, row, row);
        parent->insertChild(row, item);
        mIsModifying = false;
        endInsertRows();
    }

    void ModuleModel::addGate(u32 id, u32 parent_module)
    {
        assert(gNetlist->get_gate_by_id(id));
        assert(gNetlist->get_module_by_id(parent_module));
        assert(!mGateMap.contains(id));
        assert(mModuleMap.contains(parent_module));
        ModuleTreeItem* item   = new ModuleTreeItem(id, ModuleTreeItem::TreeItemType::Gate);
        //item->appendExistingChildIfAny(mModuleMap);
        ModuleTreeItem* parent = mModuleMap.value(parent_module);

        item->setParent(parent);
        mGateMap.insert(id, item);

        QModelIndex index = getIndex(parent);

        int row = parent->childCount();
        mIsModifying = true;
        beginInsertRows(index, row, row);
        parent->insertChild(row, item);
        mIsModifying = false;
        endInsertRows();
    }


    void ModuleModel::addNet(u32 id, u32 parent_module)
    {
        assert(gNetlist->get_net_by_id(id));
        assert(gNetlist->get_module_by_id(parent_module));
        assert(!mNetMap.contains(id));
        assert(mModuleMap.contains(parent_module));

        ModuleTreeItem* item   = new ModuleTreeItem(id, ModuleTreeItem::TreeItemType::Net);
        //item->appendExistingChildIfAny(mModuleMap);
        ModuleTreeItem* parent = mModuleMap.value(parent_module);

        item->setParent(parent);
        mNetMap.insert(id, item);

        QModelIndex index = getIndex(parent);

        int row = parent->childCount();
        mIsModifying = true;
        beginInsertRows(index, row, row);
        parent->insertChild(row, item);
        mIsModifying = false;
        endInsertRows();
    }

    void ModuleModel::addRecursively(const std::vector<Module*>& modules, QSet<u32>& added_nets)
    {
        for (auto &m : modules)
        {
            addModule(m->get_id(), m->get_parent_module()->get_id());
            addRecursively(m->get_submodules(), added_nets);

            for(auto &g : m->get_gates())
                addGate(g->get_id(), m->get_id());
            for(auto &n : m->get_internal_nets())
            {
                int size = added_nets.size();
                added_nets.insert(n->get_id());
                if(added_nets.size() > size)
                    addNet(n->get_id(), m->get_id());
            }
        }
    }

    void ModuleModel::remove_module(const u32 id)
    {
        assert(id != 1);
        assert(gNetlist->get_module_by_id(id));
        assert(mModuleMap.contains(id));

        ModuleTreeItem* item   = mModuleMap.value(id);
        ModuleTreeItem* parent = item->parent();
        assert(item);
        assert(parent);

        QModelIndex index = getIndex(parent);

        int row = item->row();

        mIsModifying = true;
        beginRemoveRows(index, row, row);
        parent->removeChild(item);
        mIsModifying = false;
        endRemoveRows();

        mModuleMap.remove(id);
        delete item;
    }

    void ModuleModel::remove_gate(const u32 id)
    {
        assert(gNetlist->get_gate_by_id(id));
        assert(mGateMap.contains(id));

        ModuleTreeItem* item   = mGateMap.value(id);
        ModuleTreeItem* parent = item->parent();
        assert(item);
        assert(parent);

        QModelIndex index = getIndex(parent);

        int row = item->row();

        mIsModifying = true;
        beginRemoveRows(index, row, row);
        parent->removeChild(item);
        mIsModifying = false;
        endRemoveRows();

        mGateMap.remove(id);
        delete item;
    }

    void ModuleModel::remove_net(const u32 id)
    {
        assert(gNetlist->get_net_by_id(id));
        assert(mModuleMap.contains(id));

        ModuleTreeItem* item   = mNetMap.value(id);
        ModuleTreeItem* parent = item->parent();
        assert(item);
        assert(parent);

        QModelIndex index = getIndex(parent);

        int row = item->row();

        mIsModifying = true;
        beginRemoveRows(index, row, row);
        parent->removeChild(item);
        mIsModifying = false;
        endRemoveRows();

        mNetMap.remove(id);
        delete item;
    }

    void ModuleModel::updateModule(u32 id)    // SPLIT ???
    {
        assert(gNetlist->get_module_by_id(id));
        assert(mModuleMap.contains(id));

        ModuleTreeItem* item = mModuleMap.value(id);
        assert(item);

        item->setName(QString::fromStdString(gNetlist->get_module_by_id(id)->get_name()));    // REMOVE & ADD AGAIN
        item->setColor(gNetlistRelay->getModuleColor(id));

        QModelIndex index = getIndex(item);
        Q_EMIT dataChanged(index, index);
    }

    ModuleTreeItem* ModuleModel::getItem(u32 id, ModuleTreeItem::TreeItemType type) const
    {
        return mModuleItemMaps[(int)type]->value(id);
    }

    QColor ModuleModel::moduleColor(u32 id) const
    {
        return mModuleColors.value(id);
    }

    QColor ModuleModel::setModuleColor(u32 id, const QColor& col)
    {
        QColor retval = mModuleColors.value(id);
        mModuleColors[id] = col;
        return retval;
    }

    QColor ModuleModel::setRandomColor(u32 id)
    {
        QColor retval = mModuleColors.value(id);
        mModuleColors.insert(id,gui_utility::getRandomColor());
        return retval;
    }

    void ModuleModel::removeColor(u32 id)
    {
        mModuleColors.remove(id);
    }

    bool ModuleModel::isModifying()
    {
        return mIsModifying;
    }



}
