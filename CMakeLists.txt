cmake_minimum_required(VERSION 3.6)
project(ft_ls)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -g")

link_directories(libft) # libraries
include_directories(inc libft/includes) # headers

set(SOURCE_FILES
        inc/ft_ls.h
        src/main.c
        src/ft_ls.c
        src/parse_input.c
        src/flags.c
        src/sort.c
        src/output.c
        src/error.c
        src/help_funcs.c
        src/stat_routine.c
        src/ft_ls_main_routine.c
        src/stat_parse.c
        src/long_output.c
        src/sort_funcs.c) # sources

add_executable(ft_ls ${SOURCE_FILES}) # compilation

target_link_libraries(ft_ls -lft) # linkage
