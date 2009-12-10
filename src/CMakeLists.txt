Find_Package(SDL REQUIRED)
Find_Package(SDL_image REQUIRED)

add_library(
	ymse STATIC
	gl/program.cpp
	gl/shader.cpp
	gl/texture.cpp
	sdl/img_load.cpp
	sdl/surface.cpp
	bindable_keyboard_handler.cpp
	core.cpp
	core_factory.cpp
	fileutil.cpp
	game.cpp
	geometry_intersection.cpp
	gl_box_reshaper.cpp
	glut_core.cpp
	key.cpp
	keyboard_handler.cpp
	load_image.cpp
	matrix.cpp
	matrix3d.cpp
	opposite_keys.cpp
	opposite_keys_listener.cpp
	pixels_per_unit_listener.cpp
	rect.cpp
	reshaper.cpp
	sdl_core.cpp
	signaling_opposite_keys.cpp
	vec.cpp
)

include_directories(
	${SDL_INCLUDE_DIR}
)

target_link_libraries(
	ymse
	${SDLIMAGE_LIBRARY}
	${SDL_LIBRARY}
	GL
#	glut
)

set_target_properties(
	ymse
	PROPERTIES
	COMPILE_FLAGS "-ggdb -ffast-math -pipe -fvisibility-inlines-hidden -Wall"
	COMPILE_DEFINITIONS "DEBUG;EBUG;GL_GLEXT_PROTOTYPES"
#	COMPILE_FLAGS "-O3 -ffast-math -pipe -fvisibility-inlines-hidden"
#	COMPILE_DEFINITIONS "NDEBUG;GL_GLEXT_PROTOTYPES"
)
