#include <iostream>
#include <thread>
#include <string>

#include "Receptionist.h"

// Метод выводит сообщение о некорректной команде.
void printErrorIncorrectInput() {
    std::cout << "error! allowed commands:\n"
              << "\t+ (add one patient to queue)\n"
              << "\t+5 (non-negative number)\n"
              << "\t- (stop execution)\n";
}

// Метод проверяет входную строку на корректность.
// Возвращает введенное число, если введена строка типа "+" или "+5".
// Возвращает -1 при некорректных данных.
int parseInput(std::string input) {
    if (input == "+") {
        return 1;
    } else if (input[0] == '+') {
        try {
            int result = stoul(input.substr(1, input.size() - 1));
            return result == 0 ? -1 : result;
        } catch (const std::invalid_argument &ex) {
            return -1;
        }
    }
    return -1;
}

// Основной метод для обработки команд пользователя.
// Команды вводятся через консоль.
void handleInput(std::vector<Receptionist *> receptionists) {
    std::cout << "input start\n";
    // Один пациент-болванка, чтобы показать работу программы.
    // В реальной программе таких пациентов может быть несколько.
    Person p;

    std::string input;
    std::cin >> input;
    int number_of_patients;
    while (input != "-") {
        number_of_patients = parseInput(input);
        if (number_of_patients == -1) {
            printErrorIncorrectInput();
        } else {
            // Если введена корректная команда,
            // то выбрать наименьшую очередь
            // и добавить в нее пациента.
            for (int i = 0; i < number_of_patients; ++i) {
                auto best = Receptionist::getBestReceptionist(receptionists);
                best->addToQueue(p);
            }
        }
        std::cin >> input;
    }
    // Как только был введен символ "-", работа больницы должна закончится.
    Work::work_is_finished = true;

    std::cout << "input finished\n";
}

// Метод, создающий докторов по условию задачи.
std::vector<Doctor *> createDoctors() {
    auto surgeon = new Doctor("surgeon");
    auto dentist = new Doctor("dentist");
    auto therapist = new Doctor("therapist");
    std::vector<Doctor *> doctors{surgeon, dentist, therapist};
    return doctors;
}

// Метод, создающий распределяющих врачей по условию задачи.
std::vector<Receptionist *> createReceptionists(std::vector<Doctor *> doctors) {
    auto operator1 = new Receptionist("operator1", doctors);
    auto operator2 = new Receptionist("operator2", doctors);
    std::vector<Receptionist *> receptionists{operator1, operator2};
    return receptionists;
}

// Основная логика программы.
int main() {
    // Создаются доктора и распределяющие врачи.
    // Потоки запускаются автоматически в их конструкторах.
    auto doctors = createDoctors();
    auto receptionists = createReceptionists(doctors);

    // Поток для обработки команд пользователя.
    std::thread generating_thread(handleInput, receptionists);
    generating_thread.join();

    // После окончания работы нужно уведомить не закончивших работать врачей.
    // Подождать окончания всех потоков.
    for (auto &doctor: doctors) {
        doctor->finishWork();
        doctor->getThread().join();
    }
    for (auto &receptionist: receptionists) {
        receptionist->finishWork();
        receptionist->getThread().join();
    }

    std::cout << "program finished\n";

    for (auto &doctor: doctors) {
        delete doctor;
    }
    for (auto &receptionist: receptionists) {
        delete receptionist;
    }
    return 0;
}
