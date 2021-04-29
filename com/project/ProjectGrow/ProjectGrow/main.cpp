#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile styleFile(":/style/qss/ManjaroMix.qss");
    styleFile.open(QFile::ReadOnly);

    QString style(styleFile.readAll());
    app.setStyleSheet(style);

    MainWindow w;
    // Make a windowless Frame
    // TODO: Move away from normal frame so we can make something nicer
    // w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // Don't allow it to change size from what was set in the form
    w.setFixedSize(w.geometry().width(), w.geometry().height());
    w.setWindowTitle("Project Grow");
    w.show();
    return app.exec();
}
