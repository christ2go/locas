#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ramsize 256 
enum command_s { STP = 0, SPR0, SPR, EIN, AUS, LDA, SPA, ADD, ADDC, SUBC, SUB, AND, INK, LDAR } asc;

typedef struct
{
  char name[255];
  int begin;
  int end;
  int len;
} identifier;
typedef struct
{
  int command;
  char argument[255];
} command;
  command commands[ramsize];
  int ccount = 0;
  identifier identifiers[ramsize];
  int identc = 0;
  char buffer[256];
  int line = 1;
  int ramcell = 0;

char* int2bin(int a)
{
  char* res = malloc(sizeof(char)*8);
  for(int i = 7;i>=0;i--)
  {
    int x = a % 2;
    a = (int) (a/2);
    if(x == 0)
      res[i] = '0';
    else
      res[i] = '1';
    
  }
  return res;
}

void writeLn(char* content,FILE* file)
{
  fprintf(file,"%s\n",content);
}

void writeNBR(int n,FILE* outfile)
{
  	char* nbr = int2bin(n);
	char* low = malloc(sizeof(char)*4);
	char* high = malloc(sizeof(char)*4);
	strncpy(high,nbr,4);
	strncpy(low,nbr+4,4);
	writeLn(low,outfile);

	writeLn(high,outfile);
	free(high);
	free(low);
	free(nbr);

}

int getcell(char* identifier)
{
  for(int i = 0;i<identc;i++)
  {
    if(strcmp(identifiers[i].name,identifier) == 0)
      return identifiers[i].begin;
  }
}
int main(int argc,char* argv[])
{
  if(argc == 1)
  {
    printf("Please run this program0000 with the following options: ./assembler <infile> [outfile]\n");
    return 1;
  }
  
  // Assembler Version 0.0.1
  int ram[100][4];
  for(int i = 0;i<100;i++)
    for(int j = 0;j<4;j++)
      ram[i][j] = 0; 
  for(int i = 0;i<ramsize;i++)
  {
    commands[i].command = 2;

  }
 // Ram is "nulled"
  FILE* infile = fopen(argv[1],"r");
  if(infile == NULL)
    printf("Datei konnte nicht geöffnet werden.");
  
  while(fgets(buffer, sizeof(buffer), infile))
  {
    char command[255];
    char arg[255];
    int num = 2;
    sscanf(buffer,"%s %s %i",command,arg,&num);
    printf("COMMAND: %s %i\n",command,ramcell);
    if(strcmp(command,"DEFR") == 0)
    {
      // Allocate memory for an identifier
      for(int i = 0;i<identc;i++)
      {
	if(strcmp(arg,identifiers[i].name) == 0)
	{
	  printf("%s::%i Bezeichner %s bereits deklariert. \n",argv[1],line,identifiers[i].name);
	  return 2;
	}
      }
      
      strcpy(identifiers[identc].name,arg);
      identifiers[identc].len = num;
      identc++;
      continue; // Jump to the next thing
    }
    if(strcmp("LABEL",command) == 0)
    {
      
    }
    if(strcmp("STP",command) == 0) // 0000
    {
      
      commands[ccount].command = 1;
      ccount++;
      // Update the number of ram cells
      ramcell += 1;
    }
    if(strcmp("SPR0",command) == 0) // 0001
    {
      
      commands[ccount].command = 2;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("SPR",command) == 0) // 0010
    {
      
      commands[ccount].command = 3;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells1001
      ramcell += 3;
    }
    if(strcmp("EIN",command) == 0)	//00011
    {
      
      commands[ccount].command = 4;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("AUS",command) == 0) // 0100
    {
      
      commands[ccount].command = 5;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("LDA",command) == 0) // 0101
    {
      commands[ccount].command = 6;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("LDAH",command) == 0)
    {
      
      commands[ccount].command = 7;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("SPA",command) == 0) // 0110
    {
      
      commands[ccount].command = 8;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("SPAH",command) == 0)
    {
      
      commands[ccount].command = 9;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("ADD",command) == 0) // 0111
    {
      
      commands[ccount].command = 10;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("ADDH",command) == 0)
    {
      
      commands[ccount].command = 11;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("ADDC",command) == 0) // 1000
    {
      
      commands[ccount].command = 12;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("ADDCH",command) == 0) 
    {
      
      commands[ccount].command = 13;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("SUBC",command) == 0) // 1001
    {
      
      commands[ccount].command = 14;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("SUBCH",command) == 0) // 1001
    {
      
      commands[ccount].command = 15;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("SUB",command) == 0) //1010
    {
      
      commands[ccount].command = 16;break;
      strcpy(commands[ccount].argument,arg);
      ccount++;
      // Update the number of ram cells
      ramcell += 3;
    }
    if(strcmp("AND",command) == 0)
    {
      
    }
    // Still missing some commands
    //printf("%s %s %i\n",command,arg,num);

    line++;
  }
  fclose(infile);
  printf("Read in the File, Speicherzelle: %i\n",ramcell);
  for(int i = 0;i<ccount;i++)
    printf("%i %i %s\n",i,commands[i].command,commands[i].argument);
  // Generate the Outfile
  for(int i = 0;i<identc;i++)
  {
    // Give them the Space the need
    identifiers[i].begin = ramcell;
    ramcell += identifiers[i].len;
    identifiers[i].end   = ramcell-1;
  }
  printf("After RAM ALLOC: %i \n",ramcell);
  
  // Bestimme die Zellen für das Programm
  
  // Assemble it
  FILE* outfile = fopen("out.lr","w");
  for(int i = 0;i<ramsize;i++)
  {
    command current = commands[i];
    switch(current.command)
    {
      case 1:
	writeLn("0000 ; STOP",outfile);
	break;
      case 4:
	// EIN
	writeLn("0011 ; EIN",outfile);
	writeNBR(getcell(current.argument),outfile);
	break;
      case 5:
	// AUS
	writeLn("0100 ; AUS",outfile);
	writeNBR(getcell(current.argument),outfile);
	break;
      case 6:
	// LDA - 0101
	writeLn("0101 ;LDA",outfile);
	writeNBR(getcell(current.argument),outfile);
	break;
      case 7:
	// LDAH
	writeLn("0101 ; LDAH",outfile);
	writeNBR(getcell(current.argument)+1,outfile);
	break;
      case 8:
	// SPA - 0110
	writeLn("0110 ;SPA",outfile);
	writeNBR(getcell(current.argument),outfile);
	break;
      case 9:
	// SPAH - 0110
	writeLn("0110 ; SPA(H)",outfile);
	writeNBR(getcell(current.argument)+1,outfile);
	break;
      case 10:
	// ADD -  0111
	writeLn("0111 ; ADD",outfile);
	writeNBR(getcell(current.argument),outfile);
	break;
      case 11:
	// ADDH -  0111
	writeLn("0111 ; ADDH",outfile);
	writeNBR(getcell(current.argument)+1,outfile);
	break;
      case 12:
	// ADDC - 1000
	writeLn("1000 ; ADDC",outfile);
	writeNBR(getcell(current.argument),outfile);
	break;
      case 13:
	// ADDC - 1000
	writeLn("1000 ; ADDCH",outfile);
	writeNBR(getcell(current.argument)+1,outfile);
	break;
      case 14:
	// SUBC 1001
	writeLn("1001 ; SUBC",outfile);
	writeNBR(getcell(current.argument),outfile);
	break;
     case 15:
	// SUBCH 1001
	writeLn("1001 ;SUBCH",outfile);
	writeNBR(getcell(current.argument)+1,outfile);
	break;
    case 16:
	// SUB 1001
	writeLn("1010 ; SUB",outfile);
	writeNBR(getcell(current.argument),outfile);
	break;
     case 17:
	// SUBH 1001
	writeLn("1010 ; SUBh",outfile);
	writeNBR(getcell(current.argument)+1,outfile);
	break;
    }
    
  }
  fclose(outfile);
}