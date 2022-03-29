sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;
sbit LCD_D4 at RC4_bit;         //Conexao Pic ->LCD
sbit LCD_D5 at RC5_bit;
sbit LCD_D6 at RC6_bit;
sbit LCD_D7 at RC7_bit;




sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;
sbit LCD_D4_Direction at TRISC4_bit;        //Conexao Pic ->LCD
sbit LCD_D5_Direction at TRISC5_bit;
sbit LCD_D6_Direction at TRISC6_bit;
sbit LCD_D7_Direction at TRISC7_bit;

int duty=127;                            //Duty Cycle
int contador=0;
const int frequencia=500;                //Frequencia PWM
char *texto = "PWM ";             //Texto para LCD
char texto1[7];                            //Variavel para Converter o Duty Cycle para String  e mostrar no LCD

void interrupt(){
     if(T0IF_bit==1){
         T0IF_bit=0;
         TMR0=100;
         contador++;

         if(contador>=2){
               contador=0;                                //Interrupçao, se os botoes forem pressionados, o duty cycle ira aumentar ou diminuir
               if(RD0_bit==0){
               duty++;
               }else if(RD1_BIT==0){
                duty--;
               }
         }
          if(duty >=256){
                 duty=0;
                                                                //se o duty cycle passar do limite, esse if o retorna para um valor aceitavel
          }
          if(duty < 0) {
               duty=255;
          }
     }



}


void main() {
    OPTION_REG =0x86;
    INTCON=0b10100000;
    TMR0=100;
    TRISD=0x03;
    TRISC=0x00;
    PORTD=0x03;
    PORTC=0X00;
    PWM1_Init(frequencia);
    PWM1_Start();                                    //Inicio Módulo PWM
    PWM1_Set_Duty(duty);

    Lcd_Init();
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Cmd(_LCD_CLEAR);                              //Inicio Módulo LCD
    Lcd_Out(1,2,texto);

    while(1){
        PWM1_Set_Duty(duty);
        
        IntToStr(duty,texto1);                                              //Converter o valor do duty em string e mostrar no LCD
        Lcd_Out(2,1,texto1);
        
        
        delay_ms(70);


    }


}