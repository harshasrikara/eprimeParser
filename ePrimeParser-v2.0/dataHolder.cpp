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
    //initialize variable
    allData = file;
    
    //get unique idenitifiers for this trial
    TrialNumber = getTrialNumber(allData);
    startTime = getStartTime(allData);
    
    //create vectors that hold data for each trial
    procedureList = getProcedure(allData);
    Hold_OnsetTime = getHold_OnsetTime(allData);
    Off_OnsetTime = getOff_OnsetTime(allData);
    RatePain_OnsetTime = getRatePain_OnsetTime(allData);
}
dataHolder::dataHolder(std::string file, std::string uniqueId) //with file and 6 digit patient ID
{
    //initialize variables
    allData = file;
    uniquePatientId = uniqueId;
    
    //get unique idenitifiers for this trial
    TrialNumber = getTrialNumber(allData);
    startTime = getStartTime(allData);
    
    //create vectors that hold data for each trial
    procedureList = getProcedure(allData);
    Hold_OnsetTime = getHold_OnsetTime(allData);
    Off_OnsetTime = getOff_OnsetTime(allData);
    RatePain_OnsetTime = getRatePain_OnsetTime(allData);
}

int dataHolder::getTrialNumber(std::string file)
{
    //adds file into a stream of data
    std::istringstream lineFinder(file);
    std::string lastLine;
    std::string lineIdentifier = "RTTime";
    
    //goes through the data line by line
    for (std::string line; std::getline(lineFinder, line);)
    {
        //searches for RTTime
        while(check(line,lineIdentifier)==-1) //get first part
        {
            std::getline(lineFinder, line);
        }
        lastLine = line;
        //gets first number found on that line - eg. StartRun1.RTTime
        //std::cout<<lastLine<<std::endl;
        return getFirstNumber(lastLine);
    }
    return -1;
}

int dataHolder::getStartTime(std::string file)
{
    //adds file into a stream of data
    std::istringstream lineFinder(file);
    std::string lastLine;
    std::string lineIdentifier = "RTTime";
    
    //goes through the data line by line
    for (std::string line; std::getline(lineFinder, line);)
    {
        //RTTime is considered as the start time for trials
        while(check(line,lineIdentifier)==-1) //get first part
        {
            std::getline(lineFinder, line);
        }
        lastLine = line;
        //gets the RTTime - eg. StartTun1.RTTime: 12345678
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

//vector const getters
std::vector<std::string> dataHolder::getProcedure() const
{
    return procedureList;
}
std::vector<int> dataHolder::getHold_OnsetTime() const
{
    return Hold_OnsetTime;
}
std::vector<int> dataHolder::getOff_OnsetTime() const
{
    return Off_OnsetTime;
}
std::vector<int> dataHolder::getRatePain_OnsetTime() const
{
    return RatePain_OnsetTime;
}

std::vector<std::string> dataHolder::getProcedure(std::string file)
{
    std::vector<std::string> procedureList;
    std::istringstream lineFinder(file);
    std::string lastLine;
    std::string lineIdentifier = "Procedure";
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        //ensures that loop exits at the end of the file
        if(lineFinder.eof())
        {
            break;
        }
        //searches for Procedure
        while(check(line,lineIdentifier)==-1 && !lineFinder.eof()) //get first part
        {
            std::getline(lineFinder, line);
        }
        //double checking that we have found procedure
        if(check(line, lineIdentifier)!=-1)
        {
            lastLine = line;
            std::stringstream ss;
            /* Storing the whole string into string stream */
            ss << lastLine;
            /* Running loop till the end of the stream */
            std::string temp;
            ss>>temp;
            ss>>temp; //gets the second word in that line which is the procedure name
            procedureList.push_back(temp);
        }
    }
    
    //std::cout<<procedureList.size()<<std::endl;
    return procedureList;
}

std::vector<int> dataHolder::getHold_OnsetTime(std::string file)
{
    std::vector<int> HoldOnsetTimeList;
    std::istringstream lineFinder(file);
    std::string lineIdentifier = "Hold.Onset";
    
    int num;
    std::string lin;
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        //ensures loop exits at the end of file
        if(lineFinder.eof())
        {
            break;
        }
        //This is considered as cueOn time
        while(check(line,lineIdentifier)==-1 && !lineFinder.eof()) //get first part
        {
            std::getline(lineFinder, line);
        }
        if(check(line, lineIdentifier)!=-1)
        {
            lin = line;
            num = getNumber(lin);
            HoldOnsetTimeList.push_back(num);
        }
    }
    return HoldOnsetTimeList;
}

std::vector<int> dataHolder::getOff_OnsetTime(std::string file)
{
    std::vector<int> HoldOnsetTimeList;
    std::istringstream lineFinder(file);
    int num;
    std::string lin;
    std::string lineIdentifier = "Off.Onset";
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        //ensures that loop exits at the end of file
        if(lineFinder.eof())
        {
            break;
        }
        //This considered as CueOff time
        while(check(line,lineIdentifier)==-1 && !lineFinder.eof()) //get first part
        {
            std::getline(lineFinder, line);
        }
        if(check(line, lineIdentifier)!=-1)
        {
            lin = line;
            num = getNumber(lin);
            HoldOnsetTimeList.push_back(num);
        }
    }
    return HoldOnsetTimeList;
}

std::vector<int> dataHolder::getRatePain_OnsetTime(std::string file)
{
    std::vector<int> HoldOnsetTimeList;
    std::istringstream lineFinder(file);
    int num;
    std::string lin;
    std::string lineIdentifier = "RatePain";
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        //ensures loop exits at the end of file
        if(lineFinder.eof())
        {
            break;
        }
        //This is when the response is given
        while(check(line,lineIdentifier)==-1 && !lineFinder.eof()) //get first part
        {
            std::getline(lineFinder, line);
        }
        if(check(line, lineIdentifier)!=-1)
        {
            lin = line;
            num = getNumber(lin);
            HoldOnsetTimeList.push_back(num);
        }
    }
    return HoldOnsetTimeList;
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

//checks if one string is a substring of another and if yes returns the index of the first character
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
