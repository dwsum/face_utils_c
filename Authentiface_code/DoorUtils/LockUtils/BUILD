load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

licenses(["notice"])
package(default_visibility = [
    "//visibility:public",
])

exports_files(["LICENSE"])

cc_library(
    name = "DoorLock",
    srcs = ["DoorLock.cpp"],
    hdrs = ["DoorLock.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code:constants",
    ],
)

cc_library(
    name = "GpioLock",
    srcs = ["GpioLock.cpp"],
    hdrs = ["GpioLock.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//Authentiface_code:constants",
        "//Authentiface_code/DoorUtils/LockUtils:DoorLock",
    ],
)