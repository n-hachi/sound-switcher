# Commandline parser library
FetchContent_Declare(
    clilib
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v1.9.0
    )
FetchContent_MakeAvailable(clilib)

# Insert git commit number
find_package(Git)
if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --always --abbrev=40 --dirty
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        OUTPUT_VARIABLE "COMMIT_HASH"
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    MESSAGE( STATUS "Git commit hash: ${COMMIT_HASH}" )
    MESSAGE( STATUS "Version: ${PROJECT_VERSION}" )
ELSE(GIT_FOUND)
    SET(BUILD_VERSION 0)
ENDIF(GIT_FOUND)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/version.h @ONLY)

add_executable(
    switcher
    main.cpp
    )

target_include_directories(
    switcher
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
    )

target_compile_features(
    switcher
    PRIVATE cxx_std_11
    )

target_link_libraries(
    switcher
    PRIVATE sound-switcher
    )
