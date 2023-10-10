load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

licenses(["notice"])
package(default_visibility = [
    "//visibility:public",
])

exports_files(["LICENSE"])

cc_library(
    name = "Preprocessing",
    srcs = ["Preprocessing.cpp"],
    hdrs = ["Preprocessing.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code/face_utils/facetools/detection:FaceDetect",
        "//Authentiface_code/DoorUtils:Door",
    ],
)

cc_library(
    name = "LmkModel",
    srcs = ["LmkModel.cpp"],
    hdrs = ["LmkModel.h"],
    visibility = [
        "//visibility:public",
    ],
    # copts = ["-Iexternal/libtorch_cpu/include"],
    deps = [
        "@libtorch//:libtorch-lib",
    ],
)
