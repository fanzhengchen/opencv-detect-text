cmake_minimum_required(VERSION 3.7)
project(opencv_crop_image)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(opencv_crop_image ${SOURCE_FILES})

target_link_libraries(opencv_crop_image
        opencv_stitching opencv_superres opencv_videostab
        opencv_photo opencv_aruco opencv_bgsegm
        opencv_bioinspired opencv_ccalib opencv_dpm
        opencv_face opencv_fuzzy opencv_img_hash
        opencv_line_descriptor opencv_optflow
        opencv_reg opencv_rgbd opencv_saliency opencv_stereo
        opencv_structured_light opencv_phase_unwrapping
        opencv_surface_matching opencv_tracking
        opencv_datasets opencv_text opencv_dnn
        opencv_plot opencv_xfeatures2d opencv_shape
        opencv_video opencv_ml opencv_ximgproc
        opencv_calib3d opencv_features2d opencv_highgui
        opencv_videoio opencv_flann opencv_xobjdetect
        opencv_imgcodecs opencv_objdetect opencv_xphoto
        opencv_imgproc opencv_core)