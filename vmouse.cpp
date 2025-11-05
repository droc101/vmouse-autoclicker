// Copyright (c) 2025 droc101
// GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)

#include "vmouse.h"

vmouse::~vmouse() {
    if (device) {
        fclose(device);
    }
}

bool vmouse::open() {
    device = fopen("/dev/vmouse", "wb");
    return device != nullptr;
}

void vmouse::command(VCommand cmd, VButton pld) {
    uint8_t c = static_cast<uint8_t>(cmd) & 0b1111;
    uint8_t p = static_cast<uint8_t>(pld) & 0b111;
    uint8_t combined = (c << 4) | p;
    fwrite(&combined, 1, 1, device);
    fflush(device);
}

void vmouse::reset() {
    command(VCommand::CMD_RESET, VButton::BTN_LEFT);
}

void vmouse::press(VButton btn) {
    command(VCommand::CMD_DOWN, btn);
}

void vmouse::release(VButton btn) {
    command(VCommand::CMD_UP, btn);
}

void vmouse::click(VButton btn) {
    command(VCommand::CMD_CLICK, btn);
}
