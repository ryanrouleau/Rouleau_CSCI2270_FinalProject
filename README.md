# CSCI2270-final-project
## Summary
This project uses libcurl to log into oncampus.colorado.edu, store each word from the raw html in a linked list, find the dining balance for the user, caluclate some fun things with the data, and display it all in a neatly formatted terminal output.  This will solve the cumbersone nature of navigating to the actual site and having to make several clicks for a small amount of information that is accessed frequently.  

## How to Run
After the git repository is downloaded, the user should cd into the directory and run the following compile command:

g++ -std=c++11 *.cpp -o a.out -lcurl

Once compiled, you can run as normal with ./a.out if you have the classic freshman 19/15 swipe per week meal plan, or you can run with an already downloaded html file with the command line argument 'test'. (this would look like: ./a.out test)

## Dependencies
If running on the cs vm or OSX, then all dependencies should already be installed.  However, if you have any issues, note that the libraries used were: iostream, sstream, ctime, unistd.h, curl/curl.h, and fstream. 

## System Requirements
Unix based OS like the cs vm, or OSX.  Will not compile on windows due to getpass() not being available.  

## Group Members
N/A - none

## Contributors
N/A - none

## Open Issues/Bugs
If your meal plan is different than the one described above, then the program may crash.

