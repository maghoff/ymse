add_library(
	ymse STATIC
	core.cpp
	game.cpp
	gl_box_reshaper.cpp
	glut_core.cpp
	reshaper.cpp
)

target_link_libraries(
	ymse
	GL
	glut
)
