#ifndef ABCPROJECT5_RECEPTIONIST_H
#define ABCPROJECT5_RECEPTIONIST_H

#include "ConveyorWorker.h"
#include "Doctor.h"

#include <vector>
#include <random>

// Класс распределяющего врача.
class Receptionist : public ConveyorWorker {
private:
    std::vector<Doctor *> doctors_;

protected:
    virtual void makeActionWithQueuePerson() override;

    Doctor *getRandomDoctor();

    void checkOnePatient();

public:
    Receptionist(std::string name, std::vector<Doctor *> doctors);

    static Receptionist *getBestReceptionist(std::vector<Receptionist *> receptionists);

    virtual ~Receptionist() {}
};

#endif //ABCPROJECT5_RECEPTIONIST_H
