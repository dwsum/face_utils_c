#include "ProcessEmbeddings.h"

ProcessEmbeddings::ProcessEmbeddings() {}

ProcessEmbeddings::ProcessEmbeddings(std::map<std::string, std::any> theData) {
    // self.passwordStrengths = []
    enroll = std::any_cast<decltype(enroll)>(theData[ENROLL]);
    idTH = std::any_cast<float>(theData[ID_THRESH]);
    lmkTH = std::any_cast<decltype(lmkTH)>(theData[LMK_THRESH]);
    door = std::any_cast<Door>(theData[DOOR]);
    // self.theUI = theUI
    // self.users = load_users(savePath)
    // self.savePath = savePath
    // self.passwordStrength = passwordStrength
    // self.strengthMinimum = self.passwordStrength["strength"]
    // self.idEMB = None
    // self.lmkEMB = None
    // self.idDist = None
    // self.idDists = []
    // self.lmkDist = None
    // self.idEMBs = []
    // self.lmkEMBs = []
    // self.lastVid = None
    // self.found_user = None
    // self.enroll_name = None
    // self.width = None
    // self.height = None
    // self.fps = None
    // self.minFrames=25
    if (enroll){StartEnrollment();}
    // self.img_seq = []
    // self.enroll_images = []

    //These are just constants - maybe don't need them here
    // self.lmkEMB_fileName = "lmkEmb.txt"
    // self.idEMB_fileName = "idEmb.txt"
    // self.numEnroll_fileName = "numEnroll.txt"
    // self.strength_fileName = "strength.txt"

}

/*
ProcessEmb

This function takes in a sequence of images and a sequence of landmarks.
It will then either add the enrollment or verify the enrollment
depending on the number of enrollments that have been added.

@param original_LMK_seq: a sequence of landmarks
@param img_seq: a sequence of images
*/
void ProcessEmbeddings::ProcessEmb(std::vector<std::vector<std::pair<float, float>>> original_LMK_seq, std::vector<cv::Mat> img_seq) {
    std::cout << "In ProcessEmb" << std::endl;
    img_seq = img_seq;
    if (enroll){
        //add_enrollment
        AddEnrollment(original_LMK_seq, img_seq);
        if (idEMBs.size() == 3){
            //save enrollment
        }
    }else{
        //verify enrollment
        myLmkModel.InitializeTheModel();//TODO: Consider doing this earlier in 

        //Set a start time
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        float lmk_emb = myLmkModel.ComputeLmkEmb(original_LMK_seq);

        std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
        std::cout << "TIME - Taken by faceMesh model in verify: " << std::chrono::duration<double>(endTime - start).count() << " seconds.\n";
    }
}

/*
AddEnrollment

Processes landmark data to create an enrollment.
*/
void ProcessEmbeddings::AddEnrollment(std::vector<std::vector<std::pair<float, float>>> original_LMK_seq, std::vector<cv::Mat> img_seq){
    std::cout << "In AddEnrollment" << std::endl;

    
    //runtime to more closely follow the python code.
    
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    float lmk_emb = myLmkModel.ComputeLmkEmb(original_LMK_seq);

    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    std::cout << "TIME - Taken by model in AddEnrollment: " << std::chrono::duration<double>(endTime - start).count() << " seconds.\n";
    
    //What is lmk_emb?
    //IN the python code lmk_emb is a numpy array of size 64 that
    //lists out 64 floats that make up the user's emb.
    //It is the output of the model after being passed the landmarks
}

void ProcessEmbeddings::StartEnrollment(){
    std::cout << "In StartEnrollment" << std::endl;

    enrollName = "Test Subject";
    enroll = true;
    idEMBs.clear();
    lmkEMBs.clear();
    enrollImages.clear();
}