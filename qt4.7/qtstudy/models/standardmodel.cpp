#include "standardmodel.h"

StandardModel::StandardModel( QObject *parent )
    : QStandardItemModel( parent )
{
}

QVariant StandardModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole )
    {
        return QVariant();
    }

    if( orientation == Qt::Horizontal )
    {
        switch( section )
        {
        case 0:
            return "!";
            break;
        case 1:
            return "@";
            break;
        case 2:
            return "#";
            break;
        default:
            break;
        }
    }
    else
    {
        switch( section )
        {
        case 0:
            return "A";
            break;
        case 1:
            return "B";
            break;
        case 2:
            return "C";
            break;
        default:
            return "X";
            break;
        }
    }
    return QVariant();
}
