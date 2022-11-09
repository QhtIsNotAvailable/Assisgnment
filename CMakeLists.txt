cmake_minimum_required (VERSION 3.8) 

project(alist)

set(CMAKE_CXX_STANDARD 17)

include(CheckCXXCompilerFlag)
include(CMakePushCheckState)

if(MSVC)
  set(CMAKE_CXX_FLAGS "/O2 /Zi")
else()
  add_compile_options("-O2" "-g")
  cmake_push_check_state(RESET)
  set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
  check_cxx_compiler_flag("-fsanitize=address" ASAN_AVAIL)
  check_cxx_compiler_flag("-fsanitize=undefined" UBSAN_AVAIL)
  cmake_pop_check_state()
  if(UBSAN_AVAIL AND ASAN_AVAIL)
    add_compile_options("-fsanitize=undefined" "-fsanitize=address" "-fno-sanitize-recover=all" )
    add_link_options("-fsanitize=undefined" "-fsanitize=address" "-fno-sanitize-recover=all")
  else()
    message(WARNING
      "Your C compiler does not support address sanitizer!"
      "Auto grading uses them to detect memory leaks and undefined behaviour."
      "Your local testing may pass but if it contains such behaviour, there may be runtime error when autograding."
      )
  endif()
endif()

add_executable(alist main.cpp)

