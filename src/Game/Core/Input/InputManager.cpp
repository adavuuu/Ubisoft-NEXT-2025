#include "InputManager.h"

#include "Keybind.h"

InputManager::InputManager()
{
}

bool InputManager::Init()
{
    // Define default keybindings
    BindActionToInput(ACTION_MOVE_FORWARD, App::KEY_W);
    BindActionToInput(ACTION_MOVE_BACKWARD, App::KEY_S);
    BindActionToInput(ACTION_MOVE_LEFT, App::KEY_A);
    BindActionToInput(ACTION_MOVE_RIGHT, App::KEY_D);
    BindActionToInput(ACTION_MOVE_FORWARD, JOYSTICK_AXIS_LEFT_Y, 0.5f, 1.0f);
    BindActionToInput(ACTION_MOVE_BACKWARD, JOYSTICK_AXIS_LEFT_Y, -1.0f, -0.5f);
    BindActionToInput(ACTION_MOVE_RIGHT, JOYSTICK_AXIS_LEFT_X, 0.5f, 1.0f);
    BindActionToInput(ACTION_MOVE_LEFT, JOYSTICK_AXIS_LEFT_X, -1.0f, -0.5f);
    BindActionToInput(ACTION_SELECT, GLUT_LEFT_BUTTON);
    BindActionToInput(ACTION_STOP, App::BTN_A, true);
    BindActionToInput(ACTION_PLAY, App::BTN_B, true);
    BindActionToInput(ACTION_PAUSE, App::BTN_X, true);
    BindActionToInput(ACTION_SCALE_UP, App::BTN_DPAD_UP, false);
    BindActionToInput(ACTION_SCALE_DOWN, App::BTN_DPAD_DOWN, false);
    BindActionToInput(ACTION_ROTATE_LEFT, App::BTN_DPAD_LEFT, false);
    BindActionToInput(ACTION_ROTATE_RIGHT, App::BTN_DPAD_RIGHT, false);

    return true;
}

void InputManager::Shutdown()
{
    m_keybinds.clear();
}

void InputManager::BindActionToInput(Action action, App::Key key)
{
    m_keybinds[action].emplace_back(key);
}

void InputManager::BindActionToInput(Action action, App::GamepadButton button, bool isPressed)
{
    m_keybinds[action].emplace_back(button, isPressed);
}

void InputManager::BindActionToInput(Action action, int mouseButton)
{
    m_keybinds[action].emplace_back(mouseButton);
}

void InputManager::BindActionToInput(Action action, JoystickAxis axis, float min, float max)
{
    m_keybinds[action].emplace_back(axis, min, max);
}

void InputManager::BindActionToInput(Action action, TriggerType trigger, float min, float max)
{
    m_keybinds[action].emplace_back(trigger, min, max);
}

bool InputManager::IsActionInputted(Action action) const
{
    if (m_keybinds.find(action) != m_keybinds.end())
    {
        for (const Keybind& keybind : m_keybinds.at(action))
        {
            if (keybind.GetInputType() == INPUT_KEYBOARD && App::IsKeyPressed(keybind.GetKey()))
            {
                return true;
            }

            if (keybind.GetInputType() == INPUT_CONTROLLER_BUTTON
                && App::GetController().CheckButton(keybind.GetButton(), keybind.IsPressed()))
            {
                return true;
            }

            if (keybind.GetInputType() == INPUT_MOUSE && App::IsMousePressed(keybind.GetMouseButton()))
            {
                return true;
            }

            if (keybind.GetInputType() == INPUT_CONTROLLER_JOYSTICK)
            {
                float value = 0.0f;
                switch (keybind.GetJoystickAxis())
                {
                    case JOYSTICK_AXIS_LEFT_X:
                        value = App::GetController().GetLeftThumbStickX();
                        break;
                    case JOYSTICK_AXIS_LEFT_Y:
                        value = App::GetController().GetLeftThumbStickY();
                        break;
                    case JOYSTICK_AXIS_RIGHT_X:
                        value = App::GetController().GetRightThumbStickX();
                        break;
                    case JOYSTICK_AXIS_RIGHT_Y:
                        value = App::GetController().GetRightThumbStickY();
                        break;
                    default:
                        break;
                }

                if (value >= keybind.GetMin() && value <= keybind.GetMax())
                {
                    return true;
                }
            }

            if (keybind.GetInputType() == INPUT_CONTROLLER_TRIGGER)
            {
                float value = 0.0f;
                switch (keybind.GetTrigger())
                {
                    case TRIGGER_LEFT:
                        value = App::GetController().GetLeftTrigger();
                        break;
                    case TRIGGER_RIGHT:
                        value = App::GetController().GetRightTrigger();
                        break;
                    default:
                        break;
                }

                if (value >= keybind.GetMin() && value <= keybind.GetMax())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

float InputManager::GetMousePosX()
{
    float x, y;
    App::GetMousePos(x, y);
    return x;
}

float InputManager::GetMousePosY()
{
    float x, y;
    App::GetMousePos(x, y);
    return glutGet(GLUT_WINDOW_HEIGHT) - y;
}

