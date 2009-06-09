Find_Package(SDL REQUIRED)

add_library(
	ymse STATIC
	bindable_keyboard_handler.cpp
	core.cpp
	core_factory.cpp
	game.cpp
	gl_box_reshaper.cpp
	glut_core.cpp
	keyboard_handler.cpp
	matrix.cpp
	matrix3d.cpp
	opposite_keys.cpp
	reshaper.cpp
	sdl_core.cpp
	vec.cpp
)

include_directories(
	${SDL_INCLUDE_DIR}
)

target_link_libraries(
	ymse
	GL
	glut
	${SDL_LIBRARY}
)
