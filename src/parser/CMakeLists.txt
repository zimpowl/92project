set(SRC
    and_or_parser.c
    command_parser.c
    func_parser.c
    input_parser.c
    list_parser.c
    pipeline_parser.c
    redir_parser.c
    rules_parser.c
    shellcom_parser.c)

add_library(parser_obj OBJECT ${SRC})
