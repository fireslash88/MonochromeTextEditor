cmake_minimum_required(VERSION 3.24)
project(TextEditor)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

foreach (CONFIG Debug Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG}
    ${CMAKE_BINARY_DIR}/bin/${CONFIG}
    )
endforeach ()

# Fetch and compile Raylib
set(RAYLIB_VERSION 6.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if(NOT raylib_FOUND)
    include(FetchContent)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_MakeAvailable(raylib)
endif()


# Include files in the src
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/core/editor.h
        src/core/editor.cpp
        src/settings/config.h
        src/core/EditorControls.cpp
        src/core/TextBuffer.h
        src/core/TextBuffer.cpp
        src/ui/UIDraw.cpp
        src/ui/UIDraw.h
        src/ui/UIDrawDebug.cpp
        src/external/gui_window_file_dialog.h
)

# Include eventual directories
target_include_directories(${PROJECT_NAME} PRIVATE
        src/external/raygui
        fonts-styles
)

# Include raylib library
target_link_libraries(${PROJECT_NAME} raylib)

if(WIN32)
    if(MSVC)
        target_link_options(${PROJECT_NAME} PRIVATE
                "$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>"
                "$<$<CONFIG:Release>:/ENTRY:mainCRTStartup>"
        )
    elseif(MINGW)
        target_link_options(${PROJECT_NAME} PRIVATE
                "$<$<CONFIG:Release>:-mwindows>"
        )
        target_link_options(${PROJECT_NAME} PRIVATE
                -static-libgcc
                -static-libstdc++
        )
    endif()
endif()

foreach(ASSET_DIR fonts-styles)
    if(EXISTS "${CMAKE_SOURCE_DIR}/${ASSET_DIR}")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/${ASSET_DIR}"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${ASSET_DIR}"
                COMMENT "Copying ${ASSET_DIR}..."
                VERBATIM
        )
    else()
        message(WARNING "Asset directory not found: ${CMAKE_SOURCE_DIR}/${ASSET_DIR}")
    endif()
endforeach()

# Installation / packaging
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION .
)

install(DIRECTORY fonts-styles/
        DESTINATION fonts-styles
)