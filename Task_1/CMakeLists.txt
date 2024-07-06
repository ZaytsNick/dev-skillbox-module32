cmake_minimum_required (VERSION 3.8)
 project ("Task_1")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Task_1 "Task_1.cpp" )

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

#add_library(foo ...)

target_link_libraries(Task_1 PRIVATE nlohmann_json::nlohmann_json)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Task_1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
