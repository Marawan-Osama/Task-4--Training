#include "Task4.h"

typedef struct ST_cardData_t{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef struct ST_terminalData_t{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_transStat_t{
    DECLINED,
    APPROVED
}EN_transStat_t;

typedef struct ST_transaction_t{
    ST_cardData_t cardHolderData;
    ST_terminalData_t transData;
    EN_transStat_t transStat;
}ST_transaction;

typedef struct ST_accountBalance_t{
    uint8_t primaryAccountNumber[20];
    float balance;
}ST_accountBalance_t;

ST_accountBalance_t Server[] = {
    { "123456789" ,  100.00},
    { "234567891" ,  6000.00},
    { "567891234" ,  3250.25},
    { "456789123" ,  1500.12},
    { "258649173" ,  500.00},
    { "654823719" ,  2100.00},
    { "971362485" ,  0.00},
    { "793148625" ,  1.00},
    { "123123456" ,  10.12},
    { "456789321" ,  0.55},
};

int main()
{
    Compare();

    return 0;
}

ST_cardData_t CardData(){
    ST_cardData_t User;
    printf("Please Enter Card Data: ");
    printf("\nPlease Enter the Card Holder Name:\n");
    scanf("%[^\n]%*c",&User.cardHolderName);
    printf("Please Enter the Primary Account Number:\n");
    scanf("%[^\n]%*c",&User.primaryAccountNumber);
    printf("Please Enter the Card Expiry Date: (MM/YY)\n");
    scanf("%[^\n]%*c",&User.cardExpirationDate);
    return User;
}

ST_terminalData_t TerminalData(){
    ST_terminalData_t Terminal;
    printf("Please Enter Terminal Data:\n");
    printf("Please Enter the transaction Amount:\n");
    scanf("%f",Terminal.transAmount);
    printf("Please Enter transaction Date: (DD/MM/YYYY)\n");
    scanf("%s",&Terminal.transactionDate);
    return Terminal;
}

int Compare(){
    int credit;
    ST_cardData_t User = CardData();
    ST_terminalData_t Terminal = TerminalData();
    char TDate[] = {Terminal.transactionDate[8],Terminal.transactionDate[9],Terminal.transactionDate[3],Terminal.transactionDate[4]};
    int transaction_date;
    sscanf(TDate, "%d", &transaction_date);
    char Edate[] = {User.cardExpirationDate[3],User.cardExpirationDate[4],User.cardExpirationDate[0],User.cardExpirationDate[1]};
    int expiration_date;
    sscanf(Edate,"%d",&expiration_date);
    printf("%d",expiration_date);
    if(transaction_date>expiration_date){
        printf("The transaction is Declined");
        return 0;
    }
    else if(Terminal.transAmount>5000){
        printf("The transaction is Declined");
        return 0;
    }
    else for(int i = 0; i<9;i++){
        if(strcmp((char*)Server[i].primaryAccountNumber,(char*)User.primaryAccountNumber) == 0){
            credit = Server[i].balance;
        }
        if(credit<Terminal.transAmount){
            printf("The transaction is Declined");
            return -1;
        }
        else{
            printf("The transaction is Accepted");
            return -1;
        }
    }
    return -1;
}
