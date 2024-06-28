#include "helpers.h"

#include "base64.h"
#include "QrToPng.h"
#include "certusPDF.h"

#include "InputByteArrayStream.h"

#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include <cctype>

#include <ft2build.h>

#include FT_TRUETYPE_TABLES_H 


void printLine(const std::string& text, std::ostream& outStream)
{
    outStream << std::endl << text << std::endl;
}

bool stringIsAscii7(const std::string& s)
{
    for (auto c : s)
        if (static_cast<unsigned char>(c) > 127)
            return false;

    return true;
}


std::size_t utf8StringLength(const std::string& utf8String)
{
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>{}.from_bytes(utf8String).size();
}


std::string stringsSet(const std::vector<std::string>& texts)
{
    std::unordered_set<wchar_t> charSet;

    for (auto& text : texts)
        for (auto c : std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>{}.from_bytes(text))
            charSet.insert(c);

    std::string stringSet;

    for (auto c : charSet)
        stringSet.push_back(c);

    return stringSet;
}


bool stringIsNumber(const std::string& text)
{
    return not text.empty() && std::find_if(text.begin(), text.end(), [](unsigned char c) { return not std::isdigit(c); }) == text.end();
}


std::string& stringTrimEdges(std::string& text)
{
	text.erase( text.begin(), std::find_if( text.begin(), text.end(), [](unsigned char ch) { return not std::isspace(ch); } ) );

	text.erase( std::find_if( text.rbegin(), text.rend(), [](unsigned char ch) { return not std::isspace(ch); } ).base(), text.end() );

	return text;
}


std::string& reduceConsecutiveWhitesToOne(std::string& text)
{
    text.erase(std::unique(text.begin(), text.end(), [](char lhs, char rhs) { return lhs == rhs and std::isspace(lhs); }), text.end());

    return text;
}


std::size_t stringFindNthOccuranceIndex(const std::string& text, const unsigned char character, const std::size_t occurance)
{
    if (occurance)
        for (std::size_t index = 0, occurances = 0; index < text.size(); ++index)
            if (text[index] == character and (++occurances == occurance))
                return index;

    return std::string::npos;
}


std::vector<std::size_t> findCharLocations(const std::string& text, const unsigned char findIt)
{
    std::vector<std::size_t> characterLocations;

    for(std::size_t index = 0; index < text.size(); ++index)
        if(text[index] == findIt)
            characterLocations.push_back(index);

    return characterLocations;
}


std::vector<std::string> stringSplit(const std::string& text, const char strDelimiter, const bool trimEdges)
{
    std::vector<std::string> tokens;
    std::istringstream iss(text);
    std::string token;

    while (std::getline(iss, token, strDelimiter))
        tokens.push_back( trimEdges ? stringTrimEdges(token) : token);

    return tokens;
}


std::string stringExtractHyperlink(std::string& text)
{
    const std::size_t sPosition = ('S' == text.at(1)) ? 1 : (('S' == text.at(2)) ? 2 : 0);

    if (sPosition not_eq 0 and text.at(sPosition + 1) == '\"')
    {
        const std::size_t rightQuotesPosition = text.find('\"', sPosition + 2);

        if (rightQuotesPosition not_eq std::string::npos)
        {
            auto hyperlink = text.substr(sPosition + 2, rightQuotesPosition - sPosition - 2);

            text = text.substr(0, sPosition) + text.substr(rightQuotesPosition + 1, text.size());

            return hyperlink;
        }
    }

    return {};
}


double sGetUnderlineThicknessFactor(PDFUsedFont* font)
{
    const auto inFTWrapper = font->GetFreeTypeFont();

    void* tableInfo = FT_Get_Sfnt_Table(*inFTWrapper, ft_sfnt_post);

    if(tableInfo)
        return ((TT_Postscript*) tableInfo)->underlineThickness * 1.0 / (*inFTWrapper)->units_per_EM;

    else
        return 0.05;
}


double sGetUnderlinePositionFactor(PDFUsedFont* font)
{
    const auto inFTWrapper = font->GetFreeTypeFont();

    void* tableInfo = FT_Get_Sfnt_Table(*inFTWrapper, ft_sfnt_post);

    if (tableInfo)
        return ((TT_Postscript*) tableInfo)->underlinePosition * 1.0 / (*inFTWrapper)->units_per_EM;

    else
        return -0.15;
}


PDFFormXObject* base64StringToImage
(
    PDFWriter& pdfWriter, 
    const std::string imageType, 
    const std::string base64Input
    )
{
    std::vector<unsigned char> decodedData = base64_decode(base64Input);

    auto byteImage = InputByteArrayStream(decodedData.data(), static_cast<long long>(decodedData.size()));

    if (imageType == "jpg" or imageType == "JPG")
        return pdfWriter.CreateFormXObjectFromJPGStream(&byteImage);

    else if (imageType == "png" or imageType == "PNG")
        return pdfWriter.CreateFormXObjectFromPNGStream(&byteImage);

    return nullptr;
}


PDFFormXObject* stringToQRCodePNGImage
(
    PDFWriter& pdfWriter, 
    const std::string& input, 
    const int imageSize
    )
{
    auto temp = QrToPng("", imageSize, 3, input, false, qrcodegen::QrCode::Ecc::MEDIUM);

    std::vector<unsigned char> outVector;
    outVector.resize(certusPDF::maxQRImageSize);
                            
    temp.writeToPNG(outVector);

    auto byteImage = InputByteArrayStream(outVector.data(), static_cast<long long>(outVector.size()));

    return pdfWriter.CreateFormXObjectFromPNGStream(&byteImage);
}


bool equalCaseInsesitive(const std::string& A, const std::string& B)
{
    return std::equal(A.begin(), A.end(), B.begin(), B.end(), 
        [](char a, char b){ return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b)); });
}


bool fileExists(const std::string& filePath)
{
    return access(filePath.data(), F_OK) not_eq -1;
}


std::string fileExtension(const std::string& filePath)
{
    return filePath.substr(filePath.find_last_of(".") + 1);
}


std::string fileToString(const std::string& filePath)
{
    if (not fileExists(filePath))
        return {};

    std::ifstream ifs(filePath);

    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    return content;
}


std::vector<std::string>& justifyStringsToMax(std::vector<std::string>& lines, std::size_t from, std::size_t to, const unsigned char fillCharacter)
{
    std::size_t index, charIndex;

    for (index = from; index < to; ++index)
        reduceConsecutiveWhitesToOne(stringTrimEdges(lines[index]));

    const auto maxSize = utf8StringLength( *( std::max_element(lines.begin() + from, lines.begin() + to, 
        [](const std::string& left, const std::string& right){ return utf8StringLength(left) < utf8StringLength(right); }) ) );
    
    for (index = from; index < to; ++index)
    {
        std::string& line = lines.at(index);

        const std::size_t fillChars = maxSize - utf8StringLength(line);

        if (fillChars == 0)
            continue;

        const auto charLocations = findCharLocations(line, fillCharacter);

        if (charLocations.size() == 0)
            continue;

        const auto charsPerLocation = std::div((int)fillChars, (int)charLocations.size());

        if (charsPerLocation.quot)
        {
            const std::string chars(charsPerLocation.quot, fillCharacter);

            for (charIndex = charLocations.size() - 1; charIndex >= 0; --charIndex)
                line.insert(charLocations[charIndex], chars);
        }

        const std::string oneChar(1, fillCharacter);

        for (charIndex = charLocations.size() - 1; charIndex >= charLocations.size() - charsPerLocation.rem; --charIndex)
            line.insert(charLocations[charIndex], oneChar);
    }

    return lines;
}


std::string& replaceVariables(std::string& line, const std::unordered_map<std::string, std::string>& variablesMap)
{
    static const unsigned char symbol = certusPDF::variableSymbol;

    line.push_back(' ');

    std::string value;

    std::size_t fieldIndex;

    for (std::size_t index = 0; index < line.size(); ++index)
    {
        if (line[index] == symbol)
        {
            for (fieldIndex = index + 1; fieldIndex < line.size() and std::isalpha(line[fieldIndex]); ++fieldIndex);

            const auto key = line.substr(index + 1, (fieldIndex - index) - 1);

            const auto node = variablesMap.find(key);

            value = node not_eq variablesMap.end() ? node->second : key;

            line.replace(index, fieldIndex - index, value);

            index += value.size() - 1;
        }
    }

    line.pop_back();

    return line;
}


void fillTemplate(std::string& templateArg, const Block* block)
{
    static const unsigned char symbol = certusPDF::variableSymbol;

    templateArg.push_back('\n');

    std::string value;

    std::size_t fieldIndex;

    bool keyExists;

    for (std::size_t index = 0; index < templateArg.size(); ++index)
    {
        if (templateArg[index] == symbol)
        {
            for (fieldIndex = index + 1; fieldIndex < templateArg.size() and std::isalpha(templateArg[fieldIndex]); ++fieldIndex);

            const auto key = templateArg.substr(index + 1, (fieldIndex - index) - 1);

            value = block->getValue(key, keyExists);

            if (not keyExists)
                value = std::string(1, symbol) + key;

            templateArg.replace(index, fieldIndex - index, value);

            index += value.size() - 1;
        }
    }
}