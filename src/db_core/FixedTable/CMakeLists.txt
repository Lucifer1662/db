project ("db")

file(GLOB SRC
     "*.h"
     "*.cpp"
)


add_library(FixedTable SHARED ${SRC})
set_target_properties(FixedTable PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(FixedTable PUBLIC BTreeIndex FixedDB)
target_include_directories(FixedTable PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(FixedTable PRIVATE)