// CPP program to convert infix to prefix 
#include <bits/stdc++.h> 
using namespace std;
  
bool isOperand(char c) 
{ 
    // If the character is a digit then it must 
    // be an operand 
    return isdigit(c); 
}

// Function to check if given character is 
// an operator or not. 
bool isOperator(char c) 
{
    if(c == '*' || c == '/' || c == '+' || c == '-')
        return true;
    return false;
} 

  
// Function to find priority of given 
// operator. 
int getPriority(char C) 
{ 
    if (C == '-' || C == '+') 
        return 1; 
    else if (C == '*' || C == '/') 
        return 2;
    return 0; 
} 
  
double evaluatePrefix(string prefix) 
{ 
    stack<double> Stack;


    for (int j = prefix.size() - 1; j >= 0; j--) { 
  
        
        if (isOperand(prefix[j])) 
            Stack.push(prefix[j] - '0'); 
  
        else { 
  
            // Operator encountered 
            // Pop two elements from Stack 
            double o1 = Stack.top(); 
            Stack.pop(); 
            double o2 = Stack.top(); 
            Stack.pop(); 
  
            // Use switch case to operate on o1 
            // and o2 and perform o1 O o2. 
            if(prefix[j] == '+') 
            {
                Stack.push(o1 + o2); 
            }
            else if(prefix[j] == '-')
            {
                Stack.push(o1 - o2);
            }
            else if(prefix[j] == '*')
            {
                Stack.push(o1 * o2);
            }
            else if(prefix[j] == '/')
            {
                Stack.push(o1 / o2);
            }
      
        } 
    } 
  
    return Stack.top(); 
}

string checkInitErrors(string infix)
{

    int bracketsBal = 0;
    int totalBrackets = 0;
    int totalOperators = 0;

    if(infix.length() == 0)
    {
        cout << "due to intial empty string given\n";
        return "NotWellFormed";
    }

    if(infix.length() == 1 && !isOperand(infix[0]))
    {
        cout << "Only non operand given\n";
        return "NotWellFormed";
    }

    if(infix.length() == 1)
    {
        return infix;
    }

    if(infix.length() > 1 && infix[0] != '(')
    {
        cout << "due to intial bracket\n";
        return "NotWellFormed";
    }

    if(infix.length() == 3)
    {
        cout << "due to len of 3" << endl;
        return "NotWellFormed";

    }

    for (int i = 0; i < infix.length(); i++) 
    {
        if(infix[i] == '(')
        {
            bracketsBal++;
            totalBrackets++;
        }
        else if(infix[i] == ')')
        {
            bracketsBal--;
            totalBrackets++;
        }
        
        

        if(isOperator(infix[i]))
        {
            totalOperators++;
        }
    }
    

    if(bracketsBal != 0)
    {
        cout << "Bracket bal" << endl;
        return "NotWellFormed";
    }

    if(totalOperators*2 != totalBrackets)
    {
        cout << totalOperators << " Brackets: " << totalBrackets << endl;
        cout << "Not enough Brackets" << endl;
        return "NotWellFormed";

    }

    return "NoInitialErrors";

}

  
// Function that converts infix 
// expression to prefix expression. 
string infixToPrefix(string infix) 
{ 

    string initErrors = checkInitErrors(infix);

    if(initErrors == "NotWellFormed")
        return initErrors;


    
    
    // stack for operators. 
    stack<char> operators; 
  
    // stack for operands. 
    stack<string> operands;



  
    for (int i = 0; i < infix.length(); i++) { 



        // If current character is an 
        // opening bracket, then 
        // push into the operators stack. 
        if (infix[i] == '(') {
            
            if( i == infix.length() - 1 || infix[i+1] == ')' || isOperator(infix[i+1]))
            {
                cout <<  infix[i+1] << endl;
                cout << "( followed by ) or operator" << endl;
                return "NotWellFormed";
            } 
            
            operators.push(infix[i]); 
        } 

        
        // If current character is a 
        // closing bracket, then pop from 
        // both stacks and push result 
        // in operands stack until 
        // matching opening bracket is 
        // not found. 
        else if (infix[i] == ')') {
            

            if(infix[i+1] == '(' || isOperand(infix[i+1]))
            {
                cout << ") followed by ( or operand" << endl;
                return "NotWellFormed";
            }

            while (operators.top() != '(') { 
  
                // operand 1 
                string op1 = operands.top(); 
                operands.pop(); 
  
                // operand 2 
                string op2 = operands.top(); 
                operands.pop(); 
  
                // operator 
                char op = operators.top(); 
                operators.pop(); 
  
                // Add operands and operator 
                // in form operator + 
                // operand1 + operand2. 
                string tmp = op + op2 + op1; 
                operands.push(tmp); 
            } 
  
            // Pop opening bracket from 
            // stack. 
            operators.pop(); 
        } 
  
        // If current character is an 
        // operand then push it into 
        // operands stack. 
        else if (isOperand(infix[i])) {

            if( i == infix.length() - 1 || isOperand(infix[i+1]))
            {
                cout << "Operand followed by operand" << endl;
                return "NotWellFormed";
            }

            operands.push(string(1, infix[i])); 
        } 
  
        // If current character is an 
        // operator, then push it into 
        // operators stack after popping 
        // high priority operators from 
        // operators stack and pushing 
        // result in operands stack. 
        else {
            if( i == infix.length() - 1 || isOperator(infix[i+1]) || infix[i+1] == ')')
            {
                cout << "i: " << i << " infix.length(): " << infix.length() << " infix[i]: " << infix[i] << " infix[i+1]: " << infix[i+1] << endl;
                cout << "Operator followed by not operand" << endl;
                return "NotWellFormed";
            }
            while (!operators.empty() &&  
                    getPriority(infix[i]) <=  
                    getPriority(operators.top())) { 
  
                string op1 = operands.top(); 
                operands.pop(); 
  
                string op2 = operands.top(); 
                operands.pop(); 
  
                char op = operators.top(); 
                operators.pop(); 
  
                string tmp = op + op2 + op1; 
                operands.push(tmp); 
            } 
  
            operators.push(infix[i]); 
        } 
    } 
  
    // Pop operators from operators stack 
    // until it is empty and add result 
    // of each pop operation in 
    // operands stack. 
    while (!operators.empty()) { 
        string op1 = operands.top(); 
        operands.pop(); 
  
        string op2 = operands.top(); 
        operands.pop(); 
  
        char op = operators.top(); 
        operators.pop(); 
  
        string tmp = op + op2 + op1; 
        operands.push(tmp); 
    } 
  
    // Final prefix expression is 
    // present in operands stack. 
    return operands.top();
} 


// Driver code 
int main() 
{ 
    string s = "(8+(2*3)/2)";
    string prefix = infixToPrefix(s);

    cout << "Prefix: " << prefix << endl;
    
    if(prefix != "NotWellFormed")
    {
        cout << "Ans: " << evaluatePrefix(infixToPrefix(s)) << endl;
    }

    return 0; 
} 