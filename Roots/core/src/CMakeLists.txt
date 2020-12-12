file(GLOB ROOTS_H *.h)

set(ROOTS_SRC
    Roots.cpp
)

# ==================== #
# Build shared library #
# ==================== #
add_library(Roots SHARED ${ROOTS_SRC} ${ROOTS_H})

#####
#include_directories(${PROJECT_SOURCE_DIR}/../AutoDiff/)
#####

# Install targets into specific directories
install(TARGETS Roots
    RUNTIME DESTINATION bin/
    LIBRARY DESTINATION lib/
	ARCHIVE DESTINATION lib/
)

install(FILES ${ROOTS_H} DESTINATION include)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
