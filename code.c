#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CARS 100
#define MAX_CUSTOMERS 100
#define MAX_FEEDBACK 100
#define DAILY_RENTAL_RATE 50

// Structure Definitions
typedef struct {
    int car_id;
    char model[50];
    int available;
    float daily_rate;
    int rating_sum;
    int rating_count;
} Car;

typedef struct {
    int customer_id;
    char name[50];
    char phone[15];
} Customer;

typedef struct {
    int car_id;
    char customer_name[50];
    int days_rented;
    float total_charge;
    time_t rental_date;
} RentalHistory;

typedef struct {
    int car_id;
    char customer_name[50];
    int rating;
    char comments[100];
} Feedback;

// Global Variables
Car cars[MAX_CARS];
Customer customers[MAX_CUSTOMERS];
RentalHistory rental_history[MAX_CARS];
Feedback feedbacks[MAX_FEEDBACK];
int car_count = 0;
int customer_count = 0;
int rental_count = 0;
int feedback_count = 0;
float total_revenue = 0;

// Function Declarations
void addCar();
void viewAllCars();
void viewCarsByRate();
void viewAvailableCars();
void viewRentedCars();
void rentCar();
void returnCar();
void removeCar();
void searchCarByModel();
void searchCarById();
void searchCarByAvailability();
void updateCarDetails();
void calculateRentalCharges();
void viewRentalHistory();
void addCustomer();
void viewAllCustomers();
void updateCustomerDetails();
void removeCustomer();
void sortCarsByModel();
void sortCarsByAvailability();
void saveData();
void loadData();
void generateRentalReceipt(int car_id, char customer_name[], int days, float total_charge);
void displayMenu();
int adminLogin();
void clearRentalHistory();
void displayTotalRevenue();
void generateMonthlyReport();
void addFeedback();
void viewFeedback();
void overdueRentals();
void customerSupport();
void showRequiredDocuments();

int main() {
    if (!adminLogin()) {
        printf("Unauthorized access. Exiting...\n");
        return 0;
    }

    loadData();  // Load data from files
    int choice;

    // Main program loop with menu
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCar(); break;
            case 2: viewAllCars(); break;
            case 3: viewAvailableCars(); break;
            case 4: viewCarsByRate(); break;
            case 5: viewRentedCars(); break;
            case 6: rentCar(); break;
            case 7: returnCar(); break;
            case 8: removeCar(); break;
            case 9: searchCarByModel(); break;
            case 10: searchCarById(); break;
            case 11: searchCarByAvailability(); break;
            case 12: updateCarDetails(); break;
            case 13: calculateRentalCharges(); break;
            case 14: viewRentalHistory(); break;
            case 15: addCustomer(); break;
            case 16: viewAllCustomers(); break;
            case 17: updateCustomerDetails(); break;
            case 18: removeCustomer(); break;
            case 19: sortCarsByModel(); break;
            case 20: sortCarsByAvailability(); break;
            case 21: displayTotalRevenue(); break;
            case 22: generateMonthlyReport(); break;
            case 23: addFeedback(); break;
            case 24: viewFeedback(); break;
            case 25: overdueRentals(); break;
            case 26: customerSupport();break;
            case 27: showRequiredDocuments();break;
            case 28: saveData(); break;
            case 29: printf("Exiting...\n"); saveData(); return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Display Menu
void displayMenu() {
    printf("\n\\\\\Car Rental Management System\\\\\n");
    printf("1. Add Car\n");
    printf("2. View All Cars\n");
    printf("3. View Available Cars\n");
    printf("4. View Cars by Rate Range\n");
    printf("5. View Rented Cars\n");
    printf("6. Rent Car\n");
    printf("7. Return Car\n");
    printf("8. Remove Car\n");
    printf("9. Search Car by Model\n");
    printf("10. Search Car by ID\n");
    printf("11. Search Car by Availability\n");
    printf("12. Update Car Details\n");
    printf("13. Calculate Rental Charges\n");
    printf("14. View Rental History\n");
    printf("15. Add Customer\n");
    printf("16. View All Customers\n");
    printf("17. Update Customer Details\n");
    printf("18. Remove Customer\n");
    printf("19. Sort Cars by Model\n");
    printf("20. Sort Cars by Availability\n");
    printf("21. Display Total Revenue\n");
    printf("22. Generate Monthly Report\n");
    printf("23. Add Feedback\n");
    printf("24. View Feedback\n");
    printf("25. Overdue Rentals\n");
    printf("26. customer Support\n");
    printf("27. Required Documents\n");
    printf("28. Save Data\n");
    printf("29. Exit\n");
}

// Admin Login
int adminLogin() {
    char password[20];
    printf("Enter admin password to access: ");
    scanf("%s", password);

    if (strcmp(password, "Vanshik123@") == 0) {
        printf("Access granted.\n");
        return 1;
    } else {
        printf("Incorrect password. Access denied.\n");
        return 0;
    }
}

// Function to View Cars by Rental Rate Range
void viewCarsByRate() {
    float min_rate, max_rate;
    printf("Enter minimum rate: ");
    scanf("%f", &min_rate);
    printf("Enter maximum rate: ");
    scanf("%f", &max_rate);

    printf("Cars within the rate range $%.2f - $%.2f:\n", min_rate, max_rate);
    for (int i = 0; i < car_count; i++) {
        if (cars[i].daily_rate >= min_rate && cars[i].daily_rate <= max_rate) {
            printf("ID: %d, Model: %s, Rate: %.2f, Available: %s\n", cars[i].car_id, cars[i].model, cars[i].daily_rate, cars[i].available ? "Yes" : "No");
        }
    }
}

// Add Feedback Function
void addFeedback() {
    if (feedback_count >= MAX_FEEDBACK) {
        printf("Feedback storage is full.\n");
        return;
    }
    int car_id;
    printf("Enter car ID for feedback: ");
    scanf("%d", &car_id);

    int found = 0;
    for (int i = 0; i < car_count; i++) {
        if (cars[i].car_id == car_id) {
            found = 1;
            Feedback fb;
            fb.car_id = car_id;
            printf("Enter customer name: ");
            scanf("%s", fb.customer_name);
            printf("Enter rating (1-5): ");
            scanf("%d", &fb.rating);
            printf("Enter comments: ");
            scanf(" %[^\n]", fb.comments);

            feedbacks[feedback_count++] = fb;

            cars[i].rating_sum += fb.rating;
            cars[i].rating_count++;
            printf("Feedback added successfully!\n");
            return;
        }
    }
    if (!found) {
        printf("Car with ID %d not found.\n", car_id);
    }
}

// View Feedback Function
void viewFeedback() {
    printf("Feedback for Cars:\n");
    for (int i = 0; i < feedback_count; i++) {
        printf("Car ID: %d, Customer: %s, Rating: %d, Comments: %s\n", feedbacks[i].car_id, feedbacks[i].customer_name, feedbacks[i].rating, feedbacks[i].comments);
    }
}

// Display Overdue Rentals
void overdueRentals() {
    time_t now = time(NULL);
    printf("\nOverdue Rentals:\n");
    for (int i = 0; i < rental_count; i++) {
        int days_since_rental = (now - rental_history[i].rental_date) / (60 * 60 * 24);
        if (days_since_rental > rental_history[i].days_rented) {
            printf("Car ID: %d, Customer: %s, Days Rented: %d, Overdue by %d days\n", rental_history[i].car_id, rental_history[i].customer_name, rental_history[i].days_rented, days_since_rental - rental_history[i].days_rented);
        }
    }
}

// Generate Monthly Report (Extended)
void generateMonthlyReport() {
    printf("\nMonthly Rental Report:\n");
    printf("Car ID\tCustomer\tDays\tCharge\n");

    float avg_rating;
    for (int i = 0; i < rental_count; i++) {
        printf("%d\t%s\t\t%d\t$%.2f\n", rental_history[i].car_id, rental_history[i].customer_name, rental_history[i].days_rented, rental_history[i].total_charge);
    }

    printf("Total Revenue: $%.2f\n", total_revenue);

    for (int i = 0; i < car_count; i++) {
        if (cars[i].rating_count > 0) {
            avg_rating = (float) cars[i].rating_sum / cars[i].rating_count;
            printf("Car ID: %d, Model: %s, Average Rating: %.2f\n", cars[i].car_id, cars[i].model, avg_rating);
        }
    }
}

// Function to add a new car to the inventory
void addCar() {
    if (car_count >= MAX_CARS) {
        printf("Cannot add more cars, storage full.\n");
        return;
    }
    Car newCar;
    newCar.car_id = car_count + 1;  // Assign a unique car ID
    printf("Enter car model: ");
    scanf("%s", newCar.model);
    printf("Enter daily rental rate: ");
    scanf("%f", &newCar.daily_rate);
    newCar.available = 1;  // Newly added car is available

    cars[car_count++] = newCar;
    printf("Car added successfully! Car ID: %d\n", newCar.car_id);
}

// Function to add a customer to the system
void addCustomer() {
    if (customer_count >= MAX_CUSTOMERS) {
        printf("Cannot add more customers, storage full.\n");
        return;
    }
    Customer newCustomer;
    newCustomer.customer_id = customer_count + 1;
    printf("Enter customer name: ");
    scanf("%s", newCustomer.name);
    printf("Enter customer phone number: ");
    scanf("%s", newCustomer.phone);

    customers[customer_count++] = newCustomer;
    printf("Customer added successfully! Customer ID: %d\n", newCustomer.customer_id);
}

// Function to view all customers
void viewAllCustomers() {
    printf("\nAll Customers:\n");
    printf("ID\tName\t\tPhone\n");
    for (int i = 0; i < customer_count; i++) {
        printf("%d\t%s\t\t%s\n", customers[i].customer_id, customers[i].name, customers[i].phone);
    }
}

// Function to remove a customer
void removeCustomer() {
    int customer_id;
    printf("Enter customer ID to remove: ");
    scanf("%d", &customer_id);

    for (int i = 0; i < customer_count; i++) {
        if (customers[i].customer_id == customer_id) {
            for (int j = i; j < customer_count - 1; j++) {
                customers[j] = customers[j + 1];
            }
            customer_count--;
            printf("Customer removed successfully!\n");
            return;
        }
    }
    printf("Customer with ID %d not found.\n", customer_id);
}

// Function to sort cars by model name alphabetically
void sortCarsByModel() {
    for (int i = 0; i < car_count - 1; i++) {
        for (int j = i + 1; j < car_count; j++) {
            if (strcmp(cars[i].model, cars[j].model) > 0) {
                Car temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }
    }
    printf("Cars sorted by model name.\n");
}

// Function to sort cars by availability status
void sortCarsByAvailability() {
    for (int i = 0; i < car_count - 1; i++) {
        for (int j = i + 1; j < car_count; j++) {
            if (cars[i].available < cars[j].available) {
                Car temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }
    }
    printf("Cars sorted by availability status.\n");
}

// Function to generate a rental receipt
void generateRentalReceipt(int car_id, char customer_name[], int days, float total_charge) {
    printf("\nRental Receipt:\n");
    printf("Car ID: %d\n", car_id);
    printf("Customer: %s\n", customer_name);
    printf("Days Rented: %d\n", days);
    printf("Total Charge: $%.2f\n", total_charge);
}

// Function to save car and customer data to files
void saveData() {
    FILE *carFile = fopen("cars.dat", "wb");
    FILE *customerFile = fopen("customers.dat", "wb");

    fwrite(&car_count, sizeof(int), 1, carFile);
    fwrite(cars, sizeof(Car), car_count, carFile);

    fwrite(&customer_count, sizeof(int), 1, customerFile);
    fwrite(customers, sizeof(Customer), customer_count, customerFile);

    fclose(carFile);
    fclose(customerFile);
    printf("Data saved successfully.\n");
}

// Function to load car and customer data from files
void loadData() {
    FILE *carFile = fopen("cars.dat", "rb");
    FILE *customerFile = fopen("customers.dat", "rb");

    if (carFile != NULL) {
        fread(&car_count, sizeof(int), 1, carFile);
        fread(cars, sizeof(Car), car_count, carFile);
        fclose(carFile);
    }
    if (customerFile != NULL) {
        fread(&customer_count, sizeof(int), 1, customerFile);
        fread(customers, sizeof(Customer), customer_count, customerFile);
        fclose(customerFile);
    }
    printf("Data loaded successfully.\n");
}

// Remaining functions here: viewAllCars, viewAvailableCars, viewRentedCars, rentCar, returnCar, removeCar, searchCar
void viewAllCars() {
    printf("\nAll Cars:\n");
    printf("ID\tModel\t\tStatus\n");
    for (int i = 0; i < car_count; i++) {
        printf("%d\t%s\t\t%s\n", cars[i].car_id, cars[i].model, cars[i].available ? "Available" : "Rented");
    }
}

// Function to view only available cars for rent
void viewAvailableCars() {
    printf("\nAvailable Cars:\n");
    printf("ID\tModel\n");
    for (int i = 0; i < car_count; i++) {
        if (cars[i].available) {
            printf("%d\t%s\n", cars[i].car_id, cars[i].model);
        }
    }
}

// Function to view only rented cars
void viewRentedCars() {
    printf("\nRented Cars:\n");
    printf("ID\tModel\n");
    for (int i = 0; i < car_count; i++) {
        if (!cars[i].available) {
            printf("%d\t%s\n", cars[i].car_id, cars[i].model);
        }
    }
}
// Function to rent a car to a customer
void rentCar() {
    int car_id;
    char customer_name[50];
    int days;

    printf("Enter car ID to rent: ");
    scanf("%d", &car_id);
    printf("Enter customer name: ");
    scanf("%s", customer_name);
    printf("Enter number of days to rent: ");
    scanf("%d", &days);

    // Find the car in the list and check availability
    for (int i = 0; i < car_count; i++) {
        if (cars[i].car_id == car_id && cars[i].available) {
            cars[i].available = 0;  // Mark the car as rented

            // Calculate total charge using the car's daily rate
            float total_charge = days * cars[i].daily_rate;

            // Store rental information in history
            RentalHistory newRental;
            newRental.car_id = car_id;
            strcpy(newRental.customer_name, customer_name);
            newRental.days_rented = days;
            newRental.total_charge = total_charge;

            rental_history[rental_count++] = newRental;

            // Update total revenue
            total_revenue += total_charge;

            printf("Car rented successfully! Total charge: $%.2f\n", newRental.total_charge);
            return;
        }
    }

    // If no matching car was found or car is unavailable
    printf("Car not available for rent or ID not found.\n");
}



// Function to return a rented car
void returnCar() {
    int car_id;
    printf("Enter car ID to return: ");
    scanf("%d", &car_id);

    for (int i = 0; i < car_count; i++) {
        if (cars[i].car_id == car_id && !cars[i].available) {
            cars[i].available = 1;  // Mark the car as available
            printf("Car returned successfully!\n");
            return;
        }
    }
    printf("Car with ID %d not found or already available.\n", car_id);
}

// Function to remove a car from the inventory
void removeCar() {
    int car_id;
    printf("Enter car ID to remove: ");
    scanf("%d", &car_id);

    for (int i = 0; i < car_count; i++) {
        if (cars[i].car_id == car_id) {
            for (int j = i; j < car_count - 1; j++) {
                cars[j] = cars[j + 1];  // Shift remaining cars up in the array
            }
            car_count--;  // Decrement car count
            printf("Car removed successfully!\n");
            return;
        }
    }
    printf("Car with ID %d not found.\n", car_id);
}

// Function to search for a car by its model name
void searchCarByModel() {
    char model[50];
    printf("Enter car model to search: ");
    scanf("%s", model);

    printf("Cars matching model '%s':\n", model);
    printf("ID\tModel\tAvailable\n");
    for (int i = 0; i < car_count; i++) {
        if (strcasecmp(cars[i].model, model) == 0) {
            printf("%d\t%s\t%s\n", cars[i].car_id, cars[i].model, cars[i].available ? "Yes" : "No");
        }
    }
}
// Function to update the details of an existing car
void updateCarDetails() {
    int car_id;
    printf("Enter car ID to update: ");
    scanf("%d", &car_id);

    for (int i = 0; i < car_count; i++) {
        if (cars[i].car_id == car_id) {
            printf("Enter new model name: ");
            scanf("%s", cars[i].model);
            printf("Is car available? (1 for Yes, 0 for No): ");
            scanf("%d", &cars[i].available);
            printf("Car details updated successfully!\n");
            return;
        }
    }
    printf("Car with ID %d not found.\n", car_id);
}

// Function to calculate rental charges for a given car based on days
void calculateRentalCharges() {
    int car_id, days;
    printf("Available Cars:\n");
    for (int i = 0; i < car_count; i++) {
        printf("ID: %d, Model: %s, Rate: %.2f, Available: %s\n",
               cars[i].car_id, cars[i].model, cars[i].daily_rate,
               cars[i].available ? "Yes" : "No");
    }

    printf("\nEnter Car ID to calculate rental charges: ");
    scanf("%d", &car_id);

    // Search for the car by ID
    int found = 0;
    for (int i = 0; i < car_count; i++) {
        if (cars[i].car_id == car_id) {
            if (!cars[i].available) {
                printf("Car ID %d is currently not available for rent.\n", car_id);
                return;
            }

            found = 1;
            printf("Selected Car: %s (Daily Rate: $%.2f)\n", cars[i].model, cars[i].daily_rate);

            printf("Enter number of rental days: ");
            if (scanf("%d", &days) != 1 || days <= 0) {
                printf("Invalid input! Number of days must be a positive integer.\n");
                return;
            }

            // Calculate total charge
            float total_charge = cars[i].daily_rate * days;
            printf("Total rental charges for %d day(s): $%.2f\n", days, total_charge);
            return;
        }
    }

    if (!found) {
        printf("Car with ID %d not found.\n", car_id);
    }
}

// Function to view all rental history
void viewRentalHistory() {
    if (rental_count == 0) {
        printf("\nNo rental history available.\n");
        return;
    }

    printf("\n========== Rental History ==========\n");
    printf("Car ID\tCustomer\t\tDays\tCharge\n");
    printf("--------------------------------------------\n");

    float total_revenue = 0;
    for (int i = 0; i < rental_count; i++) {
        printf("%-7d %-16s %-7d $%.2f\n",
               rental_history[i].car_id,
               rental_history[i].customer_name,
               rental_history[i].days_rented,
               rental_history[i].total_charge);

        // Accumulate total revenue
        total_revenue += rental_history[i].total_charge;
    }

    printf("--------------------------------------------\n");
    printf("Total Rentals: %d\n", rental_count);
    printf("Total Revenue from Rentals: $%.2f\n", total_revenue);
    printf("============================================\n");
}

// Function to search a car by ID
void searchCarById() {
    int car_id;
    printf("Enter car ID to search: ");
    scanf("%d", &car_id);

    for (int i = 0; i < car_count; i++) {
        if (cars[i].car_id == car_id) {
            printf("Car Found: ID: %d, Model: %s, Available: %s, Rate: %.2f\n", cars[i].car_id, cars[i].model, cars[i].available ? "Yes" : "No", cars[i].daily_rate);
            return;
        }
    }
    printf("Car with ID %d not found.\n", car_id);
}

// Function to search cars by availability
void searchCarByAvailability() {
    int available;
    printf("Enter availability status (1 for Available, 0 for Rented): ");
    scanf("%d", &available);

    printf("Cars with Availability Status %d:\n", available);
    for (int i = 0; i < car_count; i++) {
        if (cars[i].available == available) {
            printf("ID: %d, Model: %s, Rate: %.2f\n", cars[i].car_id, cars[i].model, cars[i].daily_rate);
        }
    }
}

// Function to clear rental history
void clearRentalHistory() {
    rental_count = 0;
    printf("Rental history cleared.\n");
}

// Function to display total revenue
void displayTotalRevenue() {
    printf("Total Revenue from Rentals: $%.2f\n", total_revenue);
}
// Function to update customer details
void updateCustomerDetails() {
    int customer_id;
    printf("Enter customer ID to update: ");
    scanf("%d", &customer_id);

    // Search for the customer with the given ID
    for (int i = 0; i < customer_count; i++) {
        if (customers[i].customer_id == customer_id) {
            // Display current customer details
            printf("Current Details of Customer ID %d:\n", customer_id);
            printf("Name: %s\n", customers[i].name);
            printf("Phone: %s\n", customers[i].phone);

            // Update customer name
            printf("Enter new name (or press enter to keep current): ");
            getchar(); // to clear the newline left in the input buffer
            char new_name[50];
            fgets(new_name, sizeof(new_name), stdin);
            new_name[strcspn(new_name, "\n")] = '\0'; // remove newline character
            if (strlen(new_name) > 0) {  // Update only if a new name is entered
                strcpy(customers[i].name, new_name);
            }

            // Update customer phone number
            printf("Enter new phone number (or press enter to keep current): ");
            char new_phone[15];
            fgets(new_phone, sizeof(new_phone), stdin);
            new_phone[strcspn(new_phone, "\n")] = '\0'; // remove newline character
            if (strlen(new_phone) > 0) {  // Update only if a new phone number is entered
                strcpy(customers[i].phone, new_phone);
            }

            printf("Customer details updated successfully!\n");
            return;
        }
    }

    // If customer with given ID is not found
    printf("Customer with ID %d not found.\n", customer_id);
}
// Function to simulate customer support with predefined responses
void customerSupport() {
    char userInput[256];
    printf("Welcome to Customer Support! How can I assist you today?\n");

    // Display available options
    printf("You can ask questions about the following topics:\n");
    printf("1. Car rental pricing\n");
    printf("2. Tour options\n");
    printf("3. Pricing information\n");
    printf("4. Insurance coverage\n");
    printf("5. Rental locations\n");
    printf("6. Payment methods\n");
    printf("Type 'exit' to end the conversation.\n");

    while(1) {
        // Get input from the user
        printf("\nYou: ");
        fgets(userInput, sizeof(userInput), stdin);

        // Remove the newline character at the end of input (fgets includes it)
        userInput[strcspn(userInput, "\n")] = '\0';

        // Check if the user wants to exit the chat
        if (strcmp(userInput, "exit") == 0) {
            printf("Thank you for using Customer Support. Have a great day!\n");
            break;
        }

        // Check if the input is empty or just whitespace
        if (userInput[0] == '\0' || strspn(userInput, " \t") == strlen(userInput)) {
            printf("Support: Please enter a valid question or type 'exit' to end the conversation.\n");
            continue;
        }




        // Check for exact matches with predefined options
        if (strcmp(userInput, "car rental pricing") == 0) {
            printf("Support: Car rental prices depend on the car model and rental duration. Please choose a car to see the pricing.\n");
        }
        else if (strcmp(userInput, "tour options") == 0) {
            printf("Support: We offer customizable tours. You can select destinations and book a car for your tour.\n");
        }
        else if (strcmp(userInput, "pricing information") == 0) {
            printf("Support: Our daily rental rate starts at $50, and may vary depending on the car and duration.\n");
        }
        else if (strcmp(userInput, "insurance coverage") == 0) {
            printf("Support: We offer optional insurance coverage for $10 per day to cover damages during the rental.\n");
        }
        else if (strcmp(userInput, "rental locations") == 0) {
            printf("Support: Our rental locations are available in major cities. Please visit our website for more details.\n");
        }
        else if (strcmp(userInput, "payment methods") == 0) {
            printf("Support: We accept payments via credit card and PayPal. Payments are processed at the time of booking.\n");
        }
        else {
            // If the question doesn't match predefined ones
            printf("Support: Sorry, I didn't understand that. Please ask about car rentals, tours, pricing, insurance, locations, or payment\n for any other quires contact undersigned\n1. Vanshik Jain");
        }
    }
}
void showRequiredDocuments() {
    printf("To rent a car, you will need the following documents:\n");
    printf("1. A valid Driver's License\n");
    printf("   - Must be valid for at least 1 year.\n");
    printf("2. Proof of Identity (ID card or Passport)\n");
    printf("   - Must be government-issued.\n");
    printf("3. A valid Credit Card\n");
    printf("   - For security deposit and rental payment.\n");
    printf("4. Proof of Insurance (if not opting for the rental company's coverage)\n");
    printf("   - You can provide your own insurance policy or opt for the rental company's insurance.\n");
    printf("5. A valid Address Proof (in some cases)\n");
    printf("   - Utility bills or government-issued letters may be accepted.\n");
    printf("6. Age Requirement\n");
    printf("   - Car rental agencies require the driver to be at least 21 years old.\n");
    printf("\nPlease ensure you have all the required documents to complete the rental process smoothly.\n");
}
