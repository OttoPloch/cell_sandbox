#pragma once

#include <unistd.h>
#include <filesystem>
#include <limits.h>

std::filesystem::path getExecutablePath();

std::filesystem::path getProjectPath();