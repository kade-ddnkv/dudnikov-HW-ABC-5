#include "Receptionist.h"

// Переопределение действия работника конвейера.
void Receptionist::makeActionWithQueuePerson() {
    checkOnePatient();
}

// Получает случайного доктора из списка.
Doctor *Receptionist::getRandomDoctor() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, doctors_.size() - 1);
    return doctors_[dist(rng)];
}

// Распределяющий врач обрабатывает первого пациента из очереди и
// добавляет его в очередь к одному из лечащих врачей.
void Receptionist::checkOnePatient() {
    // Из заблокированной очереди достается пациент.
    queue_mutex_.lock();
    std::cout << name_ + " checks a patient\n";
    Person patient = queue_.front();
    queue_.pop();
    queue_mutex_.unlock();

    // Работа распределяющего врача без блока очереди.
    std::this_thread::sleep_for(reception_time_);
    auto selected_doctor = getRandomDoctor();
    std::cout << name_ + " sends patient to " + selected_doctor->name_ + "\n";
    selected_doctor->addToQueue(patient);
}

Receptionist::Receptionist(std::string name, std::vector<Doctor *> doctors) : ConveyorWorker(name) {
    doctors_ = doctors;
    // Время работы врача условно.
    reception_time_ = std::chrono::milliseconds(600);
    // Автоматический запуск потока.
    corresponding_thread_ = std::thread(&Receptionist::run, this);
}

// Метод, возвращающий распределяющего врача с меньшей очередью.
Receptionist *Receptionist::getBestReceptionist(std::vector<Receptionist *> receptionists) {
    size_t min_queue_size = SIZE_MAX;
    size_t curr_queue_size;
    Receptionist *best;
    for (auto receptionist: receptionists) {
        curr_queue_size = receptionist->queue_.size();
        if (curr_queue_size < min_queue_size) {
            min_queue_size = curr_queue_size;
            best = receptionist;
        }
    }
    return best;
}
