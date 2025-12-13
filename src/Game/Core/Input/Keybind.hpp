//-----------------------------------------------------------------------------
// Keybind.hpp
// Represents an input binding used to trigger an action
//-----------------------------------------------------------------------------

#pragma once

#include "app.h"

// InputType defines which input source is used in a keybind
enum InputType {
    INPUT_INVALID,
    INPUT_KEYBOARD,
    INPUT_MOUSE,
    INPUT_CONTROLLER_JOYSTICK,
    INPUT_CONTROLLER_TRIGGER,
    INPUT_CONTROLLER_BUTTON,
};

// JoystickAxis defines the left/right joysticks and their X/Y axes
enum JoystickAxis {
    JOYSTICK_AXIS_INVALID,
    JOYSTICK_AXIS_LEFT_X,
    JOYSTICK_AXIS_LEFT_Y,
    JOYSTICK_AXIS_RIGHT_X,
    JOYSTICK_AXIS_RIGHT_Y,
};

// TriggerType defines the left/right triggers on a controller
enum TriggerType {
    TRIGGER_INVALID,
    TRIGGER_LEFT,
    TRIGGER_RIGHT,
};

class Keybind {
public:

    Keybind(App::Key key);
    Keybind(App::GamepadButton button, bool isHeld);
    Keybind(int mouseButton);
    Keybind(JoystickAxis axis, float min, float max);
    Keybind(TriggerType trigger, float min, float max);

    InputType GetInputType() const;
    App::Key GetKey() const;
    App::GamepadButton GetButton() const;
    bool IsPressed() const;
    int GetMouseButton() const;
    JoystickAxis GetJoystickAxis() const;
    TriggerType GetTrigger() const;
    float GetMin() const;
    float GetMax() const;

private:
    InputType m_inputType;

    // One of these is defined based on m_inputType
    App::Key m_key;
    App::GamepadButton m_button;
    int m_mouseButton; // GLUT Constants
    JoystickAxis m_joystickAxis;
    TriggerType m_trigger;

    // For GamepadButton, also have the option to press or hold
    bool m_isPressed = false;

    // For controller joystick and trigger, also have min/max values
    float m_min = 0.0f;
    float m_max = 0.0f;
};
