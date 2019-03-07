include_directories("${CMAKE_SOURCE_DIR}/liblua/include")
add_executable(qc qc.cpp crc32.cpp crc32.h)
target_link_libraries(qc liblua)