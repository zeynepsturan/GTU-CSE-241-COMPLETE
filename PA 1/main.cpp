
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

//function declarations
void readAlphabet(char alphabet[], int& usedSize); //reads alphabet.txt to form an alphabet
void printAlphabet(char alphabet[], int usedSize); //prints the alphabet in the given format

void generateWord(char alphabet[], int usedSize, string& secret); //generates the secret word using the alphabet
bool guess(char alphabet[], int usedSize, int wordLength, string secret); //allows user to make guesses and checks them

bool isWordValid(char alphabet[], int usedSize, string secret); //checks if the user entered secret word or the guessed word is valid for the given alphabet
bool isValidNumber(string n); //checks if the command-line argument(-r n) word length n is valid

void gameplay(char alphabet[], int usedSize, int wordLength, string secret); //wrapper function for the game play
void errorFound(); //prints an error message and ends the program

// must be global to be used within the functions
const int NUM_OF_MAX_GUESSES=100; //player can guess 100 times at most


int main(int argc, char *argv[]){
    
    const int CHAR_LENGTH=255; //char range is 0-255

    const char* RANDOM_GEN_ARG = "-r"; //constant for argument -r 
    const char* USER_ENTER_ARG = "-u"; //constant for argument -u

    char alphabet[CHAR_LENGTH]; //the array where the alphabet is stored
    int alphabetSize; //the real used size of the alphabet array which is partially filled
    
    string secret; //the secret word
    int secretLength; //length of the secret word given as a command-line argument
    
    bool isArgsValid=false; //check flag for command-line arguments. default is false

    srand(time(NULL)); //for random number generation takes the current time as the seed
    readAlphabet(alphabet, alphabetSize); //reads alphabet.txt to form the alphabet

    if(alphabetSize<=0){ //if the alphabet is empty the program cannot work
        errorFound();
    }

    printAlphabet(alphabet, alphabetSize);  //program first prints the alphabet to the user

    //ALL THE CHECKS FOR A VALID COMMAND-LINE ARGUMENT
    if(argc==3){ //number of arguments must be 3
        
        //if the mode is -r, the next arguement must be a positive intiger and less than the alphabet size
        //since the secret word cannot have repeating characters
        if(static_cast<string>(argv[1])==RANDOM_GEN_ARG && isValidNumber(argv[2]) && stoi(argv[2])<=alphabetSize){
            isArgsValid=true;
            secretLength=stoi(argv[2]); //length of the secret word is the argument after -r
        }

        else if(static_cast<string>(argv[1])==USER_ENTER_ARG){ //if the mode is -u, we take the next argument as the secret word
            secret=argv[2]; //secret word is the argument after -u

            if(isWordValid(alphabet, alphabetSize, secret)){ //if the user entered secret word is fully formed from the alphabet and does not have repeating characters
                isArgsValid=true;
            }
        }
        
    }

    if(!isArgsValid){   //if the arguments are not somehow valid
        errorFound();
    }
    
    if(static_cast<string>(argv[1])==RANDOM_GEN_ARG){ //if the mode is -r, secret word is randomly generated
        secret.resize(secretLength); //first the secret string is resized correctly to avoid extra resizings 
        generateWord(alphabet, alphabetSize, secret); //the word is generated and assigned to the secret word
    }

    gameplay(alphabet, alphabetSize, secretLength, secret); //game starts

    return 0; //program ends
}

void errorFound(){
    cout<<"INPUT ERROR"<<endl;    //prints error message then exits the program
    exit(1); //program ends
}

//wrapper function for the game play
void gameplay(char alphabet[], int usedSize, int wordLength, string secret){

    bool isFound=false;     //check flag for if the secret word is guessed correctly

    for(int i=1; i<=NUM_OF_MAX_GUESSES; i++){ //while the user has right to guess
        
        isFound=guess(alphabet, usedSize, wordLength, secret); //the function guess checks if the guess is correct
        
        if(isFound){ //if the secret word is found
            cout<<"FOUND "<<i<<endl; //the user is informed
            break;
        }
    }

    if(!isFound){ //if the user ran out of guesses and could not predict the word correctly
        cout<<"FAILED"<<endl; //the user is informed
    }
}

//checks if the command-line argument(-r n) word length n is valid
bool isValidNumber(string n){
    int size=n.size(); //size of the string n

    for(int i=0; i<size; i++){ //checks every character of the string n to see if they are digits
        if(!isdigit(n[i])) //if it is not a digit then it is not valid
            return false;
    }

    if(stoi(n)==0) //the number cannot be 0
        return false;
    return true;
}

//checks if the user entered secret word or the guessed word is valid for the given alphabet
bool isWordValid(char alphabet[], int usedSize, string secret){
    bool isValid=false; //flag for validation of the secret word

    for(int i=0; i<secret.size(); i++){ //checks each character of the secret word
        
        isValid=false;

        for(int j=i+1; j<secret.size(); j++){ //iterates through the secret word to check for repetition

            if(secret[i]==secret[j]){ //if repetition is found
                return false;
            }
        }

        for(int j=0; j<usedSize; j++){ //loop iterates through the alphabet to check if the secret word is formed of the alphabet

            if(secret[i]==alphabet[j]){ //if the current character exists in the alphabet validation is true
                isValid=true;
            }
        }

        if(!isValid){ //if the secret word is not valid
            return isValid;
        }
    }
    return true;
}

//generates the secret word using the alphabet
void generateWord(char alphabet[], int usedSize, string& secret){
    int secret_size=secret.size(); //size of the secret
    int random; //holds the random generated number

    char c; //holds the character alphabet[random]
    bool doesExist; //checks if the random generated character already exist in the secret

    for(int i=0; i<secret_size; i++){ //generates each character of the secret

        random=rand()%usedSize; //generates a random number between 0-usedSize-1
        c=alphabet[random]; //chooses a character from alphabet and asignes to c
        doesExist=false;

        for(int j=0; j<i; j++){ //checks if c already exists in secret word

            if(secret[j]==c){ //if c exists in secret word
                doesExist=true;
                i--; //prevents increasing i because secret[i] has not filled yet
            }
        }

        if(!doesExist){
            secret[i]=c; //secret[i] is filled with c
        }
    }
}

//prints the alphabet in the given format
void printAlphabet(char alphabet[], int usedSize){

    cout<<"["<<alphabet[0]; //prints an open brace and the first character

    for(int i=1; i<usedSize; i++){ //iterates through the alphabet and prints the rest of the alphabet seperated by commas
        cout<<","<<alphabet[i];
    }

    cout<<"]"<<endl; //prints a close brace
}

//reads alphabet.txt to form an alphabet
void readAlphabet(char alphabet[], int& usedSize){

    ifstream input; //input stream for alphabet.txt
    char c; //variable to store chars from the file
    bool flag; //true if c doesn't already occur in the alphabet, false if it does
    usedSize=0; //initializes the alphabet size to 0

    input.open("alphabet.txt"); //opens the alphabet file

    if(!input.is_open()){   //if the file could not be opened
        errorFound();
    }

    //the loop reads the file char by char to check them individually
    while(input>>c && c!=EOF){ //while the file isn't empty or hasn't been finished reading
                         
        if(c==',' || isspace(c)){ //ignores commas and spaces
            continue;
        }

        flag=true; //default value is true

        for(int i=0; i<usedSize; i++){ //iterates through the alphabet to check for repetitions
            
            if(alphabet[i]==c){ //if c already occurs in the alphabet we won't add it again
                flag=false;
                break;
            }
        }

        if(flag){ //if c doesn't occur in the alphabet
            alphabet[usedSize]=c; //adds c in alphabet
            usedSize++; //increases alphabet size
        }

    }

    input.close(); //closes the alphabet.xt
}

//allows user to make guesses and checks them
bool guess(char alphabet[], int usedSize, int wordLength, string secret){
    
    string guess; //users guess
    bool isFound=false; //flag for if the secret is found
    bool isValid=false; //flag for if the guessed word has characters other than the alphabet
    int exact=0; //number of guessed characters that is in the secret word and in the correct place
    int misplaced=0; //number of guessed characters that is in the secret but misplaced

    cin>>guess; //takes user guess

    if(guess.size()!=secret.size()){ //if the guess word's length differs from the secret's word length
        errorFound();
    }

    if(guess==secret){ //if user guesses the word right 
        isFound=true; //isFound flag is true so program knows that guess is right
    }

    else{ //the guess is not correct so program processes the guessed word

        //checks if guess is valid
        isValid=isWordValid(alphabet, usedSize, guess);

        if(!isValid){ //if the guess is not valid
            errorFound();
        }

        //checks if guess is true
        for(int i=0; i<secret.size(); i++){ //checks each character of guessed word to calculate hints and point out errors

            if(guess[i]==secret[i]){ //if the character exists in the secret word and it's in the right place
                exact++;
            }

            else{ //if the character exists is in the secret word but misplaced
                for(int j=0; j<secret.size(); j++){ //iterates through the secret

                    if(guess[i]==secret[j] && i!=j){ //if the character found but it's place is different
                        misplaced++;
                        break;
                    }
                }
                
            }
        }
        cout<<exact<<" "<<misplaced<<endl; //prints the hints
    }
    return isFound; //returns true if the guess is correct, false if it is not
}
