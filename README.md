# STEPSYNC_AVL_PROJECT
Step Sync is a step tracking application designed to help users monitor their daily steps, set and achieve weekly goals ,and engage in healthy application .The data structure used here is a Tree(AVL tree).
Features 
Individual Tracking:
Unique ID, Name, Age
Daily step goal
Weekly step count (array for 7 days)
Sorted by unique ID for efficient management

Group Tracking:
Group ID and Group name
Member IDs with pointers to individuals in the individual tree
Weekly group goal

Leaderboards:
Individual leaderboard with rewards for top 3 individuals
Group leaderboard ranking based on total steps completed by group members
Technologies Used
 AVL Tree data structures for efficient storage and retrieval
Designed with a focus on performance and scalability
typedef struct user
{
    int ID;
    int group;
    char name[50];
    int age;
    int daily_goal;
    int weekly_count[7];
    int height;

    struct user *left;
    struct user *right;
} user;

typedef struct clanmate
{
    user *clan;
    int height;

    struct clanmate *left;
    struct clanmate *right;
} clanmate;//this structure is for the group members in the group;

typedef struct group
{
    int ID;
    char name[50];
    int weelky_goal;
    clanmate *teammates;
    int height;

    struct group *left;
    struct group *right;
} group;

typedef struct leader
{
    group *team;
    int height;
    struct leader *left;
    struct leader *right;
} leader;//this structure is leader board structure
1. User Structure
The user structure represents an individual user in your application. It contains various attributes related to the user, such as their ID, group membership, personal details, and daily/weekly goals. Additionally, it includes pointers to manage this user within a  tree.
ID: Unique identifier for the user.
group: Identifier for the group the user belongs to.
name: The user's name.
age: The user's age.
daily_goal: The user's daily step goal.
weekly_count: Array to track the user's weekly step counts (7 days).
height: Height of the node in the tree (useful for balanced tree operations).
left: Pointer to the left child in the tree.
right: Pointer to the right child in the tree.

3. Clanmate Structure
The clanmate structure represents a member of a group. This structure is designed to organize users within a group using a  tree. It contains a pointer to the user structure and tree-related pointers.
clan: Pointer to the user structure representing a group member.
height: Height of the node in the tree (useful for balanced tree operations).
left: Pointer to the left child in the tree.
right: Pointer to the right child in the tree

3. Group Structure
The group structure represents a group of users. It includes attributes related to the group's identity, goals, and a  tree of clanmate structures to organize group members.
ID: Unique identifier for the group.
name: The group's name.
weekly_goal: The group's weekly step goal.
teammates: Pointer to the root of the  tree of clanmate structures representing the group members.
height: Height of the node in the tree (useful for balanced tree operations).
left: Pointer to the left child in the tree.
right: Pointer to the right child in the tree.

5. Leader Structure
The leader structure represents a node in the leaderboard. It contains a pointer to a group and tree-related pointers. This allows organizing groups within a leaderboard using a  tree.
team: Pointer to the group structure representing a group in the leaderboard.
height: Height of the node in the tree (useful for balanced tree operations).
left: Pointer to the left child in the  tree.
right: Pointer to the right child in the  tree.

Relationships and Usage
Each user is part of a group and is organized in a  tree using the left and right pointers in the user structure.
Each group contains multiple users, organized through the teammates pointer, which points to a  tree of clanmate structures. Each clanmate in turn points to a user.
The leader structure manages a  tree of groups, forming a hierarchical leaderboard of groups.
These structures collectively facilitate the organization and tracking of individual and group step goals, ensuring efficient access and updates through  tree operations.

int parse(char s[])
{
    int num = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        num = num * 10 + (s[i] - 48);
    }
    return num;
}//this function is for changing word string to integer string
// for converting string from file and store aas integer for the program
This is the parsing functions which converts charaters into integers as when we are reading contents from the file everything is characters but we need them some numbers as integers for comparing ,sorting operartions so here this function is used.

int Avg_steps(int steps[])
{
    int sum = 0;
    for (int i = 0; i < 7; i++)
    {
        sum += steps[i];
    }
    return sum /7;
}//this function is used in suggest goal update as well as get top_3

int clan_avg_steps(clanmate *root)
{
    int sum = 0;
    if (root)
    {
        sum = sum + clan_avg_steps(root->left);
        sum = sum + Avg_steps(root->clan->weekly_count);
        sum = sum + clan_avg_steps(root->right);
    }
    return sum;
}//this function will calculate the avg steps of members of the group which is needed in group achivements
// used in generating leader board while comparing groups
above first function Avg_steps calculate the average of weekly steps array.
clan_avg_steps take the parameter of root of clanmate nothing but individual from a group this function calculates average steps of each member in a group.
these two functions are used in group achivement as well as in generating the leader board.

void visit_user(user *users)
{
    if (users)
    {
        printf("ID \t %d\n", users->ID);
        printf("Group \t %d\n", users->group);
        printf("Name \t %s\n", users->name);
        printf("Age \t %d\n", users->age);
        printf("Daily Goal\t %d\n", users->daily_goal);
        printf("Weekly goal (Sundya->Saturday):\n");
        for (int i = 0; i < 7; i++)
            printf("   %d", users->weekly_count[i]);
        printf("\n the average step count of the week is %d \n", Avg_steps(users->weekly_count));
        printf("\n");
    }
}
This is visit_user functions just to print the information of user.

int clan_num(clanmate *root)
{
    int num = 0;
    if (root)
    {
        num = num + clan_num(root->left);
        num = num + 1;
        num = num + clan_num(root->right);
    }
    return num;
}//this function will calculate the number of members in the group
// for overwriting into the text file for further reading
This clan_num function is to calculate the no of members in a group .this function is also used in file overwriting operation(when we did some changes in the tree like insert ,delete these changes are also to be reflected  in the existing files of individuals as well as group).

void user_InOrder(user *root)
{
    if (root != NULL)
    {
        user_InOrder(root->left);
        visit_user(root);
        user_InOrder(root->right);
    }
}
Inorder traversal of user which is used for sorting.

void clan_free_group(clanmate *root)
{
    if (root)
    {
        clan_free_group(root->left);
        root->clan->group = 0;
        clan_free_group(root->right);
    }
}
// when a group is deleted
When the group is deleted the members should also be deleted in individuals list and the members tag which is used to identify a member is there in which group is also set to zero means now that member is now not there in any of the group.

void visit_group(group *temp)
{
  
    if (temp)
    {
        printf("Group ID \t %d\n", temp->ID);
        printf("Group Name \t %s\n", temp->name);
        printf("Weekly Group Goal\t %d\n", temp->weelky_goal);
        printf(" the clan members are : \n");
        clan_inorder(temp->teammates);
        printf("\n");
    }
}
The same visit function to print the information regarding groups.

user *create_user()
{
    user *newIndividual = (user *)malloc(sizeof(user));
    if (!newIndividual)
    {
        printf("Memory allocation failed.\n");
        newIndividual = NULL; // type mismatch ?
    }
    else
    {
        newIndividual->group = 0; // o is set for no group , natural number says the group
        printf("\n enter the desired ID of the user (should be unique) :");
        scanf("%d", &newIndividual->ID);
        printf("\n Enter the name of user :");
        scanf("%s", newIndividual->name);
        printf("\n Enter the age of user : ");
        scanf("%d", &newIndividual->age);
        printf("]\\n Enter the daily step goal , that user wants to complete : ");
        scanf("%d", &newIndividual->daily_goal);
        printf("\n Enter the weekly step count (sunday to saturday) \n");
        for (int i = 0; i < 7; i++)
            scanf("%d", &newIndividual->weekly_count[i]);
            
        newIndividual->left = NULL;
        newIndividual->right = NULL;

        printf("user created succesfully \n");
    }

    return newIndividual;
}
This is create user function is two create the user through malloc and creates space for each attribute of user.

user *user_search(user *root, int key)
{
    user *temp = root;
    if (root)
    {
        int flag = 0;
        while (temp && !flag)
        {
            if (temp->ID == key)
                flag = 1;
            else if (temp->ID > key)
                temp = temp->left;
            else if (temp->ID < key)
                temp = temp->right;
        }
    }
    return temp;
}
We are creating the AVL tree for storing the information of individulas as well as users so to insert any child in the AVL tree first we should know it's appropriate positions like in BST (the left child should be smaller than the root and root should be smaller than the right child).here we rae sorting based on ID's of individulas and groups as the id provided is unique and every node in AVL tree is unique.so these search function is used for searching the position of individual in AVL tree.

user *user_rotate_right(user *root)
{
    if (root)
    {
        if (root->left)
        {
            user *temp = root->left;
            root->left = temp->right;
            temp->right = root;
            root->height = root->height - 2;
            root = temp;
        }
    }
    return root;
    }
    user *user_rotate_left(user *root)
{
    if (root)
    {
        if (root->right)
        {
            user *temp = root->right;
            root->right = temp->left;
            temp->left = root;
            root->height = root->height - 2;
            root = temp;
        }
    }
    return root;
}
user *user_balance_root(user *root)
{
    if (root)
    {
        int left = 0;
        if (root->left)
            left = root->left->height;
        int right = 0;
        if (root->right)
            right = root->right->height;

        if (left - right > 1)
        {
            root = user_rotate_right(root);
        }
        if (right - left > 1)
        {
            root = user_rotate_left(root);
        }
    }
    return root;
}
user *user_insert_avl(user *root, user *ins)
{
    if (root)
    {
        if (root->ID > ins->ID)
        {
            root->left = user_insert_avl(root->left, ins);
        }
        else if (root->ID < ins->ID)
        {
            root->right = user_insert_avl(root->right, ins);
        }

        else if (root->ID == ins->ID)
        {
            return root;
        }

        int left = 0;
        if (root->left)
            left = root->left->height;
        int right = 0;
        if (root->right)
            right = root->right->height;

        if (left > right)
            root->height = left + 1;
        else
            root->height = right + 1;

        root = user_balance_root(root);
    }
    else
    {
        root = ins;
        root->height = 1;
    }
    return root;
}
The above function user_rotate_left,user_rotate_right,user_balance_tree,user_insert_into_avl are AVL tree operations. Like in AVL tree if we want to add any node in tree first we will search for it's appropriate position(done by searching function) then we will calculate its left height and write height we balance it by doing rotate operations (done by rotate right,left,balanceroot) then we insert the node.The implementation of this algorithm is done by these functions.

user *create_user_tree(user *head)
{
    FILE *fp = fopen("individuals.txt", "r");
    char word[40];
    int c;
    while (fscanf(fp, "%s", word) == 1)
    {                                              // traversing the file
        user *temp = (user *)malloc(sizeof(user)); // creating space
        int c;
        // reading string from file
        temp->ID = parse(word); // changing it into int
        temp->group = 0;        // initially independent
        fscanf(fp, "%s", word);
        strcpy(temp->name, word); // setting word

        fscanf(fp, "%d", &c);
        temp->age = c; // setting age
        fscanf(fp, "%d", &c);
        temp->daily_goal = c; // Daily step goal
        for (int i = 0; i < 7; i++)
        {
            fscanf(fp, "%d", &c);
            temp->weekly_count[i] = c; // weekly count of steps
        }
        temp->left = NULL;
        temp->right = NULL; // individual node , later added at leaf

        head = user_insert_avl(head, temp); // inserts every entry , starting from NULL
    }

    fclose(fp);
    return head; // returning the starting node pointer
}
Create user function above contains file oprations like first we will open the file of individulas and then read the content in it and store in AVL tree.After scanning through whole file we will close it.

user *user_top_3(user *root, user *top_3[])
{
    if (root)
    {
        // Traverse left subtree
        user_top_3(root->left, top_3);

        // Update top 3
        int avg_steps = Avg_steps(root->weekly_count);
        int max1 = 0;
        if (top_3[0])
            max1 = Avg_steps(top_3[0]->weekly_count);
        int max2 = 0;
        if (top_3[1])
            max2 = Avg_steps(top_3[1]->weekly_count);
        int max3 = 0;
        if (top_3[2])
            max3 = Avg_steps(top_3[2]->weekly_count);
        if (avg_steps >= root->daily_goal)
        {
            if (avg_steps > max1)
            {
                top_3[2] = top_3[1];
                top_3[1] = top_3[0];
                top_3[0] = root;
            }
            else if (avg_steps>max2 && root->ID!=top_3[0]->ID)
            {
                top_3[2] = top_3[1];
                top_3[1] = root;
            }
            else if (avg_steps > max3 && (root->ID!=top_3[1]->ID && root->ID!=top_3[0]->ID))
            {
                top_3[2] = root;
            }
        }

        // Traverse right subtree
        user_top_3(root->right, top_3);
    }
    return root;
}
user_top_3 functions returns the top_3 users top_3 based on the average of their weekly step_counts.also the individual can be in top_3 if and only if it crosses it's weekly goal.so in these function we calculated the average of weekly step counts of individulas and created the top_3 users.

void Check_individual_rewards(user *root, user *top_3[])
{
    printf("Enter the ID of the user to be checked : ");
    int id;
    scanf("%d", &id);

    user *uptr = user_search(root, id);
	if(uptr){
   if(uptr==top_3[0]){
	printf("You got 100 points");
   }
   else if(uptr==top_3[1]){
	printf("You got 75 points");
}
else if(uptr==top_3[2]){
	printf("You got 50 points");
}
else{
	printf("you are not in top 3");
}
	}
	else{
		printf("You entered the wrong id");
	}
}    
This function gives the rewards earned by the individuals if the individual is at first position rewards earned by him is 100 if it as second its 75 if third then 50 and if he is not in top_3 no rewards are earned so for these function we have to traverse through whole the tree and check if the individual is matching with which member of array of top_3 .if it is not matching with anyone then the reawards earned by him is 0.

