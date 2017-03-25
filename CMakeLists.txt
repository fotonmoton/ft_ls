cmake_minimum_required(VERSION 3.6)
project(ft_ls)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

include_directories(inc libft/includes) # headers
link_directories(libft) # libraries

set(SOURCE_FILES
        src/main.c
		) # sources

add_executable(ft_ls ${SOURCE_FILES}) # compilation

target_link_libraries(ft_ls -lft) # linkage
