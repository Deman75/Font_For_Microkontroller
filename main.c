#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void StringRate (void);
char *DeleteSpace (char word[]); // Удаление пробелов из слова. 
char htoi(char s[]);
char FindeString (char String[], char FindeWord[]);
char wordTmp[150];
char SymbolHeightFinde (char Name[]);
char StringToHex (char SymbolBitWidth, char String[]); // Возвращает Hex из строки вида "___X_X_"
unsigned char BitMass[10]; // Максимальная ширина символа 10 Байт.
char SymbolMaxWidth=0;
void CProgram(FILE *NewFile, char *name, char SymbolHeight);


char StringToHex (char SymbolBitWidth, char String[])
{
	// SymbolIndex - Номер символа в массиве, чтобы узнать ширину.
	unsigned char Bit=0, BitNum=0;
	unsigned char i,j=0;
	
	for (i=0;i<=strlen(String);i++)
		{
			if (String[i]=='_')
				BitNum++;
			if (String[i]=='X')
				{
					BitNum++;
					Bit=Bit | (1<<8-BitNum);
				}
			if (BitNum==8)
				{
					BitMass[j]=Bit;
					BitNum=0;
					Bit=0;
					j++;
				}
			}
	if (j<SymbolMaxWidth)
		for (j=j;j<=SymbolMaxWidth-1;j++)
			BitMass[j]=0;
	
	return (1);	
}

// Удаление пробелов из слова.
char *DeleteSpace (char word[])
{
	unsigned char i=0,j=0;
	for (i=0;word[i]!='\0';i++)
		{
			if (word[i]=='.')
					{
						return wordTmp;
						break;
					}			
			if ((word[i]>='A' && word[i]<='z') || (word[i]>='0' && word[i]<='9'))
				{
					wordTmp[j]=word[i];
					j++;
				}
		}
	return wordTmp;
}

char SymbolHeightFinde (char Name[])
{
	char HeightTmp[2];
	
	if ( (Name[ strlen(Name)-4 ] >= '0') &&( Name[ strlen(Name)-4 ] <= '9') )
			{
				HeightTmp[0]=(Name[ strlen(Name)-4]);
				HeightTmp[1]=(Name[ strlen(Name)-3]);
			}
		else
			{
				HeightTmp[0]=(Name[ strlen(Name)-3]);
			}
	return (atoi(HeightTmp));		
}

char FindeString (char String[], char FindeWord[])
{
	//strncmp(Finde, str, 18)==0
	int i=0,j=0,flag=0;
	int LenWord=0,LenFindeWord=0;
	char WordTmp[100];
	char Hex[6];
	
	WordTmp[0]='\0';
	
	for (i=0;FindeWord[i]!='\0';i++);
	LenFindeWord=i;
	
	for (i=0;String[i]!='\0';i++)
		{
			LenWord=0;
			for (j=i;(String[j]!=' ' && String[j]!='\0');j++)
				{
					WordTmp[LenWord]=String[j];
					LenWord++;
				}
			i=j;
			if (String[j]=='\0')
				i-=1;
			if ((strncmp(WordTmp, FindeWord, LenFindeWord)==0))
				{
					sprintf(Hex,"0x%c%c%c%c", WordTmp[LenFindeWord], WordTmp[LenFindeWord+1], WordTmp[LenFindeWord+2], WordTmp[LenFindeWord+3]);
					return(htoi(Hex));
					break;
				}
		}
	return(0x0000);
}

int main(int argc, char *argv[]) {

	StringRate();
	return 0;
}


void StringRate (void)
{
	FILE *fp, *NewFile; // Два файла, вохдящий и выходящий
	char name[]="Sitka Banner30.c";
	char c, String [150];
	char Finde [50];
	int i=0,j=0, StringPos=0, StringLenght=0;
	unsigned char Flag=1, StringEndFlag=0;
	char SymbolCode[1000];
	char SymbolInfoRealWidth[1000];
	char SymbolInfoBitWidth[1000];
	char SymbolInfoTmp[2];
	char SymbolHeight;	
	unsigned char SymbolCodeCount=0;
	unsigned char SymbolInfoCodeCount=0;
	unsigned char SymbolNumber=0;
	char LastSymbol=0; 
	unsigned char FindedLastSymbol=0;
	char SymbolString=0, SymbolTransformFlag=0; /* С появления SymbolTransformFlag
	начинаем считать колличество строк SymbolString до высоты символа SymbolHeight
	и переводим все это в Hex
	*/
	char End=0;
	char nameout[50];
	
	nameout[0]='\0';
	strcat(nameout, "New_");
	strcat(nameout, DeleteSpace(name));
	strcat(nameout, ".c");	
	
	SymbolHeight = SymbolHeightFinde(name);
	
	
	if(((fp = fopen(name, "r"))!=NULL) && ((NewFile = fopen(nameout, "w"))!=NULL))
		{
			SymbolCodeCount=0;
			SymbolInfoCodeCount=0;
			printf("File is open\n");

	  		fprintf(NewFile,"#include \"stm32f4xx_hal.h\"\n");	  			  		
	  		fprintf(NewFile,"#include \"New_%s.h\"\n",DeleteSpace(name));
	  		fprintf(NewFile,"#include \"LCD.h\"  \n",DeleteSpace(name));
	  		fprintf(NewFile,"#include <stdlib.h>\n\n\n");
	  		fprintf(NewFile,"/*******************************************************\n");
	  		fprintf(NewFile,"*                    Font Generate                    *\n", "");
	  		fprintf(NewFile,"*                  Font height %d                      \n", SymbolHeight);
	  		fprintf(NewFile,"********************************************************/\n\n\n\n");	  		
	  		fprintf(NewFile,"const unsigned char %s[] = {", DeleteSpace(name));
	  		printf("/*******************************************************\n");
	  		printf("*                    Font Generate                    *\n", "");
	  		printf("*                  Font height %d                      \n", SymbolHeight);
	  		printf("********************************************************/\n\n\n\n");
	  		printf("const unsigned char %s[] = {", DeleteSpace(name));	  		
									
			
			while ((c=fgetc(fp))!=EOF)
				{

					if (c != '\n' && Flag ==1)
						{
							String[StringLenght]=c;
							StringLenght++;
						}
					if (c == '\n' && Flag ==1 && StringLenght >0)
						{
							Flag=1;
							StringEndFlag=1;
							String[StringLenght]='\0';
						}
					if (StringEndFlag==1)
						{
							Finde[0]='\0';
							strcat(Finde, "acGUI_Font");
							strcat(Finde, DeleteSpace(name));
							strcat(Finde, "_");
							i=0;
							i=FindeString(String,Finde);
							
							if ((i != 0) && (FindedLastSymbol == 2))
								{
									if (SymbolTransformFlag==0)
										{
											SymbolTransformFlag=1;
											SymbolString=0;
											fprintf (NewFile,"/* Symbol code %00004hx */\n",SymbolCode[SymbolNumber]);
											fprintf (NewFile,"0x%02hx, /* Simbol Width Pixel */\n",SymbolInfoRealWidth[SymbolNumber]);
											printf ("/* Symbol code %00004hx */\n",SymbolCode[SymbolNumber]);
											printf ("0x%02hx, /* Simbol Width Pixel */\n",SymbolInfoRealWidth[SymbolNumber]);
											
											if (SymbolCode[SymbolNumber] == LastSymbol)
												End=1;
										}
									if (SymbolTransformFlag==1)
										SymbolNumber++;
								}
							
							if ( (FindedLastSymbol == 2) && (SymbolTransformFlag==1))
								{
									if (SymbolString>0)
										if (StringToHex(SymbolInfoBitWidth[SymbolNumber-1], String)==1)
											{
												for (j=1;j<=SymbolMaxWidth;j++)
													{
														if (End == 0 || SymbolHeight != SymbolString || j != SymbolMaxWidth)
															{
																fprintf (NewFile,"0x%02hx, ",BitMass[j-1]);
																printf ("0x%02hx, ",BitMass[j-1]);
															}
														if (End == 1 && SymbolHeight == SymbolString && j == SymbolMaxWidth)
															{
																fprintf (NewFile,"0x%02hx",BitMass[j-1]);
																printf ("0x%02hx",BitMass[j-1]);
															}
													}
												fprintf(NewFile,"\n");	
												printf("\n");
											}
									SymbolString++;		
									if ( (SymbolString) == (SymbolHeight+1) )
										{
											SymbolTransformFlag=0;
											if (End)
												{
													fprintf(NewFile,"};\n\n\n");
													fprintf(NewFile,"/*******************************************************/\n\n\n");
													CProgram(NewFile,name,SymbolHeight);
													fprintf(NewFile,"/*******************************************************\n");
													fprintf(NewFile,"*                   End                                *\n");
													fprintf(NewFile,"********************************************************/\n");
													
													printf("};\n\n\n");
												
													printf("/*******************************************************\n");
													printf("*                   End font                           *\n");
													printf("********************************************************/\n");
													
																										
													
													break;
												}
										}
									
								}
															
							if ((i != 0) && (FindedLastSymbol != 2))
								{
									if (FindedLastSymbol == 0)
										{
											SymbolCode[SymbolCodeCount]=i;
											SymbolCodeCount++;
										}									
									if ((i == SymbolCode[0])&&(SymbolCodeCount>1))
										{
											LastSymbol=SymbolCode[SymbolCodeCount - 2];
											FindedLastSymbol=1;
											SymbolCodeCount--;
										}
									if ((FindedLastSymbol==1))
										{
											if (String[6]!=' ')
													{
														SymbolInfoTmp[0]=String[6];
														SymbolInfoTmp[1]=String[7];
													}
												else
													{
														SymbolInfoTmp[0]=String[7];
														SymbolInfoTmp[1]='\0';
													}														
											SymbolInfoRealWidth[SymbolInfoCodeCount]=atoi(SymbolInfoTmp);
											SymbolInfoTmp[0]=String[16];
											SymbolInfoTmp[1]='\0';
											SymbolInfoBitWidth[SymbolInfoCodeCount]=atoi(SymbolInfoTmp);
											SymbolInfoCodeCount++;
										}
									if ((FindedLastSymbol==1)&&(i==LastSymbol))
										{
											FindedLastSymbol=2;
											SymbolMaxWidth=SymbolInfoBitWidth[0];
											SymbolNumber=0;
											for (j=0;j<=SymbolCodeCount;j++)
												if (SymbolMaxWidth<SymbolInfoBitWidth[j])
													SymbolMaxWidth=SymbolInfoBitWidth[j];
											rewind(fp);
										}
								}
							StringEndFlag=0;
							StringLenght=0;
						}
				}
		}
	  else 
	  	printf("File not open\n");
	  	
  	fclose(fp);
  	fclose(NewFile);
	  	 	
	nameout[0]='\0';
	strcat(nameout, "New_");
	strcat(nameout, DeleteSpace(name));
	strcat(nameout, ".h");
	
	if  ((NewFile = fopen(nameout, "w"))!=NULL)	
		{
			fprintf(NewFile,"/*******************************************************\n");
	  		fprintf(NewFile,"*                    Font Generate                    *\n", "");
	  		fprintf(NewFile,"*                  Font height %d                      \n", SymbolHeight);
	  		fprintf(NewFile,"********************************************************/\n\n\n\n");
	  		
	  		
			fprintf(NewFile,"/*********************Include****************************/\n\n");
			fprintf(NewFile,"#include \"stm32f4xx_hal.h\"\n");
			fprintf(NewFile,"#include <stdlib.h>\n");
			fprintf(NewFile,"/*****************Defines******************************/\n");
			fprintf(NewFile,"#define %s_Height %d\n", DeleteSpace(name), SymbolHeight);
			fprintf(NewFile,"#define %s_Width %d  // Simbol Byte Width\n\n\n",DeleteSpace(name),SymbolMaxWidth);
													
			fprintf(NewFile,"uint8_t CharNwe%s (uint16_t x, uint16_t y, unsigned char ch, uint16_t CharColor, uint16_t BkgColor);\n",DeleteSpace(name));
			fprintf(NewFile,"void String%s (uint16_t x, uint16_t y, char *string, uint16_t CharColor, uint16_t BkgColor);\n",DeleteSpace(name));
			fprintf(NewFile,"\n");
		}
	
	fclose(NewFile);	
	  	
  	printf("File Close !!!\n");
  	
	
}

void CProgram(FILE *NewFile, char *name, char SymbolHeight)
{
			fprintf(NewFile,"/*******************************************************\n");
	  		fprintf(NewFile,"*                    Program generate                  *\n", "");
	  		fprintf(NewFile,"*                  Font height %d                      \n", SymbolHeight);
	  		fprintf(NewFile,"********************************************************/\n\n\n\n");

	  		fprintf(NewFile,"uint8_t CharNwe%s (uint16_t x, uint16_t y, unsigned char ch, uint16_t CharColor, uint16_t BkgColor)\n",DeleteSpace(name));
	  		fprintf(NewFile,"{\n");
	  		fprintf(NewFile,"	uint8_t i, j, w, cha, posX=0;\n");
	  		fprintf(NewFile,"	uint8_t Width = (%s_Height * %s_Width)+1;\n",DeleteSpace(name),DeleteSpace(name));
	  		fprintf(NewFile,"	uint8_t SymbolWidth=0;\n");
	  		fprintf(NewFile,"	for (i=1;i<=Width-1;i++)\n");
	  		fprintf(NewFile,"		{\n");
	  		fprintf(NewFile,"			for (w=0;w<=%s_Width-1;w++)\n",DeleteSpace(name));
	  		fprintf(NewFile,"				{\n");
	  		fprintf(NewFile,"					if (ch<=0x7F)\n");
	  		fprintf(NewFile,"						{\n");
	  		fprintf(NewFile,"							cha=%s[((ch-0x20)*(Width)) + i];\n",DeleteSpace(name));
	  		fprintf(NewFile,"							SymbolWidth=%s[((ch-0x20)*(Width))];\n",DeleteSpace(name));
	  		fprintf(NewFile,"						}\n");
	  		fprintf(NewFile,"					if (ch>=0xA0)\n");
	  		fprintf(NewFile,"						{\n");
	  		fprintf(NewFile,"							cha=%s[((ch-0x20-0x20)*(Width)) + i];\n",DeleteSpace(name));
	  		fprintf(NewFile,"							SymbolWidth=%s[((ch-0x20-0x20)*(Width))];\n",DeleteSpace(name));
	  		fprintf(NewFile,"						}\n");	  
			fprintf(NewFile,"					if (ch>0x80 && ch<0xA0)\n");
	  		fprintf(NewFile,"						{\n");
	  		fprintf(NewFile,"							cha=%s[(ch-0x20)+i];\n",DeleteSpace(name));
	  		fprintf(NewFile,"							SymbolWidth=%s[((ch-0x20)*(Width))];\n",DeleteSpace(name));
	  		fprintf(NewFile,"						}\n");  		
	  		fprintf(NewFile,"					for (j=0;j<=7;j++)\n");
	  		fprintf(NewFile,"						{\n");
	  		fprintf(NewFile,"							if (cha & 0x80)\n");
	  		fprintf(NewFile,"									Pixel(x+posX,y+j+(w*7)+w,CharColor);\n");
	  		fprintf(NewFile,"								else\n");
	  		fprintf(NewFile,"									if (((j+(w*7)+w)<=SymbolWidth)&&(BkgColor!=2))\n");
	  		fprintf(NewFile,"										Pixel(x+posX,y+j+(w*7)+w,BkgColor);\n");
	  		fprintf(NewFile,"							cha=cha<<1;\n");
	  		fprintf(NewFile,"						}\n");
	  		fprintf(NewFile,"					if (w<%s_Width-1)\n",DeleteSpace(name));
	  		fprintf(NewFile,"						i++;\n");
	  		fprintf(NewFile,"				}\n");
	  		fprintf(NewFile,"			posX++;	\n");
	  		fprintf(NewFile,"		}\n");	  	
			fprintf(NewFile,"	return SymbolWidth;\n");
			fprintf(NewFile,"}\n\n\n\n");	 
			
			
			fprintf(NewFile,"//-----------------------String---------------------------------\n");
			fprintf(NewFile,"void String%s (uint16_t x, uint16_t y, char *string, uint16_t CharColor, uint16_t BkgColor)\n",DeleteSpace(name));
			fprintf(NewFile,"{\n");
			fprintf(NewFile,"	uint8_t SymbolWidth;\n");
			fprintf(NewFile,"	while (*string != 0)\n");
			fprintf(NewFile,"		{\n");
			fprintf(NewFile,"			SymbolWidth=CharNwe%s(x,y,*string,CharColor,BkgColor);\n",DeleteSpace(name));
			fprintf(NewFile,"			y=y+SymbolWidth;\n");
			fprintf(NewFile,"			string++;\n");
			fprintf(NewFile,"		}\n");
			fprintf(NewFile,"}\n");
			fprintf(NewFile,"\n");
			fprintf(NewFile,"\n");
		
}


char htoi(char s[])
{
     int c, M, i;
     
     M = 0;
     
     for(i = 2; i<=5; i++) {
 
         c = s[i];
         if(c >= '0' && c <= '9')
		 	 c -= '0';
        		 else if(c >= 'a' && c <= 'f')
				 	 c = 10 + c -'a';
         			else if(c >= 'A' && c <= 'F') 
					 	c = 10 + c - 'A';
        			else break;
         M = M*16 + c;
     }    
    return M;
}



