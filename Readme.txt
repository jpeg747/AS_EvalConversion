#M#@S                                                                                                       
#&H@i                                                                                                       
#B#@2                                                                                                       
#B@@2       ,;sis;.   ;;::    ,;:.    ;::, ,;:: .rSr.    .;iir     .;::. ;iir,        :risr.       .;si;    
#B#@2     A@@@@@@@@@s @@@@;   @@@@   i@@@h #@@@@@@@@@  r@@@@@@@@,  r@@@@@@@@@@@;    A@@@@@@@@i   r@@@@@@@@, 
#B#@2     .@@S;:r@@@@; @@@#  S@@@@r  @@@@  h@@@@@@@@# 3@@@#iX@@@@: ,@@@@@#B@@@@@, ,@@@@@##@@@@2 9@@@MSX@@@@:
#B#@2             @@@# S@@@  @@@@@@  @@@r  2@@@h     ,@@@s    A@@@  @@@#    i@@@A @@@@;    S@: :@@@i    A@@G
#B#@2     S@@@@@@@@@@M  @@@r @@XA@@ r@@@   S@#@      A@@#H#@@M@@@@  @@@5     @@@A @@@3         &@@@M#@@M@@@#
#B#@2    @@@@Hrrs&@@@M  2@@#&@@ ,@@&B@@;   S@@@,     A@@@#@@@@MH#@  @@@X     @@@3 @@@X         &@@@#@@@@#HH&
#B#@S    @@@M     @@@#   @@@@@#  @@@@@@    S@@@:     r@@@r          @@@&     @@@h @@@@,    ,X  ;@@@r        
#B@@@9A&S:h@@r  :A@@@#   3@@#@r  3@@#@r    S@@@;      #@@@Ar:s##:  .@@@A    .@@3. ,@@@@#Xh@@@@; B@@@A;:s##; 
##@@@@@@@@;s@@@@@@@@@@    @@@@    @@@@     2@@@r       5@@@@@@@@@; .@@@#    .#:5A   @@@@@@@@@B   5@@@@@@@@@:
A&BM####M#@i.9Mh; ;rss    :rr;    ;rs.      ;,r          :5&A3s,    irir     i@@#     rX&hi:       :2&A3s,  
                                     i@@@@BXii2H#@@@&                       .@@@M                           
                                     @@@@@@@@@@@@@@@@                        @@@B                           
                                     r9SiiS@@@@ssiS2r                        @@@H                           
                                           @@@#     .3@@@G:       ;h#@@MS.   @@@@rH@@#2.                    
                                           @@@@   .@@@@@@@@@    r@@@@@@@@@#  @@@@@@@@@@@r                   
                                           @@@@  :@@@X  .#@@@  r@@@@S:;A@@@  @@@@9,,S@@@@                   
                                           @@@@  @@@@    ,@@@s @@@@          @@@h    r@@@r                  
                                           @@@@  @@@@@@@@@@@@A @@@2          @@@S    .@@@s                  
                                           @@@@  @@@#          @@@#          @@@9    :@@@r                  
                                           @@@@  s@@@;         5@@@B,  ;@@5  @@@G    :@@@r                  
                                           @@@@   2@@@@@@@@@2   X@@@@@@@@@@. @@@H    :@@@s                  
                                           @@@@     h@@@@@@h,     9@@@@@#r   @@@A    ,@@@s                  
                                                                                                            
                                                                                                            
                                                                                                            
Arts and Sciences Evaluation Conversion Program
Version: 0.6

This program is meant to be used for the Arts and Sciences Dean's Office of Lawrence Technological University.
Other non-LTU purposes must first by authorized by Jeremy Quinlan or the Dean/Associate Dean of Arts and 
Sciences. 

AS_EvaluationConvert.exe is a simple C++ program I created for the sole purpose of compiling .txt evaluation
files for the A&S department for Lawrence Tech. 

The program will read each file with the '####.txt" name, with #### representing a number from 0-9999. 
NOTE: This version of the program cannot separate files by department

To check if the program read all the files, select all the files that need to be read and compare that number 
to the number that the program gives. ie: "Done. 89 opened successfully. 89 read successfully." To find the 
file that the program failed to scan, check each file for a '1' mark on the left-hand corner of the files. 
Currently, the only way for solving this issue is to simply create a new file with the same data to be 
rescanned.

-Step by step instructions-

IMPORTANT: Before running, determine if your computer is 64-bit or 32-bit.

o Open "A&S Eval Convert" folder.
o Run "vcredist_x64.exe" if your computer is 64-bit or run "vcredist_x86.exe" if your computer is 32-bit.
o Copy the "AS_EvaluationConvert-v0.6.exe" application file to the same location as the evaluation text files
  (the folder with all the numbered text files, i.e. 2331.txt, 1223.txt etc.) NOTE: Files should be sorted by
  department manually, as this program (version 0.6) cannot sort files.

IMPORTANT: This program will scan all text files with a ####.txt format and with five or more responses.
           All scanned files will be marked with a '1' at the corner.

o Results will be put into a separate text file in the same folder as the application file titled 
  "Eval_Results.txt".
o You can now copy and paste the "Eval_Results.txt" data into an excel spreadsheet or whatever other program
  you prefer. 


-Found Bugs-
o Skips certain .txt files
o A file that has data on a different line will not be read correctly
o Speed issue with large number of files

-Features to be added-
o Sort by department

Revision Log

-0.6a-
o Expanded file search field (now from 0000.txt to 8999.txt)
o Now two versions:
	0.6a_no_response -> no response filter
	0.6a -> normal 5 or more responses only

-0.6-
o Added total question filter

-0.5-
o Added more efficient min and max function
o Added question description for Eval_Results.txt
o Added error for no text files present

-0.4-
o Print to file Eval_Results.txt added
o '1' marker added for debugging purposes


Please email me at jquinlan@ltu.edu if you have any questions.

--June 6, 2012--