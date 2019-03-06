# eprimeParser
parse eprime log files and extract relevant data

### Background Information
The code was developed to assist in easily parsing eprime text files and extracting relevant information from it. It functions to extract information on trials from the eprime files. This information includes data on the procedure, cue on and off onset times as well as calculating the duration based on those values. Additional features present in the code include splitting the log files into smaller partitions if there are multiple trial runs and outputting them seperatly. This software is designed for use at the research facilities of the center for brain health. 

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
 
### Future updates in the works
 - Outputting to various different file formats and log conventions
 - Parsing multiple files at the same time instead of one at a time
 - Acessing a directory with file names to parse all at once
 - Entering an absolute file path instead of having to place file in the same folder
 - Passing in variable parameters to extract different values based on experiment
 - Passing in header values instead of searching for them
