load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

licenses(["notice"])
package(default_visibility = [
    "//visibility:public",
])

exports_files(["LICENSE"])

cc_library(
    name = "Camera",
    srcs = ["Camera.cpp"],
    hdrs = ["Camera.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code:constants",
        "//mediapipe/framework/port:opencv_highgui",
        "//mediapipe/framework/port:opencv_imgproc",
        "//mediapipe/framework/port:opencv_video",
    ],
)

cc_library(
    name = "Computer",
    srcs = ["Computer.cpp"],
    hdrs = ["Computer.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code/DoorUtils/CameraUtils:Camera",
    ],
)