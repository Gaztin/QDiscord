
require 'library'
require 'settings'
require 'third_party_library'

apps = { }

function app( name )
	group 'Apps'
	project( name )

	debugdir 'src/%{prj.name}/Assets'
	kind 'WindowedApp'
	links( libraries )
	links( third_party_libraries )
	location 'build/%{_ACTION}'
	sysincludedirs { 'include' }
	xcodebuildresources 'src/%{prj.name}/Assets'

	files {
		'src/%{prj.name}/**.cpp',
		'src/%{prj.name}/**.h',
	}

	filter 'system:linux'
		linkoptions { '-Wl,-rpath=\\$$ORIGIN' }

	filter 'system:ios'
		files { 'src/%{prj.name}/Resources/Info.plist', 'src/%{prj.name}/Assets' }

	filter { 'system:macosx or ios', 'files:**.cpp' }
		compileas 'Objective-C++'

	filter { }

	table.insert( apps, name )
end
