set(SRC
    echo.c
    cd.c
    executor.c
    export.c
    pipe.c)

add_library(exec_obj OBJECT ${SRC})
