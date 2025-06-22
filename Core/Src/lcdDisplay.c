#include "main.h"

//Prototypes:
void LCD_Manager();
void register_EN(void);
void initialize_LCD(void);
void function_Set(void);
void display_Off(void);
void clear_Display(void);
void entry_mode_Set(void);
void display_On(void);
void Write_Display(void);
void Write_caracter(uint8_t c);
void Set_Line(char line);
void registra_RS(void);
void change_Message(uint8_t line, char *new_Text);
void lcd_send_command(uint8_t cmd);

//Variaveis Locais
int8_t status_LCD_startup = 1;
char message[2][17] = {"                ", "                "};
uint8_t position_String = 0;
uint8_t position_line = 0;
uint8_t linha_LCD = 0;
uint8_t changed = FALSE;

void lcd_send_data(uint8_t data);

void register_EN(void) {
    EN_HIGH;
    LCD_delay_us(1);
    EN_LOW;
    LCD_delay_us(40);
}

//void initialize_LCD(void) {
//    LCD_delay_ms(16); //15ms
//    function_Set();
//    LCD_delay_ms(5); //4.1 ms
//    function_Set();
//    LCD_delay_ms(100); //100 usegundos
//    function_Set();
//    function_Set();
//    display_Off();
//    clear_Display(); //demora 2 ms essa funзгo
//    entry_mode_Set();
//    display_On();
//}

//void function_Set(void) {
//    RS_LOW;
//    DB7_LOW;
//    DB6_LOW;
//    DB5_HIGH;
//    DB4_HIGH;
//    DB3_HIGH;
//    DB2_LOW;
//    DB1_LOW;
//    DB0_LOW;
//    register_EN();
//}
//
//void clear_Display(void) {
//    RS_LOW;
//    DB7_LOW;
//    DB6_LOW;
//    DB5_LOW;
//    DB4_LOW;
//    DB3_LOW;
//    DB2_LOW;
//    DB1_LOW;
//    DB0_HIGH;
//    register_EN();
//    LCD_delay_us(1500);
//}
//
//void display_Off(void) {
//    RS_LOW;
//    DB7_LOW;
//    DB6_LOW;
//    DB5_LOW;
//    DB4_LOW;
//    DB3_HIGH;
//    DB2_LOW;
//    DB1_LOW;
//    DB0_LOW;
//    register_EN();
//}
//
//void display_On(void) {
//    RS_LOW;
//    DB7_LOW;
//    DB6_LOW;
//    DB5_LOW;
//    DB4_LOW;
//    DB3_HIGH;
//    DB2_HIGH;
//    DB1_HIGH;
//    DB0_HIGH;
//    register_EN();
//}

//void entry_mode_Set(void) {
//    RS_LOW;
//    DB7_LOW;
//    DB6_LOW;
//    DB5_LOW;
//    DB4_LOW;
//    DB3_LOW;
//    DB2_HIGH;
//    DB1_HIGH;
//    DB0_LOW;
//    register_EN();
//}

void Write_Display() {
    if(changed){

        lcd_set_cursor(position_String, position_line);
        Write_caracter(message[position_line][position_String]);
        position_String++;

        if(position_String >= 16){
            position_String = 0;
            
            if(position_line == 0){

                position_line = 1;
                
            } else {

                position_line = 0;
                changed = FALSE;
            }

        
        }
    }
}

void Write_caracter(uint8_t c) {
	lcd_send_data(c);
}

void registra_RS(void) {
    RS_HIGH;
    LCD_delay_us(1);
    EN_HIGH;
    LCD_delay_us(1);
    EN_LOW;
    LCD_delay_us(1);
    RS_LOW;
}

void Set_Line(char line) {
	if (line == 0)
	        lcd_send_command(0x80);  // linha 1
	    else
	        lcd_send_command(0xC0);  // linha 2
}

void change_Message(uint8_t line, char *new_Text) {
    uint8_t i = 0;
    //Verifica onde acaba a string enviada
    while (new_Text[i] != '\0' && i < 16) {

        if (message[line][i] != new_Text[i]) {
                message[line][i] = new_Text[i];
                changed = TRUE;
            }
        i++;
    }
    for (i = i; i < 16; i++) {
        message[line][i] = ' ';
    }
}

void send_nibble(uint8_t nibble) {
    (nibble & 0x08) ? DB7_HIGH : DB7_LOW;
    (nibble & 0x04) ? DB6_HIGH : DB6_LOW;
    (nibble & 0x02) ? DB5_HIGH : DB5_LOW;
    (nibble & 0x01) ? DB4_HIGH : DB4_LOW;

    register_EN();
}

void lcd_send_command(uint8_t cmd) {
    RS_LOW;
    send_nibble(cmd >> 4);  // parte alta
    send_nibble(cmd & 0x0F); // parte baixa
    //LCD_delay_us(40);
}

void lcd_send_data(uint8_t data) {
    RS_HIGH;
    //LCD_delay_us(1);
    send_nibble(data >> 4);
    send_nibble(data & 0x0F);
    //LCD_delay_us(40);
    RS_LOW;
}

void initialize_LCD(void) {
    LCD_delay_ms(15); // tempo mínimo de boot

    // Inicialização especial para 4 bits
    send_nibble(0x03);  // função set 8 bits (3)
    LCD_delay_ms(5);
    send_nibble(0x03);
    LCD_delay_us(150);
    send_nibble(0x03);
    LCD_delay_us(150);
    send_nibble(0x02);  // função set para 4 bits
    LCD_delay_us(150);

    lcd_send_command(0x28); // function set: 4 bits, 2 linhas, 5x8
    lcd_send_command(0x08); // display OFF
    lcd_send_command(0x01); // clear display
    LCD_delay_ms(2);
    lcd_send_command(0x06); // entry mode set
    lcd_send_command(0x0C); // display ON, cursor OFF
}

void lcd_create_char(uint8_t pos, uint8_t *pattern) {
    // CGRAM começa em 0x40, cada caractere ocupa 8 bytes
    lcd_send_command(0x40 | (pos << 3));  // endereço CGRAM para caractere N
    for (int i = 0; i < 8; i++) {
        lcd_send_data(pattern[i]);   // envia cada linha do caractere
    }
}

void lcd_cursor_on(void) {
    lcd_send_command(0x0F); // display ON, cursor ON
}
void lcd_cursor_off(void) {
    lcd_send_command(0x0C); // display ON, cursor OFF
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
    if (row == 0) {
        lcd_send_command(0x80 + col); // linha 1
    } else {
        lcd_send_command(0xC0 + col); // linha 2
    }
}