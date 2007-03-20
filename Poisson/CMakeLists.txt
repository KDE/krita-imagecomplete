include_directories(${CMAKE_CURRENT_BINARY_DIR} ./ ${GMM_INCLUDE_DIR})

set(Poissonlib_LIB_SRCS Algorithm.cc Pixel.cc ImageData.cc )

add_library(Poisson SHARED ${Poissonlib_LIB_SRCS})
install(TARGETS Poisson DESTINATION ${LIB_INSTALL_DIR})


