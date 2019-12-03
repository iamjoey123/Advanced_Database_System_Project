# Advanced_Database_System_Project
#Joshua Williams & Kuan Chieh Peng

Our goal for this project is to implement the paper, "Efficient Top-k Algorithms for Approximate Substring". Since the datasets are so large, we could not upload the whole project here. As a result, We will upload the actual coding of the four algorithms and the makefile here on github and provide a link below to downlip a zip file that contains the datasets and all of the code together.

https://www.dropbox.com/s/9uch3qkk5ysstts/DB_Project.zip?dl=0

 Steps to run code
 1. We have included a make file to compile all of the code. Type in the below command to create the executables
 
    a. make
    
 2. Once the executables are created you can run any of the four algorithms using the below commands
 
    a. ./Top-K_Naive
    
    b. ./Top-K_LB
    
    c. ./Top-K_Split
    
    d. ./Top-K_Index
    
 3. Once you type in any of the four commands in step 2, you have a choice of entering a 1, 2, or 3 to decide which dataset you want to use
 4. Once done testing, to clean up the directory type in the below command
 
    a. make clean
