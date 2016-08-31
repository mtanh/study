#ifndef STANDARDMODEL_H
#define STANDARDMODEL_H

#include <QStandardItemModel>

class StandardModel: public QStandardItemModel
{
public:
    StandardModel( QObject* parent = 0 );

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
};

#endif // STANDARDMODEL_H
