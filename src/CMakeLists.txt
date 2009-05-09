add_library(
	ymse STATIC
	core.cpp
	game.cpp
	gl_box_reshaper.cpp
	glut_core.cpp
	keyboard_handler.cpp
	reshaper.cpp
	vec.cpp
)

target_link_libraries(
	ymse
	GL
	glut
)
