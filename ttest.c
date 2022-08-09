#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

// function to calculate the test statistic from user entered data
float ttest(float x1[100], float x2[100], int n1, int n2);

// calculate test static from csv data
float ttest_csv(char data[100]);

// function to calculate the mean of numbers
float mean(float numbers[100], int n);

// function to compute the variance of numbers
float var(float numbers[100], int n);

int main(){
    MENU:
    system("cls");
    printf("###############################");
    printf("\n#      TWO SAMPLE T-TEST      #");
    printf("\n###############################");

    printf("\n_______________________________\n");
    printf("|\t     MENU             |");
    printf("\n|_____________________________|\n");
    printf("|  1 to enter data manually   |\n");
    printf("|  2 to use a csv file        |\n");
    printf("|  3 to exit                  |\n");
    printf("|_____________________________|\n");

    int menu_choice;
    printf("\n\nEnter choice from the menu: ");
    scanf("%d",&menu_choice);
    
    if(menu_choice==1){
        system("cls");
        int i,n1,n2;
        printf("T TEST FROM MANUALLY ENTERED DATA\n\n");
        printf("Enter first sample number (n1): ");
        scanf("%d",&n1);
        printf("Enter second sample number (n2): ");
        scanf("%d",&n2);

        float sample_data1[n1], sample_data2[n2];
        
        printf("\n\nEntering first sample data\n");
        for(i=0; i<n1; i++){
            scanf("%f",&sample_data1[i]);
        }

        printf("\n\nEntering second sample data\n");
        for(i=0; i<n2; i++){
            scanf("%f",&sample_data2[i]);
        }

        float tvalue = ttest(sample_data1, sample_data2, n1, n2);

        printf("\nTEST RESULTS");
        printf("\n___________________________________");
        printf("\nThe calculated t-value = %.3f\n",tvalue);
        printf("\ndf = %d\n",n1+n2-2);
        printf("___________________________________");
    }

    else if(menu_choice==2){
        system("cls");
        printf("T TEST FROM FILE DATA\n\n");
        printf("Import csv file by entering the path here");
        printf("\nEnter file name here: ");
        char name[100];
        scanf("%s",name);
        printf("\nTEST RESULTS\n");
        float tvalue = ttest_csv(name);
        printf("\n___________________________________");
        printf("\nThe calculated t-value = %.3f\n",tvalue);
        printf("___________________________________");
    }
    else if(menu_choice==3){
        system("cls");
        printf("PROGRAM HAS BEEN EXITED");
    }
    else{
        goto MENU;
    }
}

// the mean
float mean(float numbers[100], int n){
    float sum = 0;
    for(int i=0; i<n; i++){
        sum = sum + numbers[i];
    }
    return (sum)/n;
}

// the variance
float var(float numbers[100], int n){
    float average = mean(numbers,n);

    // calculating the variance
    float squared_sum = 0;
    for(int i=0; i<n; i++){
        squared_sum = squared_sum + pow((numbers[i] - average),2);
    }
    // returning the variance
    return squared_sum/(n-1);
}

// ttest
float ttest(float x1[100], float x2[100], int n1, int n2){
    float sum1 =  0;
    int i;

    // mean of the first sample
    float mean1 = mean(x1,n1);

    // mean of the second sample
    float mean2 = mean(x2,n2);

    // variance of the first sample
    float var1 = var(x1,n1);

    // variance of the second sample
    float var2 = var(x2,n2);

    // finding the pooled variance
    float pooled_var = (var1+var2)/(n1+n2-2);
    
    // // test statistic (computed t value) for paired sample t test (dependent)
    // float t_value = (mean1-mean2)/sqrt(pooled_var/(1/n1 + 1/n2));

    // test statistic for unpaired sample t test (independent)
    float tvalue = (mean1-mean2)/sqrt(var1/n1 + var2/n2);

    // // checking to see if the t value is negative
    // if(tvalue<0){
    //     float new_tvalue = -1*t_value;
    // }
    return tvalue;
}

float ttest_csv(char data[100]){
    FILE *fp;

    fp = fopen(data,"r");

    if(fp==NULL){
        printf("Error in opening file\nProgram is terminating...");
        exit(0);
    }

    int x, y, sample1,sample2, sum1=0, sum2=0;
    int counter1 = 0;
    float Modified_sum1, Modified_sum2, mean1, mean2;
    float variance1, variance2,Modified_var1, Modified_var2, sum_sqrd1=0, sum_sqrd2=0;
    char line[100],line1[100];;

    char *sp;
    char *sp1;
    printf("\nUsed dataset\nnote that the first row is not part of the data");
    printf("\nSample1 Sample2");
    while(fgets(line,100,fp) != NULL){

        sp = strtok(line,",");
        sample1 = atoi(sp);

        sp = strtok(NULL,",");
        sample2 = atoi(sp);
        counter1++;
        sum1 += sample1;
        sum2 += sample2;
        printf("\n%d\t%d",sample1,sample2);
    }
    fclose(fp);

    Modified_sum1 = sum1;
    Modified_sum2 = sum2;
    mean1 = Modified_sum1/(counter1-1);
    mean2 = Modified_sum2/(counter1-1);

    // calculating the variance
    fp = fopen(data,"r");
    while(fgets(line,100,fp) != NULL){

        sp = strtok(line,",");
        x = atoi(sp);

        sp = strtok(NULL,",");
        y = atoi(sp);
        sum_sqrd1 = sum_sqrd1 + pow((x-mean1),2);
        sum_sqrd2 = sum_sqrd2 + pow((y-mean2),2);
    }

    variance1 = sum_sqrd1 - pow(mean1,2);
    variance2 = sum_sqrd2 - pow(mean2,2);
    Modified_var1 = variance1/(counter1-2);
    Modified_var2 = variance2/(counter1-2);
    printf("\n\ndf = %d",counter1-1 + counter1-1 - 2);

    float tvalue = (mean1-mean2)/sqrt(Modified_var1/(counter1-1) + Modified_var2/(counter1-1));
    return tvalue;
}