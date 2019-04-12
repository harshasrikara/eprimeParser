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
#include <iomanip>
#include "dataHolder.hpp"


std::string getData(std::string filename);
std::string removePracticeSessions(std::string filename);
std::string simplifyData(std::string info);
std::string splitData1(std::string total);
std::string splitData2(std::string total);
std::string print(dataHolder data, int st);

int getFirstNumber(std::string str);
std::string getSubjectNumber(std::string file);
int func(std::string str);
int check(std::string row,std::string wordToBeFound);
void printVector(std::vector<std::string> pList);
void printVector(std::vector<int> pList);
std::vector<int> subtractStartOnset(std::vector<int> list, int st);
void printVector(std::vector<std::string> pList, std::vector<int> pList2);

int getScanStart2(std::string file);
int getScanStart1(std::string file);

int main(int argc, const char * argv[]) {
    std::cout << std::endl;
    std::string file= "";
    
    
    while(file!="sub-M87100885_NICSMELL.txt")
    {
    
        //collecting user input
        std::cout<<"Enter the filename ";
        std::getline(std::cin,file);
        int scanStart1 = 0;
        int scanStart2 = 0;
        if(file == "exit")
        {
            return 0;
        }
    
    //exception handling. Actual file opening done by the getData function.
    std::ifstream myReadFile; //input stream
    myReadFile.open(file);
    if(myReadFile)
    {
        std::string first;
        std::string second;
        
        myReadFile.close();
        //calls function to extract data
        std::string extractedData;
        extractedData = getData(file);
        
        //std::cout<<extractedData<<std::endl;
        
        std::string removedPracticeSessions;
        removedPracticeSessions = removePracticeSessions(extractedData);
        
        scanStart1 = getScanStart1(removedPracticeSessions);
        scanStart2 = getScanStart2(removedPracticeSessions);
        //std::cout << scanStart1 << " " << scanStart2 << std::endl;
        //std::cout<<removedPracticeSessions<<std::endl;
        
        
        
        std::string simplifiedData;
        simplifiedData = simplifyData(removedPracticeSessions);
        
        //std::cout<<simplifiedData<<std::endl;
        
        first = splitData1(simplifiedData);
        second = splitData2(simplifiedData);
        
        //std::cout<<first<<std::endl;
        //std::cout<<"\n\n\n\n"<<std::endl;
        //std::cout<<second<<std::endl;
        //std::cout<<"\n\n\n\n"<<std::endl;
        //std::cout<<third<<std::endl;
        
        dataHolder firstTrial(first);
        dataHolder secondTrial(second);
        
        //printVector(firstTrial.getProcedure(),firstTrial.getOnset());
        //printVector(secondTrial.getProcedure(),secondTrial.getOnset());
        print(firstTrial, scanStart1);
        //print(lastTrial, scanStart2);
        if(/* DISABLES CODE */ (false))
        {
            
            std::cout<<"Writing data to .tsv files"<<std::endl;
            std::ofstream myfile;
            std::string trialNumFileName;
            //specific outputting parameters
            //can be changed depending on how the file should be outputted
            std::cout<<"Writing out trial1"<<std::endl;
            trialNumFileName = file.substr(0,13)+"_ses-01_task-SST-Run1.tsv";
            //+ firstTrial.getUniquePatientId()
            //+ "_ses-01_task-SST-Run1"
            //+/* std::to_string(firstTrial.getTrialNumber()) +*/ ".tsv";
            myfile.open (trialNumFileName);
            //myfile << print(firstTrial,scanStart1);
            myfile.close();
            
            std::cout<<"Writing out trial2"<<std::endl;
            trialNumFileName = file.substr(0,13)+"_ses-01_task-SST-Run2.tsv";
            //+ lastTrial.getUniquePatientId()
            //+ "_ses-01_task-SST-Run2"
            //+/* std::to_string(secondTrial.getTrialNumber()) +*/ ".tsv";
            myfile.open (trialNumFileName);
            //myfile << print(secondTrial,scanStart2);
            myfile.close();
            
            //return 0;
        }
        
    }
    else
    {
        myReadFile.close();
        std::cout<<file<<" failed to open"<<std::endl;
    }
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
            skipPracticeLevel2 = !skipPracticeLevel2;
            while(check(line,level3)==-1)
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
    bool lvl4 = true;
    //converts the string into a stream of characters. Easier to go through line by line.
    std::istringstream lineFinder(info);
    std::string output = "";
    
    //cycle through all the lines in a string
    for (std::string line; std::getline(lineFinder, line);)
    {
        if(lvl4)
        {
            if(check(line,"Level: 3")!=-1)
            {
                lvl4 = !lvl4; //ensures that the extra lvl4 data does not get extracted
                
                while(check(line,"Procedure")==-1) //get procedure
                {
                     std::getline(lineFinder, line);
                }
                output = output + line;
                while(check(line,"RatePain.Onset")==-1) //get RatePainOnset
                {
                    std::getline(lineFinder, line);
                }
                output = output + line + "\n";
            }
        }
        // This extracts each of the level 3 data sets. This contains information on when the cue is presented and removed.
        if(check(line,"Level: 2")!=-1)
        {
            lvl4 = !lvl4;
            while(check(line,"Procedure")==-1) //get Procedure
            {
                std::getline(lineFinder, line);
            }
            output = output + line+ "\n";
            while(check(line,"StimReady.OnsetTime:")==-1) //get CueOn
            {
                std::getline(lineFinder, line);
            }
            output = output + line+ "\n";
        }
    }
    return output;
}

std::string splitData1(std::string total)
{
    int div = 24;
    //converts the string into a stream of characters. Easier to go through line by line.
    std::istringstream lineFinder(total);
    std::string output = "";
    
    //cycle through all the lines in a string
    for (std::string line; std::getline(lineFinder, line);)
    {
        output = output + line + "\n";
        if(check(line,"OnsetTime")!=-1) //get Procedure
        {
            div--;
        }
        //output = output + line;
        if(div == 0)
        {
            break;
        }
        //std::cout<<line<<std::endl; //useful for debug purposes
    }
    return output;
}
std::string splitData2(std::string total)
{
    int div = 24;
    int div2 = 24;
    //converts the string into a stream of characters. Easier to go through line by line.
    std::istringstream lineFinder(total);
    std::string output = "";
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        if(check(line,"OnsetTime")!=-1) //get Procedure
        {
            div--;
        }
        //output = output + line;
        if(div==0)
        {
            std::getline(lineFinder, line);
        }
        while(div == 0)
        {
            output = output + line + "\n";
            if(check(line,"OnsetTime")!=-1) //get Procedure
            {
                div2--;
            }
            if(div2 == 0)
            {
                return output;
            }
            std::getline(lineFinder, line);
        }
        //std::cout<<line<<std::endl; //useful for debug purposes
    }
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
void printVector(std::vector<std::string> pList, std::vector<int> pList2)
{
    for(int i =0;i<pList.size();i++)
    {
        std::cout<<pList[i]<<std::endl;
        std::cout<<pList2[i]<<std::endl;
        std::cout<<std::endl;
    }
}


std::string print(dataHolder data, int st)
{
    std::string output;
    std::vector<std::string> Procedure = data.getProcedure();
    std::vector<int> Onset = subtractStartOnset(data.getOnset(), st);

    output+="Onset\tDuration\tTrialType\n";
    for(int i =0;i<Procedure.size();i++)
    {
        if(i%2!=0)
        {
            output += std::to_string((double)Onset[i-1]/1000) + "\t5\t" + Procedure[i-1] +"\n";
        }
        else
        {
            output += std::to_string((double)Onset[i+1]/1000) + "\t15\t" + Procedure[i+1] + "\n";
        }
    }
    std::cout<<output<<std::endl;
    return output;
}


int getScanStart2(std::string file)
{
    //adds file into a stream of data
    std::istringstream lineFinder(file);
    std::string lastLine;
    std::string lineIdentifier = "StartRun2.RTTime:";
    
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
        return func(lastLine);
    }
    return -1;
}
int getScanStart1(std::string file)
{
    //adds file into a stream of data
    std::istringstream lineFinder(file);
    std::string lastLine;
    std::string lineIdentifier = "StartRun1.RTTime:";
    
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
        return func(lastLine);
    }
    return -1;
}

std::vector<int> subtractStartOnset(std::vector<int> list, int st)
{
    for(int i = 0;i<list.size();i++)
    {
        list[i] = list[i] - st;
    }
    return list;
}
