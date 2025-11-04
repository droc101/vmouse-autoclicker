// Copyright (c) 2025 droc101
// GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)

#ifndef VMOUSE_H
#define VMOUSE_H

#include <cstdio>
#include <cstdbool>
#include <cstdint>

class vmouse
{
public:
    enum class VButton: uint8_t {
        BTN_LEFT,
        BTN_RIGHT,
        BTN_MIDDLE,
        BTN_SIDE,
        BTN_EXTRA,
        BTN_FORWARD,
        BTN_BACK,
        BTN_TASK,
    };

    vmouse() = default;
    ~vmouse();

    bool open();

    void reset();
    void press(VButton btn);
    void release(VButton btn);
    void click(VButton btn);
private:
    FILE *device = nullptr;

    enum class VCommand: uint8_t {
        CMD_RESET,
        CMD_DOWN,
        CMD_UP
    };

    void command(VCommand cmd, VButton pld);
};

#endif // VMOUSE_H
