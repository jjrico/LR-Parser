// LR Parser
// By: Jeremy Rico
//
// Description: This program uses a bottom up parser approach with an LR
// Parse table to find all strings that adhere to the following Grammer:
// E--> E + T
// E--> E- T
// E--> T
// T--> T * F
// T--> T / F
// T--> F
// F--> ( E )
// F--> i

#include <iostream>
#include <iomanip>
#include <stack>
#include <stdexcept>

// Recursive function to print out the contents of the stack in reverse order
void print_stack(std::stack<char> k) {
  if (k.empty()) {
    return;
  }
  char temp = k.top();
  k.pop();
  print_stack(k);
  std::cout << temp << " ";
}

// This function takes the top element of the input stack and returns the
// current state of the machine. Since I wanted to use a stack of characters,
// I used alphabetic characters to represent 10 (a), 11 (b), 12 (c), 13 (d),
// 14 (e), & 15 (f). That is why this function is necessary.
int find_current_state(const std::stack<char> &k) {
  if (k.top() == '0') {
    return 0;
  } else if (k.top() == '1') {
    return 1;
  } else if (k.top() == '2') {
    return 2;
  } else if (k.top() == '3') {
    return 3;
  } else if (k.top() == '4') {
    return 4;
  } else if (k.top() == '5') {
    return 5;
  } else if (k.top() == '6') {
    return 6;
  } else if (k.top() == '7') {
    return 7;
  } else if (k.top() == '8') {
    return 8;
  } else if (k.top() == '9') {
    return 9;
  } else if (k.top() == 'a') {
    return 10;
  } else if (k.top() == 'b') {
    return 11;
  } else if (k.top() == 'c') {
    return 12;
  } else if (k.top() == 'd') {
    return 13;
  } else if (k.top() == 'e') {
    return 14;
  } else if (k.top() == 'f') {
    return 15;
  }
}

int main() {
  std::string input;
  std::stack<char> myStack;
  char current_state;
  std::string table_find;

  std::cout << "Please input a string followed by '$': ";
  std::getline(std::cin, input);

  std::string LR_table[16][11] = {
      {"S5", " ", " ", " ", " ", "S4", " ", " ", "1", "2", "3"},
      {" ", "S6", "S7", " ", " ", " ", " ", "X", " ", " ", " "},
      {" ", "R3", "R3", "S8", "S9", " ", "R3", "R3", " ", " ", " "},
      {" ", "R6", "R6", "R6", "R6", " ", "R6", "R6", " ", " ", " "},
      {"S5", " ", " ", " ", " ", "S4", " ", " ", "a", "2", "3"},
      {" ", "R8", "R8", "R8", "R8", " ", "R8", "R8", " ", " ", " "},
      {"S5", " ", " ", " ", " ", "S4", " ", " ", " ", "b", "3"},
      {"S5", " ", " ", " ", " ", "S4", " ", " ", " ", "c", "3"},
      {"S5", " ", " ", " ", " ", "S4", " ", " ", " ", " ", "d"},
      {"S5", " ", " ", " ", " ", "S4", " ", " ", " ", " ", "e"},
      {" ", "S6", "S7", " ", " ", " ", "Sf", " ", " ", " ", " "},
      {" ", "R1", "R1", "S8", "S9", " ", "R1", "R1", " ", " ", " "},
      {" ", "R2", "R2", "S8", "S9", " ", "R2", "R2", " ", " ", " "},
      {" ", "R4", "R4", "R4", "R4", " ", "R4", "R4", " ", " ", " "},
      {" ", "R5", "R5", "R5", "R5", " ", "R5", "R5", " ", " ", " "},
      {" ", "R7", "R7", "R7", "R7", " ", "R7", "R7", " ", " ", " "},
  };

  myStack.push('0'); // push starting state to the stack

  // run until accept or empty string is encountered
  while (myStack.top() != 'X' || myStack.top() != ' ') {
    print_stack(myStack);
    std::cout << "\t\tInput: " << input << std::endl;

    // Set the current state depending on which value is at the top of the stack
    current_state = find_current_state(myStack);

    // Retrieve the table value
    if (input.front() == 'i') {
      table_find = LR_table[current_state][0];
    } else if (input.front() == '+') {
      table_find = LR_table[current_state][1];
    } else if (input.front() == '-') {
      table_find = LR_table[current_state][2];
    } else if (input.front() == '*') {
      table_find = LR_table[current_state][3];
    } else if (input.front() == '/') {
      table_find = LR_table[current_state][4];
    } else if (input.front() == '(') {
      table_find = LR_table[current_state][5];
    } else if (input.front() == ')') {
      table_find = LR_table[current_state][6];
    } else if (input.front() == '$') {
      table_find = LR_table[current_state][7];
    } else if (input.front() == 'E') {
      table_find = LR_table[current_state][8];
    } else if (input.front() == 'T') {
      table_find = LR_table[current_state][9];
    } else if (input.front() == 'F') {
      table_find = LR_table[current_state][10];
    }

    switch (table_find.at(0)) {
    case 'S':
      myStack.push(input.at(0));
      myStack.push(table_find.at(1));
      input.erase(0, 1);
      break;
    case 'R':
      if (table_find.at(1) == '1' || table_find.at(1) == '2') {
        while (myStack.top() != 'E') {
          myStack.pop(); // pup until RHS limit is found
        }
        myStack.pop();                               // pop one more time
        current_state = find_current_state(myStack); // set current state
        myStack.push('E');                           // push LHS
        table_find = LR_table[current_state][8];     // find new rule
        myStack.push(table_find.at(0));              // push new state
      } else if (table_find.at(1) == '3') {// repeat this process for all rules
        while (myStack.top() != 'T') {
          myStack.pop();
        }
        myStack.pop();
        current_state = find_current_state(myStack);
        myStack.push('E');
        table_find = LR_table[current_state][8];
        myStack.push(table_find.at(0));
      } else if (table_find.at(1) == '4' || table_find.at(1) == '5') {
        while (myStack.top() != 'T') {
          myStack.pop();
        }
        myStack.pop();
        current_state = find_current_state(myStack);
        myStack.push('T');
        table_find = LR_table[current_state][9];
        myStack.push(table_find.at(0));
      } else if (table_find.at(1) == '6') {
        while (myStack.top() != 'F') {
          myStack.pop();
        }
        myStack.pop();
        current_state = find_current_state(myStack);
        myStack.push('T');
        table_find = LR_table[current_state][9];
        myStack.push(table_find.at(0));
      } else if (table_find.at(1) == '7') {
        while (myStack.top() != '(') {
          myStack.pop();
        }
        myStack.pop();
        current_state = find_current_state(myStack);
        myStack.push('F');
        table_find = LR_table[current_state][10];
        myStack.push(table_find.at(0));
      } else if (table_find.at(1) == '8') {
        while (myStack.top() != 'i') {
          myStack.pop();
        }
        myStack.pop();
        current_state = find_current_state(myStack);
        myStack.push('F');
        table_find = LR_table[current_state][10];
        myStack.push(table_find.at(0));
      }
      break;
    }

    if (table_find == "X") { // if accept state is found push('X')
      myStack.push('X');
      break;
    } else if (table_find == " ") { // if error
      myStack.push(' ');
      break;
    }
  }

  print_stack(myStack);
  std::cout << "\t\tInput: " << input << std::endl;

  // If we have gotten to this point the top element of the stack can be only
  // one of two options. Either X for accpeted or an empty string for rejected
  if (myStack.top() == 'X') {
    std::cout << "Accepted!" << std::endl;
  } else if (myStack.top() == ' ') {
    std::cout << "Rejected :(" << std::endl;
  }

  return 0;
}
