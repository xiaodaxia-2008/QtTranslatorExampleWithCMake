#pragma once
#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class QLabel;
class QTranslator;
class QEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(const char *title = "MainWin");
    void changeEvent(QEvent *event) override;

private:
    QTranslator *m_translator{nullptr};
    Ui::MainWindow *m_ui;
};