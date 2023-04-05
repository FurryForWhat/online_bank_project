//
// Created by ADMIN on 24-Feb-23.
//

#ifndef MYFIRSTPROGRAM_ONLINE_BANK_H
#define MYFIRSTPROGRAM_ONLINE_BANK_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define SIZE 1000 // symbolic constant

struct  trans{

    char note[100];
};

struct data{
    unsigned int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];

    char pOrb[1]; //personal or business
    char loan_s[1]; //loan
    unsigned int monthly_income;
    unsigned int loan_amount;   //ဘယ်လောက်ချေးထားလဲ
    float loan_rate;
    char acc_s[1];
    int acc_level;
    unsigned long long int phNumber;
    unsigned long int current_amount;
    char address[100];
    int transAmoLimitPerDay; //transition amount per day minimise for our project 5min
    struct trans tr_record[100];
};

struct data db[SIZE];

struct my_time{
    char c_Time[25];

};

struct my_time Ctime[1];

// for Global Variable Declaration

int users= 0;
int gValid= 0;
int emailExist= -1;
int two_charArray= -1;
int nrc_valid= -1;
int strongPass= -1;
int phone_valid= -1;
int passExist= -1;
int emailFounded_index= -1;
int phone_found= -1;
int total_transfer_perDay;
int trans_limit= 0;
int gloabl_record_index=0;
unsigned int global_record_sum=0;
//global array
int space_arrary[30];
char int_to_char_arrayData[10];
unsigned int charArray_to_unsigned_int= 0;


unsigned  int current_day_to_transfer= 0; //တနေ့တာ အတွက်စုစုပေါင်း
unsigned int current_amount_to_transfer= 0;// တနေ့တာအတွက် လွှဲထားတဲ့ပမာဏ

//for Function Declaration
void welcome();
void userSector();
void loadingAllDataFromFile();
void printingAllData();
void recording_alldata_toFile();
void registration();
int charCounting(char toCount[50]);
void myGmailValidation(char toValidate[50]);
void emailExistChecking(char userInputCharacter[50]);
void compare_two_charArray(char first[50], char second[50]);
void nrc_validation(char nrc_toCheck[50]);
void myStrongPassword(char pass[50]);
void phone_validation(unsigned long long int phone_toValid);
void myStringCopy(char first[50] , char second[50] );
void login();
void passExistChecking(char toValidPass[30]);
int integer_counting( unsigned long long int intCount);
void finding_phone_number(unsigned  int toFind);
void transfer_money(int transfer, int receiver, unsigned  int amount);
void transaction_record( int transfer, int receiver , char who, unsigned int amount);
void space_counter();
void integer_to_char(unsigned int value);
unsigned int charArray_to_unsigned_fun(char charArray[]);
void get_time();
unsigned int get_record_AandT(int to_calc_index);
void tran_amount_limit_pDay(unsigned int trans_limit, unsigned int amount);
void get_limit_amount(int user_index, unsigned int amount);
void transactionLimit( unsigned int amount);
void current_data_toTransfer(unsigned int current_amount_toTransfer);

void welcome(){
    int input= 0;

    printf("Welcome to bank:\n");
    printf("Press 1 to login:\nPress 2 to Register:\nPress 3 to Exit:\n");
    scanf("%d", &input);

    if(input == 1){
        login();

    } else if(input == 2){
        registration();
    }else if(input == 3){
        //exit
        recording_alldata_toFile();
        exit(1);

    } else{
        printf("Wrong option, try again!!\n");
        welcome();
    }
}

void userSector(){
    int user_option= 0;
    unsigned int phone= 0;
    unsigned int amount_to_transfer= 0;
    printf("This is user Sector\n");

    printf("Press 1 to Transfer Money:\nPress 2 to Withdraw:\nPress 3 to update your info:\nPress 4 Cash in:\nPress5 to loan:\nPress 6 to view your history:\nPress 7 to exit;");
    scanf("%d", &user_option);

    if(user_option == 1){
        printf("This is Transfer Option:\n");
        phone_found= -1;

        while(phone_found == -1){
            printf("Enter receiver phone number:");
            scanf( "%u", &phone);
            finding_phone_number(phone);
            if(phone_found == -1){
            printf("Phone number doesn't belong to any user:\n");
            }
        }

        scanf("%u", &amount_to_transfer);
        while (amount_to_transfer<db[emailExist].current_amount){
            printf("are u sure to send for %s email :%s:\n",db[phone_found].name,db[phone_found].email);
            printf("Enter your amount to transfer:");
            scanf("%u", &amount_to_transfer);
            if(db[emailExist].current_amount-1000>amount_to_transfer){
                break;

            } else{
                printf("not sufficient balance:\n");
                amount_to_transfer= 0;
            }

        }
        two_charArray= -1;
        char tran_pass[50];
        while (two_charArray == -1){
            printf("Enter password for proceed transaction:");
            scanf(" %[^\n]", &tran_pass[0]);
            compare_two_charArray(db[emailExist].password, tran_pass);

            if(two_charArray == -1){
                printf("Wrong credential:\n");
            }
        }
        transfer_money( emailExist, phone_found, amount_to_transfer);
        userSector();
    } else if(user_option== 7){
        welcome();
    }
}

void transfer_money(int transfer, int receiver, unsigned  int amount){

    printf("loading to transfer...\n");

    //to insert transaction amount limit per day function

    get_limit_amount(receiver, amount);

    db[transfer].current_amount -= amount;
    db[receiver].current_amount += amount;
    printf("Transaction success!!!\n");
    transaction_record(transfer, receiver,'t',amount);
    transaction_record(transfer,receiver, 'r',amount);

    printingAllData();
}

void transaction_record(int transfer , int receiver , char who,unsigned int amount){
// from-WinHtut-to-lonelone-100
    int trans_name_counter = charCounting(db[transfer].name);
    int receive_name_counter = charCounting(db[receiver].name);

    integer_to_char(amount); // changing int amount to char
    int amount_counter= charCounting(int_to_char_arrayData);
//    integer_to_char(amount);
//    int amount_counter = charCounting(int_to_char_array_data);

    char from[5]={'F','r','o','m','-'};
    char to[4]={'-','t','o','-'};

    if(who == 't'){
        int index_point=0;
        for(int i=0; i<5; i++){
            db[transfer].tr_record[space_arrary[transfer]-15].note[i] = from[i];
            index_point++;
        }
        //int aaa=0;
        //int end_point = trans_name_counter+index_point;
        for(int a=0; a<trans_name_counter; a++){

            db[transfer].tr_record[space_arrary[transfer]-15].note[index_point]=db[transfer].name[a];
            index_point++;

        }
        for(int a=0; a<4; a++){
            db[transfer].tr_record[space_arrary[transfer]-15].note[index_point]=to[a];
            index_point++;
        }
        for (int aaa = 0; aaa < receive_name_counter; ++aaa) {
            db[transfer].tr_record[space_arrary[transfer]-15].note[index_point]=db[receiver].name[aaa];
            index_point++;

        }


        db[transfer].tr_record[space_arrary[transfer]-15].note[index_point]='$';
        index_point++;



        for (int i = 0; i < amount_counter; ++i) {
            db[transfer].tr_record[space_arrary[transfer]-15].note[index_point]=int_to_char_arrayData[i];
            index_point++;
        }


        get_time();
        for (int i = 0; i < 25; ++i) {
            db[transfer].tr_record[space_arrary[transfer]-15].note[index_point]=Ctime[0].c_Time[i];
            index_point++;
        }


        space_arrary[transfer] +=1;


    } else{
        //lonelone-
        char rec[14]={'-','R','e','c','e','i','v','e','-','F','r','o','m','-'};

        int index_point=0;

        for(int a=0; a<receive_name_counter; a++){
            db[receiver].tr_record[space_arrary[receiver]-15].note[index_point]=db[receiver].name[a];
            index_point++;

        }
        for(int a=0; a<14; a++){
            db[receiver].tr_record[space_arrary[receiver]-15].note[index_point]=rec[a];
            index_point++;
        }
        for(int a=0; a<trans_name_counter; a++){
            db[receiver].tr_record[space_arrary[receiver]-15].note[index_point]=db[transfer].name[a];
            index_point++;
        }
        db[receiver].tr_record[space_arrary[receiver]-15].note[index_point]='$';
        index_point++;
//        for(int aaa=0; aaa<amount_counter; aaa++){
//            db[receiver].trc[space_array[receiver]-15].note[index_point]=int_to_char_array_data[aaa];
//            index_point++;
//        }


//        get_time();
//        for(int a=0; a<25; a++){
//            db[receiver].tr_record[space_arrary[receiver]-15].note[index_point]=Ctime[0].c_time[a];
//            index_point++;
//        }


        for (int i = 0; i < amount_counter; ++i) {
            db[receiver].tr_record[space_arrary[receiver]-15].note[index_point]=int_to_char_arrayData[i];
            index_point++;
            gloabl_record_index= index_point;
        }

        get_time();
        for (int i = 0; i < 25; ++i) {
            db[receiver].tr_record[space_arrary[receiver]-15].note[index_point]=Ctime[0].c_Time[i];
            index_point++;
        }

        space_arrary[receiver] +=1;
    }
}

// id name email password pOrb loan_status monthly_income
// loan_amount loan_rate accountStatus account_level phNumber current_amount address TransRC

void loadingAllDataFromFile(){

    FILE *fptr = fopen("bankflow_db.txt","r");

    if( fptr == NULL){
        printf("Error at loadingAllDataFromFile Function!\n");
    } else{
        for(int ncc=0; ncc<SIZE ; ncc++){

            fscanf(fptr ,"%u%s%s%s%s%s%s%u%u%f%s%d%u%u%s%d",&db[ncc].id,&db[ncc].name,&db[ncc].nrc,&db[ncc].email,
                   &db[ncc].password,&db[ncc].pOrb,&db[ncc].loan_s,&db[ncc].monthly_income,
                   &db[ncc].loan_amount ,&db[ncc].loan_rate , &db[ncc].acc_s ,&db[ncc].acc_level,
                   &db[ncc].phNumber , &db[ncc].current_amount,&db[ncc].address ,&db[ncc].transAmoLimitPerDay);

            for(int gcc=0; gcc<space_arrary[ncc]-15 ; gcc++){
                fscanf(fptr,"%s",&db[ncc].tr_record[gcc].note);
            }
            if(db[ncc].email[0] == '\0'){
                break;
            }
            users++;
        }
    }
    fclose(fptr);
}

void printingAllData(){

    for(int ncc=0; ncc<users ; ncc++){


        printf("%u-%s-%s-%s-%s-%s-%s-%u-%u-%f-%s-%d-%u-%u-%s-%d",db[ncc].id,db[ncc].name,db[ncc].nrc,db[ncc].email,db[ncc].password,
               db[ncc].pOrb, db[ncc].loan_s,db[ncc].monthly_income,db[ncc].loan_amount ,db[ncc].loan_rate , db[ncc].acc_s ,db[ncc].acc_level,
               db[ncc].phNumber , db[ncc].current_amount,db[ncc].address,db[ncc].transAmoLimitPerDay);

        for(int gcc=0; gcc<space_arrary[ncc]-15 ; gcc++){
            printf("-%s",&db[ncc].tr_record[gcc].note[0]);
        }
        printf("\n");
    }
}

void recording_alldata_toFile(){
    FILE *fptr = fopen("bankflow_db.txt","w");
    if(fptr==NULL){
        printf("cannot open file to record:\n");

    }

    for(int ncc=0; ncc<users; ncc++){
        fprintf(fptr,"%u%c%s%c%s%c%s%c%s%c%s%c%s%c%u%c%u%c%f%c%s%c%d%c%u%c%u%c%s%c%d",db[ncc].id,' ',db[ncc].name,' ',db[ncc].nrc,' ',db[ncc].email,' ',db[ncc].password,
                ' ',db[ncc].pOrb,' ',db[ncc].loan_s,' ',db[ncc].monthly_income,' ',db[ncc].loan_amount ,' ',db[ncc].loan_rate ,' ', db[ncc].acc_s ,' ',db[ncc].acc_level,
                ' ',db[ncc].phNumber ,' ',db[ncc].current_amount,' ',db[ncc].address,' ',db[ncc].transAmoLimitPerDay);

        for(int gcc=0; gcc<space_arrary[ncc]-15 ; gcc++){
            fprintf(fptr," %s",&db[ncc].tr_record[gcc].note[0]);
        }
        fprintf(fptr,"%c",'\n');
    }
}

void space_counter(){
    FILE *fptr = fopen("bankflow_db.txt","r");

    if(fptr==NULL){
        printf("File opening error at space_counter fun:\n");
    } else{
        char c = fgetc(fptr);
        int index=0;

        while (!feof(fptr)){
            if( c !='\n'){
                if(c==' '){
                    space_arrary[index]+=1;

                }
                c = fgetc(fptr);

            } else{

                index++;
                c = fgetc(fptr);
            }

        }

        for (int aaa = 0; aaa < 30; ++aaa) {
            printf("%d ",space_arrary[aaa]);
        }
        printf("\n");
    }
}

void registration(){
    char regiEmail[50];
    char regiName[50];
    char regiNRC[50];
    char regiPass[20];
    unsigned long long int regiPhone;
    unsigned int regiAmount;

    printf("This is NCC Bank User Registration!\n");
    printf("Enter your email:");
    scanf(" %[^\n]", &regiEmail);
    gValid= -1;
    myGmailValidation(regiEmail);

    if(gValid != -1){
        emailExist= -1;
        emailExistChecking(regiEmail);

        if(emailExist == -1){

            printf("Your email is Valid!!\n");
            printf("Enter Your name:");
            scanf(" %[^\n]", &regiName);    //[0] ထည့်ရင် warning မပြတော့
                nrc_valid = -1;
            while (nrc_valid == -1){
                printf("Enter your nrc:");
                scanf(" %[^\n]", &regiNRC);
//                nrc_valid= -1;
                nrc_validation(regiNRC);
                if(nrc_valid == -1){
                    printf("Your nrc format is not valid\n");
                }
            }
            printf("Your nrc is valid!!\n");
           strongPass= -1;
            while(strongPass == -1){
                printf("Enter your password!!");
                scanf(" %[^\n]", &regiPass);

                myStrongPassword(regiPass);
                if(strongPass == -1){
                    printf("Your password format is too weak!!\n try again!!!\n");
                }
           }
            printf("your password format is valid and saved!!\n");
            phone_valid= -1;
            while (phone_valid== -1){
                printf("Enter Your phone number:(Please only use GSM and CDMA sim-card)\n+95 ");
                scanf("%llu", &regiPhone);
                phone_validation(regiPhone);

                if(phone_valid == -1){
                    printf("Your phone number is already registered!!\n");
                }

            }
            printf("Phone number is saved!!\n");
            printf("Enter your monthly income :");
            scanf("%u", &db[users].monthly_income);
            printf("Enter your current amount :");
            scanf("%u", &db[users].current_amount);
            printf("Enter your address:");
            scanf(" %[^\n]", &db[users].address);


            db[users].id = users+1;
            compare_two_charArray(db[users].email , regiEmail);
            compare_two_charArray(db[users].name , regiName);
            compare_two_charArray(db[users].nrc , regiNRC);
            compare_two_charArray(db[users].password , regiPass);
            compare_two_charArray(db[users].pOrb , db[2].pOrb);
            compare_two_charArray(db[users].loan_s , db[2].loan_s);
            compare_two_charArray(db[users].acc_s, db[2].acc_s);
            compare_two_charArray(db[users].tr_record[0].note, db[2].tr_record[0].note);

            db[users].loan_amount = db[2].loan_amount;
            db[users].loan_rate = db[2].loan_rate;
            db[users].acc_level = db[2].acc_level;
            db[users].phNumber = regiPhone;
            db[users].transAmoLimitPerDay = db[2].transAmoLimitPerDay;




            users++;
            printingAllData();
            welcome();

        } else{
            printf("Your gmail is already taken!!\n");
            registration();
        }


    }else{
        printf("Your gmail format not valid!\n");
        registration();
    }
}

int charCounting( char toCount[50]){   //characterCounting to the end untill \0
    int charCount= 0;
    for (int i = 0; i < 50; ++i) {

        if(toCount[i] == '\0'){
            break;
        }else{
            charCount++;
        }
    }
    return charCount;
}

void myGmailValidation(char toValidate[50]){

    // winhtut@gmail.com
    int toEndPoint = charCounting(toValidate);
    char form[10]={'@','g','m','a','i','l','.','c','o','m'};
    int count=0;

    for(int i=0; i<toEndPoint; i++){

        if(toValidate[i] == '@' || toValidate[i] ==' '){
            break;
        }else{
            count++;
        }

    }
    int tocheck=0;
    for( int i=0 ; i< toEndPoint ; i++){

        if( toValidate[count] != form[i]){
            break;
        } else{
            count++;
            tocheck++;
        }
    }

    if( tocheck == 10){
        gValid=1;
    }
}

void emailExistChecking( char userInputCharacter[50]){     // Strcmp build in function ကိုမသုံးချင်လို့ ဆောက်ပြီးသုံးတယ် အပေါ်မှာက
    int sameCount= 0;                                                         // charကို အချင်းချင်း == နဲ့တိုက်စစ်တာ မရလို့

    int second= charCounting(userInputCharacter); //charကို လက်ခံပြီးတော့ တိုက်စစ်မဲ့ဟာ user inputကဟာနဲ့

    for (int i = 0; i < users; ++i) {
        int first= charCounting(db[i].email);           //charကို လက်ခံပြီးတော့ တိုက်စစ်မဲ့ဟာ struct ထဲကဟာနဲ့
        sameCount= 0;
        if(first == second){

            for (int j = 0; j < first; ++j) {

                if(db[i].email[j] != userInputCharacter[j]){
                    break;
                } else{

                    sameCount++;            // sameCountက တိုတယ် တူတာကို စုထားတာ
                }
            }
        }
        if(second == sameCount){
            emailExist= i;
            emailFounded_index= i;
        }
    }
}

struct nrc_region{
    char region[10];
};
// ')' = 41
struct nrc_region nrcUser[3];

void nrc_validation(char nrc_toCheck[50]){

    int nrc_counter =charCounting(nrc_toCheck);
    int nrc_char=0;

    for(register int i=0; i< nrc_counter ; i++){

        if( nrc_toCheck[i] == ')'){
            break;
        }
        nrc_char++;
    }

    for(int i=0; i<users; i++){

        two_charArray=-1;
        compare_two_charArray(nrc_toCheck,db[i].nrc);
        if(two_charArray == 1){
            nrc_valid=1;
            break;
        }
    }
}

void compare_two_charArray(char first[50] , char second[50]){

  int first_counter= charCounting(first);
  int second_counter= charCounting(second);
  int same_counter= 0;
  if(first_counter == second_counter){
      for ( register int i = 0; i <first_counter ; ++i) {

             if(first[i] == second[i]){
                 same_counter++;
          } else{
                 break;
             }
      }
  }
  if(first_counter == second_counter){
      two_charArray= 1;
  }
}

void myStrongPassword(char pass[50]){

    int i=0;
    int special=0;
    int numberChar=0;
    int capChar=0;
    int smallChar=0;
    int pass_counter = charCounting(pass);
    while (strongPass == -1){
        if( i == pass_counter){
            strongPass=-1;
            break;
        }
        if( pass[i] >= 33 && pass[i] <= 42){

            special++;
        } else  if( pass[i] >= 48 && pass[i] <= 57){

            numberChar++;

        } else if( pass[i] >= 65 && pass[i] <= 90){

            capChar++;
        } else if( pass[i] >= 97 && pass[i] <= 122) {

            smallChar++;
        }
        i++;
        if( special > 0 && numberChar >0 && capChar > 0 && smallChar >0){
            strongPass = 1;
        }
    }
}
// mail,name,nrc,pass,phNo
void phone_validation(unsigned long long int phone_toValid){
    //phoneကိုမတွေ့ရင် phone_valid= 1, တွေ့ခဲ့ရင် phone_valid= -1;
    int phone_counter= 0;
    int phone_charCount=0;
    phone_charCount= integer_counting( phone_toValid);
    if(phone_charCount == 8 || phone_charCount == 10 ){
        for (int i = 0; i < users; ++i) {

            if(phone_toValid != db[i].phNumber){
                phone_counter++;
            }else{
                phone_valid = -1;

                break;
            }
        }
        if(phone_counter == users){
            phone_valid= 1;
        }else{
            printf("Invalid Phone number or Phone number is already taken!:\n");
        }
    }
}

void myStringCopy(char first[50] , char second[50] ){

    int secondCount =charCounting(second);
    for( int i=0; i<50; i++){
        first[i]='\0';
    }

    for(int a=0; a<secondCount ; a++){

        first[a] = second[a];
    }
}
// email , name, nrc, pass, phNumber
 int integer_counting(unsigned long long int intCount){   //characterCounting to the end untill \0
    int count= 0;
    while ( intCount != 0){
        intCount = intCount/10;
        count++;
    }
    return  count;
}

void login(){

    char login_email[30];
    char login_pass[30];
    emailExist= -1;
    passExist= -1;
    printf("Enter your email correctly:");
    scanf(" %[^\n]", &login_email);
    emailExistChecking(login_email);
    if(emailExist != -1){
        passExist= -1;
        while (passExist == -1){
            printf("Enter your password:");
            scanf(" %[^\n]", &login_pass);
            passExistChecking(login_pass);
            if(passExist != -1){
                printf("Your login is successful!!!\n please enjoy your time:) \n");
            }else{
                printf("your password is incorrect\n");
            }
        }

    } else{
        printf("your login email is not found!!\n");
        login();
    }
    printf("Welcome Mr/Mrs: %s\n", db[emailExist].name);
    printf("This is your current amount: %d\n",db[emailExist].current_amount );
    userSector();
}

void passExistChecking(char toValidPass[30]){
    int sameCount= 0;

    int second= charCounting(toValidPass);

    for (int i = 0; i <= users; ++i) {
        int first= charCounting(db[emailFounded_index].password);
        sameCount= 0;
        if(first == second){

            for (int j = 0; j < first; ++j) {

                if(db[emailFounded_index].password[j] != toValidPass[j]){
                    break;
                } else{
                    sameCount++;
                }
            }
        }
        if(second == sameCount){
            passExist= i;

        }
    }
}

void finding_phone_number(unsigned  int toFind){
    unsigned int number;
    for (int i = 0; i < users; ++i) {
if( db[i].phNumber == toFind){
        phone_found= i;
    break;
          }
    }

}

void get_time(){

    time_t tm;
    time(&tm);

    printf("Current time =%s\n", ctime(&tm));

    FILE *fptr= fopen("myTime.txt", "w");
    fprintf(fptr, "%s", ctime(&tm));

    fclose(fptr);

    int index= 0;
    int time_space_counter= 0;
    Ctime[0].c_Time[index]= '-';
    index++;

    FILE  *fptr2= fopen("myTime.txt", "r");
   char c= fgetc(fptr2);

   while(!feof(fptr2)){

       if( c == ' '){
           time_space_counter++;
           if(time_space_counter == 1){
               Ctime[0].c_Time[index]= '!';
               c= fgetc(fptr2);
               index++;
           }else if(time_space_counter == 4 ){
               Ctime[0].c_Time[index]= '@';
               c= fgetc(fptr2);
               index++;
           } else{
               Ctime[0].c_Time[index]= '-';
               c= fgetc(fptr2);
               index++;
           }
       }else{
           Ctime[0].c_Time[index]= c;
           c= fgetc(fptr2);
           index++;
       }
   }

}

void get_limit_amount(int user_index, unsigned int amount){

    int acc_level= db[user_index].acc_level;
    char pOrb= db[user_index].pOrb[0];
    int p_or_b=0;
    if(pOrb == 'p'){
        p_or_b= 1;
    } else{
        p_or_b= 2;
    }

    switch (acc_level) {
        case 1:
            if(p_or_b == 1){
            trans_limit= 100000;
            } else{
                trans_limit= 1000000;
            }
            break;
        case 2:
            if(p_or_b == 1){
                trans_limit= 50000;
            } else{
                trans_limit= 500000;
            }
            break;
        case 3:
            if(p_or_b == 3){
                trans_limit= 10000;
            } else{
                trans_limit= 100000;
            }
            break;
        default:
            break;
    }

    transactionLimit( amount);
}

void current_data_toTransfer(unsigned int current_amount_toTransfer){
    char get_current_day[2];

    get_time();

    printf("current info :%s : current amount to transfer: %u", Ctime[0].c_Time,current_amount_toTransfer);

    get_current_day[0]= Ctime[0].c_Time[9];
    get_current_day[1]= Ctime[0].c_Time[10];
   unsigned int current_day_toTransfer=   charArray_to_unsigned_fun(get_current_day);   //using charArray to form unsinged int (current day)
    printf("\ncurrent day: %d\n", current_day_toTransfer);

    current_amount_to_transfer= current_amount_toTransfer;// amount
    current_day_to_transfer= current_day_toTransfer; // day

}
//to calculate all amount of same days
unsigned int get_record_AandT(int to_calc_index){
    int record_counter= space_arrary[to_calc_index]-15;
    int quantity_of_amount=0;
    int index_counter= 0;
//    printf("record_counter: %d", record_counter);

    char amount_char_array[10];
    for (int a = record_counter-1; a >= 0; ++a) {
        int current_record_counter= charCounting(db[to_calc_index].tr_record[a].note);
//        printf("current record counter: %d", current_record_counter);

            // aa for searching '$'
        for (int aa = 0; aa < current_record_counter; ++aa) {
            if(db[to_calc_index].tr_record[a].note[aa] == '$'){
                break;
            }

            index_counter++;

        }

        // aaa for searching '-'
        for (int aaa = index_counter; aaa < current_record_counter; ++aaa) {

            if(db[to_calc_index].tr_record[a].note[aaa] == '-') {
                break;
            }
            quantity_of_amount++;

        }
        index_counter++;
        for (int x = 0; x <quantity_of_amount-1 ; x++) {
            amount_char_array[x]= db[to_calc_index].tr_record[a].note[index_counter];
            index_counter++;
        }
         unsigned int current_record_amount= charArray_to_unsigned_fun(amount_char_array);
        printf("Current_record_amount : %d\n", current_record_amount);
            }


    }


// to calculate all amount of same days
unsigned int calculate_amounts_same_days(int to_calcu_index){
    unsigned int total_amount_for_same_day=0;

    int record_counter =space_arrary[to_calcu_index]-15;
    int index_counter=0;


    char day_char_array[3];
    for(int a=record_counter-1; a>=0 ; a--){


        int current_record_counter =  charCounting(db[to_calcu_index].tr_record[a].note);

        // to get $
        for(int aa=0; aa<current_record_counter; aa++){
            if(db[to_calcu_index].tr_record[a].note[aa]=='$'){
                break;
            }

            index_counter++;
        }
        int quantity_of_amount=0;
        for(int aaa=index_counter; aaa<current_record_counter; aaa++){

            if(db[to_calcu_index].tr_record[a].note[aaa]=='-'){

                break;

            }
            quantity_of_amount++;

        }
        index_counter++;
        char amount_char_array[10];
        for(int i=0; i<10; i++){
            amount_char_array[i]='\0';
        }
        for(int x=0; x<quantity_of_amount-1 ; x++){

            amount_char_array[x]=db[to_calcu_index].tr_record[a].note[index_counter];
            index_counter++;

        }
        unsigned int current_record_amount = charArray_to_unsigned_fun(amount_char_array);
        printf("\ncurrent_record_amount: %d\n",current_record_amount);

        total_amount_for_same_day = total_amount_for_same_day+current_record_amount;
        //to get day of current record:

        for(int xx=index_counter; xx<current_record_counter; xx++){

            if(db[to_calcu_index].tr_record[a].note[xx]=='!'){
                break;
            }
            index_counter++;
        }

        day_char_array[0]=db[to_calcu_index].tr_record[a].note[index_counter+5];
        day_char_array[1]=db[to_calcu_index].tr_record[a].note[index_counter+6];
        unsigned int current_record_day= charArray_to_unsigned_fun(day_char_array);

        printf("Current record day: %d\n",current_record_day);

        if(current_record_day!=current_day_to_transfer){
            total_amount_for_same_day = total_amount_for_same_day+current_record_amount;
            break;
        }
//            else{
//                total_amount_for_same_day = total_amount_for_same_day+current_record_amount;
//            }

        index_counter=0;
    }
    printf(" total amount for same day! %u",total_amount_for_same_day);

    return total_amount_for_same_day;
}

 void transactionLimit( unsigned int amount){

    if (amount > trans_limit) {
        printf("Transaction limit exceeded.");
    } else {
        printf("Transaction successful.");
    }
}

void integer_to_char(unsigned int value){

    FILE  *fptr= fopen("100.txt", "w");

    if(fptr == NULL){
        printf("File opening error at integer_to_char:\n");
    } else{
        fprintf(fptr, "%u", value);
    }
    fclose(fptr);

    FILE *fptr2= fopen("100.txt", "r");
    fscanf(fptr2 , "%s", &int_to_char_arrayData[0]);

//    for (int i = 0; i < 4; ++i) {
//        printf("%c ", int_to_char_arrayData[i]);
//    }
}

unsigned int charArray_to_unsigned_fun(char charArray[]){
    unsigned int data=0;
    FILE  *fptr= fopen("100.txt", "w");

    if(fptr == NULL){
        printf("File opening error at integer_to_char:\n");
    } else{
        fprintf(fptr, "%s", charArray);
    }
    fclose(fptr);

    FILE *fptr2= fopen("100.txt", "r");
    fscanf(fptr2 , "%u", &data);

    return data;
}
#endif //MYFIRSTPROGRAM_ONLINE_BANK
