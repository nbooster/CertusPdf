#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

#include "helpers.h"
#include "pdfBuffer.h"

namespace certusPDF
{
	constexpr unsigned char delimiter = ',';
	constexpr unsigned char noneSymbol = '-';
	constexpr unsigned char biggestSymbol = '@'; // '@' generally is the biggest char in most fonts (or 'W')
	constexpr unsigned char variableSymbol = '^';
	constexpr unsigned char justifiedMonospaceFillSymbol = ' ';

	constexpr std::size_t maxQRImageSize = 100'000;
	constexpr std::size_t textDelimiterStartPosition = 6;
	constexpr std::size_t pointsDelimiterStartPosition = 4;

	constexpr std::size_t dimX = 595; //842;
	constexpr std::size_t dimY = 842; //1191;

	class CertusPDF final
	{
		private:

			std::unordered_map<std::string, std::pair<std::string, std::string>> templates;

		public:

			bool addTemplatePair
			(
				const std::string& name, 
				const std::string& pdfPath, 
				const std::string& textPath
			);
			
			std::pair<std::string, std::string> getTemplatePair(const std::string& name) const;
	};

	std::pair<bool, std::string> createPDFFromPDFs
	(
		const std::vector<std::pair<std::string, std::string>>& input,
	    const std::string& fontFilePath,
	    const std::string& boldFontFilePath,
	    const std::string& barcodeFontFilePath,
	    const std::string& monospaceFontFilePath,
	    const std::string& pdfFilePath = "",
	    const bool toBase64 = true,
	    const bool withVars = false,
	    const unsigned int inputThreads = 1
	);

	std::pair<bool, std::string> createPDF
	(
	    const std::vector<std::string>& inputPages,
	    const std::string& pdfFilePath,
	    const std::string& fontFilePath,
	    const std::string& boldFontFilePath,
	    const std::string& barcodeFontFilePath,
	    const std::string& monospaceFontFilePath,
	    const unsigned int inputThreads = 1
    );

    std::pair<bool, std::string> createPDFFromXLSX
    (
    	const std::string& xlsxFilePath,
	    const std::string& fontFilePath,
	    const std::string& boldFontFilePath,
	    const std::size_t fontSize = 8,
	    const std::string& textColor = "000000",
	    const bool bold = false,
	    const bool writeToFile = true
    );
}