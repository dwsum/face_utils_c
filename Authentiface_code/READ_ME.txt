Current Method uses bazel to compile the code
Now, for the bazel updates:
bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1 -s mediapipe/examples/desktop/face_mesh:authentiface_demo

GLOG_logtostderr=1 bazel-bin/mediapipe/examples/desktop/face_mesh/authentiface_demo   --calculator_graph_config_file=mediapipe/graphs/face_mesh/face_mesh_desktop_live.pbtxt


Using g++ to compile
g++ -std=c++17 Main.cpp ./AppUtils/App.cpp ./AppUtils/FrameAnalyze.cpp ./AppUtils/TerminalSetup.cpp ./DoorUtils/Door.cpp ./DoorUtils/CameraUtils/Camera.cpp ./DoorUtils/CameraUtils/Computer.cpp ./DoorUtils/LockUtils/DoorLock.cpp ./DoorUtils/LockUtils/GpioLock.cpp ./DoorUtils/Types.cpp ./AppUtils/VideoFeed.cpp `pkg-config --cflags --libs opencv4`
