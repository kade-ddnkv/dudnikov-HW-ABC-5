#include "Doctor.h"

// Переопределение действия работника конвейера.
void Doctor::makeActionWithQueuePerson() {
    cureOnePatient();
}

// Вылечивает первого пациента из очереди.
void Doctor::cureOnePatient() {
    // Из заблокированной очереди достается пациент.
    queue_mutex_.lock();
    std::cout << name_ + " took a patient\n";
    queue_.pop();
    queue_mutex_.unlock();

    // Пока доктор выполняет работу, в очередь могут добавляться новые пациенты.
    std::this_thread::sleep_for(reception_time_);
}

Doctor::Doctor(std::string name) : ConveyorWorker(name) {
    // Время работы врача условно.
    reception_time_ = std::chrono::milliseconds(3000);
    // Автоматический запуск потока.
    corresponding_thread_ = std::thread(&Doctor::run, this);
}
