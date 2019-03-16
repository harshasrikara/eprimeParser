//
//  dataHolder.hpp
//  eprimeParser
//
//  Created by Harsha Srikara on 3/3/19.
//  Copyright © 2019 Harsha Srikara. All rights reserved.
//

#ifndef dataHolder_hpp
#define dataHolder_hpp

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class dataHolder
{
    private:
    std::string allData;
    
    int TrialNumber; //must be 1 or 2
    int startTime;
    std::string uniquePatientId; //6 digits
    
    std::vector<std::string> procedureList; // control/MJ/Fruit
    std::vector<int> Hold_OnsetTime;// CueOn
    std::vector<int> Off_OnsetTime; // CueOff
    std::vector<int> RatePain_OnsetTime; //Rate
    
    public:
    //constructors
    dataHolder(); //done
    dataHolder(std::string);//done
    dataHolder(std::string,std::string); //done
    
    //getters
    int getTrialNumber() const; //done
    int getStartTime() const; //done
    std::string getUniquePatientId() const; //done
    std::string getAllData() const; //done
    
    //vector getters
    std::vector<std::string> getProcedure() const;
    std::vector<int> getHold_OnsetTime() const;
    std::vector<int> getOff_OnsetTime() const;
    std::vector<int> getRatePain_OnsetTime() const;
    
    //setters and calculations
    int getTrialNumber(std::string); //done
    int getStartTime(std::string); //done
    
    //search and extract functions(common values)
    int check(std::string row,std::string wordToBeFound); //done
    int getNumber(std::string); //done
    int getFirstNumber(std::string); //done
    
    //search and extract functions(multiple values)
    std::vector<std::string> getProcedure(std::string);
    std::vector<int> getHold_OnsetTime(std::string);
    std::vector<int> getOff_OnsetTime(std::string);
    std::vector<int> getRatePain_OnsetTime(std::string);
};

#endif /* dataHolder_hpp */
