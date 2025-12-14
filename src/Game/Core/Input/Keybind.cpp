#include "Keybind.h"

Keybind::Keybind(App::Key key)
    : m_inputType(INPUT_KEYBOARD)
    , m_key(key)
{
}

Keybind::Keybind(App::GamepadButton button, bool isPressed)
    : m_inputType(INPUT_CONTROLLER_BUTTON)
    , m_button(button)
    , m_isPressed(isPressed)
{
}

Keybind::Keybind(int mouseButton)
    : m_inputType(INPUT_MOUSE)
    , m_mouseButton(mouseButton)
{
}

Keybind::Keybind(JoystickAxis axis, float min, float max)
    : m_inputType(INPUT_CONTROLLER_JOYSTICK)
    , m_joystickAxis(axis)
    , m_min(min)
    , m_max(max)
{
}

Keybind::Keybind(TriggerType trigger, float min, float max)
    : m_inputType(INPUT_CONTROLLER_TRIGGER)
    , m_trigger(trigger)
    , m_min(min)
    , m_max(max)
{
}

InputType Keybind::GetInputType() const
{
    return m_inputType;
}

App::Key Keybind::GetKey() const
{
    return m_key;
}

App::GamepadButton Keybind::GetButton() const
{
    return m_button;
}

bool Keybind::IsPressed() const
{
    return m_isPressed;
}

int Keybind::GetMouseButton() const
{
    return m_mouseButton;
}

JoystickAxis Keybind::GetJoystickAxis() const
{
    return m_joystickAxis;
}

TriggerType Keybind::GetTrigger() const
{
    return m_trigger;
}

float Keybind::GetMin() const
{
    return m_min;
}

float Keybind::GetMax() const
{
    return m_max;
}