
add_executable(person_test.cpp person_test.cpp)
target_link_libraries(test_person PRIVATE Catch2::Catch2WithMain)
target_include_directories(test_person PRIVATE "${CMAKE_SOURCE_DIR}/include")
