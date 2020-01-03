cmake_minimum_required(VERSION 2.8.3)
project(rqt_timeplot)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
#-DEIGEN_USE_MKL_ALL")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  roscpp
  std_msgs
  cv_bridge
)

set(CMAKE_PREFIX_PATH /home/QT/5.7/gcc_64/lib/cmake/Qt5)
SET(Qt5_INCLUDE_DIRS /home/QT/5.7/gcc_64/include )
SET(Qt5_LIBRARIES  /home/QT/5.7/gcc_64/lib)
find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED)

find_package(Qt5PrintSupport REQUIRED)

set(HEARDERS include/rqt_timeplot/qcustomplot.h include/rqt_timeplot/widget.h include/rqt_timeplot/qnode.h include/rqt_timeplot/ui_widget.h)

#set(SRCS src/qcustomplot.cpp src/widget.cpp src/qnode.cpp  )

set(UI include/rqt_timeplot/widget.ui)

qt5_wrap_cpp(HEADERS_MOC ${HEARDERS})

qt5_wrap_ui(UI_UIC ${UI})

qt5_add_resources(RCC ${SRCS})


#qt5_wrap_cpp( MOC include/rqt_timeplot/qcustomplot.h)
#qt5_wrap_cpp( MOC include/rqt_timeplot/widget.h)
#qt5_wrap_cpp( MOC include/rqt_timeplot/qnode.h)
#qt5_wrap_cpp( MOC include/rqt_timeplot/ui_widget.h)



#qt5_generate_moc(qcustomplot.cpp src/qcustomplot.moc)
#qt5_generate_moc(widget.cpp src/widget.moc)
#qt5_generate_moc(qnode.cpp src/qnode.moc)
#qt5_generate_moc(rqt_plotTime.cpp src/rqt_plotTime.moc)


#find_package(Qt5Widgets REQUIRED)
#qt5_wrap_gui(UI widget.ui)
## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   nav_msgs#   std_msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES rqt_timeplot
#  CATKIN_DEPENDS Qt5 Qt5PrintSupport nav_msgs roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${Qt5PrintSupport_INCLUDE_DIRS}
  ${Qt5_INCLUDE_DIRS}
  include/rqt_timeplot
)

message("Qt5PrintSupport_INCLUDE_DIRS: ${Qt5PrintSupport_INCLUDE_DIRS}")
message("Qt5: ${Qt5_INCLUDE_DIRS}")
message("catkin_INCLUDE_DIRS: ${catkin_INCLUDE_DIRS}")

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/rqt_timeplot.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
#add_executable(${PROJECT_NAME}_node src/rqt_plotTime.cpp src/qcustomplot.cpp src/widget.cpp src/qnode.cpp)

add_executable(${PROJECT_NAME}_node  ${HEADERS_MOC} ${UI_UIC}  src/rqt_plotTime.cpp src/qcustomplot.cpp src/widget.cpp src/qnode.cpp  )

target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} ${Qt5PrintSupport_LIBRARIES} Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)



