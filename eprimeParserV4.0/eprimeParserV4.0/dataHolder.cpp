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
    //TrialNumber = getTrialNumber(allData);
    TrialNumber = 0;
    //startTime = getStartTime(allData);
    startTime = 0;
    
    //create vectors that hold data for each trial
    Procedure = getProcedure(allData);
    FixOnset = getFix_Onset(allData);
    TargetACC = getTarget_ACC(allData);
    BlankOnset = getBlank_Onset(allData);
    updateHitMissCondition();
}

dataHolder::dataHolder(std::string file, std::string uniqueId) //with file and 6 digit patient ID
{
    /*
    //initialize variables
    allData = file;
    uniquePatientId = uniqueId;
    
    //get unique idenitifiers for this trial
    //TrialNumber = getTrialNumber(allData);
    //startTime = getStartTime(allData);
    
    //create vectors that hold data for each trial
    ConditionList = getCondition(allData);
    Anticipate_OnsetTime = getAnticipate_OnsetTime(allData);// anticipate
    Target_OnsetTime = getTarget_OnsetTime(allData); // response
    Target_RTTime = getTarget_RTTime(allData); //0 if miss else number
    Anticipate_Duration = getAnticipate_Duration(allData);
    Target_Duration = getTarget_Duration(allData);
    Feedback_Duration = getFeedback_Duration(allData);
    Feedback_OnsetTime = getFeedback_OnsetTime(allData);
    updateHitMissCondition();
    updateAnticipateList();
     */
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
    return Procedure;
}
std::vector<int> dataHolder::getFix_Onset() const
{
    return FixOnset;
}
std::vector<int> dataHolder::getTarget_ACC() const
{
    return TargetACC;
}
std::vector<int> dataHolder::getBlank_Onset() const
{
    return BlankOnset;
}

std::vector<std::string> dataHolder::getProcedure(std::string file)
{
    std::vector<std::string> procedureList;
    std::istringstream lineFinder(file);
    std::string lastLine;
    std::string lineIdentifier = "Procedure:";
    
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
    //std::cout<<ConditionList.size()<<" - ConditionListSize"<<std::endl;
    return procedureList;
}

std::vector<int> dataHolder::getFix_Onset(std::string file)
{
    std::vector<int> FixOnsetList;
    std::istringstream lineFinder(file);
    std::string lineIdentifier = "Fix.Onset";
    
    int num;
    std::string lin;
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        //ensures loop exits at the end of file
        if(lineFinder.eof())
        {
            break;
        }
        //This is considered as Target RTTime - response time
        while(check(line,lineIdentifier)==-1 && !lineFinder.eof()) //get first part
        {
            std::getline(lineFinder, line);
        }
        if(check(line, lineIdentifier)!=-1)
        {
            lin = line;
            num = getNumber(lin);
            FixOnsetList.push_back(num);
        }
    }
    //std::cout<<TargetRTTimeList.size()<<" - Target_RTTimeList"<<std::endl;
    return FixOnsetList;
}

std::string dataHolder::hit_miss(int tarACC)
{
    if(tarACC==0)
    {
        return "Miss";
    }
    else
    {
        return "Hit";
    }
}

void dataHolder::updateHitMissCondition()
{
    for(int i = 0;i<Procedure.size();i++)
    {
        Procedure[i] = hit_miss(TargetACC[i]) + "_" + Procedure[i];
    }
}

std::vector<int> dataHolder::getTarget_ACC(std::string file)
{
    std::vector<int> targetACCList;
    std::istringstream lineFinder(file);
    int num;
    std::string lin;
    std::string lineIdentifier = "Target.ACC";
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        //ensures that loop exits at the end of file
        if(lineFinder.eof())
        {
            break;
        }
        //This considered as Anticipate.OnsetTime time
        while(check(line,lineIdentifier)==-1 && !lineFinder.eof()) //get first part
        {
            std::getline(lineFinder, line);
        }
        if(check(line, lineIdentifier)!=-1)
        {
            lin = line;
            num = getNumber(lin);
            targetACCList.push_back(num);
        }
    }
    //std::cout<<AnticipateOnsetTimeList.size()<<" - Anticipate.OnsetTime"<<std::endl;
    return targetACCList;
}

std::vector<int> dataHolder::getBlank_Onset(std::string file)
{
    std::vector<int> targetACCList;
    std::istringstream lineFinder(file);
    int num;
    std::string lin;
    std::string lineIdentifier = "Blank";
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        //ensures that loop exits at the end of file
        if(lineFinder.eof())
        {
            break;
        }
        //This considered as Anticipate.OnsetTime time
        while(check(line,lineIdentifier)==-1 && !lineFinder.eof()) //get first part
        {
            std::getline(lineFinder, line);
        }
        if(check(line, lineIdentifier)!=-1)
        {
            lin = line;
            num = getNumber(lin);
            targetACCList.push_back(num);
        }
    }
    //std::cout<<AnticipateOnsetTimeList.size()<<" - Anticipate.OnsetTime"<<std::endl;
    return targetACCList;
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
