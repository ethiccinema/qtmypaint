/*
Copyright (c) 2016, François Téchené
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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



    // Open
    //
    m_openBtn = new QPushButton("Open");
    toolsLayout->addWidget(m_openBtn);

    connect(m_openBtn, SIGNAL(pressed ()), this, SLOT(btnOpenPressed()));



    // Saver
    //
    m_saveBtn = new QPushButton("Save");
    toolsLayout->addWidget(m_saveBtn);

    connect(m_saveBtn, SIGNAL(pressed ()), this, SLOT(btnSavePressed()));



    // Clear
    //
    m_clearBtn = new QPushButton("Clear");
    toolsLayout->addWidget(m_clearBtn);

    connect(m_clearBtn, SIGNAL(pressed ()), mp_view, SLOT(btnClearPressed()));



    // Color selector
    //
    m_colorBtn = new QPushButton("Click to select another brush color...");
    m_colorBtn->setMinimumHeight(60);
    m_colorBtn->setStyleSheet( "color: white; background-color: black;" );

    toolsLayout->addWidget(m_colorBtn);

    connect(m_colorBtn, SIGNAL(pressed ()), mp_view, SLOT(btnChgColorPressed()));



    toolsWidget->setLayout(toolsLayout);

    QDockWidget* p_dockTools = new QDockWidget("Tools");
    p_dockTools->setWidget(toolsWidget);

    addDockWidget ( Qt::RightDockWidgetArea, p_dockTools );


    // Add a docked widget
    QDockWidget* p_dockBrush = new QDockWidget("Brush Library");
    mp_brushes = new MPBrushSelector( ":brushes", NULL);
    p_dockBrush->setWidget(mp_brushes);
    addDockWidget ( Qt::RightDockWidgetArea, p_dockBrush );


    connect(mp_brushes,  SIGNAL(brushSelected(const QByteArray&)), mp_view, SLOT(loadBrush(const QByteArray&)));

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

void MainWindow::btnOpenPressed()
{
    // Path
    QString initPath = QDir::homePath();

    QString filePath = QFileDialog::getOpenFileName( this,
                                                     tr( "Open Image" ),
                                                     initPath);
    if ( filePath.isEmpty() )
    {
        return;// false;
    }

    mp_view->loadFromFile(filePath);
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
