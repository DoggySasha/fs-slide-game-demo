cmake_minimum_required(VERSION 3.12)
project(slide_game)
set(slide_game_PROJECT_NAME slide_game)

set(slide_game_SOURCES
	src/main.cpp
)

add_executable(${slide_game_PROJECT_NAME}
	${slide_game_SOURCES}
)

target_link_libraries(${slide_game_PROJECT_NAME} xengine)
target_compile_features(${slide_game_PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${slide_game_PROJECT_NAME} PRIVATE src)

set_target_properties(slide_game PROPERTIES FOLDER "XEngine")
