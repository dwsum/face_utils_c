import cv2
import ctypes
import numpy as np
# import mat

# Load the shared library
hello_world = ctypes.CDLL('/drive2/research/code/face_utils_C/build/libHello_World.so')  # Adjust the path as needed
# hello_world.Predict2.restype = ctypes.c_void_p
# Define the run function from the C++ library
# run = hello_world.run
# run.restype = None

# def run_hello_world():
#     run()

def run_hello_world():
    hello_world.run()

# def runCNNPredict():
print("before")
instance = hello_world.CreateCNNEmbedding()
print("after")
cam = cv2.VideoCapture(0)
ret, frame = cam.read()
cv2.imshow("frame in python", frame)
cv2.waitKey(1)
if ret:
    # print("inside")
    # print(type(frame))
    # print(frame.dtype)
    # # print(type(mat.Mat.from_array(frame)))
    # # opencv_matrix = cv2.cv.fromarray(image)
    # # print(type(opencv_matrix))
    # # Get image dimensions and channels
    # height, width, channels = frame.shape
    # print("here", height, width, channels)

    # # Convert the NumPy array to a C-compatible data type
    # image_data = frame.ctypes.data_as(ctypes.POINTER(ctypes.c_uint8))

    # print(type(np.ctypeslib.as_array(image_data, shape=(height * width * channels,))))

    height, width, channels = frame.shape
    test = np.fromstring(frame, np.uint8)
    test = np.reshape(test, (height, width, channels))
    frame = test

    # Convert the NumPy array to a C-compatible data type
    image_data = frame.tostring()#frame.ctypes.data_as(ctypes.POINTER(ctypes.c_uint8))

    # instance = hello_world.Predict(instance, frame)
    # out = hello_world.Predict(instance, image_data, width, height, channels)
    out = hello_world.Predict2(instance, image_data, width, height, channels)
    print("out", out)
# hello_world.ReleaseCNNEmbedding(instance)
print("done")

# if __name__ == '__main__':
#     run_hello_world()
#     runCNNPredict()
