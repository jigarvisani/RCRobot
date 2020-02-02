#include <avr/io.h>
#include <util/delay.h>
#define ubrr 51
#define MOSI PINB2
#define SCK PINB1
#define SS PINB0
#define MISO PINB3
void spi_master(void)
 {
	DDRB|=(1<<MOSI)|(1<<SCK)|(1<<SS);
	SPCR|=(1<<SPE)| (1<<MSTR) | (1<<SPR0);
	}
	
void initialise () //initializing UART
	{ 
	UBRRH =(51>>8);
	UBRRL =51;
	UCSRB =0b00011000 ;
	UCSRC =0b10000110 ;	// enabling receiver and transmitor
	
	}
	void letter(unsigned char x) //send letter
	{
	while(!((UCSRA) & (1<<UDRE)));
	//PORTC=0b00000001;
	UDR= x;
	}

unsigned char mastertransmit(unsigned char edata)
{
	PORTB|=(1<<MOSI)|(1<<SCK);/*high of pins*/
	PORTB&=~(1<<SS);
	SPDR=edata;
	while(!(SPSR&(1<<SPIF)));
	_delay_us(200);
	return SPDR;
}

void shortpoll(void)
{
	PORTB|=(1<<MOSI)|(1<<SCK);/*high of pins*/
	PORTB&=~(1<<SS);
	mastertransmit(0x01);
	mastertransmit(0x042);
	mastertransmit(0x00);
	mastertransmit(0xFF);
	mastertransmit(0xFF);
	PORTB|=(1<<SS);
}
	
void config(void)
	{
	PORTB|=(1<<MOSI)|(1<<SCK);/*high of pins*/
	PORTB&=~(1<<SS);
	mastertransmit(0x01);
	mastertransmit(0x43);
	mastertransmit(0x00);
	mastertransmit(0x01);
	mastertransmit(0x00);
	PORTB|=(1<<MOSI);
	_delay_ms(1);
	PORTB|=(1<<SS);
	}

void modesel(void)
	{
	PORTB|=(1<<MOSI)|(1<<SCK);/*high of pins*/
	PORTB&=~(1<<SS);
	mastertransmit(0x01);
	mastertransmit(0x44);
	mastertransmit(0x00);
 mastertransmit(0x01);
	mastertransmit(0x03);
	mastertransmit(0x00);
	mastertransmit(0x00);
	mastertransmit(0x00);
	mastertransmit(0x00);
	
	PORTB|=(1<<MOSI);
	_delay_ms(1);
	PORTB|=(1<<SS);
	
	
	}

void exit(void)
	{
	PORTB|=(1<<MOSI)|(1<<SCK);/*high of pins*/
	PORTB&=~(1<<SS);
	mastertransmit(0x01);
	mastertransmit(0x43);
	mastertransmit(0x00);
	mastertransmit(0x00);
	mastertransmit(0x5A);
	mastertransmit(0x5A);
	mastertransmit(0x5A);
	mastertransmit(0x5A);
	mastertransmit(0x5A);
	PORTB|=(1<<MOSI);
	_delay_ms(1);
	PORTB|=(1<<SS);
	}

/*unsigned char mastertransmit(unsigned char edata)
	{
	PORTB|=(1<<MOSI)|(1<<SCK);/*high of pins
	PORTB&=~(1<<SS);
	SPDR=edata;
	while(!(SPSR&(1<<SPIF)));
	_delay_us(200);
	return SPDR;
	}*/
	
int main(void)
{
	DDRC=0b00000001;
	initialise();
 spi_master();
	//PORTC=0b00000001;
	//mastertransmit('a');
	letter('a');
	_delay_ms(200);
	unsigned char d;
	
	while(d!=0x73)
	{
	/*//shortpoll();//to make connection
	//	PORTC=0b00000000;
	//PORTC=0b00000001;
	//shortpoll();
	//shortpoll();
	//_delay_us(10);
	config();//to configure or statrt connection 
	_delay_ms(10);
	modesel();//analog mode selected
	_delay_ms(10);
	exit();
	_delay_ms(10);
	PORTB&=~(1<<SS);
	
	mastertransmit(0x01);//header 
	//	PORTC=0b00000001;
	d=mastertransmit(0x42);//header
	PORTC=0b00000001;
 letter('a');
	letter(d);
	mastertransmit(0x00);//header
	mastertransmit(0x00);//button set1
	mastertransmit(0x00);//button set2
	mastertransmit(0x00);//rx 
	mastertransmit(0x00);//ry
	mastertransmit(0x00);//lx
	mastertransmit(0x00);//ly
	PORTB|=(1<<MOSI);
	_delay_ms(1);
	PORTB|=(1<<SS);
	_delay_ms(10);*/
	
	
	PORTB|=(1<<MOSI)|(1<<SCK);/*high of pins*/
	PORTB&=~(1<<SS);
	mastertransmit(0x01);
	mastertransmit(0x43);
	mastertransmit(0x00);
	mastertransmit(0x01);
	mastertransmit(0x00);
	PORTB|=(1<<MOSI);
	_delay_ms(1);
	PORTB|=(1<<SS);
	
	_delay_ms(10);
	
	PORTB|=(1<<MOSI)|(1<<SCK);/*high of pins*/
	PORTB&=~(1<<SS);
	mastertransmit(0x01);
	mastertransmit(0x44);
	mastertransmit(0x00);
	mastertransmit(0x01);
	mastertransmit(0x03);
	mastertransmit(0x00);
	mastertransmit(0x00);
	mastertransmit(0x00);
	mastertransmit(0x00);
	
	PORTB|=(1<<MOSI);
	_delay_ms(1);
	
	PORTB|=(1<<SS);
	_delay_ms(10);
	PORTB|=(1<<MOSI)|(1<<SCK);/*high of pins*/
	PORTB&=~(1<<SS);
	mastertransmit(0x01);
	mastertransmit(0x43);
	mastertransmit(0x00);
	mastertransmit(0x00);
	mastertransmit(0x5A);
	mastertransmit(0x5A);
	mastertransmit(0x5A);
	mastertransmit(0x5A);
	mastertransmit(0x5A);
	PORTB|=(1<<MOSI);
	_delay_ms(1);
	PORTB|=(1<<SS);
	
	_delay_ms(10);
	
	PORTB|=(1<<MOSI)|(1<<SCK);/*high of pins*/
	PORTB&=~(1<<SS);
	
	mastertransmit(0x01);//header
	d=mastertransmit(0x42);//header
	PORTC=0b00000001;
	letter('a');
	letter(d);
	mastertransmit(0x00);//header
	mastertransmit(0x00);//button set1
	mastertransmit(0x00);//button set2
	mastertransmit(0x00);//rx
	mastertransmit(0x00);//ry
	mastertransmit(0x00);//lx
	mastertransmit(0x00);//ly
	PORTB|=(1<<MOSI);
	_delay_ms(1);
	PORTB|=(1<<SS);
	_delay_ms(10);
	
	}
	//PORTC=0b00000001;

	//mastertransmit('b');
	
	//PORTC=0b00000000;
	
	while(1)
	{
	PORTB&=~(1<<SS);
	mastertransmit(0x01);
	d=mastertransmit(0x42);
	mastertransmit(0x00);
	unsigned char bs1=mastertransmit(0x00);//saving slave data
	unsigned char bs2= mastertransmit(0x00);//saving slave data
	PORTB|=(1<<SS);
	
	
	/*
	mastertransmit(0x00);
	mastertransmit(0x00);
	mastertransmit(0x00);
	mastertransmit(0x00);*/
	
	}

}