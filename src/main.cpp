#include <iostream>
#include "../include/Operations.hh"
#include "../include/ReplacerUtilities.hh"
#include <filesystem>

int main(){

    using namespace Operations;

    char option = 0;

    std::cout<<"Use default installation folder? y/n\n";

    while(option != static_cast<char>(Options::Yes) && option != static_cast<char>(Options::No)){

        std::cin>>option;
    }

    std::filesystem::path osuPath;

    if(option != static_cast<char>(Options::Yes)){

        std::cout<<"Paste the path of your osu folder\n";
        std::cin>>osuPath;

    }else{

        osuPath = ReplacerUitilities::getOsuPath();

    }

    char mode = 0;

    std::cout<<"Which mode do you want to use?\n";

    std::cout<<"d = delete\n";

    std::cout<<"r = replace\n";


    while (mode != static_cast<char>(Modes::Delete) && mode != static_cast<char>(Modes::Replace)) {
    
        std::cin>>mode;
    }
    


    if (mode == static_cast<char>(Modes::Replace)){
        
        std::filesystem::path replacementImage;
        char conserveImage;

        while (!ReplacerUitilities::validExtension(replacementImage) || !std::filesystem::exists(replacementImage)){

        std::cout<<"Input the replacement image, the format should be either png, jpg or jpeg";

        std::cin>>replacementImage;

        }

        std::cout<<"Should the images that aren't compatible with the format of the new one be kept? y/n\n";

        while(conserveImage != static_cast<char>(Options::Yes) && conserveImage != static_cast<char>(Options::No)){

            std::cin>>conserveImage;
        }

        ReplacerUitilities::applyToAll(osuPath,[&](const std::filesystem::path& file){

            std::cout<< ReplacerUitilities::replaceImage(file, replacementImage, conserveImage);

            });

    }

    if(mode == static_cast<char>(Modes::Delete)){

        ReplacerUitilities::applyToAll(osuPath, [&](const std::filesystem::path& file) {

        std::cout << ReplacerUitilities::deleteImage(file);

        });
    }

    return 0;
}