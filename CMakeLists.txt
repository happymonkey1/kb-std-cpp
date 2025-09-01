cmake_minimum_required(VERSION 3.10)

project(kb-std VERSION "0.1.0" LANGUAGES C CXX)
include(CheckIncludeFileCXX)

set(CMAKE_CXX_STANDARD 20)

find_package(spdlog CONFIG REQUIRED)
find_package(fmt REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(KB_STD_STANDALONE ON)

    # configure project version
    # TODO
else()
    set(KB_STD_STANDALONE OFF)
endif()

if (MINGW)
    set(BUILD_SHARED_LIBS_DEFAULT OFF)
else()
    set(BUILD_SHARED_LIBS_DEFAULT OFF)
endif()

option(BUILD_SHARED_LIBS "build shared libraries" ${BUILD_SHARED_LIBS_DEFAULT})

option(KB_STD_BUILD_TESTS "kb-std: build tests" ${KB_STD_STANDALONE})

# TODO: optional msgpack serde

add_library(kb-std
        # include/kb
        include/kb/kb_core.h
        include/kb/kb_std.hpp

        # include/kb/core
        include/kb/core/logger.hpp
        include/kb/core/owning_buffer.hpp
        include/kb/core/types.hpp

        # include/kb/mem
        include/kb/mem/arena_allocator.hpp
        include/kb/mem/intrusive_shared_ref.hpp

        # src/kb
        src/kb/kb_core.cpp

        # src/kb/core
        src/kb/core/logger.cpp
        include/kb/kb_std.hpp
)

# Include dirs
target_include_directories(kb-std
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_include_directories(kb-std PRIVATE src)
target_include_directories(kb-std PUBLIC ${LIBCORO_INCLUDE_DIRS})

target_compile_features   (kb-std PRIVATE cxx_std_20)

# Link libs
target_link_libraries(kb-std PUBLIC spdlog::spdlog_header_only)
target_link_libraries(kb-std PUBLIC fmt::fmt)

if (BUILD_SHARED_LIBS)
    set_target_properties(kb-std PROPERTIES POSITION_INDEPENDENT_CODE ON)
    target_compile_definitions(kb-std PRIVATE KB_STD_BUILD)
    target_compile_definitions(kb-std PUBLIC  KB_STD_SHARED)
endif()

# Define KB_DEBUG or KB_RELEASE macro
target_compile_definitions(kb-std PRIVATE
    $<$<CONFIG:Debug>:KB_DEBUG>
    $<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>>:KB_RELEASE>
)

if (KB_STD_BUILD_TESTS)
    enable_testing()
    include(CTest)
    add_subdirectory(tests)
endif()

# CMake install
if (KB_STD_INSTALL)
    set(KB_STD_TARGETS_CONFIG_FILE "kb-stdConfigTargets.cmake")
    set(KB_STD_CONFIG_IN "${CMAKE_CURRENT_LIST_DIR}/cmake/kb-std-config.cmake.in")
    set(KB_STD_CONFIG_OUT "${CMAKE_CURRENT_BINARY_DIR}/kb-std-config.cmake")
    set(KB_STD_EXPORT_DEST_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/kb-std")
    set(KB_STD_VERSION_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/kb-stdConfigVersion.cmake")

    install(TARGETS kb-std
            EXPORT kb-std
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    export(TARGETS kb-std NAMESPACE kb-std::
            FILE "${CMAKE_CURRENT_BINARY_DIR}/${KB_STD_TARGETS_CONFIG_FILE}")
    install(EXPORT kb-std
            DESTINATION ${KB_STD_EXPORT_DEST_DIR}
            NAMESPACE kb-std::
            FILE ${KB_STD_TARGETS_CONFIG_FILE})
    install(DIRECTORY include/
            DESTINATION include
            FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
    )

    include(CMakePackageConfigHelpers)
    configure_package_config_file("${KB_STD_CONFIG_IN}" "${KB_STD_CONFIG_OUT}"
            INSTALL_DESTINATION ${KB_STD_EXPORT_DEST_DIR})

    write_basic_package_version_file("${KB_STD_VERSION_CONFIG_FILE}" COMPATIBILITY SameMajorVersion)
    install(FILES "${KB_STD_CONFIG_OUT}" "${KB_STD_VERSION_CONFIG_FILE}"
            DESTINATION "${KB_STD_EXPORT_DEST_DIR}")
endif ()

# TODO: copy_steam_to_ip_address vcpkg.json from root into vcpkg-overlays/kbnetworking/
