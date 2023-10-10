#ifndef AUTHENTIFCE_CODE_C_LMKMODEL_H
#define AUTHENTIFCE_CODE_C_LMKMODEL_H

#include <iostream>
#include <iomanip>
#include <torch/script.h>
#include <torch/torch.h>
// #include <torch/nn/functional.h>
// #include <torch/nn/init.h>
// #include <torch/nn/modules/linear.h>
// #include <torch/nn/modules/rnn.h>
// //#include <torch/nn/padding.h>
// #include <torch/optim/optimizer.h>
// #include <torch/optim/sgd.h>
// #include <torch/serialize.h>
// //#include <torch/tensor.h>
// #include <torch/types.h>
#include <memory>
#include <vector>
#include <fstream>

class LmkModel {
    public:
        LmkModel();
        void InitializeTheModel();

        float ComputeLmkEmb(std::vector<std::vector<std::pair<float, float>>> meshSequence);
        
    private:
        int numberLandmarkPoints = 476; //468 with iris?
        int hiddenSize = 32;
        int outputSize = 64;
        int numberLayers = 2;
        int batchSize = 1;

        int sizeBLOutput = 0;

        bool batchFirst = false;
        bool bidirectional = false;

        int maxSequenceLength;

        torch::jit::script::Module mdl;
};


#endif //AUTHENTIFCE_CODE_C_LMKMODEL_H