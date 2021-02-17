#include "DgalactButton.h"
#include <Arduino.h>

DButton::DButton(uint8_t BUTT)
{
    _BUTT = BUTT;
    _debounce = 80;
    _timeout = 500;
    pinMode(_BUTT, INPUT_PULLUP);
}

void DButton::setDebounce(uint8_t debounce)
{
    _debounce = debounce;
}
void DButton::setTimeout(uint16_t timeout)
{
    _timeout = timeout;
}

boolean DButton::isPress()
{
    if (isPress_f)
    {
        isPress_f = false;
        return true;
    }
    else
        return false;
}

boolean DButton::isRelease()
{
    if (isRelease_f)
    {
        isRelease_f = false;
        return true;
    }
    else
        return false;
}

boolean DButton::isHolded()
{
    if (isHolded_f)
    {
        isHolded_f = false;
        return true;
    }
    else
        return false;
}

boolean DButton::isHold()
{
    if (isHold_f)
    {
        isHold_f = false;
        return true;
    }
    else
        return false;
}
boolean DButton::isSingle()
{
    if (counter_flag && last_counter == 1)
    {
        counter_flag = false;
        return true;
    }
    else
        return false;
}

boolean DButton::isDouble()
{
    if (counter_flag && last_counter == 2)
    {
        counter_flag = false;
        return true;
    }
    else
        return false;
}
boolean DButton::isTriple()
{
    if (counter_flag && last_counter == 3)
    {
        counter_flag = false;
        return true;
    }
    else
        return false;
}

boolean DButton::hasClics()
{
    if (counter_flag)
    {
        counter_flag = false;
        return true;
    }
    else
        return false;
}

uint8_t DButton::getClics()
{
    return last_counter;
}

void DButton::tick()
{
    btn_state = !digitalRead(_BUTT);
    if (btn_state)
        isHold_f = true;
    else
        isHold_f = false;

    if (btn_state && !btn_flag && (millis() - btn_timer > _debounce))
    {
        btn_flag = true;
        btn_counter++;
        btn_timer = millis();
        isPress_f = true;
    }
    if (!btn_state && btn_flag)
    {
        btn_flag = false;
        hold_flag = false;
        isRelease_f = true;
    }
    if (btn_flag && btn_state && (millis() - btn_timer > _timeout) && !hold_flag)
    {
        hold_flag = true;
        btn_counter = 0;
        isHolded_f = true;
    }
    if ((millis() - btn_timer > _timeout) && (btn_counter != 0))
    {
        last_counter = btn_counter;
        btn_counter = 0;
        counter_flag = true;
    }
}
