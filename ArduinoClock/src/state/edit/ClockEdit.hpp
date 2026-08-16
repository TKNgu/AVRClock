#ifndef CLOCKEDIT2_HPP
#define CLOCKEDIT2_HPP

#include "../../button/Button.hpp"
#include "../State.hpp"

class ClockEdit : public ClockState {
  public:
    virtual void reload() override;
    virtual void loop(unsigned long) override;

    virtual void displayBlinkFrame() = 0;
    virtual void increaseValue(unsigned char step) = 0;
    virtual void decreaseValue(unsigned char step) = 0;

  protected:
    void resetView(unsigned long);

    inline static Timer autoSaveTimer_ = Timer(CreateTimer(5000));
    inline static Timer longPressTimer_ = Timer(CreateTimer(500));
    inline static Button buttonUp_ = Button(Key::KeyUp);
    inline static Button buttonDown_ = Button(Key::KeyDown);

    bool isValueChanged_ = true;
};

#endif // CLOCKEDIT2_HPP
