// An emulator for the LOCAD COMPUTER
/*
  The LOCAD VIRTUAL MACHINE
  (c) Christian Albert Hagemeier, 2015
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add(int a[4],int b[4]);
int addc(int a[4],int b[4],int carry);

typedef struct{
  int acc[4];
  int c; // Carry Flag (Übertrag)
  int s;
  int z; // Zero Flag (Ergebnis der letzten Berechnung war null)
} alu;

void arrcpy(int nr,int* dest,int* src)
{
  for(int i = 0;i<nr;i++)
  {
    dest[i] = src[i];
  }
}
int doublebintoint(int a[4],int b[4])
{
  int res = 0;
  if(a[3] == 1){res += 1;}
  if(a[2] == 1){res += 2;}
  if(a[1] == 1){res += 4;}
  if(a[0] == 1){res += 8;}
  if(b[3] == 1){res += 16;}
  if(b[2] == 1){res += 32;}
  if(b[1] == 1){res += 64;}
  if(b[0] == 1){res += 128;}
  return res;
  
}
void getBin(int value, char* output)
{
    int i;
    output[7] = '\0';
    for (i = 7; i >= 0; --i, value >>= 1)
    {
        output[i] = (value & 1) + '0';
    }
}
// ALU FUNCTIONS
void alu_init(alu* alu)
{
  for(int i = 3;i>=0;i++)
    alu->acc[i] = 0;
  alu->c = 0;
  alu->s = 0;
  alu->z = 0;
}
void alu_dbg(alu* alu)
{
  printf("*** ALU DEBUG ***\n");
  printf("ACCU: %i%i%i%i\n",alu->acc[3],alu->acc[2],alu->acc[1],alu->acc[0]);
  printf("**  END DEBUG ***\n");
}

void alu_add(alu* alu,int op[4])
{
    alu->c = add(alu->acc,op);
    alu_dbg(alu);
}
void alu_addc(alu* alu,int op[4])
{
    printf("CFLAG: %i\n",alu->c);
    for(int i = 0;i<4;i++)
      printf("%i",op[i]);
    printf("\n");
    alu->c = addc(alu->acc,op,alu->c);
    alu_dbg(alu);
}


int arraycmp(int elem,int* arr1,int* arr2)
{
  for(int i = 0;i<elem;i++)
  {  if(arr1[i] != arr2[i]){
      return 0;
    }
  }
  return 1;
}
void arr_assign(int arr[4],int a,int b,int c,int d)
{
  arr[0] = a;
  arr[1] = b;
  arr[2] = c;
  arr[3] = d;
}
int ctoint(char c)
{
  return c - '0';
}
int main(int argc,char* argv[])
{
  
  if(argc != 2)
  {

    printf("Usage: ./emulator <filename> \n");
    return 1;
  }
  
  FILE* infile = fopen(argv[1],"r");
  if(infile == NULL)
  {
    printf("Ein Fehler geschah während des Öffnens der Datei.\n");
    return 2;
  }
  
  
  
  char buffer[255];
  int i = 0;
  int ram[256][4];
  for(int i = 0;i<256;i++)
  {
    for(int j = 0;j<4;j++)
      ram[i][j] = 0;
  }
  i = 0;
  alu* alu = malloc(sizeof(alu));

  
  // Syntax is one command per line
  while(fgets(buffer, sizeof(buffer), infile))
  {	
    char tcp[4];
    sscanf(buffer,"%c%c%c%c",&tcp[0],&tcp[1],&tcp[2],&tcp[3]);
    ram[i][0] = ctoint(tcp[0]);
    ram[i][1] = ctoint(tcp[1]);
    ram[i][2] = ctoint(tcp[2]);
    ram[i][3] = ctoint(tcp[3]);
    i++;
  }
  int oldi = i;
  for(int i = 0;i<oldi;i++)
  {
    for(int j = 0;j<4;j++)
      printf("%i ",ram[i][j]);
    printf("\n");
  }
  // EMULATE IT
  int debug = 1;
  for(int i = 0;i<256;i++)
  {
    // LETS RUN IT
    /*      for(int i = 3;i>=0;i--)
	printf("%i ",a[i]);
      printf("\n");
      for(int i = 3;i>=0;i--)
	printf("%i ",b[i]);

     * COMMANDS
     * STP 0 0 0 0
     * SPR0 0 0 0 1
     * SPR 0 0 1 0
     * EIN 0 0 1 1
     * AUS 0 1 0 0
     * LDA 0 1 0 1
     * SPA 0 1 1 0
     * ADD 0 1 1 1
     * ADDC1 0 0 0
     * SUBC1 0 0 1
     * SUB 1 0 1 0
     * AND 1 1 0 0
     * INC 1 1 0 1
     * LDAR 1 1 1 0
     * 
     */
    int test[] = {0,0,0,0};
    if(arraycmp(4,ram[i],test))
    {
      fclose(infile);
      if(debug)
      {
	printf("STOPPING THE PROGRAM\n");
	
	FILE* outfile = fopen("ram.dump","w");
	
	for(int i = 0;i<256;i++)
	{
	  for(int j = 0 ;j<4;j++)
	    fprintf(outfile,"%i ",ram[i][j]);
	  fprintf(outfile,"\n");
	}

	
	fclose(outfile);
	
      }
      free(alu);
      i += 2;
      return 0;
    }
    
    arr_assign(test,0,0,0,1);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)
	  printf("JUMP IF ACCU IS NULL %i \n",i);
      i += 2;
      continue;
    }
    arr_assign(test,0,0,1,0);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)
	printf("JUMP\n");
      i += 2;
      continue;   

    }

    arr_assign(test,0,0,1,1);
    if(arraycmp(4,ram[i],test))
    {
      // EIN - Gets Input (as decimal number)
      // Convert to decimal
      printf(" into %i \n",doublebintoint(ram[i+1],ram[i+2]));
      int cell = doublebintoint(ram[i+1],ram[i+2]);
      printf("Eingabe einer Zahl");
      int num = 0;
      char* res = malloc(sizeof(char)*8);
      if(res == NULL)
      {
	printf("Die virtuelle Maschine war nicht in der Lage Speicher zu allokieren. - Sofortiger Abbruch\n");
	return 3;
      }
      scanf("%i",&num);
      getBin(num,res);
      
      // Copy into array of integer
      int a[4] = {0,0,0,0};
      int b[4] = {0,0,0,0};
      for(int i = 7;i>=4;i--)
	a[i-4] = ctoint(res[i]);
      for(int i = 3;i>=0;i--)
	b[i] = ctoint(res[i]);
      // Store B in cell ; A in cell+1
      arrcpy(4,ram[cell+1],b);
      arrcpy(4,ram[cell],a);
      free(res);
    }
    
    arr_assign(test,0,1,0,0);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)
	printf("AUS\n");
      // Get the cell => output
      int cell = doublebintoint(ram[i+1],ram[i+2]);
      for(int i = 0;i<4;i++)
	printf("%i ",ram[cell+1][i]);
      for(int i = 0;i<4;i++)
	printf("%i ",ram[cell][i]);
      printf("\n");
      i += 2;
      continue;
    }     

    
    arr_assign(test,0,1,0,1);
    if(arraycmp(4,ram[i],test))
    {
      alu_dbg(alu);
      if(debug)
	printf("LDA\n");
      int cell = doublebintoint(ram[i+1],ram[i+2]);
      arrcpy(4,alu->acc,ram[cell]);
      printf("\n");
      alu_dbg(alu);
      i += 2;
      
      continue;
    }
    arr_assign(test,0,1,1,0);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)
	printf("SPA\n");
            alu_dbg(alu);

      int cell = doublebintoint(ram[i+1],ram[i+2]);
      arrcpy(4,ram[cell],alu->acc);
      

      i += 2;
      continue;
    }
    
    arr_assign(test,0,1,1,1);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)
	printf("ADD\n");
      alu_add(alu,ram[doublebintoint(ram[i+1],ram[i+2])]);
      i += 2;
      continue;
    }
    
    arr_assign(test,1,0,0,0);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)
	printf("ADDC\n");
      int cell = doublebintoint(ram[i+1],ram[i+2]);
      alu_addc(alu,ram[doublebintoint(ram[i+1],ram[i+2])]);
      i += 2;
      continue;
    }
    arr_assign(test,1,0,0,1);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)
	printf("SUBC\n");
      i += 2;
      continue;
    }
    
    arr_assign(test,1,0,1,0);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)arr_assign(test,1,0,1,0);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)
	printf("SUBC\n");
      i += 2;
      continue;
    }
	printf("SUBC\n");
      i += 2;
      continue;
    }
    
    arr_assign(test,1,0,1,1);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)
	printf("SUB\n");
      i += 2;
      continue;
    }
    
    arr_assign(test,1,1,0,0);
    if(arraycmp(4,ram[i],test))
    {
      if(debug)
	printf("AND\n");
      i += 2;
      continue;
    }
    i += 2;
    
  }
  
}