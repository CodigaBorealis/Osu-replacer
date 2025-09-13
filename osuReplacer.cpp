#include <filesystem>
#include <iostream>
#include <string>
#include "osuReplacerUtilities.h"
namespace fs = std::filesystem;
void renameAndAppend(fs::path replacementPath, fs::path backgroundPath)
{
    try
    {
        fs::path beatmapFolder = backgroundPath.parent_path() / backgroundPath;
        fs::copy_file(replacementPath, beatmapFolder, fs::copy_options::overwrite_existing);
        printInfoMessage(backgroundPath.string() + " has been replaced with " + replacementPath.string());
    }
    catch (fs::filesystem_error &e)
    {
        printInfoMessage("An error has ocurred while trying to copy your file");
    }
}
// Loops trough all the beatmap folders and deletes the image files
void deleteBackgrounds(fs::path osuPath)
{
    forAllBackrounds(osuPath, [](const fs::path &currentFile)
                     {
        fs::remove(currentFile);
        printInfoMessage("Background from: "+currentFile.string() + " has been deleted"); });
}

void replaceBackgrounds(fs::path osuPath)
{
    printInfoMessage("Input the path of the replacement image, this will replace the background of every map that shares format with the given image");
    std::string replacementPathString;
    std::getline(std::cin >> std::ws, replacementPathString);
    fs::path replacementPath = fs::path(replacementPathString);
    std::string replacementExtension = replacementPath.extension().string();

    if (!validReplacementPath(replacementPath))
    {
        replaceBackgrounds(osuPath);
    }
    forAllBackrounds(osuPath, [&](const fs::path &currentFile)
                     {
                         if (!compatibleExtension(replacementExtension, currentFile.extension().string()))
                         {
                             printInfoMessage(currentFile.string() + " could not be replaced because the file extension does not match");
                             return;
                         }
                         renameAndAppend(replacementPath, currentFile); });
}

int main()
{
    const fs::path osuPath = getOsuPath();

    if (osuPath == fs::path{})
    {
        printInfoMessage("Cant continue without a valid osu PATH");
        return 0;
    }
    int option = handleInput();
    if (option == 1)
    {
        deleteBackgrounds(osuPath);
    }
    else
    {
        replaceBackgrounds(osuPath);
    }
    printInfoMessage("Press Enter to exit");
    std::cin.get();

    return 0;
}
