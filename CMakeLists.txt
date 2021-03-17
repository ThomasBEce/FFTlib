#Define Cmake Version
cmake_minimum_required(VERSION 3.10)

#Define C++ compiler
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-lm -lfftw3f")

#Cmake instruction to make the static lib : FFTlib 
set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/fftw3f/fftw3/)

#Set Projet Name 
set(CMAKE_PROJET_NAME FFTlib)

#Cmake instructions to test using the static lib
add_subdirectory(src)
add_subdirectory(example)






