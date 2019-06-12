# IDEA
Pong videogame augmented with genetic algorithm trained neural network AI
opponent.

# Pong
The game is a Qt5 based application. Qt enables multi-platform (Windows, Linux,
Mac, Adroid), C++ and relatively easy development. It is not really optimal for
games (Godot or Unity would be better) but was used due to familiarity with it.

# Machine learning

## Neural network

### Input
The game can be asked to output the ball position and velocity and the opponent
position and velocity as 2D vectors. This vector containing 8 features can be
used as input for the neural network.

## Genetic algorithm

### Fitness
The fitness of the AI can be requested from the game. It is calculated as
(own score - opponent score)/minute.
