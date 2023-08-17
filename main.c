#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "listade.h"

int main()
{
    //Definições dos dados e variaveis
    srand(time(NULL));
    int op,aux,cd,saldoC,saldoP,user,logado,senhaAdm,senhaUser,tentativas=3;
    ListaDE lt,b;
    Conta d,u;

    //Criação dos dados
    criaLista(&lt);
    senhaAdm=102976;
    lerArquivo(&lt);

    //Pagina inicial do sistema(Menu para login)
    do
    {
    system("cls");
    logo();
    user=0;
    printf("Bem vindo ao sistema de banco!\n\nComo gostaria de entrar?\n1.Administrador            2.Cliente\n\n/");
    while(user!=1&&user!=2){
    scanf("%d", &user);}
    system("cls");
    switch (user)
    {
    case 1:
        //Login do admin
        do
        {
            printf("#Administrador\n(Digite 0 para voltar)\n\nDigite a senha de administrador:\n/");
            scanf("%d",&senhaUser);
            system("cls");
            if(senhaUser!=senhaAdm){
                printf("SENHA INCORRETA!\n\n");
                //Script simples anti ataque de força bruta
                tentativas--;
                if(tentativas == 0){
                    system("cls");
                    printf("SEGURANCA ATIVA\nSISTEMA BLOQUEADO");
                    getch();
                    return 0;
                }
                } else {
                logado = 2;
                tentativas=3;
            }
        } while (senhaUser != senhaAdm && senhaUser != 0);
        break;

    case 2:
        //Login do usuario
        do{
        printf("#Cliente\n\nVoce ja possui uma conta no banco?\n1.Sim    2.Nao\n/");
        scanf("%d",&aux);
        system("cls");
        } while (aux!=1&&aux!=2);
        if(aux==1){
            //Login em conta existente
            do{
            printf("#Cliente\n(Digite 0 para voltar)\n\nDigite o numero da sua conta bancaria:\n\n/");
            scanf("%d",&cd);
            //if(cd==0){break;}
            system("cls");
            if(consultaPorCodigo(lt,&u,cd)==CODIGO_INEXISTENTE){
                printf("Conta inexistente!\n\n");
                }
            }while(u.cod != cd&&cd != 0);
            if(u.cod == cd){
                while (senhaUser != u.senha){
                    printf("#Cliente\n\nDigite a senha da sua conta bancaria:\n\n/");
                    scanf("%d",&senhaUser);
                    system("cls");
                    if(senhaUser!=u.senha){
                        printf("SENHA INCORRETA!\n\n");
                        //Script simples anti ataque de força bruta
                        tentativas--;
                        if(tentativas == 0){
                            system("cls");
                            printf("SEGURANCA ATIVA\nSISTEMA BLOQUEADO");
                            getch();
                            return 0;
                        }
                    } else {
                    logado = 1;
                    tentativas=3;
                    }    
                }
            }
        } else {
            //Cadastro do cliente no sistema
            printf("#Cliente\n(Digite 0 para voltar)\n\nVamos criar uma conta\n\nPrecisamos dos seus dados:\nNome: ");
            do{
                u.cod = rand()%100;
            } while (consultaPorCodigo(lt,&d,u.cod)!=CODIGO_INEXISTENTE);
            scanf("%s",&u.usuario);
            if(strcmp(u.usuario,"0")==0){break;}
            printf("\nDeposito inicial: ");
            scanf("%f",&u.saldoC);
            printf("\nSenha(Apenas Numeros | Maior que 0): ");
            do{
                scanf("%d",&u.senha);
            } while (u.senha==0);
            if (incluiNoFim(&lt,u)==FALTOU_MEMORIA){
					 	printf("\n\nOperacao NAO realizada: Faltou Memoria!");
                } else {
					printf("\n\nConta criada com SUCESSO!\n");
                    logado=1;
                    printf("\nPressione uma tecla para continuar");
                    getch();
                    system("cls");
                }
        }
        break;
    
    default:
        break;
    }
    } while (logado != 1&& logado != 2);
    
    do
    {
        if (logado == 1)
        {   
            consultaPorCodigo(lt,&d,u.cod);
            //logo();
            printf("Bem Vindo %s\n\n",u.usuario);
            exibeConta(u);
            printf("Operacoes disponiveis para sua conta:\n\n");
            printf("1. Depositar dinheiro                        6. Mudar senha            \n");    
            printf("2. Retirar dinheiro                          7. Excluir conta          \n");    
            printf("3. Investir na poupanca                      0. Sair                   \n");    
            printf("4. Resgatar da poupanca\n");    
            printf("5. Enviar dinheiro\n\n");
            printf("Operacao: ");    
            scanf("%d", &op);
            system("cls");
        } else if (logado == 2){
            //logo();
            printf("Bem Vindo Administrador\n\n");
            printf("1. Exibir lista de contas                         6. Recuperar um backup            \n");    
            printf("2. Criar uma conta                                7. Gravar um backup               \n");    
            printf("3. Consultar uma conta                            8. Transferencia entre contas     \n");    
            printf("4. Alterar uma conta                              0. Sair                           \n");    
            printf("5. Excluir uma conta\n\n"); 
            printf("Operacao: ");    
            scanf("%d", &op);
            system("cls");
        }

        if (logado == 1)
        {
            switch (op)
            {
            case 1:
                exibeConta(u);
                printf("Operacao selecionada: DEPOSITO\n(Digite 0 para voltar)\n\n");
                printf("Quanto deseja depositar?\n: ");
                scanf("%d",&aux);
                system("cls");
                if(aux==0){break;}
                u.saldoC += aux;
                alteraConta(lt, u, u.cod);
                break;
            
            case 2:
                exibeConta(u);
                printf("Operacao selecionada: SAQUE\n(Digite 0 para voltar)\n\n");
                printf("Quanto deseja retirar?\n: ");
                scanf("%d",&aux);
                system("cls");
                if(aux==0){break;}
                if(u.saldoC < aux){
                    printf("Saldo insuficiente!\n\n");
                } else {
                    u.saldoC -= aux;
                    alteraConta(lt, u, u.cod);
                }
                break;
            
            case 3:
                exibeConta(u);
                printf("Operacao selecionada: INVESTIR\n(Digite 0 para voltar)\n\n");
                printf("Quanto deseja investir na poupanca?\n: ");
                scanf("%d",&aux);
                system("cls");
                if(aux==0){break;}
                if(u.saldoC < aux){
                    printf("Saldo insuficiente!\n\n");
                } else {
                    u.saldoC -= aux;
                    u.saldoP += aux;
                    alteraConta(lt, u, u.cod);
                }
                break;
            
            case 4:
                exibeConta(u);
                printf("Operacao selecionada: RESGATAR\n(Digite 0 para voltar)\n\n");
                printf("Quanto deseja resgatar da poupanca?\n: ");
                scanf("%d",&aux);
                system("cls");
                if(aux==0){break;}
                if(u.saldoP < aux){
                    printf("Saldo insuficiente!");
                } else {
                    u.saldoP -= aux;
                    u.saldoC += aux;
                    alteraConta(lt, u, u.cod);
                }
                break;
            
            case 5:
                exibeConta(u);
                do
                {
                    printf("Operacao selecionada: ENVIAR DINHEIRO\n(Digite 0 para voltar)\n\n");
                    printf("Para qual conta deseja enviar o dinheiro?(cod)\n: ");
                    scanf("%d",&cd);
                    system("cls");
                    if(cd==0){break;}
                    if (consultaPorCodigo(lt,&d,cd)==CODIGO_INEXISTENTE||cd==u.cod){
                        printf("Conta inexistente!\n\n");
                    }
                } while ((consultaPorCodigo(lt,&d,cd)!=SUCESSO)||(cd==u.cod));
                if(cd==0){break;}
                printf("Operacao selecionada: ENVIAR DINHEIRO\n\n");
                printf("Conta selecionada:\n\nConta: %d\nNome: %s\n\n",d.cod,d.usuario);
                printf("Quanto dinheiro deseja enviar?\n: ");
                scanf("%d",&aux);
                system("cls");
                if(u.saldoC < aux){
                    printf("Saldo insuficiente!");
                } else {
                    u.saldoC -= aux;
                    d.saldoC += aux;
                    alteraConta(lt, u, u.cod);
                    alteraConta(lt, d, d.cod);
                }
                break;
            
            case 6:
                exibeConta(u);
                printf("Operacao selecionada: MUDAR SENHA\n(Digite 0 para voltar)\n\n");
                printf("Digite a nova senha\n: ");
                scanf("%d",&aux);
                system("cls");
                if(aux==0){break;}
                u.senha = aux;
                alteraConta(lt, u, u.cod);
                break;
            
            case 7:
                exibeConta(u);
                printf("Operacao selecionada: EXCLUIR CONTA\n(Digite 0 para voltar)\n\n");
                printf("DESEJA MESMO EXCLUIR A SUA CONTA?\n\nCONFIRME DIGITANDO A SENHA DA CONTA\n: ");
                scanf("%d",&aux);
                system("cls");
                if(aux==0){break;}
                if(aux == u.senha){
                    excluiNodo(&lt,&d,u.cod);
                    gravaArquivo(lt);
                    return(0);
                } else {
                    printf("SENHA INCORRETA!\n\n");
                }
                
                break;
            
            default:
                break;
            }
        } else if (logado == 2){
            switch (op)
            {
            case 1:
                exibe(lt);
                break;
            
            case 2:
                printf("Operacao selecionada: Criar conta\n(Digite 0 para voltar)\n\nDados da conta:\n\n");
                do{
                u.cod = rand()%100;
                } while (consultaPorCodigo(lt,&d,u.cod)!=CODIGO_INEXISTENTE);
                printf("Codigo: %d\n\nNome: ",u.cod);
                scanf("%s",&u.usuario);
                if(strcmp(u.usuario,"0")==0){system("cls");break;}
                printf("\nDeposito inicial: ");
                scanf("%f",&u.saldoC);
                printf("\nInvestimento inicial: ");
                scanf("%f",&u.saldoP);
                printf("\nSenha(Apenas Numeros | Maior que 0): ");
                do{
                    scanf("%d",&u.senha);
                } while (u.senha==0);
                if (incluiNoFim(&lt,u)==FALTOU_MEMORIA){
					 	printf("\n\nOperacao NAO realizada: Faltou Memoria!");
                } else {
					printf("\n\nConta criada com SUCESSO!\n");
                    exibeConta(u);
                    printf("\nPressione uma tecla para continuar");
                    getch();
                    system("cls");
                }
                break;
            
            case 3:
                printf("Operacao selecionada: Consultar conta\n(Digite 0 para voltar)\n\nDigite o numero da conta\n:");
                scanf("%d",&aux);
                system("cls");
                if(aux==0){break;}
                if(consultaPorCodigo(lt,&d,aux)==SUCESSO){
                    printf("Conta encontrada!\n\n");
                    exibeConta(d);
                } else {
                    printf("Conta inexistente!\n\n");
                }
                break;
            
            case 4:
                printf("Operacao selecionada: Alterar conta\n(Digite 0 para voltar)\n\nDigite o numero da conta\n:");
                scanf("%d",&cd);
                system("cls");
                if(cd==0){break;}
                if(consultaPorCodigo(lt,&d,cd)==SUCESSO){
                    printf("Conta encontrada!\n\n");
                    exibeConta(d);
                    do
                    {
                        printf("Qual dado deseja alterar?\n\n1. Nome: %s\n\n2. Saldo conta: %.2f\n\n3. Saldo poupanca: %.2f\n\n4. Senha: %d\n\n0. Salvar\n\n:",d.usuario,d.saldoC,d.saldoP,d.senha);
                        scanf("%d",&aux);
                        switch (aux)
                        {
                        case 1:
                            printf("Digite o novo nome: ");
                            scanf("%s",&d.usuario);
                            break;
                        
                        case 2:
                            printf("Digite o novo saldo da conta: ");
                            scanf("%f",&d.saldoC);
                            break;
                        
                        case 3:
                            printf("Digite o novo saldo da poupanca: ");
                            scanf("%f",&d.saldoP);
                            break;
                        
                        case 4:
                            printf("Digite a nova senha: ");
                            scanf("%d",&d.senha);
                            break;
                        
                        default:
                            break;
                        }
                        system("cls");     
                    } while (aux!=0);
                    alteraConta(lt,d,d.cod);
                } else {
                    printf("Conta inexistente!\n\n");
                }
                break;
            
            case 5:
                printf("Operacao selecionada: Excluir conta\n(Digite 0 para voltar)\n\nDigite o numero da conta\n:");
                scanf("%d",&aux);
                system("cls");
                if(aux==0){break;}
                if(consultaPorCodigo(lt,&d,aux)==SUCESSO){
                    printf("Conta encontrada!\n\n");
                    exibeConta(d);
                    printf("CONFIRMAR EXCLUSAO!\nDIGITE A SENHA DA CONTA SELECIONADA\n\n:");
                    scanf("%d",&aux);
                    system("cls");
                    if(aux==d.senha){
                        excluiNodo(&lt,&d,d.cod);
                        printf("EXCLUSAO BEM SUCEDIDA!\n\n");
                    } else {
                        printf("EXCLUSAO CANCELADA!\n\n");
                    }
                } else {
                    printf("Conta inexistente!\n\n");
                }
                break;
            
            case 6:
                printf("Operacao selecionada: Recuperar backup\n(Digite 0 para voltar)\n\n");
                lerBackup(&b);
                exibe(b);
                printf("^^^^BACKUP^^^^\n\nDeseja carregar o backup salvo? \n(!Esta acao substituira todos dados pelo backup!)\n(Digite 0 para cancelar)\n\nDigite a senha de administrador para continuar:");
                scanf("%d",&aux);
                system("cls");
                if(aux==senhaAdm){
                    lerBackup(&lt);
                } else {
                    printf("Importacao de backup cancelada!\n\n");
                }
                break;
            
            case 7:
                printf("Operacao selecionada: Salvar backup\n(Digite 0 para voltar)\n\n");
                lerBackup(&b);
                exibe(b);
                printf("^^^^BACKUP^^^^\n\nDeseja salvar um backup? \n(!Esta acao substituira todos dados do ultimo backup!)\n(Digite 0 para cancelar)\n\nDigite a senha de administrador para continuar:");
                scanf("%d",&aux);
                system("cls");
                if(aux==senhaAdm){
                    gravaBackup(lt);
                } else {
                    printf("Gravacao de backup cancelada!\n\n");
                }
                break;

            case 8:
                printf("Operacao selecionada: Transferencia\n(Digite 0 para voltar)\n\nDigite o codigo da primeira conta :");
                scanf("%d",&aux);
                system("cls");
                if(aux==0){break;}
                if(consultaPorCodigo(lt,&d,aux)==SUCESSO){
                    printf("Conta encontrada!\n\n");
                    exibeConta(d);
                } else {
                    system("cls");
                    printf("Conta inexistente!\n\n");
                    break;
                }
                printf("Digite o codigo da segunda conta :");
                scanf("%d",&cd);
                if(consultaPorCodigo(lt,&u,cd)==SUCESSO){
                    printf("Conta encontrada!\n\n");
                    exibeConta(u);
                } else {
                    system("cls");
                    printf("Conta inexistente!\n\n");
                    break;
                }
                printf("Transferencia entre contas\n%s------>%s\n\n",d.usuario,u.usuario);
                printf("Quanto deseja transferir?\n:");
                scanf("%d",&aux);
                system("cls");
                if(d.saldoC<aux){
                    printf("Saldo insuficiente!\n\n");
                } else {
                    d.saldoC -=aux;
                    u.saldoC +=aux;
                    alteraConta(lt, u, u.cod);
                    alteraConta(lt, d, d.cod);
                    exibeConta(u);
                    exibeConta(d);
                }
                break;

            default:
                break;
            }
        }
    } while (op!=0);

    gravaArquivo(lt);
  return(0);
}
