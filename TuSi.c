#include <stdio.h>

typedef struct{
	int tusi; 	//Bo A
	int qui;	//Bo B
	char vitri;	//Co 2 bo A va bo B
}State;

//Operator
int chuyen1TuSi(State now , State *result)
{
	if(now.tusi != 0)
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi + i ;
		result->qui  = now.qui;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;	
	}
	return 0;
}
int chuyen1Qui(State now , State *result)
{
	if(now.qui != 0)
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi;
		result->qui  = now.qui+i;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;	
	}
	return 0;
}
int chuyen2TuSi(State now,State *result)
{
	if(now.tusi > 1)
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi + i*2 ;
		result->qui  = now.qui;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;
	}
	return 0;
}
int chuyen2Qui(State now,State *result)
{
	if(now.qui > 1)
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi ;
		result->qui  = now.qui + i*2;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;
	}
	return 0;
}
int chuyenTuSiQui(State now,State *result)
{
	if(now.qui != 0 && now.tusi!=0)
	{
		int i =  now.vitri=='A'?-1:1;
		result->tusi = now.tusi + i ;
		result->qui  = now.qui  + i ;
		result->vitri =  now.vitri=='A'?'B':'A';
		return 1;
	}
	return 0;
}
int show(State now)
{
	printf("State (TuSi,Qui) = (%d,%d) - thuyen dang o %c\n",now.tusi,now.qui,now.vitri);
}
int call_operator(State now,State *result,int option)
{
	switch(option)
	{
		case 0 : return chuyen1TuSi(now,result);
		case 1 : return chuyen1Qui(now,result);
		case 2 : return chuyen2TuSi(now,result);
		case 3 : return chuyen2Qui(now,result);
		case 4 : return chuyenTuSiQui(now,result);
		default : printf("Option Fail !\n"); return 0;
	}
}
char *action[] = {"Chuyen 1 Tu Si","Chuyen 1 Qui","Chuyen 2 Tu Si"
				 ,"Chuyen 2 Qui" , "Chuyen 1 Tu Si va 1 Qui"};
int main()
{
	State start,result;
	start.qui   = 3;
	start.tusi  = 3;
	start.vitri = 'A';
	int i;
	show(start);
	for(i=0;i<5;i++)
	{
		if(call_operator(start,&start,i))
		{
			printf("Action : %s Succes \n",action[i]);
			show(start);
		}
		else printf("Action : %s Fail \n",action[i]);
	}
}



