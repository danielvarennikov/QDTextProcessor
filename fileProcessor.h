#ifndef FILEPROCESSOR_H_INCLUDED
#define FILEPROCESSOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void readFile(char* path){

  string line;
  ifstream myfile;
  myfile.open(path);
  if (myfile.is_open()) {
    int i = 0;
    while(getline(myfile, line)) {
      cout <<i<<'\t'<< line << endl;
    i = i + 1;
    }
    myfile.close();
  }else{
      cout<<"Wrong path to file"<<endl;
  }

}

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

void modifyFile(char* path,int lineToChange,string toInsert){

  //Transfer the file into a string
  //Replace the line in the string with the line we want
  //Write the String back to the file
  string line;
  ostringstream toModify;
  ifstream myfile;
  myfile.open(path);
  if (myfile.is_open()) {
    int i = 0;
    while(getline(myfile, line)) {

    //The $ sign is the indicator of a new line
    toModify<<'$'<< i << '\t' << line<<'\n';
    string query(toModify.str());
    i = i + 1;
    }
    myfile.close();
  }else{
      cout<<"Wrong path to file"<<endl;
  }

  //The modified string
  string modified = toModify.str();
  int counter = 0;

  //The char where the replacement begins
  int begins = 0;
  for(int i = 0;i<modified.length() && counter <= lineToChange;i = i + 1){
    if(modified.at(i) == '$'&& modified.at(i + 1) == ((char)('0'+counter ))){
        counter = counter + 1;
    }

    begins = begins + 1;
  }

    begins = begins + 2;

    //Find out where the line ends
    int ends = begins;
    while(modified.at(ends) != '$' && ends < modified.length() - 1){
        ends = ends + 1;
    }
    //Erase the line we want to change
    modified.erase(begins, ends - begins - 1);

    //Insert the line we watt instead
    modified.insert(begins,toInsert);

    //Insert the modified string into the text file
    ofstream myFileModified;
    myFileModified.open(path);
    if (myFileModified.is_open()) {
    int currentChar = 0;
    while(currentChar < modified.length() - 1){
        if(modified.at(currentChar) == '$' && isdigit(modified.at(currentChar + 1))){
            currentChar = currentChar + 3;
        }else{
            myFileModified<<modified.at(currentChar);
            currentChar = currentChar + 1;
        }
    }
    myFileModified.close();
    }else{
      cout<<"Couldn't open file"<<endl;
    }

}


#endif // FILEPROCESSOR_H_INCLUDED
