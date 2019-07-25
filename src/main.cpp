#include "game.h"
#include <math.h>
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
    int sleep = 20;
    int nSteps = 10000;
    torch::Tensor nnInput = torch::from_blob(game.getState().data(), {1, 12});

    for (int i = 0; i < nSteps; ++i) {
        QApplication::processEvents(QEventLoop::AllEvents, sleep);

        // Play one frame of game with network
        auto gameInput = net->forward(nnInput);
        std::vector<float> gameInputStd(gameInput.data<float>(), gameInput.data<float>() + gameInput.numel());

        std::cout << gameInputStd << std::endl;

        // Convert the logsoftmax used by the network to regular softmax
        for (auto &it : gameInputStd) {
            bool isnan = std::isnan(it);
            if (isnan) {
                it = 0;
            } else {
                it = exp(it);
            }
        }

        auto gameOutput = game.playStep(gameInputStd);
        auto fitness = game.getFitness();

        // Update the nn input
        nnInput = torch::from_blob(gameOutput.data(), {1, 12});

        // Pause for a while to see results
        QThread::msleep(sleep);
    }
    a.exit();

    // Use these lines to manually play the game
    //game.loop();
    //a.exec();
}
