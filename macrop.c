#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

struct MacroNameTable
{
	int index;
	char name[10];
	int mdtindex;
}MNT[5];

struct MacroDefinitionTable
{
	int index;
	char desc[30];
}MDT[50];

struct ArgumentListArray
{
	char arg[10], no[4];
}ALA[20];

//Global Declarations :

FILE *fp1,*fp2,*fp3,*fp4;
char ch,ch2,word[20],word1[20],*mdtdes,mn[20],mname[20],opnd[20],str[20],s[20],w[20],s1[20];
char word2[20],mnamee[20];
int newline=0;
char* num[10]={"#1","#2","#3","#4","#5","#6","#7","#8","#9"};   

void get_word();
void get_word2();

fpos_t pos;

int main()
{
	int i, j, x,mntc=0, mdtc=0, ala=0, ar=1,l,len,k, let,le,t=0,n=0, com=1, m=0,flag, flag1=0,f=0;
	char line[30], line1[30], line2[30], line3[30],ct;
	
	//pass 1
	
	fp1 = fopen("pass1Input.txt","r");
	fp2 = fopen("pass1Output.txt","w");
	i=0;
	
	while(!feof(fp1))
	{
		fgetpos(fp1,&pos);
		get_word();
		
		if(strcmp(word,"MACRO")==0)
		{
			fgetpos(fp1,&pos);
			get_word();
			
			strcpy(MNT[mntc].name,word);       //Copying Macro Name to MNT
			MNT[mntc].index = mntc;              
			MNT[mntc].mdtindex = mdtc;
			mntc++;
			
			fsetpos(fp1,&pos);
			i=0;
			while(!feof(fp1))
			{
				ch=fgetc(fp1);                
				if(ch=='\n')
					goto label1;
				line1[i]=ch;
				i++;
			}
	label1: line1[i]='\0';
			strcpy(MDT[mdtc].desc,line1);        //Definition of the macro into MNT
			MDT[mdtc].index = mdtc;
			mdtc++;
			
			fsetpos(fp1,&pos);
			get_word();
			do
			{
				get_word();
				
				strcpy(ALA[ala].arg,word);         //Linking the Arguments of MDT with ALA
				strcpy(ALA[ala].no,num[ala]);
				ala++;
				
			}while(ch!='\n');
		}
		
		else if(strcmp(word,"MEND")==0)
		{
			fsetpos(fp1,&pos);
			get_word();
			
			strcpy(MDT[mdtc].desc,word);
			MDT[mdtc].index = mdtc;
			mdtc++;
		}
		
		else if(strcmp(word,"START")==0)
		{
			fsetpos(fp1,&pos);
			
			while(!feof(fp1))
			{
				ch = fgetc(fp1);
				fprintf(fp2,"%c",ch);
			}
			break;
		}
		
		else
		{
			 
			fsetpos(fp1,&pos);
			get_word();
			
			strcpy(line2,word);
			com=1;
			do
			{
				if(ch=='\n')
					goto label2;
					
				get_word();
				strcat(line2," ");
				flag=0;
				for(i=0;i<ala;i++)
				{
					if(strcmp(word,ALA[i].arg)==0)
					{
						strcpy(word1,ALA[i].no);
						strcat(line2,word1);
						flag=1;
						break;
					}
				}
				if(flag==0)
					strcat(line2,word);
					
			}while(ch!='\n');
	label2: strcpy(MDT[mdtc].desc,line2);
			MDT[mdtc].index = mdtc;
			mdtc++;
		}
		
	}
	
	fclose(fp1);
	fclose(fp2);
	
	fp1 = fopen("pass1Input.txt","r");
	char c,d,e;
	c=fgetc(fp1);
	printf("Input File is : \n");
	while(!feof(fp1))
	{
		printf("%c",c);
		c=fgetc(fp1);
	}
	
	printf("\n\n\nMacro Name Table (MNT) :");
	printf("\n\nIndex\tName\tMDT Table Index");
	printf("\n--------------------------------");
	for(j=0;j<mntc;j++)
	printf("\n%d\t%s\t%d",MNT[j].index,MNT[j].name,MNT[j].mdtindex);
	
	printf("\n\nMacro Definition Table (MDT) :");
	printf("\n\nIndex\tDefinition");
	printf("\n------------------");
	for(j=0;j<mdtc;j++)
	printf("\n%d\t%s",MDT[j].index,MDT[j].desc);
	
	printf("\n\nArgument Array List (ALA) :");
	printf("\n\nNo\tArgument");
	printf("\n-----------------");
	for(j=0;j<ala;j++)
	printf("\n%s\t%s",ALA[j].no,ALA[j].arg);
	
	fp2 = fopen("pass1Output.txt","r");
	d=fgetc(fp2);
	printf("\n\nIntermediate Output File is : \n");
	while(!feof(fp2))
	{
		printf("%c",d);
		d=fgetc(fp2);
	}
	
	printf("\n\n-----------------------PASS 1 SUCCESSFUL!!!!!!--------------------------\n");
	
	fclose(fp1);
	fclose(fp2);

	//pass2
	
	fp4 = fopen("pass1Output.txt","r");
	fp3 = fopen("pass2Output.txt","w");
	ala=1,x=1;
	while(!feof(fp4))
	{
		fgetpos(fp4,&pos);
		get_word2();
		for(i=0;i<mntc;i++)
		{
			len=strlen(word2);
			l=0;
			while(l<len && word2[l]!=' ')
			{
				mname[l]=word2[l];
				l++;
			}
			mname[l]='\0';
		
			if(strcmp(mname,MNT[i].name)==0)
			{
				n=l;
				while(n<len)
				{
				   if(word2[n]!=' '&& word2[n]!=',')
				   {
				   	  s[0]=word2[n];	
				   	  strcpy(ALA[ala++].arg,s);
				   }
				     n++;
				}
				mdtc = MNT[i].mdtindex;
				mdtc++;
				while(strcmp(MDT[mdtc].desc,"MEND")!=0)
				{
					len=strlen(MDT[mdtc].desc);
					l=0;
					while((MDT[mdtc].desc)[l]!=' ')
					{
						str[l]=(MDT[mdtc].desc)[l];
						l++;
					}
					str[l]='\0';
					strcat(str," ");
					strcat(str,ALA[x].arg);
					x++;
					fputs(str,fp3);
					fputs("\n",fp3);
					mdtc=mdtc+1;
				}
			}
			else
			{
				if(i==0)
				{
					le=strlen(word2);
					let=0;
					while(let<le && word2[let]!=' ')
					{
						mnamee[let]=word2[let];
						let++;
					}
					mnamee[let]='\0';
					let=0,f=0;
					while(let<mntc)
					{
						if(strcmp(mnamee,MNT[let++].name)==0)
						{
							f=1;
					        break;
					    }
				    }
				    if(f==0)
				    {
				    	fputs(word2,fp3);
						fputs("\n",fp3);
					}
			    }
		
			}	
		}
	}
	fclose(fp4);
	fclose(fp3);
	
	fp3 = fp3 = fopen("pass2Output.txt","r");
	e=fgetc(fp3);
	printf("\n\nFinal Output File is : \n");
	while(!feof(fp3))
	{
		printf("%c",e);
		e=fgetc(fp3);
	}
	
	fclose(fp3);
	printf("\n\n-----------------------PASS 2 SUCCESSFUL!!!!!!--------------------------\n");	
	
	getch();
}


void get_word()
{
	int i=0;
	do
	{
		ch=getc(fp1);
		if(ch!=' ' && ch!='\n' && ch!=',')
		{
			word[i]=ch;
			i++;
		}
		if(ch==' ' || ch=='\n' || ch==',')
		{
			word[i]= '\0';
			i=0;
			break;
		}
	}while(!feof(fp1));
}

void get_word2()
{
	int i=0;
	do
	{
		ch2=getc(fp4);
		if(ch2!='\n')
		{
			word2[i]=ch2;
			i++;
		}
		if(ch2=='\n')
		{
			word2[i]='\0';
			i=0;
			break;
		}
	}
	while(!feof(fp4));
}





