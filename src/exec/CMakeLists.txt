set(SRC
    echo.c
    executor.c
    export.c
    pipe.c)

add_library(exec_obj OBJECT ${SRC})
