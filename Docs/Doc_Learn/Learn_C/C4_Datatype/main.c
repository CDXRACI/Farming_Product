#include <stdio.h>
#include <stdlib.h>

/*
Boolean ( C++ ) in C #inc   1 BIT
CHAR                        1 BYTE -127 -> 127 // NGOAI RA CHAR ( KIEU KY TU DE IN KY TU RA MAN HINH HIEN THI )
Unsigned CHAR               1 BYTE 0 -> 255
SHORT                       2 ( -32768 -> 32767 ) LIKE INTEGER BUT 2 BYTES
UNSIGNED SHORT              2 ( 0 -> 65535 )
INT                         4 ( -2,147,483,648  -> 2,147,483,647 )
UNSIGNED INT                4 //
LONG                        4 //
LONG LONG                   8 //
float                       4 // 3.4 +/ -38
DOUBLE                      8 // 1.7E +/ -308
long double                 8 //

*/
unsigned int g_val = 10;
/*
Bang ma ascii

*/
char p = 12;

int main()
{
    printf("Hello world!\n");
    printf("print integer's value is = %d\r\n", g_val);
    printf("ascii char %c", p + 41 );
    return 0;
}
