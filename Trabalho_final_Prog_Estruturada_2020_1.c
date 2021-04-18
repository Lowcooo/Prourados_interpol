/*PROJETO FINAL*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "conio.h"
#include "conio2.h"
#include <time.h>
#include <ctype.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13

#define TAM 100

typedef struct data DATA;
struct data{
    int dia;
    int mes;
    int ano;
};

typedef struct aniversario ANIVERSARIO;
struct aniversario{
    DATA birthday;
};

typedef struct pessoa PESSOA;
struct pessoa{
    char nome[TAM];
    char sexo[TAM];
    char crime_desejado[TAM];
    char pais_procurado[TAM];
    DATA aniv;
};

// DECLARAÇÃO DE FUNÇÕES.
int menu_interativo();
int menu_principal();
void logo();
void maiusculo_carac(char string[]);
int valida_data(int dia, int mes, int ano);
void pais();
void crime();
void procurado();
void mostra_pais();
void mostra_crime();
void mostra_procurado();
void levantamento();
int creditos();
int busca_pais(char busca[TAM]);
int busca_crime(char busca[]);

int main(void){
menu_principal();
}

int menu_principal(){
	
	int opcao;
    char opcaoSeta [9][40] = {{"----Cadastrar país"}, {"----Cadastrar crime do procurado"}, {"----Cadastrar procurado"}, {"----Listar procurado por país"}, {"----Listar procurado por crime"}, {"----Listar procurado por nome"}, {"----Levantamento da pesquisa"}, {"----Finalizar programa"}, {"----Créditos"}};
    
    setlocale(LC_ALL,""); //FAZER COM QUE RECONHEÇA O IDIOMA PORTUGUÊS (FUNCIONA DE ACORDO COM A LINGUAGEM DO SISTEMA DA MÁQUINA). 

    do{
        opcao = menu_interativo (9 ,40, YELLOW, opcaoSeta, 9, 25, 6);
        
        switch(opcao){
        case 1:
            pais();
        break;

        case 2:
            crime();
        break;

        case 3:
            procurado();
        break;

        case 4:
            mostra_pais();
        break;

        case 5:
            mostra_crime();
        break;

        case 6:
            mostra_procurado();
        break;

        case 7:
            levantamento();
        break;
        
        case 8:
        	logo();
            printf("\n\n\nPrograma encerrado!\n");
            getchar();
            break;
            
        case 9:
        	creditos();
		break;

        default:
            printf("\n");
            printf("Opção inválida, selecione uma dentre as opções oferecidas!\n");
            getchar();
            printf("Pressione enter para continuar!\n");
            getchar();
        break;
        }  
	}while(opcao != 8);
	return 0;
}

void logo(){ //LOGO PADRÃO USADO EM TODAS AS FUNÇÕES.
    system("cls");  
    
    char c;
    FILE *ptr_arquivo;
    ptr_arquivo = fopen("Art.txt", "r");
    
    if(ptr_arquivo == NULL){
    	printf("Arquivo não encontrado!");
	}
	
    c = fgetc(ptr_arquivo);
   	   while(c != EOF){
   		printf("%c", c);
   		c = fgetc(ptr_arquivo);
	}
	
	fclose(ptr_arquivo);
}

void maiusculo_carac(char string[]){ // RECEBE STRINGS DURANTE TODO O TRABALHO PARA TRANSFORMÁ-LAS EM MAIÚSCULAS.
    
	int tamanho, i;
    
    tamanho = strlen(string);

    for(i = 0; i < tamanho; i++){
        string[i] = toupper(string[i]);
    }
}

void pais(){ // FUNÇÃO PARA CADASTRAR O PAÍS DO USUÁRIO, NÃO PERMITINDO PAÍS REPITIDOS.
    FILE* Pais;
    Pais = fopen("Pais.txt", "ab");
    char pais[TAM];
    int cadastrado = 0; //VARIÁVEL BOOLEANA PARA VERIFICAR SE O PAÍS JÁ FOI CADASTRADO OU NÃO.

    if(Pais == NULL){
        printf("\n\n\nProblemas ao abrir o arquivo! \n");
        system("pause");
    } 
	else{
        logo();
        fflush(stdin);
        printf("\n\n\nDigite o país que deseja cadastrar: ");
        gets(pais);

        maiusculo_carac(pais);
            
        cadastrado = busca_pais(pais); //FUNCAO QUE VERIFICA SE O PAÍS JÁ FOI CADASTRADO.

        if(cadastrado == 0){
            fwrite(&pais, sizeof(char) * TAM, 1, Pais); //ESCREVE UMA STRING DO PAÍS DE ATE 100 CARACTERES.
            printf("\nPaís cadastrado com sucesso!\n");
            printf("Pressione enter para continuar . . .\n");
            getchar();
        } 
		else{
            printf("\nPaís já cadastrado\n");
            printf("Pressione enter para continuar . . .\n");
            getchar();
        }   
        fclose(Pais);
    }
}

int busca_pais(char busca[]){ //FUNÇÃO QUE RECEBE A STRING PAÍS E RETORNA 0 SE ELE AINDA NÃO FOI CADASTRADO E 1 SE ELE JÁ FOI CADASTRADO.
    
	int igual = 0;
    char pais[TAM];

    FILE* Pais;
    Pais = fopen("Pais.txt", "rb");

    if(Pais == NULL){
        printf("\n\n\nProblemas ao abrir o arquivo! \n");
        system("pause");
        return 0;
    }
	else{
        while(fread(&pais, sizeof(char)*TAM, 1, Pais) == 1){ //COMPORTAMENTO ANORMAL DA FUNÇÃO SIZEOF, SE COLOCAR MAIS 100 DÁ ERRO.
            if(strcmp(busca, pais) == 0){
                igual = 1;
                break;
            }
        }
        return igual;
        fclose(Pais);
    }
}

void crime(){ // FUNÇÃO PARA CADASTRAR O crime NÃO PERMITINDO CURSOS REPITIDOS.
    
	char crime[100];
    int cadastrado = 0; // VARIÁVEL BOOLEANA PARA VERIFICAR SE O crime JÁ FOI CADASTRADO OU NÃO.
	
	FILE* Crime;
	
    Crime = fopen("Crime.txt", "ab");

    if(Crime == NULL){
        printf("\n\nProblemas ao abrir o arquivo! \n\n");
        system("pause");
    } else{
            logo();
            fflush(stdin);
            printf("\n\n\nDigite o Crime que deseja cadastrar para o Procurado: ");
            gets(crime);
            maiusculo_carac(crime);

            cadastrado = busca_crime(crime); //FUNÇÃO PARA VERIFICAR SE O crime FOI CADASTRADO.

            if(cadastrado == 0){
                fwrite(&crime, sizeof(char)*TAM, 1, Crime);
                printf("\nCrime do procurado cadastrado com sucesso!\n");
                printf("Pressione enter para continuar...\n");
                getchar();
            } else{
                printf("\nCrime já cadastrado!\n");
                printf("Pressione enter para continuar...\n");
                getchar();
            }
        fclose(Crime);
    }
}

int busca_crime(char busca[]){ //FUNÇÃO QUE RECEBE A STRING crime E RETORNA 0 SE ELE AINDA NÃO FOI CADASTRADO E 1 SE ELE JÁ FOI CADASTRADO.
    
	char crime_procurado[TAM];
    int igual = 0;

    FILE* Crime;
    Crime = fopen("Crime.txt", "rb");

    if(Crime == NULL){
        printf("\n\nProblemas ao abrir o arquivo\n\n");
        system("pause");
        return 0;
    } else{
        while(fread(&crime_procurado, sizeof(char)*TAM, 1, Crime) == 1){
            if(strcmp(crime_procurado, busca) == 0){
                igual = 1;
                break;
            }
        }
        return igual;
        fclose(Crime);
    }
}

void procurado(){ //FUNCAO QUE CADASTRA OS DADOS DO crime EM UMA STRUCT NAO PERMITINDO O CADASTRAMENTO DE DADOS INVÁLIDOS.

	FILE* Pessoa;
    PESSOA gnt; //GNT = ABREVIAÇÃO DE GENTE.
    int achei_pais = 0; //VERIFICA SE O PAÍS QUE ESTÃO CADASTRANDO A PESSOA REALMENTE EXISTE.
    int achei_crime = 0; //VERIFICA SE O crime QUE ESTÁ SENDO CADASTRADO REALMENTE EXISTE.
    int validez_data;
    int validar_masculino;
    int validar_feminino;
    int validar_sexo;
    Pessoa = fopen("Pessoa.txt", "ab");

    if(Pessoa == NULL){
        printf("\n\nProblemas ao abrir o arquivo!\n\n");
        system("pause");
    } else{
            logo();
            printf("\n\n\nDigite o nome do Procurado que deseja cadastrar: ");
            fflush(stdin);
            gets(gnt.nome);
            maiusculo_carac(gnt.nome);

 			      printf("Digite o sexo do Procurado (M-Masculino/F-Feminino): ");
            fflush(stdin);
            gets(gnt.sexo);
            maiusculo_carac(gnt.sexo);
            if(strcmp(gnt.sexo, "M") != 0 && strcmp(gnt.sexo, "F") != 0){ //VERIFICA SE O SEXO É VÁLIDO.
                printf("\nSexo inválido, retornando ao menu de opções...\n");
                fflush(stdin);
                getchar();
                return;
            }

            printf("Digite a data de nascimento desse Procurado no formato DD   MM   AAAA: ");
            scanf("%d %d %d", &gnt.aniv.dia, &gnt.aniv.mes, &gnt.aniv.ano);
            fflush(stdin);
            validez_data = valida_data(gnt.aniv.dia, gnt.aniv.mes, gnt.aniv.ano);
            if (validez_data == 0){ //VERIFICA A DATA.
                printf("\nData incorreta!\n");
                printf("Retornando ao menu de opções...\n");
                fflush(stdin);
                getchar();
                return;
            }

            printf("Digite o Crime cometido por esse Procurado: ");
            fflush(stdin);
            gets(gnt.crime_desejado);
            maiusculo_carac(gnt.crime_desejado);
            achei_crime = busca_crime(gnt.crime_desejado);
            if(achei_crime == 0){ //VERIFICA SE O crime JÁ FOI CADASTRADO NO ARQUIVO DE TEXTO crime.
                printf("\nNão foi possível incluir esse Procurado pois esse Crime não foi cadastrado!");
                printf("\nRetornando ao menu de opções...\n");
                fflush(stdin);
                getchar();
                return;
            }

            printf("Digite o País do procurado: ");
            gets(gnt.pais_procurado);
            maiusculo_carac(gnt.pais_procurado);
            achei_pais = busca_pais(gnt.pais_procurado);
            if(achei_pais == 0){ //VERIFICA SE O pais JÁ FOI CADASTRADO NO ARQUIVO pais.
                printf("\nNão foi possível incluir esse Procurado pois esse País não foi cadastrado!");
                printf("\nRetornando ao menu de opções...\n");
                fflush(stdin);
                getchar();
                return;
            }

           
            fwrite(&gnt, sizeof(PESSOA), 1, Pessoa);
            printf("\nProcurado cadastrado com sucesso!\n");
            printf("Retornando ao menu de opções...\n")/
            fflush(stdin);
            getchar();

            fclose(Pessoa);
    }
}

void mostra_procurado(){ //RECEBE O NOME DO procurado E O PESQUISA NO PROGRAMA.
    
	char nome_pesquisa[50];
    int achei = 0;
    FILE* Pessoa;
    PESSOA gente;

    Pessoa = fopen("Pessoa.txt", "rb");


    if(Pessoa == NULL){
        printf("\n\nProblemas na abertura do arquivo, não há Procurado cadastrados! \n\n");
        system("pause");
    } 
	else{
   	    logo();
        fflush(stdin);
        printf("\n\n\nDigite o nome do Procurado que deseja pesquisar: ");
        gets(nome_pesquisa);
        maiusculo_carac(nome_pesquisa);

        while(fread(&gente, sizeof(PESSOA), 1, Pessoa) == 1){ //PERCORRE O ARQUIVO.
            if(strstr(gente.nome, nome_pesquisa) != NULL){ //COMPARA AS DUAS STRINGS PERMITINDO A PROCURA POR NOME.
                printf("\n_________________________________________\n");
                printf("Nome completo: %s\n", gente.nome);
                printf("Sexo: %s\n", gente.sexo);
                printf("Data de nascimento: %d/%d/%d\n", gente.aniv.dia, gente.aniv.mes, gente.aniv.ano);
                printf("Crime cometido: %s\n", gente.crime_desejado);
                printf("País: %s\n", gente.pais_procurado);
                printf("\n_________________________________________\n");
                achei++;
            }
        }

        if(achei == 0){
            printf("\n\n\nProcurado não cadastrado! ");
            system("pause");
        }
            
        fclose(Pessoa);
        
        printf("\nPressione qualquer tecla para continuar...");
        getch();
    }
}

void mostra_pais(){//RECEBE A STRING Pais E LISTA TODAS AS PESSOAS CADASTRADAS NESSE Pais.
    
	char Pais_listar[50];
    int achei = 0;
        
    FILE* Pessoa;
    Pessoa = fopen("Pessoa.txt", "rb");

    PESSOA gente;

    if(Pessoa == NULL){
        printf("\n\nProblemas ao abrir o arquivo, não há País cadastrados! \n\n");
        system("pause");
    }
	else {
        logo();
        fflush(stdin);
        printf("\n\n\nDigite um País para listar os Procurados de acordo com o local: ");
        gets(Pais_listar);
        maiusculo_carac(Pais_listar);

        while(fread(&gente, sizeof(PESSOA), 1, Pessoa) == 1){
        	if(strcmp(Pais_listar, gente.pais_procurado) == 0){
                printf("\n_________________________________________\n");
                printf("Nome completo: %s\n", gente.nome);
                printf("Sexo: %s\n", gente.sexo);
               	printf("Data de nascimento: %d/%d/%d\n", gente.aniv.dia, gente.aniv.mes, gente.aniv.ano);
                printf("Crime cometido: %s\n", gente.crime_desejado);
                printf("País: %s\n", gente.pais_procurado);
                printf("\n_________________________________________\n");
                achei++;
            }
        }
            
		if(achei == 0){
        printf("\nPaís não cadastrado!\n");
        }
            
        fclose(Pessoa);
            
        printf("Pressione enter para continuar...\n");
        getch();
    }
}

void mostra_crime(){ //RECEBE A STRING crime E LISTA TODAS AS PESSOAS QUE VOTARAM NESSE crime.
    
	char crime_listar[50];
    int achei = 0;
        
    FILE* Pessoa;
    Pessoa = fopen("Pessoa.txt", "rb");

    PESSOA gente;

    if(Pessoa == NULL){
        printf("\n\nProblemas ao abrir o arquivo, não há Crimes cadastrados! \n\n");
        system("pause");
    } 
	else{
	    logo();
	    fflush(stdin);
	    printf("\n\n\nDigite um Crime cometido para listar os Procurados que cometeram o mesmo Crime: ");
	    gets(crime_listar);
	    maiusculo_carac(crime_listar);
	
	    while(fread(&gente, sizeof(PESSOA), 1, Pessoa) == 1){
	    	if(strcmp(crime_listar, gente.crime_desejado) == 0){
	        printf("\n_________________________________________\n");
	        printf("Nome completo: %s\n", gente.nome);
	    	printf("Sexo: %s\n", gente.sexo);
	        printf("Data de nascimento: %d/%d/%d\n", gente.aniv.dia, gente.aniv.mes, gente.aniv.ano);
	        printf("Crime cometido: %s\n", gente.crime_desejado);
	        printf("País: %s\n", gente.pais_procurado);
	        printf("_________________________________________\n");
	        achei++;
	        }
	    }
	            
		if(achei == 0){
	    printf("\nCrime não cadastrado!\n");
	    }
	            
	    fclose(Pessoa);
	            
	    printf("Pressione enter para continuar...\n");
	    getch();
    }
}

int valida_data(int dia, int mes, int ano){ // VALIDADOR DE DATA, RETORNA 1 CASO A DATA ESTEJA VALIDA OU RETORNA 0 CASO A DATA ESTEJA INVÁLIDA.
    
	int valido = 0;
        if(dia >= 1 && dia <= 31){
            if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
                if(ano >= 1900 && ano <= 2025){
                    valido = 1;
                }
            }
        }
        
        if(dia >= 1 && dia <= 30){
            if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
                if(ano >= 1900 && ano <= 2025){
                    valido = 1;
                }
            }
        }
        
        if(dia >= 1 && dia <= 28){
            if(mes == 2){
                if((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1900 && ano <= 2100)){
                    valido = 1;
                }
            }
        }
        
        return valido;
}

void levantamento(){ //CRIA UM RELATÓRIO MOSTRANDO NO PROGRAMA A PARCELA DE CANDIDADOS QUE PARTICIPARAM VOTANDO
    
	float cont_masculino = 0, cont_feminino = 0; //VARIAVEIS PARA CONTAR HOMENS E MULHERES.
    int total = 0; //VARIAVEIS PARA CONTAR O TOTAL DE procuradoS.
	float percentual_masculino, percentual_feminino; //ARMAZENA A PORCENTAGEM DE HOMENS E MULHERRES.
    int dia_atual, mes_atual, ano_atual; //RECEBE A DATA ATUAL DO USUÁRIO QUE ESTÁ FAZENDO O RELATÓRIO DEMOGRÁFICO.
    int dia_pessoa[TAM], mes_pessoa[TAM], ano_pessoa[TAM]; //RECEBE A DATA DA PESSOA DENTRO DA STRUCT.
    int data_valida; //VERIFICA SE A DATA QUE O USUARIO DIGITOU É VALIDA.
    int i = 0, k = 0, j; //VARIAVEIS AUXILIARES PARA LAÇOS DE REPETIÇÃO.
    float idade_pessoa[TAM]; //RECEBE A IDADE DA PESSOA DENTRO DA STRUCT PARA CALCULAR O PERCENTUAL.
    float cont_grupo_1 = 0, cont_grupo_2 = 0, cont_grupo_3 = 0, cont_grupo_4 = 0; //CONTA A QUANTIDADE DE procuradoS SEPARADOS EM 4 GRUPOS PARA FAZER A PORCENTAGEM DELES.
    float percentual_grupo_1, percentual_grupo_2, percentual_grupo_3, percentual_grupo_4; //CALCULA O PERCENTUAL DE procuradoS EM CADA GRUPO.
    
    ANIVERSARIO aniversario[TAM]; //NOVA STRUCT EM FORMA DE ESTRUTURA HOMOGÊNEA AUXILIAR PARA ARMAZENAR AS DATAS DAS PESSOAS DENTRO DA STRUCT.
    FILE* Pessoa;
    Pessoa = fopen("Pessoa.txt", "rb");

    PESSOA gente;
    fflush(stdin);

    if(Pessoa == NULL){
        printf("\n\nProblemas ao abrir o arquivo! \n\n");
        system("pause");
    } else{
        while(fread(&gente, sizeof(PESSOA), 1, Pessoa) == 1){ //PERCORRE TODO O ARQUIVO.
            aniversario[k].birthday.dia = gente.aniv.dia; //GRAVA O DIA NA STRUCT AUXILIAR QUE É UM VETOR.
            aniversario[k].birthday.mes = gente.aniv.mes; //GRAVA O MES NA STRUCT AUXILIAR QUE É UM VETOR.
            aniversario[k].birthday.ano = gente.aniv.ano; //GRAVA O ANO NA STRUCT AUXILIAR QUE É UM VETOR.
            k++; //VARIAVEL AUXILIAR PARA GRAVAR EM CADA POSIÇÃO DO VETOR DE STRUCT.
            if(strcmp(gente.sexo, "M") == 0){
                cont_masculino = cont_masculino + 1; //CONTAR OS HOMENS.
            }

            if(strcmp(gente.sexo, "F") == 0){
                cont_feminino = cont_feminino + 1; //CONTAR AS MULHERES.
            }
        }
        total = cont_feminino + cont_masculino; //CONTAR O TOTAL (SOMA DE HOMENS E MULHERES).

        if(total == 0){ //SE FOR IGUAL A 0 SIGNIFICA QUE NENHUMA PESSOA FOI CADASTRADA E VOLTA AO MENU DE OPÇÕES.
            printf("\nNenhum Procurado cadastrado para fazer relatório!");
            printf("\nRetornando ao menu de opções . . .");
            getchar();
            return;
        }
		logo();
        printf("\n\n\nInsira a data de hoje para prosseguir com o relatório: ");
        scanf("%i %i %i", &dia_atual, &mes_atual, &ano_atual);
        data_valida = valida_data(dia_atual, mes_atual, ano_atual); //VERIFICA SE A DATA RECEBIDA PELO USUÁRIO É VÁLIDA.

        if(data_valida == 0){ //SE FOR INVÁLIDA AQUI O RELATÓRIO SERÁ INTERROMPIDO.
            printf("\nPor favor, insira uma data válida!");
            printf("\nRetornando ao menu de opções...");
            getchar();
            getchar();
            return;
        }

        percentual_masculino = (cont_masculino / total) * 100; //CÁLCULO DO PERCENTUAL MASCULINO.
        percentual_feminino = (cont_feminino / total) * 100; //CÁLCULO DO PERCENTUAL FEMININO.

        for (j = 0; j < total; j++){
            idade_pessoa[j] = 2019 - aniversario[j].birthday.ano; //VERIFICA QUANTOS ANOS CADA PESSOA TEM.
        }
        for(j = 0; j < total; j++){
            if(idade_pessoa[j] >= 15 && idade_pessoa[j] <= 20){ //CONTA QUANTAS PESSOAS TEM ENTRE 15 E 20 ANOS.
                cont_grupo_1++;
            }
            if(idade_pessoa[j] >= 21 && idade_pessoa[j] <= 25){ //CONTA QUANTAS PESSOAS TEM ENTRE 21 E 25 ANOS.
                cont_grupo_2++;
            }
            if(idade_pessoa[j] >= 26 && idade_pessoa[j] <= 30){ //CONTA QUANTAS PESSOAS TEM ENTRE 26 E 30 ANOS.
                cont_grupo_3++;
            }
            if(idade_pessoa[j] >= 30){ //CONTA QUANTAS PESSOAS SÃO MAIORES DE 30 ANOS.
                cont_grupo_4++;
            }
        }
        //CALCULA O PERCENTUAL DE PESSOA DE CADA GRUPO.
        percentual_grupo_1 = (cont_grupo_1 / total) * 100;
        percentual_grupo_2 = (cont_grupo_2 / total) * 100;
        percentual_grupo_3 = (cont_grupo_3 / total) * 100;
        percentual_grupo_4 = (cont_grupo_4 / total) * 100;

        //INFORMA OS DADOS OBTIDOS POR MEIO DESSE RELATÓRIO.
        logo();
        printf("\n\n\nData do relatório: %i/%i/%i \n",dia_atual, mes_atual, ano_atual);
        printf("\nTotal de %i Procurados(s) registrados.\n", total);
        printf("\nDo total de Procurados registrados: ");
        printf("\n\t%.2f%% têm idade entre 15 e 20 anos.", percentual_grupo_1);
        printf("\n\t%.2f%% têm idade entre 21 e 25 anos.", percentual_grupo_2);
        printf("\n\t%.2f%% têm idade entre 26 e 30 anos.", percentual_grupo_3);
        printf("\n\t%.2f%% são maiores de 30 anos.", percentual_grupo_4);

        printf("\n\nO percentual de homens que são procurados pela interpol é de %.2f%%\n", percentual_masculino);
        printf("O percentual de mulheres que são procurados pela interpol é de %.2f%%\n", percentual_feminino);
        getchar();
		getchar();
    }
}

int creditos(){
	
	logo();
	
	printf("\n\n------------------------");  
	printf("-----------------\n\n");      
	system("PAUSE");
	return 0;
}

int menu_interativo (int tam, int d,int cor, char  opcao[d][d] ,int l_i,int l_f, int c){ //FUNÇÃO PARA MUDANÇA DE COR E USO DE SETAS.
	
	int tecla,  i, op = 1, l = l_i, caracter;
	FILE *arq;
	
	clrscr();
	_setcursortype(_NOCURSOR); /* apaga o cusor na tela */
	textcolor(cor);
	textbackground(BLACK);
	logo();
	
	do
	{
	
		for (i = 0; i < tam; ++i)
		{
			if (l == l_i+(i*2))
				textcolor(cor);
			cputsxy(c , l_i+(i*2), opcao[i]);
			textcolor(RED);
		}     
		tecla = getch();
		
		switch(tecla)
		{
			case UP: 
				l-=2;
				op--;
				if (l < l_i)
				{
				   op = 1;
					l = l_i;
				}
				break;
			case DOWN: 
				l+=2;
				op++;
				if (l > l_f)
				{
					op = tam;
					l = l_f;
				}
				break;
		}
	}while (tecla != ENTER);
	_setcursortype(_NORMALCURSOR); /* volta o cursor normal */
	return op;
}
