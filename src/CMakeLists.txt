add_library( FFTlib
	SHARED
	FFTlib.cpp)

install( TARGETS FFTlib 
	DESTINATION lib)

find_package(FFTW3f REQUIRED COMPONENTS FLOAT_LIB)
target_include_directories(FFTlib PUBLIC ${FFTW3f_INCLUDE_DIRS})
target_link_libraries(FFTlib ${FFTW3f_LIBRARIES})

file(
	GLOB
	headers
	*.h)

install(FILES ${headers}
	DESTINATION include)
