Op-Amp Gain Calculator 
- This application is a command-line tool that calculates the gain of several types of operational-amplifier configurations. 
It provides safe input handling, file saving features, and easy way to navigate menu system.  


Features 
1. Inverting Amplifier 
- Calculate gain using Rin and Rf 
- Reverse calculation: compute Rf needed for a chosen gain 

2. Non-Inverting Amplifier 
- Calculate gain from resistor values 
- Reversed calculation: compute Rf needed for a chosen gain 

3. Attenuating Amplifier 
- Computes attenuation ratio using R1 and R2 

4. Summing Amplifier (3-input) 
- Calculates the total gain using R1, R2, R3, and Rf 

5. File handling 
- Save calculation results to results.txt 
- View all saved results from the menu 
- Clear saved results (reset the file) 

 
How the program works 
1. Program starts in main.c 
The main file displays the intractive menu and waits for the user to choose an option. 

2. User input is safely validated 
All numerical entries are processed using custom helper functions like (read_int() and read_double()), preventing crashes from invalid inputs like letters or symbols. 

3. Menu item functions perform calculations 
Each amplifier mode has its own function inside (op-amp.c), which performs the correct formulas and prints the results. 

4. Users can view or clear stored results 
After each calculation, the program stores a formatted summary inside results.txt. 

5. Users can view or clear stored results 
Menu items allow reviewing past calculations or resetting the file entirely. 

6. Program loops back to the main menu 
After each operation, the user can return by passing ‘b’ or ‘B’, keeping the program running until ‘Exit’ is selected. 