#include "DebouncedSwitch.h"

void DebouncedSwitch::_init (byte pin_number, uint8_t pin_mode) {
    _pin_number = pin_number;

    pinMode(_pin_number, pin_mode);

    _on_switch_close_callback = NULL;
    _on_switch_open_callback = NULL;

    _first_trigger = 0;

    closed = digitalRead(_pin_number) != _closed_state;
};

DebouncedSwitch::DebouncedSwitch (byte pin_number, uint8_t pin_mode) {
    _closed_state = HIGH;
    _init(pin_number, pin_mode);
};

DebouncedSwitch::DebouncedSwitch (byte pin_number, uint8_t pin_mode, uint8_t closed_state) {
    _closed_state = closed_state;
    _init(pin_number, pin_mode);
};

void DebouncedSwitch::attachOnSwitchCloseCallback (SwitchCallback callback) {
    _on_switch_close_callback = callback;
};

void DebouncedSwitch::attachOnSwitchOpenCallback (SwitchCallback callback) {
    _on_switch_open_callback = callback;
};

void DebouncedSwitch::update () {
    if (closed ?
            digitalRead(_pin_number) == _closed_state :
            digitalRead(_pin_number) != _closed_state
        ) {
        if (!_first_trigger) {
            _first_trigger = millis();
            if (closed) {
                if (_on_switch_open_callback != NULL) {
                    (*_on_switch_open_callback)();
                }
            }
            else {
                if (_on_switch_close_callback != NULL) {
                    (*_on_switch_close_callback)();
                }
            }

        }

        if (millis() - _first_trigger > DEBOUNCED_SWITCH_DEBOUNCE_INTERVAL) {
            closed = !closed;
            _first_trigger = 0;
        }
    }
    else {
        if (millis() - _first_trigger > DEBOUNCED_SWITCH_DEBOUNCE_INTERVAL) {
            _first_trigger = 0;
        }
    }
};
