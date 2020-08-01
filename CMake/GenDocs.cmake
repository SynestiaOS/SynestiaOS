find_package(Doxygen REQUIRED)

file(GLOB_RECURSE KERNEL_HEADERS_FILES ${SYNESTIAOS_SOURCE_CODE_DIR}/*.h)
message("header files: ${KERNEL_HEADERS_FILES}")

set(GenDocsDIR ${SynestiaOS_SOURCE_DIR}/GenDocs)

set(DOXYGEN_INDEX_HTML ${GenDocsDIR}/html/index.html)
add_custom_command(OUTPUT ${DOXYGEN_INDEX_HTML}
        DEPENDS ${KERNEL_HEADERS_FILES}
        COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
        WORKING_DIRECTORY ${GenDocsDIR}
        #        MAIN_DEPENDENCY Doxyfile
        COMMENT "Generating docs")
add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_HTML})


find_package(Sphinx REQUIRED)
set(SPHINX_SOURCE ${GenDocsDIR}/source)
set(SPHINX_BUILD ${GenDocsDIR}/build)

add_custom_target(Sphinx ALL
        COMMAND
        ${SPHINX_EXECUTABLE} -b html -Dbreathe_projects.OSKernel=${GenDocsDIR}
        ${SPHINX_SOURCE}
        ${SPHINX_BUILD}
        COMMENT "Generating documentation with Sphinx")
