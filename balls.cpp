#include <iostream>
#include <chrono>
using namespace std;

// The categorizeRead function
char categorizeRead(float maxValues[]) {
    if (maxValues[3] > 500 && maxValues[4] > 600) {
        if (maxValues[1] > 300 && maxValues[2] > 400) {
            if (maxValues[0] > 700) {
                if (maxValues[7] > 200 && maxValues[8] > 300) {
                    if (maxValues[6] > 800) {
                        if (maxValues[4] > 900) {
                            return 'S';
                        } else {
                            return 'N';
                        }
                    } else {
                        return 'M';
                    }
                } else {
                    if (maxValues[9] > 7000) {
                        return 'J';
                    } else {
                        return 'I';
                    }
                }
            } else {
                if (maxValues[7] > 200 && maxValues[8] > 300) {
                    if (maxValues[2] > 300) {
                        return 'A';
                    } else {
                        return 'T';
                    }
                } else {
                    return 'Y';
                }
            }
        } else if (maxValues[1] < 300 && maxValues[2] < 400) {
            if (maxValues[0] > 700) {
                return 'Z';
            } else {
                return 'L';
            }
        } else {
            if (maxValues[0] > 800) {
                return 'X';
            } else {
                if (maxValues[10] < 5000) {
                    return 'Q';
                } else {
                    return 'G';
                }
            }
        }
    } else if (maxValues[3] < 500 && maxValues[4] > 600) {
        if (maxValues[9] > 7000) {
            return 'P';
        } else {
            return 'K';
        }
    } else if (maxValues[3] > 500 && maxValues[4] < 600) {
        if (maxValues[1] > 300) {
            if (maxValues[0] > 800) {
                return 'E';
            } else if (maxValues[0] < 700) {
                return 'C';
            } else {
                return 'O';
            }
        } else {
            return 'D';
        }
    } else {
        if (maxValues[1] > 300) {
            return 'F';
        } else {
            if (maxValues[5] > 500) {
                if (maxValues[2] > 520 && maxValues[4] > 525) {
                    return 'V';
                } else if (maxValues[3] > 558) {
                    return 'R';
                } else {
                    if (maxValues[9] > 2000) {
                        return 'H';
                    } else {
                        return 'U';
                    }
                }
            } else {
                if (maxValues[7] > 200) {
                    return 'W';
                } else {
                    if (maxValues[0] < 700) {
                        return '\0';  // NULL
                    } else {
                        return 'B';
                    }
                }
            }
        }
    }
}

// Main function
int main() {
    float maxValues[] = {700, 400, 450, 510, 620, 520, 810, 210, 310, 7100, 4800};

    // Start measuring time
    auto start = chrono::high_resolution_clock::now();

    // Call the function
    char result = categorizeRead(maxValues);

    // Stop measuring time
    auto end = chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    chrono::duration<double, micro> elapsed = end - start;
    cout << "Function runtime: " << elapsed.count() << " microseconds" << endl;

    return 0;
}
