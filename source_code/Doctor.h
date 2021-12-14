#ifndef ABCPROJECT5_DOCTOR_H
#define ABCPROJECT5_DOCTOR_H

#include <iostream>
#include "ConveyorWorker.h"

// Класс лечащего врача.
class Doctor : public ConveyorWorker {

protected:
    virtual void makeActionWithQueuePerson() override;

    void cureOnePatient();

public:
    Doctor(std::string name);

    virtual ~Doctor() {}
};


#endif //ABCPROJECT5_DOCTOR_H
