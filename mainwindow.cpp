// Copyright (c) 2025 droc101
// GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <KGlobalAccel>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::exitClicked);

    if (!mouse.open()) {
        QMessageBox::critical(this, "Failed to open vmouse device", "Failed to open the vmouse device. Please ensure you have the requires permissions and the module is loaded.");
        QTimer::singleShot(0, this, SLOT(close()));
    }

    QStringList buttons{};
    buttons.append("Left");
    buttons.append("Right");
    buttons.append("Middle");
    buttons.append("Side");
    buttons.append("Extra");
    buttons.append("Forward");
    buttons.append("Back");
    buttons.append("Task");
    ui->mouseButtonCombo->addItems(buttons);

    QAction *action = new QAction(this);
    action->setText("Toggle VMouse Autoclicker");
    action->setEnabled(true);
    action->setObjectName("action");

    action->connect(action, &QAction::triggered, [this]() {
        this->toggle();
    });

    if (!KGlobalAccel::self()) {
        QMessageBox::critical(this, "Error", "KGlobalAccel is not available in this session.");
    }


    if (!KGlobalAccel::self()->setGlobalShortcut(action, QKeySequence("Alt+Shift+F7"))) {
        QMessageBox::critical(this, "Failed to create shortcut", "Failed to create shortcut");
        QTimer::singleShot(0, this, SLOT(close()));
    }

    timer.setSingleShot(false);
    timer.setTimerType(Qt::PreciseTimer);
    QObject::connect(&timer, &QTimer::timeout, this, &MainWindow::timeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::exitClicked() {
    close();
}

void MainWindow::toggle() {
    enabled = !enabled;
    if (enabled) {
        ui->kled->on();
        button = static_cast<vmouse::VButton>(ui->mouseButtonCombo->currentIndex());
        timer.start(ui->frequencySpinBox->value());
    } else {
        ui->kled->off();
        timer.stop();
    }
    ui->frequencySpinBox->setEnabled(!enabled);
    ui->mouseButtonCombo->setEnabled(!enabled);
}

void MainWindow::timeout() {
    if (enabled) {
        mouse.click(button);
    }
}
