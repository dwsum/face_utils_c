set(SOURCE_FILES
    hello.cpp
)

# Set the path to your libtorch installation
set(TORCH_DIR "~/libtorch/")
find_package(Torch REQUIRED PATHS ${TORCH_DIR})
include_directories(${TORCH_INCLUDE_DIRS})

#opencv items
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_library(Authentiface2 SHARED ${SOURCE_FILES})

target_link_libraries(Authentiface2 ${TORCH_LIBRARIES})
target_link_libraries(Authentiface2 ${OpenCV_LIBS} )