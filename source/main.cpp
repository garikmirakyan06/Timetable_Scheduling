#include "BruteForceUniversity.h"
#include "Menu.h"


int main() {

    try {
        Menu menu;

        menu.display();

        int choice = menu.interact();
        std::string fileName = menu.getFileNameByIndex(choice);
        std::cout << "\nProcessing...\n\n";
        SchedulingResults schedulingResults = menu.scheduleBruteForce(fileName);
        menu.outputSchedulingResults(schedulingResults);

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}