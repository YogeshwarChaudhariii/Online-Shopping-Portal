#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
// Use : Holds information about Login Username and Password
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
// Use : Holds information about Items in Restautant
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
// Structure : Restaurant
// Use : Holds information about Restautant
//
///////////////////////////////////////////////////////////////
struct Restaurant
{
    int RId;
    char RName[50];  
    int ItemCount; 
    struct Item menu[ITEMSIZE];
};

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
            if (strcmp(fileUser, loginpage->UserName) == 0 && strcmp(filePass, loginpage->PassWord) == 0) 
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
            if (strcmp(fileUser, loginpage->UserName) == 0 && strcmp(filePass, loginpage->PassWord) == 0) 
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
// Function : ShowRestaurant
// Use : Show available restaurants
//
///////////////////////////////////////////////////////////////
void ShowRestaurant(struct Restaurant restaurant[], int no)
{
    printf("------ Available Restaurants ------\n");
    for (int i = 0; i < no; i++)
    {
        printf("%d) %s\n", 
        restaurant[i].RId, 
        restaurant[i].RName);
    }
}

///////////////////////////////////////////////////////////////
//
// Function : ShowItems
// Use : Show available items of the specific restaurant
//
///////////////////////////////////////////////////////////////
void ShowItems(struct Restaurant rarr[], int iChoice)
{
    printf("------ Available Items ------\n");

    for (int i = 0; i < rarr[iChoice - 1].ItemCount; i++)
    {
        printf("%d) %s - Rs %.2f\n",
            rarr[iChoice - 1].menu[i].No, 
            rarr[iChoice - 1].menu[i].name, 
            rarr[iChoice - 1].menu[i].price);
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
// Use : Use for checkout the added items in the cart
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
void OtherRestaurant(struct Restaurant rarr[], int iChoice)
{
    printf("------ Available Items ------\n");

    for (int i = 0; i < rarr[iChoice - 1].ItemCount; i++)
    {
        printf("%d) %s - Rs %.2f\n",
            rarr[iChoice - 1].menu[i].No, 
            rarr[iChoice - 1].menu[i].name, 
            rarr[iChoice - 1].menu[i].price);
    }
}

///////////////////////////////////////////////////////////////
//
// Function : AddToCart
// Use : Add items in the cart
//
///////////////////////////////////////////////////////////////
void AddToCart(struct CartItem cart[], struct Restaurant rarr[], int * CartCount, int RestId, int ItemId, int Quantity)
{
    for (int i = 0; i < *CartCount; i++)
    {
        if (cart[i].item.No == ItemId && strcmp(cart[i].item.name, rarr[RestId - 1].menu[ItemId - 1].name) == 0)
        {
            cart[i].quantity += Quantity;

            printf("Quantity updated...!\n");
            return;
        }
    }

    cart[*CartCount].item = rarr[RestId - 1].menu[ItemId - 1];

    cart[*CartCount].quantity = Quantity;

    (*CartCount)++;

    printf("Item added to cart!\n");
}

///////////////////////////////////////////////////////////////
//
// Function : InputRestaurantDetails
// Use : Add new restaurants and their items
//
///////////////////////////////////////////////////////////////
void InputRestaurantDetails(struct Restaurant restaurant[], int RestaurantCount)
{
    for (int i = 0; i < RestaurantCount; i++)
    {
        printf("\nEnter details for Restaurant %d\n", i + 1);
        
        printf("Enter Restaurant Id: ");
        scanf("%d", &restaurant[i].RId);

        printf("Enter Restaurant Name: ");
        scanf(" %[^\n]", restaurant[i].RName);   

        printf("How many Items for Restaurant %s :", restaurant[i].RName);
        scanf("%d", &restaurant[i].ItemCount);

        for (int j = 0; j < restaurant[i].ItemCount; j++)
        {
            printf("\nEnter details for Item %d of Restaurant %s\n", j + 1, restaurant[i].RName);

            printf("Enter Item number: ");
            scanf("%d", &restaurant[i].menu[j].No);

            printf("Enter Item name: ");
            scanf(" %[^\n]", restaurant[i].menu[j].name);

            printf("Enter Item price: ");
            scanf("%f", &restaurant[i].menu[j].price);
        }
    }    
}

///////////////////////////////////////////////////////////////
//
// Function : DisplayRestaurantDetails
// Use : Display newly added restaurants and their items
//
///////////////////////////////////////////////////////////////
void DisplayRestaurantDetails(struct Restaurant restaurant[], int RestaurantCount)
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
// Entry Point Function (main)
//
///////////////////////////////////////////////////////////////
int main()
{

// Initialized LoginPage
    struct LoginPage loginpage;


// Initialized CartItems
    struct CartItem Cart[30];


// Initialized Variables
    int CartCount = 0;

    int iChoice, Id, Qty, RestaurantChoice, OtherRestChoice, RestCount, MainChoice;


// Initialized Restaurants
    struct Restaurant rarr[3];

///////////////////////////////////////////////////////////////
//
// Restaurant 1
//
///////////////////////////////////////////////////////////////
    rarr[0].RId = 1;
    strcpy(rarr[0].RName, "Good Food");
    rarr[0].ItemCount = 5;
    rarr[0].menu[0] = (struct Item){1, "Samosa", 25};
    rarr[0].menu[1] = (struct Item){2, "Kachori", 20};
    rarr[0].menu[2] = (struct Item){3, "Vadapav", 40};
    rarr[0].menu[3] = (struct Item){4, "Paneer", 50};
    rarr[0].menu[4] = (struct Item){5, "Kanda Bhaji", 90};

///////////////////////////////////////////////////////////////
//
// Restaurant 2
//
///////////////////////////////////////////////////////////////
    rarr[1].RId = 2;
    strcpy(rarr[1].RName, "Kakke da Paratha");
    rarr[1].ItemCount = 5;
    rarr[1].menu[0] = (struct Item){1, "Bharta", 125};
    rarr[1].menu[1] = (struct Item){2, "Biryani", 35};
    rarr[1].menu[2] = (struct Item){3, "Paratha", 60};
    rarr[1].menu[3] = (struct Item){4, "Lassi", 85};
    rarr[1].menu[4] = (struct Item){5, "Kanda Bhaji", 70};

///////////////////////////////////////////////////////////////
//
// Restaurant 3
//
///////////////////////////////////////////////////////////////
    rarr[2].RId = 3;
    strcpy(rarr[2].RName, "Home Meal");
    rarr[2].ItemCount = 5;
    rarr[2].menu[0] = (struct Item){1, "Roti", 15};
    rarr[2].menu[1] = (struct Item){2, "Kanda Pohe", 30};
    rarr[2].menu[2] = (struct Item){3, "Tikka Masala", 120};
    rarr[2].menu[3] = (struct Item){4, "Kofta", 150};
    rarr[2].menu[4] = (struct Item){5, "Dal Khichdi", 110};

///////////////////////////////////////////////////////////////
//
// Main Page
//
///////////////////////////////////////////////////////////////
    printf("------- Chaudhari Canteen ------\n\n");

    printf("See available Restaurants as Guest...? Press 1: \n");
    printf("Customer Login...? Press 2: \n");
    printf("Add new Restaurant...? Press 3: \n");
    printf("Exit..? Press 0: \n");

    printf("Enter your choice: \n");
    scanf("%d",&MainChoice);

    if (MainChoice == 1)
    {
        ShowRestaurant(rarr, 3);

        printf("Select restaurant: ");
        scanf("%d", &RestaurantChoice);

        ShowItems(rarr, RestaurantChoice);
    }
    
    else if (MainChoice == 2)
    {
        CustomerAccount(&loginpage);
    }

    else if (MainChoice == 3)
    {
        RestaurantLogin(&loginpage);

        printf("How many Restaurants do you want to add :");
        scanf("%d", &RestCount);

        struct Restaurant restaurant[RESTAURANTSIZE];

        InputRestaurantDetails(restaurant, RestCount);
        DisplayRestaurantDetails(restaurant, RestCount);

        exit(EXIT_SUCCESS);
    }

    else if (MainChoice == 0)
    {
        exit(EXIT_SUCCESS);
    }
    
    else
    {
        printf("Invalid Choice\n");
        exit(EXIT_FAILURE);
    }

///////////////////////////////////////////////////////////////
//
// Menu Page
//
///////////////////////////////////////////////////////////////
    while (1)
    {
        printf("------- Menu -------\n");
        printf("1) Add to Cart\n");
        printf("2) Show Cart\n");
        printf("3) Checkout\n");
        printf("4) Apply Coupons\n");
        printf("5) Remove Items From Cart\n");
        printf("6) Select Other Restaurant\n");
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
            ShowItems(rarr, RestaurantChoice);
            printf("Enter Item ID: ");
            scanf("%d", &Id);
            if (Id > rarr->ItemCount)
            {
                printf("Invalid choice\n");
                break;
            }
            printf("Enter Quantity: ");
            scanf("%d", &Qty);

            AddToCart(Cart, rarr, &CartCount, RestaurantChoice, Id, Qty);
            break;

        case 2:
            ShowCart(Cart, CartCount);
            break;

        case 3:
            Checkout(Cart, CartCount);
            break;

        case 4:
            ApplyCoupons(Cart, CartCount);
            break;

        case 5:
            RemoveItem(Cart, &CartCount);
            break;

        case 6:
            ShowRestaurant(rarr, 3);
            EmptyCart(Cart, &CartCount);

            printf("Select restaurant: ");
            scanf("%d", &OtherRestChoice);

            ShowItems(rarr, OtherRestChoice);
            RestaurantChoice = OtherRestChoice;
            break;

        default:
            printf("Invalid choice!\n");

            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
