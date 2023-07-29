cmake_minimum_required(VERSION 3.10)
project(maolanalsa VERSION 0.0.1 DESCRIPTION "ALSA backend for Maolan library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(GNUInstallDirs)

file(GLOB SRCS src/*.cpp src/audio/*.cpp src/midi/*.cpp)
file(GLOB HEADERS maolan/audio/alsa/*.hpp)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/maolan/audio/alsa)
set(MY_HEADERS ${MY_HEADEARS} ${HEADERS})
file(GLOB HEADERS maolan/midi/alsa/*.hpp)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/maolan/midi/alsa)
set(MY_HEADERS ${MY_HEADEARS} ${HEADERS})

enable_testing()
add_custom_target(build-tests)

find_package(PkgConfig REQUIRED)

pkg_check_modules(NLOHMANN REQUIRED nlohmann_json)
set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${NLOHMANN_INCLUDE_DIRS})
set(MY_LIBRARY_DIRS ${MY_LIBRARY_DIRS} ${NLOHMANN_LIBRARY_DIRS})
set(MY_LIBRARIES ${MY_LIBRARIES} ${NLOHMANN_LIBRARIES})

pkg_check_modules(MAOLAN REQUIRED libmaolan)
set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${MAOLAN_INCLUDE_DIRS})
set(MY_LIBRARY_DIRS ${MY_LIBRARY_DIRS} ${MAOLAN_LIBRARY_DIRS})
set(MY_LIBRARIES ${MY_LIBRARIES} ${MAOLAN_LIBRARIES})

pkg_check_modules(ALSA REQUIRED alsa)
set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${ALSA_INCLUDE_DIRS})
set(MY_LIBRARY_DIRS ${MY_LIBRARY_DIRS} ${ALSA_LIBRARY_DIRS})
set(MY_LIBRARIES ${MY_LIBRARIES} ${ALSA_LIBRARIES})

add_executable(test-playback EXCLUDE_FROM_ALL tests/playback.cpp)
target_link_directories(test-playback PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${MY_LIBRARY_DIRS})
target_link_libraries(test-playback maolanalsa ${MY_LIBRARIES})
add_dependencies(build-tests test-playback)

add_executable(test-load EXCLUDE_FROM_ALL tests/load.cpp)
target_link_directories(test-load PUBLIC ${MAOLAN_LIBRARY_DIRS})
target_link_libraries(test-load ${MAOLAN_LIBRARIES})
add_dependencies(build-tests test-load)

configure_file(libmaolanalsa.pc.in libmaolanalsa.pc @ONLY)
if (PKG_CONFIG_INSTALL_PATH)
    install(FILES ${PROJECT_BINARY_DIR}/libmaolanalsa.pc DESTINATION ${CMAKE_INSTALL_PREFIX}${PKG_CONFIG_INSTALL_PATH})
elseif (BSD)
    install(FILES ${PROJECT_BINARY_DIR}/libmaolanalsa.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/libdata/pkgconfig)
else()
    install(FILES ${PROJECT_BINARY_DIR}/libmaolanalsa.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX}/include ${MY_INCLUDE_DIRS})
link_directories(${CMAKE_INSTALL_PREFIX}/lib ${MY_LIBRARY_DIRS})
add_compile_options(-Wall -Werror)

add_library(maolanalsa SHARED ${SRCS} ${MY_HEADERS})
add_dependencies(build-tests maolanalsa)
target_link_libraries(maolanalsa ${MY_LIBRARIES})
install(TARGETS maolanalsa LIBRARY DESTINATION lib)
