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
// Structure for Item, Restaurant, CartItem
//
///////////////////////////////////////////////////////////////
struct Item
{
    int No;
    char name[50];   
    float price;
};

struct Restaurant
{
    int RId;
    char RName[50];  
    int ItemCount; 
    struct Item menu[ITEMSIZE];
};

struct CartItem
{
    struct Item item;
    int quantity;
};

///////////////////////////////////////////////////////////////
//
// Function : ShowRestaurant
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
//
///////////////////////////////////////////////////////////////
float Checkout(struct CartItem cart[], int iCount)
{
    float Total = 0;

    printf("\n------ Checkout ------\n");
    if (iCount == 0) {
        printf("Your cart is empty...\n");
        return 0;
    }

    for (int i = 0; i < iCount; i++)
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
// Function : RemoveItem
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
    struct CartItem Cart[30];

    int CartCount = 0;

    int iChoice, Id, Qty, RestaurantChoice, OtherRestChoice, RestCount, AvaRestNewRest;

///////////////////////////////////////////////////////////////
//
// Initialized Restaurants
//
///////////////////////////////////////////////////////////////
    struct Restaurant rarr[3];

///////////////////////////////////////////////////////////////
//
// Restaurant 1
//
///////////////////////////////////////////////////////////////
    rarr[0].RId = 1;                                               
    strcpy(rarr[0].RName, "Good Food");
    rarr[0].menu[0].No = 1;
    strcpy(rarr[0].menu[0].name, "Samosa");
    rarr[0].menu[0].price = 25;

    rarr[0].menu[1].No = 2;
    strcpy(rarr[0].menu[1].name, "Kachori");
    rarr[0].menu[1].price = 20;

    rarr[0].menu[2].No = 3;
    strcpy(rarr[0].menu[2].name, "Vadapav");
    rarr[0].menu[2].price = 40;

    rarr[0].menu[3].No = 4;
    strcpy(rarr[0].menu[3].name, "Paneer");
    rarr[0].menu[3].price = 50;

    rarr[0].menu[4].No = 5;
    strcpy(rarr[0].menu[4].name, "Kanda Bhaji");
    rarr[0].menu[4].price = 90;
    rarr[0].ItemCount = 5;

///////////////////////////////////////////////////////////////
//
// Restaurant 2
//
///////////////////////////////////////////////////////////////
    rarr[1].RId = 2;
    strcpy(rarr[1].RName, "Kakke da Paratha");
    rarr[1].menu[0].No = 1;
    strcpy(rarr[1].menu[0].name, "Bharta");
    rarr[1].menu[0].price = 125;

    rarr[1].menu[1].No = 2;
    strcpy(rarr[1].menu[1].name, "Biryani");
    rarr[1].menu[1].price = 35;

    rarr[1].menu[2].No = 3;
    strcpy(rarr[1].menu[2].name, "Paratha");
    rarr[1].menu[2].price = 60;

    rarr[1].menu[3].No = 4;
    strcpy(rarr[1].menu[3].name, "Lassi");
    rarr[1].menu[3].price = 85;

    rarr[1].menu[4].No = 5;
    strcpy(rarr[1].menu[4].name, "Kanda Bhaji");
    rarr[1].menu[4].price = 70;
    rarr[1].ItemCount = 5;

///////////////////////////////////////////////////////////////
//
// Restaurant 3
//
///////////////////////////////////////////////////////////////
    rarr[2].RId = 3;
    strcpy(rarr[2].RName, "Home Meal");
    rarr[2].menu[0].No = 1;
    strcpy(rarr[2].menu[0].name, "Roti");
    rarr[2].menu[0].price = 15;

    rarr[2].menu[1].No = 2;
    strcpy(rarr[2].menu[1].name, "Kanda Pohe");
    rarr[2].menu[1].price = 30;

    rarr[2].menu[2].No = 3;
    strcpy(rarr[2].menu[2].name, "Tikka Masala");
    rarr[2].menu[2].price = 120;

    rarr[2].menu[3].No = 4;
    strcpy(rarr[2].menu[3].name, "Kofta");
    rarr[2].menu[3].price = 150;

    rarr[2].menu[4].No = 5;
    strcpy(rarr[2].menu[4].name, "Dal Khichdi");
    rarr[2].menu[4].price = 110;
    rarr[2].ItemCount = 5;

    printf("------- Marvellous Canteen ------\n\n");

    printf("See available Restaurants...? Press 1: \n");
    printf("Add new Restaurant...? Press 2: \n");
    printf("Exit..? Press 0: \n");
    printf("Enter your choice: \n");
    scanf("%d",&AvaRestNewRest);

    if (AvaRestNewRest == 1)
    {
        ShowRestaurant(rarr, 3);

    printf("Select restaurant: ");
    scanf("%d", &RestaurantChoice);

    ShowItems(rarr, RestaurantChoice);
    }
    else if (AvaRestNewRest == 2)
    {
        printf("How many Restaurants do you want to add :");
            scanf("%d", &RestCount);

            struct Restaurant restaurant[RESTAURANTSIZE];
            InputRestaurantDetails(restaurant, RestCount);
            DisplayRestaurantDetails(restaurant, RestCount);

            exit(EXIT_SUCCESS);
    }
    else if (AvaRestNewRest == 0)
    {
        exit(EXIT_SUCCESS);
    }
    
    else
    {
        printf("Invalid Choice\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("------- Menu -------\n");
        printf("1) Add to Cart\n");
        printf("2) Show Cart\n");
        printf("3) Checkout\n");
        printf("4) Remove Items From Cart\n");
        printf("5) Select Other Restaurant\n");
        printf("6) Add New Restaurant\n");
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
            printf("Enter Item ID: ");
            scanf("%d", &Id);
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
            RemoveItem(Cart, &CartCount);
            break;

        case 5:
            ShowRestaurant(rarr, 3);
            EmptyCart(Cart, &CartCount);

            printf("Select restaurant: ");
            scanf("%d", &OtherRestChoice);

            ShowItems(rarr, OtherRestChoice);
            RestaurantChoice = OtherRestChoice;
            break;

        case 6:
            printf("How many Restaurants do you want to add ):");
            scanf("%d", &RestCount);

            struct Restaurant restaurant[RESTAURANTSIZE];
            InputRestaurantDetails(restaurant, RestCount);
            DisplayRestaurantDetails(restaurant, RestCount);
            
            break;

        default:
            printf("Invalid choice!\n");

            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
