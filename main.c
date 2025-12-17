// ELEC2645 Unit 2 Project Template
// Command Line Application Menu Handling Code
//gcc Op-amps/main.c Op-amps/op-amp.c -o opamp_calculator
//./opamp_calculator


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "op-amp.h"


/*======================= Prototypes =======================*/
// These helper functions support menu control and validation.
static void main_menu(void);             /* runs in the main loop */
static void print_main_menu(void);       /* output the main menu description */
static int  get_user_input(void);        /* get a valid integer menu choice */
static void select_menu_item(int input); /* run code based on user's choice */
static void go_back_to_main(void);       /* wait for 'b'/'B' to continue */
static int  is_integer(const char *s);   /* validate integer string */

int main(void)
{
    /* this will run forever until we call exit(0) in select_menu_item() */
    for(;;) {
        main_menu();
    }
    return 0;  /* not reached */
}

static void main_menu(void)
{
    print_main_menu();                 // Shows the list of menu options
    int input = get_user_input();      // Wait for valid integer input
    select_menu_item(input);           // Run the selected option
}

static int get_user_input(void)
{
    enum { MENU_ITEMS = 7 };           // number of selectable menu items (1 to 7)
    char buf[128];
    int valid_input = 0;
    int value = 0;

    // Loops until the user enters a valid menu number
    do {
        printf("\nSelect item: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error. Exiting.");
            exit(1);
        }

        buf[strcspn(buf, "\r\n")] = '\0';

        if (!is_integer(buf)) {
            printf("Enter an integer!\n");
        } else {
            value = (int)strtol(buf, NULL, 10);
            if (value >= 1 && value <= MENU_ITEMS) {
                valid_input = 1;
            } else {
                printf("Invalid menu item!\n");
            }
        }

    } while (!valid_input);

    return value;
}

static void select_menu_item(int input)
{
    switch (input) {
        case 1:
            menu_item_1();   // Inverting Amplifier
            go_back_to_main();
            break;
        case 2:
            menu_item_2();   // Non-inverting Amplifier
            go_back_to_main();
            break;
        case 3:
            menu_item_3();   // Attenuating Amplifier
            go_back_to_main();
            break;
        case 4:
            menu_item_4();   // Summing Amplifier
            go_back_to_main();
            break;
        case 5:
            View_saved_results();   //View saved results
            go_back_to_main();
            break;
        case 6:
            clear_saved_results();  // Clear saved results
            go_back_to_main();
            break;
        default:
            printf("code Exited!\n");
            exit(0);
    }
}

static void print_main_menu(void)
{
    printf("\n----------- Op-Amp Gain Calculator -----------\n\n");
    printf("\t1. Inverting Amplifier\n");
    printf("\t2. Non-Inverting Amplifier\n");
    printf("\t3. Attenuating Amplifier\n");
    printf("\t4. Summing Amplifier (3-input)\n");
    printf("\t5. View saved results\n");
    printf("\t6. Clear saved results\n");
    printf("\t7. Exit\n\n");
    printf("---------------------------------------------\n");
}

static void go_back_to_main(void)
{
    char buf[64];

    // Wait until user presses 'b' or 'B'
    do {
        printf("\nEnter 'b' or 'B' to go back to main menu: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error. Exiting.");
            exit(1);
        }
        buf[strcspn(buf, "\r\n")] = '\0';

    } while (!(buf[0] == 'b' || buf[0] == 'B') || buf[1] != '\0');
}

static int is_integer(const char *s)
{
    if (!s || !*s) return 0;
    if (*s == '+' || *s == '-') s++;
    if (!isdigit((unsigned char)*s)) return 0;

    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}
