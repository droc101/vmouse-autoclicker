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
    vmouse mouse{};
    bool enabled = false;
    vmouse::VButton button;
    QTimer timer{};

    void exitClicked();

    void toggle();

    void timeout();
};
#endif // MAINWINDOW_H
