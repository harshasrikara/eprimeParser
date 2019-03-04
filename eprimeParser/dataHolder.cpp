//
//  dataHolder.cpp
//  eprimeParser
//
//  Created by Harsha Srikara on 3/3/19.
//  Copyright © 2019 Harsha Srikara. All rights reserved.
//

#include "dataHolder.hpp"

//Constructors
dataHolder::dataHolder() //default
{
    allData = "";
}
dataHolder::dataHolder(std::string file) //with file
{
    allData = file;
    TrialNumber = getTrialNumber(allData);
    startTime = getStartTime(allData);
}
dataHolder::dataHolder(std::string file, std::string uniqueId) //with file and 6 digit patient ID
{
    allData = file;
    uniquePatientId = uniqueId;
    TrialNumber = getTrialNumber(allData);
    startTime = getStartTime(allData);
}

int dataHolder::getTrialNumber(std::string file)
{
    std::istringstream lineFinder(file);
    std::string lastLine;
    for (std::string line; std::getline(lineFinder, line);)
    {
        while(check(line,"RTTime")==-1) //get first part
        {
            std::getline(lineFinder, line);
        }
        lastLine = line;
        return getFirstNumber(lastLine);
    }
    return -1;
}

int dataHolder::getStartTime(std::string file)
{
    std::istringstream lineFinder(file);
    std::string lastLine;
    for (std::string line; std::getline(lineFinder, line);)
    {
        while(check(line,"RTTime")==-1) //get first part
        {
            std::getline(lineFinder, line);
        }
        lastLine = line;
        return getNumber(lastLine);
    }
    return -1;
}

//const getters
int dataHolder::getTrialNumber() const
{
    return TrialNumber;
}
int dataHolder::getStartTime() const
{
    return startTime;
}
std::string dataHolder::getUniquePatientId() const
{
    return uniquePatientId;
}
std::string dataHolder::getAllData() const
{
    return allData;
}

//gets a number inside a string
int dataHolder::getNumber(std::string str)
{
    std::stringstream ss;
    /* Storing the whole string into string stream */
    ss << str;
    /* Running loop till the end of the stream */
    std::string temp;
    int found;
    while (!ss.eof()) {
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

//gets the first number within a string even if it is embedded
int dataHolder::getFirstNumber(std::string str)
{
    for(char c:str) //for each character in str
    {
        if(isdigit(c))
        {
            return (int)c - 48; //converts ascii to int
        }
    }
    return -1;
}

int dataHolder::check(std::string row,std::string wordToBeFound)
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
