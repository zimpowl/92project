set(SRC
    check.c
    fct_lexer.c
    string.c
    type.c
    lexer.c)

add_library(lexer_obj OBJECT ${SRC})
