load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

licenses(["notice"])
package(default_visibility = [
    "//visibility:public",
])

exports_files(["LICENSE"])

cc_library(
    name = "Door",
    srcs = ["Door.cpp"],
    hdrs = ["Door.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":Types",
    ],
)

cc_library(
    name = "Types",
    srcs = ["Types.cpp"],
    hdrs = ["Types.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code/DoorUtils/CameraUtils:Camera",
        "//Authentiface_code/DoorUtils/CameraUtils:Computer",
        "//Authentiface_code/DoorUtils/LockUtils:DoorLock",
        "//Authentiface_code/DoorUtils/LockUtils:GpioLock",
    ],
)