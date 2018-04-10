# Arduino Debounced Switch libraray

This is a small and simple library for adding a debounced switch to your project. It can use any available pin and it can handle both active-high and active-low based switches. Active-high means "on" or "closed" is represented by a `HIGH` signal and "off" or "open" is represented by a `LOW` signal.

This library should work with any Arduino-compatible board. Tested on an Arduino Uno clone.

## How to use

Include the header file and create an instance of the `DebouncedSwitch` object. Create a callback function for one or both the open and close events. These functions must be bound to the switch and are called when the switch closes or opens, depending on the set callback.

The example below will turn on the built-in LED the switch is closed and will turn off the built-in LED when the switch is opened again. Note: the update method should be called inside the `loop()` function as it updates the state of the switch.

```
#include <DebouncedSwitch.h>

#define LED_PIN 13

DebouncedSwitch switch(3, INPUT_PULLUP, LOW);

void onSwitchClose () {
    digitalWrite(LED_PIN, HIGH);
}

void onSwitchOpen () {
    digitalWrite(LED_PIN, LOW);
}

void setup () {
    switch.attachOnSwitchCloseCallback(onSwitchClose);
    switch.attachOnSwitchOpenCallback(onSwitchOpen);
}

void loop () {
    switch.update();
}

```

The constructor can be called in two ways. The first one is without the active state defined and the second is with the active state defined. When the active state is not set, it will default to `HIGH`.

```
// Without active state
DebouncedSwitch switch1(3, INPUT);

// With active state, essentially the same as the one above
DebouncedSwitch switch2(3, INPUT, HIGH);

// With active state
DebouncedSwitch switch3(3, INPUT_PULLUP, LOW);
```

Note: When _not_ using the built-in pull-up resistor on a pin, you will need to add a pull-down or pull-up resistor yourself, depending on your type of switch. Most digital signals can be used without any pull-down or pull-up resistors. When using an external pull-down or pull-up resistor, 10K is a good value to start with. For more information on specifically pull-up resistors, see [this Sparkfun page](https://learn.sparkfun.com/tutorials/pull-up-resistors).

|              | active-high              | active-low         |
| ------------ | ------------------------ | ------------------ |
| INPUT        | external pull-down       | external pull-up   |
| INPUT_PULLUP | Invalid state, always on | internal pull-up   |

## API

### `DebouncedSwitch(byte pin_number, uint8_t pin_mode)` constructor

Initialises the `DebounceSwitch` object.

```
DebouncedSwitch switch(3, INPUT);
```

| Argument | Type | Description |
| -------- | :--: | ----------- |
| pin_number | byte    | The pin number of the pin which is connected to the switch. |
| pin_mode   | uint8_t | The pin mode for this pin. `INPUT` or `INPUT_PULLUP`. |

### `DebouncedSwitch(byte pin_number, uint8_t pin_mode, uint8_t closed_state)` constructor

Initialises the `DebounceSwitch` object.

```
DebouncedSwitch switch(3, INPUT_PULLUP, LOW);
```

| Argument | Type | Description |
| -------- | :--: | ----------- |
| pin_number   | byte    | The pin number of the pin which is connected to the switch. |
| pin_mode     | uint8_t | The pin mode for this pin. `INPUT` or `INPUT_PULLUP`. |
| closed_state | uint8_t | The active state for this switch. `HIGH` or `LOW`. |

### `void attachOnSwitchCloseCallback(SwitchCallback callback)` method

Attaches the given callback function to the switch close event. Should be called inside the `setup()` function.

```
switch.attachattachOnSwitchCloseCallback(onSwitchClose);
```

| Argument | Type | Description |
| -------- | :--: | ----------- |
| callback | SwitchCallback | The function to be called when the switch closes. |


### `void attachOnSwitchOpenCallback(SwitchCallback callback)` method

Attaches the given callback function to the switch open event. Should be called inside the `setup()` function.

```
switch.attachOnSwitchOpenCallback(onSwitchOpen);
```

| Argument | Type | Description |
| -------- | :--: | ----------- |
| callback | SwitchCallback | The function to be called when the switch opens. |

### `void update()` method

Updates the state of the switch. Should be called inside the `loop()` function. The callbacks are called inside this function, if applicable.

```
switch.update();
```

### `bool closed` property

Reflects the state of the switch. True if the switch is closed (or pressed). False if the switch is open. Read-only property.
