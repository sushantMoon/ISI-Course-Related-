/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 18 Sepetember, 2018
Program description: Hetrogeneous Stack 
Acknowledgements:
------------------------------------*/
#include "../generic/stack.h"
#include "../generic/common.h"


typedef union HeterogeneousNode{
    int i;    // type = 0
    char c;    // type = 1
    float f;    // type = 2
}HeterogeneousNode;

typedef struct HNode{
    HeterogeneousNode nh;
    int type;
}HNode;

int main()
{
    Stack *hetStack = newStack(sizeof(HNode));
    printf("Testing Heterogenous Stack!!!\n");
    printf("Enter the size for the heterogenous stack you want: ");
    int size;
    scanf("%d", &size);
    int i;
    for(i = 0; i < size; i++)
    {
        printf("Enter :\n\tFor int : enter 0\n\tFor char : enter 1\n\tFor float : enter 2\n");
        int t;
        scanf("%d", &t);
        HNode *hn;
        if (t == 0){
            hn = MALLOC(HNode, 1);
            (*hn).type = 0;
            printf("Enter the Integer : ");
            scanf("%d",&((*hn).nh.i));
            printf("%d\n", (*hn).nh.i);
            push(hetStack, hn);
        }
        else if (t == 1){
            hn = MALLOC(HNode, 1);
            (*hn).type = 1;
            // getchar();
            printf("Enter the Char : ");
            scanf("\n%c",&((*hn).nh.c));
            printf("%c\n", (*hn).nh.c);
            push(hetStack, hn);
        }
        else if (t == 2){
            hn = MALLOC(HNode, 1);
            (*hn).type = 2;
            printf("Enter the Float : ");
            scanf("%f",&((*hn).nh.f));
            printf("%f\n", (*hn).nh.f);
            push(hetStack, hn);
        }
        else{
            printf("Enter a valid number, valid choices are => 0,1,2\n");
        }
    }
    
    printf("Total Elements in the Stack : %d\n",(int)hetStack->num_elements);
    while(hetStack->num_elements != 0){
        HNode hn;
        pop(hetStack, &hn);
        if (hn.type == 0){
                printf("Popped int : %d\n", hn.nh.i);
        }
        if (hn.type == 1){
                printf("Popped char : %c\n", hn.nh.c);
        }
        if (hn.type == 2){
                printf("Popped float : %f\n", hn.nh.f);
        }
    }
    freeStack(&hetStack);
    return 0;
}
