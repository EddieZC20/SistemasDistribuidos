/* Archivo Calculadora.x */

struct inputs{
float i;
float j;
char operator;
};

program CALCU_PROG{
 version CALCU_VERS{
 float SUM(inputs) = 1;
 float RES(inputs) = 2;
 float DIV(inputs) = 3;
 float MUL(inputs) = 4;
 } = 1;
} = 0x2fffffff;
