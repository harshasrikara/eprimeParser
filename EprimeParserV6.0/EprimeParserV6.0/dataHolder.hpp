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
    
    std::vector<std::string> TasteName; // H2O/ HCD
    std::vector<int> Taste_Onset; //onset of taste cue
    std::vector<int> Rest_Onset;  //onset of washout
    std::vector<int> Rest_Offset; //onset of rate
    
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
    std::vector<std::string> getTasteName() const;
    std::vector<int> getTaste_Onset() const;
    std::vector<int> getRest_Onset() const;
    std::vector<int> getRest_Offset() const;
    
    //setters and calculations
    int getTrialNumber(std::string); //done
    int getStartTime(std::string); //done
    
    //search and extract functions(common values)
    int check(std::string row,std::string wordToBeFound); //done
    int getNumber(std::string); //done
    int getFirstNumber(std::string); //done
    
    //search and extract functions(multiple values)
    std::vector<std::string> getTasteName(std::string);
    std::vector<int> getTaste_Onset(std::string);
    std::vector<int> getRest_Onset(std::string);
    std::vector<int> getRest_Offset(std::string);
};

#endif /* dataHolder_hpp */
