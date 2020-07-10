if _ACTION == 'qmake' then
	require 'extensions/premake-qmake/qmake'
else
	require 'extensions/premake-qt/qt'
end

QTDIR_X86 = io.readfile('../../tmp/.qtdir_x86')
QTDIR_X64 = io.readfile('../../tmp/.qtdir_x64')

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

	dofile 'libs.lua'
	dofile 'demos.lua'
