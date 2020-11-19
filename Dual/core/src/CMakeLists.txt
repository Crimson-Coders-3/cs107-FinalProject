file(GLOB DUAL_H *.h)

set(DUAL_SRC
    Dual.cpp
)

# ==================== #
# Build shared library #
# ==================== #
add_library(Dual SHARED ${DUAL_SRC} ${DUAL_H})

# Install targets into specific directories
install(TARGETS Dual
    RUNTIME DESTINATION bin/
    LIBRARY DESTINATION lib/
	ARCHIVE DESTINATION lib/
)

install(FILES ${DUAL_H} DESTINATION include)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
