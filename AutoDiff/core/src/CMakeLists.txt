file(GLOB AD_H *.h)

set(AD_SRC
    ADFunc.cpp
)

# ==================== #
# Build shared library #
# ==================== #
add_library(AutoDiff SHARED ${AD_SRC} ${AD_H})

# Install targets into specific directories
install(TARGETS AutoDiff
    RUNTIME DESTINATION bin/
    LIBRARY DESTINATION lib/
	ARCHIVE DESTINATION lib/
)

install(FILES ${AD_H} DESTINATION include)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)