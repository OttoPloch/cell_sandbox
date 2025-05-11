#include "getPaths.hpp"

std::filesystem::path getExecutablePath() {
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
    buffer[len] = '\0';
    return std::filesystem::path(buffer).parent_path();
}

std::filesystem::path getProjectPath() {
    return getExecutablePath().parent_path().parent_path();
}