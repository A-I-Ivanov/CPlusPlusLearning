/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

enum Operators{
    kAdd,
    kSubtract,
    kMultiply,
    kDivide,
    kNotAnOperator
};

struct DataInt{
    std::vector<double> values;
    std::vector<pair<Operators, int>> operators;
};

double toNumber(char letter){
    switch(letter){
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case '0':
            return 0;
        default:
            return -1;
    }
}

bool isNumber(char letter) {
    if(toNumber(letter)==-1){
        return false;
    }
    return true;
}

Operators toOperator(char letter){
    switch(letter){
        case '+':
            return Operators::kAdd;
        case '-':
            return Operators::kSubtract;
        case '/':
            return Operators::kDivide;
        case '*':
            return Operators::kMultiply;
        default:
            return Operators::kNotAnOperator;
    }
}

bool isOperator(char letter) {
    if(toOperator(letter)==Operators::kNotAnOperator){
        return false;
    }
    return true;
}


DataInt ParseStringToData(const string& input)
{
    DataInt output;
    for(int ii=0; ii<input.size(); ii++)
    {
        if(isNumber(input[ii]))
        {
            output.values.push_back(toNumber(input[ii]));
        }
        else if (isOperator(input[ii])){
            output.operators.push_back({toOperator(input[ii]),ii});
        }
    }
    return output;
}

double operate(double number1, double number2, Operators op){
    switch(op){
        case Operators::kAdd:
            return number1+number2;
        case  Operators::kSubtract:
            return number1-number2;
        case Operators::kDivide:
            return number1/number2;
        case Operators::kMultiply:
            return number1*number2;
        default:
            return 0;
    }
}

int operatorPriority(Operators op){
    switch(op){
        case Operators::kAdd:
        case  Operators::kSubtract:
            return 1;
        case Operators::kDivide:
        case Operators::kMultiply:
            return 2;
        default:
            return 0;
    }
}


double operate(DataInt input){
    if(input.operators.size()==0)
    {
        return input.values.front();
    }

    Operators op = input.operators.front().first;
    double val = input.values.front();

    for(int ii =1; ii<input.values.size() ; ii++)
    {
        val = operate(val, input.values[ii], op);
    }

}



int main()
{
    string kInput = "1*2+8/4*5+6*7-3";


    DataInt output = ParseStringToData(kInput);

    for(auto number : output.values){
        cout<< number << ", ";
    }

    for(auto op : output.operators){
        cout<<"\nType:" << op.first << ", index :" << op.second;
    }

    cout<<"\n Testing base operate: " << operate(output);


    return 0;
}
