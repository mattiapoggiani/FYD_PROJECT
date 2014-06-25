cmake_minimum_required(VERSION 2.8)
project(FYD_PROJECT)

include_directories(${CMAKE_SOURCE_DIR}/include)

#This is not the best practices but for now it is working. The bes practice is to code a Find*.cmake file
#include FRI Library from Stanford
add_definitions(-D__LINUX__ -Wall)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

#find_package(Eigen REQUIRED Dense Geometry)
#include_directories( ${Eigen_INCLUDE_DIRS} )

execute_process(COMMAND tar -xf ../FRILibrary.tar.gz)
execute_process(COMMAND make -C FRILibrary/Linux)
set(FRILibrary ${CMAKE_SOURCE_DIR}/build/FRILibrary)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/input_files
                                                           ${CMAKE_BINARY_DIR}/input_files)

include_directories(${FRILibrary}/include/)
include_directories(/usr/include/eigen3)
include_directories(${Boost_INCLUDE_DIRS})

set(QT_USE_QTOPENGL TRUE)
set(QT_USE_QTXML TRUE)
set(QT_INCLUDE_DIR ${QT_ROOT}/include)
set(CMAKE_AUTOMOC ON)

set(LIBS  
	-L${FRILibrary}/Linux/x64/release/lib/ 
	-lFastResearchInterfaceLibrary 
	-lTypeIRML 
	-m64  
	-pthread 
	-ldl 
	-lm 
	-lpthread 
	-lrt
        -lphidget21
        -lopencv_core 
        -lopencv_highgui
)

add_executable(FYD_PROJECT src/wireless_communicator.cpp src/FYD_Client.cpp src/functions.cpp src/conio.cpp src/accelerometers.cpp src/flexiforce.cpp src/main.cpp mainwindow.cpp)

#add_executable(FYD_PROJECT mainwindow.cpp)

target_link_libraries(FYD_PROJECT 
	${LIBS}
	${Boost_LIBRARIES}
	${OpenCV_LIBS}
	${QT_LIBRARIES}
	)

