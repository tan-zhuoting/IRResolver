#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <memory>
#include "IRResolver.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

    void on_actionLoad_triggered();

    void on_actionQuit_triggered();

private:
    void find_and_show(int value);
    Ui::MainWindow *ui;

    std::shared_ptr<IRResolver> irr;
};

#endif // MAINWINDOW_H
