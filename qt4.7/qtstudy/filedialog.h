#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QFileDialog>

class FileDialog: public QFileDialog
{
    Q_OBJECT

public:
    FileDialog(QWidget *parent = 0);
    ~FileDialog();

public slots:
    void onClose();
};

#endif // FILEDIALOG_H
