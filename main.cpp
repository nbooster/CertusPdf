#include <iostream>
#include <chrono>
#include <vector>

#include "certusPDF.h"
#include "block.h"

int main()
{
    std::cout << "\nStart pdf writting...\n";

    /* --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

    /*const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    const std::string templatePath = "./templates/";

    const std::string templateName = "templateEVehicle1";

    const auto result = certusPDF::createPDF({ fileToString(templatePath + templateName + ".txt") }, templatePath + templateName + "1.pdf", "./fonts/arialnarrow.ttf", "./fonts/G_ari_bd.TTF", "./fonts/bcode39.ttf", "./fonts/monofonto rg.otf");

    const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    const auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    std::cout << "\nPdf ended in time: " << time / 1'000'000.0 << " msecs.\n\n";*/

     /* --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

    /*constexpr std::size_t pages = 1;

    for (auto ip = pages; ip <= pages; ++ip)
    {
        const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        certusPDF::CertusPDF certusPDFObject;

        certusPDFObject.addTemplatePair("vehicle1", "./templates/templateEVehicle1.pdf", "./templates/fieldsEVehicle1.txt");
        certusPDFObject.addTemplatePair("passenger1", "./templates/templateEPassenger1.pdf", "./templates/fieldsEPassenger1.txt");

        Block block;

        std::vector<std::pair<std::string, std::string>> data;

        std::string base64pdf; 

        for (auto i = 1; i <= ip; ++i)
        {
            block.setValue("totalprice", std::to_string(i * 10));

            const auto& valuePair = certusPDFObject.getTemplatePair("passenger1");

            auto fields = fileToString(valuePair.second);

            fillTemplate(fields, &block);

            data.emplace_back(valuePair.first, fields);
        }

        std::string pdfFileName = "result_" + std::to_string(ip) + ".pdf";

        constexpr auto threads = 1;
        
        base64pdf = certusPDF::createPDFFromPDFs(data, "./fonts/cynthopro-regular-webfont.ttf", "./fonts/cynthopro-bold-webfont.ttf", "./fonts/bcode39.ttf", "./fonts/monofonto rg.otf", pdfFileName, true, false, threads).second;
        
        const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        std::cout << "\n" << ip << " pages Pdf ended in best time: " << time << " msecs, with: " << threads << " threads and base64 buffer size: " << base64pdf.size() << " .\n\n";
        
    }*/

     /* --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

    const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    constexpr auto inputPdf = "244187.xlsx";//14662.xlsx

    std::string base64pdf = certusPDF::createPDFFromXLSX(inputPdf, "./fonts/gfs-neohellenic.regular.ttf", "./fonts/gfs-neohellenic.bold.ttf", 8).second;
    
    const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    const auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    std::cout << "\nPdf ended in time: " << time / 1'000'000.0 << " msecs, and size: " << base64pdf.size() << " bytes. \n\n";

     /* --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
    
    return EXIT_SUCCESS;
}
