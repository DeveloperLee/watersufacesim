#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Databinding.h"
#include "Settings.h"
#include <QSettings>
#include <assert.h>
#include <QGridLayout>
#include <QFileDialog>
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    settings.loadDefaults();

    QGLFormat qglFormat;
    qglFormat.setVersion(4,0);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    m_ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(m_ui->centralWidget);
    m_glWidget = new GLWidget(qglFormat, this);
    gridLayout->addWidget(m_glWidget, 0, 1);

    // restore the UI settings
    QSettings qtSettings("SkyView");
    restoreGeometry(qtSettings.value("geometry").toByteArray());
    restoreState(qtSettings.value("windowState").toByteArray());

    // resize the window to default size
    resize(750,370);
    m_ui->actionOpen->setEnabled(true);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionEffects->setEnabled(true);
    m_ui->effectsDock->setEnabled(true);

    // Bind the UI elements to their properties in the global settings object
    QList<QAction*> actions;

#define SETUP_ACTION(dock, key)\
    actions.push_back(m_ui->dock->toggleViewAction()); \
    actions.back()->setShortcut(QKeySequence(key));

    SETUP_ACTION(effectsDock, "CTRL+1");

    m_ui->menuBar->addActions(actions);
#undef SETUP_ACTION

    addDockWidget(Qt::LeftDockWidgetArea, m_ui->effectsDock);

    dataBind();
}

MainWindow::~MainWindow()
{
    foreach (DataBinding *b, m_bindings)
        delete b;
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
    BIND(BoolBinding::bindCheckbox(m_ui->lensButton, settings.enableLens))
    BIND(BoolBinding::bindCheckbox(m_ui->rainButton, settings.enableRain))
    BIND(BoolBinding::bindCheckbox(m_ui->snowButton, settings.enableSnow))
    BIND(BoolBinding::bindCheckbox(m_ui->shadowButton, settings.enableShadow))
    BIND(FloatBinding::bindSlider(m_ui->thicknessSlider, settings.cloudThickness, 0.f, 6.f))
    BIND(FloatBinding::bindSlider(m_ui->hardnessSlider, settings.shadowHardness, 0.f, 1.f))
    BIND(FloatBinding::bindSlider(m_ui->bigWaveSlider, settings.bigWave, 0.f, 6.f))
    BIND(FloatBinding::bindSlider(m_ui->smallWaveSlider, settings.smallWave, 0.f, 1.f))
    BIND(FloatBinding::bindSlider(m_ui->waveSpeedXSlider, settings.waveSpeedX, -1.f, 1.f))
    BIND(FloatBinding::bindSlider(m_ui->waveSpeedYSlider, settings.waveSpeedY, -1.f, 1.f))
    BIND(FloatBinding::bindSlider(m_ui->camXSlider, settings.camX, 0.f, 300.f))
    BIND(FloatBinding::bindSlider(m_ui->camYSlider, settings.camY, 0.f, 300.f))
    BIND(FloatBinding::bindSlider(m_ui->wideAngleSlider, settings.wideAngle, 0.f, 1.f))

#undef BIND

}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings qtSettings("SkyView");
    qtSettings.setValue("geometry", saveGeometry());
    qtSettings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::settingsChanged()
{
    m_glWidget->update();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
               tr("Image Files (*.jpg *png)"));

    if (!fileName.isEmpty()) {
        m_glWidget->reloadTexture(fileName);
    }
}

void MainWindow::on_actionEffects_triggered()
{
    m_ui->effectsDock->show();
}
