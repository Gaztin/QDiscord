project ('QDiscordCore')
	if premake.extensions.qt then
		premake.extensions.qt.enable()
		qtgenerateddir ('../core/GeneratedFiles/')
		qtprefix ('Qt5')
		filter {'architecture:x86'}
			qtpath (QTDIR_X86)
		filter {'architecture:x86_64'}
			qtpath (QTDIR_X64)
		filter {}
	end
	targetname ('QDiscord')
	targetdir ('../../lib/%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}')
	objdir ('../../bin/%{cfg.architecture}/obj/')
	location ('../projects/')
	kind ('StaticLib')
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

	filter {'configurations:Debug'}
		symbols ('On')
		optimize ('Off')
	filter {'configurations:Release'}
		symbols ('Off')
		optimize ('Full')
		defines {
			'QT_NO_DEBUG',
		}

	filter {}
