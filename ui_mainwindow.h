/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    QWidget *canvas;
    QDockWidget *effectDock;
    QWidget *effectDockContents;
    QGroupBox *effectType;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QCheckBox *cloudButton;
    QHBoxLayout *horizontalLayout;
    QLabel *thicknessLabel;
    QSlider *thicknessSlider;
    QCheckBox *shadowButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *hardnessLabel;
    QSlider *hardnessSlider;
    QCheckBox *fogButton;
    QCheckBox *lensButton;
    QCheckBox *rainButton;
    QCheckBox *snowButton;
    QGroupBox *waveBox;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *bigWaveLabel;
    QSlider *bigWaveSlider;
    QHBoxLayout *horizontalLayout_8;
    QLabel *smallWaveLabel;
    QSlider *smallWaveSlider;
    QHBoxLayout *horizontalLayout_7;
    QLabel *waveSpeedXLabel;
    QSlider *waveSpeedXSlider;
    QHBoxLayout *horizontalLayout_6;
    QLabel *waveSpeedYLabel;
    QSlider *waveSpeedYSlider;
    QGroupBox *cameraBox;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *camXLabel;
    QSlider *camXSlider;
    QHBoxLayout *horizontalLayout_4;
    QLabel *camYLabel;
    QSlider *camYSlider;
    QHBoxLayout *horizontalLayout_5;
    QLabel *wideAngleLabel;
    QSlider *wideAngleSlider;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(842, 579);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        canvas = new QWidget(centralWidget);
        canvas->setObjectName(QStringLiteral("canvas"));
        canvas->setGeometry(QRect(9, 9, 401, 461));
        MainWindow->setCentralWidget(centralWidget);
        effectDock = new QDockWidget(MainWindow);
        effectDock->setObjectName(QStringLiteral("effectDock"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(effectDock->sizePolicy().hasHeightForWidth());
        effectDock->setSizePolicy(sizePolicy);
        effectDock->setBaseSize(QSize(200, 500));
        effectDockContents = new QWidget();
        effectDockContents->setObjectName(QStringLiteral("effectDockContents"));
        effectType = new QGroupBox(effectDockContents);
        effectType->setObjectName(QStringLiteral("effectType"));
        effectType->setEnabled(true);
        effectType->setGeometry(QRect(10, 0, 211, 241));
#ifndef QT_NO_ACCESSIBILITY
        effectType->setAccessibleName(QStringLiteral(""));
#endif // QT_NO_ACCESSIBILITY
        widget = new QWidget(effectType);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 30, 191, 197));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cloudButton = new QCheckBox(widget);
        cloudButton->setObjectName(QStringLiteral("cloudButton"));

        verticalLayout->addWidget(cloudButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        thicknessLabel = new QLabel(widget);
        thicknessLabel->setObjectName(QStringLiteral("thicknessLabel"));

        horizontalLayout->addWidget(thicknessLabel);

        thicknessSlider = new QSlider(widget);
        thicknessSlider->setObjectName(QStringLiteral("thicknessSlider"));
        thicknessSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(thicknessSlider);


        verticalLayout->addLayout(horizontalLayout);

        shadowButton = new QCheckBox(widget);
        shadowButton->setObjectName(QStringLiteral("shadowButton"));

        verticalLayout->addWidget(shadowButton);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        hardnessLabel = new QLabel(widget);
        hardnessLabel->setObjectName(QStringLiteral("hardnessLabel"));

        horizontalLayout_2->addWidget(hardnessLabel);

        hardnessSlider = new QSlider(widget);
        hardnessSlider->setObjectName(QStringLiteral("hardnessSlider"));
        hardnessSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(hardnessSlider);


        verticalLayout->addLayout(horizontalLayout_2);

        fogButton = new QCheckBox(widget);
        fogButton->setObjectName(QStringLiteral("fogButton"));

        verticalLayout->addWidget(fogButton);

        lensButton = new QCheckBox(widget);
        lensButton->setObjectName(QStringLiteral("lensButton"));

        verticalLayout->addWidget(lensButton);

        rainButton = new QCheckBox(widget);
        rainButton->setObjectName(QStringLiteral("rainButton"));

        verticalLayout->addWidget(rainButton);

        snowButton = new QCheckBox(widget);
        snowButton->setObjectName(QStringLiteral("snowButton"));

        verticalLayout->addWidget(snowButton);

        waveBox = new QGroupBox(effectDockContents);
        waveBox->setObjectName(QStringLiteral("waveBox"));
        waveBox->setGeometry(QRect(10, 240, 211, 171));
        widget1 = new QWidget(waveBox);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 30, 191, 128));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        bigWaveLabel = new QLabel(widget1);
        bigWaveLabel->setObjectName(QStringLiteral("bigWaveLabel"));

        horizontalLayout_9->addWidget(bigWaveLabel);

        bigWaveSlider = new QSlider(widget1);
        bigWaveSlider->setObjectName(QStringLiteral("bigWaveSlider"));
        bigWaveSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(bigWaveSlider);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        smallWaveLabel = new QLabel(widget1);
        smallWaveLabel->setObjectName(QStringLiteral("smallWaveLabel"));

        horizontalLayout_8->addWidget(smallWaveLabel);

        smallWaveSlider = new QSlider(widget1);
        smallWaveSlider->setObjectName(QStringLiteral("smallWaveSlider"));
        smallWaveSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(smallWaveSlider);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        waveSpeedXLabel = new QLabel(widget1);
        waveSpeedXLabel->setObjectName(QStringLiteral("waveSpeedXLabel"));

        horizontalLayout_7->addWidget(waveSpeedXLabel);

        waveSpeedXSlider = new QSlider(widget1);
        waveSpeedXSlider->setObjectName(QStringLiteral("waveSpeedXSlider"));
        waveSpeedXSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(waveSpeedXSlider);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        waveSpeedYLabel = new QLabel(widget1);
        waveSpeedYLabel->setObjectName(QStringLiteral("waveSpeedYLabel"));

        horizontalLayout_6->addWidget(waveSpeedYLabel);

        waveSpeedYSlider = new QSlider(widget1);
        waveSpeedYSlider->setObjectName(QStringLiteral("waveSpeedYSlider"));
        waveSpeedYSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(waveSpeedYSlider);


        verticalLayout_3->addLayout(horizontalLayout_6);

        cameraBox = new QGroupBox(effectDockContents);
        cameraBox->setObjectName(QStringLiteral("cameraBox"));
        cameraBox->setGeometry(QRect(10, 410, 211, 131));
        widget2 = new QWidget(cameraBox);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(10, 30, 191, 94));
        verticalLayout_2 = new QVBoxLayout(widget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        camXLabel = new QLabel(widget2);
        camXLabel->setObjectName(QStringLiteral("camXLabel"));

        horizontalLayout_3->addWidget(camXLabel);

        camXSlider = new QSlider(widget2);
        camXSlider->setObjectName(QStringLiteral("camXSlider"));
        camXSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(camXSlider);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        camYLabel = new QLabel(widget2);
        camYLabel->setObjectName(QStringLiteral("camYLabel"));

        horizontalLayout_4->addWidget(camYLabel);

        camYSlider = new QSlider(widget2);
        camYSlider->setObjectName(QStringLiteral("camYSlider"));
        camYSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(camYSlider);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        wideAngleLabel = new QLabel(widget2);
        wideAngleLabel->setObjectName(QStringLiteral("wideAngleLabel"));

        horizontalLayout_5->addWidget(wideAngleLabel);

        wideAngleSlider = new QSlider(widget2);
        wideAngleSlider->setObjectName(QStringLiteral("wideAngleSlider"));
        wideAngleSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(wideAngleSlider);


        verticalLayout_2->addLayout(horizontalLayout_5);

        effectDock->setWidget(effectDockContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), effectDock);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FinalProject", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        effectType->setTitle(QApplication::translate("MainWindow", "Effect Types", 0));
        cloudButton->setText(QApplication::translate("MainWindow", "enable cloud", 0));
        thicknessLabel->setText(QApplication::translate("MainWindow", "Thickness", 0));
        shadowButton->setText(QApplication::translate("MainWindow", "enable shadow", 0));
        hardnessLabel->setText(QApplication::translate("MainWindow", "Hardness", 0));
        fogButton->setText(QApplication::translate("MainWindow", "enable fog", 0));
        lensButton->setText(QApplication::translate("MainWindow", "enable lens", 0));
        rainButton->setText(QApplication::translate("MainWindow", "enable rain", 0));
        snowButton->setText(QApplication::translate("MainWindow", "enable snow", 0));
        waveBox->setTitle(QApplication::translate("MainWindow", "Wave Parameters", 0));
        bigWaveLabel->setText(QApplication::translate("MainWindow", "Big Wave", 0));
        smallWaveLabel->setText(QApplication::translate("MainWindow", "Small Wave", 0));
        waveSpeedXLabel->setText(QApplication::translate("MainWindow", "Wave Speed X", 0));
        waveSpeedYLabel->setText(QApplication::translate("MainWindow", "Wave Speed Y", 0));
        cameraBox->setTitle(QApplication::translate("MainWindow", "Camera", 0));
        camXLabel->setText(QApplication::translate("MainWindow", "X Position", 0));
        camYLabel->setText(QApplication::translate("MainWindow", "Y Position", 0));
        wideAngleLabel->setText(QApplication::translate("MainWindow", "Wide Angle", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
