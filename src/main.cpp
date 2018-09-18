#include <vector>
#include <string>
#include <iostream>
using namespace std;

/**
 * Author: Lucas Saraiva
 * Problem: Crosswords
 * Method: Backtrack
 **/

static bool solved = false;
static std::vector<string> result;


std::vector<string> tryVertical(std::vector<string> matrix,
                                unsigned int row,
                                unsigned int colum,
                                string wordToBePlaced,
                                unsigned int wordLenght){

    unsigned int posRow = 0;
    for (unsigned int i = 0; i < wordLenght; i++) {
        posRow = row +i;
        if (matrix[posRow][colum] == '-' || matrix[posRow][colum] == wordToBePlaced[i])
            matrix[posRow][colum] = wordToBePlaced[i];
        else {
            matrix[0][0] = '&';
            return matrix;
        }
    }
    return matrix;
}


std::vector<string> tryHorizontal(std::vector<string> matrix,
                                  unsigned int row,
                                  unsigned int colum,
                                  string wordToBePlaced,
                                  unsigned int wordLenght){

    unsigned int posColum = 0;
    for (unsigned int i = 0; i < wordLenght; i++) {
        posColum = colum + i;
        if (matrix[row][posColum] == '-' || matrix[row][posColum] == wordToBePlaced[i])
            matrix[row][posColum] = wordToBePlaced[i];
        else {            
            matrix[0][0] = '&';
            return matrix;
        }
    }    
    return matrix;
}

//Np-Complete reference: http://www-imai.is.s.u-tokyo.ac.jp/~seta/paper/senior_thesis/seniorthesis.pdf
void solvePuzzle(vector<string> words,
                 vector<string> matrix,
                 int index,
                 unsigned int n){

    if(solved){
        return;
    }
    if (index != -1) {
        string wordToBePlaced = words[index];
        int spacesToTry = n-wordToBePlaced.length();
        std::vector<string> temp;
       
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = 0; j <= spacesToTry; j++) {
                temp= tryHorizontal(matrix, i, j, wordToBePlaced , wordToBePlaced.size());
                if (temp[0][0] != '&')
                    solvePuzzle(words, temp, index - 1, n);
            }
        }
        
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = 0; j <= spacesToTry; j++) {
                temp = tryVertical(matrix, j, i,wordToBePlaced , wordToBePlaced.size());
                if (temp[0][0] != '&')
                    solvePuzzle(words, temp, index - 1, n);
            }
        }
    }
    else {        
        result = matrix;
        solved = true;
        return;
    }
}


int main(void){
  
    std::vector<string> matrix,words;
   
    int n = 10; //size of matrix

    matrix.push_back("-+++++++++");
    matrix.push_back("-+---+++++");
    matrix.push_back("-+++++-+++");
    matrix.push_back("--++++--+-");
    matrix.push_back("-++-++-++-");
    matrix.push_back("-++-+-+++-");
    matrix.push_back("-++-+++++-");
    matrix.push_back("-++-+++++-");
    matrix.push_back("-++-+++++-");
    matrix.push_back("+++-++++++");
    
    words.push_back("12345");
    words.push_back("DA");
    words.push_back("ABCDFGRTY");
    words.push_back("24");
    words.push_back("ca");

    solvePuzzle(words, matrix, words.size()-1, n);

    cout << "Solution" <<endl;
    for (unsigned int i = 0; i < 10; i++)
        cout << result[i] << endl;


    return 0;
}
