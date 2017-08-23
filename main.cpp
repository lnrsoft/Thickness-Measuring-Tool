/*
    Author: Roland Ihasz   https://chtbsoft.com
    Created on 07 February 2015, 15:09 final
*/

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
