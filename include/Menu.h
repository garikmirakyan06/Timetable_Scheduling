#pragma once


#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include <nlohmann/json.hpp>
#include "BruteForceUniversity.h"
#include "University.h"
#include "Timer.h"

namespace fs = std::filesystem;


class Menu {
private:
    const std::string dirPath = "../resources/";
    std::vector<std::string> fileNames;


    std::vector<std::string> getFilesInfo() const;

public:
    Menu() {
        constructFileNames();
        if (fileNames.size() == 0) {
            throw std::runtime_error("Error: There are no JSON files in the directory");
        }
    }

    static void clear();

    static void waitForEnter();

    SchedulingResults scheduleBruteForce(const std::string& fileName) const;

    void outputSchedulingResults(const SchedulingResults& results);

    void display() const;

    void constructFileNames();

    const std::string& getFileNameByIndex(int index) const;

    int interact() const;
};









