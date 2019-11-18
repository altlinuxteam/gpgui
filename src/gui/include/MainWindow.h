class MainWindow : public QMainWindow {
    Q_OBJECT

  protected:
    void closeEvent(QCloseEvent *event) override;

  private slots:
    void about();

  private:
    void createStatusBar();
}
