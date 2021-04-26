cmake_minimum_required(VERSION 3.17)
project(Datos_2_Proyecto_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Cliente-Servidor Cliente-Servidor/ClienteRes)

set(EXECUTABLE_NAME "cliente")
set(EXECUTABLE_NAME2 "mserver")
#set(EXECUTABLE_NAME3 "Manager")
add_executable(${EXECUTABLE_NAME} Cliente-Servidor/cliente.cpp)
add_executable(${EXECUTABLE_NAME2} Cliente-Servidor/servidor.cpp)
#add_executable(${EXECUTABLE_NAME3} Cliente-Servidor/MemoryManager.cpp)


target_link_libraries(mserver sfml-network)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()