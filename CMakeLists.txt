CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(AUSI)

include_directories(
	"${PROJECT_SOURCE_DIR}/include/"
)

file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/src/*.c"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_library(AUSI STATIC ${SRCS})
