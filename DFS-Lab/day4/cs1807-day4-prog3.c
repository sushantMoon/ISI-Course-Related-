/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 31 July, 2018
Program description: Sum for large numbers
Acknowledgements:
------------------------------------*/

#include <stdio.h>

#define MALLOC(type, size) (type *)malloc(sizeof(type)* size)
#define COUNT 100
#define TEMPFILE "TempFile"
#define OUTPUTFILE "3_LARGESUM"
int main(){
    FILE *fp1, *fp2, *fp3, *fp4;
    char file1[COUNT], file2[COUNT];
    printf("Enter the First File Name:\n");
    scanf("%s",file1);
    printf("Enter the Second File Name:\n");
    scanf("%s",file2);

    fp1 = fopen(file1, "r");
    if (fp1 == NULL){
        printf("Enter the valid string\n");
        return 0;
    }
    fp2 = fopen(file2, "r");
    if (fp2 == NULL){
        printf("Enter the valid string\n");
        return 0;
    }
    // fp1 = fopen("3_file1", "r");
    // fp2 = fopen("3_file2", "r");
    remove(TEMPFILE);
    remove(OUTPUTFILE);
    fp3 = fopen(TEMPFILE, "a+");
    if (fp3 == NULL){
        printf("Enter the valid string\n");
        return 0;
    }
    fp4 = fopen(OUTPUTFILE, "a+");
    if (fp4 == NULL){
        printf("Enter the valid string\n");
        return 0;
    }

    // moving to the end of the file1
    fseek(fp1, 0, 2);
    int byteSize1 = ftell(fp1);
    // moving to the end of the file2
    fseek(fp2, 0, 2);
    int byteSize2 = ftell(fp2);

    int i=1, j=1;
    int carry = 0, a = 0, b = 0;
    while(1){
        a = 0;
        b = 0;
        if ((i<=byteSize1) && (j<=byteSize2)){
            char a1, b1;
            fseek(fp1, -1*i, 2);
            a1 = fgetc(fp1);
            a = a1 - '0';
            // printf("%d ", a);

            fseek(fp2, -1*j, 2);
            b1 = fgetc(fp2);
            b = b1 - '0';
            // printf("%d \n", b);
            i++;
            j++;
        }
        else if ((i>byteSize1) && (j<=byteSize2)){
            char b1;
            fseek(fp2, -1*j, 2);
            b1 = fgetc(fp2);
            b = b1 - '0';
            // printf("%d \n", b);
            j++;
        }
        else if ((i<=byteSize1) && (j>byteSize2)){
            char a1;
            fseek(fp1, -1*i, 2);
            a1 = fgetc(fp1);
            a = a1 - '0';
            // printf("%d \n", b);
            i++;
        }
        else{
            if (carry>0){
                fputc((carry + '0'), fp3);
            }
            break;
        }
        // printf("%d %d %d\n",a,b,carry);
        int sum = a+b+carry;
        fputc(((sum%10) + '0'), fp3);
        carry = sum/10;
    }


    // moving to the end of the file3
    fseek(fp3, 0, 2);
    int byteSize3 = ftell(fp3);
    // saving the right result 
    for(i = 1; i <= byteSize3; i++)
    {
        char s1;
        fseek(fp3, -1*i, 2);
        s1 = fgetc(fp3);
        // printf("%c",s1);
        fputc(s1, fp4);
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    remove(TEMPFILE);
    fclose(fp4);
    printf("The Sum of number in %s and %s is stored in the file : %s\n", file1, file2, OUTPUTFILE);
    return 0;
}



// int main()
// {
//     int i=0, alen=0, blen=0, j=0, k=0, carry=0, clen=0;
//     char a[COUNT], b[COUNT], c[COUNT+1], d[COUNT+1];

//     printf("Enter the First Number:\n");
//     scanf("%s",a);
//     printf("Enter the Second Number:\n");
//     scanf("%s",b);
//     while(a[alen] != '\0'){
//         alen++;
//         if (a[alen] == '\0')
//             break;
//     }
//     while(b[blen] != '\0'){
//         blen++;
//         if (b[blen] == '\0')
//             break;
//     }
//     // printf("%d %d\n", alen, blen);
//     if (alen>=blen){
//         j = alen-1;
//         k = blen-1;
//         while(1){
//             if (k>=0){
//                 // printf("%d %d %d\n",(a[j] - '0') , (b[k] - '0') , carry );
//                 int sum = (a[j] - '0') + (b[k] - '0') + carry;
//                 c[clen] = '0' + (sum%10);
//                 carry = sum/10;
//                 j--;
//                 k--;
//                 clen++;
//             }
//             else{
//                 if (j>=0) {
//                     // printf("%d %d\n",(a[j] - '0') ,  carry );
//                     int sum = (a[j] - '0') + carry;
//                     c[clen] = '0' + (sum%10);
//                     carry = sum/10;
//                     j--;
//                     k--;
//                     clen++;
//                 }
//                 else{
//                     if (carry > 0){
//                         c[clen] = '0' + carry;
//                         clen++;
//                     }
//                     break;
//                 }
//             }
//             // printf("%c\n",c[clen-1]);
//         }
//     }
//     else{
//         j = blen-1;
//         k = alen-1;
//         while(1){
//             if (k>=0){
//                 // printf("%d %d %d\n",(b[j] - '0') , (a[k] - '0') , carry );
//                 int sum = (b[j] - '0') + (a[k] - '0') + carry;
//                 c[clen] = '0' + (sum%10);
//                 carry = sum/10;
//                 j--;
//                 k--;
//                 clen++;
//             }
//             else{
//                 if (j>=0) {
//                     // printf("%d %d\n",(b[j] - '0') ,  carry );
//                     int sum = (b[j] - '0') + carry;
//                     c[clen] = '0' + (sum%10);
//                     carry = sum/10;
//                     j--;
//                     k--;
//                     clen++;
//                 }
//                 else{
//                     if (carry > 0){
//                         c[clen] = '0' + carry;
//                         clen++;
//                     }
//                     break;
//                 }
//             }
//             // printf("%c\n",c[clen-1]);
//         }
//     }
    
//     j=0;
//     i = clen-1;
//     while(i >= 0){
//         d[j] = c[i];
//         j++;
//         i--;
//     }
//     d[j] = '\0';
//     i=0;
//     printf("The Sum is : ");
//     while(1)
//     {
//         if (d[i] == '\0')
//             break;
//         printf("%c",d[i]);
//         i++;
//     }
//     printf("\n");
//     return 0;
// }
