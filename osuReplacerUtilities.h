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
int validateOption(std::string input){
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

