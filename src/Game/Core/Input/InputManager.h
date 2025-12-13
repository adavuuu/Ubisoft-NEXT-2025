//-----------------------------------------------------------------------------
// InputManager.h
// Manages input from the user.
//-----------------------------------------------------------------------------

#pragma once

#include <unordered_map>

#include "app.h"

#include "Keybind.h"

// Action defines in game actions from the player's perspective
enum Action {
    ACTION_INVALID,
    ACTION_MOVE_FORWARD,
    ACTION_MOVE_BACKWARD,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
    ACTION_SELECT,
    ACTION_STOP,
    ACTION_PLAY,
    ACTION_PAUSE,
    ACTION_SCALE_UP,
    ACTION_SCALE_DOWN,
    ACTION_ROTATE_LEFT,
    ACTION_ROTATE_RIGHT,
    // Add more actions as needed
};

class InputManager
{
public:

    InputManager();
    ~InputManager() = default;

    bool Init();
    void Shutdown();

    void BindActionToInput(Action action, App::Key key);
    void BindActionToInput(Action action, App::GamepadButton controllerButton, bool isPressed);
    void BindActionToInput(Action action, int mouseButton);
    void BindActionToInput(Action action, JoystickAxis axis, float min, float max);
    void BindActionToInput(Action action, TriggerType, float min, float max);

    bool IsActionInputted(Action action) const;

    static float GetMousePosX();
    static float GetMousePosY();



private:
    std::unordered_map<Action, std::vector<Keybind>> m_keybinds;
};