#include <stdio.h>
#include <stdlib.h>

#define TAM_NORMAL 29


void Welcome(int* size2,int* size, char* name)
{
	printf("Bienvenido ingrese su nombre: \n");
	scanf("%s",name);
	printf("Seleccione el tamaño de la matriz, desde 3 hasta 15: \n");
	scanf("%d", size);
	while(*size<3  || *size>15)
	{
		printf("Seleccione el tamaño de la matriz, desde 3 hasta 15: \n");
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
	printf("JUEGA USTED \n");
	printf("Elija en que fila poner \n");
	scanf("%d",x);
	printf("Elija en que columna poner \n");
	scanf("%d",y);
	*y=*y-1;
	*x=*x-1;
	// Le pide hasta que de una respuesta correcta
	while(board[*x][*y]=='.' || board[*x][*y]=='|' || (*x<0 && *x>29) || (*y<0 && *y>29) || (*y%2!=0 && *x%2!=0) || board[*x][*y]=='-')
	{
		printf("Jugada no disponible \n");
		printf("Elija en que fila poner \n");
		scanf("%d",x);
		printf("Elija en que columna poner \n");
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
void Marksquare(int* size,int T,int* x,int* y,int* PCx,int* PCy,char board[TAM_NORMAL][TAM_NORMAL])
{
	int i,j;
	char Q[0];
	if (T==0)
	{
		i=*x;
		j=*y;
		Q[0]='J';
	}else{
		i=*PCx;
		j=*PCy;
		Q[0]='P';
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
				}
			}
		}
	}
	if (board[i-1][j+1]=='-')           //si el ultimo movimineto es arriba
	{
		if (board[i+2][j]=='|')
		{
			if (board[i+1][j+1]=='|')
			{
				if (board[i][j]=='-')
				{
					board[i+1][j]=Q[0];
					printf("Felicidades tiene 1 cuadrado \n");
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
int WhoStarts(){
	srand(time(NULL));
	int Turn=rand() % 2;
	if (Turn==0){
		printf("EMPIEZA USTED \n");
	}else{
		printf("EMPIEZA LA PC \n");
	}
	return Turn;
}
void main(){
	int size,size2,i,Starts;
	int Jogadas=0;
	int x,y,PCx,PCy,T;
	char name[TAM_NORMAL];
	//int GameMode;
	char Board[TAM_NORMAL][TAM_NORMAL];
	Welcome(&size2,&size,name);
	//Mode(&GameMode);
	CreateBoard(size,Board);
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
	printf("Cantidad de Jugadas %d \n",Jogadas);
	i=0;
	printf("Tamano real %d \n",size);
	printf("Tamano visual %d \n\n",size2);
	Starts=WhoStarts();                    //Se elije quien empieza.0-Jugador.1-Pc
	while (i<Jogadas)
	{
		if (Starts==0)                    //Empieza jugador
		{
			PlayerMove(&x,&y,Board);
			printf("Jugada Jugador \n");
			i++;
			T=0;
			Marksquare(&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
			PrintBoard(size,Board);      //Primera Jugada
			printf("Jugada Pc \n");
			PcMove(&PCx,&PCy,size,Board);
			i++;
			T=1;
			Marksquare(&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
			PrintBoard(size,Board);      //Segunda Jugada
		}else{                           //Empieza Pc
			printf("Jugada Pc \n");
			PcMove(&PCx,&PCy,size,Board);
			i++;
			T=1;
			Marksquare(&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
			PrintBoard(size,Board);      //Segunda Jugada
			PlayerMove(&x,&y,Board);
			printf("Jugada Jugador \n");
			i++;
			T=0;
			Marksquare(&size,T,&x,&y,&PCx,&PCy,Board);  //control de marca
			PrintBoard(size,Board);      //Primera Jugada
		}
	}
	printf("Termino");
}
