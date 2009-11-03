Find_Package(SDL REQUIRED)

add_library(
	ymse STATIC
	bindable_keyboard_handler.cpp
	core.cpp
	core_factory.cpp
	game.cpp
	gl_box_reshaper.cpp
	glut_core.cpp
	key.cpp
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

set_target_properties(
	ymse
	PROPERTIES
	COMPILE_FLAGS "-ggdb -ffast-math -pipe -fvisibility-inlines-hidden -Wall"
	COMPILE_DEFINITIONS "DEBUG;EBUG"
#	COMPILE_FLAGS "-O3 -ffast-math -pipe -fvisibility-inlines-hidden"
#	COMPILE_DEFINITIONS "NDEBUG;GL_GLEXT_PROTOTYPES"
)
