#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <time.h>

struct TpJogos{
	
	int COD;
	char desc[30];
	int status;
};

struct TpParticipantes{
	
	int COD;
	char desc[30];
	int status;
};

struct TpCampeonatos{
	
	int CodTipoDeJogo;
	int status;
	int COD, ano;
	char desc[30], titulo[30], responsavel[30];
};

struct TpControle{
			
	int CODParticipante;
	int CODCampeonato;
	int status;
	char nome[40];	
	char nick[30];
};


//-----------------------------PARAMETROS
int main(void);
void Executar(void);

char MenuOPC(void);
char MenuPrincipal(void);
char MenuRelatorio(void);

void Logo(void);
void quadro(int CI,int LI,int CF,int LF);
void background(int xi, int yi, int xf, int yf);

void CadastroTipoDeJogos(void);
void CadastroDeParticipantes(void);
void CadastroDosCampeonatos(void);
void CadastroControle(void);

int BuscaJogo(FILE *ponteiro, int COD);
int BuscaParticipantes(FILE *ponteiro, int COD);
int BuscaParticipantesNome(FILE *ponteiro, char nome);
int BuscaCampeonato(FILE *ponteiro, int COD);
int BuscaNick(FILE *ponteiro, char nick[30]);
int BuscaControleCOD(FILE *ponteiro, int COD);

void AlterarTipoDeJogos(void);
void AlterarParticipantes(void);
void AlterarCampeonato(void);
void AlterarControle(void);

void ConsultaTipoDeJogos(void);
void ConsultaParticipantes(void);
void ConsultaDosCampeonatos(void);
void ConsultaControle(void);

void RelatorioJogos(void);
void RelatorioParticipantes(void);
void RelatorioCampeonatos(void);
void RelatorioControle(void);

void Relatorio1(void);

void ORDJogos(void);
void ORDParticipantes(void);
void ORDCampeonatos(void);
void ORDControle(void);

void ExclusaoJogo(void);
void ExclusaoParticipante(void);
void ExclusaoCampeonato(void);
void ExclusaoControle(void);

int AnalisePartCamp(FILE *ponteiro, int CODCamp, int CODPart);

void InserirJogos(void);
void InserirPart(void);
void InserirCamp(void);
void InserirNick(void);
//-----------------------------FUN��ES

void background(int xi, int yi, int xf, int yf)
{
	int i, j;
	for(i=xi; i<xf; i++){
		for(j=yi; j<yf; j++){
			gotoxy(i,j);
			printf("%c",255);
		}
	}
}

void Logo(void)
{
	
	textbackground(7);
	background(1, 1, 121, 6);
	background(1, 25, 121, 32);
	textcolor(0);
	gotoxy(42,3),printf(" CAMPEONATOS JOGOS ELETRONICOS ");
	textcolor(3);
	textbackground(7);
	quadro(40,2,74,4);
	textcolor(0);
	textbackground(8);
	
}

void quadro(int CI,int LI,int CF,int LF)
{
	
	int i;

	gotoxy(CI,LI), printf("%c",201); 
	gotoxy(CF,LI), printf("%c",187); 
	
	gotoxy(CI,LF), printf("%c",200); 
	gotoxy(CF,LF), printf("%c",188);


	//LINHA HORIZONTAL = 205
	for(i=CI+1; i<CF ; i++){
		gotoxy(i,LI), printf("%c",205);
		gotoxy(i,LF), printf("%c",205);
	}
	
	//LINHA VERTICAL = 186
	for(i=LI+1; i<LF ; i++){
		gotoxy(CI,i), printf("%c",186);
		gotoxy(CF,i), printf("%c",186);
	}			
			
}

char MenuRelatorio(void)
{
	gotoxy(8,14);
	printf("[A] - RELATORIO 1");
	gotoxy(8,16);
	printf("[B] - RELATORIO 2");
	textcolor(0);
	
	return toupper(getch());
}

char MenuOPC(void)
{
	int i = 8;
	
	gotoxy(8, i++), printf("[A] - CADASTRAR");
	i++;
	gotoxy(8, i++), printf("[B] - ALTERAR");
	i++;
	gotoxy(8, i++), printf("[C] - EXCLUSAO");
	i++;
	gotoxy(8, i++), printf("[D] - RELATORIO");
	i++;
	gotoxy(8, i++), printf("[E] - CONSULTA");
	i++;
	gotoxy(8, i++), printf("[ESC] - SAIR");
	
	textcolor(0);
	
	return toupper(getch());
}

char MenuPrincipal(void)
{
	char opc;
	Logo();
		textbackground(3);
		background(1,6,121,25);
		gotoxy(6,12);
		printf("[A] - TIPO DE JOGOS");
		gotoxy(6,13);
		printf("[B] - PARTICIPANTES");
		gotoxy(6,14);
		printf("[C] - CAMPEONATOS");
		gotoxy(6,15);
		printf("[D] - CONTROLE DE PARTICIPANTES");
		gotoxy(6,16);
		printf("[E] - RELATORIOS ESPECIFICOS");
		gotoxy(6,17);
		printf("[ESC] - ENCERRAR");
		textcolor(0);
		textbackground(3);
		quadro(1,6,38,19);
		quadro(40,6,120,19);
		quadro(1,20,120,24);
		opc = toupper(getch());
}

//-----------------------------FUN�OES DE BUSCA

int BuscaCampeonato(FILE *ponteiro, int COD) //BUSCA EXALTIVA [ATIVO]
{
	TpCampeonatos C;
	
	rewind(ponteiro);
	
	fread(&C, sizeof(TpCampeonatos), 1, ponteiro);
	while(!feof(ponteiro) && C.COD != COD && C.status == 1)
		fread(&C, sizeof(TpCampeonatos), 1, ponteiro);
		
	if(C.COD == COD)
		return ftell(ponteiro) - sizeof(TpCampeonatos);
	else
		return -1;
}

int BuscaJogo(FILE* ponteiro, int COD) 
{

    TpJogos J;
	
	rewind(ponteiro);
    
    fread(&J, sizeof(TpJogos), 1, ponteiro);
    while (!feof(ponteiro) && J.COD != COD && J.status == 1) 
        fread(&J, sizeof(TpJogos), 1, ponteiro);

    if (J.COD == COD) 
        return ftell(ponteiro) - sizeof(TpJogos);
    else 
        return -1;
}

int BuscaParticipantes(FILE *ponteiro, int COD) //BUSCA EXALTIVA [ATIVO]
{
	TpParticipantes P;
	
	rewind(ponteiro);
	
	fread(&P, sizeof(TpParticipantes), 1, ponteiro);
	while(!feof(ponteiro) && P.COD != COD && P.status == 1)
		fread(&P, sizeof(TpParticipantes), 1, ponteiro);
		
	if(P.COD == COD)
		return ftell(ponteiro) - sizeof(TpParticipantes);
	else
		return -1;
}

int BuscaParticipantesNome(FILE *ponteiro, char nome[30]) //BUSCA EXALTIVA [ATIVO]
{
	TpParticipantes P;
	
	rewind(ponteiro);
	
	fread(&P, sizeof(TpParticipantes), 1, ponteiro);
	while(!feof(ponteiro) && stricmp(P.desc,nome) != 0 && P.status == 1)
		fread(&P, sizeof(TpParticipantes), 1, ponteiro);
		
	if(stricmp(P.desc,nome) == 0)
		return ftell(ponteiro) - sizeof(TpParticipantes);
	else
		return -1;
}

int BuscaNick(FILE *ponteiro, char nick[30]) //BUSCA EXALTIVA [ATIVO]
{
	TpControle C;
	
	rewind(ponteiro);
	
	fread(&C, sizeof(TpControle), 1, ponteiro);
	while(!feof(ponteiro) && stricmp(nick,C.nick) != 0 && C.status == 1)
		fread(&C, sizeof(TpControle), 1, ponteiro);
		
	if(stricmp(nick,C.nick) == 0)
		return ftell(ponteiro) - sizeof(TpControle);
	else
		return -1;	
}

int BuscaControleCOD(FILE *ponteiro, int COD)
{
	TpControle C;
	
	rewind(ponteiro);
	
	fread(&C, sizeof(TpControle), 1, ponteiro);
	while(!feof(ponteiro) && C.CODParticipante != COD && C.status == 1)
		fread(&C, sizeof(TpControle), 1, ponteiro);
		
	if(C.CODParticipante == COD)
		return ftell(ponteiro) - sizeof(TpControle);
	else
		return -1;		
}
//-----------------------------FUN��ES DE CADASTRO

void CadastroTipoDeJogos(void)
{
	TpJogos J;
	int pos;
	FILE * ponteiro = fopen("jogos.dat","ab+");
	
	gotoxy(50,7); printf("================ CADASTRO DE JOGOS ================");
	gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
	gotoxy(50,9); printf("DIGITE O CODIGO :"); scanf("%d", &J.COD);
	
	while(J.COD > 0)
	{
		pos = BuscaJogo(ponteiro,J.COD);
		if(pos == -1)
		{
			gotoxy(50,11); printf("DESCRICAO DO JOGO : "); fflush(stdin); gets(J.desc);
			while(stricmp(J.desc,"\0") == 0)
			{
				gotoxy(50,11); printf("								");
				gotoxy(50,11); printf("DESCRICAO DO JOGO : "); fflush(stdin); gets(J.desc);
			}	
			J.status = 1;
			fwrite(&J, sizeof(TpJogos), 1, ponteiro);
			gotoxy(50,15); printf("================ CADASTRADO COM SUCESSO ================");
			getch();
		}
		else
		{
			gotoxy(50,12); printf("================ JOGO JA CADASTRADO ================");
			getch();
		}
		background(41,7,119,18);	
		gotoxy(50,7); printf("================ CADASTRO DE JOGOS ================");
		gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
		gotoxy(50,9); printf("DIGITE O CODIGO :"); scanf("%d", &J.COD);
	}
	ORDJogos();
	background(41,7,119,18);
	background(2,21,120,24);
	fclose(ponteiro);
}

void CadastroDeParticipantes(void)
{
	TpParticipantes P;	
	int pos;
	
	FILE * ponteiro = fopen("Participantes.dat","ab+");
	
	gotoxy(50,7); printf("================ CADASTRO DE PARTICIPANTES ================");
	gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
	gotoxy(50,9); printf("DIGITE O CODIGO DO PARTICIPANTE : "); scanf("%d", &P.COD);
	
	while(P.COD > 0)
	{
		pos = BuscaParticipantes(ponteiro,P.COD);
		
		if(pos == -1)
		{
			gotoxy(50,11); printf("DESCRICAO DO PARTICIPANTE : "); fflush(stdin); gets(P.desc);
			while(stricmp(P.desc,"\0") == 0)
			{
				gotoxy(50,11); printf("						       		");
				gotoxy(50,11); printf("DESCRICAO DO PARTICIPANTE : "); fflush(stdin); gets(P.desc);
			}
			P.status = 1;			
			fwrite(&P, sizeof(TpParticipantes), 1, ponteiro);
			gotoxy(50,15); printf("================ CADASTRADO COM SUCESSO ================");
			getch();
		}
		else
		{
			gotoxy(50,12); printf("================ PARTICIPANTE JA CADASTRADO ================");
			getch();
		}
		background(41,7,119,18);
		gotoxy(50,7); printf("================ CADASTRO DE PARTICIPANTES ================");
		gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
		gotoxy(50,9); printf("DIGITE O CODIGO DO PARTICIPANTE : "); scanf("%d", &P.COD);
	}
	ORDParticipantes();
	background(41,7,119,18);
	background(2,21,120,24);
	fclose(ponteiro);
}

void CadastroDosCampeonatos(void)
{
	FILE * ponteiro = fopen("Campeonatos.dat","ab+");
	FILE * ponteiroJogo = fopen("jogos.dat","rb");
	
	TpCampeonatos C;
	TpJogos J;
	int pos, auxCOD;
	
	gotoxy(50,7); printf("================ CADASTRO DOS CAMPEONATOS ================");
	gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
	gotoxy(50,9); printf("DIGITE O CODIGO DO CAMPEONATO : "); scanf("%d", &C.COD);
	
	while(C.COD > 0)
	{
		pos = BuscaCampeonato(ponteiro,C.COD);
		
		if(pos == -1)
		{
			gotoxy(50,11); printf("TITULO DO CAMPEONATO :"); fflush(stdin); gets(C.titulo);
			while(stricmp(C.titulo,"\0") == 0)
			{
				gotoxy(50,11); printf("								");
				gotoxy(50,11); printf("TITULO DO CAMPEONATO :"); fflush(stdin); gets(C.titulo);
			}	
					
			gotoxy(50,12); printf("RESPONSAVEL PELO CAMPEONATO :"); fflush(stdin); gets(C.responsavel);
			while(stricmp(C.responsavel,"\0") == 0)
			{
				gotoxy(50,12); printf("								");
				gotoxy(50,12); printf("RESPONSAVEL PELO CAMPEONATO :"); fflush(stdin); gets(C.responsavel);
			}
						
			gotoxy(50,13); printf("ANO DA DISPUTA : "); scanf("%d", &C.ano);
			while(C.ano <= 0)
			{
				gotoxy(50,13); printf("								"); 
				gotoxy(50,13); printf("ANO DA DISPUTA : "); scanf("%d", &C.ano);
			}
			
			gotoxy(50,14); printf("COD DO TIPO DO JOGO :"); scanf("%d", &auxCOD);
			while(BuscaJogo(ponteiroJogo,auxCOD) == -1)
			{
				gotoxy(50,14); printf("								");
				gotoxy(50,14); printf("COD DO TIPO DO JOGO :"); scanf("%d", &auxCOD);
			}
				
			gotoxy(50,15); printf("DESCRICAO DO CAMPEONATO : "); fflush(stdin); gets(C.desc); 
			while(stricmp(C.desc,"\0") == 0)
			{
				gotoxy(50,15); printf("								");
				gotoxy(50,15); printf("DESCRICAO DO CAMPEONATO : "); fflush(stdin); gets(C.desc);
			}
			
			C.status = 1;
			fwrite(&C, sizeof(TpCampeonatos), 1, ponteiro);
				
			gotoxy(50,18); printf("================ CADASTRADO COM SUCESSO ================");
			getch();		
		}
		else
		{
			gotoxy(50,11); printf("================ CAMPEONATO JA CADASTRADO ================");
			getch();
		}
		background(41,7,119,19);
		gotoxy(50,7); printf("================ CADASTRO DOS CAMPEONATOS ================");
		gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
		gotoxy(50,9); printf("DIGITE O CODIGO DO CAMPEONATO : "); scanf("%d", &C.COD);
	}
	ORDCampeonatos();
	background(41,7,119,18);
	background(2,21,120,24);
	fclose(ponteiro);
	fclose(ponteiroJogo);
}

void CadastroControle(void)
{
	FILE * ponteiro = fopen("Controle.dat","ab+");
	FILE * ponteiroC = fopen("Campeonatos.dat","rb");
	FILE * ponteiroP = fopen("Participantes.dat","rb");
	
	TpControle C;
	TpCampeonatos Camp;
	TpParticipantes P;
	
	char opc;
	int pos, auxCamp, auxPart;

	gotoxy(50,7); printf("================ CADASTRO DO CONTROLE ================");
	gotoxy(50,22); printf("DIGITE [ENTER] PARA SAIR");	
	gotoxy(50,9); printf("DIGITE O NICK DO CAMPEONATO : "); fflush(stdin); gets(C.nick);	
		
	while(stricmp(C.nick,"\0") != 0)
	{
		pos = BuscaNick(ponteiro,C.nick);
		
		if(pos == -1)
		{
			gotoxy(50,11); printf("DIGITE O COD DO CAMPEONATO : "); scanf("%d", &auxCamp);
			if(auxCamp > 0)
			{
				pos = BuscaCampeonato(ponteiroC,auxCamp);
				while(pos == -1)
				{
					gotoxy(50,11); printf("DIGITE O COD DO CAMPEONATO : "); scanf("%d", &auxCamp);
					pos = BuscaCampeonato(ponteiroC,auxCamp);
				}
				C.CODCampeonato == auxCamp;
			}
			
			gotoxy(50,13); printf("DIGITE O COD DO PARTICIPANTE : "); scanf("%d", &auxPart);
			if(auxPart > 0)
			{
				pos = BuscaParticipantes(ponteiroP, auxPart);
				while(pos == -1)
				{
					gotoxy(50,13); printf("DIGITE O COD DO PARTICIPANTE : "); scanf("%d", &auxPart);
					pos = BuscaParticipantes(ponteiroP, auxPart);
				}
				C.CODParticipante = auxPart;
			}	
			fwrite(&C, sizeof(TpControle), 1, ponteiro);
			gotoxy(50,15); printf("================ CADASTRADO COM SUCESSO ================");
			getch();		
		}
		else
		{
			gotoxy(50,11); printf("================ NICK JA CADASTRADO ================");
			
			fseek(ponteiro, pos, 0);
			fread(&C, sizeof(TpControle), 1, ponteiro);
			
			gotoxy(50,13); printf("CODIGO DO CAMPEONATO : %d", C.CODCampeonato);
			gotoxy(50,15); printf("CODIGO DO PARTICIPANTE : %d", C.CODParticipante);
			gotoxy(50,17); printf("NICK DO CAMPEONATO : %s", C.nick);
			getch();
		}
		background(41,7,119,19);
		gotoxy(50,7); printf("================ CADASTRO DO CONTROLE ================");
		gotoxy(50,22); printf("DIGITE [ENTER] PARA SAIR");	
		gotoxy(50,9); printf("DIGITE O NICK DO CAMPEONATO : "); fflush(stdin); gets(C.nick);
	}
	ORDControle();
	background(41,7,119,18);
	background(2,21,120,24);		
	fclose(ponteiro);	
	fclose(ponteiroC);
	fclose(ponteiroP);
}

int AnalisePartCamp(FILE *ponteiro, int CODCamp, int CODPart)
{
    TpControle C;
    rewind(ponteiro);

    fread(&C, sizeof(TpControle), 1, ponteiro);
    while (!feof(ponteiro) && C.CODCampeonato != CODCamp && C.CODParticipante != CODPart)
        fread(&C, sizeof(TpControle), 1, ponteiro);

    if (C.CODCampeonato == CODCamp && C.CODParticipante == CODPart)
    	return ftell(ponteiro) - sizeof(TpControle);
    else
        return -1;
}
//-----------------------------FUN��ES DE ALTERA��O

void AlterarTipoDeJogos(void)
{
	FILE * ponteiro = fopen("jogos.dat","rb+");
		
	TpJogos J;	
	
	int pos, auxCOD;
	
	gotoxy(50, 7); printf("================ ALTERACAO DE JOGOS ================");
	gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
	gotoxy(50,10); printf("DIGITE O COD DO JOGO : "); scanf("%d", &auxCOD);
	
	while(auxCOD > 0)
	{
		pos = BuscaJogo(ponteiro,auxCOD);
		if(pos == -1)
		{
			gotoxy(50,13); printf("================ JOGO NAO CADASTRADO ================");
			getch();
		}
		else
		{
			fseek(ponteiro, pos, 0);
			fread(&J, sizeof(TpJogos), 1, ponteiro);
			
			gotoxy(50,14); printf("NOVO COD DO JOGO : "); scanf("%d", &J.COD);
			gotoxy(50,16); printf("NOVA DESCRICAO : "); fflush(stdin); gets(J.desc);
			
			fseek(ponteiro, pos, 0);
			fwrite(&J, sizeof(TpJogos), 1, ponteiro);
			
			gotoxy(50,18); printf("================ ALTERADO COM SUCESSO ================");
			getch();
		}
		background(41,7,119,19);
		gotoxy(50, 7); printf("================ ALTERACAO DE JOGOS ================");
		gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
		gotoxy(50,10); printf("DIGITE O COD DO JOGO : "); scanf("%d", &auxCOD);
	}
	ORDJogos();
	background(41,7,119,18);
	background(2,21,120,24);
	fclose(ponteiro);
}

void AlterarParticipantes(void)
{
	FILE * ponteiro = fopen("Participantes.dat","rb+");
		
	TpParticipantes P;	
	
	int pos, auxCOD;
	
	gotoxy(50, 7); printf("================ ALTERACAO DE PARTICIPANTES ================");
	gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
	gotoxy(50,10); printf("DIGITE O COD DO PARTICIPANTE : "); scanf("%d", &auxCOD);
	
	while(auxCOD > 0)
	{
		pos = BuscaParticipantes(ponteiro,auxCOD);
		if(pos == -1)
		{
			gotoxy(50,13); printf("================ PARTICIPANTE NAO CADASTRADO ================");
			getch();
		}
		else
		{
			fseek(ponteiro, pos, 0);
			fread(&P, sizeof(TpParticipantes), 1, ponteiro);
			
			gotoxy(50,14); printf("NOVO COD DO PARTICIPANTE : "); scanf("%d", &P.COD);
			gotoxy(50,16); printf("NOVA DESCRICAO : "); fflush(stdin); gets(P.desc);
			
			fseek(ponteiro, pos, 0);
			fwrite(&P, sizeof(TpParticipantes), 1, ponteiro);
			
			gotoxy(50,18); printf("================ ALTERADO COM SUCESSO ================");
			getch();
		}
		background(41,7,119,19);
		gotoxy(50, 7); printf("================ ALTERACAO DE PARTICIPANTES ================");
		gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
		gotoxy(50,10); printf("DIGITE O COD DO PARTICIPANTE : "); scanf("%d", &auxCOD);
	}
	ORDParticipantes();
	background(41,7,119,18);
	background(2,21,120,24);
	fclose(ponteiro);
}

void AlterarCampeonato(void)
{
	FILE * ponteiro = fopen("Campeonatos.dat","rb+");
	FILE * ponteiroJogo = fopen("jogos.dat","rb");
	
	TpJogos J;
	TpCampeonatos C;
	
	int pos, auxCOD, auxCODTipo;
	
	gotoxy(50, 7); printf("================ ALTERACAO DO CAMPEONATO ================");
	gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
	gotoxy(50,9); printf("DIGITE O COD DO CAMPEONATO : "); scanf("%d", &auxCOD);
	
	while(auxCOD > 0)
	{
		pos = BuscaCampeonato(ponteiro,auxCOD);
		if(pos == -1)
		{
			gotoxy(50,11); printf("================ CAMPEONATO NAO CADASTRADO ================");
			getch();			
		}
		else
		{
			fseek(ponteiro, pos, 0);
			fread(&C, sizeof(TpCampeonatos), 1, ponteiro);
			
			gotoxy(50,12); printf("NOVO COD DO CAMPEONATO : "); scanf("%d", &C.COD);
						
			while(BuscaCampeonato(ponteiro,C.COD) != -1)
			{
				gotoxy(50,12); printf("NOVO COD DO CAMPEONATO : "); scanf("%d", &C.COD);
			}

			gotoxy(50,13); printf("NOVO TITULO : "); fflush(stdin); gets(C.titulo);
			gotoxy(50,14); printf("NOVO RESPONSAVEL : "); fflush(stdin); gets(C.responsavel);
			gotoxy(50,15); printf("NOVO ANO DA DISPUTA : "); scanf("%d", &C.ano);
			gotoxy(50,16); printf("NOVO COD DO TIPO DO JOGO : "); scanf("%d", &C.CodTipoDeJogo);
				
			while(BuscaJogo(ponteiroJogo,auxCODTipo) == -1)
			{
				gotoxy(50,16); printf("NOVO COD DO TIPO DO JOGO : "); scanf("%d", &auxCODTipo);
				
				if(auxCODTipo > 0)
					C.CodTipoDeJogo = auxCODTipo;
			}
	
			gotoxy(50,17); printf("NOVA DESCRICAO : "); fflush(stdin); gets(C.desc);
				
			fseek(ponteiro, pos, 0);
			fwrite(&C, sizeof(TpCampeonatos), 1, ponteiro);
				
			gotoxy(50,18); printf("================ ALTERADO COM SUCESSO ================");
			getch();
					
		}	
		background(41,7,119,19);
		gotoxy(50, 7); printf("================ ALTERACAO DO CAMPEONATO ================");
		gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
		gotoxy(50,10); printf("DIGITE O COD DO CAMPEONATO : "); scanf("%d", &auxCOD);
	}
	ORDCampeonatos();
	background(41,7,119,18);
	background(2,21,120,24);
	fclose(ponteiro);
	fclose(ponteiroJogo);	
}

void AlterarControle(void)
{
	FILE * ponteiro = fopen("Controle.dat","rb+");
	FILE * ponteiroC = fopen("Campeonatos.dat","rb");
	FILE * ponteiroP = fopen("Participantes.dat","rb");	
	
	TpControle C;
	TpCampeonatos Camp;
	TpParticipantes P;
	
	int pos, auxCamp, auxPart;
	char aux[30];
	
	gotoxy(50,7); printf("================ ALTERACAO DO CONTROLE ================");
	gotoxy(50,22); printf("DIGITE [ENTER] PARA SAIR");	
	gotoxy(50,9); printf("DIGITE O NICK DO CAMPEONATO : "); fflush(stdin); gets(aux);
	
	while(stricmp(aux,"\0") != 0)
	{
		
		pos = BuscaNick(ponteiro,aux);
		if(pos == -1)
		{
			gotoxy(50,11); printf("================ NICK NAO CADASTRADO ================");
			getch();
		}
		else
		{
			gotoxy(50,11); printf("DIGITE O NOVO COD DO CAMPEONATO : "); scanf("%d", &auxCamp);
			while(BuscaCampeonato(ponteiroC,auxCamp) == -1)
			
			{
				gotoxy(50,11); printf("                                          ");
				gotoxy(50,11); printf("DIGITE O NOVO COD DO CAMPEONATO : "); scanf("%d", &auxCamp);
			}
			C.CODCampeonato == auxCamp;
			
			gotoxy(50,13); printf("DIGITE O NOVO COD DO PARTICIPANTE : "); scanf("%d", &auxPart);
			while(BuscaParticipantes(ponteiroP, auxPart) == -1)
			{
				gotoxy(50,13); printf("                                          ");
				gotoxy(50,13); printf("DIGITE O NOVO COD DO PARTICIPANTE : "); scanf("%d", &auxPart);
			}
			C.CODParticipante = auxPart;
					
			fwrite(&C, sizeof(TpControle), 1, ponteiro);
			gotoxy(50,15); printf("================ ALTERADO COM SUCESSO ================");
			getch();			
		}
		background(41,7,119,19);
		gotoxy(50,7); printf("================ ALTERACAO DO CONTROLE ================");
		gotoxy(50,22); printf("DIGITE [ENTER] PARA SAIR");	
		gotoxy(50,9); printf("DIGITE O NICK DO CAMPEONATO : "); fflush(stdin); gets(aux);	
	}
	background(41,7,119,18);
	background(2,21,120,24);	
	fclose(ponteiro);
	fclose(ponteiroC);
	fclose(ponteiroP);	
}

//-----------------------------FUN��ES DE CONSULTA

void ConsultaTipoDeJogos(void)
{
	FILE * ponteiro = fopen("jogos.dat","rb");
	
	TpJogos J;
	
	int pos, auxCOD;
	
	gotoxy(50, 7); printf("================ CONSULTAR JOGOS ================");
	gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
	gotoxy(50,10); printf("DIGITE O COD DO JOGO : "); scanf("%d", &auxCOD);	
	
	while(auxCOD > 0)
	{
		pos = BuscaJogo(ponteiro,auxCOD);
		if(pos == -1)
		{
			gotoxy(50,14); printf("================ JOGOS NAO ENCONTRADO ================");
			getch();
		}
		else
		{
			fseek(ponteiro, pos, 0);
			fread(&J, sizeof(TpJogos), 1, ponteiro);
			
			gotoxy(45,12); printf("=====================================");
			
			gotoxy(50,14); printf("DESCRICAO DO JOGO : %s", J.desc);
			gotoxy(50,16); printf("CODIGO DO JOGO : %d", J.COD);
			
			gotoxy(45,18); printf("=====================================");
			
			getch();
		}
		background(41,7,119,19);
		gotoxy(50, 7); printf("================ CONSULTAR JOGOS ================");
		gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
		gotoxy(50,10); printf("DIGITE O COD DO JOGO : "); scanf("%d", &auxCOD);			
	}
	background(41,7,119,18);
	background(2,21,120,24);	
	fclose(ponteiro);
}

void ConsultaParticipantes(void)
{
	FILE * ponteiro = fopen("Participantes.dat","rb");
	
	TpParticipantes P;
	
	int pos, auxCOD;
	
	gotoxy(50, 7); printf("================ CONSULTAR PARTICIPANTES ================");
	gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
	gotoxy(50,10); printf("DIGITE O COD DO JOGO : "); scanf("%d", &auxCOD);	
	
	while(auxCOD > 0)
	{
		pos = BuscaParticipantes(ponteiro,auxCOD);
		if(pos == -1)
		{
			gotoxy(50,14); printf("================ PARTICIPANTE NAO ENCONTRADO ================");
			getch();
		}
		else
		{
			fseek(ponteiro, pos, 0);
			fread(&P, sizeof(TpParticipantes), 1, ponteiro);
			
			gotoxy(45,12); printf("=====================================");
			
			gotoxy(50,14); printf("DESCRICAO DO PARTICIPANTE : %s", P.desc);
			gotoxy(50,16); printf("CODIGO DO PARTICIPANTE : %d", P.COD);
			
			gotoxy(45,18); printf("=====================================");
			
			getch();
		}
		background(41,7,119,19);
		gotoxy(50, 7); printf("================ CONSULTAR PARTICIPANTES ================");
		gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
		gotoxy(50,10); printf("DIGITE O COD DO JOGO : "); scanf("%d", &auxCOD);			
	}
	background(41,7,119,18);
	background(2,21,120,24);	
	fclose(ponteiro);
}

void ConsultaDosCampeonatos(void)
{
	FILE * ponteiro = fopen("Campeonatos.dat","rb");
	
	TpCampeonatos C;
	
	int pos, auxCOD;
	
	gotoxy(50, 7); printf("================ CONSULTA DOS CAMPEONATOS ================");
	gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
	gotoxy(50,10); printf("DIGITE O COD DO CAMPEONATO : "); scanf("%d", &auxCOD);	
	
	while(auxCOD > 0)
	{
		pos = BuscaCampeonato(ponteiro,auxCOD);
		if(pos == -1)
		{
			gotoxy(50,14); printf("================ CAMPEONATO NAO ENCONTRADO ================");
			getch();
		}
		else
		{
			fseek(ponteiro, pos, 0);
			fread(&C, sizeof(TpCampeonatos), 1, ponteiro);
			
			gotoxy(45,11); printf("=====================================");
			
			gotoxy(50,17); printf("CODIGO DO CAMPEONATO : %d", C.COD);
			gotoxy(50,12); printf("TITULO : %s", C.titulo);
			gotoxy(50,13); printf("RESPONSAVEL : %s", C.responsavel);
			gotoxy(50,14); printf("ANO : %d", C.ano);
			gotoxy(50,15); printf("COD DO TIPO DO JOGO : %d", C.CodTipoDeJogo);
			gotoxy(50,16); printf("DESCRICAO : %s", C.desc);
			
			gotoxy(45,18); printf("=====================================");
			
			getch();
		}
		background(41,7,119,19);
		gotoxy(50, 7); printf("================ CONSULTA DOS CAMPEONATOS ================");
		gotoxy(50,22); printf("DIGITE [0] PARA SAIR");
		gotoxy(50,10); printf("DIGITE O COD DO CAMPEONATO : "); scanf("%d", &auxCOD);			
	}
	background(41,7,119,18);
	background(2,21,120,24);	
	fclose(ponteiro);
}

void ConsultaControle(void)
{
	FILE * ponteiro = fopen("Controle.dat","rb");
	
	TpControle C;
	
	int pos;
	char aux[30];
	
	gotoxy(50, 7); printf("================ CONSULTA CONTROLE DE PARTICIPANTES ================");
	gotoxy(50,22); printf("DIGITE [ENTER] PARA SAIR");
	gotoxy(50,9); printf("DIGITE O NICK : "); fflush(stdin); gets(aux);
	
	while(stricmp(aux,"\0") != 0)
	{
		pos = BuscaNick(ponteiro,aux);
		if(pos == -1)
		{
			gotoxy(50,11); printf("================ NICK NAO CADASTRADO ================");
			getch();
		}
		else
		{
			fseek(ponteiro, pos, 0);
			fread(&C, sizeof(TpControle), 1, ponteiro);
			
			gotoxy(50,11); printf("NICK : %s", C.nick);
			gotoxy(50,13); printf("COD DO CAMPEONATO : %d", C.CODCampeonato);
			gotoxy(50,15); printf("COD DO PARTICIPANTE : %d", C.CODParticipante);
			getch();
		}
		background(41,7,119,19);
		gotoxy(50, 7); printf("================ CONSULTA CONTROLE DE PARTICIPANTES ================");
		gotoxy(50,22); printf("DIGITE [ENTER] PARA SAIR");
		gotoxy(50,10); printf("DIGITE O NICK : "); fflush(stdin); gets(aux);
	}
	background(41,7,119,18);
	background(2,21,120,24);	
	fclose(ponteiro);	
}

//-----------------------------FUN��ES DE RELATORIO

void RelatorioJogos(void)
{
	FILE * ponteiro = fopen("jogos.dat","rb");
	
	TpJogos J;
	ORDJogos();
	
	gotoxy(49,7); printf("===================== RELATORIO DE JOGOS ====================");
	gotoxy(45,22); printf("PRESSIONE [ENTER] PARA IR PASSANDO OS CADASTROS");
	if(feof(ponteiro))
	{
		gotoxy(50,9); printf("================ NAO A JOGOS CADASTRADOS ================");
		getch();
	}
	else
	{
		fread(&J, sizeof(TpJogos), 1, ponteiro);
		
		while(!feof(ponteiro))
		{
				
			gotoxy(50,9); printf("COD : %d", J.COD);
			gotoxy(50,11); printf("DESCRICAO : %s", J.desc);
			getch();
			
			gotoxy(50,9); printf("                              ");
			gotoxy(50,11); printf("                              ");
			fread(&J, sizeof(TpJogos), 1, ponteiro);
		}
		gotoxy(70,17); printf("PRECIONE [ENTER] PARA SAIR");
		getch();
	}
	background(41,7,119,18);
	background(2,21,120,24);	
	fclose(ponteiro);
}

void RelatorioParticipantes(void)
{
	FILE * ponteiro = fopen("Participantes.dat","rb");
	
	TpParticipantes P;
	ORDParticipantes();
	
	gotoxy(49,7); printf("===================== RELATORIO DE PARTICIPANTES ====================");
	gotoxy(45,22); printf("PRESSIONE [ENTER] PARA IR PASSANDO OS CADASTROS");
	if(feof(ponteiro))
	{
		gotoxy(50,9); printf("================ NAO A PARTICIPANTES CADASTRADOS ================");
		getch();
	}
	else
	{
		fread(&P, sizeof(TpParticipantes), 1, ponteiro);
		
		while(!feof(ponteiro))
		{
					
			gotoxy(50,9); printf("COD : %d", P.COD);
			gotoxy(50,11); printf("DESCRICAO : %s", P.desc);
			getch();
			
			gotoxy(50,9); printf("                                            ");
			gotoxy(50,11); printf("                                             ");
			fread(&P, sizeof(TpParticipantes), 1, ponteiro);
		}
		gotoxy(70,17); printf("PRECIONE [ENTER] PARA SAIR");
	}
	background(41,7,119,18);
	background(2,21,120,24);	
	fclose(ponteiro);	
}

void RelatorioCampeonatos(void)
{
	FILE * ponteiro = fopen("Campeonatos.dat","rb");
	
	TpCampeonatos C;
	ORDCampeonatos();
	
	gotoxy(49,7); printf("===================== RELATORIO DE PARTICIPANTES ====================");
	gotoxy(45,22); printf("PRESSIONE [ENTER] PARA IR PASSANDO OS CADASTROS");
	if(feof(ponteiro))
	{
		gotoxy(50,9); printf("================ NAO A PARTICIPANTES CADASTRADOS ================");
		getch();
	}
	else
	{
		fread(&C, sizeof(TpCampeonatos), 1, ponteiro);
		
		while(!feof(ponteiro))
		{
					
			gotoxy(50,9); printf("COD : %d", C.COD);
			gotoxy(50,10); printf("TITULO : %s", C.titulo);
			gotoxy(50,11); printf("RESPONSAVEL : %s", C.responsavel);
			gotoxy(50,12); printf("ANO : %d", C.ano);
			gotoxy(50,13); printf("COD TIPO JOGO : %d", C.CodTipoDeJogo);
			gotoxy(50,14); printf("DESCRICAO : %s", C.desc);
			getch();
			
			gotoxy(50,9); printf("                                                                     ");
			gotoxy(50,10); printf("                                                                     ");
			gotoxy(50,11); printf("                                                                     ");
			gotoxy(50,12); printf("                                                                     ");
			gotoxy(50,13); printf("                                                                     ");
			gotoxy(50,14); printf("                                                                     ");
			
			fread(&C, sizeof(TpCampeonatos), 1, ponteiro);
		}
		gotoxy(70,17); printf("PRECIONE [ENTER] PARA SAIR");
		getch();
	}
	background(41,7,119,18);
	background(2,21,120,24);	
	fclose(ponteiro);	
}

void RelatorioControle(void)
{
	FILE * ponteiro = fopen("Controle.dat","rb");
	
	TpControle C;
	ORDControle();
	
	gotoxy(49,7); printf("===================== RELATORIO DE PARTICIPANTES ====================");
	gotoxy(45,22); printf("PRESSIONE [ENTER] PARA IR PASSANDO OS CADASTROS");
	if(feof(ponteiro))
	{
		gotoxy(50,9); printf("================ NAO A PARTICIPANTES CADASTRADOS ================");
		getch();
	}
	else
	{
		fread(&C, sizeof(TpControle), 1, ponteiro);
		
		while(!feof(ponteiro))
		{
					
			gotoxy(50,9); printf("COD DO CAMPEONATO: %d", C.CODCampeonato);
			gotoxy(50,11); printf("COD DO PARTICIANTE : %d", C.CODParticipante);
			gotoxy(50,13); printf("NICK : %s", C.nick);
			getch();
			
			gotoxy(50,9); printf("                                ");
			gotoxy(50,11); printf("                                ");
			gotoxy(50,13); printf("                                ");
			fread(&C, sizeof(TpControle), 1, ponteiro);
		}
		gotoxy(70,17); printf("PRECIONE [ENTER] PARA SAIR");
		getch();
	}
	background(41,7,119,18);
	background(2,21,120,24);	
	fclose(ponteiro);
}

//-----------------------------FUN��ES DE ORDENA��O

void ORDJogos(void)
{
	FILE * ponteiro = fopen("jogos.dat","rb+");
	
	TpJogos RA,RB;
	int a,b, qtde;
	
	fseek(ponteiro,0,2);
	qtde = ftell(ponteiro)/sizeof(TpJogos);
	
	for(a = 0; a < qtde-1; a++)
		for(b = a+1; b < qtde; b++)
		{
			fseek(ponteiro,a*sizeof(TpJogos),0);
			fread(&RA,sizeof(TpJogos),1,ponteiro);
			
			fseek(ponteiro,b*sizeof(TpJogos),0);
			fread(&RB,sizeof(TpJogos),1,ponteiro);
			
			if(RA.COD > RB.COD)
			{
				fseek(ponteiro,a*sizeof(TpJogos),0);
				fwrite(&RB,sizeof(TpJogos),1,ponteiro);
				
				fseek(ponteiro,b*sizeof(TpJogos),0);
				fwrite(&RA,sizeof(TpJogos),1,ponteiro);
			}
		}
	fclose(ponteiro);
}

void ORDParticipantes(void)
{
	FILE * ponteiro = fopen("Participantes.dat","rb+");
	
	TpParticipantes RA,RB;
	int a,b, qtde;
	
	fseek(ponteiro,0,2);
	qtde = ftell(ponteiro)/sizeof(TpParticipantes);
	
	for(a = 0; a < qtde-1; a++)
		for(b = a+1; b < qtde; b++)
		{
			fseek(ponteiro,a*sizeof(TpParticipantes),0);
			fread(&RA,sizeof(TpParticipantes),1,ponteiro);
			
			fseek(ponteiro,b*sizeof(TpParticipantes),0);
			fread(&RB,sizeof(TpParticipantes),1,ponteiro);
			
			if(RA.COD > RB.COD)
			{
				fseek(ponteiro,a*sizeof(TpParticipantes),0);
				fwrite(&RB,sizeof(TpParticipantes),1,ponteiro);
				
				fseek(ponteiro,b*sizeof(TpParticipantes),0);
				fwrite(&RA,sizeof(TpParticipantes),1,ponteiro);
			}
		}
	fclose(ponteiro);
}

void ORDCampeonatos(void)
{
	FILE * ponteiro = fopen("Participantes.dat","rb+");
	
	TpCampeonatos RA,RB;
	int a,b, qtde;
	
	fseek(ponteiro,0,2);
	qtde = ftell(ponteiro)/sizeof(TpCampeonatos);
	
	for(a = 0; a < qtde-1; a++)
		for(b = a+1; b < qtde; b++)
		{
			fseek(ponteiro,a*sizeof(TpCampeonatos),0);
			fread(&RA,sizeof(TpCampeonatos),1,ponteiro);
			
			fseek(ponteiro,b*sizeof(TpCampeonatos),0);
			fread(&RB,sizeof(TpCampeonatos),1,ponteiro);
			
			if(RA.COD > RB.COD)
			{
				fseek(ponteiro,a*sizeof(TpCampeonatos),0);
				fwrite(&RB,sizeof(TpCampeonatos),1,ponteiro);
				
				fseek(ponteiro,b*sizeof(TpCampeonatos),0);
				fwrite(&RA,sizeof(TpCampeonatos),1,ponteiro);
			}
		}
	fclose(ponteiro);
}

void ORDControle(void)
{
	FILE * ponteiro = fopen("Controle.dat","rb+");
	
	TpControle RA,RB;
	int a,b, qtde;
	
	fseek(ponteiro,0,2);
	qtde = ftell(ponteiro)/sizeof(TpControle);
	
	for(a = 0; a < qtde-1; a++)
		for(b = a+1; b < qtde; b++)
		{
			fseek(ponteiro,a*sizeof(TpControle),0);
			fread(&RA,sizeof(TpControle),1,ponteiro);
			
			fseek(ponteiro,b*sizeof(TpControle),0);
			fread(&RB,sizeof(TpControle),1,ponteiro);
			
			if(RA.CODParticipante > RB.CODParticipante)
			{
				fseek(ponteiro,a*sizeof(TpControle),0);
				fwrite(&RB,sizeof(TpControle),1,ponteiro);
				
				fseek(ponteiro,b*sizeof(TpControle),0);
				fwrite(&RA,sizeof(TpControle),1,ponteiro);
			}
		}
	fclose(ponteiro);
}

//-------------------------FUN��ES DE EXCLUSAO

void ExclusaoJogo(void)
{
	TpJogos J;
	int COD, pos, i;
	char op;
	
	FILE * ponteiro = fopen("jogos.dat", "rb+");
	
	if(ponteiro == NULL)
	{
		
		textcolor(RED);
		gotoxy(45,11);
		printf("Erro de Abertura!");
		textcolor(0);
		getch();
	}
	else
	{
		gotoxy(49,7); printf("===================== [EXCLUSAO DE JOGOS] ====================");	
		
		gotoxy(45,22); printf("(![DIGITE '0' PARA SAIR]!) ");
		gotoxy(45,9); printf("DIGITE O COD DO JOGO : "); scanf("%d", &COD);
		
		while(COD > 0)
		{
			pos = BuscaJogo(ponteiro, COD);
			if(pos == -1)
			{
				gotoxy(45,11); printf("===================== JOGO NAO CADASTRADO =====================");
				getch();
			}	
			else
			{
				fseek(ponteiro, pos, 0);
				fread(&J, sizeof(TpJogos), 1, ponteiro);
				
				if(J.status == 1)
				{
					gotoxy(45,9),printf("DADOS DO JOGO :");
					
					gotoxy(45,11),printf("COD : %d", J.COD);
					gotoxy(45,12),printf("DESCRICAO : %s", J.desc);
					
					gotoxy(45,14),printf("CONFIRMA  A EXCLUSAO? (S/N)");

					if(toupper(getch()) == 'S')
					{
						
						fseek(ponteiro, pos ,0);
						J.status = 0;					
						fwrite(&J, sizeof(TpJogos), 1, ponteiro);
						
						
						gotoxy(45,17); printf("=========== EXCLUSAO CONCLUIDA COM SUCESSO ===========");
						getch();
					}
					else
					{
						gotoxy(45,17),printf("================== EXCLUSAO CANCELADA ==================");
						getch();
					}
				}
				else
				{	
					gotoxy(45,17); printf("===================== JOGO NAO CADASTRADO =====================");
					getch();
				}					
			}
			background(41,7,119,18);
			gotoxy(49,7); printf("===================== [EXCLUSAO DE JOGOS] ====================");	
			
			gotoxy(45,22); printf("(![DIGITE '0' PARA SAIR]!) ");
			gotoxy(45,9); printf("DIGITE O COD DO JOGO : "); scanf("%d", &COD);	
		}
	}
	background(41,7,119,18);
	background(2,21,120,24);
	
//--------------------Exclusao fisica

	FILE * Auxiliar = fopen("Auxiliar.dat","wb");
	
	rewind(ponteiro);
	
	fread(&J, sizeof(TpJogos), 1, ponteiro);
	while(!feof(ponteiro))
	{
		if(J.status == 1)
			fwrite(&J, sizeof(TpJogos), 1, Auxiliar);
		fread(&J, sizeof(TpJogos), 1, ponteiro);		
	}
	fclose(ponteiro);
	fclose(Auxiliar);
	remove("jogos.dat");
	rename("Auxiliar.dat","jogos.dat");	
}

void ExclusaoParticipante(void)
{
	TpParticipantes P;
	int COD, pos, i;
	char op;
	
	FILE * ponteiro = fopen("Participantes.dat", "rb+");
	
	if(ponteiro == NULL)
	{
		
		textcolor(RED);
		gotoxy(45,11);
		printf("Erro de Abertura!");
		textcolor(0);
		getch();
	}
	else
	{
		gotoxy(49,7); printf("===================== [EXCLUSAO DE PARTICIPANTES] ====================");	
		
		gotoxy(45,22); printf("(![DIGITE '0' PARA SAIR]!) ");
		gotoxy(45,9); printf("DIGITE O COD DO PARTICIPANTE : "); scanf("%d", &COD);
		
		while(COD > 0)
		{
			pos = BuscaParticipantes(ponteiro, COD);
			if(pos == -1)
			{
				gotoxy(45,11); printf("===================== PARTICIPANTE NAO CADASTRADO =====================");
				getch();
			}	
			else
			{
				fseek(ponteiro, pos, 0);
				fread(&P, sizeof(TpParticipantes), 1, ponteiro);
				
				if(P.status == 1)
				{
					gotoxy(45,9),printf("DADOS DO PARTICIPANTE :");
					
					gotoxy(45,11),printf("COD : %d", P.COD);
					gotoxy(45,12),printf("DESCRICAO : %s", P.desc);
					
					gotoxy(45,14),printf("CONFIRMA  A EXCLUSAO? (S/N)");

					if(toupper(getch()) == 'S')
					{
						
						fseek(ponteiro, pos ,0);
						P.status = 0;					
						fwrite(&P, sizeof(TpParticipantes), 1, ponteiro);
						
						
						gotoxy(45,17); printf("=========== EXCLUSAO CONCLUIDA COM SUCESSO ===========");
						getch();
					}
					else
					{
						gotoxy(45,17),printf("================== EXCLUSAO CANCELADA ==================");
						getch();
					}
				}
				else
				{	
					gotoxy(45,17); printf("===================== PARTICIPANTE NAO CADASTRADO =====================");
					getch();
				}					
			}
			background(41,7,119,18);
			gotoxy(49,7); printf("===================== [EXCLUSAO DE PARTICIPANTES] ====================");	
			
			gotoxy(45,22); printf("(![DIGITE '0' PARA SAIR]!) ");
			gotoxy(45,9); printf("DIGITE O COD DO PARTICIPANTE : "); scanf("%d", &COD);	
		}
	}
	background(41,7,119,18);
	background(2,21,120,24);
	
//--------------------Exclusao fisica

	FILE * Auxiliar = fopen("Auxiliar.dat","wb");
	
	rewind(ponteiro);
	
	fread(&P, sizeof(TpParticipantes), 1, ponteiro);
	while(!feof(ponteiro))
	{
		if(P.status == 1)
			fwrite(&P, sizeof(TpParticipantes), 1, Auxiliar);
		fread(&P, sizeof(TpParticipantes), 1, ponteiro);		
	}
	fclose(ponteiro);
	fclose(Auxiliar);
	remove("Participantes.dat");
	rename("Auxiliar.dat","Participantes.dat");	
}

void ExclusaoCampeonato(void)
{
	TpCampeonatos C;
	int COD, pos, i;
	char op;
	
	FILE * ponteiro = fopen("Campeonatos.dat", "rb+");
	
	if(ponteiro == NULL)
	{
		
		textcolor(RED);
		gotoxy(45,11);
		printf("Erro de Abertura!");
		textcolor(0);
		getch();
	}
	else
	{
		gotoxy(49,7); printf("===================== [EXCLUSAO DE CAMPEONATOS] ====================");	
		
		gotoxy(45,22); printf("(![DIGITE '0' PARA SAIR]!) ");
		gotoxy(45,9); printf("DIGITE O COD DO CAMPEONATO : "); scanf("%d", &COD);
		
		while(COD > 0)
		{
			pos = BuscaCampeonato(ponteiro, COD);
			if(pos == -1)
			{
				gotoxy(45,11); printf("===================== CAMPEONATO NAO CADASTRADO =====================");
				getch();
			}	
			else
			{
				fseek(ponteiro, pos, 0);
				fread(&C, sizeof(TpCampeonatos), 1, ponteiro);
				
				if(C.status == 1)
				{
					gotoxy(45,10),printf("================== DADOS DO CAMPEONATO ==================");
					
					gotoxy(45,11),printf("COD : %d", C.COD);
					gotoxy(45,12),printf("TITULO : %s", C.titulo);
					gotoxy(45,13),printf("RESPONSAVEL : %s", C.responsavel);
					gotoxy(45,14),printf("ANO : %d", C.ano);
					gotoxy(45,15),printf("COD TIPO DO JOGO : %d", C.CodTipoDeJogo);
					gotoxy(45,16),printf("DESCRICAO : %s", C.desc);
					
					gotoxy(45,17),printf("CONFIRMA  A EXCLUSAO? (S/N)");

					if(toupper(getch()) == 'S')
					{
						
						fseek(ponteiro, pos ,0);
						C.status = 0;					
						fwrite(&C, sizeof(TpCampeonatos), 1, ponteiro);
						
						
						gotoxy(45,18); printf("=========== EXCLUSAO CONCLUIDA COM SUCESSO ===========");
						getch();
					}
					else
					{
						gotoxy(45,18),printf("================== EXCLUSAO CANCELADA ==================");
						getch();
					}
				}
				else
				{	
					gotoxy(45,17); printf("===================== PARTICIPANTE NAO CADASTRADO =====================");
					getch();
				}					
			}
			background(41,7,119,19);
			gotoxy(49,7); printf("===================== [EXCLUSAO DE CAMPEONATO] ====================");	
			
			gotoxy(45,22); printf("(![DIGITE '0' PARA SAIR]!) ");
			gotoxy(45,9); printf("DIGITE O COD DO CAMPEONATO : "); scanf("%d", &COD);	
		}
	}
	background(41,7,119,19);
	background(2,21,120,24);
	
//--------------------Exclusao fisica

	FILE * Auxiliar = fopen("Auxiliar.dat","wb");
	
	rewind(ponteiro);
	
	fread(&C, sizeof(TpCampeonatos), 1, ponteiro);
	while(!feof(ponteiro))
	{
		if(C.status == 1)
			fwrite(&C, sizeof(TpCampeonatos), 1, Auxiliar);
		fread(&C, sizeof(TpCampeonatos), 1, ponteiro);		
	}
	fclose(ponteiro);
	fclose(Auxiliar);
	remove("Campeonatos.dat");
	rename("Auxiliar.dat","Campeonatos.dat");	
}

void ExclusaoControle(void)
{
	TpControle C;
	int COD, pos, i;
	char op, aux[30];
	
	FILE * ponteiro = fopen("Controle.dat", "rb+");
	
	if(ponteiro == NULL)
	{
		
		textcolor(RED);
		gotoxy(45,11);
		printf("Erro de Abertura!");
		textcolor(0);
		getch();
	}
	else
	{
		gotoxy(49,7); printf("===================== [EXCLUSAO DO CONTROLE] ====================");	
		
		gotoxy(45,22); printf("(![PRECIONE 'ENTER' PARA SAIR]!) ");
		gotoxy(45,9); printf("DIGITE O NICK : "); fflush(stdin); gets(aux);
		
		while(stricmp(aux,"\0") != 0)
		{
			pos = BuscaNick(ponteiro, aux);
			if(pos == -1)
			{
				gotoxy(45,11); printf("===================== JOGO NAO CADASTRADO =====================");
				getch();
			}	
			else
			{
				fseek(ponteiro, pos, 0);
				fread(&C, sizeof(TpControle), 1, ponteiro);
				
				if(C.status == 1)
				{
					gotoxy(45,9),printf("DADOS :");
					gotoxy(45,11),printf("NICK : %s", C.nick);
					gotoxy(45,12),printf("COD DO COMPEONATO : %d", C.CODCampeonato);
					gotoxy(45,13),printf("COD DO PARTICIPANTE : %d", C.CODParticipante);
					
					gotoxy(45,15),printf("CONFIRMA  A EXCLUSAO? (S/N)");

					if(toupper(getch()) == 'S')
					{
						
						fseek(ponteiro, pos ,0);
						C.status = 0;					
						fwrite(&C, sizeof(TpControle), 1, ponteiro);
						
						
						gotoxy(45,17); printf("=========== EXCLUSAO CONCLUIDA COM SUCESSO ===========");
						getch();
					}
					else
					{
						gotoxy(45,17),printf("================== EXCLUSAO CANCELADA ==================");
						getch();
					}
				}
				else
				{	
					gotoxy(45,17); printf("===================== NICK NAO CADASTRADO =====================");
					getch();
				}					
			}
			background(41,7,119,18);
			gotoxy(49,7); printf("===================== [EXCLUSAO DO CONTROLE] ====================");	
			
			gotoxy(45,22); printf("(![PRECIONE 'ENTER' PARA SAIR]!) ");
			gotoxy(45,9); printf("DIGITE O NICK : "); fflush(stdin); gets(aux);	
		}
	}
	background(41,7,119,18);
	
	background(2,21,120,24);
	
//--------------------Exclusao fisica

	FILE * Auxiliar = fopen("Auxiliar.dat","wb");
	
	rewind(ponteiro);
	
	fread(&C, sizeof(TpControle), 1, ponteiro);
	while(!feof(ponteiro))
	{
		if(C.status == 1)
			fwrite(&C, sizeof(TpControle), 1, Auxiliar);
		fread(&C, sizeof(TpControle), 1, ponteiro);		
	}
	fclose(ponteiro);
	fclose(Auxiliar);
	remove("Controle.dat");
	rename("Auxiliar.dat","Controle.dat");	
}

void Relatorio1(void)
{
	int i, pos1, pos2, pos3, pos4, aux1, aux2, aux3, cont=0, contT=0;
	
	TpJogos R1;
	TpParticipantes R2;
	TpCampeonatos R3;
	TpControle R4;
	
	FILE * Pont1 = fopen("jogos.dat", "rb");
	FILE * Pont2 = fopen("Participantes.dat", "rb");
	FILE * Pont3 = fopen("Campeonatos.dat", "rb");
	FILE * Pont4 = fopen("Controle.dat", "rb");
	

	gotoxy(50,9); printf("RELATORIO DE CAMPEONATOS DO PARTICIPANTE");
	
	rewind(Pont1);
	rewind(Pont2);
	rewind(Pont3);
	rewind(Pont4);
	
	fread(&R1, sizeof(TpJogos), 1, Pont1);
	fread(&R2, sizeof(TpParticipantes), 1, Pont2);
	fread(&R3, sizeof(TpCampeonatos), 1, Pont3);
	fread(&R4, sizeof(TpControle), 1, Pont4);
	
	gotoxy(50,10); printf("Digite o codigo do participante: "); scanf("%d",&aux1);
	
	while(aux1 != 0)
	{
		pos1 = BuscaParticipantes(Pont2, aux1); 
		if (pos1 != -1)
		{
			gotoxy(50,10); printf("                                      ");
			
			fseek (Pont2, pos1, 0);
			fread(&R2, sizeof(TpParticipantes), 1, Pont2);
			
			gotoxy(50,10); printf("Jogador selecionado: %s",R2.desc);
			
			gotoxy(50,11); printf("---------------------------------------------------------------");
			pos2 = BuscaControleCOD(Pont4, aux1);
			if(pos2 != -1) 
			{
				rewind(Pont4);
				fread(&R4, sizeof(TpControle), 1, Pont4);
				
				i=12;
				while(!feof(Pont4))
				{
					if(R4.CODParticipante == aux1)
					{
						aux2 = R4.CODCampeonato;
						pos3 = BuscaCampeonato(Pont3, aux2);
						
						if(pos3 != -1)//achou
						{
							fseek (Pont3, pos3, 0);
							fread(&R3, sizeof(TpCampeonatos), 1, Pont3);
							
							aux3 = R3.CodTipoDeJogo;
							
							pos4 = BuscaJogo(Pont1, aux3);
							if(pos4 != -1)
							{
								fseek (Pont1, pos4, 0);
								fread(&R1, sizeof(TpJogos), 1, Pont1);
								gotoxy(50,i);
								printf("-> Tipo de jogo: %s",R1.desc);
								i++;
								cont=0;
								rewind(Pont3);
								fread(&R3, sizeof(TpCampeonatos), 1, Pont3);
								while(!feof(Pont3))
								{	
									if(R3.COD == aux2)
									{ 
										gotoxy(50,i);
										printf("\t %s - Responsavel: %s (%d) - Nick: %s\n",R3.titulo, R3.responsavel, R3.ano, R4.nick);
										i++;
										cont++;
										contT++;
									}
									fread(&R3, sizeof(TpCampeonatos), 1, Pont3);
								}
								gotoxy(50,i);
								printf("Total de campeonatos: %d",cont);
								i++;
								gotoxy(50,i);
								printf("-------------------------------------------------------------------------------------");
								i=i++;
							}
						}
					}
					fread(&R4, sizeof(TpControle), 1, Pont4);
				}
				gotoxy(50,i); printf("Total de campeonatos do participante: %d",contT);
				getch();
			}
		}
		else
		{
			gotoxy(50,17);printf("Mensagem: Codigo do jogador nao encontrado!");
			getch();
		}
		background(41,7,119,19);
		gotoxy(50,8); printf("RELATORIO DE CAMPEONATOS DO PARTICIPANTE");
		gotoxy(50,10); printf("Digite o codigo do jogador: "); scanf("%d",&aux1);
		
	}
	background(41,7,119,18);
	background(2,21,120,24);	
	fclose(Pont1);
	fclose(Pont2);
	fclose(Pont3);
	fclose(Pont4);	
}

void InserirJogos(void) 
{	
	FILE * Ptrjogos = fopen("jogos.dat", "ab+");
	
	TpJogos R;
	

	R.COD = 1;
	strcpy(R.desc, "League of Legends");
	R.status = 1;
	fwrite(&R, sizeof(TpJogos), 1, Ptrjogos);
	
	R.COD = 2;
	strcpy(R.desc, "Fortnite");
	R.status = 1;
	fwrite(&R, sizeof(TpJogos), 1, Ptrjogos);
	
	R.COD = 3;
	strcpy(R.desc, "Mortal Kombat");
	R.status = 1;
	fwrite(&R, sizeof(TpJogos), 1, Ptrjogos);
	
	R.COD = 4;
	strcpy(R.desc, "CS:GO");
	R.status = 1;
	fwrite(&R, sizeof(TpJogos), 1, Ptrjogos);
	
	fclose(Ptrjogos);
}

void InserirPart(void) 
{	
	FILE * PtrPart = fopen("Participantes.dat", "ab+");
	
	TpParticipantes R;
	
	R.COD = 10;
	strcpy(R.desc, "Marcelo coldzera David");
	R.status = 1;
	fwrite(&R, sizeof(TpParticipantes), 1, PtrPart);
	
	R.COD = 20;
	strcpy(R.desc, "Olof olofmeister Kajbjer");
	R.status = 1;
	fwrite(&R, sizeof(TpParticipantes), 1, PtrPart);
	
	R.COD = 30;
	strcpy(R.desc, "Ladslav GuardiaN Kovacs");
	R.status = 1;
	fwrite(&R, sizeof(TpParticipantes), 1, PtrPart);
	
	R.COD = 40;
	strcpy(R.desc, "Nicolai dev1ce Reedtz");
	R.status = 1;
	fwrite(&R, sizeof(TpParticipantes), 1, PtrPart);
	
	R.COD = 50;
	strcpy(R.desc, "Santorin");
	R.status = 1;
	fwrite(&R, sizeof(TpParticipantes), 1, PtrPart);
	
	R.COD = 60;
	strcpy(R.desc, "SGD Sty1eee");
	R.status = 1;
	fwrite(&R, sizeof(TpParticipantes), 1, PtrPart);
	
	R.COD = 70;
	strcpy(R.desc, "Solokill3hk");
	R.status = 1;
	fwrite(&R, sizeof(TpParticipantes), 1, PtrPart);

	R.COD = 80;
	strcpy(R.desc, "JUGKlNG");
	R.status = 1;
	fwrite(&R, sizeof(TpParticipantes), 1, PtrPart);
	
	R.COD = 90;
	strcpy(R.desc, "Kyle Giersdorf (Bugha)");
	R.status = 1;
	fwrite(&R, sizeof(TpParticipantes), 1, PtrPart);
	
	fclose(PtrPart);
}

void InserirCamp(void) 
{	
	FILE * PtrCamp = fopen("Campeonatos.dat", "ab+");
	
	TpCampeonatos R;
	
	R.COD = 123;
	strcpy(R.titulo, "Mundial de LoL");
	strcpy(R.responsavel, "Riot Games");
	R.ano = 2019;
	R.CodTipoDeJogo = 1;
	strcpy(R.desc, "O torneio mais importante do MOBA da Riot Games..");
	R.status = 1;
	fwrite(&R, sizeof(TpCampeonatos), 1, PtrCamp);
	
	R.COD = 456;
	strcpy(R.titulo, "Copa do Mundo de Fortnite");
	strcpy(R.responsavel, "Epic Games");
	R.ano = 2019;
	R.CodTipoDeJogo = 2;
	strcpy(R.desc, "A jornada para a Fortnite Word Cup comeca com dez..");
	R.status = 1;
	fwrite(&R, sizeof(TpCampeonatos), 1, PtrCamp);
	
	R.COD = 789;
	strcpy(R.titulo, "Campeonato Brasileiro de CS:GO");
	strcpy(R.responsavel, "Valve");
	R.ano = 2020;
	R.CodTipoDeJogo = 3;
	strcpy(R.desc, "Uma nova competicao Counter-Strike: Global ..");
	R.status = 1;
	fwrite(&R, sizeof(TpCampeonatos), 1, PtrCamp);
	
	fclose(PtrCamp);
}

void InserirNick(void) 
{	
	FILE * ponteiro = fopen("Controle.dat", "ab+");
	TpControle R;
	
	R.CODCampeonato = 789;
	R.CODParticipante = 20;
	strcpy(R.nick, "SQ BOOTCAMP");
	strcpy(R.nome, "Olof olofmeister Kajbjer");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);
	
	R.CODCampeonato = 789;
	R.CODParticipante = 10;
	strcpy(R.nick, "PERAQTOCOSTA");
	strcpy(R.nome, "Marcelo coldzera David");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);
		
	R.CODCampeonato = 123;
	R.CODParticipante = 10;
	strcpy(R.nick, "KT ROLSTER");
	strcpy(R.nome, "Marcelo coldzera David");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);
		
	R.CODCampeonato = 123;
	R.CODParticipante = 20;
	strcpy(R.nick, "FREECS");
	strcpy(R.nome, "Olof olofmeister Kajbjer");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);
		
	R.CODCampeonato = 789;
	R.CODParticipante = 40;
	strcpy(R.nick, "INSTANTK");
	strcpy(R.nome, "Nicolai dev1ce Reedtz");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);
	
	R.CODCampeonato = 123;
	R.CODParticipante = 90;
	strcpy(R.nick, "ROYAL NEVER");
	strcpy(R.nome, "Kyle Giersdorf (Bugha)");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);	
		
	R.CODCampeonato = 123;
	R.CODParticipante = 30;
	strcpy(R.nick, "GEN.G");
	strcpy(R.nome, "Ladslav GuardiaN Kovacs");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);
		
	R.CODCampeonato = 789;
	R.CODParticipante = 50;
	strcpy(R.nick, "NASDH");
	strcpy(R.nome, "Santorin");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);
	
	R.CODCampeonato = 456;
	R.CODParticipante = 60;
	strcpy(R.nick, "BUGHA");
	strcpy(R.nome, "SGD Sty1eee");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);
	
	R.CODCampeonato = 123;
	R.CODParticipante = 80;
	strcpy(R.nick, "ROOKIE");
	strcpy(R.nome, "JUGKlNG");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);
	
	R.CODCampeonato = 456;
	R.CODParticipante = 70;
	strcpy(R.nick, "NYHROX");
	strcpy(R.nome, "Solokill3hk");
	R.status = 1;
	fwrite(&R, sizeof(TpControle), 1, ponteiro);		
	
	fclose(ponteiro);
}
//-----------------------------FUN��ES PRINCIPAIS

void Executar(void)
{
	// InserirJogos();
	// InserirPart();
	// InserirCamp();
	// InserirNick();
	
	char opc1, opc2;
	
	do
	{
		
		opc1 = MenuPrincipal();
		
		clrscr();
		Logo();
		textcolor(0);
		textbackground(3);
		quadro(1,6,38,19);
		quadro(40,6,120,19);
		quadro(1,20,120,24);
			
		switch(opc1)
		{
			case 'A':
				do
				{		
					opc2 = MenuOPC();
					
					switch(opc2)
					{
						case 'A':
							CadastroTipoDeJogos();
							break;
							
						case 'B':
							AlterarTipoDeJogos();
							break;
							
						case 'C':
							ExclusaoJogo();
							break;
							
						case 'D':
							RelatorioJogos();
							break;
							
						case 'E':
							ConsultaTipoDeJogos();
							break;
					}
					
				}while(opc2 != 27);
			
			break;
				
			case 'B':
				do
				{
					opc2 = MenuOPC();
					
					switch(opc2)
					{
						case 'A':
							CadastroDeParticipantes();
							break;
							
						case 'B':
							AlterarParticipantes();
							break;
							
						case 'C':
							ExclusaoParticipante();
							break;
															
						case 'D':
							RelatorioParticipantes();
							break;
							
						case 'E':
							ConsultaParticipantes();
							break;
					}
					
				}while(opc2 != 27);
					
			break;
					
			case 'C':
				do
				{
					opc2 = MenuOPC();
					
					switch(opc2)
					{
						case 'A':
							CadastroDosCampeonatos();
							break;
							
						case 'B':
							AlterarCampeonato();
							break;
							
						case 'C':
							ExclusaoCampeonato();
							break;
													
						case 'D':
							RelatorioCampeonatos();
							break;
							
						case 'E':
							ConsultaDosCampeonatos();
							break;
					}
					
				}while(opc2 != 27);
				
			break; 
					
			case 'D':
				do
				{
					opc2 = MenuOPC();
				
					switch(opc2)
					{
						case 'A':
							CadastroControle();
							break;
							
						case 'B':
							AlterarControle();
							break;
	
						case 'C':
							ExclusaoControle();
							break;	
													
						case 'D':
							RelatorioControle();
							break;
							
						case 'E':
							ConsultaControle();	
							break;
					}
				}while(opc2 != 27);
				
			break;	
			
			case 'E':
				do
				{
					opc2 = MenuRelatorio();
					
					switch(opc2)
					{
						case'A':
							Relatorio1();
							break;
							
						case'B':
							break;
					}
					
				}while(opc2 != 27);
				
			break;	
		}
		
	}while(opc1 != 27);
}

int main(void)
{
	Executar();
	return 0;
}
