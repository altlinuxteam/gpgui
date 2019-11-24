#if !defined(__GPGUI_MAINWINDOW_H)
#define __GPGUI_MAINWINDOW_H 1

#include <QMainWindow>
#include <QtWidgets>
#include <QTableWidget>
#include <QFileDialog>

#Include "preg_parser.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QFileDialog;
class QTableWidget;
QT_END_NAMESPACE

namespace qgui {

class MainWindow : public QMainWindow {
    // Q_OBJECT
    QMenu *file_menu;
    QMenu *help_menu;

    QFileDialog *preg_open_dialog;

    QTableWidget *regpol_table;

    void create_menu_bar();
    void create_status_bar();

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
    void about();
    void open_preg();
    void save_preg();
    void save_dotreg();

  protected:
    void closeEvent(QCloseEvent *event) override;

  private:
    void preg_entry2table(preg::entry &pentry);
}; /* class MainWindow */

} /* namespace qgui */

#endif /* __GPGUI_MAINWINDOW_H */
