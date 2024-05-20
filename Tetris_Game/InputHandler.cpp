#include "InputHandler.h"
#include "conio.h"

void InputHandler::input_User(int& blockPosX, int& blockPosY, bool& rotate, bool& drop)
{
    int nKey = 0;

    if (_kbhit() > 0)
    {
        nKey = _getch();

        switch (nKey)
        {
        case eKeyCode::KEY_UP:
            break;
        case eKeyCode::KEY_DOWN:
            blockPosY++;
            break;
        case eKeyCode::KEY_LEFT:
            blockPosX--;
            break;
        case eKeyCode::KEY_RIGHT:
            blockPosX++;
            break;
        case eKeyCode::KEY_R:
            rotate = true;
            break;
        case eKeyCode::KEY_SPACE:
            drop = true;
            break;
        }
    }
}
