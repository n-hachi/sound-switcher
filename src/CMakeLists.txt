set(HEADER_LIST
    "${PROJECT_SOURCE_DIR}/include/sound/lib.hpp"
    )

# Make an automatic library
add_library(sound-switcher
    lib.cpp
    ${HEADER_LIST}
    )

# This library depends repositories include and rapidxml
target_include_directories(sound-switcher PUBLIC
    ../include
    )

# All users of this library will need at least C++11
target_compile_features(sound-switcher PUBLIC cxx_std_11)
