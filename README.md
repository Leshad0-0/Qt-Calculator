# GUI Calculator on Qt and C++

## Introduction
This project is a graphical calculator built using C++ and Qt. The calculator supports basic arithmetic operations such as addition, subtraction, multiplication, division, modulo, power, root, logarithm, sine, cosine, tangent, cotangent, factorial, reciprocal, and parentheses. It also supports the use of constants such as pi and e and can calculate in both degrees and radians. The calculator has a clear button to remove all characters from the screen. If you want to remove the last character entered, you need to press the Backspace key. Calculator supports keyboard input.


## Installation
To run this application, Qt and C++ must be installed. Clone this repository, compile the code using your preferred C++ compiler, and run the executable file.


## Usage
The calculator interface is intuitive and easy to use. Buttons for digits, operators, and functions are displayed on the screen, and clicking them will enter the corresponding symbol into the input field. Keyboard input is also supported. You can switch between degrees and radians by clicking on the "Deg" or "Rad" buttons. You can clear the screen by clicking on the "C" button or by pressing the "Backspace" key on your keyboard.


## Screenshot
> **Note:** Screenshots of application were taken on macOS and may appear differently on other operating systems due to differences in user interface design.
<img src=https://github.com/Leshad0-0/Qt-Calculator/blob/main/Screenshots/calculator_dark_theme.png? alt="image" width=75%/>
<img src=https://github.com/Leshad0-0/Qt-Calculator/blob/main/Screenshots/calculator_white_theme.png? alt="image" width=75%/>

## Code overview
The calculator is built using the Qt framework and C++. The `MainWindow` class handles the user interface and the calculation logic.

The `digit_pressed()` function is used to handle the pressing of digit buttons. It checks if the display screen has a value of 0 or if the equals button has been pressed, and resets the display screen in those cases. It also handles special cases for when the root, power, or logarithm operations are being used.

The `on_pushButton_decimal_released()` function adds a decimal point to the number currently being entered. It also checks if a decimal point has already been entered.

The `on_pushButton_clear_released()` function is used to clear the display screen and reset all operation flags.

The `on_pushButton_equals_released()` function calculates the result of the entered expression and displays it on the screen.

The `binary_operation_pressed()` function handles the pressing of binary operation buttons, such as addition, subtraction, multiplication, and division. It checks if the last character on the display screen is a binary operation and replaces it with the newly pressed operation if it is.

The `brakets_pressed()` function handles the pressing of the parentheses buttons.

The `trigonometric_functions_pressed()` function handles the pressing of the sine, cosine, tangent, and cotangent buttons. It also converts the entered value to radians or degrees based on the mode selected by the user.

The `unary_operation_pressed()` function is called when a unary operation button is pressed, such as +/- or persent button.

The `root_pressed()` function is called when the root button is pressed. It takes the current value displayed on the calculator and calculates its root, updating the display with the result.

The `power_pressed()` function is called when the power button is pressed. It takes the current value displayed on the calculator and raises it to the power, updating the display with the result.

The `mathematical_constants_pressed()` function is called when a mathematical constant button is pressed, such as pi or e. It updates the display with the value of the selected constant.

The `logarithm_pressed()` function is called when the logarithm button is pressed. It takes the current value displayed on the calculator and calculates its logarithm with the given base, updating the display with the result.

The `radians_degrees_pressed()` function is called when the radians/degrees button is pressed. It switches the calculator between radians and degrees mode, depending on the current mode.

The `inverse_pressed()` function is called when the inverse button is pressed. It takes the current value displayed on the calculator and calculates its inverse, updating the display with the result.

The `factorial_pressed()` function is called when the factorial button is pressed. It takes the current value displayed on the calculator and calculates its factorial, updating the display with the result.

The `calculation()` function is auxiliary to the main functions. It returns a QJSValue object that represents the calculation result. It does not require any arguments.