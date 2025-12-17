
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "op-amp.h"




/* ======================================================== 
                   FILE HANDLING FUNCTIONS
   These functions allow the program to save and view
   previous calculation results in a text file (results.txt).
   ========================================================= */

void save_result(const char *text) {
    // Open file in append mode ==> keeps old results and adds new ones
    FILE *fp = fopen("results.txt", "a");
    if (!fp) {
        printf("Error: Could not open results.txt for writing.\n");
        return;
    }

    fprintf(fp, "%s\n", text);
    fclose(fp);
}

/* ---------------- Menu Item 5: show_saved_results ---------------- */
void View_saved_results(void) {
    FILE *fp = fopen("results.txt", "r");

    printf("\n----------- SAVED RESULTS -----------\n\n");

    // If file does not exist, tell the user
    if (!fp) {
        printf("No saved results found. (results.txt missing)\n");
        return;
    }

    char line[256];
    int empty = 1;   // used to detect if the file has zero lines

    // Reads the file line-by-line and print to the terminal
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
        empty = 0;
    }

    fclose(fp);

    if (empty) {
        printf("No saved results found.\n");
    }

    printf("\n-------------------------------------\n");
}

/* ---------------- Menu Item 6: show_saved_results ---------------- */
void clear_saved_results(void) {
    // Opening in 'w' mode and erases all contents immediately
    FILE *fp = fopen("results.txt", "w");
    if (!fp) {
        printf("Error: Could not clear saved results.\n");
        return;
    }
    fclose(fp);
    printf("\nSaved results have been cleared successfully.\n");
}

/* ========= SAFE INPUT HELPERS ========= */

double read_double(void) {
    char buf[1024], *endptr;
    double value;

    if (!fgets(buf, sizeof(buf), stdin)) {
        return NAN;
    }

    errno = 0;  // reset overflow flag

    value = strtod(buf, &endptr);

    if (endptr == buf) {
        return NAN;   // invalid numeric input (Not A Number)
    }

     if (errno == ERANGE) {
        return NAN;
    }

    // Reject extra characters 
    while (*endptr != '\0') {
        if (*endptr != '\n' && *endptr != ' ')
            return NAN;
        endptr++;
    }

    return value;
}

int read_int(void) {
    char buf[100], *endptr;
    long value;

    if (!fgets(buf, sizeof(buf), stdin)) {
        return -9999999;
    }

    errno = 0;
    value = strtol(buf, &endptr, 10);

    if (endptr == buf || errno == ERANGE) {
        return -9999999;
    }

    return (int)value;
}

/* ---------------- Menu Item 1: Inverting Amplifier ---------------- */
void menu_item_1(void) {
    int choice;
    double Rin, Rf, gain, desired_gain;

    printf("\n>> Inverting Amplifier\n");
    printf("1. Calculate gain from resistor values\n");
    printf("2. Calculate resistor values from desired gain\n");
    printf("3. Back to main menu\n");
    printf("Select option: ");

    choice = read_int();

    if (choice == 1) {
        /* -------- Option 1: User enters resistors => calculate gain -------- */
        printf("Enter Rin (Ohms): ");
        Rin = read_double();

        if (isnan(Rin)) { printf("Invalid input.\n"); return; }
        if (Rin <= 0) { printf("Error: Rin must be greater than zero.\n"); return; }
        

        printf("Enter Rf (Ohms): ");
        Rf = read_double();
        
        if (isnan(Rf)) { printf("Invalid input.\n"); return; }
        if (Rf < 0) { printf("Error: Rf values must be positive.\n"); return; }


        gain = fabs(-Rf / Rin);
        printf("Inverting Gain (Av) = %f\n", gain);

         char text[200];
        snprintf(text, sizeof(text),
                 "Inverting amplifier: Gain = %.6f (From: Rin=%.2f, Rf=%.2f)",
                 gain, Rin, Rf);

        save_result(text);
    }

    else if (choice == 2) {
        /* -------- Option 2: User enters desired gain + Rin => calculate Rf -------- */
        printf("Enter desired gain (Av): ");
        desired_gain = read_double();

        if (isnan(desired_gain)) { printf("Invalid input.\n"); return; }
        if (desired_gain > 1e9) { printf("Error: gain is too large to be meaningful.\n"); return; }
        if (desired_gain <= 0) { printf("Error: Gain must be positive.\n"); return; }


        printf("Enter Rin (Ohms): ");
        Rin = read_double();

        if (isnan(Rin)) { printf("Invalid input.\n"); return; }
        if (Rin > 1e9) {printf("Error: Rin is too large to be meaningful.\n"); return; }
        if (Rin <= 0) { printf("Error: Rin must be greater than zero.\n"); return; }
        

        Rf = desired_gain * Rin;
        printf("\nTo achieve a gain of %f:\n", desired_gain);
        printf("Use Rin = %f ohms\n", Rin);
        printf("Use Rf  = %f ohms\n", Rf);

        char text[200];
        snprintf(text, sizeof(text),
                 "Inverting amplifier (reverse calc): Rf=%.2f (From: Rin=%.2f, Gain=%.2f)",
                 Rin, desired_gain, Rf);

        save_result(text);
    }

    else if (choice == 3) {
        return;
    }

    else {
        printf("Invalid selection.\n");
    }
}

/* ---------------- Menu Item 2: Non-Inverting Amplifier ---------------- */
void menu_item_2(void) {
    int choice;
    double Rin, Rf, gain, desired_gain;

    printf("\n>> Non-Inverting Amplifier\n");
    printf("1. Calculate gain from resistor values\n");
    printf("2. Calculate resistor values from desired gain\n");
    printf("3. Back to main menu\n");
    printf("Select option: ");
    choice = read_int();

    if (choice == 1) {
        /* -------- Option 1: User enters resistors => calculate gain -------- */
        printf("Enter Rin (Ohms): ");
        Rin = read_double();

        if (isnan(Rin)) { printf("Invalid input.\n"); return; }
        if (Rin <= 0) { printf("Error: Rin must be greater than zero.\n"); return; }


        printf("Enter Rf (Ohms): ");
        Rf = read_double();

        if (isnan(Rf)) { printf("Invalid input.\n"); return; }
        if (Rf < 0) { printf("Error: Rf values must be positive.\n"); return; }


        gain = 1 + (Rf / Rin);
        printf("Non-Inverting Gain (Av) = %f\n", gain);

        char text[200];
        snprintf(text, sizeof(text),
                 "Non-inverting amplifier: Gain = %.6f (From: Rin=%.2f, Rf=%.2f)",
                 gain, Rin, Rf);

        save_result(text);
    }

    else if (choice == 2) {
        /* -------- Option 2: User enters desired gain + Rin => calculate Rf -------- */
        printf("Enter desired gain (Av): ");
        desired_gain = read_double();

        if (isnan(desired_gain)) { printf("Invalid input.\n"); return; }
        if (desired_gain > 1e9) { printf("Error: gain is too large to be meaningful.\n"); return; }
        if (desired_gain <= 1) { printf("Error: Gain must be greater than 1.\n"); return; }


        printf("Enter Rin (Ohms): ");
        Rin = read_double();

        if (isnan(Rin)) { printf("Invalid input.\n"); return; }
        if (Rin > 1e9) { printf("Error: Rin is too large to be meaningful.\n"); return; }
        if (Rin <= 0) { printf("Error: Rin must be greater than zero.\n"); return; }
        

        Rf = (desired_gain - 1) * Rin;
        printf("\nTo achieve a gain of: %f\n", desired_gain);
        printf("Use Rin = %f ohms\n", Rin);
        printf("Use Rf  = %f ohms\n", Rf);

        char text[200];
        snprintf(text, sizeof(text),
                 "Non-inverting (reverse calc): Rf=%.2f (From: Rin=%.2f, Gain=%.2f)",
                 Rin, desired_gain, Rf);

        save_result(text);
    }

    else if (choice == 3) {
        return;
    }

    else {
        printf("Invalid selection.\n");
    }
}

/* ---------------- Menu Item 3: Attenuating Amplifier ---------------- */
void menu_item_3(void) {
    double R1, R2;

    printf("\n>> Attenuator Amplifier\n");
    printf("Enter R1 (Ohms): ");
    R1 = read_double();

    if (isnan(R1)) { printf("Invalid input.\n"); return; }
    if (R1 < 0) { printf("Error: R1 value must be positive.\n"); return; }


    printf("Enter R2 (Ohms): ");
    R2 = read_double();

    if (isnan(R2)) { printf("Invalid input.\n"); return; }
    if (R2 <= 0) { printf("Error: R2 value must be positive.\n"); return; }


    double gain = R2 / (R1 + R2);
    printf("Attenuator Gain (Av) = %f\n", gain);

    char text[200];
    snprintf(text, sizeof(text),
             "Attenuator: Gain = %.6f (From: R1=%.2f, R2=%.2f)",
             gain, R1, R2);

    save_result(text);
}

/* ---------------- Menu Item 4: Summing Amplifier ---------------- */
void menu_item_4(void) {
    double R1, R2, R3, Rf;

    printf("\n>> Summing Amplifier (3 Inputs)\n");


    printf("Enter R1 (Ohms): ");
    R1 = read_double();

    if (isnan(R1)) { printf("Invalid input.\n"); return; }
    if (R1 > 1e9) { printf("Error: R1 is too large to be meaningful.\n"); return; }
    if (R1 <= 0) { printf("Error: R1 value must be greater than zero.\n"); return; }


    printf("Enter R2 (Ohms): ");
    R2 = read_double();
    
    if (isnan(R2)) { printf("Invalid input.\n"); return; }
    if (R2 > 1e9) { printf("Error: R2 is too large to be meaningful.\n"); return; }
    if (R2 <= 0) { printf("Error: R2 value must be greater than zero.\n"); return; }


    printf("Enter R3 (Ohms): ");
    R3 = read_double();

    if (isnan(R3)) { printf("Invalid input.\n"); return; }
    if (R3 > 1e9) { printf("Error: R3 is too large to be meaningful.\n"); return; }
    if (R3 <= 0) { printf("Error: R3 value must be greater than zero.\n"); return; }


    printf("Enter Rf (Ohms): ");
    Rf = read_double();

    if (isnan(Rf)) { printf("Invalid input.\n"); return; }
    if (Rf > 1e9) { printf("Error: Rf is too large to be meaningful.\n"); return; }
    if (Rf <= 0) { printf("Error: Rf value must be greater than zero.\n"); return; }


    double gain = fabs(-((Rf / R1) + (Rf / R2) + (Rf / R3)));
    printf("Total Summing Amplifier Gain (Av) = %f\n", gain);

    char text[200];
    snprintf(text, sizeof(text),
             "Summing amplifier: Total Gain = %.6f (From: R1=%.2f, R2=%.2f, R3=%.2f, Rf=%.2f)",
             gain, R1, R2, R3, Rf);

    save_result(text);
}
