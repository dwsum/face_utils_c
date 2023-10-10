load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

licenses(["notice"])
package(default_visibility = [
    "//visibility:public",
])

exports_files(["LICENSE"])

cc_library(
    name = "CNNEmbedding",
    srcs = ["CNNEmbedding.cpp"],
    hdrs = ["CNNEmbedding.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "@libtorch//:libtorch-lib",
    ],
)