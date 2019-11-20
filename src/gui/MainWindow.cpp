#include <QtWidgets>
#include <QAction>
#include <QFrame>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCloseEvent>

#include <QTabWidget>

#include "MainWindow.h"

void
qgui::MainWindow::createMenuBar() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    exitAction = fileMenu->addAction(tr("&Exit"), this, &QWidget::close);
    exitAction->setStatusTip(tr("Exit GPGUI"));

    QAction *aboutAction = helpMenu->addAction(tr("&About"), this, &qgui::MainWindow::about);
    aboutAction->setStatusTip(tr("About GPGUI"));
}

void
qgui::MainWindow::createStatusBar() {
    this->statusBar()->showMessage(tr("Ready"));
}

qgui::MainWindow::MainWindow(QWidget *parent)
//: QMainWindow(parent)
{
    QTabWidget *tw = new QTabWidget;
    tw->addTab(new QWidget, tr("Registry.pol editor"));
    tw->addTab(new QWidget, tr("GPO editor"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tw);

    QFrame *frame = new QFrame;
    frame->setLayout(layout);
    setCentralWidget(frame);

    this->createMenuBar();
    this->createStatusBar();
}

qgui::MainWindow::~MainWindow() {
}

void 
qgui::MainWindow::closeEvent(QCloseEvent *event) {
    event->accept();
}

void
qgui::MainWindow::about() {
    QMessageBox::about(this, tr("About GPGUI"), tr("GPGUI about"));
}

