#pragma once
#include <filesystem>
#include <functional>

namespace ReplacerUitilities{

std::filesystem::path getOsuPath();
std::string deleteImage(const std::filesystem::path&);
std::string replaceImage(const std::filesystem::path&, const std::filesystem::path&, char);
std::string toUpperCase(const std::string);
bool compatibleExtension(const std::filesystem::path&, const std::filesystem::path&);
bool validExtension(const std::filesystem::path&);
void applyToAll(const std::filesystem::path&, const std::function<void(const std::filesystem::path&)>& callback);
};