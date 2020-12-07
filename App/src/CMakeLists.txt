# ================================= #
# Create variable called "MATRIX_H"
# ================================= #
file(GLOB APP_H *.h *.hpp)

# =================================== #
# Create variable called "MATRIX_SRC"
# =================================== #
set(APP_SRC
    main.cpp
)


# Create executable called "mixed" which depends on main.cpp
add_executable(app_demo main.cpp)

# Link our library "AutoDiffLibrary" to our executable
target_link_libraries(app_demo ${autodiff_lb})

# Install targets into specific directories
install(TARGETS app_demo
    RUNTIME DESTINATION bin/
    LIBRARY DESTINATION lib/
    ARCHIVE DESTINATION lib/
)

install(FILES ${APP_H} DESTINATION include)
