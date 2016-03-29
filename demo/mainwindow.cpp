/*
    Copyright © 2015 by The QTMyPaint Project

    This file is part of QTMyPaint, a Qt-based interface for MyPaint C++ library.

    QTMyPaint is libre software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QTMyPaint is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QTMyPaint. If not, see <http://www.gnu.org/licenses/>.
*/
#include <QFileDialog>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Central widget:
    mp_view = new MypaintView();
    setCentralWidget (mp_view);




    // Add tools:
    //
    QWidget* toolsWidget = new QWidget();

    QVBoxLayout* toolsLayout = new QVBoxLayout();
    toolsLayout->setSpacing(0);
    toolsLayout->setMargin(0);
    toolsLayout->setContentsMargins(0,0,0,0);
    toolsLayout->setSizeConstraint(QLayout::SetFixedSize);


    // Color selector
    //
    m_colorBtn = new QPushButton("Click to select another brush color...");
    m_colorBtn->setMinimumHeight(60);
    m_colorBtn->setStyleSheet( "color: white; background-color: black;" );

    toolsLayout->addWidget(m_colorBtn);

    connect(m_colorBtn, SIGNAL(pressed ()), mp_view, SLOT(btnChgColorPressed()));


    // Clear button
    //
    m_clearBtn = new QPushButton("Clear");
//    m_clearBtn->setMinimumHeight(60);

    toolsLayout->addWidget(m_clearBtn);

    connect(m_clearBtn, SIGNAL(pressed ()), mp_view, SLOT(btnClearPressed()));


    m_saveBtn = new QPushButton("Save");
//    m_saveBtn->setMinimumHeight(60);

    toolsLayout->addWidget(m_saveBtn);

    connect(m_saveBtn, SIGNAL(pressed ()), this, SLOT(btnSavePressed()));


    toolsWidget->setLayout(toolsLayout);

    QDockWidget* p_dockTools = new QDockWidget("Tools");
    p_dockTools->setWidget(toolsWidget);

    addDockWidget ( Qt::RightDockWidgetArea, p_dockTools );




    m_tabletActive = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTabletDevice(QTabletEvent* event)
{
    mp_view->setTabletDevice(event);
}

void MainWindow::btnSavePressed()
{
    // Path
    QString initPath = QDir::homePath() + "/untitled.png";

    QString filePath = QFileDialog::getSaveFileName( this,
                                                     tr( "Save Image" ),
                                                     initPath);
    if ( filePath.isEmpty() )
    {
        return;// false;
    }

    mp_view->saveToFile(filePath);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED( event );
    mp_view->setSize(this->centralWidget()->rect().size());
}
