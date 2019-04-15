# eprimeParser
parse eprime log files and extract relevant data

## Note
## Additional Information and documention is being added. The information below is only an overview of the project. More information and specific readme files for each project will be developed soon. Background information deals only with V1.0, will be updated soon.

### Background Information
The code was developed to assist in easily parsing eprime text files and extracting relevant information from it. It functions to extract information on trials from the eprime files. This information includes data on the procedure, cue on and off onset times as well as calculating the duration based on those values. Additional features present in the code include splitting the log files into smaller partitions if there are multiple trial runs and outputting them seperatly. This software is designed for use at the research facilities of the center for brain health. 

### Version Information
Each distinct version is designed to deal with a specific type of data stored in a specific format. 
- V1.0 - MJC
- V2.0 - MJC + Practice
- V3.0 - MID
- V4.0 - SST
- V5.0 - NICSMELL
- V6.0 - GUSTO

Also added in each progression of versions are new features. These include the ability to handle multiple parameter. The ability to search through the file itself for subject ID, date and time identifiers. 
The last few versions also include the ability to run through an entire folder of data immidiately instead of one file at a time. They can also handle unique file names being passed to them.

### How to Use
- Clone/download the code (recommend clone so that future updates can easily be pulled)
- Place the eprime text file in the same folder as the main.cpp file
- If you have IDE, you can easily compile and run the code at this time.
- If you would like to use terminal, execute the following commands
  - cd ~/ENTER YOUR FILE PATH HERE
  - g++ main.cpp dataHolder.cpp
  - ./a.out
 - At this point, the console will prompt for the file name. 
 - Enter in that information and the output will be logged to console and .tsv files will be created
 
### Future updates in the works (Most have been added to later versions already)
 - Outputting to various different file formats and log conventions
 - Parsing multiple files at the same time instead of one at a time
 - Acessing a directory with file names to parse all at once
 - Entering an absolute file path instead of having to place file in the same folder
 - Passing in variable parameters to extract different values based on experiment
 - Passing in header values instead of searching for them
