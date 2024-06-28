#pragma once

#include <vector>
#include <iostream>

#include "PDFWriter.h"
#include "PDFUsedFont.h"
#include "PDFFormXObject.h"

#include "block.h"

void printLine(const std::string& text, std::ostream& outStream = std::cout);

bool stringIsAscii7(const std::string& text);

std::size_t utf8StringLength(const std::string& utf8String);

std::string stringsSet(const std::vector<std::string>& texts);

bool stringIsNumber(const std::string& text);

std::string& stringTrimEdges(std::string& text);

std::string& reduceConsecutiveWhitesToOne(std::string& text);

std::size_t stringFindNthOccuranceIndex(const std::string& text, const unsigned char character, const std::size_t occurance = 1);

std::vector<std::size_t> findCharLocations(const std::string& text, const unsigned char findIt);

std::vector<std::string> stringSplit(const std::string& text, const char strDelimiter = ' ', const bool trimEdges = false);

std::string stringExtractHyperlink(std::string& text);

double sGetUnderlineThicknessFactor(PDFUsedFont* font);

double sGetUnderlinePositionFactor(PDFUsedFont* font);

PDFFormXObject* base64StringToImage(PDFWriter& pdfWriter, const std::string imageType, const std::string base64Input);

PDFFormXObject* stringToQRCodePNGImage (PDFWriter& pdfWriter, const std::string& input, const int imageSize);

bool equalCaseInsesitive(const std::string& A, const std::string& B);

bool fileExists(const std::string& filePath);

std::string fileExtension(const std::string& filePath);

std::string fileToString(const std::string& filePath);

std::vector<std::string>& justifyStringsToMax(std::vector<std::string>& lines, std::size_t from, std::size_t to, const unsigned char fillCharacter = ' ');

std::string& replaceVariables(std::string& line, const std::unordered_map<std::string, std::string>& variablesMap);

void fillTemplate(std::string& templateArg, const Block* block);