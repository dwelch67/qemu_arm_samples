
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
unsigned int GET8 ( unsigned int );
unsigned int GETPC ( void );
unsigned int GETSP ( void );
unsigned int GETMODE ( void );
void GO_USER ( unsigned int );
unsigned int DO_SWI ( unsigned int, unsigned int, unsigned int, unsigned int );

#define UART_BASE 0x101F1000
#define UARTDR    (UART_BASE+0x000)
#define UARTFR    (UART_BASE+0x018)

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
unsigned int swi_main ( unsigned int a, unsigned int b, unsigned int c, unsigned int d )
{
    switch(a)
    {
        case 0:
        {
            return(~b);
        }
        case 1:
        {
            return(GETMODE());
        }
    }
    return(0);
}
//-------------------------------------------------------------------
void user_main ( void )
{
    hexstring(GETMODE());
    hexstring(GETSP());
    hexstring(DO_SWI(0,0x1234,0,0));
    hexstring(DO_SWI(1,0x1234,0,0));
}
//-------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;

    uart_init();

    for(ra=0;ra<0x40;ra+=4)
    {
        hexstrings(ra);
        rb=GET32(ra);
        hexstrings(rb);
        rb=GET32(0x10000+ra);
        hexstring(rb);
    }

    hexstring(GETMODE());
    hexstring(GETSP());

    GO_USER((unsigned int)user_main);
    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
