#ifndef FILEPROCESSOR_H_INCLUDED
#define FILEPROCESSOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

//read the file as it is
void readFile(char* path){

  string line;
  ifstream myfile;
  ostringstream getLine;
  string text;
  myfile.open(path);
  if (myfile.is_open()) {

    //Transfer the file to a string so that we can work with it
    while(getline(myfile, line)) {
        getLine<<line;
        string query(getLine.str());
    }
    myfile.close();
  }else{
      cout<<"Wrong path to file"<<endl;
  }

  //Our file as a string
  text = getLine.str();

  ostringstream regularExpression;
  regularExpression<<"[^.]*[.]{1}+";
  string query(regularExpression.str());
  string regularExpressionFinal = regularExpression.str();
  regex r(regularExpressionFinal);
  auto words_begin = sregex_iterator(text.begin(), text.end(), r);
  auto words_end = sregex_iterator();
  int counter = 0;

    //Iterate through all the found matches
    //Each line has its indicator number
    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        string match_str = match.str();
        cout <<counter<<'\t'<< match_str << endl;
        counter = counter + 1;
    }

}

//append text to the file
void writeToFileAppend(char* path,char* message){
  string line;
  ofstream myfile;
  myfile.open(path,ios_base::app);
  if (myfile.is_open()) {

    //Get to the end of the file
    myfile<<message<<endl;
    myfile.close();
  }else{
      cout<<"Wrong path to file"<<endl;
  }

}


//change a line
void modifyFile(char* path,int lineToChange,string toInsert){

  //Transfer the file into a string
  //Replace the line in the string with the line we want
  //Write the String back to the file
  string line;
  ostringstream toModify;
  ifstream myfile;
  string text;
  myfile.open(path);
  if (myfile.is_open()) {

    //Transfer the file to a string so that we can work with it
    while(getline(myfile, line)) {
        toModify<<line;
        string query(toModify.str());
    }
    myfile.close();
  }else{
      cout<<"Wrong path to file"<<endl;
  }
  string tempText = toModify.str();
  ostringstream regularExpression;
  regularExpression<<"[^.]*[.]{1}+";
  string query(regularExpression.str());
  string regularExpressionFinal = regularExpression.str();
  regex r(regularExpressionFinal);
  auto words_begin = sregex_iterator(tempText.begin(), tempText.end(), r);
  auto words_end = sregex_iterator();
  int counter = 0;
  ostringstream toModify2;
    //Iterate through all the found matches
    //Each line has its indicator number
    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        string match_str = match.str();
        toModify2<<'$'<<counter<<'\t'<<match_str<<endl;
        string query(toModify2.str());
        counter = counter + 1;
    }
  //The modified string
  text = toModify2.str();
  int counter2 = 0;
  //The char where the replacement begins
  int begins = 0;
  for(int i = 0;i<text.length() && counter2 <= lineToChange;i = i + 1){
    if(text.at(i) == '$'&& text.at(i + 1) == ((char)('0'+counter2 ))){
        counter2 = counter2 + 1;
    }

    begins = begins + 1;
  }

    begins = begins + 2;
    //Find out where the line ends
    int ends = begins;
    while(text.at(ends) != '$' && ends < text.length() - 1){
        ends = ends + 1;
    }
    //Erase the line we want to change
    text.erase(begins, ends - begins - 1);

    //Insert the line we watt instead
    text.insert(begins,toInsert);

    //Insert the modified string into the text file
    ofstream myFileModified;
    myFileModified.open(path);
    if (myFileModified.is_open()) {
    int currentChar = 0;
    while(currentChar < text.length() - 1){
        if(text.at(currentChar) == '$' && isdigit(text.at(currentChar + 1))){
            currentChar = currentChar + 3;
        }else{
            myFileModified<<text.at(currentChar);
            currentChar = currentChar + 1;
        }
    }
    myFileModified.close();
    }else{
      cout<<"Couldn't open file"<<endl;
    }

}


void grep(char* path,string expression){
//Print all the sentences containing the expression

  string line;
  ifstream myfile;
  ostringstream getLine;
  string text;
  myfile.open(path);
  if (myfile.is_open()) {

    //Transfer the file to a string so that we can work with it
    while(getline(myfile, line)) {
        getLine<<line;
        string query(getLine.str());
    }
    myfile.close();
  }else{
      cout<<"Wrong path to file"<<endl;
  }

  //Our file as a string
  text = getLine.str();

  ostringstream regularExpression;
  regularExpression<<"[^.]*"<<expression<<"[^.]*[.]{1}+";
  string query(regularExpression.str());
  string regularExpressionFinal = regularExpression.str();
  regex r(regularExpressionFinal);
  auto words_begin = sregex_iterator(text.begin(), text.end(), r);
  auto words_end = sregex_iterator();
  int counter = 0;

    //Iterate through all the found matches
    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        string match_str = match.str();
        cout <<counter<<'\t'<< match_str << endl;
        counter = counter + 1;
    }

}
#endif // FILEPROCESSOR_H_INCLUDED
