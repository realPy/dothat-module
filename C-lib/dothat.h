
void backlight_rgb(int, int, int);
void backlight_led_rgb(int, int, int, int);
void backlight_array(int [5][2]);
void lcd_clear(void);
void lcd_contrast(int);
void lcd_cursor(int, int);
void lcd_cursor_pos(int,int);
void lcd_text(char *);
void lcd_text_line(int , char *);
void lcd_text_lines(char *, char *, char *);
void graph_bar(int, int);
void led_intensity(int, int);
void led_state(int, int);
void led_polarity(int, int);
int led_get_state(int);
int led_get_polarity(int);
void led_states(int, int, int, int, int, int);
void led_polarities(int, int, int, int, int, int);
