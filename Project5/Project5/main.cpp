#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <stdio.h>
using namespace std;

const int maxLineLength = 5;

int render(int lineLength, istream& inf, ostream& outf);
void getWords(char* text, char words[][maxLineLength], int& maxLenWord);
void getWordPortions(char words[][maxLineLength], char wordPortions[][maxLineLength], int& numHyphens, int& numSpaces);

void getWordPortions(char words[][maxLineLength], char wordPortions[][maxLineLength], int& numHyphens, int& numSpaces) { // gets the wordPortions from words
    int hyphenCounter = 0;
    for (int i = 0; i < (numSpaces+numHyphens); i++){ // iterating through the length of wordPortions
        
        if (strchr(words[i], '-') != nullptr){ // the word contains more than one portion
            
            char wordWithHyphens[numHyphens][maxLineLength];
            int portions = 0;
            
            while (strchr(words[i], '-') != strrchr(words[i], '-')){ // checking if the pointer to the last and first hyphen is the same or not (if the word has more than one hyphen)
                strncpy(wordWithHyphens[portions], words[i], strlen(words[i]) - strlen(strchr(words[i], '-')+1)); // copies the section of the word until and including the first hyphen
                strcpy(strrchr(words[i],'-')-strlen(wordWithHyphens[portions]), strrchr(words[i], '-')); // deletes the copied section of the word by moving the remaining section of the word forward in the array
                portions++;
                hyphenCounter++;
            }
            strcpy(wordWithHyphens[portions+1], strchr(words[i], '-')+1); // handles the one hyphen case
            strncpy(wordWithHyphens[portions], words[i], strlen(words[i])-strlen(strchr(words[i],'-'))+1);
            hyphenCounter++;
            
            for (int j = 0; j <= portions+1; j++) { // copies the portions in wordWithHyphens to wordPortions
                strcpy(wordPortions[i+j], wordWithHyphens[j]);
            }
            i += portions+1;
        }
        else { // the word contains one portion
            strcpy(wordPortions[i+hyphenCounter], words[i]);
        }
    }
}

void getWords(char* text, char words[][maxLineLength], int& maxLenWord) { // gets the words from the text
    /*
    char word[maxLenWord]; // dummy variable for a given word
    int posInWord = 0;
    int wordNum = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (!(isspace(text[i]))){
            word[posInWord] = text[i];
            posInWord++;
        }
        else {
            strcpy(words[wordNum], word);
            memset(word, 0, strlen(word));
            posInWord = 0;
            wordNum++;
        }
     }
     */
    
    int posCount = 0;
    int wordCount = 0;
    for (int i = 0; i < strlen(text); i++){
        if (!isspace(text[i])){
            words[wordCount][posCount] = text[i];
            posCount++;
        }
        else {
            words[wordCount][posCount] = '\0';
            posCount = 0;
            wordCount++;
        }
    }
    
    for (int i = 0; i <= wordCount; i++){
        cout << words[i] << endl;
    }
    
}

int render(int lineLength, istream& inf, ostream& outf) {

    
    if ((lineLength < 1) or (lineLength > 250)) {
        return 2;
    }
    
    char text[10000];
    char c;
    
    int return_val = 0;
    int i = 0; // character counting variable
    int numSpaces = 1;
    int numHyphens = 0;
    int wordsLenMoreThanMax = 0;
    int lenWord = 0;
    int maxLenWord = 0;
    while (inf.get(c)){ // iterating through the file character by character
        text[i] = c;
        if (isspace(c)){
            numSpaces++;
            
            if (numSpaces > 1) { // fixing counting error
                lenWord--;
            }
            
            if (lenWord > maxLineLength) {
                wordsLenMoreThanMax++;
            }
            
            if (lenWord > maxLenWord) {
                maxLenWord = lenWord;
                return_val = 1;
            }
            lenWord = 0;
        }
        else if (c == '-'){
            numHyphens++;
        }
        lenWord++;
        i++;
    }
    
    char words[numSpaces][maxLineLength];
    getWords(text, words, maxLenWord);
    
    /*
    int wordPortionsLen = numSpaces+numHyphens;
    char wordPortions[wordPortionsLen][maxLineLength];
    getWordPortions(words, wordPortions, numHyphens, numSpaces);
    
    for (int i = 0; i < wordPortionsLen+1; i++) {
        cout << wordPortions[i] << endl;
    }
    
    // outfile rendering
    char paraBreak[4] = "@P@";
    for (int i = 0; i < wordPortionsLen; i++){
        
        if ((strcmp(wordPortions[i], paraBreak) and ((i != 0) or (i != wordPortionsLen)))){
            outf << endl << endl;
        }
        
        int lineCharacters = 0;
        
        if (strlen(wordPortions[i])+lineCharacters < lineLength) {
            outf << wordPortions[i];
        }
        else {
            outf << endl << wordPortions[i];
        }
        lineCharacters += strlen(wordPortions[i]);
        if (!(strlen(wordPortions[i+1])+lineCharacters > lineLength)) {
            outf << " ";
            char *lastChar = wordPortions[i]+strlen(wordPortions[i]);
            if ((*lastChar == '.') or (*lastChar == '!') or (*lastChar == '?') or (*lastChar == ':')){
                outf << " ";
            }
        }
    }
     */
    return return_val;
}

int main()
{
    ifstream infile("/Users/devanshmishra/Desktop/Top of the food chain/Devansh/UCLA/Classes/CS31/Projects/Project5/Project5/data.txt");
    ofstream outfile("/Users/devanshmishra/Desktop/Top of the food chain/Devansh/UCLA/Classes/CS31/Projects/Project5/Project5/results.txt");
    
    cout << render(maxLineLength, infile, outfile) << endl;
    
    return 0;
}
