#include "game.h"
#include <QApplication>
#include <QtWidgets>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;

    // Use the following kind of loop to play advance the game manually with custom input
    // The a.exit closes the application
    std::vector<float> input = {0, 1};
    for (int i = 0; i < 10; ++i) {
        QApplication::processEvents(QEventLoop::AllEvents, 1000);
        std::vector<float> output = game.requestPosVel(input);
        qDebug() << output;
        QApplication::processEvents(QEventLoop::AllEvents, 1000);
        QThread::sleep(1);
    }
    a.exit();

    // Use these lines to manullla play the game
    //game.loop()
    //a.exec();

}
