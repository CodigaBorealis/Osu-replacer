#include <filesystem>
#include <algorithm>
#include <functional>
namespace fs = std::filesystem;
void printInfoMessage(std::string message)
{
    std::cout << message << "\n";
}
std::string toUpperCase(std::string stringToConvert)
{
    std::transform(stringToConvert.begin(), stringToConvert.end(), stringToConvert.begin(), [](unsigned char c)
                   { return std::toupper(c); });
    return stringToConvert;
}
bool validExtension(std::string filePathString)
{
    filePathString = toUpperCase(filePathString);
    return filePathString == ".PNG" || filePathString == ".JPG" || filePathString == ".JPEG";
}
int validateOption(std::string input)
{
    int option;
    try
    {
        option = std::stoi(input);
    }
    catch (const std::invalid_argument &e)
    {
        printInfoMessage("Only numbers please\n");
        return -1;
    }
    catch (const std::out_of_range &e)
    {
        printInfoMessage("There are only two options silly.\n");
        return -1;
    }
    return option;
}
bool compatibleExtension(std::string replacementExtension, std::string currentFileExtension)
{
    return replacementExtension == currentFileExtension;
}
fs::path getOsuPath()
{
    // get the path where osu! is installed, if it isnt installed returns an empty PATH;returns the osu PATH otherwise
    const char *user = std::getenv("USERPROFILE");
    if (nullptr == user)
    {
        printInfoMessage("Couldnt find the user path \n");
        return fs::path{};
    }

    fs::path path = fs::path(user) / "AppData" / "Local" / "osu!" / "Songs";

    if (!fs::exists(path))
    {
        printInfoMessage("Couldnt find the osu! folder \n");
        return fs::path{};
    }
    return path;
}
bool validReplacementPath(fs::path replacementPath)
{
    if (!fs::exists(replacementPath))
    {
        printInfoMessage("The specified file does not exist");
        return false;
    }
    if (!validExtension(replacementPath.extension().string()))
    {
        printInfoMessage("The specified file's extension is not valid");
        return false;
    }
    return true;
}
int handleInput()
{
    int option = -1;
    std::string input;
    while (option < 1 || option > 2)
    {

        printInfoMessage("Input 1 to delete all backgrounds, input 2 to replace them \n");
        std::getline(std::cin, input);
        option = validateOption(input);
    }
    return option;
}
void forAllBackrounds(const fs::path osuPath, std::function<void(const fs::path)> action)
{
    for (const auto &osuFolder : fs::directory_iterator(osuPath))
    {
        if (!fs::is_directory(osuFolder))
        {
            continue;
        }

        fs::path mapFolder = osuFolder.path();
        for (const auto &songFolder : fs::directory_iterator(mapFolder))
        {
            if (!fs::is_regular_file(songFolder))
            {
                continue;
            }
            fs::path currentFilePath = songFolder.path();
            std::string currentFileExtension = currentFilePath.extension().string();
            if (!validExtension(currentFileExtension))
            {
                continue;
            }
            action(currentFilePath);
        }
    }
}