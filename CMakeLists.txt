cmake_minimum_required(VERSION 3.15...3.26)

set(CMAKE_CXX_STANDARD 17)

project(Tardis LANGUAGES C CXX ASM)

include(cmake/textfile2h.cmake)

# Try to import all Python components potentially needed by nanobind
find_package(Python 3.8
        REQUIRED COMPONENTS Interpreter Development.Module
        OPTIONAL_COMPONENTS Development.SABIModule)

execute_process(
        COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
        OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)

# Import nanobind through CMake's find_package mechanism
find_package(nanobind CONFIG REQUIRED)

find_package(fmt CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

add_subdirectory(third_party)

# ==================================================================================================
# ADD LIBS
# ==================================================================================================
add_subdirectory(src/libs)

set(BINDING_FILES
        src/py_binding/py_ad.cpp
        src/py_binding/py_tardis_ext.cpp
)

# We are now ready to compile the actual extension module
nanobind_add_module(
        # Name of the extension
        py_tardis_ext

        # Target the stable ABI for Python 3.12+, which reduces
        # the number of binary wheels that must be built. This
        # does nothing on older Python versions
        STABLE_ABI

        # Build libnanobind statically and merge it into the
        # extension (which itself remains a shared library)
        #
        # If your project builds multiple extensions, you can
        # replace this flag by NB_SHARED to conserve space by
        # reusing a shared libnanobind across libraries
        NB_STATIC

        # Source code goes here
        ${BINDING_FILES}
)

nanobind_add_stub(
        py_tardis_stub
        MODULE py_tardis_ext
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/tardis/__init__.pyi
        PYTHON_PATH $<TARGET_FILE_DIR:py_tardis_ext>
        DEPENDS py_tardis_ext
)

# ==================================================================================================
# LINK
# ==================================================================================================
target_include_directories(py_tardis_ext PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libs
        ${CPPAD_INCLUDE_DIRS}
)

#target_link_libraries(py_tardis_ext PRIVATE
#        tardis-lib
#)

# ==================================================================================================
# TEST
# ==================================================================================================
add_subdirectory(tests/cpp)

# ==================================================================================================
# INSTALL
# ==================================================================================================

file(GLOB PY_FILES "./src/tardis/*.py" "./src/tardis/*.pyi")

# Install directive for scikit-build-core
install(TARGETS py_tardis_ext LIBRARY DESTINATION tardis)
install(FILES ${PY_FILES} DESTINATION tardis)
