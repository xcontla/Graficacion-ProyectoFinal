#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    glWidget = new GLWidget;
    //std::cout << ui->scrollArea->width() << " " << ui->scrollArea->height() << std::endl;
    glWidget->resize(ui->scrollArea->width(),ui->scrollArea->height());
    ui->scrollArea->setWidget(glWidget);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClose_triggered()
{
    close();
}
