# this function will dump all cmake predefined variables to the specific files
macro(dump_cmake_variables)
    get_cmake_property(variable_names VARIABLES)

    string(APPEND cmake_variables_dump_seprator "\n")
    foreach (index RANGE 100)
        string(APPEND cmake_variables_dump_seprator "--")
    endforeach ()
    string(APPEND cmake_variables_dump_seprator "\n")

    string(TIMESTAMP current_time "this file was generated at local time: %Y-%m-%dT%H:%M:%S")
    string(TIMESTAMP vars_dump_file_timestamp "%Y-%m-%d-%H-%M-%S")

    list(APPEND cmake_variables_list "${current_time}${cmake_variables_dump_seprator}")
    foreach (variable_name ${variable_names})
        list(APPEND cmake_variables_list "${variable_name}=${${variable_name}}${cmake_variables_dump_seprator}")
    endforeach ()

    set(cmake_variables_dump_dir ${CMAKE_BINARY_DIR}/cmake_variables_dump)
    # todo: SynestiaARCH here not working
    set(cmake_variables_dump_file ${cmake_variables_dump_dir}/cmake_variables_${vars_dump_file_timestamp}_${CMAKE_BUILD_TYPE}.txt)
    file(MAKE_DIRECTORY ${cmake_variables_dump_dir})
    file(WRITE ${cmake_variables_dump_file} ${cmake_variables_list})
    message("cmake variables have been saved to ${cmake_variables_dump_file}")
endmacro()
