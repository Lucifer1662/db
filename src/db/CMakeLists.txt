project ("db")

add_executable (db "main.cpp")

target_link_libraries(db PUBLIC db_core)

