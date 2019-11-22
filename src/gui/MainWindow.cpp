#include <QAction>
#include <QCloseEvent>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtWidgets>

#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "MainWindow.h"

#include "preg_parser.h"

void qgui::MainWindow::createMenuBar() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    exitAction = fileMenu->addAction(tr("&Exit"), this, &QWidget::close);
    exitAction->setStatusTip(tr("Exit GPGUI"));

    QAction *aboutAction =
        helpMenu->addAction(tr("&About"), this, &qgui::MainWindow::about);
    aboutAction->setStatusTip(tr("About GPGUI"));
}

void qgui::MainWindow::createStatusBar() {
    this->statusBar()->showMessage(tr("Ready"));
}

namespace {
void preg_entry2table(QTableWidget *regpol_table, preg::entry &pentry, size_t rownum) {
    std::string regtype = std::string(preg::regtype2str(pentry.type));
    std::string val = std::to_string(pentry.value);
    QTableWidgetItem *vname = new QTableWidgetItem(pentry.value_name.c_str());
    QTableWidgetItem *kname = new QTableWidgetItem(pentry.key_name.c_str());
    QTableWidgetItem *vtype = new QTableWidgetItem(regtype.c_str());
    QTableWidgetItem *vval = new QTableWidgetItem(val.c_str());
    regpol_table->insertRow(regpol_table->rowCount());
    regpol_table->setItem(rownum, 0, vname);
    regpol_table->setItem(rownum, 1, kname);
    regpol_table->setItem(rownum, 2, vtype);
    regpol_table->setItem(rownum, 3, vval);
}
}

qgui::MainWindow::MainWindow(QWidget *parent)
//: QMainWindow(parent)
{
    preg::preg_parser *test_regpol = new preg::preg_parser("Registry.pol");
    preg::entry pentry = test_regpol->get_next_entry();
    preg::entry pentry2 = test_regpol->get_next_entry();
    preg::entry pentry3 = test_regpol->get_next_entry();
    preg::entry pentry4 = test_regpol->get_next_entry();

    QVBoxLayout *layout_regpol_editor = new QVBoxLayout;
    QVBoxLayout *layout_gpo_editor = new QVBoxLayout;

    QTabWidget *tw = new QTabWidget;
    tw->addTab(new QWidget, tr("Registry.pol editor"));
    tw->addTab(new QWidget, tr("GPO editor"));

    QTableWidget *regpol_table = new QTableWidget(0, 4, this);
    tw->widget(0)->setLayout(layout_regpol_editor);
    layout_regpol_editor->addWidget(regpol_table);

    preg_entry2table(regpol_table, pentry, 0);
    preg_entry2table(regpol_table, pentry2, 1);
    preg_entry2table(regpol_table, pentry3, 2);
    preg_entry2table(regpol_table, pentry4, 3);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tw);

    QFrame *frame = new QFrame;
    frame->setLayout(layout);
    frame->setFixedSize(800, 800);
    setCentralWidget(frame);
    this->adjustSize();

    this->createMenuBar();
    this->createStatusBar();
}

qgui::MainWindow::~MainWindow() {}

void qgui::MainWindow::closeEvent(QCloseEvent *event) { event->accept(); }

void qgui::MainWindow::about() {
    QMessageBox::about(this, tr("About GPGUI"), tr("GPGUI about"));
}
