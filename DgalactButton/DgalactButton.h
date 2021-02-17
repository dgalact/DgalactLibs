#ifndef DgalactButton_h
#define DgalactButton_h
#include <Arduino.h>

class DButton
{
public:
    DButton(uint8_t BUTT);
    void setDebounce(uint8_t debounce);
    void setTimeout(uint16_t timeout);
    void tick();

    boolean isPress();
    boolean isRelease();
    boolean isHolded();
    boolean isHold();
    boolean hasClics();
    boolean isSingle();
    boolean isDouble();
    boolean isTriple();
    uint8_t getClics();

private:
    uint8_t _BUTT;
    uint8_t _debounce;
    uint16_t _timeout;
    uint8_t btn_counter, last_counter;
    boolean btn_state, btn_flag, hold_flag, counter_flag;
    uint32_t btn_timer;
    boolean isHold_f, isHolded_f, isRelease_f, isPress_f;
};

#endif