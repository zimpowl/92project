set (CMAKE_C_FLAGS "-Wall -Wextra -Werror -std=c99 -pedantic -g")

include_directories(src/include)

add_subdirectory(src/exec)
add_subdirectory(src/parser)
add_subdirectory(src/lexer)
add_subdirectory(src/tree)
add_subdirectory(src/ast_reader)

set(SRC
    src/42sh.c
    $<TARGET_OBJECTS:parser_obj>
    $<TARGET_OBJECTS:exec_obj>
    $<TARGET_OBJECTS:tree_obj>
    $<TARGET_OBJECTS:readast_obj>
    $<TARGET_OBJECTS:lexer_obj>)

add_custom_target(ast
  COMMAND dot mondot.dot -Tpng -o hello.png
  COMMAND eog hello.png)

add_custom_target(check 
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/42sh ../tests
    COMMAND ../tests/./install.sh
    COMMAND ./tests.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)

add_executable(42sh ${SRC})
