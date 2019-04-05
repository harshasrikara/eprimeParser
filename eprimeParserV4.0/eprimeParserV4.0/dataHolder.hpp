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
    
    std::vector<std::string> ConditionList; // neutral/loss/gain
    std::vector<std::string> AnticipateList; //Anticipate_neutral/loss/gain
    std::vector<int> Anticipate_OnsetTime;// anticipate
    std::vector<int> Target_OnsetTime; // response
    std::vector<int> Target_RTTime; //0 if miss else number
    std::vector<int> Target_RT; //0 if miss else number
    std::vector<int> Anticipate_Duration;
    std::vector<int> Target_Duration;
    std::vector<int> Feedback_Duration;
    std::vector<int> Feedback_OnsetTime;
    
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
    std::vector<std::string> getCondition() const;
    std::vector<int> getAnticipate_OnsetTime() const;
    std::vector<int> getTarget_OnsetTime() const;
    std::vector<int> getTarget_RTTime() const;
    std::vector<int> getTarget_RT() const;
    std::vector<int> getAnticipate_Duration() const;
    std::vector<int> getTarget_Duration() const;
    std::vector<int> getFeedback_Duration() const;
    std::vector<int> getFeedback_OnsetTime() const;
    std::vector<std::string> getAnticipateList() const;
    
    //setters and calculations
    int getTrialNumber(std::string); //done
    int getStartTime(std::string); //done
    std::string condition(std::string);
    std::string hit_miss(int);
    void updateHitMissCondition();
    void updateAnticipateList();
    
    //search and extract functions(common values)
    int check(std::string row,std::string wordToBeFound); //done
    int getNumber(std::string); //done
    int getFirstNumber(std::string); //done
    
    //search and extract functions(multiple values)
    std::vector<std::string> getCondition(std::string);
    std::vector<int> getAnticipate_OnsetTime(std::string);
    std::vector<int> getTarget_OnsetTime(std::string);
    std::vector<int> getTarget_RTTime(std::string);
    std::vector<int> getTarget_RT(std::string);
    std::vector<int> getAnticipate_Duration(std::string);
    std::vector<int> getTarget_Duration(std::string);
    std::vector<int> getFeedback_Duration(std::string);
    std::vector<int> getFeedback_OnsetTime(std::string);
};

#endif /* dataHolder_hpp */
