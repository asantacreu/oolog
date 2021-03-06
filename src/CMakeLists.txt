
cmake_minimum_required(VERSION 3.0)

project(oolog)

set(CMAKE_CXX_STANDARD 11)


set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 0)
set(${PROJECT_NAME}_VERSION_REVISION 0)


include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../include
)


configure_file(
    version.h.in
    version.h
)


set(SOURCES
    oolog.cpp
    printers/Console.cpp
    printers/File.cpp
    printers/Fake.cpp
    printers/RotatedFile.cpp
    printers/decorators/Decorator.cpp
    printers/decorators/Level.cpp
    printers/decorators/NewLine.cpp
    printers/decorators/Split.cpp
    printers/decorators/Timestamp.cpp
)

if(MSVC)
    set(SOURCES ${SOURCES}
        printers/decorators/ColorWin32Console.cpp
    )
else()
    set(SOURCES ${SOURCES}
        printers/decorators/ColorANSI.cpp
    )
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd -DOOLOG_EXPORTS")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /MT -DOOLOG_EXPORTS")
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME}-static STATIC ${SOURCES})


