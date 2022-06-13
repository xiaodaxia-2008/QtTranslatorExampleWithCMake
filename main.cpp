#include "MainWindow.h"

#include <QApplication>
#include <QTranslator>


int main(int argn, char **argv)
{
  QApplication app(argn, argv);
  Q_INIT_RESOURCE(Resources);

  auto win = new MainWindow;
  win->show();
  app.exec();
  return 0;
}