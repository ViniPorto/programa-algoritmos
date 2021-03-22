#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#define NMAX_LIVROS 10
#define NMAX_VENDAS 20

// Trabalho de algoritmos e lógica de programaçao
// academicos: Vinicius Porto, andrei Fransozi e alisson Garçoa

int pos_lv, pos_vd = 0; //VARIÁVEIS GLOBAIS PARA GERENCIAR AS POSIÇÕES DE INSERÇÃO NO ARQUIVO .TXT

int cod_venda; //VARIÁVEL PARA CONTROLAR OS NOVOS CÓDIGOS DE VENDAS
/* DECLARAÇÃO DAS STRUCTS */

typedef struct { //STRUCT PARA REGISTRO DE VENDAS
    int codVenda;
    int codLivro;
    char data[11];
    int qt;
    float valorTotal;
} VENDA;

typedef struct { //STRUCT PARA CADASTRO DE LIVROS
    int codigo;
    char titulo[100];
    float preco;
    VENDA registro_de_venda[NMAX_VENDAS];
} LIVRO;
LIVRO livro[NMAX_LIVROS];

// struct tm *tempo; //PARA O CASO DE SALVAR AUTOMÁTICAMENTE A DATA NA HORA DO REGISTRO DA VENDA

/* DECLARAÇÃO DAS FUNÇÕES */

void cadastrarLivro();

void mostrarLivros();

void criarMenu();

void inicializarCadastros();

int verificarLivrosCheio();

void excluirLivro();

int mostrarLivros2();

void consultar_dados_livro_pelo_titulo();

void registrarVenda();

void mostrarVendas();

void mostrarVendasPorTitulo();

void mostrarVendasPorPeriodo();

void exportarDados();

void importarDados();


/* DECLARAÇÃO DA FUNÇÃO MAIN() */

int main(void){
    setlocale(LC_ALL, "Portuguese");
    inicializarCadastros();
    criarMenu();
    //carregando();
    return 0;
}

/* DESENVOLVIMENTO DAS FUNÇÕES */

void inicializarCadastros(){                                  //O PARÂMETRO PARA SABER SE UM LIVRO OU VENDA NÃO EXISTEM É SABER SE ESTÁ TUDO
    for(int i = 0; i<NMAX_LIVROS; i++){                       //SETADO COMO 0 OU NULL
        livro[i].codigo = 0;
        livro[i].preco = 0;
        strcpy(livro[i].titulo, "NULL");
        for(int j = 0; j<NMAX_VENDAS; j++){
            livro[i].registro_de_venda[j].codVenda = 0;
            livro[i].registro_de_venda[j].codLivro = 0;
            strcpy(livro[i].registro_de_venda[j].data, "NULL");
            livro[i].registro_de_venda[j].qt = 0;
            livro[i].registro_de_venda[j].valorTotal = 0;
        }
    }
}

void criarMenu(){
    int escolhaMenu, escolhaConsulta;
    do{
        system("cls");
        printf("+----------------------------------------------------------------------------------------+");
        printf("\n| (1) - Cadastrar livro                                                                  |");
        printf("\n| (2) - Registrar venda                                                                  |");
        printf("\n| (3) - Excluir livro                                                                    |");
        printf("\n| (4) - Consultar dados                                                                  |");
        printf("\n| (5) - Importar dados                                                                   |");
        printf("\n| (6) - Exportar dados                                                                   |");
        printf("\n| (7) - Sair                                                                             |");
        printf("\n+----------------------------------------------------------------------------------------+\n\n");
        scanf("%d", &escolhaMenu);
        switch(escolhaMenu){
            case 1:
                cadastrarLivro();
                system("cls");
                break;
            case 2:
                registrarVenda();
                break;
            case 3:
                excluirLivro();
                system("cls");
                break;
            case 4:
                system("cls");
                printf("+----------------------------------------------------------------------------------------+\n");
                printf("| (1) - Mostrar livros cadastrados                                                       |\n");
                printf("| (2) - Consultador dados de livros pelo título                                          |\n");
                printf("| (3) - Consultar dados de venda por título do livro                                     |\n");
                printf("| (4) - Consultar dados de vendas por período                                            |\n");
                printf("| (5) - Consultar dados de todas as vendas                                               |\n");
                printf("| (6) - Voltar ao menu                                                                   |\n");
                printf("+----------------------------------------------------------------------------------------+\n\n");
                scanf("%d", &escolhaConsulta);
                if(escolhaConsulta == 1){
                    mostrarLivros();
                    break;
                }
                if(escolhaConsulta == 2){
                    consultar_dados_livro_pelo_titulo();
                    break;
                }
                if(escolhaConsulta == 3){
                    mostrarVendasPorTitulo();
                    break;
                }
                if(escolhaConsulta == 4){
                    mostrarVendasPorPeriodo();
                    break;
                }
                if(escolhaConsulta == 5){
                    mostrarVendas();
                    break;
                }
                if(escolhaConsulta == 6){
                    break;
                }
                if(escolhaConsulta > 6){
                    system("cls");
                    printf("+----------------------------------------------------------------------------------------+\n");
                    printf("|Escolha uma opção válida!                                                               |\n");
                    printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
                    printf("+----------------------------------------------------------------------------------------+\n");
                    fflush(stdin);         //LIMPA O BUFFER PARA O GETS() NÃO CAPTURAR "LIXO"
                    getchar();
                    break;
                }
            case 5:                        //-> DESENVOLVER GRAVAÇÃO case(5) EM ARQUIVO E LEITURA case(6)
                importarDados();
                break;                   //-> DECLARAR UMA FUNÇÃO ACIMA DA MAIN() E DESENVOLVER NO FINAL COMO FIZ COM TODAS!
            case 6:
                exportarDados();                        //-> AO REQUISITAR PARA SALVAR EM ARQUIVO VERIFICAR SE O ARQUIVO ESTÁ VAZIO E PEDIR AO USUÁRIO
                break;                     //-> SE QUER SOBRESCREVER OS DADOS OU ADICIONAR MAIS LIVROS AO ARQUIVO
                                           //-> NO CASO DE LEITURA SEMPRE CADASTRAR COMO NOVOS LIVROS/VENDAS AS INFORMAÇÕES IMPORTADAS
                                           //-> CUIDADO QUE O SÓ REGISTRA VENDA SE O LIVRO[I].REGISTRO_DE_VENDA[J].CODVENDA EXISTE

            case 7:
                exit(1);
        }

    }while(1);
}

int verificarLivrosCheio(){                    //SE HOUVER UMA POSIÇÃO DE VETOR DE LIVRO[I].CODIGO == 0 SIGNIFICA QUE ESTÁ VAGO, PORTANTO NÃO ESTÁ CHEIO
    for(int i = 0; i<NMAX_LIVROS; i++){        //SE O FOR TERMINAR SIGNIFICA QUE NÃO ENCONTROU VETOR DE LIVRO[I].CODIGO == 0, OU SEJA, ESTÁ CHEIO
        if(livro[i].codigo == 0){
            return 0;
        }
    }
    return 1;
}

void cadastrarLivro(){
    system("cls");
    int quantidade_alunos, i, capacidade;
    capacidade = verificarLivrosCheio();
    if(capacidade == 1){
        system("cls");
        printf("+----------------------------------------------------------------------------------------+\n");
        printf("|Acervo na capacidade máxima, exclua livros para adicionar mais!                         |\n");
        printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
        printf("+----------------------------------------------------------------------------------------+\n");
        fflush(stdin);
        getchar();
        return;
    }
    printf("Cadastrar quantos livros?\n");
    scanf("%d", &quantidade_alunos);
    system("cls");
    for(i = 0; i<quantidade_alunos; i++){
        if(i > NMAX_LIVROS){               //NMAX_LIVROS INDICA O FINAL DO VETOR LIVRO[NMAX_LIVROS], OU SEJA, A CAPACIDADE DO ACERVO
            system("cls");
            printf("+----------------------------------------------------------------------------------------+\n");
            printf("|Acervo na capacidade máxima, exclua livros para adicionar mais!                         |\n");
            printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
            printf("+----------------------------------------------------------------------------------------+\n");
            fflush(stdin);
            getchar();
            break;
        }
        if(livro[i].codigo != 0){                                //COMO TODOS FORAM INICIALIZADOS COM 0, NÃO SER 0 SIGNIFICA QUE JÁ TEM UM LIVRO ALOCADO NESSA POSIÇÃO DO VETOR
            quantidade_alunos = quantidade_alunos + 1;
            continue;                                            //PARA AS INSTRUÇÕES E SEGUE PARA A PRÓXIMA INTERAÇÃO DO LAÇO DE REPETIÇÃO
        }
        if(livro[i].codigo == 0){                                 //COMO TODOS FORAM INICIALIZADOS COM 0, ENTÃO TER UM VALOR 0 SIGNIFICA QUE ESTA POSIÇÃO DO VETOR ESTÁ LIVRE

            fflush(stdin);
            printf("\nCódigo do livro(diferente de 0): ");
            scanf("%d", &livro[i].codigo);
            fflush(stdin);
            printf("\n\nNome do livro: ");
            gets(livro[i].titulo);
            printf("\n\nPreço do livro: ");
            scanf("%f", &livro[i].preco);
            system("cls");
        }
    }

}

void mostrarLivros(){
    system("cls");
    int i;
    for(i = 0; i <= NMAX_LIVROS; i++){      //VERIFICA EM QUAL POSIÇÃO HÁ ALGO ALOCADO, SE ENCONTRAR UM CÓDIGO DE LIVRO DIFERENTE DE 0 VAI PARAR
        if(livro[i].codigo != 0){           //O LAÇO, AÍ O VALOR DE "I" É ANALISADO. SE FOR MAIOR QUE O NÚMERO MÁXIMO DE LIVROS SIGNIFICA QUE
            break;                          //QUE NÃO TEM LIVROS CADASTRADOS JÁ QUE NADA ACIONOU O "BREAK". SE FOR MENOR QUE O NÚMERO MÁXIMO DE
        }                                   //LIVROS ENTÃO SIGNIFICA QUE ALGO ACIONOU O "BREAK", OU SEJA, HÁ LIVROS CADASTRADOS
    }
    if(i > NMAX_LIVROS){
        printf("+----------------------------------------------------------------------------------------+\n");
        printf("|Não há livros cadastrados                                                               |\n");
        printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
        printf("+----------------------------------------------------------------------------------------+\n");
    }
    if(i < NMAX_LIVROS){
        printf("             LIVROS CADASTRADOS            \n");
        for(i = 0; i < NMAX_LIVROS; i++){
            if(livro[i].codigo == 0){        //SÓ RODA AS INSTRUÇÕES SE O CÓDIGO DO LIVRO FOR DIFERENTE DE 0
                continue;
            }
            printf("+-----------------------------------------+\n");
            printf("Código do livro...: %d\n", livro[i].codigo);
            printf("Título do livro...: %s\n", livro[i].titulo);
            printf("Preço do livro....: R$%.2f\n", livro[i].preco);
            printf("+-----------------------------------------+\n");
        }
        printf("+-----------------------------------------+\n");
        printf("|Pressione uma tecla para voltar ao menu! |\n");
        printf("+-----------------------------------------+\n\n\n");
    }
    fflush(stdin);
    getchar();
}

int mostrarLivros2(){
    system("cls");
    int i;
    for(i = 0; i <= NMAX_LIVROS; i++){
        if(livro[i].codigo != 0){
            break;
        }
    }
    if(i > NMAX_LIVROS){
        printf("+----------------------------------------------------------------------------------------+\n");
        printf("|Não há livros cadastrados                                                               |\n");
        printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
        printf("+----------------------------------------------------------------------------------------+\n");
        fflush(stdin);
        getchar();
        return 0;
    }
    if(i < NMAX_LIVROS){
        printf("             LIVROS CADASTRADOS            \n");
        for(i = 0; i < NMAX_LIVROS; i++){
            if(livro[i].codigo == 0){
                continue;
            }
            printf("+-----------------------------------------+\n");
            printf("Código do livro...: %d\n", livro[i].codigo);
            printf("Título do livro...: %s\n", livro[i].titulo);
            printf("Preço do livro....: R$%.2f\n", livro[i].preco);
            printf("+-----------------------------------------+\n");
        }
    }
    return 1;
}

void excluirLivro(){
    system("cls");
    int i, j, codigo_a_excluir, confirmacao_exclusao, resultado_mostrarLivros2;
    resultado_mostrarLivros2 = mostrarLivros2();
    if(resultado_mostrarLivros2 == 0){
        return;
    }
    printf("\nDigite o código do livro a ser excluido: ");
    scanf("%d", &codigo_a_excluir);
    for(i = 0; i<NMAX_LIVROS; i++){
        if(livro[i].codigo == codigo_a_excluir){
            system("cls");
            printf("\nA exclusão do livro resultará na exclusão de registros de vendas do mesmo. Continuar? [sim(1) - não(2)]\n");
            scanf("%d", &confirmacao_exclusao);
            if(confirmacao_exclusao != 1){
                system("cls");
                printf("+----------------------------------------------------------------------------------------+\n");
                printf("|Exclusão cancelada!                                                                     |\n");
                printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
                printf("+----------------------------------------------------------------------------------------+\n\n\n");
                fflush(stdin);
                getchar();
                return;
            }
            livro[i].codigo = 0;
            livro[i].preco = 0;
            strcpy(livro[i].titulo, "NULL");
            for(j = 0; j<NMAX_VENDAS; j++){
                livro[i].registro_de_venda[j].codVenda = 0;          //A EXCLUSÃO DE UM LIVRO NADA MAIS É DO QUE SETAR TUDO EM DEFAULT
                livro[i].registro_de_venda[j].codLivro = 0;          //0 E NULL
                strcpy(livro[i].registro_de_venda[j].data, "NULL");
                livro[i].registro_de_venda[j].qt = 0;
                livro[i].registro_de_venda[j].valorTotal = 0;
            }
            system("cls");
            printf("+----------------------------------------------------------------------------------------+\n");
            printf("|Livro excluido com sucesso!                                                             |\n");
            printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
            printf("+----------------------------------------------------------------------------------------+\n");
            fflush(stdin);
            getchar();
            return;
            }
    }
    printf("+----------------------------------------------------------------------------------------+\n");
    printf("|Livro não encontrado!                                                                   |\n");
    printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
    printf("+----------------------------------------------------------------------------------------+\n");
}

void consultar_dados_livro_pelo_titulo(){
    system("cls");
    int i;
    char titulo_livro_a_pesquisar[100];
    printf("Digite o título do livro a pesquisar: ");
    fflush(stdin);
    gets(titulo_livro_a_pesquisar);
    for(i = 0; i < NMAX_LIVROS; i++){
        if(strcmp(livro[i].titulo, titulo_livro_a_pesquisar) == 0){
            system("cls");
            printf("             LIVRO ENCONTRADO!             \n");
            printf("+-----------------------------------------+\n");
            printf("Código do livro...: %d\n", livro[i].codigo);
            printf("Título do livro...: %s\n", livro[i].titulo);
            printf("Preço do livro....: R$%.2f\n", livro[i].preco);
            printf("+-----------------------------------------+\n");
            printf("+-----------------------------------------+\n");
            printf("|Pressione uma tecla para voltar ao menu! |\n");
            printf("+-----------------------------------------+\n\n\n");
            fflush(stdin);
            getchar();
            return;

        }
    }
    system("cls");
    printf("+----------------------------------------------------------------------------------------+\n");
    printf("|Livro não encontrado!                                                                   |\n");
    printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
    printf("+----------------------------------------------------------------------------------------+\n");
    fflush(stdin);
    getchar();
}

void registrarVenda(){
    /* char dataHora[100];  --\
       time_t agora;        ----> PARA O CASO DE SALVAR AUTOMÁTICAMENTE A DATA NA HORA DO REGISTRO DE VENDA
       agora = time(NULL);  --/
    */

    system("cls");
    int i = 0, j = 0, k = 0, aux_cod_vendas = 0, codigo_livro_a_ser_vendido = 0, posicao_registro_venda = 0;
    int resultado_mostrarLivros2;
    resultado_mostrarLivros2 = (int)mostrarLivros2();
    if(resultado_mostrarLivros2 == 0){
        return;
    }
    fflush(stdin);
    printf("\nDigite o código do livro a ser vendido: ");
    scanf("%d", &codigo_livro_a_ser_vendido);
    for(i = 0; i < NMAX_LIVROS; i++){
        if(livro[i].codigo == codigo_livro_a_ser_vendido){
            system("cls");
            aux_cod_vendas = 0;
            for(j = 0; j < NMAX_LIVROS; j++){         //PARA GERAR AUTOMÁTICAMENTE UM NOVO CÓDIGO DE VENDA SEMPRE CRESCENTE
                for(k = 0; k < NMAX_VENDAS; k++){
                    if((livro[j].registro_de_venda[k].codVenda > 0) && (livro[j].registro_de_venda[k].codVenda > aux_cod_vendas)){
                        aux_cod_vendas = livro[j].registro_de_venda[k].codVenda;
                    }
                }
            }
            for(j = 0; j < NMAX_VENDAS; j++){
                if(livro[i].registro_de_venda[j].codVenda == 0){
                    posicao_registro_venda = j;
                    break;
                }
            }
            if(j > NMAX_VENDAS && posicao_registro_venda != j){
                system("cls");
                printf("+----------------------------------------------------------------------------------------+\n");
                printf("|Limite de vendas para este livro alcançado!                                             |\n");
                printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
                printf("+----------------------------------------------------------------------------------------+\n");
                fflush(stdin);
                getchar();
                return;
            }
            livro[i].registro_de_venda[posicao_registro_venda].codLivro = livro[i].codigo;
            livro[i].registro_de_venda[posicao_registro_venda].codVenda = aux_cod_vendas + 1;

            /* strftime(dataHora, sizeof(dataHora), "%d/%m/%Y", localtime(&agora)); -> para o caso de salvar automáticamente a data na hora do registro de venda
               strcpy(livro[i].registro_de_venda.data, dataHora);     -> PARA O CASO DE SALVAR AUTOMÁTICAMENTE A DATA NA HORA DO REGISTRO DA VENDA */

            printf("\nDigite a quantidade a ser vendida: ");
            scanf("%d", &livro[i].registro_de_venda[posicao_registro_venda].qt);
            printf("\nDigite a data de venda(xx-xx-xxxx): ");
            fflush(stdin);
            gets(livro[i].registro_de_venda[posicao_registro_venda].data);
            livro[i].registro_de_venda[posicao_registro_venda].valorTotal = livro[i].preco * livro[i].registro_de_venda[posicao_registro_venda].qt;

            system("cls");

            printf("        VENDA REGISTRADA COM SUCESSO       \n");
            printf("+-----------------------------------------+\n");
            printf("Código da venda: %d                        \n", livro[i].registro_de_venda[posicao_registro_venda].codVenda);
            printf("Código do livro: %d                        \n", livro[i].codigo);
            printf("Quantidade: %d                             \n", livro[i].registro_de_venda[posicao_registro_venda].qt);
            printf("Data da venda: %s                          \n", livro[i].registro_de_venda[posicao_registro_venda].data);
            printf("Valor total: R$%.2f                        \n", livro[i].registro_de_venda[posicao_registro_venda].valorTotal);
            printf("+-----------------------------------------+\n");
            printf("+-----------------------------------------+\n");
            printf("|Pressione uma tecla para voltar ao menu! |\n");
            printf("+-----------------------------------------+\n\n\n");
            fflush(stdin);
            getchar();
            return;

        }
    }
    system("cls");
    printf("+----------------------------------------------------------------------------------------+\n");
    printf("|Livro não encontrado!                                                                   |\n");
    printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
    printf("+----------------------------------------------------------------------------------------+\n");
    fflush(stdin);
    getchar();
}

void mostrarVendas(){
    system("cls");
    int i, j, break_true = 0;
    for(i = 0; i <= NMAX_LIVROS; i++){
        for(j = 0; j < NMAX_VENDAS; j++){
            if(livro[i].registro_de_venda[j].codVenda > 0){
                break_true = 1;
                break;
            }
        }
        if(break_true == 1){
            break;
        }
    }
    if(i > NMAX_LIVROS){
        printf("+----------------------------------------------------------------------------------------+\n");
        printf("|Não há vendas registradas!                                                              |\n");
        printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
        printf("+----------------------------------------------------------------------------------------+\n\n\n");
    }
    if(i < NMAX_LIVROS){
        printf("             VENDAS REGISTRADAS            \n");
        for(i = 0; i < NMAX_LIVROS; i++){
            for(j = 0; j < NMAX_VENDAS; j++){
                if(livro[i].registro_de_venda[j].codVenda == 0){
                    continue;
                }
                printf("+-----------------------------------------+\n");
                printf("Código da venda: %d                        \n", livro[i].registro_de_venda[j].codVenda);
                printf("Código do livro: %d                        \n", livro[i].codigo);
                printf("Quantidade: %d                             \n", livro[i].registro_de_venda[j].qt);
                printf("Data da venda: %s                          \n", livro[i].registro_de_venda[j].data);
                printf("Valor total: R$%.2f                        \n", livro[i].registro_de_venda[j].valorTotal);
                printf("+-----------------------------------------+\n");
            }
        }
        printf("+-----------------------------------------+\n");
        printf("|Pressione uma tecla para voltar ao menu! |\n");
        printf("+-----------------------------------------+\n\n\n");
    }
    fflush(stdin);
    getchar();
}

void mostrarVendasPorTitulo(){
    system("cls");
    int livro_encontrado_primeira_interacao = 0, i = 0, j = 0, break_true = 0;
    char titulo_buscar[100];
    for(i = 0; i <= NMAX_LIVROS; i++){
        for(j = 0; j < NMAX_VENDAS; j++){
            if(livro[i].registro_de_venda[j].codVenda > 0){
                break_true = 1;
                break;
            }
        }
        if(break_true == 1){
            break;
        }
    }
    break_true = 0;
    if(i > NMAX_LIVROS){
        printf("+----------------------------------------------------------------------------------------+\n");
        printf("|Não há vendas registradas!                                                              |\n");
        printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
        printf("+----------------------------------------------------------------------------------------+\n\n\n");
    }
    if(i < NMAX_LIVROS){
        printf("\nDigite o título do livro vendido: ");
        fflush(stdin);
        gets(titulo_buscar);
        system("cls");
        for(i = 0; i <= NMAX_LIVROS; i++){
            for(j = 0; j < NMAX_VENDAS; j++){
                if((strcmp(livro[i].titulo, titulo_buscar) == 0) && livro[i].registro_de_venda[j].codVenda != 0){
                    break_true = 1;
                    break;
                }
            }
            if(break_true == 1){
                    break;
            }
        }
        if(i > NMAX_LIVROS){
        printf("+----------------------------------------------------------------------------------------+\n");
        printf("|Venda não encontrada!                                                                   |\n");
        printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
        printf("+----------------------------------------------------------------------------------------+\n\n\n");
        fflush(stdin);
        getchar();
        return;
        }
        for(i = 0; i < NMAX_LIVROS; i++){
            for(j = 0; j < NMAX_VENDAS; j++){
                if((strcmp(livro[i].titulo, titulo_buscar) == 0) && livro[i].registro_de_venda[j].codVenda != 0){
                    if(livro_encontrado_primeira_interacao == 0){
                        printf("           VENDA(S) ENCONTRADA(S)!         \n");
                    }
                    printf("+-----------------------------------------+\n");
                    printf("Código da venda: %d                        \n", livro[i].registro_de_venda[j].codVenda);
                    printf("Código do livro: %d                        \n", livro[i].codigo);
                    printf("Quantidade: %d                             \n", livro[i].registro_de_venda[j].qt);
                    printf("Data da venda: %s                          \n", livro[i].registro_de_venda[j].data);
                    printf("Valor total: R$%.2f                        \n", livro[i].registro_de_venda[j].valorTotal);
                    printf("+-----------------------------------------+\n");
                    livro_encontrado_primeira_interacao++;
                    }
                }
            }
        }
    printf("+-----------------------------------------+\n");
    printf("|Pressione uma tecla para voltar ao menu! |\n");
    printf("+-----------------------------------------+\n\n\n");
    fflush(stdin);
    getchar();
}

void mostrarVendasPorPeriodo(){
    system("cls");
    int venda_encontrada_primeira_interacao = 0, i = 0, j = 0, break_true = 0;
    float somaValor = 0;
    char dataInformada[100];
    for(i = 0; i <= NMAX_LIVROS; i++){
        for(j = 0; j < NMAX_VENDAS; j++){
            if(livro[i].registro_de_venda[j].codVenda > 0){
                break_true = 1;
                break;
            }
        }
        if(break_true == 1){
            break;
        }
    }
    break_true = 0;
    if(i > NMAX_LIVROS){
        printf("+----------------------------------------------------------------------------------------+\n");
        printf("|Não há vendas registradas!                                                              |\n");
        printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
        printf("+----------------------------------------------------------------------------------------+\n\n\n");
        fflush(stdin);
        getchar();
        return;
    }
    if(i < NMAX_LIVROS){
        printf("\nDigite a data(xx-xx-xxxx): ");
        fflush(stdin);
        gets(dataInformada);
        system("cls");



        for(i = 0; i <= NMAX_LIVROS; i++){
            for(j = 0; j < NMAX_VENDAS; j++){
                if(strcmp(livro[i].registro_de_venda[j].data, dataInformada) == 0){
                    break_true = 1;
                    break;
                }
            }
            if(break_true == 1){
                    break;
            }
        }
        if(i > NMAX_LIVROS){
        printf("+----------------------------------------------------------------------------------------+\n");
        printf("|Não há vendas no período informado!                                                     |\n");
        printf("|Pressione uma tecla para voltar ao menu!                                                |\n");
        printf("+----------------------------------------------------------------------------------------+\n\n\n");
        fflush(stdin);
        getchar();
        return;
        }
        for(i = 0; i < NMAX_LIVROS; i++){
            for(j = 0; j < NMAX_VENDAS; j++){
                if(strcmp(livro[i].registro_de_venda[j].data, dataInformada) == 0){
                    if(venda_encontrada_primeira_interacao == 0){
                        printf("VENDA(S) ENCONTRADA(S) NA DATA %s  \n", dataInformada);
                    }
                    printf("+-----------------------------------------+\n");
                    printf("Código da venda: %d                        \n", livro[i].registro_de_venda[j].codVenda);
                    printf("Código do livro: %d                        \n", livro[i].codigo);
                    printf("Quantidade: %d                             \n", livro[i].registro_de_venda[j].qt);
                    printf("Data da venda: %s                          \n", livro[i].registro_de_venda[j].data);
                    printf("Valor total: R$%.2f                        \n", livro[i].registro_de_venda[j].valorTotal);
                    printf("+-----------------------------------------+\n");
                    venda_encontrada_primeira_interacao = venda_encontrada_primeira_interacao + 1;
                    somaValor = somaValor + livro[i].registro_de_venda[j].valorTotal;
                    }
                }
            }
        }
    printf("\nValor total recebido no dia %s: R$%.2f\n\n", dataInformada, somaValor);
    printf("+-----------------------------------------+\n");
    printf("|Pressione uma tecla para voltar ao menu! |\n");
    printf("+-----------------------------------------+\n\n\n");
    fflush(stdin);
    getchar();
}

void exportarDados(){
    system("cls");
    printf("+---------------------------------------------------------------+\n"
           "|                  EXPORTAR DADOS PARA ARQUIVO                  |\n"
           "+---------------------------------------------------------------+\n");
    printf(">> Abrindo arquivo...\n");
    FILE *arq;
    char nmArq[20];
    strcpy(nmArq, "registro.bin");
    arq = fopen(nmArq, "wb");
    if(arq == NULL){
        printf(">> Erro ao abrir arquivo para gravacao.\n");
    }else{
        int i = 0, j = 0, qtdVendas = 0, qtdLivros = 0;
        //Contagem dos livros

        for(i = 0; i < NMAX_LIVROS; i++){
            if(livro[i].codigo != 0){
                qtdLivros ++;
            }
        }

        fwrite(&qtdLivros, sizeof(int), 1, arq);

        for(i = 0; i < NMAX_LIVROS; i++){
            if(livro[i].codigo != 0){
                printf("%d - %s [%.2f]\n", livro[i].codigo, livro[i].titulo, livro[i].preco);
                fwrite(&livro[i].codigo, sizeof(livro[i].codigo), 1, arq);
                fwrite(&livro[i].titulo, sizeof(livro[i].titulo), 1, arq);
                fwrite(&livro[i].preco, sizeof(livro[i].preco), 1, arq);

                //Contagem das vendas
                qtdVendas = 0;
                for(j = 0; j < NMAX_VENDAS; j++){
                    if(livro[i].registro_de_venda[j].codVenda > 0){
                        qtdVendas++;
                        printf("venda: %d\n", livro[i].registro_de_venda[j].codVenda);
                        printf("data: %s\n", livro[i].registro_de_venda[j].data);
                        printf("valor: %.2f\n", livro[i].registro_de_venda[j].valorTotal);
                    }
                }
                fwrite(&qtdVendas, sizeof(int), 1, arq);

                if(qtdVendas > 0){
                    for(j = 0; j < NMAX_VENDAS; j++){
                        if(livro[i].registro_de_venda[j].codVenda != 0){
                            fwrite(&livro[i].registro_de_venda[j].codVenda, sizeof(livro[i].registro_de_venda[j].codVenda), 1, arq);
                            fwrite(&livro[i].registro_de_venda[j].codLivro, sizeof(livro[i].registro_de_venda[j].codLivro), 1, arq);
                            fwrite(&livro[i].registro_de_venda[j].data, sizeof(livro[i].registro_de_venda[j].data), 1, arq);
                            fwrite(&livro[i].registro_de_venda[j].qt, sizeof(livro[i].registro_de_venda[j].qt), 1, arq);
                            fwrite(&livro[i].registro_de_venda[j].valorTotal, sizeof(livro[i].registro_de_venda[j].valorTotal), 1, arq);
                        }
                    }
                }
            }
        }
    }
    printf(">> Dados exportados!\n");
    fclose(arq);
    printf("+---------------------------------------------------------------+\n"
           "|Precione qualquer tecla para sair                              |\n"
           "+---------------------------------------------------------------+\n"
           ">>>");
    getch();
}

void importarDados(){
    system("cls");
    printf("+---------------------------------------------------------------+\n"
           "|                   IMPORTAR DADOS DE ARQUIVO                   |\n"
           "+---------------------------------------------------------------+\n");
    printf(">> Abrindo arquivo...\n");
    FILE *arq;
    arq = fopen("registro.bin", "rb");
    if(arq == NULL){
        printf("Erro ao abrir arquivo para gravacao.\n");
    }else{
        int i = 0, j = 0, qtdLivros = 0, qtdVendas = 0;

        fread(&qtdLivros ,sizeof(int), 1, arq);
        printf(">> Quantidade de livros no arquivo: %d\n", qtdLivros);

        if(qtdLivros > 0){
            inicializarCadastros();
            for(i = 1; i <= qtdLivros; i++){
                int codL;
                char titulo[100];
                float preco;
                fread(&codL, sizeof(livro[0].codigo), 1, arq);
                fread(&titulo, sizeof(livro[0].titulo), 1, arq);
                fread(&preco, sizeof(livro[0].preco), 1, arq);

                livro[i - 1].codigo = codL;
                strcpy(livro[i - 1].titulo, titulo);
                livro[i - 1].preco = preco;

                //leitura das vendas
                fread(&qtdVendas, sizeof(int), 1, arq);
                if(qtdVendas > 0){
                    int j = 0;
                    for(j = 1; j <= qtdVendas; j++){
                        int codV = 0, codLv = 0, qtd = 0;
                        float total = 0.0f;
                        char data[11];

                        fread(&codV, sizeof(livro[0].registro_de_venda[0].codVenda), 1, arq);
                        fread(&codLv, sizeof(livro[0].registro_de_venda[0].codLivro), 1, arq);
                        fread(&data, sizeof(livro[0].registro_de_venda[0].data), 1, arq);
                        fread(&qtd, sizeof(livro[0].registro_de_venda[0].qt), 1, arq);
                        fread(&total, sizeof(livro[0].registro_de_venda[0].valorTotal), 1, arq);

                        livro[i - 1].registro_de_venda[j - 1].codLivro = codLv;
                        livro[i - 1].registro_de_venda[j - 1].codVenda = codV;
                        livro[i - 1].registro_de_venda[j - 1].qt = qtd;
                        livro[i - 1].registro_de_venda[j - 1].valorTotal = total;
                        strcpy(livro[i - 1].registro_de_venda[j - 1].data, data);
                    }
                }
            }
        }
    }
    fclose(arq);
    printf(">> Dados importados!\n");
    printf("+---------------------------------------------------------------+\n"
           "|Precione qualquer tecla para sair                              |\n"
           "+---------------------------------------------------------------+\n"
           ">>>");
    getch();
}

