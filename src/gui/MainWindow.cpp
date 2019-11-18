#include <QtWidgets>

#include "MainWindow.h"

MainWindow::MainWindow() { createStatusBar(); }

void MainWindow::closeEvent(QCloseEvent *event) { event->ignore(); }

void MainWindow::about() {
    QMessageBox::about(
        this, tr("About GPGUI"),
        tr("<b>GPGUI</b> is a multiplatform Windows Group Policy Editor."));
}

void MainWindow::createStatusBar() { statusBar()->showMessage(tr("Ready")); }
