local function demo(prettyname, dirname)
	project (prettyname)
	premake.extensions.qt.enable()
	debugdir ('../../bin/%{cfg.platform}/')
	kind ('ConsoleApp')
	location ('../projects/demos/')
	objdir ('../../bin/%{cfg.platform}/obj/')
	qtgenerateddir ('../demos/' .. dirname .. '/GeneratedFiles/')
	qtprefix ('Qt5')
	targetdir ('../../bin/%{cfg.platform}/')

	files {
		'../demos/' .. dirname .. '/**.h',
		'../demos/' .. dirname .. '/**.cpp',
		'../demos/' .. dirname .. '/**.ui',
		'../demos/' .. dirname .. '/**.qrc',
	}
	flags {
		"MultiProcessorCompile",
	}
	includedirs {
		'../core/',
		'../demos/' .. dirname .. '/',
	}
	links {
		'QDiscordCore',
	}
	qtmodules {
		'core',
		'gui',
		'network',
		'websockets',
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
		qtpath (QTDIR_X86)

	filter {'platforms:x64'}
		qtpath (QTDIR_X64)

	filter {}
end

group ('Demos')
	demo ('BotDemo01', 'botdemo01')
	demo ('BotUser', 'botuser')
	demo ('Embeds', 'embeds')
