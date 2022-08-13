project ("db")

file(GLOB SRC
     "*.h"
     "*.cpp"
)

add_subdirectory("BTreeIndex")
add_subdirectory("FixedDB")
add_subdirectory("IO")
add_subdirectory("FixedTable")

add_library(db_core SHARED ${SRC})
set_target_properties(db_core PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(db_core PUBLIC FixedDB BTreeIndex IO FixedTable)
target_include_directories(BTreeIndex PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(BTreeIndex PRIVATE)
