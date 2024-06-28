#pragma once

#include <unordered_map>
#include <string>
#include <regex>

class Block
{
private:
	std::unordered_map<std::string, std::string> _data = 
	{
		{"compname", "ΚΟΙΝΟΠΡΑΞΙΑ"},
		{"compaddress", "PIREAUS"},
		{"compzip", "176 74"},
		{"compcity", "ΑΘΗΝΑ"},
		{"compdoy", "ΠΛΟΙΩΝ ΠΕΙΡΑΙΑ"},
		{"compvatno", "997595200"},
		{"depportdescr", "RAFINA"},
		{"depdate", "05/04/2024"},
		{"deptime", "08:00"},
		{"depgate", "9"},
		{"destportdescr", "ΜΥKΟΝΟS"},
		{"arrdate", "04/04/2024"},
		{"arrtime", "12:40"},
		{"vesselname", "THUNDER"},
		{"ticketletter", "K"},
		{"ticketnumber", "31920"},
		{"bookingref", "10000THUNE"},
		{"bookdate", "16/02/2024"},
		{"booktime", "09:31"},
		{"agencycode", "1000"},
		{"usercode", "ZARKOS"},
		{"loyaltycard", "4321"},
		{"pastype", "AD"},
		{"firstname", "PANOS"},
		{"lastname", "KAZANTZIS"},
		{"birthdate", "08/08/1988"},
		{"nationality", "GR"},
		{"registrationno", "LA-0199"},
		{"classname", "OIK"},
		{"cabinno", "23"},
		{"discountcode", "ΑΚΕΡΑΙΟ/FULL PRICE"},
		{"gender", "M"},
		{"residentno", "123"},
		{"priority", "26"},
		{"protocol", "1611"},
		{"netfare", "46.35"},
		{"taxes", "2.32"},
		{"vat", "6.33"},
		{"totalprice", "55.00"},
		{"isafv", "000000"}
	};

public:

	static const unsigned char fieldSymbol = '^';

	Block() = default;

	~Block() = default;

	std::string getValue(const std::string& key, bool& exists) const
	{
		auto node = _data.find(key);

		if (node not_eq _data.end())
		{
			exists = true;

			return node->second;
		}

		exists = false;

		return {};
	}

	void setValue(const std::string& key, const std::string& value)
	{
		auto it = _data.find(key);

		if (it not_eq _data.end())
			it->second = value;
	}

	std::vector<std::pair<std::string, std::string>> getItems(void) const
	{
		std::vector<std::pair<std::string, std::string>> temp(_data.begin(), _data.end());

		return temp;
	}
};