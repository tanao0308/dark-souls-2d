# version 1.2
set(CPM_USE_NAMED_CACHE_DIRECTORIES ON)

# If not in release, try to use local-installed packages rather than fresh ones
if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CPM_USE_LOCAL_PACKAGES ON)
endif()

# Required to be able to fetch dependencies with CPM
include(./cmake/CPM.cmake)

# Now declare all dependencies
CPMAddPackage(
    URI "gh:libsdl-org/SDL#release-3.2.18"
    NAME SDL3
    SYSTEM
)
CPMAddPackage(
    URI "gh:libsdl-org/SDL_image#release-3.2.4"
    NAME SDL3_image
    OPTIONS "SDLIMAGE_AVIF OFF"
    "SDLIMAGE_BMP OFF"
    "SDLIMAGE_JPG OFF"
    "SDLIMAGE_WEBP OFF"
    "SDLIMAGE_GIF OFF"
    "SDLIMAGE_LBM OFF"
    "SDLIMAGE_PCX OFF"
    "SDLIMAGE_PNM OFF"
    "SDLIMAGE_QOI OFF"
    "SDLIMAGE_SVG OFF"
    "SDLIMAGE_TIF OFF"
    "SDLIMAGE_XCF OFF"
    "SDLIMAGE_XPM OFF"
    "SDLIMAGE_XV OFF"
    "SDLIMAGE_VENDORED ON"
    SYSTEM
)
CPMAddPackage(
    URI "gh:chalonverse/SDL_mixer#fix-undefined-warning"
    OPTIONS "SDLMIXER_MIDI_NATIVE OFF"
    "SDLMIXER_GME OFF"
    "SDLMIXER_WAVPACK OFF"
    "SDLMIXER_MOD OFF"
    "SDLMIXER_OPUS OFF"
    "SDLMIXER_FLAC OFF"
    "SDLMIXER_MP3 OFF"
    "SDLMIXER_MIDI OFF"
    "SDLMIXER_VENDORED ON"
    SYSTEM
)
CPMAddPackage(
    URI "gh:libsdl-org/SDL_ttf#release-3.2.2"
    NAME SDL3_ttf
    OPTIONS "SDLTTF_PLUTOSVG OFF" # Disable Pluto SVG because it kills linking on MinGW
	"SDLTTF_HARFBUZZ OFF" # Ditto
    "SDLTTF_VENDORED ON"
    SYSTEM
)

# Emscripten already includes GLEW support natively
if (NOT EMSCRIPTEN)
    CPMAddPackage(
        URI "gh:chalonverse/glew-cmake#glew-cmake-release"
        OPTIONS "glew-cmake_BUILD_SHARED OFF"
        SYSTEM
    )
endif()
