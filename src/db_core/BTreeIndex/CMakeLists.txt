project ("db")

file(GLOB SRC
     "*.h"
     "*.cpp"
)

add_library(BTreeIndex SHARED ${SRC})
target_link_libraries(BTreeIndex PUBLIC FixedDB)
target_include_directories(BTreeIndex PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(BTreeIndex PRIVATE)
