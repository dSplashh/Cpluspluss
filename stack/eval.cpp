#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cmath>

void stackCheck(std::stack < double > &mystack, std::string operand){
    if (operand == "+"){
        double num1 = mystack.top();
        mystack.pop();
        double num2 = mystack.top();
        mystack.pop();
        double num3 = std::ceil(num2 + num1);
        mystack.push(num3);
    }
    if (operand == "-"){
        double num1 = mystack.top();
        mystack.pop();
        double num2 = mystack.top();
        mystack.pop();
        double num3 = std::ceil(num2 - num1);
        mystack.push(num3);
    }
    if (operand == "*"){
        double num1 = mystack.top();
        mystack.pop();
        double num2 = mystack.top();
        mystack.pop();
        double num3 = std::ceil(num2 * num1);
        mystack.push(num3);
    }
    if (operand == "/"){
        double num1 = mystack.top();
        mystack.pop();
        double num2 = mystack.top();
        mystack.pop();
        double num3 = std::floor(num2 / num1);
        mystack.push(num3);
    }
    if (operand == "^"){
        double num1 = mystack.top();
        mystack.pop();
        double num2 = mystack.top();
        mystack.pop();
        double num3 = std::ceil(pow(num2, num1));
        mystack.push(num3);
    }
}

int main(int argc, char *argv[]){
    std::stack < double > numz;
    std::string num;

    std::stringstream str(argv[1]);

    while(getline(str, num, ' '))
    {
        if (num == "+" || num == "-" || num == "*" || num == "/" || num == "^"){
            stackCheck(numz, num);
        }
        else {
            numz.push(std::stoi(num));
        }
    }

    std::cout << std::ceil(numz.top()) << std::endl;

    return 0;
}
