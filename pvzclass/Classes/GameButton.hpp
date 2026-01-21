#include "../PVZ.h"

namespace PVZ {
    class PVZApp;
    class Board;
    class GameButton : PVZ::BaseClass
    {
    public:
        GameButton(int address) : PVZ::BaseClass(address) {};
        GameButton() : PVZ::BaseClass(INVALID_BASEADDRESS) {};

        INT_PROPERTY(mX, __get_mX, __set_mX, 0x8);
        INT_PROPERTY(mY, __get_mY, __set_mY, 0xC);
        INT_PROPERTY(mWidth, __get_mWidth, __set_mWidth, 0x10);
        INT_PROPERTY(mHeight, __get_mHeight, __set_mHeight, 0x14);
        T_PROPERTY(BOOL, mDisabled, __get_Disabled, __set_Disabled, 0x1A);
        INT_PROPERTY(mId, __get_mId, __set_mId, 0x7C);
        PVZApp GetPVZApp();
        Widget GetParentWidget();
        PVZString GetLabel();
    };
}