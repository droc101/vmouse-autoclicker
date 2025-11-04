# vmouse-autclicker
A Linux autoclicker that works on X11 and Wayland using the [vmouse kernel module](https://github.com/droc101/vmouse). Designed for the KDE desktop environment.

This program also contains a C++ interface for the vmouse device file.

## vmouse permissions
By default, the vmouse device file requires root permissions to use. If you are unable to run this program as root, you may set the paramater `allow_non_root_write` to `1` on the `hid_vmouse` kernel module.
