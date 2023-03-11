#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>

#include <compile.h>

std::vector<std::string> open_files(const std::vector<std::string>& file_paths);

int main() {
//
//    for (auto & [k, v]: TOKEN) {
//        std::cout << k << "\n";
//    }
//    auto b = TOKENS_MAP["hellpo"];
//    auto a = 10;
    auto data = open_files(std::vector<std::string>({"/home/spaceeye/CLionProjects/PrettyNormalProgrammingLanguage/test.pnpl"}));

    if (data.empty()) {
        std::cout << "No files detected. Aborting.";
        return 0;
    }

    compile(data[0]);

    return 0;
}

std::vector<std::string> open_files(const std::vector<std::string>& file_paths) {
    std::vector<std::string> to_return;

    for (auto & path_name: file_paths) {
        std::filesystem::path path{path_name};
        if (is_directory(path) || !exists(path)) {
            std::cout << path << " is not included because it is either a directory or doesn't exist.\n";
            continue;
        }
        std::ifstream t(path);
        std::stringstream buffer;
        buffer << t.rdbuf();
        to_return.emplace_back(buffer.str());
    }

    return to_return;
}