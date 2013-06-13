#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GLWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionClose_triggered();

//signals:
//	void disableLightsSignal();
//	void enableLightsSignal();
//	void keyPressedSignal(int);

private:
    Ui::MainWindow *ui;
    GLWidget *glWidget;
//    bool eventFilter(QObject*, QEvent*);
};

#endif // MAINWINDOW_H
