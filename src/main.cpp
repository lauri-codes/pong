#include "game.h"
#include <QApplication>
#include <QtWidgets>
#include <QThread>
#include <torch/torch.h>
#include "nn.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;

    // Initialize the NN
    auto net = std::make_shared<Net>();
    //torch::Tensor tensor = torch::rand({2, 3});
    //std::cout << tensor << std::endl;

    // Use the following kind of loop to play advance the game manually with custom input
    // The a.exit closes the application
//    std::vector<float> input = {0, 1};
//    for (int i = 0; i < 10; ++i) {
//        QApplication::processEvents(QEventLoop::AllEvents, 1000);
//        std::vector<float> output = game.requestPosVel(input);
//        qDebug() << output;
//        QApplication::processEvents(QEventLoop::AllEvents, 1000);
//        QThread::sleep(1);
//    }
//    a.exit();

    // Use these lines to manually play the game
    game.loop();
    a.exec();
}
