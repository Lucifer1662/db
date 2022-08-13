project ("db")

file(GLOB SRC
     "*.h"
     "*.cpp"
)

add_library(IO SHARED ${SRC})
target_include_directories(IO PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(IO PRIVATE IO=1.1)