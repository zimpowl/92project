set(SRC
    read_ast.c
    rules_ast.c
    func_ast.c)

add_library(readast_obj OBJECT ${SRC})
