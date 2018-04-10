#ifndef __ARDUINO_DEBOUNCED_SWITCH
#define __ARDUINO_DEBOUNCED_SWITCH

#include "Arduino.h"

#ifndef DEBOUNCED_SWITCH_DEBOUNCE_INTERVAL
#define DEBOUNCED_SWITCH_DEBOUNCE_INTERVAL 10
#endif

typedef void (*SwitchCallback)();

class DebouncedSwitch {
    public:
        DebouncedSwitch(byte pin_number, uint8_t pin_mode);
        DebouncedSwitch(byte pin_number, uint8_t pin_mode, uint8_t closed_state);

        void attachOnSwitchCloseCallback(SwitchCallback callback);
        void attachOnSwitchOpenCallback(SwitchCallback callback);

        void update();

        bool closed;

    private:
        byte _pin_number;

        SwitchCallback _on_switch_close_callback;
        SwitchCallback _on_switch_open_callback;

        unsigned long _first_trigger;

        uint8_t _closed_state;

        void _init(uint8_t pin_number, uint8_t pin_mode);
};

#endif
