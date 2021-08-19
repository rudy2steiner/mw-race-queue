cmake_minimum_required(VERSION 3.0)

project(queue_race)
# set 设置变量名,不区分大小写
set(CMAKE_CXX_STANDARD 11)
#SET(CMAKE_CXX_FLAGS "-pg")
SET(CMAKE_CXX_FLAGS "-O0")
# 输出中间结果到屏幕
MESSAGE (STATUS ${PROJECT_SOURCE_DIR})
# 头文件依赖
include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCE_FILES queue_store.cpp include/store_io.h store_io.cpp include/message_queue.h message_queue.cpp include/idle_page_manager.h idle_page_manager.cpp include/commit_service.h commit_service.cpp include/buffer_pool.h buffer_pool.cpp read_ahead_service.cpp include/read_ahead_service.h)

# 编译库 STATIC/SHARE(静态/动态库)
add_library(queue_race SHARED ${SOURCE_FILES})

# In case you need boost::filesystem
#target_link_libraries(queue_race boost_filesystem boost_system)

# In case you need lz4
#target_link_libraries(queue_race lz4)

# In case you need lzma
#target_link_libraries(queue_race lzma)

# In case you need snappy
#target_link_libraries(queue_race snappy)

# In case you need lz
#target_link_libraries(queue_race z)

target_link_libraries(queue_race pthread)

set(tbb_include /usr/local/opt/tbb/include)
set(tbb_lib /usr/local/opt/tbb/lib)
# 声明头文件依赖目录
include_directories(${tbb_include})
# 声明库依赖目录
link_directories(${tbb_Lib})

link_libraries(tdd)
# 添加三方库
target_link_libraries(queue_race tbb)

#target_link_libraries(queue_race profiler)
# 在 source dir 寻找对应的CMakefile.txt
add_subdirectory(example)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION include)
install(TARGETS queue_race
        LIBRARY DESTINATION lib)

#ref: https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html