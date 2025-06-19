#include "Menu.h"

#include <iostream>


std::vector<std::string> Menu::getFilesInfo() const {
    std::vector<std::string> result;
    result.reserve(fileNames.size());
    for (const auto& fileName : fileNames) {
        std::string filePath = dirPath + fileName;
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Error: Could not open file: " + filePath + " to read info.");
        }
        nlohmann::json jsonObject;
        file >> jsonObject;
        int coursesCount = jsonObject["courses"].size();
        int instructrosCount = jsonObject["instructors"].size();
        int timeSlotsCount = jsonObject["timeSlots"].size();
        std::string fileInfo = "Courses: " + std::to_string(coursesCount) +
                               ", instructors: " + std::to_string(instructrosCount) +
                               ", timeSlots: " + std::to_string(timeSlotsCount);
        result.push_back(fileInfo);
        file.close();
    }
    return result;
}

void Menu::clear() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux, macOS
    #endif
}

void Menu::waitForEnter() {
    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Menu::display() const {
    Menu::clear();
    std::vector<std::string> filesInfo = getFilesInfo(); // can throw
    std::cout << "Choose the file you want to schedule (located in the 'resources' directory)." << "\n\n";
    for (int i = 0; i < fileNames.size(); i++) {
        std::cout << i+1 << ") " << fileNames[i] << "\n";
        std::cout << filesInfo[i] << "\n\n";
    }
}

void Menu::constructFileNames() {
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            fileNames.push_back(entry.path().filename());
        }
    }
}

const std::string & Menu::getFileNameByIndex(int index) const {
    if (index > fileNames.size() || index <= 0) {
        throw std::out_of_range("Error: File index out of range");
    }
    return fileNames[index-1];
}

int Menu::chooseOption() const {
    if (fileNames.size() == 0) {
        throw std::runtime_error("Error: There are no JSON files in the resources directory");
    }

    std::cout << "Choose number in range [1, " << fileNames.size() << "] (or 0 if you want to exit): ";
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again: ";
            continue;
        }
        if (choice < 0 || choice > fileNames.size()) {
            std::cout << "Invalid input. Try again: ";
            continue;
        }
        break;
    }
    return choice;
}

int Menu::chooseScheduler() const {
    Menu::clear();
    std::cout << "Choose Scheduler.\n\n";
    std::cout << "1) Brute Force Scheduler.\n";
    std::cout << "2) Dummy Scheduler.\n\n";
    std::cout << "Input option: ";

    int choice{-1};
    std::cin >> choice;
    if (choice == 1) {
        return 1;
    } else if (choice == 2) {
        return 2;
    }
    std::cerr << "Invalid input.\n";
    return -1;
}