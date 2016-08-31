#include <QtGui/QApplication>
#include <QLabel>
#include <QFile>
#include <QDataStream>
#include <QString>
#include <QDebug>
#include <QSet>
#include <QTableWidget>
#include <QHeaderView>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    QFile file("./test.dat");
    //    QString test("Hello");
    //    int iA = 10;
    //    int iB = 20;

    //    if ( file.open( QIODevice::WriteOnly | QIODevice::Truncate ) ) {

    //        QDataStream stream( &file );
    //        stream.setVersion(QDataStream::Qt_4_7);

    //        stream << test;
    //        stream << iB;
    //        stream << iA;
    //        file.close();
    //    }

    //    QFile file1("./test.dat");
    //    QString res("");
    //    int b = 0;
    //    if ( file1.open( QIODevice::ReadOnly ) ) {

    //        QDataStream stream( &file1 );
    //        stream.setVersion(QDataStream::Qt_4_7);

    //        stream >> res;
    //        stream >> b;
    //        file1.close();

    //        qDebug() << b;
    //    }



    MainWindow w;
    w.resize(800, 640);
    w.show();

    //    QTableWidget *m_pTableWidget = new QTableWidget();

    //    m_pTableWidget->setRowCount(2);
    //    m_pTableWidget->setColumnCount(2);

    //    //    m_pTableWidget->setHorizontalHeader(headerView);
    //    m_pTableWidget->setHorizontalHeaderLabels(QStringList()<<"#"<<"Name"<<"Text");

    //    QHeaderView *vHeader = new QHeaderView(Qt::Vertical, m_pTableWidget->horizontalHeader());

    //    m_pTableWidget->setVerticalHeader(vHeader);
    //    m_pTableWidget->setVerticalHeaderLabels(QStringList()<<"A"<<"B"<<"C");
    //    m_pTableWidget->verticalHeader()->setVisible(true);

    //    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //    m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //    m_pTableWidget->setShowGrid(false);
    //    m_pTableWidget->setShowGrid(true);

    //    m_pTableWidget->setItem(0, 1, new QTableWidgetItem("5"));
    //    m_pTableWidget->setItem(1, 1, new QTableWidgetItem("10"));
    //    QObject::connect( m_pTableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)),
    //                      m_pTableWidget, SLOT(sortByColumn(int)));
    //    QObject::connect( m_pTableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)),
    //                      m_pTableWidget->verticalHeader(), SLOT(setOffsetToSectionPosition(int)));

    //    m_pTableWidget->show();

    return a.exec();
}
