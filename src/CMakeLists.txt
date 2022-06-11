cmake_minimum_required(VERSION 3.17)

include_directories(~/.local/include)
add_definitions(-DSPDLOG_FMT_EXTERNAL)

add_subdirectory(main)
add_subdirectory(shader)
add_subdirectory(vertex)
add_subdirectory(core)
add_subdirectory(client)
add_subdirectory(lightscene)
# add_subdirectory(game)
add_subdirectory(graphic)
add_subdirectory(physics)
add_subdirectory(light)
add_subdirectory(framebuffer)
add_subdirectory(lightroom)


project(Practice1)