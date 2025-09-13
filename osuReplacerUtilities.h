#include <filesystem>
void printInfoMessage(std::string message){
    std::cout<<message;
    }
std::string toUpperCase(std::string stringToConvert){
    std::transform(stringToConvert.begin(), stringToConvert.end(), stringToConvert.begin(),[](unsigned char c) { return std::toupper(c); });
    return stringToConvert;
    }
bool validExtension(std::string filePathString){
    filePathString=toUpperCase(filePathString);
    return filePathString==".PNG" || filePathString==".JPG" || filePathString==".JPEG";
}
