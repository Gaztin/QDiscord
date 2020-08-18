require 'premake/app'
require 'premake/customizations'
require 'premake/defaults'
require 'premake/library'
require 'premake/options'
require 'premake/settings'
require 'premake/target'
require 'premake/utils'

workspace( settings.workspace_name )
platforms( utils.get_platforms() )
configurations { 'Debug', 'Release' }

library 'QDiscord'

if( _ARGS[ 'demos' ] ) then
	app 'DemoBot01'
	app 'DemoBotUser'
	app 'DemoEmbeds'
end

-- Set last app as startup
workspace( settings.workspace_name )
