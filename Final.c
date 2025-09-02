// Standart Input Output Header File
#include<stdio.h>

// Standart Library Header File
#include<stdlib.h>

// String Header File
#include<string.h>

// Unix Standart Header File (sleep function)
#include<unistd.h>

///////////////////////////////////////////////////////////////
//
//  User defined Macros
//
///////////////////////////////////////////////////////////////

// Max Restaurant Size
# define RESTAURANTSIZE 10

// Max Item Size
# define ITEMSIZE 10

///////////////////////////////////////////////////////////////
//
// Structure : LoginPage
// Use : Holds information about login Username and Password
//
///////////////////////////////////////////////////////////////
struct LoginPage
{
    char UserName[20];
    char PassWord[16];
    char FileName[20];
};

///////////////////////////////////////////////////////////////
//
// Structure : Item
// Use : Holds information about Items in Restaurant
//
///////////////////////////////////////////////////////////////
struct Item
{
    int No;
    char name[50];
    float price;
};

///////////////////////////////////////////////////////////////
//
// Structure : Restaurant (With DoublyLinearLinkedList)
// Use : Holds information about Restautant
//
///////////////////////////////////////////////////////////////
struct node
{
    int RId;
    char RName[50];
    struct Item menu[ITEMSIZE];
    int ItemCount;
    struct node *next;
    struct node *prev;
};

typedef struct node NODE;
typedef struct node *PNODE;
typedef struct node **PPNODE;

///////////////////////////////////////////////////////////////
//
// Structure : CartItem
// Use : Holds information about Items in Cart
//
///////////////////////////////////////////////////////////////
struct CartItem
{
    struct Item item;
    int quantity;
};

///////////////////////////////////////////////////////////////
//
// Function : CustomerAccount
// Use : Customer can login to the portal
//
///////////////////////////////////////////////////////////////
void CustomerAccount(struct LoginPage* loginpage)
{
    FILE *fp;
    char line[100], fileUser[20], filePass[16];

    fp = fopen("AccountLogin.txt", "r");

    printf("Enter your username: ");
    scanf("%s", loginpage->UserName);  

    printf("Enter your password: ");
    scanf("%s", loginpage->PassWord);

    while (fgets(line, sizeof(line), fp)) 
    {
        if (sscanf(line, "%[^,],%s", fileUser, filePass) == 2) 
        {
            if (strcmp(fileUser, loginpage->UserName) == 0 && 
                strcmp(filePass, loginpage->PassWord) == 0) 
            {
                fclose(fp);
                printf("Login successful...!\n");
            }
            else
            {
                printf("Login failed... Invalid username or password...!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(fp);
}

///////////////////////////////////////////////////////////////
//
// Function : RestaurantLogin
// Use : Customer can login to the portal
//
///////////////////////////////////////////////////////////////
void RestaurantLogin(struct LoginPage* loginpage)
{
    FILE *fp;
    char line[100], fileUser[20], filePass[16];

    fp = fopen("RestaurantLogin.txt", "r");

    printf("Enter your username: ");
    scanf("%s", loginpage->UserName);  

    printf("Enter your password: ");
    scanf("%s", loginpage->PassWord);

    while (fgets(line, sizeof(line), fp)) 
    {
        if (sscanf(line, "%[^,],%s", fileUser, filePass) == 2) 
        {
            if (strcmp(fileUser, loginpage->UserName) == 0 && 
                strcmp(filePass, loginpage->PassWord) == 0) 
            {
                fclose(fp);
                printf("Login successful...!\n");
            }
            else
            {
                printf("Login failed... Invalid username or password...!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(fp);
}

///////////////////////////////////////////////////////////////
//
// Function : InsertFirst
// Use : Inserting Restaurant Dynamically
//
///////////////////////////////////////////////////////////////
void InsertFirst(PPNODE first, int id, char *name, struct Item items[], int itemCount)
{
    PNODE newn = (PNODE)malloc(sizeof(NODE));
    newn->RId = id;
    strcpy(newn->RName, name);
    newn->ItemCount = itemCount;

    for (int i = 0; i < itemCount; i++)
        newn->menu[i] = items[i];

    newn->next = *first;
    newn->prev = NULL;

    if (*first != NULL)
        (*first)->prev = newn;

    *first = newn;
}

///////////////////////////////////////////////////////////////
//
// Function : InsertLast
// Use : Inserting Restaurant Dynamically
//
///////////////////////////////////////////////////////////////
void InsertLast(PPNODE first, int id, char *name, struct Item items[], int itemCount)
{
    PNODE newn = (PNODE)malloc(sizeof(NODE));
    newn->RId = id;
    strcpy(newn->RName, name);
    newn->ItemCount = itemCount;

    for (int i = 0; i < itemCount; i++)
        newn->menu[i] = items[i];

    newn->next = NULL;
    newn->prev = NULL;

    if (*first == NULL)
    {
        *first = newn;
    }
    else
    {
        PNODE temp = *first;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newn;
        newn->prev = temp;
    }
}

///////////////////////////////////////////////////////////////
//
// Function : ReadFromFile 
// Use : Load restaurants from file
//
///////////////////////////////////////////////////////////////
void ReadFromFile(PPNODE head, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    char line[200];
    int RId, itemNo, itemCount;
    char RName[50], itemName[50];
    float price;

    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\r\n")] = 0;  

        if (strncmp(line, "RId", 3) == 0)
        {
            if (sscanf(line, "RId %d | RName = \"%[^\"]\"", &RId, RName) == 2)
            {
                struct Item items[ITEMSIZE];
                itemCount = 0;

                while (fgets(line, sizeof(line), fp))
                {
                    line[strcspn(line, "\r\n")] = 0;

                    if (strchr(line, ';')) break;  

                    if (sscanf(line, "menu %d , \"%[^\"]\" , %f", 
                               &itemNo, itemName, &price) == 3)
                    {
                        items[itemCount].No = itemNo;
                        strcpy(items[itemCount].name, itemName);
                        items[itemCount].price = price;
                        itemCount++;
                    }
                }

                InsertLast(head, RId, RName, items, itemCount);
            }
        }
    }

    fclose(fp);
}

///////////////////////////////////////////////////////////////
//
// Function : ShowRestaurant
// Use : Show available restaurants
//
///////////////////////////////////////////////////////////////
void ShowRestaurant(PNODE first)
{
    printf("\n------ Available Restaurants ------\n");
    while (first != NULL)
    {
        printf("%d) %s\n", first->RId, first->RName);
        first = first->next;
    }
}

///////////////////////////////////////////////////////////////
//
// Function : ShowItems
// Use : Show available items of the specific restaurant
//
///////////////////////////////////////////////////////////////
void ShowItems(PNODE first, int iChoice)
{
    while (first != NULL)
    {
        if (first->RId == iChoice)
        {
            printf("\n------ Available Items ------\n");
            for (int i = 0; i < first->ItemCount; i++)
            {
                printf("%d) %s - Rs %.2f\n",
                       first->menu[i].No,
                       first->menu[i].name,
                       first->menu[i].price);
            }
            return;
        }
        first = first->next;
    }
}

///////////////////////////////////////////////////////////////
//
// Function : ShowCart
// Use : Show Items those are added in the cart
//
///////////////////////////////////////////////////////////////
void ShowCart(struct CartItem cart[], int iCount)
{
    float total = 0;
    printf("\n------ Your Cart ------\n");
    if (iCount == 0)
    {
        printf("Cart is empty...\n");
        return;
    }

    for (int i = 0; i < iCount; i++)
    {
        printf("%d. %s | Qty: %d | Price: Rs %.2f\n",
               i + 1, cart[i].item.name, cart[i].quantity,
               cart[i].item.price * cart[i].quantity);

        total += cart[i].item.price * cart[i].quantity;
    }
    printf("Total: Rs %.2f\n", total);
}

///////////////////////////////////////////////////////////////
//
// Function : AddToCart
// Use : Add items in the cart
//
///////////////////////////////////////////////////////////////
void AddToCart(struct CartItem cart[], int *CartCount, struct Item item, int Quantity)
{
    for (int i = 0; i < *CartCount; i++)
    {
        if (cart[i].item.No == item.No && 
    strcmp(cart[i].item.name, item.name) == 0)
        {
            cart[i].quantity += Quantity;
            printf("Quantity updated!\n");
            return;
        }
    }

    cart[*CartCount].item = item;
    cart[*CartCount].quantity = Quantity;
    (*CartCount)++;
    printf("Item added to cart!\n");
}

///////////////////////////////////////////////////////////////
//
// Function : RemoveItem
// Use : Use to remove item or reduce quantity of items 
//
///////////////////////////////////////////////////////////////
void RemoveItem(struct CartItem cart[], int* iCount)
{
    int choice, RemoveId, RemoveQuantity;

    if (*iCount == 0)
    {
        printf("Cart is empty...\n");
        return;
    }

    ShowCart(cart, *iCount);

    printf("1) Remove item completely\n");
    printf("2) Reduce quantity\n");
    scanf("%d", &choice);

    printf("Enter item number: ");
    scanf("%d", &RemoveId);

    if (choice == 1)
    {
        for (int i = RemoveId - 1; i < *iCount - 1; i++)
        {
            cart[i] = cart[i + 1];
        }
        (*iCount)--;
        printf("Item removed!\n");
    }
    else if (choice == 2)
    {
        printf("Enter quantity to reduce: ");
        scanf("%d", &RemoveQuantity);
        cart[RemoveId - 1].quantity -= RemoveQuantity;

        if (cart[RemoveId - 1].quantity <= 0) {
            for (int i = RemoveId - 1; i < *iCount - 1; i++)
            {
                cart[i] = cart[i + 1];
            }
            (*iCount)--;
        }
        printf("Quantity updated...!\n");
    }
}

///////////////////////////////////////////////////////////////
//
// Function : OtherRestaurant
// Use : Show other available restaurants
//
///////////////////////////////////////////////////////////////
void OtherRestaurant(PNODE first)
{
    printf("\n------ Available Restaurants ------\n");
    while (first != NULL)
    {
        printf("%d) %s\n", first->RId, first->RName);
        first = first->next;
    }
}

///////////////////////////////////////////////////////////////
//
// Function : EmptyCart
// Use : Use to delete added items
//
///////////////////////////////////////////////////////////////
void EmptyCart(struct CartItem cart[], int* iCount)
{
    for (int i = 0; i < *iCount; i++)
    {
        cart[i].item.No = 0;
        strcpy(cart[i].item.name, "");  
        cart[i].item.price = 0.0;
        cart[i].quantity = 0;
    }

    *iCount = 0;

    printf("Cart is empty...\n");
}

///////////////////////////////////////////////////////////////
//
// Function : Checkout
// Use : Use for checkout items
//
///////////////////////////////////////////////////////////////
float Checkout(struct CartItem cart[], int iCount)
{
    int i = 0;
    float Total = 0;

    printf("\n------ Checkout ------\n");
    if (iCount == 0) 
    {
        printf("Your cart is empty...\n");
        return 0;
    }

    for (i = 0; i < iCount; i++)
    {
        printf("%s x %d = Rs %.2f\n",
            cart[i].item.name, cart[i].quantity,
            cart[i].item.price * cart[i].quantity);

            Total += cart[i].item.price * cart[i].quantity;
    }
    float GST = Total * 0.18;
    Total += GST;

    printf("GST (18%%): Rs %.2f\n", GST);
    printf("Total Bill: Rs %.2f\n", Total);

    return Total;
}

///////////////////////////////////////////////////////////////
//
// Function : Apply Coupons
// Use : Use for apply coupons to the items
//
///////////////////////////////////////////////////////////////
float ApplyCoupons(struct CartItem cart[], int iCount)
{
    int i = 0, iChoice = 0;
    float Total = 0;

    printf("\n------ Apply Coupon ------\n");
    if (iCount == 0) 
    {
        printf("Your cart is empty...\n");
        return 0;
    }

    for (i = 0; i < iCount; i++)
    {
        printf("%s x %d = Rs %.2f\n",
            cart[i].item.name, cart[i].quantity,
            cart[i].item.price * cart[i].quantity);

            Total += cart[i].item.price * cart[i].quantity;
    }
    float GST = Total * 0.18;
    Total += GST;

    if (Total < 100)
    {
        printf("\n\nPlease add minimum 100 Rs to apply coupons...\n\n");
    }

    printf("GST (18%%): Rs %.2f\n", GST);
    printf("Total Bill: Rs %.2f\n", Total);

    if (Total > 100)
    {
        printf("\nApply Coupons...!\n\n");
        printf("Total price is greater than 100 then 40 Rs off... Apply Press 1\n");
        printf("Total price is greater than 250 then 125 Rs off... Apply Press 2\n");
        printf("Total price is greater than 499 then 175 Rs off... Apply Press 3\n");
        printf("Total price is greater than 999 then 299 Rs off... Apply Press 4\n");
        scanf("%d",&iChoice);

        switch (iChoice)
        {
            case 1:
                if (Total > 100)
                {
                    Total = Total - 40;
                    printf("\nTotal Bill: Rs %.2f\n", Total);
                }
                break;
            
            case 2:
                if (Total > 250)
                {
                    Total = Total - 125;
                    printf("\nTotal Bill: Rs %.2f\n", Total);
                }
                break;
            
            case 3:
                if (Total > 499)
                {
                    Total = Total - 175;
                    printf("\nTotal Bill: Rs %.2f\n", Total);
                }
                break;
            
            case 4:
                if (Total > 999)
                {
                    Total = Total - 299;
                    printf("\nTotal Bill: Rs %.2f\n", Total);
                }
                break;
            
            default:
                printf("Invalid Choice\n");
                break;
        }
    }
    return Total;
}

///////////////////////////////////////////////////////////////
//
// Function : InputRestaurantDetails
// Use : Add new restaurants and their items 
//
///////////////////////////////////////////////////////////////
void InputRestaurantDetails(struct node restaurant[], int RestaurantCount, char *filename, PPNODE head)
{
    FILE *fp = fopen(filename, "a");  
    

    for (int i = 0; i < RestaurantCount; i++)
    {
        printf("\nEnter details for Restaurant %d\n", i + 1);

        printf("Enter Restaurant Id: ");
        scanf("%d", &restaurant[i].RId);

        printf("Enter Restaurant Name: ");
        scanf(" %49[^\n]", restaurant[i].RName);

        printf("How many Items for Restaurant %s: ", restaurant[i].RName);
        scanf("%d", &restaurant[i].ItemCount);

        fprintf(fp, "\nRId %d | RName = \"%s\"\n", restaurant[i].RId, restaurant[i].RName);

        for (int j = 0; j < restaurant[i].ItemCount; j++)
        {
            printf("\nEnter details for Item %d of Restaurant %s\n", j + 1, restaurant[i].RName);

            printf("Enter Item number: ");
            scanf("%d", &restaurant[i].menu[j].No);

            printf("Enter Item name: ");
            scanf(" %49[^\n]", restaurant[i].menu[j].name);

            printf("Enter Item price: ");
            scanf("%f", &restaurant[i].menu[j].price);

            if (j < restaurant[i].ItemCount - 1)
            {
                fprintf(fp, "menu %d, \"%s\", %.2f,\n",
                        restaurant[i].menu[j].No,
                        restaurant[i].menu[j].name,
                        restaurant[i].menu[j].price);
            }
            else
            {
                fprintf(fp, "menu %d, \"%s\", %.2f\n",
                        restaurant[i].menu[j].No,
                        restaurant[i].menu[j].name,
                        restaurant[i].menu[j].price);
            }
        }

        fprintf(fp, ";\n");

        InsertLast(head, restaurant[i].RId, restaurant[i].RName, restaurant[i].menu, restaurant[i].ItemCount);
    }

    fclose(fp);
}

///////////////////////////////////////////////////////////////
//
// Function : DisplayRestaurantDetails
// Use : Display newly added restaurants and their items
//
///////////////////////////////////////////////////////////////
void DisplayRestaurantDetails(struct node restaurant[], int RestaurantCount)
{
    printf("\n--- Restaurant Details ---\n");
    for (int i = 0; i < RestaurantCount; i++)
    {
        printf("\nRestaurant Id: %d\n", restaurant[i].RId);
        printf("Restaurant Name: %s\n", restaurant[i].RName);

        printf("Items:\n");
        for (int j = 0; j < restaurant[i].ItemCount; j++)
        {
            printf("  Item %d: Number = %d, Name = %s, Price = %.2f\n", 
                   j + 1, 
                   restaurant[i].menu[j].No, 
                   restaurant[i].menu[j].name,
                   restaurant[i].menu[j].price);
        }
    }
}

///////////////////////////////////////////////////////////////
//
// Function : RemoveRestrauntFromFile
// Use : Remove a restaurant from linked list and file
//
///////////////////////////////////////////////////////////////
void RemoveRestrauntFromFile(PPNODE head, int RId, char *filename)
{
    PNODE temp = *head;
    PNODE target = NULL;
    PNODE FileData = NULL;

    if (temp->RId == RId)
    {
        *head = temp->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;

            free(temp);
            printf("Restaurant removed...!\n", RId);
        }
    }
    else
    {
        while (temp != NULL && temp->RId != RId)
            temp = temp->next;

        if (temp == NULL)
        {
            printf("Invalid Choice...!\n");
            exit(EXIT_FAILURE);
        }

        if (temp->prev != NULL)
        {
            temp->prev->next = temp->next;
        }

        if (temp->next != NULL)
        {
            temp->next->prev = temp->prev;
        }

        free(temp);
        printf("Restaurant removed...!\n", RId);
    }

    FILE *fp = fopen(filename, "w"); 

    FileData = *head;

    while (FileData != NULL)
    {
        fprintf(fp, "RId %d | RName = \"%s\"\n", 
               FileData->RId, FileData->RName);

        for (int j = 0; j < FileData->ItemCount; j++)
        {
            fprintf(fp, "menu %d, \"%s\", %.2f\n",
                    FileData->menu[j].No,
                    FileData->menu[j].name,
                    FileData->menu[j].price);
        }
        fprintf(fp, ";\n");
        FileData = FileData->next;
    }
    fclose(fp);
}

///////////////////////////////////////////////////////////////
//
// Function : ChaudhariCanteenMenu
// Use : Display and handle main page options
//
///////////////////////////////////////////////////////////////
void ChaudhariCanteenMenu(PPNODE head, struct LoginPage *loginpage)
{
// Initialized Variables
    int MainChoice, RestChoice, RestCount, InputRestChoice;

///////////////////////////////////////////////////////////////
//
// Main Page
//
///////////////////////////////////////////////////////////////
    printf("|----------------------------------------------|\n");
    printf("|------------- Chaudhari Canteen --------------|\n");
    printf("|----------------------------------------------|\n");

    printf("See available Restaurants as Guest...? Press 1: \n");
    printf("Customer Login...? Press 2: \n");
    printf("Add new Restaurant...? Press 3: \n");
    printf("Remove Restaurant...? Press 4: \n");
    printf("Exit..? Press 0: \n");

    printf("Enter your choice: ");
    scanf("%d", &MainChoice);

    if (MainChoice == 1)
    {
        system("cls");
        ShowRestaurant(*head);

        printf("Exit...? Press 0\n");
        printf("Select restaurant: ");
        scanf("%d", &RestChoice);
        if (RestChoice == 0)
        {
            exit(EXIT_SUCCESS);
        }
        ShowItems(*head, RestChoice);
    }
    else if (MainChoice == 2)
    {
        CustomerAccount(loginpage);
        system("cls");
        ShowRestaurant(*head);

        printf("Exit...? Press 0\n");
        printf("Select restaurant: ");
        scanf("%d", &RestChoice);
        if (RestChoice == 0)
        {
            exit(EXIT_SUCCESS);
        }
        ShowItems(*head, RestChoice);
    }
    else if (MainChoice == 3)
    {
        RestaurantLogin(loginpage);

        printf("How many Restaurants do you want to add :");
        scanf("%d", &RestCount);

        struct node restaurant[RESTAURANTSIZE];
        InputRestaurantDetails(restaurant, RestCount, "RestaurantNameMenu.txt", head);
        DisplayRestaurantDetails(restaurant, RestCount);

        printf("Continue to login...? Press 1\n");
        printf("Exit...? Press 0\n");
        scanf("%d", &InputRestChoice);

        if (InputRestChoice == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else if (InputRestChoice == 1)   
        {
            //Recursion to reload menu
            ChaudhariCanteenMenu(head, loginpage);  
        }
        else
        {
            printf("Invalid Choice...!\n");
        }
    }
    else if (MainChoice == 4)
    {
        RestaurantLogin(loginpage);

        int RemoveId;
        ShowRestaurant(*head);

        printf("Enter restaurant Id to delete restaurant: ");
        scanf("%d", &RemoveId);

        RemoveRestrauntFromFile(head, RemoveId, "RestaurantNameMenu.txt");
        sleep(3);

        ShowRestaurant(*head);
    }
    else if (MainChoice == 0)
    {
        printf("Thank you... Visit Again...!\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Invalid Choice\n");
        exit(EXIT_FAILURE);
    }
}

///////////////////////////////////////////////////////////////
//
// Function : MainMenuPage
// Use : Handles the main menu loop 
//
///////////////////////////////////////////////////////////////
void MainMenuPage(PNODE head, struct CartItem Cart[], int *CartCount)
{
// Declared NODE with NULL
    PNODE temp = NULL;

// Initialized Variables
    int iChoice, RestChoice, ItemId, Qty, OtherRestaurantChoice;

///////////////////////////////////////////////////////////////
//
// Menu Page
//
///////////////////////////////////////////////////////////////
    while (1)
    {
        printf("\n------- Main Menu -------\n");
        printf("1) Show Restaurants\n");
        printf("2) Show Items \n");
        printf("3) Add to Cart\n");
        printf("4) Show Cart\n");
        printf("5) CheckOut\n");
        printf("6) Remove Items From Cart..?\n");
        printf("7) Apply Coupons\n");
        printf("8) Select Other Restaurant\n");
        printf("9) Clear Screen\n");
        printf("0) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &iChoice);

        if (iChoice == 0)
        {
            printf("Thank you..!\n");
            break;
        }

        switch (iChoice)
        {
        case 1:
            ShowRestaurant(head);
            break;

        case 2:
            ShowRestaurant(head);
            printf("Enter Restaurant ID: ");
            scanf("%d", &RestChoice);
            ShowItems(head, RestChoice);
            break;

        case 3:
            ShowRestaurant(head);
            printf("Enter Restaurant ID: ");
            scanf("%d", &RestChoice);

            ShowItems(head, RestChoice);
            printf("Enter Item ID: ");
            scanf("%d", &ItemId);
            printf("Enter Quantity: ");
            scanf("%d", &Qty);

            temp = head;
            while (temp != NULL)
            {
                if (temp->RId == RestChoice && ItemId <= temp->ItemCount)
                {
                    AddToCart(Cart, CartCount, temp->menu[ItemId - 1], Qty);
                    break;
                }
                temp = temp->next;
            }
            break;

        case 4:
            ShowCart(Cart, *CartCount);
            break;

        case 5:
            Checkout(Cart, *CartCount);
            break;

        case 6:
            RemoveItem(Cart, CartCount);
            break;

        case 7: 
            ApplyCoupons(Cart, *CartCount);
            break;

        case 8: 
            ShowRestaurant(head);
            EmptyCart(Cart, CartCount);

            ShowRestaurant(head);

            printf("Enter Restaurant ID: ");
            scanf("%d", &OtherRestaurantChoice);
 
            ShowItems(head, OtherRestaurantChoice);

            break;

        case 9:
            system("cls");
            break;

        default:
            printf("Invalid choice!\n");
            exit(EXIT_FAILURE);
        }
    }
}

///////////////////////////////////////////////////////////////
//
// Entry Point Function (main)
//
///////////////////////////////////////////////////////////////
int main()
{
    PNODE head = NULL;
    struct CartItem Cart[50]; 
    struct LoginPage loginpage;
    int CartCount = 0; 

// Load restaurants from file
    ReadFromFile(&head, "RestaurantNameMenu.txt");

// Handle main menu 
    ChaudhariCanteenMenu(&head, &loginpage);

// Handle customer menu page 
    MainMenuPage(head, Cart, &CartCount);

    return 0;
}



