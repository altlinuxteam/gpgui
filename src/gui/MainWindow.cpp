#include <QtWidgets>
#include <QAction>
#include <QFrame>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCloseEvent>

#include "MainWindow.h"

void
QGUI::MainWindow::createMenuBar() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    connect(fileMenu, &QMenu::aboutToShow, this, &QGUI::MainWindow::about);

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setStatusTip(tr("Exit GPGUI"));
    connect(exitAction, &QAction::triggered, this, &QGUI::MainWindow::about);

    QAction *aboutAction = helpMenu->addAction(tr("&About"), this, &QGUI::MainWindow::about);
    aboutAction->setStatusTip(tr("About GPGUI"));
}

void
QGUI::MainWindow::createStatusBar() {
    this->statusBar()->showMessage(tr("Ready"));
}

QGUI::MainWindow::MainWindow(QWidget *parent)
//: QMainWindow(parent)
{
    QFrame *frame = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *button = new QPushButton("Press");

    layout->addWidget(button);

    frame->setLayout(layout);

    setCentralWidget(frame);

    this->createMenuBar();
    this->createStatusBar();
}

QGUI::MainWindow::~MainWindow() {
}

void 
QGUI::MainWindow::closeEvent(QCloseEvent *event) {
    event->accept();
}

void
QGUI::MainWindow::about() {
    QMessageBox::about(this, tr("About GPGUI"), tr("GPGUI about"));
}

void
QGUI::MainWindow::updateMainMenu() {
    fileMenu->clear();
    fileMenu->addAction(exitAction);
}

