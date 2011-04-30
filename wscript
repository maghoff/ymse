#!/bin/env python
# -*- coding: utf-8 -*-


def options(opt):
	opt.load('compiler_cxx')
	opt.load('compiler_c')

	opt.add_option('--sdl-includes', dest='sdl_includes', default=None, action='store', help='The path that contains SDL.h')
	opt.add_option('--sdl-lib', dest='sdl_lib', default=None, action='store', help='The SDL library')

	opt.add_option('--sdl-image-includes', dest='sdl_image_includes', default=None, action='store', help='The path that contains SDL_image.h')
	opt.add_option('--sdl-image-lib', dest='sdl_image_lib', default=None, action='store', help='The SDL_image library')


def configure(conf):
	import sys, external
	sys.path.append('.')

	import pymse.wafutil as wafutil

	wafutil.msvc_initial_setup(conf.env)

	conf.load('compiler_cxx')
	conf.load('compiler_c')

	conf.check_cfg(package='sdl', uselib_store='SDL', args=['--cflags', '--libs'])
	conf.check_cfg(package='SDL_image', uselib_store='SDL_image', args=['--cflags', '--libs'])

	cc = wafutil.get_compiler_configurator(conf)

	cc.sane_default(conf.env)
	cc.many_warnings(conf.env)
	cc.warnings_as_errors(conf.env)

	core_env = conf.env.derive()

	from Options import options as opt

	if opt.sdl_includes != None:
		core_env.INCLUDES_SDL = [ opt.sdl_includes ]
	if opt.sdl_lib != None:
		core_env.LIBS_SDL = [ opt.sdl_lib ]

	if opt.sdl_image_includes != None:
		core_env.INCLUDES_SDL_image = [ opt.sdl_image_includes ]
	if opt.sdl_image_lib != None:
		core_env.LIBS_SDL_image = [ opt.sdl_image_lib ]

	debug_env = core_env.derive()
	cc.debug_mode(debug_env)
	conf.setenv('debug', env = debug_env)

	release_env = core_env.derive()
	cc.release_mode(release_env)
	cc.optimize(release_env)
	cc.link_time_code_generation(release_env)
	conf.setenv('release', env = release_env)

	external.do_import()
	external.configure(debug_env, release_env)


def core_build(bld):
	bld.add_subdirs('src')


# All of the following boiler plate is recommended (demanded) by the waf book for enabling build variants:

def build(bld):
	if not bld.variant:
		bld.fatal('call "waf build_debug" or "waf build_release", and try "waf --help"')

	core_build(bld)

from waflib.Build import BuildContext, CleanContext, InstallContext, UninstallContext

for x in ['debug', 'release']:
	for y in (BuildContext, CleanContext, InstallContext, UninstallContext):
		name = y.__name__.replace('Context','').lower()
		class tmp(y):
			cmd = name + '_' + x
			variant = x
