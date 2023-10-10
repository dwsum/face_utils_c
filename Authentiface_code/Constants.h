//
// Created by Drew Sumsion on 8/15/22.
//

#ifndef AUTHENTIFACEDEMO_C_CONSTANTS_H
#define AUTHENTIFACEDEMO_C_CONSTANTS_H

//Toggle debug
#define DEBUG true

//Values that change reults:
#define VARIABLE_PASSWORD_STRENGTH_SETTING 0
#define VARIABLE_VIDEO_SIZE 512     //int
#define RECORDING_TIME 2.0    //seconds
#define VARIABLE_FIND_FACE_SECONDS 0.05
//How long do we need to wait after recording?
// #define VARIABLE_WAIT_AFTER_RECORDING (RECORDING_TIME+(1.0)) //seconds
#define VARIABLE_WAIT_AFTER_RECORDING (RECORDING_TIME)
#define VARIABLE_NUMBER_FRAMES_FACE_ID 3
#define VARIABLE_MAX_FPS_ALLOWED 20
#define COMPUTER_CAMERA_WIDTH 640
#define COMPUTER_CAMERA_HEIGHT 480

//TerminalSetup
#define CAMERA "camera"
#define DOOR "door"
#define LOCK "lock"
#define ID_THRESH "id_thresh"
#define LMK_THRESH "lmk_thres"
#define PASSWORD_STRENGTH "pass_strength"
#define VIDEO_SIZE "video_size"
#define WIDTH "width"
#define HEIGHT "height"
#define FPS "fps"
#define VIDEO_X "videoX"
#define VIDEO_Y "videoY"
#define DETECT_FACE "detectFace"
#define FACE_MESH "faceMesh"
#define FACE_ID "faceID"
#define ENROLL "enroll"

//paths
#define SETTINGS_PATH_LMK "Authentiface_code/Data/Settings/lmkTH.txt"
#define SETTINGS_PATH_ID "Authentiface_code/Data/Settings/idTH.txt"
#define SETTINGS_PATH_STRENGTH "Authentiface_code/Data/Settings/passwordStrengthPercentile.txt"
#define PATH_PB_TXT_FILE "mediapipe/graphs/face_mesh/face_mesh_desktop_live.pbtxt"
#define PATH_DETECT_FACE_PB_TXT_FILE "mediapipe/graphs/face_detection/face_detection_desktop_live.pbtxt"

// For Finding the password strengths.
#define PERCENTILE_LABEL " Percentile: "
#define PERCENTILE_SCORE_0 "percentile_0"
#define PERCENTILE_SCORE_1 "percentile_1"
#define PERCENTILE_SCORE_2 "percentile_2"
#define PERCENTILE_SCORE_3 "percentile_3"
#define PERCENTILE_SCORE_4 "percentile_4"
#define PERCENTILE_SCORE_5 "percentile_5"
#define PERCENTILE_SCORE_6 "percentile_6"
#define PERCENTILE_SCORE_7 "percentile_7"
#define PERCENTILE_SCORE_8 "percentile_8"
#define PERCENTILE_SCORE_9 "percentile_9"
#define PERCENTILE_SCORE_10 "percentile_10"
#define PERCENTILE_SCORE_0_NUM 0
#define PERCENTILE_SCORE_1_NUM 10
#define PERCENTILE_SCORE_2_NUM 20
#define PERCENTILE_SCORE_3_NUM 30
#define PERCENTILE_SCORE_4_NUM 40
#define PERCENTILE_SCORE_5_NUM 50
#define PERCENTILE_SCORE_6_NUM 60
#define PERCENTILE_SCORE_7_NUM 70
#define PERCENTILE_SCORE_8_NUM 80
#define PERCENTILE_SCORE_9_NUM 90
#define PERCENTILE_SCORE_10_NUM 100
#define STRENGTH_LABEL "strength"

//Camera Constants FOR KEY IN MAPS
#define COMPUTER_CAMERA "COMPUTER_CAMERA0"

//LOCK CONSTANTS FOR KEY IN MAPS
#define GPIO_LOCK "gpio_lock"

//LOCK CONSTANTS FOR PRINTING
#define GPIO_LOCK_NAME "Gpio Lock (Not a real Lock)"
#define MESSAGE_DOOR_LOCK "No Lock Connected. Default Lock class\n"
#define LOCKING_MESSAGE "Locking: "
#define UNLOCKING_MESSAGE "Unlocking: "
#define INIT_MESSAGE "Initializing: "
#define ONLINE_MESSAGE "ONLINE :"
#define NEW_LINE "\n";

//camera constants
#define DEFAULT_WIDTH 640 //Note, this currently doesn't do anything besides prevent the init from crashing. Will not change the size.
#define DEFAULT_HEIGHT 480 //Note, this currently doesn't do anything besides prevent the init from crashing. Will not change the size.

//Error Messages
#define THRESH_ERROR "One of the Thresholds was not loaded correctly. Please try restarting. If the problem continues, please report the problem."
#define POWER_LOAD_ERROR "There was an error loading the strength of the password."

//UI messages
#define MESSAGE_UI_START_RECORDING "Recording\n"
#define MESSAGE_UI_PROCESSING "Processing\n"

#endif //AUTHENTIFACEDEMO_C_CONSTANTS_H
