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
	flags {
		"MultiProcessorCompile",
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
		qtpath (QTDIR_X86)
		targetdir ('../../bin/x86/')

	filter {'platforms:x86_64 or x64'}
		objdir ('../../bin/x64/obj/')
		qtpath (QTDIR_X64)
		targetdir ('../../bin/x64/')

	filter {}
