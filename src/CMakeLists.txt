cmake_minimum_required(VERSION 3.15)
project(PJ2_wesley.lucas C)

set(CMAKE_C_STANDARD 11)
set(ALLEGRO_DIR "C:\\MinGW")
include_directories(${ALLEGRO_DIR}/include)
link_directories(${ALLEGRO_DIR}/lib)

add_executable(PJ2_wesley.lucas PJ2_wesley.lucas.c LS_allegro.c LS_allegro.h opcion1.c opcion1.h ficheros.c ficheros.h estructuras.h sortedlist.h sortedlist.c opcion2.c opcion2.h opcion3.c opcion3.h menu.c menu.h)

target_link_libraries(PJ2_wesley.lucas -lmingw32 -lallegro-5.0.10-monolith-md-debug)