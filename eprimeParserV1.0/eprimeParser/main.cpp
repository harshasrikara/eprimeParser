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

//prototypes
std::string getData(std::string filename);
std::string simplifyData(std::string info);
std::string splitData(std::string &total);

std::string removePractice(std::string info);
std::string simplifyDataTemp(std::string info);
std::string splitDataTemp(std::string &info);

int getFirstNumber(std::string str);
std::string getSubjectNumber(std::string file);
int func(std::string str);
int check(std::string row,std::string wordToBeFound);
void printVector(std::vector<std::string> pList);
void printVector(std::vector<int> pList);
std::string print(dataHolder data);


int main(int argc, const char * argv[]) {
    
    //collecting user input
    std::cout<<"Enter the filename: ";
    std::string file;
    std::getline(std::cin,file);
    
    bool removePracticeSession = false;
    
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
        
        //added feature to eliminate practice sessions at beginning of log
        if(removePracticeSession)
        {
            std::string reducedData;
            reducedData = removePractice(extractedData);
            
            //std::cout<<reducedData<<std::endl;
            
            std::string simplifiedData;
            simplifiedData = simplifyDataTemp(reducedData);
            
            //std::cout<<simplifiedData<<std::endl;

            first = splitDataTemp(simplifiedData);
            last = simplifiedData;
        }
        else
        {
            //calls function to isolate relevant sections
            std::string simplfiedData;
            simplfiedData = simplifyData(extractedData);
            
            //std::cout<<simplfiedData<<std::endl;
            
            //This splits the two runs into seperate strings.
            last = splitData(simplfiedData);
            first = simplfiedData;
            
        }
        //std::cout<<extractedData<<std::endl;
        std::string subjectNumber = getSubjectNumber(extractedData);
    
        //std::cout<<"FIRST"<<first<<std::endl;
        //std::cout<<"\n\n\n\n"<<std::endl;
        //std::cout<<"LAST"<<last<<std::endl;
        
        dataHolder firstTrial(first,subjectNumber);
        dataHolder lastTrial(last,subjectNumber);
        
        /*
        std::vector<int> pList = firstTrial.getRatePain_OnsetTime(first);
        for(int i =0;i<pList.size();i++)
        {
            std::cout<<pList[i]<<std::endl;
        }
        */
        
        //optional cout to console/terminal
        std::cout<<print(firstTrial)<<std::endl;
        std::cout<<"\n\n\n\n"<<std::endl;
        std::cout<<print(lastTrial)<<std::endl;
        
        //writing to a .tsv file
        std::cout<<"Writing data to .tsv files"<<std::endl;
        std::ofstream myfile;
        std::string trialNumFileName;
        //specific outputting parameters
        //can be changed depending on how the file should be outputted
        if(removePracticeSession)
        {
            trialNumFileName ="sub-M8710"+ firstTrial.getUniquePatientId() + "_ses-01_task-MJCue-Run1" +/* std::to_string(firstTrial.getTrialNumber()) +*/ ".tsv";
            myfile.open (trialNumFileName);
            myfile << print(firstTrial);
            myfile.close();
            
            trialNumFileName ="sub-M8710"+ lastTrial.getUniquePatientId() + "_ses-01_task-MJCue-Run2" +/* std::to_string(lastTrial.getTrialNumber()) +*/ ".tsv";
            myfile.open (trialNumFileName);
            myfile << print(lastTrial);
            myfile.close();
            return 0;
        }
        else
        {
            trialNumFileName ="sub-"+ firstTrial.getUniquePatientId() + "_ses-01_task-run1_bold" +/* std::to_string(firstTrial.getTrialNumber()) +*/ ".tsv";
            myfile.open (trialNumFileName);
            myfile << print(firstTrial);
            myfile.close();
            
            trialNumFileName ="sub-"+ lastTrial.getUniquePatientId() + "_ses-01_task-run2_bold" +/* std::to_string(lastTrial.getTrialNumber()) +*/ ".tsv";
            myfile.open (trialNumFileName);
            myfile << print(lastTrial);
            myfile.close();
            return 0;
        }
    }
    else //if file opening failed
    {
        std::cout<<file << " failed to open"<<std::endl;
        return 2;
    }
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
        //std::cout<<line<<std::endl; //useful for debug purposes
    }
    return output;
}

std::string splitData(std::string &simplifiedData)
{
    std::istringstream lineFinder(simplifiedData);
    std::string first = "";
    std::string last = "";
    std::string lineIdentifier = "RTTime";
    
    for (std::string line; std::getline(lineFinder, line);)
    {
        first = first + line+ "\n";
        while(check(line,lineIdentifier)==-1) //get first part
        {
            std::getline(lineFinder, line);
            first = first + line+ "\n";
        }
        std::getline(lineFinder, line);
        last = last + line+ "\n";
        while(check(line,lineIdentifier)==-1) //get second part
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

//The following 3 functions are temporary and will need to be replaced.
//They will be combined with the existing functions that have the same name
//This is just to ensure that they work properly

std::string removePractice(std::string info)
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
            //removes the 100 practice sessions at the beginning
            while(check(line,level3)==-1)
            {
                std::getline(lineFinder, line);
            }
            
            //removes the 4 practice sessions
            while(check(line,level2)==-1)
            {
                std::getline(lineFinder, line);
            }
            std::getline(lineFinder, line);
            while(check(line,level2)==-1)
            {
                std::getline(lineFinder, line);
            }
            std::getline(lineFinder, line);
            while(check(line,level2)==-1)
            {
                std::getline(lineFinder, line);
            }
            std::getline(lineFinder, line);
            while(check(line,level2)==-1)
            {
                std::getline(lineFinder, line);
            }
            std::getline(lineFinder, line);
        }
        
        output = output + line + "\n";
    }
    return output;
}

std::string simplifyDataTemp(std::string info)
{
    //converts the string into a stream of characters. Easier to go through line by line.
    std::istringstream lineFinder(info);
    std::string output = "";
    
    bool lvl3 = true;
    int count =0;
    //cycle through all the lines in a string
    for (std::string line; std::getline(lineFinder, line);)
    {
        //extracts the very first level 3 data. This is when the participant responds to the cue.
        if(lvl3)
        {
            if(check(line,"Level: 3")!=-1)
            {
                lvl3 = !lvl3; //ensures that the extra lvl4 data does not get extracted
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
        // This extracts each of the level 2 data sets. This contains information on when the cue is presented and removed.
        if(check(line,"Level: 2")!=-1)
        {
            count++;
            lvl3 = !lvl3;
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
        //std::cout<<line<<std::endl; //useful for debug purposes
    }
    //std::cout<<count<<std::endl;
    return output;
}

std::string splitDataTemp(std::string &info)
{
    //converts the string into a stream of characters. Easier to go through line by line.
    std::istringstream lineFinder(info);
    std::string output = "";
    std::string output2 = "";
    
    int div = 12;
    for (std::string line; std::getline(lineFinder, line);)
    {
        if(check(line,"RatePain")!=-1)
        {
            div = div - 1;
        }
        if(div>-1)
        {
            if(check(line,"RTTime")==-1)
            {
                output = output + line + "\n";
            }
        }
        else
        {
            if(check(line,"RTTime")==-1)
            {
                output2 = output2 + line + "\n";
            }
        }
        if(check(line,"StartRun1.RTTime")!=-1)
        {
            output = output + line + "\n";
        }
        if(check(line,"StartRun2.RTTime")!=-1)
        {
            output2 = output2 + line + "\n";
        }
    }
    //std::cout<<div<<std::endl;
    info = output2;
    return output;
}

//END OF TEMPORARY FUNCTIONS

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
    //initialization. Collect variables.
    std::string output;
    std::vector<std::string> procedureList = data.getProcedure();
    std::vector<int> hold_onsetTime = data.getHold_OnsetTime();
    std::vector<int> off_onsetTime = data.getOff_OnsetTime();
    std::vector<int> ratePain_onsetTime = data.getRatePain_OnsetTime();
    int startScanTime = data.getStartTime();
    int runNum = data.getTrialNumber();
    
    std::cout<<"This is trial "<<std::to_string(runNum)<<std::endl;
    //Hold - Off - Rate
    output = "Onset\tDuration\tTrialType\n";
    for(int i = 0;i<procedureList.size();i++)
    {
        //removing offset and converting to seconds from milliseconds
        hold_onsetTime[i] = (hold_onsetTime[i] - startScanTime)/1000;
        off_onsetTime[i] = (off_onsetTime[i] - startScanTime)/1000;
        ratePain_onsetTime[i] = (ratePain_onsetTime[i] - startScanTime)/1000;
    }
    for(int i = 0;i<procedureList.size();i++)
    {
        output = output + std::to_string(hold_onsetTime[i])+"\t"+std::to_string(off_onsetTime[i] - hold_onsetTime[i])+"\t"+procedureList[i] + "CueOn\n";
        if(i!=procedureList.size()-1)
        {
            output = output + std::to_string(off_onsetTime[i])+"\t"+std::to_string(hold_onsetTime[i+1] - off_onsetTime[i])+"\t"+procedureList[i] + "CueOff\n";
        }
        else
        {
            output = output + std::to_string(off_onsetTime[i])+"\t"+std::to_string(20)+"\t"+procedureList[i] + "CueOff\n";
        }
        output = output + std::to_string(ratePain_onsetTime[i])+"\t"+std::to_string(off_onsetTime[i] - ratePain_onsetTime[i])+"\t"+procedureList[i] + "RateOnset\n";
    }
    
    //std::cout<<output<<std::endl;
    return output;
}
