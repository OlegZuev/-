string infToPost(string s);

int getPriority(char c);

string infToPost(string s) {
    stack<char> stack;
    string output = "";
    for (int i = 0; i < s.length(); ++i) {
        char x = s[i];
        if (x >= '0' && x <= '9') {
            output += x;
        } else if (x == '(') {
            stack.push(x);
        } else if (x == ')') {
            while (stack.top() != '(') {
                output += stack.top();
                stack.pop();
            }
            stack.pop();
        } else {
            int priority = getPriority(x);
            while (!stack.empty() && getPriority(stack.top()) > priority) {
                output += stack.top();
                stack.pop();
            }
            stack.push(x);
        }
    }
    while (!stack.empty()) {
        output += stack.top();
        stack.pop();
    }
    return output;
}

int getPriority(char c) {
    switch (c) {
    case '(':
        return 1;
    case ')':
        return 2;
    case '=':
        return 3;
    case '+':
    case '-':
        return 4;
    case '*':
    case '/':
        return 5;
    }
    return -1;
}