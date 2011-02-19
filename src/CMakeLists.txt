Find_Package(SDL REQUIRED)
Find_Package(SDL_image REQUIRED)
Find_package(Boost REQUIRED)
Find_package(OpenGL REQUIRED)

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
	key.cpp
	keyboard_handler.cpp
	mouse_handler.cpp
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
	${SDLIMAGE_INCLUDE_DIR}
	${SDL_image_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
)

link_directories(
	${Boost_LIBRARY_DIRS}
)

target_link_libraries(
	ymse
	${SDLIMAGE_LIBRARY}
	${SDL_LIBRARY}
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY}
)

set_target_properties(
	ymse
	PROPERTIES
	COMPILE_DEFINITIONS "GL_GLEXT_PROTOTYPES"
)

