cmake_minimum_required(VERSION 3.9)
project(LabC)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(INCLUDE_PATHS ${PROJECT_SOURCE_DIR}/include)
set(LIB_PATHS ${PROJECT_SOURCE_DIR}/lib)


include_directories(${INCLUDE_PATHS}/mysql/)
include_directories(${INCLUDE_PATHS}/mysql/cppconn/)
include_directories(${INCLUDE_PATHS}/pistache/)
include_directories(${INCLUDE_PATHS}/nlohmann/)
include_directories(${INCLUDE_PATHS}/crypt/)

link_directories(${LIB_PATHS}/mysql/lib/)
link_directories(${LIB_PATHS}/pistache/)
link_directories(${LIB_PATHS}/nlohmann/)
link_directories(${LIB_PATHS}/crypt/)

add_executable(LabC src/posts/Post.h src/posts/PostManager.cpp src/posts/PostManager.h src/storage/StorageManager.h src/users/User.h src/posts/Post.cpp src/Main.h src/Main.cpp src/users/User.cpp src/rest/RestHandler.cpp src/rest/RestHandler.h src/storage/MySQL.h src/storage/MySQL.cpp src/users/UserManager.cpp src/users/UserManager.h src/storage/JSON.cpp src/storage/JSON.h src/commandhandler/CommandHandler.cpp src/commandhandler/CommandHandler.h)

target_include_directories(LabC PRIVATE ${INCLUDE_PATHS})
target_include_directories(LabC PRIVATE ${LIB_PATHS})
target_link_libraries(LabC cryptopp pistache mysqlcppconn)
target_compile_features(LabC PRIVATE cxx_range_for)
