#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->spinBox->setValue(value);
    if (irr == nullptr) {
        return;
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->horizontalSlider->setValue(arg1);
    if (irr == nullptr) {
        return;
    }
}

void MainWindow::on_actionLoad_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open IR Data File", "./", "Data Files (*.txt);;Any Files (*.*)");
    std::fstream ifs;
    ifs.open(filename.toStdString());
    if (!ifs.is_open()) {
        QMessageBox msgbox;
        msgbox.setText(QString("Cannot open file: ").append(filename));
        msgbox.exec();
        return;
    }
    irr = std::make_shared<IRResolver>();
    std::string line;
    while (std::getline(ifs, line)) {
        bool ret = irr->add_record(line);
        if (!ret) {
            QMessageBox msgbox;
            msgbox.setText(QString("parse failed at line :\n").append(line.c_str()).append("\nAborting"));
            msgbox.exec();
            irr = nullptr;
            return;
        }
    }
    QMessageBox msgbox;
    msgbox.setText(QString("File ").append(filename).append(" successfully loaded."));
    msgbox.exec();
}
