#include <QDebug>
#include <QStandardItem>
#include <QSortFilterProxyModel>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "models/standardmodel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_tableModel = new StandardModel();

    QSortFilterProxyModel *proxy = new QSortFilterProxyModel();
    proxy->setSourceModel( m_tableModel );

    ui->tableView->setModel( proxy );
    ui->tableView->setSortingEnabled( true );

    QList<QStandardItem*> items;
    items << new QStandardItem("5");
    items << new QStandardItem("10");
    items << new QStandardItem("15");

    QList<QStandardItem*> items1;
    items1 << new QStandardItem("2");
    items1 << new QStandardItem("4");
    items1 << new QStandardItem("6");

    m_tableModel->appendRow( items );
    m_tableModel->appendRow( items1 );

    connect(ui->tableView->horizontalHeader(),
            SIGNAL(sectionClicked(int)),
            ui->tableView, SLOT(sortByColumn(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

