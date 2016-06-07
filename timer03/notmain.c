
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
unsigned int GET8 ( unsigned int );
unsigned int GETPC ( void );

void IRQ_ENABLE ( void );

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

#define NVIC_BASE       0x10140000
#define VICIRQSTATUS    (NVIC_BASE+0x000)
#define VICFIQSTATUS    (NVIC_BASE+0x004)
#define VICRAWINTR      (NVIC_BASE+0x008)
#define VICINTSELECT    (NVIC_BASE+0x00C)
#define VICINTENABLE    (NVIC_BASE+0x010)
#define VICINTENCLEAR   (NVIC_BASE+0x014)
#define VICSOFTINT      (NVIC_BASE+0x018)


    //dev = sysbus_create_varargs("pl190", 0x10140000,

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
volatile unsigned int tcount;
void irq_main ( void )
{
    PUT32(TIMER0_INTCLR,0);
    tcount++;
    hexstring(tcount);
}
//-------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;
    unsigned int rd;
    unsigned int re;

    uart_init();
    hexstring(0x12345678);

if(0)
{
    PUT32(TIMER0_CONTROL,0x00);
    PUT32(TIMER0_LOAD,0x000FFFFF);
    PUT32(TIMER0_INTCLR,0);
    PUT32(TIMER0_CONTROL,0xE2);

if(0)
{
    PUT32(VICINTENABLE,0x10);
}
    
    for(rc=0;rc<5;)
    {
        ra=GET32(TIMER0_RIS);
        rd=GET32(TIMER0_RIS);
        rb=GET32(VICRAWINTR);
        re=GET32(VICIRQSTATUS);
        hexstrings(ra); hexstrings(rd); hexstrings(re); hexstring(rb);
        if(ra) rc++;
    }
    PUT32(TIMER0_INTCLR,0);
    ra=GET32(TIMER0_RIS);
    rd=GET32(TIMER0_RIS);
    rb=GET32(VICRAWINTR);
    re=GET32(VICIRQSTATUS);
    hexstrings(ra); hexstrings(rd); hexstrings(re); hexstring(rb);
}

    tcount=0;
    PUT32(TIMER0_CONTROL,0x00);
    PUT32(TIMER0_LOAD,0x000FFFFF);
    PUT32(TIMER0_INTCLR,0);
    PUT32(TIMER0_CONTROL,0xE2);
    PUT32(VICINTENABLE,0x10);
    IRQ_ENABLE();

    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
