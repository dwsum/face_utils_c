load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

licenses(["notice"])
package(default_visibility = [
    "//visibility:public",
])

exports_files(["LICENSE"])


cc_library(
    name = "Lmk",
    srcs = ["Lmk.cpp"],
    hdrs = ["Lmk.h"],
    data = ["//mediapipe/modules/face_detection:face_detection_short_range.tflite"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame",
        "//mediapipe/framework/formats:image_frame_opencv",
        "//mediapipe/framework/formats:landmark_cc_proto",
        "//mediapipe/framework/port:file_helpers",
        "//mediapipe/framework/port:opencv_highgui",
        "//mediapipe/framework/port:opencv_imgproc",
        "//mediapipe/framework/port:opencv_video",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "//mediapipe/modules/face_geometry/libs:geometry_pipeline",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "//Authentiface_code:constants",
        
        "//mediapipe/examples/desktop:demo_run_graph_main",
        "//mediapipe/graphs/face_detection:desktop_live_calculators",
    ],
)

cc_library(
    name = "FaceDetect",
    srcs = ["FaceDetect.cpp"],
    hdrs = ["FaceDetect.h"],
    data = ["//mediapipe/modules/face_detection:face_detection_short_range.tflite"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame",
        "//mediapipe/framework/formats:image_frame_opencv",
        "//mediapipe/framework/port:file_helpers",
        "//mediapipe/framework/port:opencv_highgui",
        "//mediapipe/framework/port:opencv_imgproc",
        "//mediapipe/framework/port:opencv_video",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "//mediapipe/modules/face_geometry/libs:geometry_pipeline",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "//Authentiface_code:constants",
        
        "//mediapipe/examples/desktop:demo_run_graph_main",
        "//mediapipe/graphs/face_detection:desktop_live_calculators",

    ],
)

cc_library(
    name = "Core",
    srcs = ["Core.cpp"],
    hdrs = ["Core.h"],
    data = ["//mediapipe/modules/face_detection:face_detection_short_range.tflite"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        
        "//Authentiface_code:constants",
    ],
)
