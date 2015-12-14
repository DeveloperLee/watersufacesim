#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "glwidget.h"
#include "Databinding.h"

namespace Ui {
    class MainWindow;
}

class DataBinding;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void changeEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent *e);

private:
    void dataBind();

    QList<DataBinding*> m_bindings;
    QList<QButtonGroup*> m_buttonGroups;
    Ui::MainWindow *m_ui;
    GLWidget *m_glWidget;

public slots:
    void settingsChanged();
private slots:
    void on_actionOpen_triggered();
    void on_actionEffects_triggered();
};

#endif // MAINWINDOW_H
