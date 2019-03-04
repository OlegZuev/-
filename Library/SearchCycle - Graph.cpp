struct Peak {
    int number;
    vector<Peak*> next;
    bool isIncluded;
};

bool isCycle(Peak* original, Peak* prev, Peak* peak, int length) {
    for (auto& elem : peak->next) {
        if (prev != original && elem == original) {
            return length > 2;
        }
    }
    for (int i = 0; i < peak->next.size(); ++i) {
        bool flag = false;
        if (peak->next[i] != prev) {
            flag = isCycle(original, peak, peak->next[i], length + 1);
        }
        if (flag) {
            return true;
        }
    }
    return false;
}