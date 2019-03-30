//
//  main.cpp
//  eprimeParserV3.0
//
//  Created by Harsha Srikara on 3/28/19.
//  Copyright © 2019 Harsha Srikara. All rights reserved.
//


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "dataHolder.hpp"


std::string getData(std::string filename);
std::string removePracticeSessions(std::string filename);
std::string simplifyData(std::string info);
std::string splitData(std::string &total);
std::string print(dataHolder data);

int getFirstNumber(std::string str);
std::string getSubjectNumber(std::string file);
int func(std::string str);
int check(std::string row,std::string wordToBeFound);
void printVector(std::vector<std::string> pList);
void printVector(std::vector<int> pList);

int main(int argc, const char * argv[]) {
    
    //collecting user input
    std::cout<<"Enter the filename: ";
    std::string file;
    std::getline(std::cin,file);
    
    //exception handling. Actual file opening done by the getData function.
    std::ifstream myReadFile; //input stream
    myReadFile.open(file);
    if(myReadFile)
    {
        std::string first;
        std::string last;
        
        myReadFile.close();
        //calls function to extract data
        std::string extractedData;
        extractedData = getData(file);
        
        //std::cout<<extractedData<<std::endl;
        
        std::string removedPracticeSessions;
        removedPracticeSessions = removePracticeSessions(extractedData);
        
        //std::cout<<removedPracticeSessions<<std::endl;
        
        std::string simplifiedData;
        simplifiedData = simplifyData(removedPracticeSessions);
        
        //std::cout<<simplifiedData<<std::endl;
        
        first = splitData(simplifiedData);
        last = simplifiedData;
        
        //std::cout<<"FIRST\n"<<first<<std::endl;
        //std::cout<<"\n\n\n\n"<<std::endl;
        //std::cout<<"LAST\n"<<last<<std::endl;
        
        dataHolder firstTrial(first);
        print(firstTrial);
        //printVector(firstTrial.getTarget_OnsetTime());
    }
    else
    {
        myReadFile.close();
        std::cout<<file<<" failed to open"<<std::endl;
    }
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
        std::cout<<filename<<" successfully opened\n\n"<<std::endl;
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

std::string removePracticeSessions(std::string info)
{
    //converts the string into a stream of characters. Easier to go through line by line.
    std::istringstream lineFinder(info);
    std::string output = "";
    
    bool skipPracticeLevel2 = true;
    
    std::string level2 = "Level: 2";
    std::string level3 = "Level: 3";
    std::string level4 = "Level: 4";
    
    //cycle through all the lines in a string
    for (std::string line; std::getline(lineFinder, line);)
    {
        if(skipPracticeLevel2)
        {
            skipPracticeLevel2 = false;
            for(int i =0;i<7;i++)
            {
                //removes the 7 practice sessions
                while(check(line,level2)==-1)
                {
                    std::getline(lineFinder, line);
                }
                std::getline(lineFinder, line);
            }
            while(check(line,level2)==-1)
            {
                std::getline(lineFinder, line);
            }
        }
        
        output = output + line + "\n";
    }
    return output;
}

std::string simplifyData(std::string info)
{
    //converts the string into a stream of characters. Easier to go through line by line.
    std::istringstream lineFinder(info);
    std::string output = "";
    
    //cycle through all the lines in a string
    for (std::string line; std::getline(lineFinder, line);)
    {
        if(check(line,"Condition")!=-1) //get Procedure
        {
            output = output + line+ "\n";
        }
        if(check(line,"Anticipate.OnsetTime")!=-1) //get Procedure
        {
            output = output + line+ "\n";
        }
        if(check(line,"Target.OnsetTime")!=-1) //get Procedure
        {
            output = output + line+ "\n";
        }
        if(check(line,"Target.RTTime")!=-1) //get Procedure
        {
            output = output + line+ "\n";
        }
        if(check(line,"AnticipateDuration")!=-1) //get Procedure
        {
            output = output + line+ "\n";
        }
        if(check(line,"TargetDuration")!=-1) //get Procedure
        {
            output = output + line+ "\n";
        }
        if(check(line,"FeedbackDuration")!=-1) //get Procedure
        {
            output = output + line+ "\n";
        }
        if(check(line,"Feedback.OnsetTime")!=-1) //get Procedure
        {
            output = output + line+ "\n\n";
        }
        //std::cout<<line<<std::endl; //useful for debug purposes
    }
    return output;
}

std::string splitData(std::string &info)
{
    //converts the string into a stream of characters. Easier to go through line by line.
    std::istringstream lineFinder(info);
    std::string output = "";
    std::string output2 = "";
    int div = 72;
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        if(check(line,"Condition")!=-1)
        {
            div = div - 1;
        }
        if(div>-1)
        {
                output = output + line + "\n";
        }
        else
        {
                output2 = output2 + line + "\n";
        }
    }
    info = output2;
    return output;
}


//helper functions
//checks to see if one string is a substring of another string (returns index of where substring begins) (-1 if not found)
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
    
    //makes the unique ID 6 digits starting with 0 eg. 20053 -> 020053
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

void printVector(std::vector<std::string> pList)
{
    for(int i =0;i<pList.size();i++)
    {
        std::cout<<pList[i]<<std::endl;
    }
}
void printVector(std::vector<int> pList)
{
    for(int i =0;i<pList.size();i++)
    {
        std::cout<<pList[i]<<std::endl;
    }
}


std::string print(dataHolder data)
{
    std::string output;
    std::vector<std::string> AnticipateList = data.getAnticipateList();
    std::vector<std::string> ConditionList = data.getCondition();
    std::vector<int> TargetOnsetList = data.getTarget_OnsetTime();
    std::vector<int> AnticipateOnsetList = data.getAnticipate_OnsetTime();
    std::vector<int> AnticipateDuration = data.getAnticipate_Duration();
    int TargetDuration = 0;
    
    std::cout<<"Onset\tDuration\tTrialType\n"<<std::endl;
    for(int i =0;i<ConditionList.size();i++)
    {
        std::cout<<AnticipateOnsetList[i]<<"\t"<<AnticipateDuration[i]<<"\t"<<AnticipateList[i]<<std::endl;
        std::cout<<TargetOnsetList[i]<<"\t"<<TargetDuration<<"\t"<<ConditionList[i]<<std::endl;
    }
    return "";
}
