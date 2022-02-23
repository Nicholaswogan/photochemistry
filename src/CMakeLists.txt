
add_library(example types.cpp yaml_tools.cpp input.cpp)
target_link_libraries(example PUBLIC xtensor xtensor::optimize ${YAML_CPP_LIBRARIES})
target_include_directories(example PUBLIC ${YAML_CPP_INCLUDE_DIRS})
