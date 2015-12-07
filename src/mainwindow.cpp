#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Databinding.h"
#include "Settings.h"
#include <QSettings>
#include <assert.h>
#include <QGridLayout>
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    settings.loadSettingsOrDefaults();

    this->setMinimumSize(100, 100);
    QGLFormat qglFormat;
    qglFormat.setVersion(4,0);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    m_ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(m_ui->centralWidget);
    m_glWidget = new GLWidget(qglFormat, this);
    gridLayout->addWidget(m_glWidget, 0, 1);

    // Restore the UI settings
    QSettings qtSettings("SkyView");
    restoreGeometry(qtSettings.value("geometry").toByteArray());
    restoreState(qtSettings.value("windowState").toByteArray());


    // resize the window to default size
    resize(700,500);

    // Bind the UI elements to their properties in the global settings object
    QList<QAction*> actions;

    m_ui->effectDock->raise();

    dataBind();
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_glWidget;
}

void MainWindow::dataBind()
{

#define BIND(b) { \
    DataBinding *_b = (b); \
    m_bindings.push_back(_b); \
    assert(connect(_b, SIGNAL(dataChanged()), this, SLOT(settingsChanged()))); \
}

    QButtonGroup *effectButtonGroup = new QButtonGroup;
    m_buttonGroups.push_back(effectButtonGroup);

    BIND(BoolBinding::bindCheckbox(m_ui->cloudButton, settings.enableCloud))
    BIND(BoolBinding::bindCheckbox(m_ui->fogButton, settings.enableFog))
    BIND(FloatBinding::bindSlider(m_ui->thicknessSlider, settings.cloudThickness, 0.f, 1.f))

#undef BIND

}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);

//    switch (e->type()) {
//    case QEvent::LanguageChange:
//        m_ui->retranslateUi(this);
//        break;
//    case QEvent::MouseMove:

//    default:
//        break;
//    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Save the settings before we quit
    settings.saveSettings();
    QSettings qtSettings("SkyView");
    qtSettings.setValue("geometry", saveGeometry());
    qtSettings.setValue("windowState",saveState());

    QMainWindow::closeEvent(event);
}

void MainWindow::settingsChanged()
{
    m_glWidget->update();
}

void MainWindow::fileOpen()
{
    QString file = QFileDialog::getOpenFileName(this, QString(), "./sources/");
    if (!file.isNull())
    {
    }
}
