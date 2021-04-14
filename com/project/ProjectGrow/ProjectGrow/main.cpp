#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    // Make a windowless Frame
    // TODO: Move away from normal frame so we can make something nicer
    // w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // Don't allow it to change size from what was set in the form
    w.setFixedSize(w.geometry().width(), w.geometry().height());
    w.setWindowTitle("Project Grow");
    w.show();
    return a.exec();
}
