
-- Add switch to target iOS instead of macOS
if _TARGET_OS == 'macosx' then
	newoption {
		trigger     = 'ios',
		description = 'Target iOS'
	}
end

newoption {
	trigger     = 'demos',
	description = 'Generate Demo Apps'
}

newoption {
	trigger     = 'qtdir',
	description = 'Path to Qt installation. Example: "C:/Qt/5.0.0/msvc2015/"',
	default     = os.getenv( 'QTDIR' ) or os.getenv( 'QT_DIR' )
}
