#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJSEngine>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digit_pressed();
    void on_pushButton_decimal_released();
    void unary_operation_pressed();
    void on_pushButton_clear_released();
    void on_pushButton_equals_released();
    void binary_operation_pressed();
    void brakets_pressed();
    void trigonometric_functions_pressed();
    void root_pressed();
    void power_pressed();
    void logarithm_pressed();
    void mathematical_constants_pressed();
    void radians_degrees_pressed();
    void inverse_pressed();
    void factorial_pressed();
    QJSValue calculation();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
