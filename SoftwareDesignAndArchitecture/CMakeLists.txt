cmake_minimum_required(VERSION 3.16)
project(DesignPatterns LANGUAGES C CXX)

# ----------------------------------------------------------------------
# Usage:
#   cmake -B build -DTRACK=embedded -DDOMAIN=HardwareAccess -DPATTERN=HardwareProxy -DLANG=c
#   cmake -B build -DTRACK=embedded -DDOMAIN=HardwareAccess -DPATTERN=Observer -DLANG=cpp
#   cmake -B build -DTRACK=embedded -DDOMAIN=HardwareAccess -DPATTERN=HardwareProxy -DLANG=c -DMODE=exercise
#   cmake -B build -DTRACK=embedded -DDOMAIN=HardwareAccess -DPATTERN=HardwareAdapter -DLANG=c -DDEPS=HardwareProxy
#   cmake -B build -DTRACK=generic -DPATTERN=Strategy -DLANG=cpp
#   cmake --build build
#   ./build/<PatternName>
# ----------------------------------------------------------------------

# -- Options -----------------------------------------------------------
set(TRACK "" CACHE STRING "Track: generic | embedded | rtos")
set(DOMAIN "" CACHE STRING "Domain (embedded only): HardwareAccess | Concurrency | StateMachines | SafetyReliability")
set(PATTERN "" CACHE STRING "Pattern name (e.g., Observer, HardwareProxy)")
set(LANG "" CACHE STRING "Language: c | cpp")
set(MODE "src" CACHE STRING "Mode: src (reference demo) | exercise (your practice)")
set(DEPS "" CACHE STRING "Semicolon-separated dependency patterns (e.g., HardwareProxy)")

# -- Validation --------------------------------------------------------
if(NOT TRACK)
    message(FATAL_ERROR "TRACK not set. Use -DTRACK=generic|embedded|rtos")
endif()
if(NOT PATTERN)
    message(FATAL_ERROR "PATTERN not set. Use -DPATTERN=<PatternName>")
endif()
if(NOT LANG)
    message(FATAL_ERROR "LANG not set. Use -DLANG=c|cpp")
endif()

set(VALID_TRACKS generic embedded rtos)
if(NOT TRACK IN_LIST VALID_TRACKS)
    message(FATAL_ERROR "Invalid TRACK '${TRACK}'. Must be: generic, embedded, rtos")
endif()
if(NOT LANG STREQUAL "c" AND NOT LANG STREQUAL "cpp")
    message(FATAL_ERROR "Invalid LANG '${LANG}'. Must be: c, cpp")
endif()
if(NOT MODE STREQUAL "src" AND NOT MODE STREQUAL "exercise")
    message(FATAL_ERROR "Invalid MODE '${MODE}'. Must be: src, exercise")
endif()

# Validate DOMAIN when TRACK is embedded
set(VALID_DOMAINS HardwareAccess Concurrency StateMachines SafetyReliability)
if(TRACK STREQUAL "embedded")
    if(NOT DOMAIN)
        message(FATAL_ERROR
            "DOMAIN not set for embedded track.\n"
            "Use -DDOMAIN=HardwareAccess|Concurrency|StateMachines|SafetyReliability")
    endif()
    if(NOT DOMAIN IN_LIST VALID_DOMAINS)
        message(FATAL_ERROR "Invalid DOMAIN '${DOMAIN}'. Must be: HardwareAccess, Concurrency, StateMachines, SafetyReliability")
    endif()
endif()

# Map MODE to directory name
if(MODE STREQUAL "exercise")
    set(MODE_DIR "exercises")
else()
    set(MODE_DIR "src")
endif()

# -- Resolve source directory ------------------------------------------
# Embedded track uses domain sublayer: embedded/{src,exercises}/{lang}/{Domain}/{Pattern}
# Generic/RTOS tracks remain flat: {track}/{src,exercises}/{lang}/{Pattern}
if(TRACK STREQUAL "embedded")
    set(PATTERN_DIR "${CMAKE_SOURCE_DIR}/${TRACK}/${MODE_DIR}/${LANG}/${DOMAIN}/${PATTERN}")
else()
    set(PATTERN_DIR "${CMAKE_SOURCE_DIR}/${TRACK}/${MODE_DIR}/${LANG}/${PATTERN}")
endif()

if(NOT EXISTS "${PATTERN_DIR}")
    message(FATAL_ERROR
        "Pattern directory not found: ${PATTERN_DIR}\n"
        "Check TRACK=${TRACK}, PATTERN=${PATTERN}, LANG=${LANG}, MODE=${MODE}")
endif()

message(STATUS "Building: ${TRACK}/${MODE_DIR}/${LANG}/${PATTERN}")

# -- Compiler settings -------------------------------------------------
if(LANG STREQUAL "c")
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS OFF)
elseif(LANG STREQUAL "cpp")
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Warnings for learning -- catch mistakes early
add_compile_options(
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
    $<$<COMPILE_LANGUAGE:C>:-Wstrict-prototypes>
)

# -- Collect sources ---------------------------------------------------
if(LANG STREQUAL "c")
    file(GLOB_RECURSE SOURCES "${PATTERN_DIR}/*.c")
    file(GLOB_RECURSE HEADERS "${PATTERN_DIR}/*.h")
elseif(LANG STREQUAL "cpp")
    file(GLOB_RECURSE SOURCES "${PATTERN_DIR}/*.cpp")
    file(GLOB_RECURSE HEADERS "${PATTERN_DIR}/*.hpp")
endif()

# -- Collect dependency sources (cross-pattern) ------------------------
set(DEP_SOURCES "")
if(DEPS)
    foreach(DEP ${DEPS})
        # Dependencies use the same DOMAIN by default (embedded track)
        if(TRACK STREQUAL "embedded")
            set(DEP_DIR "${CMAKE_SOURCE_DIR}/${TRACK}/src/${LANG}/${DOMAIN}/${DEP}")
        else()
            set(DEP_DIR "${CMAKE_SOURCE_DIR}/${TRACK}/src/${LANG}/${DEP}")
        endif()
        if(NOT EXISTS "${DEP_DIR}")
            message(FATAL_ERROR "Dependency directory not found: ${DEP_DIR}")
        endif()
        if(LANG STREQUAL "c")
            file(GLOB_RECURSE _DEP_SRC "${DEP_DIR}/*.c")
            file(GLOB_RECURSE _DEP_HDR "${DEP_DIR}/*.h")
        else()
            file(GLOB_RECURSE _DEP_SRC "${DEP_DIR}/*.cpp")
            file(GLOB_RECURSE _DEP_HDR "${DEP_DIR}/*.hpp")
        endif()
        # Exclude dependency main.c/main.cpp to avoid duplicate main()
        list(FILTER _DEP_SRC EXCLUDE REGEX "main\\.(c|cpp)$")
        list(APPEND DEP_SOURCES ${_DEP_SRC} ${_DEP_HDR})
        message(STATUS "Dependency: ${DEP} -> ${_DEP_SRC}")
    endforeach()
endif()

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in ${PATTERN_DIR}")
endif()

# -- Build executable --------------------------------------------------
add_executable(${PATTERN} ${SOURCES} ${HEADERS} ${DEP_SOURCES})

# Include: the pattern directory itself + domain dir (for cross-pattern includes)
if(TRACK STREQUAL "embedded")
    target_include_directories(${PATTERN} PRIVATE
        "${PATTERN_DIR}"
        "${CMAKE_SOURCE_DIR}/${TRACK}/${MODE_DIR}/${LANG}/${DOMAIN}"
    )
else()
    target_include_directories(${PATTERN} PRIVATE
        "${PATTERN_DIR}"
        "${CMAKE_SOURCE_DIR}/${TRACK}/${MODE_DIR}/${LANG}"
    )
endif()

message(STATUS "Sources: ${SOURCES}")
message(STATUS "Target:  ${PATTERN}")
