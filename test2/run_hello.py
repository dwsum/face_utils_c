import ctypes
import cv2
import numpy as np

# Load the shared library
# if ctypes.windll.kernel32:
#     lib = ctypes.CDLL('.make/Authentiface2.dll')  # Windows
# else:
lib = ctypes.CDLL('/drive2/research/code/face_utils_C/test2/build/libAuthentiface2.so')  # Linux


cam = cv2.VideoCapture(0)
ret, frame = cam.read()
cv2.imshow("frame in python", frame)
cv2.waitKey(1)
if ret:
    # print("inside")
    # print(type(frame))
    # print(frame.dtype)
    # print(type(mat.Mat.from_array(frame)))
    # opencv_matrix = cv2.cv.fromarray(image)
    # print(type(opencv_matrix))
    # Get image dimensions and channels
    height, width, channels = frame.shape
    print("here", height, width, channels)
    test = np.fromstring(frame, np.uint8)
    test = np.reshape(test, (height, width, channels))
    frame = test
    print("here2", test.shape)

    # Convert the NumPy array to a C-compatible data type
    image_data = frame.tostring()#frame.ctypes.data_as(ctypes.POINTER(ctypes.c_uint8))

    # print(type(np.ctypeslib.as_array(image_data, shape=(height * width * channels,))))

    # instance = hello_world.Predict(instance, frame)
    # out = hello_world.Predict(instance, image_data, width, height, channels)
else:
    raise Exception("no ret")

# Call the run function
lib.run(image_data, width, height, channels)