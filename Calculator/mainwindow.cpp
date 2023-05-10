#include <QKeyEvent>
#include <QRegularExpression>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("calculator");

    connect(ui->pushButton_0, &QPushButton::released, this, &MainWindow::digit_pressed);
    connect(ui->pushButton_1, &QPushButton::released, this, &MainWindow::digit_pressed);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::digit_pressed);
    connect(ui->pushButton_3, &QPushButton::released, this, &MainWindow::digit_pressed);
    connect(ui->pushButton_4, &QPushButton::released, this, &MainWindow::digit_pressed);
    connect(ui->pushButton_5, &QPushButton::released, this, &MainWindow::digit_pressed);
    connect(ui->pushButton_6, &QPushButton::released, this, &MainWindow::digit_pressed);
    connect(ui->pushButton_7, &QPushButton::released, this, &MainWindow::digit_pressed);
    connect(ui->pushButton_8, &QPushButton::released, this, &MainWindow::digit_pressed);
    connect(ui->pushButton_9, &QPushButton::released, this, &MainWindow::digit_pressed);

    connect(ui->pushButton_plusMinus, &QPushButton::released, this, &MainWindow::unary_operation_pressed);
    connect(ui->pushButton_percent, &QPushButton::released, this, &MainWindow::unary_operation_pressed);
    ui->pushButton_plusMinus->setCheckable(true);
    ui->pushButton_percent->setCheckable(true);

    connect(ui->pushButton_add, &QPushButton::released, this, &MainWindow::binary_operation_pressed);
    connect(ui->pushButton_subtract, &QPushButton::released, this, &MainWindow::binary_operation_pressed);
    connect(ui->pushButton_multiply, &QPushButton::released, this, &MainWindow::binary_operation_pressed);
    connect(ui->pushButton_divide, &QPushButton::released, this, &MainWindow::binary_operation_pressed);

    connect(ui->pushButton_leftBrackets, &QPushButton::released, this, &MainWindow::brakets_pressed);
    connect(ui->pushButton_rightBrackets, &QPushButton::released, this, &MainWindow::brakets_pressed);

    connect(ui->pushButton_sine, &QPushButton::released, this, &MainWindow::trigonometric_functions_pressed);
    connect(ui->pushButton_cosine, &QPushButton::released, this, &MainWindow::trigonometric_functions_pressed);
    connect(ui->pushButton_tangent, &QPushButton::released, this, &MainWindow::trigonometric_functions_pressed);
    connect(ui->pushButton_cotangent, &QPushButton::released, this, &MainWindow::trigonometric_functions_pressed);
    ui->pushButton_sine->setCheckable(true);
    ui->pushButton_cosine->setCheckable(true);
    ui->pushButton_tangent->setCheckable(true);
    ui->pushButton_cotangent->setCheckable(true);

    connect(ui->pushButton_squareRoot, &QPushButton::released, this, &MainWindow::root_pressed);
    connect(ui->pushButton_cubeRoot, &QPushButton::released, this, &MainWindow::root_pressed);
    connect(ui->pushButton_nthRoot, &QPushButton::released, this, &MainWindow::root_pressed);
    ui->pushButton_squareRoot->setCheckable(true);
    ui->pushButton_cubeRoot->setCheckable(true);
    ui->pushButton_nthRoot->setCheckable(true);

    connect(ui->pushButton_squarePower, &QPushButton::released, this, &MainWindow::power_pressed);
    connect(ui->pushButton_cubePower, &QPushButton::released, this, &MainWindow::power_pressed);
    connect(ui->pushButton_nthPower, &QPushButton::released, this, &MainWindow::power_pressed);
    ui->pushButton_squarePower->setCheckable(true);
    ui->pushButton_cubePower->setCheckable(true);
    ui->pushButton_nthPower->setCheckable(true);

    connect(ui->pushButton_log2, &QPushButton::released, this, &MainWindow::logarithm_pressed);
    connect(ui->pushButton_log10, &QPushButton::released, this, &MainWindow::logarithm_pressed);
    connect(ui->pushButton_log_y, &QPushButton::released, this, &MainWindow::logarithm_pressed);
    ui->pushButton_log2->setCheckable(true);
    ui->pushButton_log10->setCheckable(true);
    ui->pushButton_log_y->setCheckable(true);

    connect(ui->pushButton_number_Pi, &QPushButton::released, this, &MainWindow::mathematical_constants_pressed);
    connect(ui->pushButton_number_e, &QPushButton::released, this, &MainWindow::mathematical_constants_pressed);
    ui->pushButton_number_Pi->setCheckable(true);
    ui->pushButton_number_e->setCheckable(true);

    connect(ui->pushButton_Rad_Deg, &QPushButton::released, this, &MainWindow::radians_degrees_pressed);
    connect(ui->pushButton_inverse, &QPushButton::released, this, &MainWindow::inverse_pressed);
    connect(ui->pushButton_factorial, &QPushButton::released, this, &MainWindow::factorial_pressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

struct OperationData {
   bool isActive = false;
   bool isTypingNext = true;
   double number;

   void clear() {
       isActive = false;
       isTypingNext = true;
       number = 0.0;
   }
};

OperationData ROOT_DATA;
OperationData POWER_DATA;
OperationData LOG_DATA;

bool IN_DEGREES = true;
bool P_M_DIGIT_WRITE = false;
bool DECIMAL_PRESSED = false;
bool EQUALS_PRESSED = false;

void MainWindow::brakets_pressed()
{
    if(ui->label->text() == "0") {
        ui->label->setText("");
    }
    QPushButton* button = (QPushButton*)sender();
    ui->label->setText(ui->label->text() + button->text());
}

void MainWindow::digit_pressed()
{
    QPushButton* button = (QPushButton*)sender();
    if(ui->label->text() == "0" || EQUALS_PRESSED) {
        ui->label->setText("");
    }
    else if (ROOT_DATA.isActive && ROOT_DATA.isTypingNext) {
        ui->label->setText("");
        ROOT_DATA.isTypingNext = false;
    }
    else if (LOG_DATA.isActive && LOG_DATA.isTypingNext) {
        ui->label->setText("");
        LOG_DATA.isTypingNext = false;
    }
    else if (POWER_DATA.isActive && POWER_DATA.isTypingNext) {
        ui->label->setText("");
        POWER_DATA.isTypingNext = false;
    }
    if(P_M_DIGIT_WRITE) {
        ui->label->setText(ui->label->text().insert(ui->label->text().length()-1, button->text()));
    } else {
        ui->label->setText(ui->label->text() + button->text());
    }
    EQUALS_PRESSED = false;
}

void MainWindow::on_pushButton_decimal_released()
{
    if (!DECIMAL_PRESSED && ui->label->text().back().isDigit()) {
        ui->label->setText(ui->label->text() + ".");
        DECIMAL_PRESSED = true;
    }
}

void MainWindow::on_pushButton_clear_released()
{
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_decimal->setChecked(false);
    ui->label->setText("0");
    DECIMAL_PRESSED = false;
    P_M_DIGIT_WRITE = false;
    EQUALS_PRESSED = false;
    POWER_DATA.clear();
    ROOT_DATA.clear();
    LOG_DATA.clear();
}

void MainWindow::on_pushButton_equals_released()
{
    double result = calculation().toNumber();
    if (POWER_DATA.isActive) {
            result = pow(POWER_DATA.number, result);
            POWER_DATA.clear();
    }
    else if(ROOT_DATA.isActive) {
        result = pow(double(ROOT_DATA.number), 1.0/result);
        ROOT_DATA.clear();
    }
    else if (LOG_DATA.isActive) {
        result = std::log(LOG_DATA.number) / std::log(result);
        LOG_DATA.clear();
    }
    EQUALS_PRESSED = true;
    ui->label->setText(QString::number(result));
}

void MainWindow::binary_operation_pressed()
{
    if(DECIMAL_PRESSED) DECIMAL_PRESSED = false;
    if(P_M_DIGIT_WRITE) P_M_DIGIT_WRITE = false;

    if(EQUALS_PRESSED) {
        ui->label->setText("0");
    }
    else if(ui->label->text().endsWith('+') || ui->label->text().endsWith('-') || ui->label->text().endsWith("×") || ui->label->text().endsWith("÷")) {
        QPushButton* button = (QPushButton*)sender();
        auto labelText = ui->label->text();
        labelText.chop(1);
        ui->label->setText(labelText+button->text());
    }
    else {
        QPushButton* button = (QPushButton*)sender();
        auto labelText = ui->label->text() + button->text();
        ui->label->setText(labelText);
    }
    EQUALS_PRESSED = false;
}


void MainWindow::trigonometric_functions_pressed()
{
    QPushButton* button = (QPushButton*)sender();
    button->setChecked(true);
    QJSValue result = calculation();
    double answer = 0;
    if(IN_DEGREES) {
        if(ui->pushButton_sine->isChecked()) {
            answer = std::sin(result.toNumber() * (M_PI / 180));
        }
        else if(ui->pushButton_cosine->isChecked()) {
            answer = std::cos(result.toNumber() * (M_PI / 180));
        }
        else if(ui->pushButton_tangent->isChecked()) {
            answer = std::tan(result.toNumber() * (M_PI / 180));
        }
        else if(ui->pushButton_cotangent->isChecked()) {
            answer = 1 / std::tan(result.toNumber() * (M_PI / 180));
        }
    } else {
        if(ui->pushButton_sine->isChecked()) {
            answer = std::sin(result.toNumber());
        }
        else if(ui->pushButton_cosine->isChecked()) {
            answer = std::cos(result.toNumber());
        }
        else if(ui->pushButton_tangent->isChecked()) {
            answer = std::tan(result.toNumber());
        }
        else if(ui->pushButton_cotangent->isChecked()) {
            answer = 1 / std::tan(result.toNumber());
        }
    }
    ui->label->setText(QString::number(answer));
    button->setChecked(false);
}

void MainWindow::root_pressed()
{
    QPushButton* button = (QPushButton*)sender();
    button->setChecked(true);
    double result = calculation().toNumber();
    if(ui->pushButton_squareRoot->isChecked()) {
        ui->label->setText(QString::number(std::sqrt(result)));
    } else if(ui->pushButton_cubeRoot->isChecked()) {
        ui->label->setText(QString::number(std::cbrt(result)));
    } else if(ui->pushButton_nthRoot->isChecked()) {
        ROOT_DATA.isActive = true;
        ROOT_DATA.number = calculation().toNumber();
    }
    button->setChecked(false);
}

void MainWindow::power_pressed() {
    QPushButton* button = (QPushButton*)sender();
    button->setChecked(true);
    double result = calculation().toNumber();
    if(ui->pushButton_squarePower->isChecked()) {
        ui->label->setText(QString::number(std::pow(result, 2)));
    } else if(ui->pushButton_cubePower->isChecked()) {
        ui->label->setText(QString::number(std::pow(result, 3)));
    } else if(ui->pushButton_nthPower->isChecked()) {
        POWER_DATA.isActive = true;
        POWER_DATA.number = calculation().toNumber();
    }
    button->setChecked(false);
}

void MainWindow::logarithm_pressed() {
    QPushButton* button = (QPushButton*)sender();
    button->setChecked(true);
    QJSValue result = calculation();

    if(ui->pushButton_log2->isChecked()) {
        ui->label->setText(QString::number(std::log2(result.toNumber())));
    }
    else if(ui->pushButton_log10->isChecked()) {
        ui->label->setText(QString::number(std::log10(result.toNumber())));
    }
    else if(ui->pushButton_log_y->isChecked()) {
        LOG_DATA.isActive = true;
        LOG_DATA.number = calculation().toNumber();
    }
    button->setChecked(false);
}

void MainWindow::mathematical_constants_pressed() {
    QPushButton* button = (QPushButton*)sender();
    button->setChecked(true);
    if(ui->label->text() == "0") {
        ui->label->setText("");
    }
    QString math_constant;
    if(ui->pushButton_number_Pi->isChecked()) {
        math_constant = QString::number(M_PI, 'g', 15);
    }
    else if(ui->pushButton_number_e->isChecked()) {
        math_constant = QString::number(M_E, 'g', 15);
    }
    ui->label->setText(ui->label->text() + math_constant);
    button->setChecked(false);
}

void MainWindow::radians_degrees_pressed() {
    QPushButton *button = (QPushButton *) sender();
    if (button->text() == "Rad") {
        IN_DEGREES = false;
        button->setText("Deg");
        ui->label_Rad_Deg->setText("Rad");
    }
    else if (button->text() == "Deg") {
        IN_DEGREES = true;
        button->setText("Rad");
        ui->label_Rad_Deg->setText("");
    }
}

void MainWindow::inverse_pressed() {
    ui->label->setText(QString::number(1 / calculation().toNumber()));
}

void MainWindow::factorial_pressed() {
    double result = calculation().toNumber();
    if (result == std::floor(result)) {
        ui->label->setText(QString::number(std::tgamma(result + 1)));
    }
}

void MainWindow::unary_operation_pressed()
{
    QPushButton* button = (QPushButton*)sender();
    button->setChecked(true);
    QString text = ui->label->text();

    if(ui->pushButton_plusMinus->isChecked()) {
        QRegularExpression re1("\\(-\\d+(\\.\\d+)?\\)$");
        QRegularExpressionMatch match = re1.match(text);
        if(text.toDouble()) {
            ui->label->setText(QString::number(-text.toDouble()));
        }
        else if (text.endsWith("(-)")) {
            text.chop(3);
            ui->label->setText(text);
        }
        else if(match.hasMatch()) {
            QString newText = match.captured(0);
            int pos = text.lastIndexOf(newText);
            QString replacement = newText.mid(2, newText.length() - 3);
            text.replace(pos, newText.length(), replacement);
            ui->label->setText(text);
        }
        else if(text.endsWith('+') || text.endsWith('-') || text.endsWith("×") || text.endsWith("÷")) {
            P_M_DIGIT_WRITE = true;
            ui->label->setText(text + "(-)");
        }
        else {
            QRegularExpression re2("\\d+(\\.\\d+)?");
            int pos = text.lastIndexOf(re2);
            text.insert(pos, "(-");
            text += ")";
            ui->label->setText(text);
            re2 = QRegularExpression();
        }
    }

    else if(ui->pushButton_percent->isChecked()) {
        QStringList parts = text.split(QRegularExpression("(\\+|\\-|\\*|\\/)"));
        if (parts.count() > 1) {
            double operand = parts.last().toDouble();
            double result = parts[parts.count()-2].toDouble() * operand * 0.01;
            parts[parts.count()-2] = QString::number(parts[parts.count()-2].toDouble() - result, 'g', 15);
            QString newText = parts[parts.count()-2];

            QRegularExpression re("(\\d+)(\\s*[+\\-\\*/])\\s*\\d+\\s*$");
            QRegularExpressionMatch match = re.match(text);
            if (match.hasMatch()) {
                text.remove(match.capturedStart(), match.capturedLength());
            }
            ui->label->setText(text + newText);
        } else {
            ui->label->setText(QString::number(text.toDouble() * 0.01, 'g', 15));
        }
    }
    button->setChecked(false);
}

QJSValue MainWindow::calculation()
{
    QJSEngine engine;
    QString expression = ui->label->text();
    expression.replace("×", "*");
    expression.replace("÷", "/");
    return engine.evaluate(expression);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace) {
        QString text = ui->label->text();
        if (!text.isEmpty()) {
            if(text.length() == 1) {
                text = "0";
            }
            else {
                text.chop(1);
            }
        ui->label->setText(text);
        }
    }

    switch (event->key()) {
        case Qt::Key_0:
            ui->pushButton_0->click();
            break;
        case Qt::Key_1:
            ui->pushButton_1->click();
            break;
        case Qt::Key_2:
            ui->pushButton_2->click();
            break;
        case Qt::Key_3:
            ui->pushButton_3->click();
            break;
        case Qt::Key_4:
            ui->pushButton_4->click();
            break;
        case Qt::Key_5:
            ui->pushButton_5->click();
            break;
        case Qt::Key_6:
            ui->pushButton_6->click();
            break;
        case Qt::Key_7:
            ui->pushButton_7->click();
            break;
        case Qt::Key_8:
            ui->pushButton_8->click();
            break;
        case Qt::Key_9:
            ui->pushButton_9->click();
            break;
        case Qt::Key_Plus:
            ui->pushButton_add->click();
            break;
        case Qt::Key_Minus:
            ui->pushButton_subtract->click();
            break;
        case Qt::Key_Asterisk:
            ui->pushButton_multiply->click();
            break;
        case Qt::Key_Slash:
            ui->pushButton_divide->click();
            break;
        case Qt::Key_Percent:
            ui->pushButton_percent->click();
            break;
        case Qt::Key_Return:
            ui->pushButton_equals->click();
            break;
        case Qt::Key_Period:
            ui->pushButton_decimal->click();
            break;
        case Qt::Key_C:
            ui->pushButton_clear->click();
            break;
        case Qt::Key_ParenLeft:
            ui->pushButton_leftBrackets->click();
            break;
        case Qt::Key_ParenRight:
            ui->pushButton_rightBrackets->click();
            break;
        case Qt::Key_P:
            ui->pushButton_number_Pi->click();
            break;
        case Qt::Key_E:
            ui->pushButton_number_e->click();
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
    QMainWindow::keyPressEvent(event);
}
