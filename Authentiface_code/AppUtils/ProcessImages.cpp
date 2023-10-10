#include "ProcessImages.h"

//TDODO: GetLMKTuple()

ProcessImages::ProcessImages() {}

/*
ProcessImages 
constructor that takes in a map of strings to any type of data

Here we lay out all the information that we need to process the images.


@param transferData: a map of strings to any type of data
*/
ProcessImages::ProcessImages(std::map<std::string, std::any> theData){
    processingBatch = false;

    enroll = std::any_cast<decltype(enroll)>(theData[ENROLL]);
    idTH = std::any_cast<float>(theData[ID_THRESH]);
    lmkTH = std::any_cast<decltype(lmkTH)>(theData[LMK_THRESH]);
    door = std::any_cast<Door>(theData[DOOR]);

    // detectFace = theData["detectFace"]
    // fn512 = theData["fn512"]
    // face_mesh = theData["face_mesh"]
    
    // passwordStrength= theData["passwordStrength"]//TDOO

    // self.savePath = Path(theData["user_path"])
    // self.theUI = theData['theUI']
    // self.faceEMB = []
    original_LMK_seq.clear();
    lmkEMB = 0;
    idEMB = 0;
    // self.lmkEMBs = []
    // self.idEMBs = []
    // meshSequence = std::any_cast<decltype(meshSequence)>(theData.at("meshSequence"));
    // img_seq = std::any_cast<decltype(img_seq)>(theData.at("img_seq"));
    // self.processEmbeddings = processEmbeddings(door, enroll, idTH, lmkTH, self.savePath, self.theUI, passwordStrength)

    // # flags
    processingBatch = false;
    isProcessing = false;

    // self.camera_width,self.camera_height =door.camera.getWidthHeight()
}

void ProcessImages::SetData(std::map<std::string, std::any> transferData) {
    std::cout << "In ProcessImages::SetData" << std::endl;
    meshSequence = std::any_cast<decltype(meshSequence)>(transferData.at("meshSequence"));


    img_seq = std::any_cast<decltype(img_seq)>(transferData.at("img_seq"));
    fps = std::any_cast<decltype(fps)>(transferData.at("fps"));
    //cameraPntr = std::any_cast<Camera*>(transferData.at("camera")); // Updated line
    videoY = std::any_cast<decltype(videoY)>(transferData.at("videoY"));
    videoX = std::any_cast<decltype(videoX)>(transferData.at("videoX"));
    videoSize = std::any_cast<decltype(videoSize)>(transferData.at("videoSize"));
    width = std::any_cast<decltype(width)>(transferData.at("width"));
    height = std::any_cast<decltype(height)>(transferData.at("height"));
}

void ProcessImages::StartEnrollment(){
    processEmbeddings.StartEnrollment();
}


void ProcessImages::ProcessBatch(std::vector<std::vector<std::pair<float, float>>> receivedMeshSequence, std::vector<std::pair<float, float>> idemb){//, faceEMBTemp){
    std::cout << "In ProcessBatch" << std::endl;
    //Print sizes of receivedMeshSequence and loop through them

    processingBatch = true;

    original_LMK_seq = myLmkHelper.PackLmk(receivedMeshSequence);

    processingBatch = false;

    std::vector<float> meshSequenceVector;
    meshSequenceVector.reserve(30 * 476 * 2);

    for (int i = 0; i < receivedMeshSequence.size(); i++){
        for (int j = 0; j < meshSequence[i].size(); j++){
            meshSequenceVector.push_back(receivedMeshSequence[i][j].first);
            meshSequenceVector.push_back(receivedMeshSequence[i][j].second);
        }
    }

    // //save meshSequenceVector to file
    // std::ofstream myfile;
    // myfile.open ("meshSequenceVector.txt");
    // for (int i = 0; i < meshSequenceVector.size(); i++){
    //     myfile << meshSequenceVector[i] << std::endl;
    // }
    // myfile.close();
}

void ProcessImages::ProcessImg(){

    std::cout << "In ProcessImg" << std::endl;
    std::cout << original_LMK_seq.size() << std::endl;
    isProcessing = true;

    if (original_LMK_seq.empty()) {
        std::cout << "LMK_seq is empty(0)" << std::endl;
        
    }else{
        if (original_LMK_seq.size() == 0){//Does same thing as before?
            std::cout << "LMK_seq is empty" << std::endl;

        } else {
            std::cout << "Send to ProcessEmb" << std::endl;
            processEmbeddings.ProcessEmb(original_LMK_seq, img_seq);//This is what should trigger add enrollment
            
        }
    }

    // self.theUI.updateTxt2()
    original_LMK_seq.clear();
    isProcessing = false;
    // self.faceEMB = []
    // blank = np.zeros((self.camera_width,self.camera_height,3),dtype=np.uint8)
    // global face_mesh
    // face_mesh.process(blank)

    std::cout << "Processed image" << std::endl;
}