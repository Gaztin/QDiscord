local function demo(prettyname, dirname)
	project (prettyname)
	if premake.extensions.qt then
		premake.extensions.qt.enable()
		qtgenerateddir ('../demos/' .. dirname .. '/GeneratedFiles/')
		qtprefix ('Qt5')
		filter {'configurations:Debug'}
			qtsuffix ('d')
		filter {'architecture:x86'}
			qtpath (QTDIR_X86)
		filter {'architecture:x64'}
			qtpath (QTDIR_X64)
		filter {}
	end
	debugdir ('../../bin/%{cfg.platform}/')
	kind ('ConsoleApp')
	location ('../projects/demos/')
	objdir ('../../bin/%{cfg.platform}/obj/')
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
		symbols ('On')
		optimize ('Off')
	filter {'configurations:Release'}
		symbols ('Off')
		optimize ('Full')
		defines {
			'QT_NO_DEBUG',
		}

	filter {}
end

group ('Demos')
	demo ('BotDemo01', 'botdemo01')
	demo ('BotUser', 'botuser')
	demo ('Embeds', 'embeds')
