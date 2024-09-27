#include "Bar.h"

// Name: Bar (Default Constructor) (not used)
// Desc: Dynamically allocates m_data for strings (always). m_fileName defaults to test.txt
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
Bar::Bar(){
    m_fileName = "test.txt";
     m_data = new LL<string>();
}
// Name: Bar (Overloaded Constructor)
// Desc: Used to pass an input file
//       Dynamically allocates m_data for strings (always)
//       Sets m_fileName and nothing done with m_dataSorted until SortData
// Preconditions: Input file
// Postconditions: m_data is allocated, m_fileName populated

Bar::Bar(string filename){
    m_fileName = filename;
    m_data = new LL<string>(); 
}
// Name: ~Bar (Destructor)
// Desc: Deallocates m_data
// Preconditions: m_data has been dynamically allocated
// Postconditions: m_data is empty
Bar::~Bar (){
    delete m_data;
}
// Name: Start
// Desc: Calls LoadFile, RemoveCommon, RemoveSingles, Sort, DisplayBars, and Export
//       During testing, may want to call Display
// Preconditions: None (filename is available)
// Postconditions: None
void Bar::Start(){
    LoadFile();
    RemoveCommon();
    RemoveSingles();
    SortData();
    DisplayBars();
    Export();
}
// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything stringlike)
//       Calls RemovePunct as each item is loaded
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_data is populated
void Bar::LoadFile(){
    cout << "Load file runs" << endl;
    string word;
    int count = 0;
    ifstream inputStream;
    //open file
    inputStream.open(m_fileName);
    //while there is a word keep taking it in and remove its punctutation and add it to linked list
    while(inputStream >> word){
        RemovePunct(word);
        m_data->Insert(word);
        count++;
    }
    cout << count << " loaded" << endl;
    inputStream.close();
}
// Name: RemovePunct (passed a string)
// Desc: Converts all input into lowercase using tolower
//       When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
//       You can use ispunct - https://www.geeksforgeeks.org/ispunct-function-c/
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void Bar::RemovePunct(string& words){
    //make string lowercase
    for(string::iterator it = words.begin(); it != words.end(); it++){
        *it = tolower(*it);
    }
    //remove punctuation at the bginning of the string
    for(string::iterator p = words.begin(); p != words.end(); ++p){
        if(ispunct(*p) && (p == words.begin())){
            words.erase(p);
        }
        //remove at the end
        else if(ispunct(*p) && (*p == words.back())){
            words.pop_back();
            return;
        }
    }
}
// Name: RemoveCommon
// Desc: Asks user if they want to remove common words
//       If yes, iterates through m_data and removes all common words after they are read
// Preconditions: m_data is populated and EXCLUDE_LIST is populated
// Postconditions: m_data will have no words from EXCLUDE_LIST
void Bar::RemoveCommon(){
    string choice;
    //lower input so any variation of yes and no works
    //validate the input
    do{
        cout << "Would you like to remove all common words (Only use with essays) ?" << endl;
        cin >> choice;
        for(string::iterator it = choice.begin(); it != choice.end(); it++){
            *it = tolower(*it);
        }
        //go through vector to delete any words in linked list that are in the vector
        if (choice == "yes"){
            for(vector<string>::const_iterator p = EXCLUDE_LIST.begin(); p != EXCLUDE_LIST.end(); ++p){
                m_data->RemoveAt(*p);
            }
            cout << "All common words removed." << endl;
            return;
        }
        else if(choice == "no"){
            return;
        }
        else{
            cout << endl;
        }
    }while(choice != "yes" || choice != "no");
}

// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_data is a pointer!
// Preconditions: m_data is populated
// Postconditions: m_data will have no words with a frequency of 1
void Bar::RemoveSingles(){
    string choice;
    int count = 0;
    do{
        cout << "Would you like to remove all words with a frequency of 1?" << endl;
        cin >> choice;
        for(string::iterator it = choice.begin(); it != choice.end(); it++){
            *it = tolower(*it);
        }
        if (choice == "yes"){
            //dereference m_data and access it's frequency to check if it's one in order 
            //to remove that node
            for (int i = 0; i < m_data->GetSize(); i++){
                if ((*m_data)[i].second == 1){
                    m_data->RemoveAt((*m_data)[i].first);
                    count++;
                    i--;
                }
            }
            cout << count << " words removed." << endl;
            return;
        }
        else if(choice == "no"){
            return;
        }
        else{
            cout << endl;
        }
    }while(choice != "yes" || choice != "no");

}
// Name: SortData
// Desc: Iterates through each items in m_data and inserts into
//       m_dataSorted using the frequency as the key (can use make_pair)
// Preconditions: m_data is populated
// Postconditions: m_dataSorted is populated and sorted based on frequency
void Bar::SortData(){
    //go through the linked list and add it to the multimap in order of frequency
    for (int i = 0; i < m_data->GetSize(); i++){
        m_dataSorted.insert(make_pair((*m_data)[i].second, (*m_data)[i].first));
    }
}
// Name: DisplayBars
// Desc: Displays a bar chart for each item in m_dataSorted from highest
//       frequency (at the top) to lowest frequency (at the bottom) (iterate backwards)
// Preconditions:  m_dataSorted is populated
// Postconditions: Bar charts are displayed
void Bar::DisplayBars(){
    //reverse throught the multimap and cout the * to represent frequency
    for (multimap<int, string>::reverse_iterator rp = m_dataSorted.rbegin(); rp != m_dataSorted.rend(); rp++){
        cout << setw(15) << rp->second << ": ";
        for (int i = 0; i < rp->first; i++){
            cout << barChar;
        }
        cout << endl;
    }
    return;
}
// Name: Export
// Desc: Asks the user what name the export file should be called
//       Iterates through m_dataSorted and exports to file
// Preconditions: m_dataSorted is populated
// Postconditions: New export file is created and populated with a formatted bar chart
void Bar::Export(){
    string filename;
    //checks that a string is entered
    do{
        cout << "What would you like to call the export file?" << endl;
        cin >> filename;
    }while (filename.size() < 1);

    cout << "Output to exportFile " << filename << endl;

    //write onto a new file the multimap display
    ofstream outputStream;

    outputStream.open(filename);

    for (multimap<int, string>::reverse_iterator rit = m_dataSorted.rbegin(); rit != m_dataSorted.rend(); rit++){
        outputStream << setw(15) << rit->second << ": ";
        for (int i = 0; i < rit->first; i++){
            outputStream << barChar;
        }
        outputStream << endl;
    }
    
    outputStream.close();
    return;
}