CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(SHELL_INPUT_LIB)

include_directories(
	"${PROJECT_SOURCE_DIR}/include/"
)

file(GLOB _SRCS
	"${PROJECT_SOURCE_DIR}/src/*.c"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_library(SHELL_INPUT_LIB ${_SRCS})
