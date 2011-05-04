#!/bin/env python
# -*- coding: utf-8 -*-


def options(opt):
	opt.load('compiler_cxx')
	opt.load('compiler_c')

	opt.add_option('--sdl', dest='sdl_root', default=None, action='store', help='The path that contains include/SDL.h')
	opt.add_option('--sdl-image', dest='sdl_image_root', default=None, action='store', help='The path that contains include/SDL_image.h')


def configure(conf):
	import os, sys, external
	sys.path.append('.')

	import pymse.wafutil as wafutil

	wafutil.msvc_initial_setup(conf.env)

	conf.load('compiler_cxx')
	conf.load('compiler_c')

	cc = wafutil.get_compiler_configurator(conf)

	cc.sane_default(conf.env)
	cc.many_warnings(conf.env)
	cc.warnings_as_errors(conf.env)

	core_env = conf.env.derive()

	from Options import options as opt

	if opt.sdl_root == None:
		conf.check_cfg(package='sdl', uselib_store='SDL', args=['--cflags', '--libs'])
	else:
		core_env.INCLUDES_SDL = [ os.path.join(opt.sdl_root, 'include') ]
		core_env.LIBPATH_SDL = [ os.path.join(opt.sdl_root, 'lib') ]
		core_env.LIB_SDL = [ 'SDL' ]

	core_env.LIB_SDLmain = [ 'SDLmain' ]

	if opt.sdl_image_root == None:
		conf.check_cfg(package='SDL_image', uselib_store='SDL_image', args=['--cflags', '--libs'])
	else:
		core_env.INCLUDES_SDL_image = [ os.path.join(opt.sdl_image_root, 'include') ]
		core_env.LIBPATH_SDL_image = [ os.path.join(opt.sdl_image_root, 'lib') ]
		core_env.LIB_SDL_image = [ 'SDL_image' ]

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
