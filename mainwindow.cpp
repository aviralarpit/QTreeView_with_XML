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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      model(new DomModel(QDomDocument(), this)),
      view(new QTreeView(this))
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open..."), this, &MainWindow::openFile, QKeySequence::Open);
    fileMenu->addAction(tr("E&xit"), this, &QWidget::close, QKeySequence::Quit);

    view->setModel(model);

    view->setSelectionMode(QAbstractItemView::MultiSelection);
    setCentralWidget(view);
    setWindowTitle(tr("QTreeViewXML"));

}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
        xmlPath, tr("XML files (*.xml);;HTML files (*.html);;"
                    "SVG files (*.svg);;User Interface files (*.ui)"));

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
