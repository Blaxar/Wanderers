file(GLOB_RECURSE Wanderers_src_files *.cpp)

add_executable(Wanderers ${Wanderers_src_files})
target_link_libraries(Wanderers ${GL_LIBS})
set_target_properties(Wanderers PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DEFAULT_BIN_DIR})
