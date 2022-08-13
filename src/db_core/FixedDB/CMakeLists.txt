project ("db")

file(GLOB SRC
     "*.h"
     "*.cpp"
)

add_library(FixedDB SHARED ${SRC})
target_link_libraries(FixedDB PUBLIC IO)
target_include_directories(FixedDB PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(FixedDB PRIVATE)
