# include <iostream> // in/out functions like cout
# include <string> // library to work with strings
# include <fstream> // library to work with files
# include <vector>

using namespace std;

string verify(string guess, string chosen_word, vector <char> &mistakes_array) {
    char common;
    string palavra(5, '*');  // initialize the word to be shown to the user as "*****"

    // compare the letters
    for(int a = 0; a < 5; a++){
        common = '*';
        for(int b = 0; b < 5; b++){
            if(guess[a] == chosen_word[b]){
                common = (a == b) ? guess[a] : tolower(guess[a]); // if the correct letter is in the right place, it will be upper; if the correct letter is in the wrong place, it will be lower case
                break;
            }
            // verifing if the mistakes_array already contains the character and appending it if not
            else{
                if (b == 4){
                    int add_char = 1;
                    for (int i = 0; i < mistakes_array.size(); i++) {
                        if (mistakes_array[i] == guess[a]){
                            add_char = 0;
                            break;
                        } 
                    }
                    if (add_char) mistakes_array.push_back(guess[a]);
                }
            }
        }
        palavra[a] = common;
    }
    return palavra;
}

void check(string output, string chosen_word, int tries, bool &finish){
    if(output == chosen_word){
        cout << "GANHOU!";  
        finish = true;
    }else{
        if(tries == 4){
            cout << "PERDEU! " << chosen_word;
        }
    }
}

int main(){
    
    ifstream words_file ("words.txt"); // Input File STREAM
    // checking if the file was correctly oppened
    if (!words_file){
        cerr << "Error oppening the file" << endl;  // Console ERRor (standard error stream). writes immediately without buffering
        return 1; // Exit with error code
    }
    
    // reading the key word from the user
    int key;
    cin >> key;
    
    // looping through the file and saving the key'th one in the chosen_word variable
    string chosen_word;
    for(int i = 0; i<key; i++){
        getline(words_file, chosen_word);
    }
    chosen_word.erase(chosen_word.find_last_not_of(" \n\r\t") + 1); // trimming white spaces after reading the word
    
    int tries = 0;
    bool finish = false;
    vector <char> mistakes_array;
    mistakes_array.reserve(25); // reserving 25 positions (5 tries x 5 letters)
    
    while(tries < 5 && finish == false){
        string guess;
        cin >> guess;
        
        string output = verify(guess, chosen_word, mistakes_array);
        cout << output << ' ';
        
        // showing the letters that don't belong to the word
        cout << '(';
        for (int i = 0; i < mistakes_array.size(); i++) {
            cout << mistakes_array[i];
        }
        cout << ')' << endl;
        
        check(output, chosen_word, tries, finish);
        
        tries ++;
    }
    words_file.close();
    return 0;
}
