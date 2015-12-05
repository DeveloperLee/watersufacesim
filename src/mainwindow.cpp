#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <assert.h>
#include <QGridLayout>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    this->setMinimumSize(100, 100);
    QGLFormat qglFormat;
    qglFormat.setVersion(4,0);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    m_ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(m_ui->centralWidget);
    m_glWidget = new GLWidget(qglFormat, this);
    gridLayout->addWidget(m_glWidget, 0, 1);
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_glWidget;
}
