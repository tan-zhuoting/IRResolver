#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>
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

void MainWindow::find_and_show(int value)
{
    ui->listWidget->clear();
    if (irr == nullptr) {
        return;
    }
    auto recs = irr->find_records(value);
    for (const auto& r : recs) {
        auto item = new QListWidgetItem(r->c_str(), ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->spinBox->setValue(value);
    find_and_show(value);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->horizontalSlider->setValue(arg1);
    find_and_show(arg1);
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
    ui->listWidget->clear();
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
