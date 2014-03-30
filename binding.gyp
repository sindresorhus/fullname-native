{
	"targets": [{
		"target_name": "binding",
		"sources": [
			"binding.cc"
		],
		"include_dirs": [
			"<!(node -e \"require('nan')\")"
		],
		"conditions": [
			["OS == 'win'", {
				"msvs_settings": {
			        "VCLinkerTool": {
			          "AdditionalDependencies": [
			            "secur32.lib",
			          ]
			        }
			      }
			}]
		]
	}]
}
