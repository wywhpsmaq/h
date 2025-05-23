int search(int n, int *p, int target) {
    int low = 0, high = n;
    while (low <= high) {
        int middle = (low + high) / 2;
        if (target == p[middle]) {
            return middle;
        } else if (target > p[middle]) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return -1;
}