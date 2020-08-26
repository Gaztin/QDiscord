
require 'extensions/premake-qt/qt'
require 'customizations'
require 'options'

cppdialect 'C++17'
debugdir '../assets'
exceptionhandling 'Off'
flags { 'MultiProcessorCompile' }
includedirs { '../include/' }
objdir '../obj'
qtgenerateddir '../src/%{prj.name}/GeneratedFiles'
qtpath '%{_OPTIONS["qtdir"]}'
qtprefix 'Qt5'
rtti 'Off'
targetdir '../%{iif(prj.kind == "StaticLib" or prj.kind == "SharedLib","lib","bin")}/%{cfg.platform}/%{cfg.buildcfg}'
warnings 'Extra'

filter 'configurations:Debug'
	defines { 'DEBUG' }
	optimize 'Off'
	qtsuffix 'd'
	symbols 'On'

filter 'configurations:Release'
	defines { 'RELEASE', 'NDEBUG' }
	optimize 'Full'
	symbols 'Off'

filter 'system:windows'
	defines { 'NOMINMAX' }
	toolset 'msc'

filter 'system:not windows'
	toolset 'gcc'

filter 'system:linux'
	debugenvs { 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../%{OUTDIR}' }

filter { }
