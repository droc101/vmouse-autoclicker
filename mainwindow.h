// Copyright (c) 2025 droc101
// GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vmouse.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /// The vmouse device interface
    vmouse mouse{};

    /// Whether the program is currently autoclicing
    bool enabled = false;
    /// What button the program is autoclicking
    vmouse::VButton button;
    /// The number of clicks per iteration
    int numClicks = 1;
    /// The number of times to click, -1 to go until stopped manually
    int numRepeats = -1;

    /// The autoclick timer
    QTimer timer{};

    /// Start or stop autoclicking
    void toggle();

    void timeout();
    void repeatCountChanged(int newValue);
};
#endif // MAINWINDOW_H
