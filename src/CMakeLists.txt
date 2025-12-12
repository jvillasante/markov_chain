set(PROGRAM_NAME random_english)
add_executable(${PROGRAM_NAME} ${PROGRAM_NAME}.cpp)
target_compile_features(${PROGRAM_NAME} PRIVATE cxx_std_23)
target_compile_options(${PROGRAM_NAME} PRIVATE
    $<$<CONFIG:Debug>:-Wall -Wextra -Werror -Wpedantic>
)

add_custom_command(
        TARGET ${PROGRAM_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/../data
                ${CMAKE_CURRENT_BINARY_DIR}/data)
