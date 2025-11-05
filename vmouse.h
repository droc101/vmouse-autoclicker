// Copyright (c) 2025 droc101
// GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)

#ifndef VMOUSE_H
#define VMOUSE_H

#include <cstdio>
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

    /**
     * @brief Open the vmouse device file. This must be called before any other function.
     * @return Whether the vmouse device was opened. If this returns false, do not use the vmouse.
     */
    bool open();

    /**
     * @brief Release all mouse buttons
     */
    void reset();

    /**
     * @brief Press a mouse button (start holding it down)
     * @param btn The button to press
     */
    void press(VButton btn);

    /**
     * @brief Release a mouse button (stop holding it down)
     * @param btn The button to release
     */
    void release(VButton btn);

    /**
     * @brief Click a button (quickly press and release it)
     * @param btn The button to click
     */
    void click(VButton btn);
private:
    FILE *device = nullptr;

    enum class VCommand: uint8_t {
        CMD_RESET = 0,
        CMD_DOWN = 1,
        CMD_UP = 2,
        CMD_CLICK = 3,
    };

    /**
     * @brief Send a command to the vmouse device
     * @param cmd The command to send. Only the lower 2 bits are used.
     * @param pld The payload to send. Onlt the lower 6 bits are used.
     */
    void command(VCommand cmd, VButton pld);
};

#endif // VMOUSE_H
