#!/usr/bin/env python

import os


class Exists:
	def __init__(self, path):
		self.path = path

	def __call__(self, installpath):
		return os.path.exists(os.path.join(installpath, self.path))


BOOST = {
	"name": "boost",
	"uri": "http://downloads.sourceforge.net/project/boost/boost/1.46.1/boost_1_46_1.zip",
	"target_path": "",
	"is_installed": Exists("boost_1_46_1"),
	"includes": "boost_1_46_1",
}

GLEW = {
	"name": "glew",
	"uri": "https://sourceforge.net/projects/glew/files/glew/1.5.8/glew-1.5.8.zip/download",
	"target_path": "",
	"is_installed": Exists("glew-1.5.8"),
	"includes": "glew-1.5.8/include",
}

PACKAGES = [
	BOOST,
	GLEW,
]


def extract_uri(uri, target_path, verbosity=1):
	import urllib2, zipfile, StringIO

	if verbosity >= 1: print "Downloading %s..." % uri
	f = urllib2.urlopen(uri)
	b = StringIO.StringIO(f.read())
	if verbosity >= 1: print "Extracting...",
	z = zipfile.ZipFile(b, 'r')
	z.extractall(target_path)
	if verbosity >= 1: print "done"


def do_import(verbosity=1):
	basepath = os.path.join(os.path.dirname(__file__), "downloads")

	for p in PACKAGES:
		installpath = os.path.join(basepath, p["target_path"])
		is_installed = p["is_installed"](installpath)

		if is_installed:
			if verbosity >= 1: print "%s already installed" % p["name"]
		else:
			extract_uri(p["uri"], installpath, verbosity)


def configure(debug_env, release_env):
	basepath = os.path.join(os.path.abspath(os.path.dirname(__file__)), "downloads")

	for package in PACKAGES:
		includes_property_name = 'INCLUDES_%s' % package['name']
		includepath = os.path.join(basepath, package['target_path'], package['includes'])
		setattr(debug_env, includes_property_name, includepath)
		setattr(release_env, includes_property_name, includepath)


if __name__ == '__main__':
	do_import()
