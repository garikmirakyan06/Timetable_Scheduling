#include "BruteForceScheduler.h"
#include "DummyScheduler.h"
#include "Menu.h"
#include "SchedulerContext.h"


int main() {
    while (true) {
        try {
            Menu menu;

            menu.display();

            int fileChoice = menu.chooseOption();
            if (fileChoice == 0) {
                break;
            }
            std::string fileName = menu.getFileNameByIndex(fileChoice);
            University university;
            university.loadState(menu.getDirPath() + fileName);

            int schedulerChoice = menu.chooseScheduler();
            if (schedulerChoice == -1) {
                return 0;
            }
            Timer timer;
            std::unique_ptr<IScheduler> scheduler{nullptr};
            if (schedulerChoice == 1) {
                scheduler = std::make_unique<BruteForceScheduler>(university);
            } else if (schedulerChoice == 2) {
                scheduler = std::make_unique<DummyScheduler>(university);
            }
            SchedulerContext schedulerContext(std::move(scheduler));
            std::cout << "\nProcessing...\n\n";
            std::vector<TimeTable> timeTables = schedulerContext.schedule();
            double timeTaken = timer.getDuration();
            schedulerContext.displaySchedulingResults(timeTables, timeTaken);

        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << "\n";
            break;
        } catch (const std::out_of_range& e) {
            std::cerr << e.what() << "\n";
            break;
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
            break;
        }
    }

    return 0;
}
