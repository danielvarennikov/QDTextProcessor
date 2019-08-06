# QDTextProcessor
Quick and Dirty Text processor

A simple text file processor.

readFile(/path/) -> prints the lines of the file in a numbered order.

writeToFileAppend(/path/,/message/) -> appends a message to the end of the file.

modifyFile(/path/,/lineToChange/,/toInsert/) -> inserts a line instead of the chosen line.

grep(/path/,/expression/) -> prints all the lines with the chosen expression.

spellchecker(/path/) -> checks words in your file and checks the dictionary(has 59000 words in it) for matches. If it finds a mismatch(the word doesn't appear in the dictionary) it prints it.
