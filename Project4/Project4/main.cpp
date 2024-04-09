//
//  main.cpp
//  Project4
//
//  Created by Devansh Mishra on 04/11/23.
//

#include <iostream>
#include <string>
using namespace std;

int reduplicate(string a[], int n);
int locate(const string a[], int n, string target);
int locationOfMax(const string a[], int n);
int circleLeft(string a[], int n, int pos);
int enumerateRuns(const string a[], int n);
int flip(string a[], int n);
int locateDifference(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int locateAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);

int divide(string a[], int n, string divider) {
    if (n < 0) {
        return -1;
    }
    
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n-1; i++) {
            if ((a[i] >= divider) and (a[i+1] <= divider)) {
                string temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (divider <= a[i]) {
            return i;
        }
    }
    return n;
}

int locateAny(const string a1[], int n1, const string a2[], int n2) {
    if ((n1 < 0) or (n2 < 0)) {
        return -1;
    }
    
    int smallest = n1;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++){
            if ((a1[i] == a2[j]) and (i < smallest)) {
                smallest = i;
            }
        }
    }
    
    if (smallest == n1) {
        return -1;
    }
    else {
        return smallest;
    }
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
    if ((n1 < 0) or (n2 < 0)) {
        return -1;
    }
    
    for (int i = 0; i < n1; i++) {
        if (a2[0] == a1[i]){
            bool flag = true;
            for (int j = 1; j < n2; j++){
                if (not(a2[j] == a1[i+j])){
                    flag = false;
                }
            }
            if (flag) {
                return i;
            }
        }
    }
    
    return -1;
    
}

int locateDifference(const string a1[], int n1, const string a2[], int n2) {
    if ((n1 < 0) or (n2 < 0)) {
        return -1;
    }
    
    int n;
    if (n1 <= n2) {
        n = n1;
    }
    else {
        n = n2;
    }
    
    for (int i = 0; i < n; i++) {
        if (a1[i] != a2[i]) {
            return i;
        }
    }
    return n;
}

int flip(string a[], int n) {
    if (n < 0) {
        return -1;
    }
    
    for (int i = 0; i < n/2; i++) {
        string temp = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }
    
    return n;
}

int enumerateRuns(const string a[], int n) {
    if (n < 0) {
        return -1;
    }
    else if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }
    
    int numRuns = 1;
    
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i-1]){
            numRuns += 1;
        }
    }
    
    return numRuns;
}

int circleLeft(string a[], int n, int pos) {
    if (n < 0) {
        return -1;
    }
    
    string temp = a[pos];
    for (int i = pos; i < n-1; i++) {
        a[i] = a[i+1];
    }
    a[n-1] = temp;
    
    return 1;
}

int locationOfMax(const string a[], int n) {
    if (n < 0) {
        return -1;
    }
    
    int maxPos = -1;
    string bigString = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > bigString){
            maxPos = i;
            bigString = a[i];
        }
    }
    return maxPos;
}

int locate(const string a[], int n, string target) {
    if (n < 0) {
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        if (a[i] == target){
            return i;
        }
    }
    
    return -1;
}

int reduplicate(string a[], int n) {
    if (n < 0) {
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        a[i] += a[i];
    }
    return n;
}

int main() {
    
    string h[7] = { "nikki", "ron", "asa", "vivek", "", "chris", "donald" };
    assert(locate(h, 7, "chris") == 5);
    assert(locate(h, 7, "asa") == 2);
    assert(locate(h, 2, "asa") == -1);
    assert(locationOfMax(h, 7) == 3);

    string g[4] = { "nikki", "ron", "chris", "tim" };
    assert(locateDifference(h, 4, g, 4) == 2);
    assert(circleLeft(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "ron");

    string c[4] = { "ma", "can", "tu", "do" };
    assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

    string e[4] = { "asa", "vivek", "", "chris" };
    assert(subsequence(h, 7, e, 4) == 2);

    string d[5] = { "ron", "ron", "ron", "chris", "chris" };
    assert(enumerateRuns(d, 5) == 2);
        
    string f[3] = { "vivek", "asa", "tim" };
    assert(locateAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tim" && f[2] == "vivek");
        
    assert(divide(h, 7, "donald") == 3);
        
    cout << "All tests succeeded" << endl;
    
    return 0;
}
