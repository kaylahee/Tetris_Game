enum eKeyCode
{
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
    KEY_R = 114,
    KEY_SPACE = 32,
    KEY_H = 104,
};

#pragma once
class InputHandler
{
public:
    void input_User(int& blockPosX, int& blockPosY, bool& rotate, bool& drop);
};

