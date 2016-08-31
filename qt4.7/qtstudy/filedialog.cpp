#include <QDebug>
#include "filedialog.h"

FileDialog::FileDialog(QWidget *parent)
    : QFileDialog(parent)
{
}

FileDialog::~FileDialog()
{

}

void FileDialog::onClose()
{
    if( acceptMode() == QFileDialog::AcceptOpen ) {
        qDebug() << selectedFiles().at(0);
    }
}
