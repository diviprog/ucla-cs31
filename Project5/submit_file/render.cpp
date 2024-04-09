#include <cstring>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

const int maxLineLength = 10;

int render(int lineLength, istream& inf, ostream& outf);
void getWords(char inputString[], char words[][2*maxLineLength]);

void getWords(char inputString[], char words[][2*maxLineLength]) {
    
    int wordCount = 0;
    int wordIndex = 0;
    int charIndex = 0;

    while (inputString[wordIndex] != '\0') {
        char currentChar = inputString[wordIndex];

        if (currentChar == ' ' || currentChar == '\t' || currentChar == '\n' || currentChar == '\r') { // If a space, tab, newline, or carriage return is encountered, terminate the current word
            words[wordCount][charIndex] = '\0';
            ++wordCount;
            charIndex = 0;
        } else { // Add the character to the current word
            words[wordCount][charIndex] = currentChar;
            ++charIndex;
        }

        ++wordIndex;
    }
    // Terminate the last word
    words[wordCount][charIndex] = '\0';
    ++wordCount;
}

int render(int lineLength, istream& inf, ostream& outf) {
    
    int return_val = 0; // return value variable
    
    if (lineLength < 1) { // returns 2
        return 2;
    }
    
    char text[10000]; // input text variable
    int i = 0;
    char c;
    while (inf.good()){ // gets the input file character by character and places it in a c string text
        c = inf.get();
        text[i] = c;
        i++;
    }
    text[i+1] = '\0';
    
    const int j = i;
    char processedtext[j+1];
    int processedtextCounter = 0;
    int maxWordLen = 0;
    int wordLen = 0;
    for (int i = 0; text[i] != '\0'; i++){ // iterates through the input text to process it
        if (wordLen > maxLineLength){ // adds a space between a word if it is longer than the linelength
            processedtext[processedtextCounter] = ' ';
            processedtext[processedtextCounter+1] = text[i];
            wordLen=1;
            processedtextCounter++;
        }
        else if (((isspace(text[i])) and !(isspace(processedtext[processedtextCounter-1]))) or !(isspace(text[i]))){ // adds all other characters to a string
            processedtext[processedtextCounter] = text[i];
            processedtextCounter++;
        }
        
        if (isspace(text[i])){ // checks for spaces to track word length
            if (wordLen > maxWordLen){
                maxWordLen = wordLen;
            }
            wordLen = 0;
        }
        else if (text[i] == '-'){ // adds a space after every hyphen to separate it into two words to not have a wordPortions function
            processedtext[processedtextCounter] = ' ';
            processedtextCounter++;
        }
        else {
            wordLen++;
        }
    }
    
    int numSpaces = 0;
    int numHyphens = 0;
    for (int i = 0; i < strlen(processedtext); i++){ // to count the number of hyphens and spaces in the string
        if (isspace(processedtext[i])){
            numSpaces++;
        }
        else if (processedtext[i] == '-'){
            numHyphens++;
        }
    }

    int numOfWords = numSpaces+1; // number of word portions in the string
    char words[numOfWords][2*maxLineLength];
    getWords(processedtext, words);
    
    char paraBreak[4] = "@P@";
    int paraCount = 0;
    for (int i = 0; i < numOfWords-1; i++){
        if (strlen(words[i])>maxLineLength){ // handles the return 1 case
            return_val=1;
        }
        if ((strcmp(words[i], paraBreak)==0) and (strcmp(words[i-1], paraBreak)!=0) and (i!=0) and (i!=numOfWords)){ // counts the number of para breaks in the string
            paraCount++;
        }
    }
    
    int lineCharacters = 0;
    for (int i = 0; i < numOfWords-paraCount; i++){ // renders the words 2d c string into the outfile
        if ((strcmp(words[i], paraBreak) == 0) and (strcmp(words[i-1], paraBreak)!=0) and (i!=0) and (i!=numOfWords) and (words[i-1][strlen(words[i-1])-1]!='-')){ // handles the para breaks
            cout << i << endl;
            outf << endl << endl;
            lineCharacters = 0;
        }
        
        if (strlen(words[i])+lineCharacters < lineLength){ // checks if the word can fit on the given line
            if ((words[i-1][strlen(words[i-1])-1] != '-') and (lineCharacters != 0) and (strcmp(words[i-1], paraBreak)!=0)){ // checks if a space should be printed before the word
                outf << " ";
                lineCharacters++;
            }
        }
        else { // goes to the next line if not
            outf << endl;
            lineCharacters = 0;
        }
        
        if (((words[i-1][strlen(words[i-1])-1] == '!') or (words[i-1][strlen(words[i-1])-1] == '.') or (words[i-1][strlen(words[i-1])-1] == '?') or (words[i-1][strlen(words[i-1])-1] == ':')) and (i!=numOfWords-1) and (lineCharacters!=0)){ // handles the double space after a punctuation case
            outf << " ";
            lineCharacters++;
        }
        
        if (strcmp(words[i], paraBreak)!=0){ // renders the word to the outfile
            outf << words[i];
            lineCharacters += strlen(words[i]);
        }
        
    }
    outf << endl;
    
    return return_val;
}

int main () {
    
    ifstream infile ("/Users/devanshmishra/Desktop/Top of the food chain/Devansh/UCLA/Classes/CS31/Projects/Project5/Project5/data.txt");
    ofstream outfile("/Users/devanshmishra/Desktop/Top of the food chain/Devansh/UCLA/Classes/CS31/Projects/Project5/Project5/results.txt");
    
    cout << render(maxLineLength, infile, outfile) << endl;
}
