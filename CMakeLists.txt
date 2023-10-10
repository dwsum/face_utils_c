cmake_minimum_required(VERSION 3.12)
project(Hello_World)

set(CMAKE_CXX_STANDARD 14)

# Set the path to your libtorch installation
set(TORCH_DIR "~/libtorch/")
find_package(Torch REQUIRED PATHS ${TORCH_DIR})
include_directories(${TORCH_INCLUDE_DIRS})

#opencv items
set(OpenCV_DIR /drive2/research/code/face_utils_C/test2/env/lib/python3.10/site-packages/cv2/)
find_package( OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found")
endif()
include_directories( ${OpenCV_INCLUDE_DIRS} )

# MediaPipe Configuration
set(MEDIAPIPE_DIR "/drive2/research/code/AuthentifaceDemo_C/")

if(NOT EXISTS "${MEDIAPIPE_DIR}")
	message(FATAL_ERROR "Mediapipe directory '${MEDIAPIPE_DIR}' not found!")
endif()
get_filename_component(MEDIAPIPE_DIRNAME "${MEDIAPIPE_DIR}" NAME)

# LibMP
set(LIBMP_TARGET_NAME "libmp")
set(LIBMP_SOURCE_DIR "${MEDIAPIPE_DIR}/mediapipe/examples/desktop/${LIBMP_TARGET_NAME}")
set(LIBMP_BIN_DIR "${MEDIAPIPE_DIR}/bazel-bin/mediapipe/examples/desktop/${LIBMP_TARGET_NAME}")
add_library(LIBMP SHARED IMPORTED)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(LIBMP_SHARED_LIBRARY "${LIBMP_BIN_DIR}/${LIBMP_TARGET_NAME}.dll")
	set(LIBMP_IMPORT_LIB "${LIBMP_BIN_DIR}/${LIBMP_TARGET_NAME}.dll.if.lib")
	set_target_properties(LIBMP PROPERTIES
    	IMPORTED_LOCATION "${LIBMP_SHARED_LIBRARY}"
		IMPORTED_IMPLIB "${LIBMP_IMPORT_LIB}"
    	INTERFACE_INCLUDE_DIRECTORIES "${LIBMP_SOURCE_DIR}"
	)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	set(LIBMP_SHARED_LIBRARY "${LIBMP_BIN_DIR}/${LIBMP_TARGET_NAME}.so")
	set_target_properties(LIBMP PROPERTIES
    	IMPORTED_LOCATION "${LIBMP_SHARED_LIBRARY}"
    	INTERFACE_INCLUDE_DIRECTORIES "${LIBMP_SOURCE_DIR}"
	)
endif()

# Protobuf
# use Protobuf bundled with LibMP
set(protobuf_source_dir "${MEDIAPIPE_DIR}/bazel-bin/external/com_google_protobuf")
message("right here")
message("${CMAKE_CURRENT_SOURCE_DIR}/libprotobuf.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/libprotobuf.cmake")

# MediaPipe Formats
file(GLOB_RECURSE MP_FORMATS_SRC "${MEDIAPIPE_DIR}/bazel-bin/mediapipe/framework/formats/*.cc")
if(MSVC)
  # MSVC warning suppressions
  add_definitions(${MSVC_WARNINGS})
endif(MSVC)
add_library(MP_FORMATS STATIC ${MP_FORMATS_SRC})
target_include_directories(MP_FORMATS PUBLIC "${MEDIAPIPE_DIR}/bazel-bin")
target_link_libraries(MP_FORMATS libprotobuf)

# Process Abseil's CMake build system
add_subdirectory(abseil-cpp)

add_library(Hello_World SHARED hello2.cpp /drive2/research/code/face_utils_C/Authentiface_code/face_utils/facetools/representation/CNNEmbedding.cpp /drive2/research/code/face_utils_C/Authentiface_code/AppUtils/FrameAnalyze.cpp)

# Link against the libtorch libraries
target_link_libraries(Hello_World ${TORCH_LIBRARIES})
target_link_libraries(Hello_World ${OpenCV_LIBS} )
target_link_libraries(Hello_World LIBMP)
target_link_libraries(Hello_World MP_FORMATS)
# Declare dependency on the absl::strings library
target_link_libraries(Hello_World absl::strings)

### Post-build copies ###
# LibMP - MediaPipe Shared Library
add_custom_command(TARGET Hello_World POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${LIBMP_SHARED_LIBRARY}" "$<TARGET_FILE_DIR:Hello_World>"
    COMMENT "Copying ${LIBMP_SHARED_LIBRARY}"
)
# Mediapipe Modules
add_custom_command(TARGET Hello_World POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${MEDIAPIPE_DIR}/bazel-bin/mediapipe/modules" "$<TARGET_FILE_DIR:Hello_World>/mediapipe/modules"
    COMMENT "Copying mediapipe/modules"
)
# Mediapipe Models
add_custom_command(TARGET Hello_World POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${MEDIAPIPE_DIR}/bazel-bin/mediapipe/models" "$<TARGET_FILE_DIR:Hello_World>/mediapipe/models"
    COMMENT "Copying mediapipe/models"
)
# OpenCV (Windows only)
IF(WIN32)
	add_custom_command(TARGET Hello_World POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy "${LIBMP_BIN_DIR}/opencv_world460.dll" "$<TARGET_FILE_DIR:main>"
		COMMENT "Copying OpenCV DLL (Release)"
	)
ENDIF()