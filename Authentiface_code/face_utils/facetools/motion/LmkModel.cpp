#include "LmkModel.h"

//INitial setup for the model
LmkModel::LmkModel(){}

void LmkModel::InitializeTheModel(){
    std::cout << "In InitializeTheModel" << std::endl;

    const std::string filePath = "tracedModule_Authentiface_v3.pt";

    try {
        mdl = torch::jit::load(filePath);
    }
    catch (const torch::Error& error) {
        std::cerr << "Could not load scriptmodule from file " << filePath << ".\n";
        return;
    }

    mdl.to(torch::kCPU);

    mdl.eval();

    torch::NoGradGuard no_grad;
}

//Creates an emb with the given information 
float LmkModel::ComputeLmkEmb(std::vector<std::vector<std::pair<float, float>>> meshSequence){
    std::cout << "In ComputeLmkEmb" << std::endl;
    
    //THe size of meshSequence is the number of frames that were passed into the sequence. (~60)
    // std::cout << "meshSequence.size() = " << meshSequence.size() << std::endl;

    //The size of meshSequence[0] is the number of landmarks in the first frame. 
    // std::cout << "meshSequence[0].size() = " << meshSequence[0].size() << std::endl;

    torch::jit::script::Module model = mdl;

    int sequenceLength = meshSequence.size();

    torch::Tensor sequenceLengthTensor = torch::tensor({sequenceLength});
    // std::cout << "sequenceLengthTensor = " << sequenceLengthTensor << std::endl;//Very long

    //Convert meshSequence to a one dimensional vector
    std::vector<float> meshSequenceVector;
    meshSequenceVector.reserve(sequenceLength * 476 * 2);

    for (int i = 0; i < meshSequence.size(); i++){
        for (int j = 0; j < meshSequence[i].size(); j++){
            meshSequenceVector.push_back(meshSequence[i][j].first);
            meshSequenceVector.push_back(meshSequence[i][j].second);
        }
    }

    std::cout << "meshSequenceVector.size() = " << meshSequenceVector.size() << std::endl;

    //Convert meshSequence to a tensor. May need to flatten
    torch::Tensor meshSequenceTensor = torch::from_blob(meshSequenceVector.data(), {sequenceLength, 476, 2}, torch::kFloat32);
    // std::cout << "meshSequenceTensor = " << meshSequenceTensor << std::endl; //Very long

    //Pad the sequence
    torch::Tensor paddedSequence = torch::nn::utils::rnn::pad_sequence(meshSequenceTensor, /*batch_first=*/false, /*padding_value=*/0.0);
    //Get sizes of paddedSequence
    std::cout << "paddedSequence.sizes() = " << paddedSequence.sizes() << std::endl;
    for (int i = 0; i < paddedSequence.sizes().size(); i++){
        std::cout << "paddedSequence.sizes()[" << i << "] = " << paddedSequence.sizes()[i] << std::endl;
    }

    //Convert the sequence to a float and run on the CPU
    torch::Tensor lmkdata = paddedSequence.to(torch::kCPU).to(torch::kFloat32);
    // std::cout << "lmkdata = " << lmkdata << std::endl;
    //Print the first point in lmkdata
    // std::cout << "lmkdata[0][0][0] = " << lmkdata[0][0][0] << std::endl;
    // std::cout << "lmkdata[0][0][1] = " << lmkdata[0][0][1] << std::endl;
    // std::cout << "real lmkdata info: " << lmkdata.sizes() << std::endl;//[30, 1, 476, 2]
    // std::cout << "real lmkdata info: " << lmkdata.type() << std::endl;//CPUFloatType

    std::vector<torch::jit::IValue> input = {lmkdata, sequenceLengthTensor};
    
    auto emb = model.forward(input).toTensor();

    torch::Tensor out = emb.detach().to(torch::kCPU);

    std::cout << "This is the out: " << out << std::endl;
    
    //OPTIONAL CODE - Used for saving data for analysis
    //save the lmk_emb to a .pt file
    // torch::save(out, "modelEmb.pt");

    // torch::Tensor x = lmkdata.detach().to(torch::kCPU);
    // torch::save(x, "lmkdata_tensor.pt");

    // std::ofstream outfile("lmkdata.bin", std::ios::binary);
    // outfile.write(reinterpret_cast<const char*>(lmkdata.data_ptr<float>()), lmkdata.numel() * sizeof(float));
    // outfile.close();

    return 0;
}