#ifndef OP_AMP_H
#define OP_AMP_H

/* --- SAFE INPUT HELPERS --- */
double read_double(void);
int read_int(void);

/* --- FILE HANDLING FUNCTIONS --- */
void save_result(const char *text);
void View_saved_results(void);    //Show saved results
void clear_saved_results(void);   //Delete saved results

/* --- AMPLIFIER CALCULATION FUNCTIONS --- */
void menu_item_1(void);   // Inverting Amplifier
void menu_item_2(void);   // Non-inverting Amplifier
void menu_item_3(void);   // Attenuating Amplifier
void menu_item_4(void);   // Summing Amplifier

#endif



