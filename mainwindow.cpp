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

    ui->clickType->addItem("Single");
    ui->clickType->addItem("Double");
    ui->clickType->addItem("Triple");
    ui->clickType->addItem("Quadruple");

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

    connect(ui->repeatCount, &QSpinBox::valueChanged, this, &MainWindow::repeatCountChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toggle() {
    enabled = !enabled;
    if (enabled) {
        ui->kled->setColor(QColor(0,255,0));
        button = static_cast<vmouse::VButton>(ui->mouseButtonCombo->currentIndex());
        if (ui->repeatForever->isChecked()) {
            numRepeats = -1;
        } else {
            numRepeats = ui->repeatCount->value();
        }
        numClicks = ui->clickType->currentIndex() + 1;
        timer.start(ui->frequencySpinBox->value());
        timeout();
    } else {
        ui->kled->setColor(QColor(255,0,0));
        timer.stop();
    }
    ui->frequencySpinBox->setEnabled(!enabled);
    ui->mouseButtonCombo->setEnabled(!enabled);
    ui->clickType->setEnabled(!enabled);
    ui->repeatCount->setEnabled(!enabled);
    ui->repeatForever->setEnabled(!enabled);
    ui->repeatLimited->setEnabled(!enabled);
}

void MainWindow::timeout() {
    if (enabled) {
        for (int i = 0; i < numClicks; i++) {
            mouse.click(button);
        }

        if (numRepeats != -1) {
            numRepeats--;
            if (numRepeats == 0) {
                toggle();
            }
        }
    }
}

void MainWindow::repeatCountChanged(int newValue) {
    ui->repeatLimited->setChecked(true);
}
