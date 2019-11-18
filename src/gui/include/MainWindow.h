#if !defined(__GPGUI_MAINWINDOW_H)
#   define GPGUI_MAINWINDOW_H 1

class MainWindow : public QMainWindow {
    Q_OBJECT

  protected:
    void closeEvent(QCloseEvent *event) override;

  private slots:
    void about();

  private:
    void createStatusBar();
};

#endif /* __GPGUI_MAINWINDOW_H */

