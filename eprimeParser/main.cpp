//
//  main.cpp
//  eprimeParser
//
//  Created by Harsha Srikara on 3/1/19.
//  Copyright © 2019 Harsha Srikara. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "dataHolder.hpp"

std::string getData(std::string filename);
std::string simplifyData(std::string info);
std::string splitData(std::string &total);
int getFirstNumber(std::string str);
std::string getSubjectNumber(std::string file);
int func(std::string str);

int check(std::string row,std::string wordToBeFound);

int main(int argc, const char * argv[]) {
    
    //collecting user input
    std::cout<<"Enter the filename: ";
    std::string file;
    std::getline(std::cin,file);
    
    //calls function to extract data
    std::string extractedData;
    extractedData = getData(file);
    
    //std::cout<<extractedData<<std::endl;
    std::string subjectNumber = getSubjectNumber(extractedData);
    
    //calls function to isolate relevant sections
    std::string simplfiedData;
    simplfiedData = simplifyData(extractedData);
    
    //std::cout<<simplifiedData<<std::endl;
    
    std::string first;
    std::string last;
    
    //This splits the two runs into seperate strings.
    last = splitData(simplfiedData);
    first = simplfiedData;
    
    //std::cout<<"FIRST"<<first<<std::endl;
    //std::cout<<"\n\n\n\n"<<std::endl;
    //std::cout<<"LAST"<<last<<std::endl;
    
    dataHolder firstTrial(first,subjectNumber);
    dataHolder lastTrial(last,subjectNumber);
    
    
    return 0;
    
}

std::string getData(std::string filename)
{
    //temporary variables
    std::string line; //contains line by line strings from the txt file
    std::string output; //contains the concatnation of all lines
    std::ifstream myReadFile; //input stream
    
    //opens the input stream with the txt file
    myReadFile.open(filename);
    if(myReadFile.is_open()) //checks to see if the file opened successfully
    {
        std::cout<<filename<<" successfully opened"<<std::endl;
        while(!myReadFile.eof()) // To get you all the lines. eof - end of file
        {
            std::getline(myReadFile,line); // Saves the line in line. Gets one line at a time
            //std::cout<<line; // Prints the line.  (if you want to debug)
            output = output + line + "\n";
        }
    }
    else //if file opening failed
    {
        std::cout<<filename << " failed to open"<<std::endl;
    }
    myReadFile.close(); //ends the input stream
    return output;
}

std::string simplifyData(std::string info)
{
    //converts the string into a stream of characters. Easier to go through line by line.
    std::istringstream lineFinder(info);
    std::string output = "";
    
    bool lvl4 = true;
    //cycle through all the lines in a string
    for (std::string line; std::getline(lineFinder, line);)
    {
        //extracts the very first level 4 data. This is when the participant responds to the cue.
        if(lvl4)
        {
            if(check(line,"Level: 4")!=-1)
            {
                lvl4 = !lvl4; //ensures that the extra lvl4 data does not get extracted
                /*
                while(check(line,"Procedure")==-1) //get procedure
                {
                    std::getline(lineFinder, line);
                }
                output = output + line;
                */
                while(check(line,"RatePain")==-1) //get RatePainOnset
                {
                    std::getline(lineFinder, line);
                }
                output = output + line + "\n";
            }
        }
        // This extracts each of the level 3 data sets. This contains information on when the cue is presented and removed.
        if(check(line,"Level: 3")!=-1)
        {
            lvl4 = !lvl4;
            while(check(line,"Procedure")==-1) //get Procedure
            {
                std::getline(lineFinder, line);
            }
            output = output + line+ "\n";
            while(check(line,"Hold.OnsetTime")==-1) //get CueOn
            {
                std::getline(lineFinder, line);
            }
            output = output + line+ "\n";
            while(check(line,"Off.OnsetTime")==-1) //get CueOff
            {
                std::getline(lineFinder, line);
            }
            output = output + line+ "\n";
        }
        if(check(line,"StartRun1.RTTime")!=-1)
        {
            output = output + line+ "\n";
        }
        if(check(line,"StartRun2.RTTime")!=-1)
        {
            output = output + line+ "\n";
        }
        //std::cout<<line<<std::endl; useful for debug purposes
    }
    return output;
}

std::string splitData(std::string &simplifiedData)
{
    std::istringstream lineFinder(simplifiedData);
    std::string first = "";
    std::string last = "";
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        while(check(line,"RTTime")==-1) //get first part
        {
            std::getline(lineFinder, line);
            first = first + line+ "\n";
        }
        std::getline(lineFinder, line);
        last = last + line+ "\n";
        while(check(line,"RTTime")==-1) //get second part
        {
            std::getline(lineFinder, line);
            last = last + line+ "\n";
        }
        std::getline(lineFinder, line);
        last = last + line+ "\n";
    }
    simplifiedData = first;
    return last;
}

//checks to see if one string is a substring of another string
int check(std::string row,std::string wordToBeFound)
{
    
    std::string temp;
    int i = (int)row.size()+1;
    int j = (int)wordToBeFound.size();
    int checkStart = 0;
    while((checkStart+j)<i)
    {
        temp =row.substr(checkStart,j);
        if(temp==wordToBeFound)
        {
            return checkStart;
        }
        checkStart +=1;
    }
    return -1;
}

//gets any numbers which  are part of a string
int func(std::string str)
{
    std::stringstream ss;
    
    /* Storing the whole string into string stream */
    ss << str;
    
    /* Running loop till the end of the stream */
    std::string temp;
    int found;
    while (!ss.eof())
    {
        /* extracting word by word from stream */
        ss >> temp;
        
        /* Checking the given word is integer or not */
        if (std::stringstream(temp) >> found)
        {
            return found;
        }
        /* To save from space at the end of string */
        temp = "";
    }
    return -1;
}

//gets any numbers embedded within in an alphanumeric string
int getFirstNumber(std::string str)
{
    //int num;
    for(char c:str) //for each character in str
    {
        if(isdigit(c))
        {
            return (int)c - 48; //converts ascii to int
        }
    }
    return -1;
}

std::string getSubjectNumber(std::string file)
{
    std::string subject;
    std::istringstream lineFinder(file);
    for (std::string line; std::getline(lineFinder, line);)
    {
        while(check(line,"Subject")==-1) //get first part
        {
            std::getline(lineFinder, line);
        }
        subject = line;
        break;
        
    }
    int temp = func(subject);
    if(temp/100000==0)
    {
        subject = "0" + std::to_string(temp);
    }
    else
    {
        subject = std::to_string(temp);
    }
    return subject;
}
