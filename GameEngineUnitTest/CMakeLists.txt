set(PROJECT_NAME GameEngineUnitTest)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "App/MouseStateTest.cpp"
    "App/MouseStateTest.h"
    "App/SpriteTest.cpp"
    "App/SpriteTest.h"
    "App/TextureMapTest.cpp"
    "gepchTest.cpp"
    "ObjectTest.cpp"
)
source_group("" FILES ${no_group_source_files})

set(GE
    "GE/WindowTest.cpp"
    "GE/WindowTest.h"
)
source_group("GE" FILES ${GE})

set(GE__Graphics
    "GE/Graphics/RendererTest.cpp"
    "GE/Graphics/RendererTest.h"
)
source_group("GE\\Graphics" FILES ${GE__Graphics})

set(ALL_FILES
    ${no_group_source_files}
    ${GE}
    ${GE__Graphics}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE GameEngineUnitTest)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "GameEngineUnitTest"
    TARGET_NAME_DIST    "GameEngineUnitTest"
    TARGET_NAME_RELEASE "GameEngineUnitTest"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86/GameEngineUnitTest/"
    OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist-windows-x86/GameEngineUnitTest/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86/GameEngineUnitTest/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86/GameEngineUnitTest"
    ARCHIVE_OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist-windows-x86/GameEngineUnitTest"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86/GameEngineUnitTest"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_NAME_DEBUG   "GameEngineUnitTest"
    ARCHIVE_OUTPUT_NAME_DIST    "GameEngineUnitTest"
    ARCHIVE_OUTPUT_NAME_RELEASE "GameEngineUnitTest"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebug
    >
    $<$<CONFIG:Dist>:
        MultiThreaded
    >
    $<$<CONFIG:Release>:
        MultiThreaded
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Dist>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "$ENV{VCInstallDir}UnitTest/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/libs;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/libs/GLFW/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/libs/Glad/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/libs/spdlog/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/libs/stb_image;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/libs/glm;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/libs/imgui;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/libs/freetype/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/libs/freetype"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /ZI
        >
        $<$<CONFIG:Dist>:
            /Od;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        $<$<CONFIG:Release>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        /std:c++17;
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG;
            /INCREMENTAL
        >
        $<$<CONFIG:Dist>:
            /DEBUG:FULL;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /DEBUG:FULL;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /SUBSYSTEM:WINDOWS;
        /FORCE:MULTIPLE
    )
endif()

################################################################################
# Post build events
################################################################################
add_custom_command_if(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMANDS
    COMMAND   $<CONFIG:Debug> xcopy "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/>GameEngine/res" "${OUTPUT_DIRECTORY}/res" /e /y /i /r /d
)

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    GameEngine
    GLFW
    ImGui
    Glad
    freetype
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    GameEngine
    GLFW
    ImGui
    Glad
    freetype
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "opengl32;"
    "$(SolutionDir)bin-int/Debug-windows-x86/GameEngine/*.obj"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "$ENV{VCInstallDir}UnitTest/lib;"
    "${CMAKE_SOURCE_DIR}/GameEngine"
)

