load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

licenses(["notice"])
package(default_visibility = [
    "//visibility:public",
])

exports_files(["LICENSE"])

cc_library(
    name = "App",
    srcs = ["App.cpp"],
    hdrs = ["App.h"],
    visibility = [
        "//visibility:public",
    ],
    copts = ["-Iexternal/libtorch_cpu/include"],
    deps = [
        ":FrameAnalyze",
        ":TerminalSetup",
        ":VideoFeed",
        #INCLUDED FOR TESTING
        #"@libtorch_cpu//include/torch",
        #How do we specify the target?
        #"@libtorch_cpu//include/torch:script",
        "@libtorch//:libtorch-lib",
    ],
)


cc_library(
    name = "FrameAnalyze",
    srcs = ["FrameAnalyze.cpp"],
    hdrs = ["FrameAnalyze.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code/DoorUtils:Door",
        "//Authentiface_code/face_utils/facetools/motion:Preprocessing",
        "//Authentiface_code/face_utils/facetools/detection:Lmk",
        "//Authentiface_code/face_utils/facetools/detection:Core",
        "//Authentiface_code/face_utils/facetools/detection:FaceDetect",
        "//Authentiface_code/AppUtils:ProcessImages",
        "//Authentiface_code/face_utils/facetools/representation:CNNEmbedding",
        "@libtorch//:libtorch-lib",
    ],
)

cc_library(
    name = "TerminalSetup",
    srcs = ["TerminalSetup.cpp"],
    hdrs = ["TerminalSetup.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code:constants",
        "//Authentiface_code/DoorUtils/CameraUtils:Camera",
        "//Authentiface_code/DoorUtils/CameraUtils:Computer",
        "//Authentiface_code/DoorUtils:Door",
    ],
)

cc_library(
    name = "VideoFeed",
    srcs = ["VideoFeed.cpp"],
    hdrs = ["VideoFeed.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code:constants",
        "//Authentiface_code/DoorUtils/CameraUtils:Camera",
    ],
)

cc_library(
    name = "ProcessImages",
    srcs = ["ProcessImages.cpp"],
    hdrs = ["ProcessImages.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code:constants",
        "//Authentiface_code/DoorUtils:Door",
        "//Authentiface_code/AppUtils:ProcessEmbeddings",
        "//Authentiface_code/face_utils/facetools/detection:Lmk",
    ],
)

cc_library(
    name = "ProcessEmbeddings",
    srcs = ["ProcessEmbeddings.cpp"],
    hdrs = ["ProcessEmbeddings.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code:constants",
        "//Authentiface_code/DoorUtils:Door",
        "//Authentiface_code/face_utils/facetools/motion:LmkModel",
    ],
)

cc_library(
    name = "UserInterface",
    srcs = ["UserInterface.cpp"],
    hdrs = ["UserInterface.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code:constants",
        "//Authentiface_code/AppUtils:ProcessImages",
    ],
)