#include "MainWindow.h"
#include <QTranslator>
#include <QApplication>
#include <QEvent>
#include <ui_MainWindow.h>
#include <QFile>
#include <QLocale>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include <spdlog/spdlog.h>

void LoadTranslator(QTranslator *translator, const char *file_name, QLocale locale = QLocale())
{
    SPDLOG_DEBUG("locale: {}", locale.name().toStdString());
    if (translator->load(locale, file_name, "_", ":/Languages"))
    {
        SPDLOG_DEBUG("Load translation file {}", translator->filePath().toStdString());
    }
    else
    {
        return;
    }
    auto app = QApplication::instance();
    if (app)
    {
        app->installTranslator(translator);
    }
    else
    {
        SPDLOG_DEBUG("app is nullptr!");
    }
}

MainWindow::MainWindow(const char *title)
    : m_translator(new QTranslator)
{
    LoadTranslator(m_translator, "MainWindow");

    setWindowTitle(title);
    m_ui = new Ui::MainWindow;
    m_ui->setupUi(this);

    connect(m_ui->actionChinese, &QAction::triggered, [this]
            { LoadTranslator(this->m_translator, "MainWindow", QLocale("zh")); });
    connect(m_ui->actionEnglish, &QAction::triggered, [this]
            { LoadTranslator(this->m_translator, "MainWindow", QLocale("en")); });
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        SPDLOG_DEBUG("Language is changed!");
        m_ui->retranslateUi(this);
    }
    else if (event->type() == QEvent::LocaleChange)
    {
        LoadTranslator(m_translator, "MainWindow");
        m_ui->retranslateUi(this);
    }
    QMainWindow::changeEvent(event);
}