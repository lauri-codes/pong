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

    // This section uses a NN to play the game

    // Initialize the NN
    auto net = std::make_shared<Net>();

    // Use the following kind of loop to play advance the game manually with custom input
    // The a.exit closes the application
    int sleep = 100;
    for (int i = 0; i < 100; ++i) {
        QApplication::processEvents(QEventLoop::AllEvents, sleep);

        // Play one frame of game with network
        torch::Tensor randomInput = torch::randn({1, 12});
        auto gameInput = net->forward(randomInput);
        std::vector<float> gameInputStd(gameInput.data<float>(), gameInput.data<float>() + gameInput.numel());
        std::cout << gameInputStd << std::endl;
        auto gameOutput = game.getInput(gameInputStd);
        auto fitness = game.getFitness();

        QThread::msleep(sleep);
    }
    a.exit();

    // Use these lines to manually play the game
    //game.loop();
    //a.exec();
}
