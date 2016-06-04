
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
unsigned int GET8 ( unsigned int );
unsigned int GETPC ( void );

#define UART_BASE 0x101F1000
#define UARTDR    (UART_BASE+0x000)
#define UARTFR    (UART_BASE+0x018)


#define TIMER0_BASE     0x101E2000
#define TIMER0_LOAD     (TIMER0_BASE+0x00)
#define TIMER0_VALUE    (TIMER0_BASE+0x04)
#define TIMER0_CONTROL  (TIMER0_BASE+0x08)
#define TIMER0_INTCLR   (TIMER0_BASE+0x0C)
#define TIMER0_RIS      (TIMER0_BASE+0x10)
#define TIMER0_MIS      (TIMER0_BASE+0x14)
#define TIMER0_BGLOAD   (TIMER0_BASE+0x18)


    /* 0x101e2000 Timer 0/1.  */
    //sysbus_create_simple("sp804", 0x101e2000, pic[4]);

//-------------------------------------------------------------------
static void uart_send ( unsigned int x )
{
    while(1)
    {
        if(GET32(UARTFR)&(1<<7)) break;
    }
    PUT32(UARTDR,x);
}
//-------------------------------------------------------------------
//static unsigned int uart_recv ( void )
//{
    //while(1)
    //{
        //if(GET32(UARTFR)&(1<<6)) break;
    //}
    //return(GET32(UARTDR));
//}
//-------------------------------------------------------------------
static void uart_init(void)
{
    GET32(UARTDR);
}
//-------------------------------------------------------------------
static void hexstrings ( unsigned int d )
{
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_send(rc);
        if(rb==0) break;
    }
    uart_send(0x20);
}
//-------------------------------------------------------------------
static void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_send(0x0D);
    uart_send(0x0A);
}
//-------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;

    uart_init();
    hexstring(0x12345678);

    PUT32(TIMER0_CONTROL,0x00);
    PUT32(TIMER0_LOAD,0xFFFFFFFF);
    PUT32(TIMER0_INTCLR,0);
    PUT32(TIMER0_CONTROL,0x80);

    hexstring(GET32(TIMER0_RIS));
    ra=0xFFFF;
    while(1)
    {
        rb=GET32(TIMER0_VALUE);
        //hexstring(rb);
        if(rb>ra) break;
        ra=rb;
    }
    hexstring(GET32(TIMER0_RIS));
    PUT32(TIMER0_INTCLR,0);
    for(ra=0;ra<5;)
    {
        rb=GET32(TIMER0_RIS);
        if(rb)
        {
            PUT32(TIMER0_INTCLR,0);
            hexstring(ra);
            ra++;
        }
    }

if(0)
{
    PUT32(TIMER0_CONTROL,0x00);
    PUT32(TIMER0_LOAD,0x000FFFFF);
    PUT32(TIMER0_INTCLR,0);
    PUT32(TIMER0_CONTROL,0xC2);
    while(1)
    {
        hexstring(GET32(TIMER0_VALUE));
        //if(GET32(TIMER0_RIS)) break;
    }
}

    PUT32(TIMER0_CONTROL,0x00);
    PUT32(TIMER0_LOAD,0x001FFFFF);
    PUT32(TIMER0_INTCLR,0);
    PUT32(TIMER0_CONTROL,0xC2);
    for(ra=0;ra<5;)
    {
        rb=GET32(TIMER0_RIS);
        if(rb)
        {
            PUT32(TIMER0_INTCLR,0);
            hexstring(ra);
            ra++;
        }
    }

    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
