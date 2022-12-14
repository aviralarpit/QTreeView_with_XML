/*
******************************************************************************
* License Information: Accord Global Technology Solutions Private Limited.
* 72 & 73, Krishna Reddy Colony, Domlur layout
* Bangalore - 560071, INDIA
* Licensed software and all rights reserved.
******************************************************************************
* File:
*
* Description:
*
* Compiler:
*
* Compiler options:
*
* Pragma:
*
* H/W platform:
*
* Portability:
*
* Author(s):            Arpit K @ AGTSPL
*
* Classes:
*
* References:
*
* Version History:
* <Version Number> <Author> <date> <defect Number> <Modification made
* and reason
* for modification>
* 1.1
*****************************************************************************/


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DomModel.h"
#include <QDomDocument>
#include <QTreeView>
#include <QMenuBar>
#include <QFileDialog>
#include<QToolBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      model(new DomModel(QDomDocument(), this)),
      view(new QTreeView(this))
{

    //fileMenu = menuBar()->addMenu(tr("&File"));
    //fileMenu->addAction(tr("&FIND"), this, &MainWindow::openFile, QKeySequence::Open);
    //fileMenu->addAction(tr("E&xit"), this, &QWidget::close, QKeySequence::Quit);

    //FIND Button Implementation
     QToolBar *fileToolBar = addToolBar(tr("FIND"));
     const QIcon newIcon = QIcon::fromTheme("FIND", QIcon("C:\\Users\\arpit.k\\Documents\\QT\\build-QTreeViewXML-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\FIND.png"));
     QAction *newAct = new QAction(newIcon, tr("&FIND"), this);
     newAct->setShortcuts(QKeySequence::Open);
     connect(newAct, &QAction::triggered, this, &MainWindow::openFile);
     fileToolBar->addAction(newAct);

     //Expand ALL Button Implementation

     const QIcon newIcon2 = QIcon::fromTheme("Expand", QIcon("C:\\Users\\arpit.k\\Documents\\QT\\build-QTreeViewXML-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\Expand.png"));
     QAction *newAct2 = new QAction(newIcon2, tr("&Expand"), this);
     newAct2->setShortcuts(QKeySequence::Open);
     connect(newAct2, &QAction::triggered, this,
             [this]{ view->expandAll(); });

     fileToolBar->addAction(newAct2);

    view->setModel(model);

    setCentralWidget(view);
    setWindowTitle(tr("QTreeViewXML"));

}

void MainWindow::openFile()
{
//    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
//        xmlPath, tr("XML files (*.xml);;HTML files (*.html);;"
//                    "SVG files (*.svg);;User Interface files (*.ui)"));

    QString filePath = QFileInfo("C:\\Users\\arpit.k\\Documents\\QT\\build-QTreeViewXML-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\Sample.xml").absoluteFilePath();

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            QDomDocument document;
            if (document.setContent(&file)) {
                DomModel *newModel = new DomModel(document, this);
                view->setModel(newModel);
                delete model;
                model = newModel;
                xmlPath = filePath;
            }
            file.close();
        }
    }
}
void MainWindow::expandChildren(const QModelIndex &index, QTreeView *view)
{
    if (!index.isValid()) {
        return;
    }

    int childItem = index.model()->rowCount(index);
    for (int i = 0; i < childItem; i++) {
        const QModelIndex &child = index.child(i, 0);
        // Recursively call the function for each child node.
        expandChildren(child, view);
    }

    if (!view->isExpanded(index)) {
        view->expand(index);
    }
}
