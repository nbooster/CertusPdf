#include <algorithm>
#include <iomanip>
#include <numeric>
#include <locale>
#include <future>
#include <cmath>

#include "PDFPage.h"
#include "PDFArray.h"
#include "PDFWriter.h"
#include "PDFParser.h"
#include "PDFPageInput.h"
#include "PDFObjectCast.h"
#include "PDFFormXObject.h"
#include "PageContentContext.h"
#include "InputByteArrayStream.h"
#include "XObjectContentContext.h"
#include "PDFDocumentCopyingContext.h"
#include "PDFIndirectObjectReference.h"
        
#include "AnnotationsWriter.h"
#include "base64.h"

#include "certusPDF.h"

#include <libxl/libxl.h>

#include "colorMatching.hpp"

static std::unordered_map<std::string, std::string> variablesMap;

const std::string noOpacityString = std::to_string(NO_OPACITY_VALUE);

constexpr auto WHITE = "FFFFFF";
constexpr auto BLACK = "000000";
constexpr auto WHITE_LONG = 16777215;

static void drawLine
(
    PDFWriter& pdfWriter, 
    PDFPage* pdfPage, 
    const std::string& fromX = "0", 
    const std::string& fromY = "0", 
    const std::string& toX = "1", 
    const std::string& toY = "1", 
    const std::string& width = "1",
    const std::string& hexRGBColorValue = BLACK,
    const std::string& opacity = noOpacityString,
    PageContentContext* PCC = nullptr
    )
{
    PageContentContext* pageContentContext;

    if (PCC)
        pageContentContext = PCC;
        
    else
        pageContentContext = pdfWriter.StartPageContentContext(pdfPage);

    pageContentContext->q();

    pageContentContext->SetupColor(
        { PageContentContext::eStroke, PageContentContext::eRGB, std::stoul(hexRGBColorValue, nullptr, 16), 1.0, false, std::stod(opacity) });

    pageContentContext->w(std::stod(width));

    pageContentContext->m(std::stod(fromX), std::stod(fromY));

    pageContentContext->l(std::stod(toX), std::stod(toY));

    pageContentContext->s();
    
    pageContentContext->Q();

    if (PCC == nullptr)
        pdfWriter.EndPageContentContext(pageContentContext);
}

static void writeText
(
    PDFWriter& pdfWriter, 
    PDFPage* pdfPage, 
    PDFUsedFont* font,
    const std::string& textLine = "", 
    const std::string& startX = "0", 
    const std::string& startY = "0", 
    const std::string& fontSize = "10", 
    const std::string& textHexRGBColorValue = BLACK, 
    const std::string& textOpacity = noOpacityString,
    const std::string& highlightHexRGBColorValue = WHITE, 
    const std::string& highlightOpacity = noOpacityString,
    const std::string& endX = "",
    const bool underlined = false,
    const std::string& hyperlink = "",
    const bool rightAligned = false,
    const bool centerAligned = false,
    const PDFUsedFont::TextMeasures* textDimensionsPtr = nullptr,
    PageContentContext* PCC = nullptr
    )
{
    std::string line { textLine };

    stringTrimEdges(line);

    if ( not line.size())
        return;

    PageContentContext* pageContentContext;

    if (PCC)
        pageContentContext = PCC;
        
    else
        pageContentContext = pdfWriter.StartPageContentContext(pdfPage);

    PDFUsedFont::TextMeasures textDimensions;

    auto doubleStartX = rightAligned ? 0.0 : std::stod(startX);

    const auto doubleStartY = std::stod(startY);
    const auto intFontSize = std::stoi(fontSize);

    bool dimensionsCalculated = false;

    if (textDimensionsPtr != nullptr)
    {
        dimensionsCalculated = true;

        textDimensions = *textDimensionsPtr;
    }

    const bool highlight = highlightHexRGBColorValue not_eq WHITE ? true : false;

    if (endX == "")
    {
        if (highlight)
        {   

            if ( not dimensionsCalculated)
            {
                textDimensions = font->CalculateTextDimensions(line, intFontSize);
                dimensionsCalculated = true;
            }

            pageContentContext->DrawRectangle(doubleStartX + textDimensions.xMin, doubleStartY + textDimensions.yMin, textDimensions.width, textDimensions.height, 
                { PageContentContext::eFill, PageContentContext::eRGB, std::stoul(highlightHexRGBColorValue, nullptr, 16), 1.0, false, std::stod(highlightOpacity) });
        }

        pageContentContext->WriteText(doubleStartX, doubleStartY, line, 
            { font, static_cast<double>(intFontSize), PageContentContext::eRGB, std::stoul(textHexRGBColorValue, nullptr, 16), std::stod(textOpacity) });

        if (underlined)
        {
            if ( not dimensionsCalculated)
            {
                textDimensions = font->CalculateTextDimensions(line, intFontSize);
                dimensionsCalculated = true;
            }

            const auto lineY = std::to_string(doubleStartY + sGetUnderlinePositionFactor(font) * intFontSize);

            drawLine(pdfWriter, pdfPage, std::to_string(doubleStartX + textDimensions.xMin), lineY, 
                std::to_string(doubleStartX + textDimensions.xMin + textDimensions.width), lineY, 
                std::to_string(sGetUnderlineThicknessFactor(font) * intFontSize), textHexRGBColorValue, textOpacity, pageContentContext);
        }
    }

    else
    {
        const auto doubleEndX = std::stod(endX);

        if (rightAligned or centerAligned)
        {
            if ( not dimensionsCalculated)
            {
                textDimensions = font->CalculateTextDimensions(line, intFontSize);
                dimensionsCalculated = true;
            }

            if (rightAligned)
                doubleStartX = doubleEndX - textDimensions.width;

            else if (centerAligned)
                doubleStartX += (doubleEndX - doubleStartX - textDimensions.width) / 2.0;
            
            if (highlight) 
                pageContentContext->DrawRectangle(doubleStartX + textDimensions.xMin, doubleStartY + textDimensions.yMin, (doubleEndX - doubleStartX - textDimensions.xMin), textDimensions.height, 
                    { PageContentContext::eFill, PageContentContext::eRGB, std::stoul(highlightHexRGBColorValue, nullptr, 16), 1.0, false, std::stod(highlightOpacity) });

            pageContentContext->WriteText(doubleStartX /*+ textDimensions.xMin*/, doubleStartY /*+ textDimensions.yMin*/, line, 
                { font, static_cast<double>(intFontSize), PageContentContext::eRGB, std::stoul(textHexRGBColorValue, nullptr, 16), std::stod(textOpacity) });

            if (underlined)
            {
                const auto lineY = std::to_string(doubleStartY + sGetUnderlinePositionFactor(font) * intFontSize);

                drawLine(pdfWriter, pdfPage, std::to_string(doubleStartX + textDimensions.xMin), lineY, endX, lineY, 
                    std::to_string(sGetUnderlineThicknessFactor(font) * intFontSize), textHexRGBColorValue, textOpacity, pageContentContext);
            }
        }

        else if (doubleEndX > doubleStartX)
        {
            reduceConsecutiveWhitesToOne(line);

            if ( not dimensionsCalculated)
            {
                textDimensions = font->CalculateTextDimensions(line, intFontSize);
                dimensionsCalculated = true;
            }

            if (highlight) 
                pageContentContext->DrawRectangle(doubleStartX + textDimensions.xMin, doubleStartY + textDimensions.yMin, (doubleEndX - doubleStartX - textDimensions.xMin), textDimensions.height, 
                    { PageContentContext::eFill, PageContentContext::eRGB, std::stoul(highlightHexRGBColorValue, nullptr, 16), 1.0, false, std::stod(highlightOpacity) });

            if (underlined)
            {
                const auto lineY = std::to_string(doubleStartY + sGetUnderlinePositionFactor(font) * intFontSize);

                drawLine(pdfWriter, pdfPage, std::to_string(doubleStartX + textDimensions.xMin), lineY, endX, lineY, 
                    std::to_string(sGetUnderlineThicknessFactor(font) * intFontSize), textHexRGBColorValue, textOpacity, pageContentContext);
            }

            const auto words = stringSplit(line);

            std::vector<double> wordsWidth;

            std::transform(words.begin(), words.end(), std::back_inserter(wordsWidth), 
                [&font, intFontSize](const std::string& word){ return (font->CalculateTextDimensions(word, intFontSize)).width; });

            const auto wordsWidthSum = std::accumulate(wordsWidth.begin(), wordsWidth.end(), decltype(wordsWidth)::value_type(0));

            const auto spaceBetweenWords = ((doubleEndX - doubleStartX - textDimensions.xMin) - static_cast<double>(wordsWidthSum)) / static_cast<double>(words.size() - 1);

            const AbstractContentContext::TextOptions textOptions = { font, static_cast<double>(intFontSize), PageContentContext::eRGB, std::stoul(textHexRGBColorValue, nullptr, 16), std::stod(textOpacity) };

            if (spaceBetweenWords >= 0)
            {
                auto xPosition = doubleStartX;

                for(std::size_t index = 0; index < words.size(); ++index)
                {
                    pageContentContext->WriteText(xPosition, doubleStartY, words[index], textOptions);

                    xPosition += spaceBetweenWords + static_cast<double>(wordsWidth[index]);
                }
            }
        }
    }

    if (PCC == nullptr)
        pdfWriter.EndPageContentContext(pageContentContext);

    if (not hyperlink.empty() and stringIsAscii7(hyperlink))
    {
        if (not dimensionsCalculated)
        {
            textDimensions = font->CalculateTextDimensions(line, intFontSize);
            dimensionsCalculated = true;
        }

        std::string URL = hyperlink;

        stringTrimEdges(URL);
        
        pdfWriter.AttachURLLinktoCurrentPage( (URL.find("http") == std::string::npos) ? "http://" + URL : URL , 
            {doubleStartX + textDimensions.xMin, doubleStartY + textDimensions.yMin, 
            doubleStartX + textDimensions.xMin + textDimensions.width, doubleStartY + textDimensions.yMin + textDimensions.height});
    }
}

static void writePlainTexts
(
    PDFWriter& pdfWriter, 
    PDFPage* pdfPage,
    PDFUsedFont* font,
    std::vector<std::string>& textLines,
    const std::size_t lineStart = 0,
    const std::size_t lineEnd = 1,
    const std::string& fontSize = "10", 
    const std::string& textHexRGBColorValue = BLACK, 
    const std::string& textOpacity = noOpacityString,
    PageContentContext* PCC = nullptr
    )
{
    if ((not textLines.size()) or lineStart >= lineEnd or lineEnd > textLines.size())
        return;

    std::vector<std::string> fields;

    PageContentContext* pageContentContext;

    if (PCC)
        pageContentContext = PCC;
        
    else
        pageContentContext = pdfWriter.StartPageContentContext(pdfPage);

    pageContentContext->SetupColor(PageContentContext::eFill, std::stoul(textHexRGBColorValue, nullptr, 16), PageContentContext::eRGB, std::stod(textOpacity));

    pageContentContext->Tf(font, std::stod(fontSize));

    for (std::size_t index { lineStart }; index not_eq lineEnd; ++index)
    {
        const auto& textLine = textLines[index];

        const auto textStart = stringFindNthOccuranceIndex(textLine, certusPDF::delimiter, 2);

        auto text = textLine.substr(textStart + 1);

        fields = stringSplit(textLine.substr(0, textStart), certusPDF::delimiter);

        if (fields.size() not_eq 2)
            continue;

        pageContentContext->BT();

        pageContentContext->Td(std::stod(fields[0]), std::stod(fields[1]));

        pageContentContext->Tj(stringTrimEdges(text));
        
        pageContentContext->ET();
    }

    if (PCC == nullptr)
        pdfWriter.EndPageContentContext(pageContentContext);
}

static void writeParagraph
(
    PDFWriter& pdfWriter, 
    PDFPage* pdfPage,
    PDFUsedFont* font,
    std::vector<std::string>& lines,
    const std::size_t lineStart = 0,
    const std::size_t lineEnd = 1,
    const std::string& startX = "0", 
    const std::string& startY = "0", 
    const std::string& fontSize = "10", 
    const std::string& textHexRGBColorValue = BLACK, 
    const std::string& textOpacity = noOpacityString,
    const std::string& highlightHexRGBColorValue = WHITE, 
    const std::string& highlightOpacity = noOpacityString,
    const std::string& endX = "",
    const bool underlined = false,
    const bool rightAligned = false,
    const std::string& ySpacing = "1",
    PDFUsedFont* monospaceFont = nullptr,
    const bool excludeLastLine = false,
    PageContentContext* PCC = nullptr
    )
{
    static const auto noneSymbol = std::to_string(certusPDF::noneSymbol);
    static const auto biggestSymbol = std::to_string(certusPDF::biggestSymbol);

    if ((not lines.size()) or lineStart >= lineEnd or lineEnd >= lines.size())
        return;

    const std::size_t space = std::stoul(ySpacing) + 
        ( monospaceFont not_eq nullptr ? monospaceFont : font)->CalculateTextDimensions(stringsSet(lines)/*biggestSymbol*/, std::stoi(fontSize)).height; 

    auto currentY = stol(startY);

    if (monospaceFont not_eq nullptr)
    {
        justifyStringsToMax(lines, lineStart, lineEnd - (int)excludeLastLine, certusPDF::justifiedMonospaceFillSymbol);

        for (std::size_t index { lineStart }; index not_eq lineEnd; ++index)
        {   
            if (currentY < 0)
                return;

            writeText(pdfWriter, pdfPage, monospaceFont, lines[index], (startX == noneSymbol ? "0" : startX), std::to_string(currentY), fontSize, 
                textHexRGBColorValue, textOpacity, highlightHexRGBColorValue, highlightOpacity, "", underlined, "", rightAligned, false, nullptr, PCC);

            currentY -= space;
        }
    }

    else
    {
        for (std::size_t index { lineStart }; index not_eq lineEnd - (int)excludeLastLine; ++index)
        {
            if (currentY < 0)
                return;

            writeText(pdfWriter, pdfPage, font, lines[index], (startX == noneSymbol ? "0" : startX), std::to_string(currentY), fontSize, textHexRGBColorValue, textOpacity,
                highlightHexRGBColorValue, highlightOpacity, (endX == noneSymbol ? "" : endX), underlined, "", rightAligned, false, nullptr, PCC);

            currentY -= space;
        }

        if (excludeLastLine)
            writeText(pdfWriter, pdfPage, font, lines[lineEnd - 1], (startX == noneSymbol ? "0" : startX), std::to_string(currentY), fontSize, 
                textHexRGBColorValue, textOpacity, highlightHexRGBColorValue, highlightOpacity, "", underlined, "", rightAligned, false, nullptr, PCC);
    }
}

static void drawRectangle
(
    PDFWriter& pdfWriter, 
    PDFPage* pdfPage,
    const std::string& inLeft,
    const std::string& inBottom,
    const std::string& inWidth,
    const std::string& inHeight,
    const std::string& hexRGBColorValue = BLACK,
    const std::string& opacity = noOpacityString,
    const std::string& fill = "Y",
    PageContentContext* PCC = nullptr
    )
{
    PageContentContext* pageContentContext;

    if (PCC)
        pageContentContext = PCC;
        
    else
        pageContentContext = pdfWriter.StartPageContentContext(pdfPage);

    pageContentContext->DrawRectangle(std::stod(inLeft), std::stod(inBottom), std::stod(inWidth), std::stod(inHeight), 
        { (fill == "N" ? PageContentContext::eStroke : PageContentContext::eFill), PageContentContext::eRGB, std::stoul(hexRGBColorValue, nullptr, 16), 1.0, false, std::stod(opacity) });

    if (PCC == nullptr)
        pdfWriter.EndPageContentContext(pageContentContext);
}

static void drawCircle
(
    PDFWriter& pdfWriter, 
    PDFPage* pdfPage,
    const std::string& inCenterX,
    const std::string& inCenterY,
    const std::string& inRadius,
    const std::string& hexRGBColorValue = BLACK,
    const std::string& opacity = noOpacityString,
    const std::string& fill = "N",
    PageContentContext* PCC = nullptr
    )
{
    PageContentContext* pageContentContext;

    if (PCC)
        pageContentContext = PCC;
        
    else
        pageContentContext = pdfWriter.StartPageContentContext(pdfPage);

    pageContentContext->DrawCircle(std::stod(inCenterX), std::stod(inCenterY), std::stod(inRadius), 
        { (fill == "N" ? PageContentContext::eStroke : PageContentContext::eFill), PageContentContext::eRGB, std::stoul(hexRGBColorValue, nullptr, 16), 1.0, false, std::stod(opacity) });

    if (PCC == nullptr)
        pdfWriter.EndPageContentContext(pageContentContext);
}

static void drawPolygon
(
    PDFWriter& pdfWriter, 
    PDFPage* pdfPage,
    const std::string& points,
    const std::string& hexRGBColorValue = BLACK,
    const std::string& opacity = noOpacityString,
    const std::string& fill = "N",
    PageContentContext* PCC = nullptr
    )
{
    auto strPoints = stringSplit(points, certusPDF::delimiter);

    if (strPoints.size() % 2)
        return;

    DoubleAndDoublePairList doublePoints;

    for (std::size_t index = 0; index < strPoints.size(); index += 2)
        doublePoints.emplace_back(std::stod(strPoints[index]), std::stod(strPoints[index + 1]));

    PageContentContext* pageContentContext;

    if (PCC)
        pageContentContext = PCC;
        
    else
        pageContentContext = pdfWriter.StartPageContentContext(pdfPage);

    pageContentContext->DrawPath(doublePoints,
        { (fill == "N" ? PageContentContext::eStroke : PageContentContext::eFill), PageContentContext::eRGB, std::stoul(hexRGBColorValue, nullptr, 16), 1.0, false, std::stod(opacity) });

    if (PCC == nullptr)
        pdfWriter.EndPageContentContext(pageContentContext);
}

static void drawImage
(
    PDFWriter& pdfWriter, 
    PDFPage* pdfPage, 
    PDFFormXObject* image, 
    const std::string& startX = "0", 
    const std::string& startY = "0",
    const std::string& scaleX = "1.0", 
    const std::string& scaleY = "1.0",
    const std::string& opacity = noOpacityString,
    PageContentContext* PCC = nullptr
    )
{
    PageContentContext* pageContentContext;

    if (PCC)
        pageContentContext = PCC;
        
    else
        pageContentContext = pdfWriter.StartPageContentContext(pdfPage);

    pageContentContext->q();

    pageContentContext->SetOpacity(std::stod(opacity));

    pageContentContext->cm(std::stod(scaleX), 0, 0, std::stod(scaleY), std::stoi(startX), std::stoi(startY));

    pageContentContext->Do(pdfPage->GetResourcesDictionary().AddFormXObjectMapping(image->GetObjectID()));

    pageContentContext->SetOpacity(NO_OPACITY_VALUE);

    pageContentContext->Q();

    if (PCC == nullptr)
        pdfWriter.EndPageContentContext(pageContentContext);
}

static EStatusCode appendPageWithAnnotationsToPDFStream
(
    PDFWriter& inTargetWriter, 
    IByteReaderWithPosition* onePagePdfStreamBuffer
    )
{
    EStatusCode status = eSuccess;

    AnnotationsWriter annotationsWriter;
    
    inTargetWriter.GetDocumentContext().AddDocumentContextExtender(&annotationsWriter);

    auto copyingContext = inTargetWriter.CreatePDFCopyingContext(onePagePdfStreamBuffer);

    if ( not copyingContext)
        return eFailure;

    std::size_t pagesCount = copyingContext->GetSourceDocumentParser()->GetPagesCount();

    for(std::size_t index = 0; index < pagesCount and eSuccess == status; ++index)
    {
        RefCountPtr<PDFDictionary> pageDictionary(copyingContext->GetSourceDocumentParser()->ParsePage(index));

        PDFObjectCastPtr<PDFArray> annotations(copyingContext->GetSourceDocumentParser()->QueryDictionaryObject(pageDictionary.GetPtr(), "Annots"));

        if(annotations.GetPtr())
        {
            SingleValueContainerIterator<PDFObjectVector> annotationDictionaryObjects = annotations->GetIterator();

            PDFObjectCastPtr<PDFIndirectObjectReference> annotationReference;

            while(annotationDictionaryObjects.MoveNext() and eSuccess == status)
            {
                annotationReference = annotationDictionaryObjects.GetItem();

                EStatusCodeAndObjectIDType result = copyingContext->CopyObject(annotationReference->mObjectID);

                status = result.first;

                if(eSuccess == status)
                    annotationsWriter.AddCopiedAnnotation(result.second);
            }

            if(status not_eq eSuccess)
            {
                delete copyingContext;

                return status;
            }
        }

        status = copyingContext->AppendPDFPageFromPDF(index).first;
    }

    delete copyingContext;

    inTargetWriter.GetDocumentContext().RemoveDocumentContextExtender(&annotationsWriter);

    return eSuccess;
}

bool certusPDF::CertusPDF::addTemplatePair
(
    const std::string& name, 
    const std::string& pdfPath, 
    const std::string& textPath
    )
{
    if (fileExists(pdfPath) and fileExtension(pdfPath) == "pdf" and fileExists(textPath) and fileExtension(textPath) == "txt")
    {
        this->templates[name] = {pdfPath, textPath};

        return true;
    }

    return false;
}

std::pair<std::string, std::string> certusPDF::CertusPDF::getTemplatePair(const std::string& name)  const
{
    const auto it = this->templates.find(name);

    if (it not_eq this->templates.end())
        return it->second;

    return {};
}

static void writePage
(
    PDFWriter& pdfWriter, 
    PDFUsedFont* font,
    PDFUsedFont* boldFont,
    PDFUsedFont* barcodeFont,
    PDFUsedFont* monospaceFont,
    const std::string& inputPage,
    PDFPage* pdfPage = nullptr,
    const int dimX = certusPDF::dimX,
    const int dimY = certusPDF::dimY,
    const bool withVars = false
    )
{
    bool writePDF = false;

    if (pdfPage == nullptr)
    {
        pdfPage = new PDFPage();

        pdfPage->SetMediaBox(PDFRectangle(0, 0, dimX, dimY));

        writePDF = true;
    }

    PageContentContext* pageContentContext = pdfWriter.StartPageContentContext(pdfPage);
    
    std::vector<std::string> fields, textParts;

    std::size_t delimiterPos;

    std::string hyperlink = "";

    PDFUsedFont* usedFont = font;

    auto lines = stringSplit(inputPage, '\n');

    for (std::size_t index = 0; index < lines.size(); ++index)
    {
        std::string& line = lines[index];

        stringTrimEdges(line);

        if (line.size() <= 4)
            continue;

        if (withVars)
            replaceVariables(line, variablesMap);

        if (line[0] == 'B')
        {
            usedFont = boldFont;
            line.erase(0, 1);
        }
        else if (line[0] == 'C')
        {
            usedFont = barcodeFont;
            line.erase(0, 1);
        }

        hyperlink = stringExtractHyperlink(line);

        switch (line[0])
        {
            case 'V':

                if (not withVars)
                    break;

                fields = stringSplit(line, certusPDF::delimiter);

                if (fields.size() == 3)
                {
                    std::string& name = fields[1];

                    name.erase(std::remove_if(name.begin(), name.end(), isspace), name.end());

                    variablesMap[name] = fields[2];
                }

                break;

            case 'L':

                fields = stringSplit(line, certusPDF::delimiter);
                
                if (fields.size() == 8)
                    drawLine(pdfWriter, pdfPage, fields[1], fields[2], fields[3], fields[4], fields[5], fields[6], fields[7], pageContentContext);

                break;

            case 'R':

                fields = stringSplit(line, certusPDF::delimiter);

                if (fields.size() == 8)
                    drawRectangle(pdfWriter, pdfPage, fields[1], fields[2], fields[3], fields[4], fields[5], fields[6], fields[7], pageContentContext);

                break;

            case 'C':

                fields = stringSplit(line, certusPDF::delimiter);

                if (fields.size() == 7)
                    drawCircle(pdfWriter, pdfPage, fields[1], fields[2], fields[3], fields[4], fields[5], fields[6], pageContentContext);

                break;

            case 'Z':

                delimiterPos = stringFindNthOccuranceIndex(line, certusPDF::delimiter, certusPDF::pointsDelimiterStartPosition);
                
                if (delimiterPos not_eq std::string::npos)
                {
                    fields = stringSplit(line.substr(0, delimiterPos), certusPDF::delimiter);
                    
                    if (fields.size() == 4)
                        drawPolygon(pdfWriter, pdfPage, line.substr(delimiterPos + 1), fields[1], fields[2], fields[3], pageContentContext);
                }
               
                break;

            case 'I':

                fields = stringSplit(line, certusPDF::delimiter);
                
                if (fields.size() == 8)
                {
                    const auto imageType = stringTrimEdges(fields[6]);
                    const auto data = stringTrimEdges(fields[7]);

                    if (line[1] == 'F')
                    {                        
                        if (not (fileExists(data) and equalCaseInsesitive(imageType, fileExtension(data))))
                            break;

                        PDFFormXObject* image = nullptr;

                        if (imageType == "jpg" or imageType == "JPG")
                            image = pdfWriter.CreateFormXObjectFromJPGFile(data);

                        else if (imageType == "png" or imageType == "PNG")
                            image = pdfWriter.CreateFormXObjectFromPNGFile(data);

                        else
                            break;

                        drawImage(pdfWriter, pdfPage, image, fields[1], fields[2], fields[3], fields[4], fields[5], pageContentContext);

                        delete image;
                    }

                    else
                    {
                        PDFFormXObject* image = base64StringToImage(pdfWriter, imageType, data);

                        drawImage(pdfWriter, pdfPage, image, fields[1], fields[2], fields[3], fields[4], fields[5], pageContentContext);
                        
                        delete image;
                    }
                }
                    
                break;

            case 'Q':

                fields = stringSplit(line, certusPDF::delimiter);
                
                if (fields.size() == 6)
                {
                    auto& text = fields[5];

                    stringTrimEdges(text);
                    
                    PDFFormXObject* image = stringToQRCodePNGImage(pdfWriter, text, std::stoi(fields[3]));
                    
                    drawImage(pdfWriter, pdfPage, image, fields[1], fields[2], "1.0", "1.0", fields[4], pageContentContext);

                    delete image; 
                }

                break;
            
            case 'T':
                
                delimiterPos = stringFindNthOccuranceIndex(line, certusPDF::delimiter, certusPDF::textDelimiterStartPosition);
                
                if (delimiterPos not_eq std::string::npos)
                {
                    fields = stringSplit(line.substr(0, delimiterPos), certusPDF::delimiter);
                    
                    if (fields.size() == 6)
                        writeText(pdfWriter, pdfPage, usedFont, line.substr(delimiterPos + 1), 
                            fields[1], fields[2], fields[3], fields[4], fields[5], WHITE, noOpacityString, "", line[1] == 'U', hyperlink, 
                            false, false, nullptr, pageContentContext);
                }
               
                break;

            case 'H':

                delimiterPos = stringFindNthOccuranceIndex(line, certusPDF::delimiter, certusPDF::textDelimiterStartPosition + 2);
                
                if (delimiterPos not_eq std::string::npos)
                {
                    fields = stringSplit(line.substr(0, delimiterPos), certusPDF::delimiter);
                    
                    if (fields.size() == 8)
                        writeText(pdfWriter, pdfPage, usedFont, line.substr(delimiterPos + 1), 
                            fields[1], fields[2], fields[3], fields[4], fields[5], fields[6], fields[7], "", line[1] == 'U', hyperlink, 
                            false, false, nullptr, pageContentContext);
                }
               
                break;

            case 'A':
 
                delimiterPos = stringFindNthOccuranceIndex(line, certusPDF::delimiter, certusPDF::textDelimiterStartPosition + 1);
                
                if (delimiterPos not_eq std::string::npos)
                {
                    fields = stringSplit(line.substr(0, delimiterPos), certusPDF::delimiter);
                    
                    if (fields.size() == 7)
                        writeText(pdfWriter, pdfPage, usedFont, line.substr(delimiterPos + 1), fields[1], fields[2], fields[4], fields[5], fields[6], 
                            WHITE, noOpacityString, fields[3], line[1] == 'U', hyperlink, not stringIsNumber(fields[1]), false, nullptr, pageContentContext);
                }
               
                break;

            case 'W':

                delimiterPos = stringFindNthOccuranceIndex(line, certusPDF::delimiter, certusPDF::textDelimiterStartPosition + 3);
                
                if (delimiterPos not_eq std::string::npos)
                {
                    fields = stringSplit(line.substr(0, delimiterPos), certusPDF::delimiter);
                    
                    if (fields.size() == 9)
                        writeText(pdfWriter, pdfPage, usedFont, line.substr(delimiterPos + 1), fields[1], fields[2], fields[4], fields[5], 
                            fields[6], fields[7], fields[8], fields[3], line[1] == 'U', hyperlink, not stringIsNumber(fields[1]), false, nullptr, pageContentContext);
                }
               
                break;

            case 'S':

                fields = stringSplit(line, certusPDF::delimiter);
                
                if (fields.size() == 6 and stringIsAscii7(fields[5]))
                {
                    const auto URL = stringTrimEdges(fields[5]);

                    pdfWriter.AttachURLLinktoCurrentPage( (URL.find("http") == std::string::npos) ? "http://" + URL : URL , 
                        { std::stod(fields[1]), std::stod(fields[2]), std::stod(fields[3]), std::stod(fields[4]) });
                }

            case 'P':

                fields = stringSplit(line, certusPDF::delimiter, true);

                stringTrimEdges(fields[2]);

                if (line[1] == 'T' and fields.size() == 6)
                {
                    const auto advance = std::stoul(fields[1]);

                    writePlainTexts(pdfWriter, pdfPage, (fields[2] == "Y" or fields[2] == "y") ? boldFont: font, lines, 
                        index + 1, index  + 1 + advance, fields[3], fields[4], fields[5], pageContentContext);

                    index += advance;
                }

                else if (fields.size() == 15)
                {
                    const auto advance = std::stoul(fields[1]);

                    stringTrimEdges(fields[3]);
                    stringTrimEdges(fields[11]);
                    stringTrimEdges(fields[14]);

                    writeParagraph(pdfWriter, pdfPage, (fields[2] == "Y" or fields[2] == "y") ? boldFont: font, lines, index + 1, index  + 1 + advance,
                        fields[9], fields[10], fields[4], fields[5], fields[6], fields[7], fields[8], (fields[11] == "L") ? "" : fields[12], 
                        (fields[3] == "Y" or fields[3] == "y"), (fields[11] == "R" or fields[11] == "r"), fields[13], 
                        monospaceFont, (fields[14] == "Y" or fields[14] == "y"), pageContentContext);

                    index += advance;
                }
                
                break;

            default:

                break;
        }

        usedFont = font;
    }

    pdfWriter.EndPageContentContext(pageContentContext);

    if (writePDF)
        pdfWriter.WritePageAndRelease(pdfPage);
}

static pdfBuffer createOnePDFFromPDF
(
    const std::vector<std::pair<std::string, std::string>>& input,
    const std::size_t start,
    const std::size_t end,
    const std::string& fontFilePath,
    const std::string& boldFontFilePath,
    const std::string& barcodeFontFilePath,
    const std::string& monospaceFontFilePath,
    const bool withVars = false,
    const std::string& fileName = ""
    )
{
    pdfBuffer pdfStreamBuffer;

    PDFWriter pdfWriter;

    PDFPageRange range;

    range.mSpecificRanges.push_back({0, 0});

    PDFRectangle mediaBox;

    ObjectIDType objectId;

    PDFPage* pdfPage = nullptr;

    PDFParser* pdfParser = nullptr;

    PageContentContext* PCC = nullptr;

    PDFDocumentCopyingContext* DCC = nullptr;

    std::unordered_map<std::string, std::pair<ObjectIDType, PDFRectangle>> templateCache;

    if (fileName.size())
        pdfWriter.StartPDF(fileName, ePDFVersion13);

    else
        pdfWriter.StartPDFForStream(&pdfStreamBuffer, ePDFVersion13);

    PDFUsedFont* font = fileExists(fontFilePath) ? pdfWriter.GetFontForFile(fontFilePath) : nullptr;

    PDFUsedFont* boldFont = fileExists(boldFontFilePath) ? pdfWriter.GetFontForFile(boldFontFilePath) : nullptr;

    PDFUsedFont* barcodeFont = fileExists(barcodeFontFilePath) ? pdfWriter.GetFontForFile(barcodeFontFilePath) : nullptr;

    PDFUsedFont* monospaceFont = fileExists(monospaceFontFilePath) ? pdfWriter.GetFontForFile(monospaceFontFilePath) : nullptr;

    if (font == nullptr or boldFont == nullptr or barcodeFont == nullptr or monospaceFont == nullptr)
        return pdfStreamBuffer;

    const auto endPtr = &input[std::min(end, input.size())];

    for (auto inputPtr = &input[start]; inputPtr < endPtr; ++inputPtr)
    {
        const auto& templatePath = inputPtr->first;

        const auto node = templateCache.find(templatePath);

        if (node not_eq templateCache.end())
        {
            objectId = node->second.first;

            mediaBox = node->second.second;
        }
        
        else
        {
            DCC = pdfWriter.CreatePDFCopyingContext(templatePath);

            objectId = DCC->CreateFormXObjectFromPDFPage(0, EPDFPageBox::ePDFPageBoxMediaBox).second;

            pdfParser = DCC->GetSourceDocumentParser();

            mediaBox = PDFPageInput(pdfParser, pdfParser->ParsePage(0)).GetMediaBox();

            templateCache[templatePath] = {objectId, mediaBox};
        }

        pdfPage = new PDFPage();

        pdfPage->SetMediaBox(mediaBox);
        
        PCC = pdfWriter.StartPageContentContext(pdfPage);

        PCC->q();

        PCC->Do(pdfPage->GetResourcesDictionary().AddFormXObjectMapping(objectId));

        PCC->Q();

        pdfWriter.EndPageContentContext(PCC);

        writePage(pdfWriter, font, boldFont, barcodeFont, monospaceFont, inputPtr->second, pdfPage, mediaBox.GetWidth(), mediaBox.GetHeight(), withVars);

        pdfWriter.WritePageAndRelease(pdfPage);
    }

    if (fileName.size())
        pdfWriter.EndPDF();

    else
        pdfWriter.EndPDFForStream();

    return pdfStreamBuffer;
}

std::pair<bool, std::string> certusPDF::createPDFFromPDFs
(
    const std::vector<std::pair<std::string, std::string>>& input,
    const std::string& fontFilePath,
    const std::string& boldFontFilePath,
    const std::string& barcodeFontFilePath,
    const std::string& monospaceFontFilePath,
    const std::string& pdfFilePath,
    const bool toBase64,
    const bool withVars,
    const unsigned int inputThreads
    )
{
    std::thread writeToFile;

    try
    {   
        if (pdfFilePath.size())
            writeToFile = std::thread( &createOnePDFFromPDF, input, 0, input.size(), fontFilePath, 
                boldFontFilePath, barcodeFontFilePath, monospaceFontFilePath, withVars, pdfFilePath );

        if (not toBase64)
        {
            if (writeToFile.joinable())
                writeToFile.join();

            return {true, {}};
        }
        
        if (inputThreads == 1 or input.size() == 1)
        {
            const auto buffer = createOnePDFFromPDF(input, 0, input.size(), fontFilePath, boldFontFilePath, barcodeFontFilePath, monospaceFontFilePath, withVars);

            const auto& temp = base64_encode(buffer.data(), buffer.size());

            if (writeToFile.joinable())
                writeToFile.join();

            return { true,  temp};
        }

        std::size_t actualThreads = std::min(inputThreads == 0 ? static_cast<unsigned int>(input.size()) : inputThreads, std::thread::hardware_concurrency());
        actualThreads = (actualThreads <= input.size() ? actualThreads : input.size()) - 1;

        const std::size_t pagesPerThread = static_cast<std::size_t>(std::ceil(static_cast<float>(input.size()) / static_cast<float>(actualThreads)));

        pdfBuffer buffer;

        PDFWriter pdfWriterFinal;

        pdfWriterFinal.StartPDFForStream(&buffer, ePDFVersion13);

        std::vector<std::future<pdfBuffer>> outPdfBuffers;
        outPdfBuffers.reserve(actualThreads);

        for (std::size_t index = 0; index < actualThreads; ++index)
            outPdfBuffers.push_back(
                std::async(&createOnePDFFromPDF, input, index * pagesPerThread, (index + 1) * pagesPerThread, 
                    fontFilePath, boldFontFilePath, barcodeFontFilePath, monospaceFontFilePath, withVars, ""));

        for (auto& outPdfBuffer : outPdfBuffers)
        {
            pdfBuffer buffer = outPdfBuffer.get();

            InputByteArrayStream IBAS(buffer.data(), static_cast<long long>(buffer.size()));

            appendPageWithAnnotationsToPDFStream(pdfWriterFinal, &IBAS);
        }

        pdfWriterFinal.EndPDFForStream();

        const auto& temp = base64_encode(buffer.data(), buffer.size());

        if (writeToFile.joinable())
            writeToFile.join();

        return { true, temp };
    }

    catch(const std::exception& e)
    {
        if (writeToFile.joinable())
            writeToFile.join();

        return { false, e.what() };
    }
}

static pdfBuffer createAppendPDF
(
    const std::vector<std::string>& inputPages,
    const std::size_t start,
    const std::size_t end,
    const std::string& fontFilePath,
    const std::string& boldFontFilePath,
    const std::string& barcodeFontFilePath,
    const std::string& monospaceFontFilePath
    )
{
    if (start >= inputPages.size())
        return {};

    PDFWriter pdfWriter;

    pdfBuffer pdfStreamBuffer;

    pdfWriter.StartPDFForStream(&pdfStreamBuffer, ePDFVersion13);

    PDFUsedFont* font = fileExists(fontFilePath) ? pdfWriter.GetFontForFile(fontFilePath) : nullptr;

    PDFUsedFont* boldFont = fileExists(boldFontFilePath) ? pdfWriter.GetFontForFile(boldFontFilePath) : nullptr;

    PDFUsedFont* barcodeFont = fileExists(barcodeFontFilePath) ? pdfWriter.GetFontForFile(barcodeFontFilePath) : nullptr;

    PDFUsedFont* monospaceFont = fileExists(monospaceFontFilePath) ? pdfWriter.GetFontForFile(monospaceFontFilePath) : nullptr;

    for (std::size_t index = start; index < end and index < inputPages.size(); ++index)
        writePage(pdfWriter, font, boldFont, barcodeFont, monospaceFont, inputPages[index]);

    pdfWriter.EndPDFForStream();

    return pdfStreamBuffer;
}

std::pair<bool, std::string> certusPDF::createPDF
(
    const std::vector<std::string>& inputPages,
    const std::string& pdfFilePath,
    const std::string& fontFilePath,
    const std::string& boldFontFilePath,
    const std::string& barcodeFontFilePath,
    const std::string& monospaceFontFilePath,
    const unsigned int inputThreads
    )
{
    std::size_t actualThreads = std::min(inputThreads == 0 ? static_cast<unsigned int>(inputPages.size()) : inputThreads, std::thread::hardware_concurrency());
    actualThreads = (actualThreads <= inputPages.size() ? actualThreads : inputPages.size());

    const std::size_t pagesPerThread = static_cast<std::size_t>(std::ceil(static_cast<float>(inputPages.size()) / static_cast<float>(actualThreads)));

    try
    {
        PDFWriter pdfWriterFinal;

        pdfWriterFinal.StartPDF(pdfFilePath, ePDFVersion13);

        std::vector<std::future<pdfBuffer>> outPdfBuffers;
        outPdfBuffers.reserve(actualThreads);

        for (std::size_t index = 0; index < actualThreads; ++index)
            outPdfBuffers.push_back(
                std::async(&createAppendPDF, std::ref(inputPages), index * pagesPerThread, (index + 1) * pagesPerThread,
                            fontFilePath, boldFontFilePath, barcodeFontFilePath, monospaceFontFilePath) );

        for (auto& outPdfBuffer : outPdfBuffers)
        {
            pdfBuffer buffer = outPdfBuffer.get();

            InputByteArrayStream IBAS(buffer.data(), static_cast<long long>(buffer.size()));

            appendPageWithAnnotationsToPDFStream(pdfWriterFinal, &IBAS);
        }

        pdfWriterFinal.EndPDF();

        return { true, {} };
    }

    catch(const std::exception& e)
    {
        return { false, e.what() };
    }
}

static std::string cellValueAsString
(
    libxl::Sheet* sheet, 
    const int row, 
    const int col, 
    std::stringstream& sstream, 
    libxl::Format** format
    )
{
    const auto type = sheet->cellType(row, col);

    if (type == libxl::CELLTYPE_NUMBER)
    {
        const double number = sheet->readNum(row, col, format);

        if ((*format)->numFormat() == libxl::NUMFORMAT_NUMBER)
            sstream << std::lround(number);

        else
            sstream << number;

        const auto temp = sstream.str();

        sstream.str("");

        return temp;
    }

    else if (type == libxl::CELLTYPE_STRING)
    {
        const auto temp = sheet->readStr(row, col, format);

        return temp not_eq nullptr ? temp : "";
    }

    else if (type == libxl::CELLTYPE_BOOLEAN)
        return sheet->readBool(row, col, format) ? "True" : "False";

    *format = sheet->cellFormat(row, col);

    return "";
}

std::pair<bool, std::string> certusPDF::createPDFFromXLSX
(
    const std::string& xlsxFilePath,
    const std::string& fontFilePath,
    const std::string& boldFontFilePath,
    const std::size_t fontSize,
    const std::string& textColor,
    const bool bold,
    const bool writeToFile
    )
{
    libxl::Book* book = nullptr;

    try
    {
        if (not fileExists(xlsxFilePath))
            return {false, "Xlsx file not found."};

        if (not (fileExtension(xlsxFilePath) == "xlsx"))
            return {false, "File is not xlsx."};

        const auto pdfFilePath = stringSplit(xlsxFilePath, '.', false)[0] + ".pdf";

        book = xlCreateXMLBook();

        //book->setKey("holder name", "code");
        book->setLocale("UTF-8");

        if (not book->loadSheet(xlsxFilePath.data(), 0))
            return { false, "Error opening the xlsx file." };

        constexpr auto borderThicknessThin = "0.5";
        constexpr auto borderThicknessMedium = "1";
        constexpr auto borderThicknessThick = "2";

        constexpr bool linesCoverColumnSpaces = true;

        constexpr std::int32_t horizontalSpace = 1, verticalSpace = 2, margin = 25;

        libxl::Sheet* sheet = book->getSheet(0);
        libxl::Format* cellFormat = nullptr;
        libxl::Font* cellFont = nullptr;

        int rowRepeatFirst, rowRepeatLast;
        const bool repeats = sheet->printRepeatRows(&rowRepeatFirst, &rowRepeatLast);

        const std::int32_t firstRow = sheet->firstRow(), lastRow = sheet->lastRow();
        const std::int32_t firstCol = sheet->firstCol(), lastCol = sheet->lastCol();

        int rowFirst = 0, rowLast = 0, colFirst = 0, colLast = 0;

        std::map<std::pair<std::int32_t, std::int32_t>, std::array<int, 4>> mergedCells;

        for (auto i = 0; i < sheet->mergeSize(); ++i)
        {
            sheet->merge(i, &rowFirst, &rowLast, &colFirst, &colLast);

            for (auto r = rowFirst; r <= rowLast; ++r)
                for (auto c = colFirst; c <= colLast; ++c)
                    mergedCells[{r, c}] = {rowFirst, rowLast, colFirst, colLast};
        }

        const auto mapEnd = mergedCells.end();

        PDFWriter pdfWriter;

        pdfBuffer pdfStreamBuffer;

        PDFUsedFont* pdfRegularFont = fileExists(fontFilePath) ? pdfWriter.GetFontForFile(fontFilePath) : nullptr;

        PDFUsedFont* pdfBoldFont = fileExists(boldFontFilePath) ? pdfWriter.GetFontForFile(boldFontFilePath) : nullptr;

        PDFUsedFont* pdfUsedFont = bold ? pdfBoldFont : pdfRegularFont; 

        PDFUsedFont* pdfCellUsedFont = nullptr;

        if (pdfRegularFont == nullptr or pdfBoldFont == nullptr)
            return {false, "Font files not valid."};

        std::stringstream sstream;
        sstream.setf(std::ios::fixed);
        sstream.precision(2);
        sstream.imbue(std::locale(""));

        std::size_t usedDimX = certusPDF::dimX;
        std::size_t usedDimY = certusPDF::dimY;

        if (sheet->landscape())
            std::swap(usedDimX, usedDimY);

        std::int32_t pageWidthPx = 0;
        for(auto c = firstCol; c not_eq lastCol; ++c)
            pageWidthPx += sheet->colWidthPx(c);

        const double factorHorizontal = (usedDimX - 2.0 * margin - (lastCol - firstCol) * horizontalSpace) / pageWidthPx;

        std::vector<std::size_t> colWidthsVector(lastCol + 1);
        for (auto c = firstCol; c not_eq lastCol; ++c)
            colWidthsVector[c] = std::lround(sheet->colWidthPx(c) * factorHorizontal);

        const std::int32_t startX = margin, endX = usedDimX - margin;
        const std::int32_t startY = usedDimY - margin, endY = margin;

        const std::string fontSizeString = std::to_string(fontSize);
        const std::string startXString = std::to_string(startX);
        const std::string endXString = std::to_string(endX);

        const auto headerPtr = sheet->header();

        std::string header = headerPtr not_eq nullptr ? headerPtr : "";

        if (header.size() > 3)
            header = header.substr(3);

        const auto headerDimensions = (bold ? pdfBoldFont : pdfRegularFont)->CalculateTextDimensions(header, fontSize);
        const auto headerHeight = headerDimensions.height + headerDimensions.yMin;
        const std::string headerY = std::to_string(startY + ((margin - std::lround(headerHeight)) >> 1));

        const std::string footerCompany = "Powered by CERTUS ONLINE";
        const auto dateTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const std::string footerDateTime = std::ctime(&dateTime);
        const std::string footerPage = "Page: ";
        const std::string footer = footerCompany + footerDateTime + footerPage + std::string("0123456789");

        const auto footerCompanyDimensions = (bold ? pdfBoldFont : pdfRegularFont)->CalculateTextDimensions(footerCompany, fontSize);
        const auto footerDateTimeDimensions = (bold ? pdfBoldFont : pdfRegularFont)->CalculateTextDimensions(footerDateTime, fontSize);

        const auto footerDimensions = (bold ? pdfBoldFont : pdfRegularFont)->CalculateTextDimensions(footer, fontSize);
        const auto footerHeight = footerDimensions.height + footerDimensions.yMin;
        const std::string footerY = std::to_string((margin - std::lround(footerHeight)) >> 1);

        if (writeToFile)
            pdfWriter.StartPDF(pdfFilePath, ePDFVersion13);

        else
            pdfWriter.StartPDFForStream(&pdfStreamBuffer, ePDFVersion13);

        const auto pdfRectangle = PDFRectangle(0, 0, usedDimX, usedDimY);

        PDFPage* pdfPage = new PDFPage();

        pdfPage->SetMediaBox(pdfRectangle);

        PageContentContext* pageContentContext = pdfWriter.StartPageContentContext(pdfPage);

        writeText(pdfWriter, pdfPage, pdfUsedFont, header, startXString, headerY, fontSizeString, textColor, noOpacityString,
            WHITE, noOpacityString, endXString, false, "", false, true, &headerDimensions, pageContentContext);

        std::int32_t currentRow, cellWidth, cellHeight, textHeight;

        std::size_t pageIndex = 1, advanceCols;

        bool isOverlapped, isMerged = false;

        for (std::int32_t row = firstRow, cursorY = startY; row < lastRow; ++row, cursorY -= cellHeight + verticalSpace)
        {   
            if (repeats and pageIndex > 1 and row == rowRepeatLast + 1)
                row = currentRow;

            if (cursorY <= endY)
            {
                writeText(pdfWriter, pdfPage, pdfUsedFont, footerCompany, startXString, footerY, fontSizeString, 
                    textColor, noOpacityString, WHITE, noOpacityString, "", false, "", false, true, &footerCompanyDimensions, pageContentContext);

                writeText(pdfWriter, pdfPage, pdfUsedFont, footerDateTime, startXString, footerY, fontSizeString, 
                    textColor, noOpacityString, WHITE, noOpacityString, endXString, false, "", false, true, &footerDateTimeDimensions, pageContentContext);

                writeText(pdfWriter, pdfPage, pdfUsedFont, footerPage + std::to_string(pageIndex), startXString, footerY, fontSizeString, 
                    textColor, noOpacityString, WHITE, noOpacityString, endXString, false, "", true, false, nullptr, pageContentContext);

                pdfWriter.EndPageContentContext(pageContentContext);

                pdfWriter.WritePageAndRelease(pdfPage);

                pdfPage = new PDFPage();

                pdfPage->SetMediaBox(pdfRectangle);

                pageContentContext = pdfWriter.StartPageContentContext(pdfPage);

                writeText(pdfWriter, pdfPage, pdfUsedFont, header, startXString, headerY, fontSizeString, textColor, noOpacityString, 
                    WHITE, noOpacityString, endXString, false, "", false, true, &headerDimensions, pageContentContext);

                ++pageIndex;

                cursorY = startY;

                if (repeats)
                {
                    currentRow = row;

                    row = rowRepeatFirst;
                }
            }

            isOverlapped = false;

            for (std::int32_t col = firstCol, cursorX = startX; col < lastCol; cursorX += cellWidth + horizontalSpace, col += advanceCols)
            {
                advanceCols = 1;

                const std::string cellStrValue = cellValueAsString(sheet, row, col, sstream, &cellFormat);

                cellFont = cellFormat->font();

                const auto cellTextColorCode = cellFont->color();
                const auto cellColorCode = cellFormat->patternForegroundColor();

                std::string cellTextColor = WHITE;
                std::string cellColor = WHITE;

                if (cellTextColorCode > 7 and cellTextColorCode < 66 and cellTextColorCode not_eq libxl::COLOR_WHITE and cellTextColorCode not_eq libxl::COLOR_DEFAULT_FOREGROUND and cellTextColorCode not_eq libxl::COLOR_DEFAULT_BACKGROUND)
                    cellTextColor = libxlColors::colorMap.at(cellTextColorCode);

                if (cellColorCode > 7 and cellColorCode < 66 and cellColorCode not_eq libxl::COLOR_WHITE and cellColorCode not_eq libxl::COLOR_DEFAULT_FOREGROUND and cellColorCode not_eq libxl::COLOR_DEFAULT_BACKGROUND)
                    cellColor = libxlColors::colorMap.at(cellColorCode);

                pdfCellUsedFont = cellFont->bold() ? pdfBoldFont : pdfRegularFont;

                const auto cellStrValueDimensions = pdfCellUsedFont->CalculateTextDimensions(cellStrValue, cellFont->size());

                textHeight = cellStrValueDimensions.height + cellStrValueDimensions.yMin;

                const auto node = mergedCells.find({row, col});

                if (node not_eq mapEnd)
                {
                    isMerged = true;

                    const auto& arrayRef = node->second;

                    advanceCols = arrayRef[3] - arrayRef[2] + 1;

                    cellWidth = cellHeight = 0;

                    for(auto r = arrayRef[0]; r <= arrayRef[1]; ++r)
                        cellHeight += sheet->rowHeight(r);

                    for(auto c = arrayRef[2]; c <= arrayRef[3]; ++c)
                        cellWidth += colWidthsVector[c];

                    cellWidth += (advanceCols - 1) * horizontalSpace;
                }

                else
                {
                    isMerged = false;

                    cellHeight = sheet->rowHeight(row);

                    cellWidth = colWidthsVector[col];
                }

                auto horizontalLineLength = linesCoverColumnSpaces ? cellWidth + horizontalSpace : cellWidth;

                if (col == lastCol - 1)
                    cellWidth += horizontalSpace;

                auto tempCursorY = cursorY - cellHeight;                    

                if (cellFormat->fillPattern() == libxl::FILLPATTERN_SOLID and cellColor not_eq WHITE)
                    pageContentContext->DrawRectangle(cursorX, tempCursorY, cellWidth, cellHeight, 
                        { PageContentContext::eFill, PageContentContext::eRGB, std::stoul(cellColor, nullptr, 16), 1.0, false, NO_OPACITY_VALUE });
                
                else if (isOverlapped)
                    pageContentContext->DrawRectangle(cursorX, tempCursorY, cellWidth, cellHeight, 
                        { PageContentContext::eFill, PageContentContext::eRGB, WHITE_LONG, 1.0, false, NO_OPACITY_VALUE });

                isOverlapped = false;

                if (cellStrValueDimensions.width + cellStrValueDimensions.xMin > cellWidth)
                    isOverlapped = true;

                const auto blc = cellFormat->borderLeftColor();
                const auto brc = cellFormat->borderRightColor();
                const auto btc = cellFormat->borderTopColor();
                const auto bbc = cellFormat->borderBottomColor();

                if (cellFormat->borderLeft() not_eq libxl::BORDERSTYLE_NONE and (blc == libxlColors::DEFAULT or (blc > 7 and blc < 66 and blc not_eq libxl::COLOR_WHITE and blc not_eq libxl::COLOR_DEFAULT_FOREGROUND and blc not_eq libxl::COLOR_DEFAULT_BACKGROUND)))
                    drawLine(pdfWriter, pdfPage, std::to_string(cursorX), std::to_string(tempCursorY), std::to_string(cursorX), std::to_string(tempCursorY + cellHeight), 
                        cellFormat->borderLeft() == libxl::BORDERSTYLE_THIN ? borderThicknessThin : (cellFormat->borderLeft() == libxl::BORDERSTYLE_MEDIUM ? borderThicknessMedium : borderThicknessThick), 
                        libxlColors::colorMap.at(blc), noOpacityString, pageContentContext);

                if (cellFormat->borderRight() not_eq libxl::BORDERSTYLE_NONE and (blc == libxlColors::DEFAULT or (brc > 7 and brc < 66 and brc not_eq libxl::COLOR_WHITE and brc not_eq libxl::COLOR_DEFAULT_FOREGROUND and brc not_eq libxl::COLOR_DEFAULT_BACKGROUND)))
                    drawLine(pdfWriter, pdfPage, std::to_string(cursorX + cellWidth), std::to_string(tempCursorY), std::to_string(cursorX + cellWidth), std::to_string(tempCursorY + cellHeight), 
                        cellFormat->borderRight() == libxl::BORDERSTYLE_THIN ? borderThicknessThin : (cellFormat->borderRight() == libxl::BORDERSTYLE_MEDIUM ? borderThicknessMedium : borderThicknessThick), 
                        libxlColors::colorMap.at(brc), noOpacityString, pageContentContext);

                if (cellFormat->borderTop() not_eq libxl::BORDERSTYLE_NONE and (blc == libxlColors::DEFAULT or (btc > 7 and btc < 66 and btc not_eq libxl::COLOR_WHITE and btc not_eq libxl::COLOR_DEFAULT_FOREGROUND and btc not_eq libxl::COLOR_DEFAULT_BACKGROUND)))
                    drawLine(pdfWriter, pdfPage, std::to_string(cursorX), std::to_string(tempCursorY + cellHeight), std::to_string(cursorX + horizontalLineLength), std::to_string(tempCursorY + cellHeight), 
                        cellFormat->borderTop() == libxl::BORDERSTYLE_THIN ? borderThicknessThin : (cellFormat->borderTop() == libxl::BORDERSTYLE_MEDIUM ? borderThicknessMedium : borderThicknessThick), 
                        libxlColors::colorMap.at(btc), noOpacityString, pageContentContext);

                if (cellFormat->borderBottom() not_eq libxl::BORDERSTYLE_NONE and (blc == libxlColors::DEFAULT or (bbc > 7 and bbc < 66 and bbc not_eq libxl::COLOR_WHITE and bbc not_eq libxl::COLOR_DEFAULT_FOREGROUND and bbc not_eq libxl::COLOR_DEFAULT_BACKGROUND)))
                    drawLine(pdfWriter, pdfPage, std::to_string(cursorX), std::to_string(tempCursorY), std::to_string(cursorX + horizontalLineLength), std::to_string(tempCursorY), 
                        cellFormat->borderBottom() == libxl::BORDERSTYLE_THIN ? borderThicknessThin : (cellFormat->borderBottom() == libxl::BORDERSTYLE_MEDIUM ? borderThicknessMedium : borderThicknessThick), 
                        libxlColors::colorMap.at(bbc), noOpacityString, pageContentContext);

                if (cellStrValue.size() == 0)
                {
                    if (isMerged)
                        cellWidth = 0;

                    continue;
                }

                const auto diffHeight = cellHeight - textHeight;

                if (diffHeight > 0)
                {
                    const auto align = cellFormat->alignV();

                    if (align == libxl::ALIGNV_CENTER)
                        tempCursorY += diffHeight >> 1;

                    else if (align == libxl::ALIGNV_TOP)
                        tempCursorY += diffHeight;
                }

                switch(cellFormat->alignH())
                {
                    case libxl::ALIGNH_CENTER:

                        writeText(pdfWriter, pdfPage, pdfCellUsedFont, cellStrValue, std::to_string(cursorX), std::to_string(tempCursorY), std::to_string(cellFont->size()), 
                            cellTextColor, noOpacityString, WHITE, noOpacityString, std::to_string(cursorX + cellWidth), cellFont->underline(), "", false, true, &cellStrValueDimensions, pageContentContext);

                        break;

                    case libxl::ALIGNH_RIGHT:

                        writeText(pdfWriter, pdfPage, pdfCellUsedFont, cellStrValue, std::to_string(cursorX), std::to_string(tempCursorY), std::to_string(cellFont->size()), 
                            cellTextColor, noOpacityString, WHITE, noOpacityString, std::to_string(cursorX + cellWidth), cellFont->underline(), "", true, false, &cellStrValueDimensions, pageContentContext);

                        break;

                    case libxl::ALIGNH_LEFT:

                        writeText(pdfWriter, pdfPage, pdfCellUsedFont, cellStrValue, std::to_string(cursorX), std::to_string(tempCursorY), std::to_string(cellFont->size()), 
                            cellTextColor, noOpacityString, WHITE, noOpacityString, "", cellFont->underline(), "", false, false, &cellStrValueDimensions, pageContentContext);

                        break;

                    default:

                        if (sheet->cellType(row, col) == libxl::CELLTYPE_STRING)
                            writeText(pdfWriter, pdfPage, pdfCellUsedFont, cellStrValue, std::to_string(cursorX), std::to_string(tempCursorY), std::to_string(cellFont->size()), 
                                cellTextColor, noOpacityString, WHITE, noOpacityString, "", cellFont->underline(), "", false, false, &cellStrValueDimensions, pageContentContext);
                        else
                            writeText(pdfWriter, pdfPage, pdfCellUsedFont, cellStrValue, std::to_string(cursorX), std::to_string(tempCursorY), std::to_string(cellFont->size()), 
                                cellTextColor, noOpacityString, WHITE, noOpacityString, std::to_string(cursorX + cellWidth), cellFont->underline(), "", true, false, &cellStrValueDimensions, pageContentContext);

                        break;
                }
            }            
        }

        writeText(pdfWriter, pdfPage, pdfUsedFont, footerCompany, startXString, footerY, fontSizeString, 
            textColor, noOpacityString, WHITE, noOpacityString, "", false, "", false, true, &footerCompanyDimensions, pageContentContext);

        writeText(pdfWriter, pdfPage, pdfUsedFont, footerDateTime, startXString, footerY, fontSizeString, 
            textColor, noOpacityString, WHITE, noOpacityString, endXString, false, "", false, true, &footerDateTimeDimensions, pageContentContext);

        writeText(pdfWriter, pdfPage, pdfUsedFont, footerPage + std::to_string(pageIndex), startXString, footerY, fontSizeString, 
            textColor, noOpacityString, WHITE, noOpacityString, endXString, false, "", true, false, nullptr, pageContentContext);

        pdfWriter.EndPageContentContext(pageContentContext);

        pdfWriter.WritePageAndRelease(pdfPage);

        if (writeToFile)
            pdfWriter.EndPDF();

        else
            pdfWriter.EndPDFForStream();

        book->release();

        return { true, writeToFile ? "" : base64_encode(pdfStreamBuffer.data(), pdfStreamBuffer.size()) };
    }

    catch(const std::exception& e)
    {
        if (book) 
            book->release();

        return { false, e.what() };
    }
}