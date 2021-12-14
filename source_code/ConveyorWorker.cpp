#include "ConveyorWorker.h"

/*
 * Информация об используемых классах:
 * https://en.cppreference.com/w/cpp/thread/mutex
 * https://en.cppreference.com/w/cpp/thread/condition_variable
 * https://en.cppreference.com/w/cpp/thread/unique_lock
 */

ConveyorWorker::ConveyorWorker(const std::string &name) {
    name_ = name;
}

// Добавляет пациента в очередь.
void ConveyorWorker::addToQueue(const Person &person) {
    queue_mutex_.lock();
    queue_.push(person);
    queue_mutex_.unlock();
    // После добавления уведомляет врача.
    person_in_queue_.notify_one();
}

// Метод, помещаемый в поток.
void ConveyorWorker::run() {
    // Пока работа не закончена...
    while (!Work::work_is_finished) {
        // Если очередь пуста, то поток помещается в состояние ожидания.
        if (queue_.empty()) {
            std::cout << name_ + " is waiting\n";
            std::unique_lock<std::mutex> lk(queue_mutex_);
            person_in_queue_.wait(lk);
            lk.unlock();
        }
        // За время ожидания рабочий день мог закончиться,
        // поэтому стоит проверка.
        if (Work::work_is_finished) {
            break;
        }
        // Работник конвейера совершает действие.
        makeActionWithQueuePerson();
    }
    std::cout << name_ + " finished working\n";
}

// Завершает работу работника.
// На деле просто уведомляет работника, если тот застыл в ожидании.
// Причем поток могу уже закончить свою работу.
void ConveyorWorker::finishWork() {
    person_in_queue_.notify_one();
}

// Метод для получения потока работника.
// Например, для синхронизации с другими потоками.
std::thread &ConveyorWorker::getThread() {
    return corresponding_thread_;
}