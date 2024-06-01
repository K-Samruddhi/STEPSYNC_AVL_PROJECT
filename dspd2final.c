
#include "dspd2final.h"


void main()
{
    user *user_tree = create_user_tree(NULL);
    user_InOrder(user_tree);
    group *group_tree = create_group_list(user_tree, NULL);
    user *top_3[3] = {NULL, NULL, NULL};
	            user_tree = user_top_3(user_tree, top_3);

    group *new = NULL;
    leader *leader_board = NULL;

    printf("Welcome to the fitness application \n ");

    printf("----------------------------------\n");
    printf("1 \t Add a person publicly \n");
    printf("2 \t Create a Group \n");
    printf("3 \t Check global top 3 \n");
    printf("4 \t Group Achievement\n");
    printf("5 \t Group Leader Board \n");
    printf("6 \t Check My Rewards \n");
    printf("7 \t Delete a User \n");
    printf("8 \t Delete a Group of Users \n");
    printf("9 \t Merge two given Groups \n");
    printf("10 \t Display Group Information \n");
    printf("11 \t Suggest Goal Updates \n");
    printf("12 \t display information of individuals \n");
    printf("----------------------------------");

    char choice;
    int oprn;
    char null;

    do
    {
        printf("Choose your operation : \n");
        scanf("%d", &oprn);

        switch (oprn)
        {
        case 1:
        {
            user *new;
            new = create_user();
            user_tree = user_insert_avl(user_tree, new);
            printf("function completed \n");
             user_InOrder(user_tree);
            break;
        }

        case 2:
            new = create_group(user_tree);
            group_tree = group_inserst_avl(group_tree, new);
            break;

        case 3:
            user_tree = user_top_3(user_tree, top_3);
            printf("the top 3 individuals of the day are : \n");
            printf("\n");
            visit_user(top_3[0]);
            printf("\n");
            visit_user(top_3[1]);
            printf("\n");
            visit_user(top_3[2]);
            break;

        case 4:
            printf("Enter the ID of the group  : ");
            int id;
            scanf("%d", &id);
            group *temp = group_search(group_tree, id);
            Check_group_acheivement(temp);
            break;

        case 5:
            leader_board = create_leader_tree(NULL, group_tree);
            printf("============================\n");
            leader_inorder(leader_board);
            printf("Leader preorder : \n");
            leader_preorder(leader_board);
            printf("Leader postorder : \n");
            leader_postorder(leader_board);
            break;

        case 6:
            Check_individual_rewards(user_tree, top_3);
            break;

        case 7:
            printf("ENter th ID of the individual to be deleted \n");
            int key;
            scanf("%d", &key);
            user_tree = user_delete_avl(user_tree, group_tree, key);
            printf("===========================================\n");
             user_InOrder(user_tree);
            break;

        case 8:
            printf("Enter the ID of the group to be deleted : ");
            int gkey;
            scanf("%d", &gkey);
            group_tree = group_delete_avl(group_tree, gkey);
            printf("===========================================\n");
            break;

        case 9:
            group_tree = merge_groups(group_tree);
            break;

        case 10:
            printf("the information of the groups present are : \n");
            printf("===========================================\n");
            group_Inorder(group_tree);
            printf("the height of the tree is %d \n",group_tree->height);
            printf("===========================================\n");
            group_preorder(group_tree);
            printf("===========================================\n");
            group_postorder(group_tree);
            printf("===========================================\n");
            break;

        case 11:
            Suggest_goal_update(user_tree, top_3);
            break;

        case 12:
            printf("  INDIVIDUAL INFORMATION \n");
            printf("===========================================\n");
            user_InOrder(user_tree);            
            printf("the height of the tree is %d \n",user_tree->height);
            printf("===========================================\n");
            printf(" User Preorder  \n");
            user_preorder(user_tree);
            printf(" User Postorder \n");
            user_postorder(user_tree);
            break;
            case 13:
             printf("the information of the groups present are : \n");
             int low;
             printf("Enter the low value");
             scanf("%d",&low);
             int high;
             printf("Enter the high value:");
             scanf("%d",&high);
             display_range_info(group_tree,low,high);
        }
    
        printf("Do you want to continue , if yes type y ");
        scanf("%c", &null);
        scanf("%c", &choice);
    } while (choice == 'y');
    
    // output_user_list(user_list) ;
    // output_group_list(group_list );
}