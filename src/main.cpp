#include "game.h"
#include <QApplication>
#include <QtWidgets>
#include <QThread>
#include<armadillo>
#include"simpleNN.h"
#include"ga.h"

int main(int argc, char *argv[])
{
    srand (time(NULL));
   int population = 100;
   int generations = 1000;
   double temperature = 50;
   arma::vec fitness =  arma::zeros<arma::vec>(population);

   arma::vec inpNN = arma::ones<arma::vec>(8);

   int inpSize = inpNN.n_elem;
   int height = 10;
   int depth = 10;
   int outputSize = 2;

   arma::mat inpWeights = arma::randu<arma::mat>(height,inpSize);
   arma::cube weights = arma::randu<arma::cube>(height,height,depth);
   arma::mat outWeights = arma::randu<arma::mat>(outputSize,height);
   arma::vec inpBiases = arma::randu<arma::vec>(height);
   arma::mat biases = arma::randu<arma::mat>(height,depth);
   arma::vec outBiases = arma::randu<arma::vec>(outputSize);

   arma::mat DNAS=1 - 2*arma::randu<arma::mat>(fitness.n_elem, inpWeights.n_elem + weights.n_elem + outWeights.n_elem + inpBiases.n_elem + biases.n_elem + outBiases.n_elem);
   DNAS=0.1*DNAS;
  DNAS.load("DNAS2.save");
   arma::mat outputsNN = arma::zeros<arma::mat>(fitness.n_elem,outBiases.n_elem);

    QApplication a(argc, argv);
    Game game;

    // Use the following kind of loop to play advance the game manually with custom input
    // The a.exit closes the application
    std::vector<float> GUIinput = {0, 1};
//        if(i % 100 < 50){input = {0,1};}else{input={1,0};}// 133/44000
 //       QApplication::processEvents(QEventLoop::AllEvents, 1000);
    std::vector<float> GUIoutput = game.requestPosVel(GUIinput);

    for(int gen=0; gen < generations; gen++){
        fitness = zeros<vec>(fitness.n_elem);
      for(int candidate=0; candidate < population; candidate++){
        for (int step = 0; step < 1000; step++){
            for(int j = 0; j < inpNN.n_elem; j++){
                inpNN(j) = GUIoutput[j];
            }
            outputsNN.row(candidate)= simpleNNvec(DNAS.row(candidate).t(),inpNN, inpWeights, weights, outWeights, inpBiases, biases, outBiases).t();
//            outputsNN.print("outpyt");
            GUIinput[0] = outputsNN(candidate,0);
            GUIinput[1] = outputsNN(candidate,1);
            GUIoutput = game.requestPosVel(GUIinput);
//            if(abs(GUIoutput[1]) > 25 ){fitness(candidate) += 1.0;}
            fitness(candidate) += 0.1*(GUIoutput[4] - GUIoutput[1])*(GUIoutput[4] - GUIoutput[1]);
//            qDebug() << GUIoutput;

            QApplication::processEvents(QEventLoop::AllEvents, 1000);
//        QThread::sleep(0);
        }
      }
        fitness.t().print("fit");
      DNAS = ga_eval(DNAS, 0.00001*fitness, 5.0,0.001000000, temperature);
      DNAS.save("DNAS2.save",raw_ascii);
        cout << "MaxFitIs: " << max(fitness) << "\n";
        cout << "MinFitIs: " << min(fitness) << "\n";
        temperature -= temperature/(double)generations;
        cout << "TempIs: " << temperature << endl;
        cout << "genis" << gen << "\n";


    }
    //    a.exit();

    // Use these lines to manullla play the game
//    game.loop();
//    a.exec();

}
