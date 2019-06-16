#ifndef NN_H
#define NN_H

#include <torch/torch.h>

// Define a new Module.
struct Net : torch::nn::Module {
  Net() {
    // Construct and register two Linear submodules.
    fc1 = register_module("fc1", torch::nn::Linear(12, 32));
    fc2 = register_module("fc2", torch::nn::Linear(32, 16));
    fc3 = register_module("fc3", torch::nn::Linear(16, 2));
  }

  // Implement the Net's forward pass.
  torch::Tensor forward(torch::Tensor x) {
    x = torch::relu(fc1->forward(x));
    x = torch::relu(fc2->forward(x));
    x = torch::relu(fc3->forward(x));
    x = torch::log_softmax(x, 1);
    return x;
  }

  // Use one of many "standard library" modules.
  torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};
};

#endif // NN_H
