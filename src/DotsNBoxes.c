#include <stdio.h>
#include <stdlib.h>

#define TAM_NORMAL 29


void Welcome(int* size2,int* size, char* name)
{
	char a;
	printf("Bienvenido ingrese su nombre: \n");
	scanf("%s",name);
	printf("Seleccione el tamaño de la matriz, desde 3 hasta 15: \n");
	while((a=getchar()) != EOF && a != '\n');
	scanf("%d", size);
	while(*size<3  || *size>15)
	{
		printf("Seleccione el tamaño de la matriz, desde 3 hasta 15: \n");
		while((a=getchar()) != EOF && a != '\n');
		scanf("%d",size);
	}
	*size2=*size;
	*size=*size *2 -1;
}
/*void Mode(int* gameMode)
{
	printf("Seleccione el modo de juego \n");
	printf("1-Computadora vs Computadora \n");
	printf("2-Jugador vs Computadora \n");
	printf("3-Jugador vs Jugador \n");
	printf("0-Finalizar programa \n");
	scanf("%d", &gameMode);
	while (*gameMode<0 && *gameMode>3)
	{
		printf("Seleccione el modo de juego \n");
		printf("1-Computadora vs Computadora \n");
		printf("2-Jugador vs Computadora \n");
		printf("3-Jugador vs Jugador \n");
		printf("0-Finalizar programa \n");
		scanf("%d", &gameMode);
	}
}*/
void CreateBoard(int size,char board[TAM_NORMAL][TAM_NORMAL])
{
	int i;
	int j;
	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
			if (j%2){
				board[i][j]=' ';
			}else{
			board[i][j]='.';
			}
	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
			if (i%2){
				board[i][j]=' ';
				if (j%2 ==0){
					board[i][j]=' ';
				}
			}
}
void PrintBoard(int size,char board[TAM_NORMAL][TAM_NORMAL])
{
	int i,j;
	for (i=0; i<size; i++)
	{
		printf("\n");
		for(j=0; j<size; j++)
		printf("%c", board[i][j]);
	}
	printf("\n");
}
void PlayerMove(int* x,int* y,char board[TAM_NORMAL][TAM_NORMAL])
{
	//El jugador elije la fila y columna
	char a;
	printf("JUEGA USTED \n");
	printf("Elija en que fila poner \n");
	while((a=getchar()) != EOF && a != '\n');
	scanf("%d",x);
	printf("Elija en que columna poner \n");
	while((a=getchar()) != EOF && a != '\n');
	scanf("%d",y);
	*y=*y-1;
	*x=*x-1;
	// Le pide hasta que de una respuesta correcta
	while(board[*x][*y]=='.' || board[*x][*y]=='|' || (*x<0 && *x>29) || (*y<0 && *y>29) || (*y%2!=0 && *x%2!=0) || board[*x][*y]=='-')
	{
		printf("Jugada no disponible \n");
		printf("Elija en que fila poner \n");
		while((a=getchar()) != EOF && a != '\n');
		scanf("%d",x);
		printf("Elija en que columna poner \n");
		while((a=getchar()) != EOF && a != '\n');
		scanf("%d",y);
		*y=*y-1;
		*x=*x-1;
	}
	if (*x%2==0){
		board[*x][*y]='-';
	}else{
		board[*x][*y]='|';
	}
}
void Marksquare(int* Comp,int* User,int* R,int* size,int T,int* x,int* y,int* PCx,int* PCy,char board[TAM_NORMAL][TAM_NORMAL])
{
	int i,j,f;
	char Q[0];
	if (T==0)
	{
		i=*x;
		j=*y;
		Q[0]='J';
		f=1;
	}else{
		i=*PCx;
		j=*PCy;
		Q[0]='P';
		f=0;
	}
	if (board[i-1][j-1]=='|')           //si el ultimo movimineto es abajo
	{
		if (board[i-2][j]=='-')
		{									//SE CAMBIO
			if (board[i-1][j+1]=='|')
			{
				if (board[i][j]=='-')
				{
					board[i-1][j]=Q[0];
					printf("Felicidades tiene 1 cuadrado \n");
					*R=1;
					if (f==1)
						*User=*User+1;
					if (f==0)
						*Comp=*Comp+1;
				}
			}
		}
	}
	if (board[i+1][j-1]=='|')           //si el ultimo movimineto es arriba
	{
		if (board[i+2][j]=='-')
		{
			if (board[i+1][j+1]=='|')
			{
				if (board[i][j]=='-')
				{
					board[i+1][j]=Q[0];
					printf("Felicidades tiene 1 cuadrado \n");
					*R=1;
					if (f==1)
						*User=*User+1;
					if (f==0)
						*Comp=*Comp+1;
				}
			}
		}
	}
	if (board[i][j-2]=='|')           //si el ultimo movimineto es derecha
	{
		if (board[i-1][j-1]=='-')
		{
			if (board[i+1][j-1]=='-')
			{
				if (board[i][j]=='|')
				{
					board[i][j-1]=Q[0];
					printf("Felicidades tiene 1 cuadrado \n");
					*R=1;
					if (f==1)
						*User=*User+1;
					if (f==0)
						*Comp=*Comp+1;
				}
			}
		}
	}
	if (board[i-1][j+1]=='-')           //si el ultimo movimineto es izquierda
	{
		if (board[i][j+2]=='|')
		{
			if (board[i+1][j+1]=='-')
			{
				if (board[i][j]=='|')
				{
					board[i][j+1]=Q[0];
					printf("Felicidades tiene 1 cuadrado \n");
					*R=1;
					if (f==1)
						*User=*User+1;
					if (f==0)
						*Comp=*Comp+1;
				}
			}
		}
	}
}
void PcMove(int* PCx,int* PCy,int size,char board[TAM_NORMAL][TAM_NORMAL])
{
		srand(time(NULL));
		*PCx=rand() % size;
		*PCy=rand() % size;

		while(board[*PCx][*PCy]=='.' || board[*PCx][*PCy]=='|' || (*PCy%2!=0 && *PCx%2!=0) || board[*PCx][*PCy]=='-' || board[*PCx][*PCy]=='J' || board[*PCx][*PCy]=='P')
		{
			srand(time(NULL));
			*PCx=rand() % size;
			*PCy=rand() % size;
		}
		if (*PCx%2==0){
			board[*PCx][*PCy]='-';
		}else{
			board[*PCx][*PCy]='|';
		}
}
void WhoStarts(int* Starts)
{
	char a;
	printf("Elija si quiere:\n");
	printf("1-Si empieza el jugador\n");
	printf("2-Si empieza la PC\n");
	printf("3-Aleatorio\n");
	while((a=getchar()) != EOF && a != '\n');
	scanf("%d", Starts);
	while(*Starts<1 || *Starts>3)
	{
		printf("Opcion no disponible\n");
		printf("Elija si quiere:\n");
		printf("1-Si empieza el jugador\n");
		printf("2-Si empieza la PC\n");
		printf("3-Aleatorio\n");
		while((a=getchar()) != EOF && a != '\n');
		scanf("%d", Starts);
	}
	if(*Starts==1)
	{
		printf("EMPIEZA USTED \n");
		*Starts=0;
	}
	if(*Starts==2)
	{
		printf("EMPIEZA LA PC \n");
		*Starts=1;
	}
	if(*Starts==3)
	{
		srand(time(NULL));
		int Turn=rand() % 2;
		if (Turn==0){
			printf("EMPIEZA USTED \n");
		}else{
			printf("EMPIEZA LA PC \n");
		}
		*Starts=Turn;
	}
}
void main(){
	int size,size2,i,Starts;
	int Jogadas=0;
	int x,y,PCx,PCy,T,R;
	int User=0;
	int Comp=0;
	char name[TAM_NORMAL];
	//int GameMode;
	char Board[TAM_NORMAL][TAM_NORMAL];
	Welcome(&size2,&size,name);
	//Mode(&GameMode);
	CreateBoard(size,Board);
	WhoStarts(&Starts); 			//Se elije quien empieza.
	PrintBoard(size,Board);
	/*switch (GameMode)
	{
		case '1':
				PlayerMove(Board);
				PrintBoard(size,Board);      //Primera Jugada
				PcMove(size,Board);
				PrintBoard(size,Board);      //Segunda Jugada
				break;
		case '2':
				PlayerMove(Board);
				PrintBoard(size,Board);      //Primera Jugada
				PcMove(size,Board);
				PrintBoard(size,Board);      //Segunda Jugada
				break;
		case '3':
				PlayerMove(Board);
				PrintBoard(size,Board);      //Primera Jugada
				PlayerMove(Board);
				PrintBoard(size,Board);      //Segunda Jugada
				break;
		case '0':
				break;
				//terminaTodo
				 */
	for (i=0;i<size2;i++)
	{
		Jogadas=i*i*4-Jogadas;
	}
	//printf("Cantidad de Jugadas %d \n\n",Jogadas);
	i=0;
	//printf("Tamano real %d \n",size);
	//printf("Tamano visual %d \n\n",size2);
	while (i<Jogadas)
	{
		if (Starts==0)                    //Empieza jugador
		{
			R=0;
			PlayerMove(&x,&y,Board);
			printf("Jugada Jugador \n");
			T=0;
			Marksquare(&Comp,&User,&R,&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
			PrintBoard(size,Board);      //Primera Jugada
			i++;
			printf("Jugada numero %d \n",i);
			printf("\n");
			if (i>=Jogadas)
				break;
			while (R==1)
			{
				R=0;
				PlayerMove(&x,&y,Board);
				printf("Jugada Jugador \n");
				T=0;
				Marksquare(&Comp,&User,&R,&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
				PrintBoard(size,Board);      //Primera Jugada
				i++;
				if (i>=Jogadas)
					break;
				printf("Jugada numero %d \n",i);
				printf("\n");
			}
			if (i>=Jogadas)
				break;
			printf("Jugada Pc \n");
			PcMove(&PCx,&PCy,size,Board);
			T=1;
			Marksquare(&Comp,&User,&R,&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
			PrintBoard(size,Board);      //Segunda Jugada
			i++;
			printf("Jugada numero %d \n",i);
			printf("\n");
			if (i>=Jogadas)
				break;
			while (R==1)          //Se repite
			{
				R=0;
				printf("Jugada Pc \n");
				PcMove(&PCx,&PCy,size,Board);
				T=1;
				Marksquare(&Comp,&User,&R,&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
				PrintBoard(size,Board);      //Segunda Jugada
				i++;
				if (i>=Jogadas)
					break;
				printf("Jugada numero %d \n",i);
				printf("\n");
			}
			if (i>=Jogadas)
				break;
		}else{                           //Empieza Pc
			printf("Jugada Pc \n");
			PcMove(&PCx,&PCy,size,Board);
			T=1;
			Marksquare(&Comp,&User,&R,&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
			PrintBoard(size,Board);      //Primera Jugada
			i++;
			printf("Jugada numero %d \n",i);
			printf("\n");
			if (i>=Jogadas)
				break;
			while (R==1)          //Si cierra un cuadrado se repite
			{
				R=0;
				printf("Jugada Pc \n");
				PcMove(&PCx,&PCy,size,Board);
				T=1;
				Marksquare(&Comp,&User,&R,&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
				PrintBoard(size,Board);
				i++;
				if (i==Jogadas)
					break;
				printf("Jugada numero %d \n",i);
				printf("\n");
			}
			if (i>=Jogadas)
				break;
			PlayerMove(&x,&y,Board);
			printf("Jugada Jugador \n");
			T=0;
			Marksquare(&Comp,&User,&R,&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
			PrintBoard(size,Board);      //Segunda Jugada
			i++;
			if (i>=Jogadas)
				break;
			printf("Jugada numero %d \n",i);
			printf("\n");
			while (R==1)         //Si cierra un cuadrado se repite
			{
				R=0;
				PlayerMove(&x,&y,Board);
				printf("Jugada Jugador \n");
				T=0;
				Marksquare(&Comp,&User,&R,&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
				PrintBoard(size,Board);
				i++;
				if (i>=Jogadas)
					break;
				printf("Jugada numero %d \n",i);
				printf("\n");
			}
			if (i>=Jogadas)
				break;
		}
	}
	if (Comp<User)
		printf("Gano usted %d a %d",User,Comp);
	if(User<Comp)
		printf("Gano la Pc %d a %d",Comp,User);
	if(User==Comp)
		printf("Empataron %d a %d",Comp,User);
}
