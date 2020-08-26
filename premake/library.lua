
require 'extensions/premake-qt/qt'

libraries = { }

function library( name )
	group 'Libraries'
	project( name )

	kind 'StaticLib'
	links( libraries )
	location 'build/%{_ACTION}'
	qtgenerateddir 'src/%{prj.name}/GeneratedFiles'

	files {
		'include/**.h',
		'src/%{prj.name}/**.cpp',
		'src/%{prj.name}/**.h',
	}
	
	premake.extensions.qt.enable()

	filter 'system:macosx or ios'
		files { 'src/%{prj.name}/**.mm' }

	filter { 'system:macosx or ios', 'files:**.cpp' }
		compileas 'Objective-C++'

	filter { }

	table.insert( libraries, name )
end
