#if !defined(__GPGUI_MAINWINDOW_H)
#   define __GPGUI_MAINWINDOW_H 1

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

namespace qgui {

class MainWindow : public QMainWindow {
    //Q_OBJECT
    QMenu    *fileMenu;
    QMenu    *helpMenu;
    QAction  *exitAction;

    void createMenuBar();
    void createStatusBar();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void about();

protected:
    void closeEvent(QCloseEvent *event) override;
}; /* class MainWindow */

} /* namespace qgui */

#endif /* __GPGUI_MAINWINDOW_H */

