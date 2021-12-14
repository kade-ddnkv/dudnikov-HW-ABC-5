#ifndef ABCPROJECT5_CONVEYORWORKER_H
#define ABCPROJECT5_CONVEYORWORKER_H

#include <string>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <iostream>

#include "Person.h"
#include "Work.h"

// Класс работника конвейера.
class ConveyorWorker {

    // Для доступа к protected полям.

    friend class Doctor;

    friend class Receptionist;

protected:
    std::string name_;
    std::queue<Person> queue_;
    std::chrono::milliseconds reception_time_;
    std::mutex queue_mutex_;
    std::condition_variable person_in_queue_;

    std::thread corresponding_thread_;

    // Абстрактный метод, переопределяемый любым наследником.
    virtual void makeActionWithQueuePerson() = 0;

public:
    explicit ConveyorWorker(const std::string &name);

    void addToQueue(const Person &person);

    void run();

    void finishWork();

    std::thread &getThread();

    virtual ~ConveyorWorker() {}
};


#endif //ABCPROJECT5_CONVEYORWORKER_H
