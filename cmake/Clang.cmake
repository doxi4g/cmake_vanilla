# Set build-directive (used in core to tell which buildtype we used)
target_compile_definitions(metin2-compile-option-interface
  INTERFACE
    -D_BUILD_DIRECTIVE="${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-Wno-invalid-source-encoding")
if(WITH_WARNINGS)
  target_compile_options(metin2-warning-interface
    INTERFACE
      -W
      -Wall
      -Wextra
      -Winit-self
      -Wfatal-errors
      -Wno-mismatched-tags
      -Woverloaded-virtual)

  message(STATUS "Clang: All warnings enabled")
endif()

if(WITH_COREDEBUG)
  target_compile_options(metin2-compile-option-interface
    INTERFACE
      -g3)

  message(STATUS "Clang: Debug-flags set (-g3)")
endif()

# -Wno-narrowing needed to suppress a warning in g3d
# -Wno-deprecated-register is needed to suppress 185 gsoap warnings on Unix systems.
target_compile_options(metin2-compile-option-interface
  INTERFACE
    -Wno-narrowing
    -Wno-deprecated-register
    -Winvalid-source-encoding)