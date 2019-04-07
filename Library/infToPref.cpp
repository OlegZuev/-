string infToPref(string s) {
    stack<char> stack;
    string output = "";
    for (int i = s.length() - 1; i >= 0; --i) {
        char x = s[i];
        if (x >= '0' && x <= '9') {
            output = x + output;
        } else if (x == ')') {
            stack.push(x);
        } else if (x == '(') {
            while (stack.top() != ')') {
                output = stack.top() + output;
                stack.pop();
            }
            stack.pop();
        } else {
            int priority = getPriority(x);
            while (!stack.empty() && getPriority(stack.top()) > priority) {
                output = stack.top() + output;
                stack.pop();
            }
            stack.push(x);
        }
    }
    while (!stack.empty()) {
        output = stack.top() + output;
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