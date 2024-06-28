#pragma once

#include <libxl/enum.h>

#include <string>
#include <unordered_map>

namespace libxlColors
{
	constexpr std::int32_t NO_COLOR = 127, DEFAULT = -1;

	const std::unordered_map<std::int32_t, std::string> colorMap = 
	{
		{ DEFAULT, "000000"},
		{ NO_COLOR, "FFFFFF" },
		{ libxl::COLOR_BLACK, "000000" },
		{ libxl::COLOR_WHITE, "FFFFFF" },
		{ libxl::COLOR_RED, "FF0000" },
		{ libxl::COLOR_BRIGHTGREEN, "00FF00" },
		{ libxl::COLOR_BLUE, "0000FF" },
		{ libxl::COLOR_YELLOW, "FFFF00" },
		{ libxl::COLOR_PINK, "FF00FF" },
		{ libxl::COLOR_TURQUOISE, "00FFFF" },
		{ libxl::COLOR_DARKRED, "800000" },
		{ libxl::COLOR_GREEN, "008000" },
		{ libxl::COLOR_DARKBLUE, "000080" },
		{ libxl::COLOR_DARKYELLOW, "808000" },
		{ libxl::COLOR_VIOLET, "800080" },
		{ libxl::COLOR_TEAL, "008080" },
		{ libxl::COLOR_GRAY25, "C0C0C0" },
		{ libxl::COLOR_GRAY50, "808080" },
		{ libxl::COLOR_PERIWINKLE_CF, "9999FF" },
		{ libxl::COLOR_PLUM_CF, "993366" },
		{ libxl::COLOR_IVORY_CF, "FFFFCC" },
		{ libxl::COLOR_LIGHTTURQUOISE_CF, "CCFFFF" },
		{ libxl::COLOR_DARKPURPLE_CF, "660066" },
		{ libxl::COLOR_CORAL_CF, "FF8080" },
		{ libxl::COLOR_OCEANBLUE_CF, "0066CC" },
		{ libxl::COLOR_ICEBLUE_CF, "CCCCFF" },
		{ libxl::COLOR_DARKBLUE_CL, "000080" },
		{ libxl::COLOR_PINK_CL, "FF00FF" },
		{ libxl::COLOR_YELLOW_CL, "FFFF00" },
		{ libxl::COLOR_TURQUOISE_CL, "00FFFF" },
		{ libxl::COLOR_VIOLET_CL, "800080" },
		{ libxl::COLOR_DARKRED_CL, "800000" },
		{ libxl::COLOR_TEAL_CL, "008080" },
		{ libxl::COLOR_BLUE_CL, "0000FF" },
		{ libxl::COLOR_SKYBLUE, "00CCFF" },
		{ libxl::COLOR_LIGHTTURQUOISE, "CCFFFF" },
		{ libxl::COLOR_LIGHTGREEN, "CCFFCC" },
		{ libxl::COLOR_LIGHTYELLOW, "FFFF99" },
		{ libxl::COLOR_PALEBLUE, "99CCFF" },
		{ libxl::COLOR_ROSE, "FF99CC" },
		{ libxl::COLOR_LAVENDER, "CC99FF" },
		{ libxl::COLOR_TAN, "FFCC99" },
		{ libxl::COLOR_LIGHTBLUE, "3366FF" },
		{ libxl::COLOR_AQUA, "33CCCC" },
		{ libxl::COLOR_LIME, "99CC00" },
		{ libxl::COLOR_GOLD, "FFCC00" },
		{ libxl::COLOR_LIGHTORANGE, "FF9900" },
		{ libxl::COLOR_ORANGE, "FF6600" },
		{ libxl::COLOR_BLUEGRAY, "666699" },
		{ libxl::COLOR_GRAY40, "969696" },
		{ libxl::COLOR_DARKTEAL, "003366" },
		{ libxl::COLOR_SEAGREEN, "339966" },
		{ libxl::COLOR_DARKGREEN, "003300" },
		{ libxl::COLOR_OLIVEGREEN, "333300" },
		{ libxl::COLOR_BROWN, "993300" },
		{ libxl::COLOR_PLUM, "993366" },
		{ libxl::COLOR_INDIGO, "333399" },
		{ libxl::COLOR_GRAY80, "333333" },
		{ libxl::COLOR_DEFAULT_FOREGROUND, "000000" },	
		{ libxl::COLOR_DEFAULT_BACKGROUND, "000000" }
	};
} 