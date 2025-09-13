#include <filesystem>
#include <iostream>
#include <string>
#include <typeinfo>
#include <algorithm> 
#include <cctype>   

namespace fs = std::filesystem;

void printInfoMessage(std::string message){
    std::cout<<message;
    }

std::string toUpperCase(std::string stringToConvert){
    std::transform(stringToConvert.begin(), stringToConvert.end(), stringToConvert.begin(),[](unsigned char c) { return std::toupper(c); });
    return stringToConvert;
    }

fs::path getOsuPath(){
    //get the path where osu! is installed, if it isnt installed returns an empty PATH;returns the osu PATH otherwise
    const char* user=std::getenv("USERPROFILE");
    if(nullptr==user){
        printInfoMessage("Couldnt find the user path \n");
        return fs::path{};
    }

    fs::path path=fs::path(user)/"AppData"/"Local"/"osu!"/"Songs";

    if(!fs::exists(path)){
        printInfoMessage("Couldnt find the osu! folder \n");
        return fs::path{};
    }
    return path;
}

bool validExtension(std::string filePathString){
    filePathString=toUpperCase(filePathString);
    return filePathString==".PNG" || filePathString==".JPG" || filePathString==".JPEG";
}

bool validReplacementPath(fs::path replacementPath){
    if(!fs::exists(replacementPath)){
        printInfoMessage("The specified file does not exist");
        return false;
    }
    if(!validExtension(replacementPath.extension().string())){
        printInfoMessage("The specified file's extension is not valid");
        return false;
    }
    return true;
    }
void deleteBackrounds(fs::path osuPath){
    for(const auto& osuFolder: fs::directory_iterator(osuPath)){
        if(!fs::is_directory(osuFolder)){
            continue;
        }
 
        fs::path mapFolder=osuFolder.path();
        for(const auto& songFolder: fs::directory_iterator(mapFolder)){//loops trough every folder in songs
            if(!fs::is_regular_file(songFolder)){//ignores anything that is not a regular file
                continue;
            }
            fs::path currentFilePath=songFolder.path();//stores the current file its checking
            std::string currentFileExtension=currentFilePath.extension().string();//obtains the extension of the current file its checking
            if(!validExtension(currentFileExtension)){
                continue;
            }  
            fs::remove(currentFilePath);
            printInfoMessage("background from "+currentFilePath.string()+" has been deleted \n");
                                                }
                                            }
                                        }


void replaceBackgrounds(fs::path osupath){

    printInfoMessage("Input the path of the replacement image");
    std::string replacementPathString;
    std::getline(std::cin>>std::ws,replacementPathString);
    fs::path replacementPath=fs::path(replacementPathString);
    if(validReplacementPath(replacementPath)){
        return;
    }
}
int setOption(std::string input){
    int option;
        try {
        option = std::stoi(input); 
    } catch (const std::invalid_argument& e) {
        printInfoMessage("Only numbers please\n");
        return -1;
    } catch (const std::out_of_range& e) {
        printInfoMessage("There are only two options silly.\n");
        return -1;
    }
    return option;
}

int main(){
    fs::path osuPath=getOsuPath();

    if(osuPath==fs::path{}){
        printInfoMessage("Cant continue without a valid osu PATH \n");
        return 0;
    }

    int option=-1;
    std::string input;
    while(option<1 || option>2){
        
    printInfoMessage("Input 1 to delete all backgrounds, input 2 to replace them \n");
    std::getline(std::cin,input);
    option=setOption(input);
    }
        option==1? deleteBackrounds(osuPath):replaceBackgrounds(osuPath);
    

    return 0;
}

