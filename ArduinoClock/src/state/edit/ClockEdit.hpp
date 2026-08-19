#ifndef CLOCKEDIT2_HPP
#define CLOCKEDIT2_HPP

#include "../../button/Button.hpp"
#include "../State.hpp"

class ClockEdit : public ClockState {
  public:
    virtual void reload() override;
    virtual void loop(unsigned long) override;

    virtual void displayBlinkFrame() = 0;
    virtual void increaseValue(unsigned char) = 0;
    virtual void decreaseValue(unsigned char) = 0;

  protected:
    inline static Timer autoSaveTimer = Timer(CreateTimer(5000));
    inline static Timer longPressTimer = Timer(CreateTimer(500));
    inline static Button buttonUp = Button(Key::KeyUp);
    inline static Button buttonDown = Button(Key::KeyDown);

  private:
    void resetView(unsigned long);
};

#endif // CLOCKEDIT2_HPP
