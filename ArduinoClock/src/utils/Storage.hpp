#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "../clock/LightController.hpp"

class Storage {
  public:
    void loadLight(MovingMaxFilter* const);
    void saveLightIndex(unsigned);
    void saveLightValue(unsigned, unsigned);

    float getWDTScale();
    void saveWDTScale(float);
};

extern Storage storage;

#endif // STORAGE_HPP
