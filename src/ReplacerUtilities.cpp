#include "../include/ReplacerUtilities.hh"
#include "../include/Operations.hh"
#include <algorithm>
#include <filesystem>

std::string ReplacerUitilities::toUpperCase(std::string string){

    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c){

        return std::toupper(c); 

    });

    return string;
}

void ReplacerUitilities::applyToAll(const std::filesystem::path& parentDirectory, const std::function<void (const std::filesystem::path&)>& callback){

    for (const auto &dirEntry : std::filesystem::directory_iterator(parentDirectory)){

        if (!dirEntry.is_directory()){

            continue;
        }

        for (const auto &fileEntry : std::filesystem::directory_iterator(dirEntry.path())){

            if (!fileEntry.is_regular_file()){

                continue;
            }

            const auto& currentFile = fileEntry.path();
            
            if (!validExtension(currentFile)){

                continue;
            }

            callback(currentFile);
        }
    }
}

std::filesystem::path ReplacerUitilities::getOsuPath(){

    const char *user = std::getenv("USERPROFILE");

    if (nullptr == user){
        
        return std::filesystem::path{};
    }

    return std::filesystem::path(user) / "AppData" / "Local" / "osu!" / "Songs";
}

bool ReplacerUitilities::compatibleExtension(const std::filesystem::path& replacementFile, const std::filesystem::path& currentFile){

        return toUpperCase(replacementFile.extension().string()) == toUpperCase(currentFile.extension().string());
}

bool ReplacerUitilities::validExtension(const std::filesystem::path& file){

    std::string extension = toUpperCase(file.extension().string());

    return extension == ".PNG" || extension == ".JPG" || extension == ".JPEG";
}

std::string ReplacerUitilities::deleteImage(const std::filesystem::path& file){
    
    try{

        std::filesystem::remove(file);

        return "Background from: " + file.string() + " has been deleted\n";

    }catch(std::filesystem::filesystem_error& e){

        return "ERROR: Could not delete" + file.string() + std::string(" ") + std::string(e.what()) + "\n";

    }

}

std::string ReplacerUitilities::replaceImage(const std::filesystem::path& original, const std::filesystem::path& replacement, char keepFiles){

    if(!compatibleExtension(replacement,  original)){

        if(keepFiles == static_cast<char>(Operations::Options::No)){
            
            deleteImage(original);

            return "";

        }else{

            return "ERROR:" + original.string() + " could not be replaced because the file extension does not match\n";

        }

    }
        
    try{

        std::filesystem::copy_file(replacement, original, std::filesystem::copy_options::overwrite_existing);

        return original.string() + " has been replaced with " + replacement.string() + "\n";

    }catch (std::filesystem::filesystem_error &e){

        return "ERROR: Could not replace" + original.string() + "with " + replacement.string() + " " +  std::string(e.what()) + "\n";
    }
    
}
