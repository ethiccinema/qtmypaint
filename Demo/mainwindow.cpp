#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Central widget:
    MypaintView* mpView = new MypaintView();
    setCentralWidget (mpView);

    // Add a color selector:
    QDockWidget* p_dockColor = new QDockWidget("Color selection");
    m_colorBtn = new QPushButton("Click to select another brush color...");
    m_colorBtn->setMinimumHeight(60);
    m_colorBtn->setStyleSheet( "color: white; background-color: black;" );
    p_dockColor->setWidget(m_colorBtn);
    addDockWidget ( Qt::RightDockWidgetArea, p_dockColor );


    connect(m_colorBtn, SIGNAL(pressed ()), mpView, SLOT(btnChgColorPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
