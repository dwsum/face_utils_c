//
// Created by Drew Sumsion on 8/13/22.
//

#include "FrameAnalyze.h"

//public:

//Testing
//TODO - Can you simplify how many conditional or mutex variables you have?
std::mutex mtx;
std::mutex mtxFaceID;
std::condition_variable cVar;
std::condition_variable cVarFaceID;
std::condition_variable cVarMainThread;
std::condition_variable cVarMainThread_FaceID;
std::queue<cv::Mat> dataQueue;
std::queue<cv::Mat> frameAnalyze_queueFaceID;
bool processedFaceMeshData = false;
bool processedFaceIDData = false;

//Create meshSequence queue. It will hold the faceMeshResult of each frame.
std::queue<std::vector<std::pair<float, float>>> meshSequence_queue;
std::queue<torch::Tensor> faceID_queue;

FrameAnalyze::FrameAnalyze() : frameAnalyze_queueFaceMesh{}, faceMesh_thread{} {

}

FrameAnalyze::FrameAnalyze(std::map<std::string, std::any> data) : frameAnalyze_queueFaceMesh{}, faceMesh_thread{} {

    //For image processing
    //meshSequence = 0;
    numImages = 0;
    maxFaceIDFrames = VARIABLE_NUMBER_FRAMES_FACE_ID;

    faceStartTime = std::chrono::system_clock::now();

    faceFound = false;
    isProcessing = false;
    isRecording = false;
    findFaceSeconds = VARIABLE_FIND_FACE_SECONDS;
    waitAfterRecording = VARIABLE_WAIT_AFTER_RECORDING;
//    thread threadProcess;

    width = std::any_cast<int>(data[WIDTH]);
    height = std::any_cast<int>(data[HEIGHT]);
////    detectFace
    //detectFace = std::any_cast<int>(data[DETECT_FACE]);
    door = std::any_cast<Door>(data[DOOR]);
    videoSize = std::any_cast<int>(data[VIDEO_SIZE]);
    cameraPntr = std::any_cast<Camera*>(data[CAMERA]);
    videoY = std::any_cast<int>(data[VIDEO_Y]);
    videoX = std::any_cast<int>(data[VIDEO_X]);
    fps = std::any_cast<int>(data[FPS]);
////    processImagesPntr
////    uiPntr
////    faceDetector
////    faceMesh
    idTH = std::any_cast<float>(data[ID_THRESH]);
    totalNumFrames = RECORDING_TIME * fps;
////    std::vector img_seq; I think this one is already good.
    
////    queueFaceID

    recordingStartTime = std::chrono::system_clock::now();
    
    myPreprocessing = Preprocessing();

    if(fps > VARIABLE_MAX_FPS_ALLOWED) {
        doEveryOther = true;
    }
    else {
        doEveryOther = false;
    }
    
    //Setup for multithreading
    //By adding &FrameAnalyze::readDataFromQueue, you are providing the 
    //address of the member function that you want to execute in the 
    //new thread. The this pointer is passed as the second argument, 
    //which binds the method call to the current instance of the 
    //FrameAnalyze class.
    readerThread = std::thread(&FrameAnalyze::readDataFromQueue, this); // Initialize readerThread
    runFaceIDThread = std::thread(&FrameAnalyze::RunFaceID, this);
}

/* IsFace()
Used by App.cpp to find when a face is both present and within range.

Starts the process of getting facial landmarks to run FaceMesh
*/
void FrameAnalyze::IsFace(cv::Mat roi) {
    // std::cout << "In IsFace\n";

    //If pulling from video, use this.
    // if (!isRecording){
    //     StartRecording();
    //     faceFound = true;
    // }

    //Commenting this if statement out when you want it to read the faceMesh
    // points from the video input rather than the live feed. 

    //if not already analyzing a face
    if ((!isRecording) && (!isProcessing) && (std::chrono::duration<double>(std::chrono::system_clock::now() - faceStartTime).count() > findFaceSeconds)
            && (std::chrono::duration<double>(std::chrono::system_clock::now() - recordingStartTime).count() > (waitAfterRecording))) {
        faceStartTime = std::chrono::system_clock::now();

        //bool faceDetectResult = myFaceDetect.GenFaceDetect(roi);
        
        // std::cout << "Start findFace\n";
        bool findFace = myPreprocessing.FindFace(roi, myFaceDetect, door);
        // bool findFace = true;//Using this line for now to avoid Segmentation fault error w/ faceDetect

        if (findFace) {//findFace(roi, self.detectFace, self.door):
            //TODO: lock stuff here?

            if (!faceFound) {
                //TODO start recording here.
                StartRecording();
                faceFound = true;
            }
        }
        else {
            std::cout << "No face detected.\n";
            faceFound = false;
        }
    }
}

/* CheckCurrRecording()
Used by App.cpp to check if the current frame should be recorded.

Finalizes the recording if the recording time has been reached or if the
max number of frames has been reached.
*/
cv::Mat FrameAnalyze::CheckCurrRecording(cv::Mat roi) {
    // std::cout << "In CheckCurrRecording\n";
    if (isRecording) {
        std::cout << cntFaceID << " cntFaceID\n";
        std:: cout << maxFaceIDFrames << " maxFaceIDFrames\n";
        if (cntFaceID < maxFaceIDFrames) {
            cntFaceID += 1;
            frameAnalyze_queueFaceID.push(roi);

            //Tell our FaceID thread to carry on if it's in 
            //the waiting state
            cVarFaceID.notify_one();
        }

        if (numImages < totalNumFrames) {
            cv::Mat newroi = CurrRecording(roi);

            //Print number of cntFaceID
            std::cout << "Number of frames: " << numImages << std::endl;

            return newroi;
        }
        else if((std::chrono::duration<double>(std::chrono::system_clock::now() - recordingStartTime).count()) > RECORDING_TIME) {
            FinalizeRecording();
        }
    }

    return roi;
}

/* StartRecording()

Starts the recording process by setting the recordingStartTime and
isRecording variables.
*/
void FrameAnalyze::StartRecording() {
    std::cout << "In StartRecording\n";
    recordingStartTime = std::chrono::system_clock::now();
    isRecording = true;
    door.myLock->IsOnline(); // note: this was for the zwave lock. If not doing zwave, then possibilly pull it out for slightly quicker?
    //TODO make this cout be part of the UI.
    std::cout << MESSAGE_UI_START_RECORDING;
    //TODO implement lists below.
//    frameAnalyze_queueFaceMesh = reset;
//    imgSeq = reset;
    numImages = 0;
}

void FrameAnalyze::ResetFaceID() {
    passFaceID = false;
    cntFaceID = 0;
}

/*RunFaceID()
- Runs the FaceID model on the frames in the frameAnalyze_queueFaceID queue
- Adds the results to the faceIDSequence vector
Runs on a separate thread
*/
void FrameAnalyze::RunFaceID() {

    int totalFramesProcessed = 0;

    while (true) {
        std::unique_lock<std::mutex> lock(mtxFaceID);

        //Wait until the queue is not empty or until the processedFaceIDData
        //flag is set to true.
        cVarFaceID.wait(lock, []{ 
            
            if (processedFaceIDData){
                return true;
            }
            return (!frameAnalyze_queueFaceID.empty()); 
        });

        //if the processedFaceIDData flag is set to true, we don't 
        //need to process any more data.
        if (processedFaceIDData){
            std::cout << "Processed faceID data.\n";
            break;
        }

        cv::Mat roi = frameAnalyze_queueFaceID.front();
        frameAnalyze_queueFaceID.pop();
        lock.unlock(); // Unlock before processing the data to allow other threads to access the queue

        //Start timer for how long it takes for the frame to get processed in FaceID model
        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        
        torch::Tensor resultTensor = IsEnrolled(roi);
            
        // std::unique_lock<std::mutex> lock(mtxFaceID);
        lock.lock(); // Lock before pushing the data to the queue

        faceID_queue.push(resultTensor);
        totalFramesProcessed += 1;
        lock.unlock(); // Unlock before processing the data to allow other threads to access the queue

        cVarMainThread_FaceID.notify_one();

        std::cout << "FACEID_THREAD TIME - Data processed in" << std::chrono::duration<double>(std::chrono::system_clock::now() - start).count() << " seconds" << std::endl;

        std::cout << "Total frames processed: " << totalFramesProcessed << std::endl;
    }
}

/*readDataFromQueue()
- Reads the data from the frameAnalyze_queueFaceMesh queue
- Adds the data to the meshSequence vector
Runs on a separate thread
*/
void FrameAnalyze::readDataFromQueue() {

    int totalFramesProcessed = 0;

    //The idea here is that by initializing the class here, it will be restricted to this thread.
    Lmk myLmkHelper;

    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        //Wait until the queue is not empty or until the processedFaceMeshData
        //flag is set to true.
        cVar.wait(lock, []{ 
            
            if (processedFaceMeshData){
                return true;
            }
            return (!dataQueue.empty()); 
        });
        
        //if the processedFaceMeshData flag is set to true, we don't 
        //need to process any more data.
        if (processedFaceMeshData){
            std::cout << "Processed face mesh data.\n";
            break;
        }

        //Equivalent to python code: data = dataQueue.get()
        cv::Mat data = dataQueue.front();
        dataQueue.pop();
        lock.unlock(); // Unlock before processing the data to allow other threads to access the queue
        
        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        std::vector<std::pair<float, float>> faceMeshResult = myLmkHelper.GenLmk(data);
        std::cout << "FACEMESH_THREAD TIME - Data processed in" << std::chrono::duration<double>(std::chrono::system_clock::now() - start).count() << " seconds" << std::endl;

        //If the size of faceMeshResult > 0 Add the faceMeshResult to a 
        //vector of vectors of pairs that can be shared with the UI thread.
        if (faceMeshResult.size() > 0){
            //locking the thread here so that we're able to throw the faceMeshResult into the meshSequence_queue
            //without any other threads trying to access it.
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << "FACEMESH_THREAD - Size of faceMeshResult: " << faceMeshResult.size() << std::endl;
            // meshSequence.push_back(faceMeshResult);//If I run this line, I get std::bad_alloc error
            meshSequence_queue.push(faceMeshResult);
            totalFramesProcessed += 1;
            lock.unlock(); // Unlock before processing the data to allow other threads to access the queue
            
            cVarMainThread.notify_one();
        } else {
            std::cout << "No face detected.\n";
            lock.unlock(); // Unlock before processing the data to allow other threads to access the queue
        }

        // Process the data (replace this with your custom processing code)
        // For example, you can print the data to the console:
        
        std::cout << "Total frames processed: " << totalFramesProcessed << std::endl;
    }
}

/*
CurrRecording
- Add frame to FaceMesh queue
- Add frame to imgage sequence queue (conditional)
- Add UI to the image (conditional)

return roi
- Contains an image frame with the added UI template
*/
cv::Mat FrameAnalyze::CurrRecording(cv::Mat roi) {
    numImages += 1;

    if ((numImages%2 != 0) || !doEveryOther) {

        //Add the current frame to the queueFaceMesh
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Pushing a frame to queueFaceMesh so we now have: " << (numImages/2)+1 << " frames.\n";
 
        dataQueue.push(roi);
        
        //Tell our FaceMesh thread to carry on if it's in the waiting state
        cVar.notify_one();
        
    }
    //TODO check the UI if we are supposed to save and then if we are add the frame to the img_seq

    return roi;
}

void FrameAnalyze::FinalizeRecording() {
    std::cout << "Finalize recording\n";
    finalizeRecordingTime = std::chrono::system_clock::now();
    //TODO make this cout be part of the UI.
    //std::cout << MESSAGE_UI_PROCESSING;
    isRecording = false;
    StartProcessing();
    //process();
    //passFaceID = true; //TODO - Temporary hardcode.
    // if(passFaceID) {
    //     std::cout << "Start processing the frames\n";
    //     StartProcessing();
    // }
    ResetFaceID();
}

void FrameAnalyze::Process() {
    //TODO discuss with shad. I feel like we are transferring data twice in the PYthon code in process and startProcessing. Do we need to do that? I didn't include it here.

    //TODO join the facemesh and faceID threading here.
}

void FrameAnalyze::StartProcessing() {

    std::cout << "FrameAnalyze Start processing\n";
    
    std::chrono::system_clock::time_point endTime;
    std::map<std::string, std::any> transferData;

    isProcessing = true;

    std::unique_lock<std::mutex> lock(mtx);
    cVarMainThread.wait(lock, []{ return !meshSequence_queue.empty(); }); // Wait until the queue is not empty

    //Pull out the data from the queue and store it in meshSequence
    while (!meshSequence_queue.empty()) {
        std::vector<std::pair<float, float>> datas = meshSequence_queue.front();
        meshSequence_queue.pop();
        meshSequence.push_back(datas);
    }

    transferData = {
        {"meshSequence", meshSequence},
        {"img_seq", img_seq},
        {"fps", fps},
        //{"camera", cameraPntr},
        {"videoY", videoY},
        {"videoX", videoX},
        {"videoSize", videoSize},
        {"width", width},
        {"height", height}
    };

    //Get size of meshSequence (should be 30 if it got all the frames)
    std::cout << "meshSequence size: " << meshSequence.size() << std::endl;
    processedFaceMeshData = true;
    lock.unlock();

    cVar.notify_one(); // Tell the reading thread to carry on.
    //The reading thread should be done now.

    //FACEID THREAD CODE
    std::cout << "Going through FaceID thread\n";
    std::unique_lock<std::mutex> lockFaceID(mtxFaceID);
    cVarMainThread_FaceID.wait(lockFaceID, []{ return !faceID_queue.empty(); }); // Wait until the queue is not empty

    //Pull out the data from the queue and store it in faceIDSequence
    std::cout << "before faceID while loop\n";
    while (!faceID_queue.empty()) {
        std::cout << "In the faceID while loop\n";
        torch::Tensor datas = faceID_queue.front();
        faceID_queue.pop();
        faceIDSequence.push_back(datas);
    }
    std::cout << "Setting processedFaceIDData to true\n";
    processedFaceIDData = true;
    lockFaceID.unlock();

    cVarFaceID.notify_one(); // Tell the RunFaceiD thread to carry on.

    // Wait for the threads to finish
    readerThread.join();
    runFaceIDThread.join();

    passFaceID = true;//TODO - develop further Temporary hardcode.

    processImagesPntr.SetData(transferData);
    //Join threads here.

    if(passFaceID) {
        std::cout << "FrameAnalyze/StartProcessing/passFaceIDLoop\n";
        //print size of meshSequence
        std::cout << "meshSequence size: " << meshSequence.size() << std::endl;
        processImagesPntr.ProcessBatch(meshSequence, idemb);
    }
    processImagesPntr.ProcessImg();
    isProcessing = false;

    endTime = std::chrono::system_clock::now();
    std::cout << "TIME - From start of recording to end of processing:" << std::chrono::duration<double>(endTime - recordingStartTime).count() << " seconds.\n";
    std::cout << "TIME - From start of recording to beginning of finalizeRecording:" << std::chrono::duration<double>(finalizeRecordingTime - recordingStartTime).count() << " seconds.\n";
    //TODO Add total time functionality.
}

/*
IsEnrolled
- Checks if the face is enrolled in the system

return bool - True if the face is enrolled, false otherwise
*/
torch::Tensor FrameAnalyze::IsEnrolled(cv::Mat roi) {
    FaceDetect myFaceDetector;
    Core myCore;
    CNNEmbedding myCNNEmbedding;

    std::cout << "In IsEnrolled\n";
    //Details of the roi's shape
    std::cout << "roi size: " << roi.size() << std::endl;

    //For use when analyzing data going to FaceID
    //Set roi = to the roi.jpg file in the directory
    // roi = cv::imread("roi.jpg");

    //Detection Array information
    //detect[0] = myFaceDetect.boundXmin * width, 
    //detect[1] = myFaceDetect.boundYmin * height, 
    //detect[2] = (myFaceDetect.boundXmin + myFaceDetect.boundWidth) * width, 
    //detect[3] = (myFaceDetect.boundYmin + myFaceDetect.boundHeight) * height
    std::array<float, 4> detected = myPreprocessing.DetectFaceHelper(roi, myFaceDetector);
    std::cout << "detected size: " << detected.size() << std::endl;
    std::cout << "detected: " << detected[0] << " " << detected[1] << " " 
        << detected[2] << " " << detected[3] << std::endl;
    
    float expansion = 1.3;
    float targetSize = 160;
    bool largest = true;

    //Run through all your image processing before sending image through
    //FaceID.
    cv::Mat facePhoto = myCore.GetCroppedFaceImage(roi, detected, expansion, targetSize, largest);
    
    std::cout << "moved past GetCroppedFaceImage\n";

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    
    torch::Tensor idembTensor = myCNNEmbedding.Predict(facePhoto);

    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    std::cout << "TIME - Taken by faceID model: " << std::chrono::duration<double>(endTime - start).count() << " seconds.\n";

    //Run the image through FaceID
    
    return idembTensor;
}