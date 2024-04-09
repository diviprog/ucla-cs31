#include "grid.h"
#include <cctype>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

// function declaration
void plotHorizontalLine(int r, int c, int distance, char ch, int fgbg);
void plotVerticalLine(int r, int c, int distance, char ch, int fgbg);
void plotRectangle(int r, int c, int height, int width, char ch);

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
const int HORIZ = 0;
const int VERT = 1;
const int FG = 0;
const int BG = 1;
void setFgBg(int r, int c, char plotChar, int fgbg);

int performCommands(string commandString, char& plotChar, int& mode, int& badPos);
void ToLower(string& commandString);

// converts all alpha characters to lowercase for ease of checking during if-statements
void ToLower(string& commandString){
    for (int i = 0; i != commandString.size(); i++){
        if (isalpha(commandString.at(i))){
            commandString.at(i) = tolower(commandString.at(i));
        }
    }
}

// performs the commands given by the input string
int performCommands(string commandString, char& plotChar, int& mode, int& badPos){
    
    if (not(isprint(plotChar) or (mode == FG) or (mode == BG))){ // checks for return 2 cases (not printable character or mode is not FG nor BG
        return 2;
    }
    
    int current_row = 1;
    int current_column = 1; // initialises the position of cursor to (1,1)
    ToLower(commandString);
    
    bool return_3 = false; // flag variable to see if there is an out of bounds to plot so that first syntax error is checked and then the out of bounds plotting is checked
    
    for (int i = 0; i != commandString.size(); i++){
        if (commandString.at(i) == 'c'){ // c command
            clearGrid();
        }
        else if (commandString.at(i) == 'f'){ // f command
            mode = FG;
            if (i != commandString.size()) { // checks whether it is the last command so that there is no runtime error
                if (not(isprint(commandString.at(i+1)))){ // checks whether the character is printable or not
                    badPos = i+1;
                    return 2;
                }
            }
            else {
                badPos = i+1;
                return 1; // action for when the string ends with 'f'
            }
            plotChar = commandString.at(i+1);
            i += 1;
        }
        else if (commandString.at(i) == 'b'){
            mode = BG;
            if (i != commandString.size()) { // checks whether it is the last command so that there is no runtime error
                if (not(isprint(commandString.at(i+1)))){ // checks whether the character is printable or not
                    badPos = i+1;
                    return 2;
                }
            }
            else {
                badPos = i+1;
                return 1; // action for when the string ends with 'b'
            }
            plotChar = commandString.at(i+1);
            i += 1;
        }
        else if (commandString.at(i) == 'h'){
            int distance;
            if (i+1 == commandString.size()){
                badPos = i+1;
                return 1; // action for when the string ends with 'h'
            }
            else if (isdigit(commandString.at(i+1)) and i+2 == commandString.size()){ // case when the final command is 'h' followed by single digit number
                distance = stoi(commandString.substr(i+1,1));
                i += 1;
            }
            else if (isdigit(commandString.at(i+1))){ // case when the command is 'h' and checks whether the following char is numeric (not the final command)
                if (isdigit(commandString.at(i+2))){ // checks for a 2-digit number
                    distance = stoi(commandString.substr(i+1,2));
                    i += 2;
                }
                else {
                    distance = stoi(commandString.substr(i+1,1));
                    i += 1;
                }
            }
            else if (commandString.at(i+1) == '-'){ // case of negative number
                if (isdigit(commandString.at(i+2))) {
                    if (i+3 == commandString.size()) { // case of final command being 'h' followed by negative single digit number
                        distance = stoi(commandString.substr(i+1,2));
                        i += 2;
                    }
                    else {
                        if (isdigit(commandString.at(i+3))) { // case of negative double digit number
                            distance = stoi(commandString.substr(i+1,3));
                            i += 3;
                        }
                        else { // case of negative single digit number
                            distance = stoi(commandString.substr(i+1,2));
                            i+= 2;
                        }
                    }
                }
                else {
                    badPos = i+2;
                    return 1; // negative sign followed by no number --> syntax error
                }
            }
            else {
                badPos = i+1;
                return 1;
            }
            
            if (distance+current_column > getCols() and not(return_3)) {
                return_3 = true; // handles the plotting error case
                badPos = i-1;
            }
            else {
                plotLine(current_row, current_column, distance, HORIZ, plotChar, mode);
                current_column += distance;
            }
        }
        else if (commandString.at(i) == 'v'){
            int distance;
            if (i+1 == commandString.size()){
                badPos = i+1;
                return 1; // action for when the string ends with 'h'
            }
            else if (isdigit(commandString.at(i+1)) and i+2 == commandString.size()){ // case when the final command is 'v' followed by single digit number
                distance = stoi(commandString.substr(i+1,1));
                i += 1;
            }
            else if (isdigit(commandString.at(i+1))){ // case when the command is 'v' and checks whether the following char is numeric (not the final command)
                if (isdigit(commandString.at(i+2))){ // checks for a 2-digit number
                    distance = stoi(commandString.substr(i+1,2));
                    i += 2;
                }
                else {
                    distance = stoi(commandString.substr(i+1,1));
                    i += 1;
                }
            }
            else if (commandString.at(i+1) == '-'){ // case of negative number
                if (isdigit(commandString.at(i+2))) {
                    if (i+3 == commandString.size()) { // case of final command being 'v' followed by negative single digit number
                        distance = stoi(commandString.substr(i+1,2));
                        i += 2;
                    }
                    else {
                        if (isdigit(commandString.at(i+3))) { // case of negative double digit number
                            distance = stoi(commandString.substr(i+1,3));
                            i += 3;
                        }
                        else { // case of negative single digit number
                            distance = stoi(commandString.substr(i+1,2));
                            i+= 2;
                        }
                    }
                }
                else {
                    badPos = i+2;
                    return 1; // negative sign followed by no number --> syntax error
                }
            }
            else {
                badPos = i+1;
                return 1;
            }
            
            if (distance+current_row > getRows() and not(return_3)) {
                return_3 = true; // handles the plotting error case
                badPos = i-1;
            }
            else {
                plotLine(current_row, current_column, distance, VERT, plotChar, mode);
                current_row += distance;
            }
        }
        else {
            badPos = i;
            return 1;
        }
    }
    
    if(return_3){
        return 3;
    }
    
    return 0;
}

// function that checks whether foreground or background plot and sets the character accordingly
void plotFgBg(int r, int c, char ch, int fgbg) {
    if ((fgbg == 0) or (fgbg == 1 and getChar(r, c) == ' ')){
        setChar(r, c, ch);
    }
}

// plots a line given starting row, column, length of line, direction of line, character to plot and foreground/background parameter
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg){
    bool answer = true;
    
    if ((not((dir == 0) or (dir == 1))) or (not((fgbg == 0) or (fgbg == 1))) or (((dir == 0) and ((c+distance > getCols()) or c+distance < 1)) or ((dir == 1) and ((r+distance > getRows()) or r+distance < 1))) or (not(isprint(plotChar)))) { // checks the invalid parameters for the plotLine function
        answer = false;
    }
    else {
        if (distance < 0){ // handles the negative distance case
            if (dir == 0) {
                c = c + distance;
            }
            else {
                r = r + distance;
            }
            distance = -distance;
        }
        
        if (dir == 0){ // plots line according to direction
            plotHorizontalLine(r, c, distance, plotChar, fgbg);
        }
        else {
            plotVerticalLine(r, c, distance, plotChar, fgbg);
        }
    }
    
    return answer;
}


// horizontal line plot
void plotHorizontalLine(int r, int c, int distance, char ch, int fgbg){
    if (distance >= 0 && c<=getCols() && r<=getRows()){
        for (int i = 0; i <= distance; i++){
            if (c+i <= getCols() && c+i >= 1){
                plotFgBg(r, c+i, ch, fgbg);
            }
        }
    }
}


// vertical line plot
void plotVerticalLine(int r, int c, int distance, char ch, int fgbg){
    if (distance >= 0 && c<=getCols() && r<=getRows()){
        for (int i = 0; i <= distance; i++){
            if (r+i <= getRows() && r+i >= 1){
                plotFgBg(r+i, c, ch, fgbg);
            }
        }
    }
}


// main method
int main()
{
    for (;;)
    {
        cout << "Enter the number of grid rows and columns (max 30 each): ";
        int nRows;
        int nCols;
        cin >> nRows >> nCols;
        cin.ignore(10000, '\n');
        if (nRows >= 1  &&  nRows <= MAXROWS  &&  nCols >= 1  &&  nCols <= MAXCOLS)
        {
            setSize(nRows, nCols);
            break;
        }
        cout << "The numbers must be between 1 and 30." << endl;
    }
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string (empty line to quit): ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = performCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
            case 0:
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << position << endl;
                break;
            case 2:
                if (!isprint(currentChar))
                    cout << "Current charaacter is not printable" << endl;
                if (currentMode != FG  &&  currentMode != BG)
                    cout << "Current mode is " << currentMode << ", not FG or BG" << endl;
                break;
            case 3:
                cout << "Cannot perform command at position " << position << endl;
                break;
            default:
                // It should be impossible to get here.
                cout << "performCommands returned " << status << "!" << endl;
        }
    }
}
