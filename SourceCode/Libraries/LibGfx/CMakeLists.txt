PROJECT(Gfx C ASM)

aux_source_directory(${Gfx_SOURCE_DIR}/src LibGfxSrc)

add_library(${PROJECT_NAME}
        OBJECT
        ${LibGfxSrc})
target_include_libc_header_files(${PROJECT_NAME})
target_include_libgfx_header_files(${PROJECT_NAME})
target_include_raspberry_pi3_header_files(${PROJECT_NAME})
