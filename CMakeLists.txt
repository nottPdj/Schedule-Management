cmake_minimum_required(VERSION 3.26)
project(projeto)

set(CMAKE_CXX_STANDARD 17)

add_executable(projeto main.cpp
        src/Schedule.cpp
        src/Schedule.h
        src/Student.cpp
        src/Student.h
        src/Class.cpp
        src/Class.h
        src/UC.cpp
        src/UC.h
        src/Lecture.h
        src/Lecture.cpp
        src/Terminal.h
        src/Terminal.cpp
        src/Course.h
        src/Course.cpp
        src/Auxiliar.cpp
        src/Auxiliar.h
        src/Request.h
        src/Request.cpp
        src/JoinRequest.h
        src/JoinRequest.cpp
        src/LeaveRequest.h
        src/LeaveRequest.cpp
        src/SwitchUcRequest.h
        src/SwitchUcRequest.cpp
        src/SwitchClassRequest.h
        src/SwitchClassRequest.cpp
)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

