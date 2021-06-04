#include "TM4C123.h" //header

#define LCD_DATA GPIOB
#define LCD_CTRL GPIOA
#define RS 0x20 /* PORTA BIT5 mask */
#define RW 0x40 /* PORTA BIT6 mask */
#define EN 0x80 /* PORTA BIT7 mask */

void delayMs(int n);
void delayUs(int n);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void keypad_init(void);
unsigned char keypad_kbhit(void);
void keypad_init(void);
unsigned char keypad_getkey(void);


int main(void)
{
unsigned char key;
keypad_init();
LCD_init();
  
while(1)
{
LCD_command(0x80);    /* LCD cursor location */
key = keypad_getkey();    /* read the keypad */

/* if a key is pressed */ 
if (key != 0)   
{
LCD_data(key);   /* display the key label */
} 
else
LCD_data(' ');
delayMs(20);    /* wait for 20 mS */
}
}

#define KEYPAD_ROW GPIOE
#define KEYPAD_COL GPIOC

/*initialize the ports connected to the keypad */
void keypad_init(void)
{
SYSCTL->RCGCGPIO |= 0x04; 
SYSCTL->RCGCGPIO |= 0x10; 
 
KEYPAD_ROW->DIR |= 0x0F; 
KEYPAD_ROW->DEN |= 0x0F; 
KEYPAD_ROW->ODR |= 0x0F; 
 
KEYPAD_COL->DIR &= ~0xF0; 
KEYPAD_COL->DEN |= 0xF0; 
KEYPAD_COL->PUR |= 0xF0; 
}

/*function to read the keypad. */
/* If a key is pressed, it returns the key label. else, it returns 0 */
unsigned char keypad_getkey(void)
{
const unsigned char keymap[4][4] =
{
{ '1', '2', '3', 'A'},
{ '4', '5', '6', 'B'},
{ '7', '8', '9', 'C'},
{ '*', '0', '#', 'D'},
};
int row, col;
/* check to see if any key pressed first */
KEYPAD_ROW->DATA = 0;             /* enable all rows */
col = KEYPAD_COL->DATA & 0xF0;    /* read all columns */
if (col == 0xF0) 
   return 0;         /* no key pressed */
