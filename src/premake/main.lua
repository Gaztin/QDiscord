require 'extensions/premake-qt/qt'

local qtdir_x86 = io.readfile('../../tmp/.qtdir_x86')
local qtdir_x64 = io.readfile('../../tmp/.qtdir_x64')

workspace ('QDiscord')
	location ('../')
	configurations {
		'Debug',
		'Release',
	}
	platforms {
		'x86',
		'x64',
	}

project ('QDiscordCore')
	premake.extensions.qt.enable()
	location ('../projects/')
	kind ('StaticLib')
	qtgenerateddir ('../core/GeneratedFiles/')
	qtprefix ('Qt5')
	files {
		'../core/**.h',
		'../core/**.cpp',
	}
	includedirs {
		'../core/',
	}

	filter {'configurations:Release'}
		optimize ('Full')
		defines {
			'QT_NO_DEBUG',
		}

	filter {'platforms:x86'}
		objdir ('../../bin/x86/obj/')
		qtpath (qtdir_x86)
		targetdir ('../../bin/x86/')

	filter {'platforms:x64'}
		objdir ('../../bin/x64/obj/')
		qtpath (qtdir_x64)
		targetdir ('../../bin/x64/')

	filter {}

project ('Demo')
	premake.extensions.qt.enable()
	dependson ('QDiscordCore')
	location ('../projects/')
	kind ('ConsoleApp')
	qtgenerateddir ('../demo/GeneratedFiles/')
	qtprefix ('Qt5')
	files {
		'../demo/**.h',
		'../demo/**.cpp',
		'../demo/**.ui',
		'../demo/**.qrc',
	}
	includedirs {
		'../core/',
		'../demo/',
	}
	links {
		'QDiscordCore',
	}
	qtmodules {
		'core',
		'gui',
		'widgets',
	}

	filter {'configurations:Debug'}
		qtsuffix ('d')

	filter {'configurations:Release'}
		optimize ('Full')
		defines {
			'QT_NO_DEBUG',
		}

	filter {'platforms:x86'}
		debugdir ('../../bin/x86/')
		objdir ('../../bin/x86/obj/')
		qtpath (qtdir_x86)
		targetdir ('../../bin/x86/')

	filter {'platforms:x64'}
		debugdir ('../../bin/x64/')
		objdir ('../../bin/x64/obj/')
		qtpath (qtdir_x64)
		targetdir ('../../bin/x64/')

	filter {}