#include "game.h"
#include <QApplication>
#include <QtWidgets>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;

    std::vector<float> input = {0, 1};
    for (int i = 0; i < 2; ++i) {
//        qDebug() << output;
//        QCoreApplication::processEvents();
        QApplication::processEvents(QEventLoop::AllEvents, 1000);
        std::vector<float> output = game.requestFrame(input);
        QApplication::processEvents(QEventLoop::AllEvents, 1000);
        QThread::sleep(1);
    }

    return a.exec();
}
