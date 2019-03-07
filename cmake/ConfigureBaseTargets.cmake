# An interface library to make the target com available to other targets
add_library(metin2-compile-option-interface INTERFACE)

# Use -std=c++11 instead of -std=gnu++11
set(CXX_EXTENSIONS OFF)

# An interface library to make the target features available to other targets
add_library(metin2-feature-interface INTERFACE)

target_compile_features(metin2-feature-interface
  INTERFACE
    cxx_alias_templates
    cxx_auto_type
    cxx_constexpr
    cxx_decltype
    cxx_decltype_auto
    cxx_final
    cxx_lambdas
    cxx_generic_lambdas
    cxx_variadic_templates
    cxx_defaulted_functions
    cxx_nullptr
    cxx_trailing_return_types
    cxx_return_type_deduction)

# An interface library to make the warnings level available to other targets
# This interface taget is set-up through the platform specific script
add_library(metin2-warning-interface INTERFACE)

# An interface used for all other interfaces
add_library(metin2-default-interface INTERFACE)
target_link_libraries(metin2-default-interface
  INTERFACE
    metin2-compile-option-interface
    metin2-feature-interface)

# An interface used for silencing all warnings
add_library(metin2-no-warning-interface INTERFACE)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(metin2-no-warning-interface
    INTERFACE
      /W0)
else()
  target_compile_options(metin2-no-warning-interface
    INTERFACE
      -w)
endif()

# An interface library to change the default behaviour
# to hide symbols automatically.
add_library(metin2-hidden-symbols-interface INTERFACE)

# An interface amalgamation which provides the flags and definitions
# used by the dependency targets.
add_library(metin2-dependency-interface INTERFACE)
target_link_libraries(metin2-dependency-interface
  INTERFACE
    metin2-default-interface
    metin2-no-warning-interface
    metin2-hidden-symbols-interface)

# An interface amalgamation which provides the flags and definitions
# used by the core targets.
add_library(metin2-core-interface INTERFACE)
target_link_libraries(metin2-core-interface
  INTERFACE
    metin2-default-interface
    metin2-warning-interface)
