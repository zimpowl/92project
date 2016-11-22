set(SRC
    echo.c
    executor.c
    pipe.c)

add_library(exec_obj OBJECT ${SRC})
