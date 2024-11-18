cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

find_program(CLANG_EXECUTABLE clang)
find_program(CLANGXX_EXECUTABLE clang++)

# If clang is found, use it as the compiler
if(CLANG_EXECUTABLE AND CLANGXX_EXECUTABLE)
    message(STATUS "Using Clang compiler")
    set(CMAKE_C_COMPILER ${CLANG_EXECUTABLE})
    set(CMAKE_CXX_COMPILER ${CLANGXX_EXECUTABLE})
else()
    message(WARNING "Clang compiler not found, using default compiler")
endif()

project(lab_1_kudakov) 


IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message(" \n ——————————► DEBUG ◄——————————")
  # debugging information in a binary file
  add_compile_options( -g3 -O0 ) 

  #add_compile_options(-Werror) # turnsform  warnings into errors
  
  # Warnings include  
  add_compile_options(
    -pedantic-errors
    -Wall
    -Wextra
    -Wpedantic
    -Wfloat-equal
    -Wpointer-arith
    -Wstrict-overflow=5 
    -Wwrite-strings
    -Waggregate-return
    -Wswitch-default -Wswitch-enum
    -Wconversion
    -Wunreachable-code
    #-fstack-clash-protection -fstack-protector	-fcf-protection
    #-fasynchronous-unwind-tables


    #-Wcast-align
    #-Wcast-qual
    #-Wctor-dtor-privacy
    #-Wduplicated-branches
    #-Wduplicated-cond

    #-Wextra-semi
    #-Wlogical-op
    #-Wnon-virtual-dtor
    #-Wold-style-cast
  
    #-Woverloaded-virtual
    #-Wredundant-decls
    #-Wsign-conversion
    #-Wsign-promo
    #-Weffc++
    #-Woverloaded-virtual
    )

  IF(tsan)
    # https://clang.llvm.org/docs/ThreadSanitizer.html
    message("TREAD sanitazer ON") 
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fsanitize=thread  ")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -fsanitize=thread   ")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fsanitize=thread  ")
    add_compile_options(  -fsanitize=thread  ) 
  ENDIF()
  IF(asan) 
    # https://clang.llvm.org/docs/AddressSanitizer.html
    message("ADRESS sanitazer ON")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address ")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address  ")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address ")
    add_compile_options( -fsanitize=address  ) 
  ENDIF()

  IF(msan) 
    #https://clang.llvm.org/docs/MemorySanitizer.html
    message("MEMORY sanitazer ON")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory  -fno-omit-frame-pointer ")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=memory  -fno-omit-frame-pointer  ")
   SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=memory   -fno-omit-frame-pointer ")
    add_compile_options( -fsanitize=memory  -fno-omit-frame-pointer  -fno-optimize-sibling-calls -fno-sanitize-memory-use-after-dtor -fsanitize-recover=all -O1 ) 
  ENDIF()

  IF(ubsan) 
    #https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
    message("UB san  sanitazer ON")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=undefined")
    add_compile_options(-fsanitize=undefined  -fsanitize=signed-integer-overflow,null,alignment -fsanitize-recover=all) 
  ENDIF()

ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  message("————————► RELEASE ◄————————")

  
  add_compile_options(-O2 -DNDEBUG  -fomit-frame-pointer)
  add_compile_definitions(RELEASE)

ELSE()
  message( FATAL_ERROR "ALARM Build type abort")

ENDIF()

add_executable(test_sort main.cpp)
target_link_libraries(test_sort pthread)

IF(CMAKE_BUILD_TYPE MATCHES Release)
if( supported )
    message(STATUS "IPO / LTO enabled")
    set_property(TARGET test_sort PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()

ENDIF()