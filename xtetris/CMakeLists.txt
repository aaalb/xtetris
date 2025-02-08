cmake_minimum_required(VERSION 3.21)
project(xtetris C)

set(CMAKE_C_STANDARD 90)

link_directories(/opt/homebrew/opt/ncurses/lib)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic-errors -O3")

add_executable(xtetris main.c Field.c Field.h Game.c Game.h GameGraphics.c GameGraphics.h MenuGraphics.c MenuGraphics.h Moves.c Moves.h Pieces.c Pieces.h Player.c Player.h)
target_link_libraries(xtetris menu ncurses)