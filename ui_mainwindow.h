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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionEffects;
    QAction *actionWater_Parameters;
    QAction *actionCamera;
    QWidget *centralWidget;
    QWidget *canvas;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Toolbar;
    QDockWidget *effectsDock;
    QWidget *dockWidgetContents_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_10;
    QCheckBox *cloudButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *thicknessSlider;
    QCheckBox *shadowButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSlider *hardnessSlider;
    QCheckBox *fogButton;
    QCheckBox *lensButton;
    QCheckBox *rainButton;
    QCheckBox *snowButton;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSlider *bigWaveSlider;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSlider *smallWaveSlider;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSlider *waveSpeedXSlider;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSlider *waveSpeedYSlider;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QSlider *camXSlider;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QSlider *camYSlider;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QSlider *wideAngleSlider;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(842, 714);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionEffects = new QAction(MainWindow);
        actionEffects->setObjectName(QStringLiteral("actionEffects"));
        actionWater_Parameters = new QAction(MainWindow);
        actionWater_Parameters->setObjectName(QStringLiteral("actionWater_Parameters"));
        actionCamera = new QAction(MainWindow);
        actionCamera->setObjectName(QStringLiteral("actionCamera"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        canvas = new QWidget(centralWidget);
        canvas->setObjectName(QStringLiteral("canvas"));
        canvas->setGeometry(QRect(9, 9, 401, 461));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 842, 22));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Toolbar = new QMenu(menuBar);
        menu_Toolbar->setObjectName(QStringLiteral("menu_Toolbar"));
        MainWindow->setMenuBar(menuBar);
        effectsDock = new QDockWidget(MainWindow);
        effectsDock->setObjectName(QStringLiteral("effectsDock"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        splitter = new QSplitter(dockWidgetContents_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(10, 10, 181, 456));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_3->addWidget(label_10);

        cloudButton = new QCheckBox(layoutWidget);
        cloudButton->setObjectName(QStringLiteral("cloudButton"));

        verticalLayout_3->addWidget(cloudButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        thicknessSlider = new QSlider(layoutWidget);
        thicknessSlider->setObjectName(QStringLiteral("thicknessSlider"));
        thicknessSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(thicknessSlider);


        verticalLayout_3->addLayout(horizontalLayout);

        shadowButton = new QCheckBox(layoutWidget);
        shadowButton->setObjectName(QStringLiteral("shadowButton"));

        verticalLayout_3->addWidget(shadowButton);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        hardnessSlider = new QSlider(layoutWidget);
        hardnessSlider->setObjectName(QStringLiteral("hardnessSlider"));
        hardnessSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(hardnessSlider);


        verticalLayout_3->addLayout(horizontalLayout_2);

        fogButton = new QCheckBox(layoutWidget);
        fogButton->setObjectName(QStringLiteral("fogButton"));

        verticalLayout_3->addWidget(fogButton);

        lensButton = new QCheckBox(layoutWidget);
        lensButton->setObjectName(QStringLiteral("lensButton"));

        verticalLayout_3->addWidget(lensButton);

        rainButton = new QCheckBox(layoutWidget);
        rainButton->setObjectName(QStringLiteral("rainButton"));

        verticalLayout_3->addWidget(rainButton);

        snowButton = new QCheckBox(layoutWidget);
        snowButton->setObjectName(QStringLiteral("snowButton"));

        verticalLayout_3->addWidget(snowButton);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 2, 0, 2);
        label_11 = new QLabel(layoutWidget1);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout->addWidget(label_11);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        bigWaveSlider = new QSlider(layoutWidget1);
        bigWaveSlider->setObjectName(QStringLiteral("bigWaveSlider"));
        bigWaveSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(bigWaveSlider);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        smallWaveSlider = new QSlider(layoutWidget1);
        smallWaveSlider->setObjectName(QStringLiteral("smallWaveSlider"));
        smallWaveSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(smallWaveSlider);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        waveSpeedXSlider = new QSlider(layoutWidget1);
        waveSpeedXSlider->setObjectName(QStringLiteral("waveSpeedXSlider"));
        waveSpeedXSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(waveSpeedXSlider);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        waveSpeedYSlider = new QSlider(layoutWidget1);
        waveSpeedYSlider->setObjectName(QStringLiteral("waveSpeedYSlider"));
        waveSpeedYSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(waveSpeedYSlider);


        verticalLayout->addLayout(horizontalLayout_6);

        splitter->addWidget(layoutWidget1);
        layoutWidget2 = new QWidget(splitter);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_2->addWidget(label_12);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        camXSlider = new QSlider(layoutWidget2);
        camXSlider->setObjectName(QStringLiteral("camXSlider"));
        camXSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(camXSlider);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_8->addWidget(label_8);

        camYSlider = new QSlider(layoutWidget2);
        camYSlider->setObjectName(QStringLiteral("camYSlider"));
        camYSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(camYSlider);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_9->addWidget(label_9);

        wideAngleSlider = new QSlider(layoutWidget2);
        wideAngleSlider->setObjectName(QStringLiteral("wideAngleSlider"));
        wideAngleSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(wideAngleSlider);


        verticalLayout_2->addLayout(horizontalLayout_9);

        splitter->addWidget(layoutWidget2);
        effectsDock->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), effectsDock);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Toolbar->menuAction());
        menu_File->addAction(actionOpen);
        menu_File->addAction(actionQuit);
        menu_Toolbar->addAction(actionEffects);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FinalProject", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Meta+O", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Meta+Q", 0));
        actionEffects->setText(QApplication::translate("MainWindow", "Effects", 0));
        actionEffects->setShortcut(QApplication::translate("MainWindow", "Meta+1", 0));
        actionWater_Parameters->setText(QApplication::translate("MainWindow", "Water Parameters", 0));
        actionWater_Parameters->setShortcut(QApplication::translate("MainWindow", "Meta+2", 0));
        actionCamera->setText(QApplication::translate("MainWindow", "Camera", 0));
        actionCamera->setShortcut(QApplication::translate("MainWindow", "Meta+3", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menu_Toolbar->setTitle(QApplication::translate("MainWindow", "&Toolbar", 0));
        label_10->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Effects</span></p></body></html>", 0));
        cloudButton->setText(QApplication::translate("MainWindow", "enable cloud", 0));
        label->setText(QApplication::translate("MainWindow", "Thickness", 0));
        shadowButton->setText(QApplication::translate("MainWindow", "enable shadows", 0));
        label_2->setText(QApplication::translate("MainWindow", "Hardness", 0));
        fogButton->setText(QApplication::translate("MainWindow", "enable fog", 0));
        lensButton->setText(QApplication::translate("MainWindow", "enable lens", 0));
        rainButton->setText(QApplication::translate("MainWindow", "enable rain", 0));
        snowButton->setText(QApplication::translate("MainWindow", "enable snow", 0));
        label_11->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Water</span></p></body></html>", 0));
        label_3->setText(QApplication::translate("MainWindow", "Big Wave", 0));
        label_4->setText(QApplication::translate("MainWindow", "Small Wave", 0));
        label_5->setText(QApplication::translate("MainWindow", "Wave Speed X", 0));
        label_6->setText(QApplication::translate("MainWindow", "Wave Speed Y", 0));
        label_12->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Camera</span></p></body></html>", 0));
        label_7->setText(QApplication::translate("MainWindow", "Position X", 0));
        label_8->setText(QApplication::translate("MainWindow", "Position Y", 0));
        label_9->setText(QApplication::translate("MainWindow", "Wide Angle", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
