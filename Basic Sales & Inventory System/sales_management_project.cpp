#ifdef _WIN32
#include<windows.h>
#endif
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

// ANSI Escape Color Codes for Visual Enhancements
const string COLOR_RESET   = "\033[0m";
const string COLOR_HEADER  = "\033[1;36m"; // Bright Cyan
const string COLOR_LABEL   = "\033[1;33m"; // Bright Yellow
const string COLOR_SUCCESS = "\033[1;32m"; // Bright Green
const string COLOR_ERROR   = "\033[1;31m"; // Bright Red
const string COLOR_TOTAL   = "\033[1;35m"; // Bright Magenta
const string COLOR_BOLD    = "\033[1m";

int main(){
#ifdef _WIN32
	// Enable ANSI escape sequence processing on Windows consoles
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &dwMode)) {
		SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}
#endif

	// Variable for storing menu selection
	int choice = 0;
	
	// Product management storage configuration
	int product_size=100;                           // Maximum capacity for products array
	string pr_code, product_code[product_size];      // Array storing unique product identification codes
	string product_name[product_size];               // Array storing product names
	int product_quantity[product_size],product_price[product_size]; // Arrays for stock count and unit prices
	int product_index=0,end;                         // product_index: tracks total registered products; end: loop continuation flag
	bool chk=false;                                  // Flag for uniqueness search and validation
	
	// Order management parallel array storage (Capacity: 100 order line items)
	string customer[100], order[100];                // Arrays for customer names and order identification numbers
	string pro_code[100], odr_pro_name[100], code_chk; // Arrays for line-item product codes and names, code_chk: search input
	int qty1,qty[100]={0}, order_index=0, index_of_prdct; // qty1: temporary qty input; qty: ordered quantity; order_index: line item counter
	
	// Main interactive application menu loop
	while (choice != 6){
		cout << COLOR_HEADER << "========================================================\n";
		cout << "||               SALES MANAGEMENT SYSTEM              ||\n";
		cout << "========================================================\n" << COLOR_RESET;
		cout << COLOR_LABEL << " [1]" << COLOR_RESET << " Products Entry      " << COLOR_LABEL << "[2]" << COLOR_RESET << " Products Display\n";
		cout << COLOR_LABEL << " [3]" << COLOR_RESET << " Orders Posting      " << COLOR_LABEL << "[4]" << COLOR_RESET << " Received Orders\n";
		cout << COLOR_LABEL << " [5]" << COLOR_RESET << " Sales Invoice       " << COLOR_LABEL << "[6]" << COLOR_RESET << " Exit System\n";
		cout << COLOR_HEADER << "--------------------------------------------------------\n" << COLOR_RESET;
		cout << COLOR_BOLD << "Enter your choice (1-6): " << COLOR_RESET;
		cin >> choice;
		system("cls"); // Clear terminal screen for visual consistency
		
		// -------------------------------------------------------------
		// OPTION 1: Product Entry System
		// -------------------------------------------------------------
		if (choice==1){			// Products entry module
			cout << COLOR_HEADER << "========================================================\n";
			cout << "||                 PRODUCT ENTRY SYSTEM               ||\n";
			cout << "========================================================\n\n" << COLOR_RESET;
			do{
				cout << COLOR_LABEL << "Enter Product Code: " << COLOR_RESET;
				cin >> pr_code;
				
				// Validation loop: Linear search to guarantee distinct product codes
				do{				
					for (int i=0; i<product_index; i++){	// Check existing products for duplicate code
						if(pr_code==product_code[i]){
							chk=true;
							break;
						}else{
							chk=false;
						}
					}
					if(chk==true){
						cout << COLOR_ERROR << ">> Duplicate code detected! Enter unique code: " << COLOR_RESET;
						cin >> pr_code;
					}
				}while(chk==true);
				
				// Store verified unique product details into parallel arrays
				product_code[product_index]=pr_code;
				cout << COLOR_LABEL << "Enter Product Name: " << COLOR_RESET;
				cin >> product_name[product_index];
				
				// Product price input validation: price must be greater than 0
				do{
					cout << COLOR_LABEL << "Enter Price ($): " << COLOR_RESET;
					cin >> product_price[product_index];
					if (product_price[product_index] <= 0) {
						cout << COLOR_ERROR << ">> Price must be greater than 0!\n" << COLOR_RESET;
					}
				}while(product_price[product_index] <= 0);
				
				cout << COLOR_LABEL << "Enter Initial Stock Quantity: " << COLOR_RESET;
				cin >> product_quantity[product_index];
				product_index++; // Increment total product inventory count
				
				cout << COLOR_SUCCESS << "\n--------------------------------------------------------\n";
				cout << ">> Product record added successfully!\n";
				cout << "--------------------------------------------------------\n" << COLOR_RESET;
				cout << COLOR_BOLD << "Add another product? (1 to Continue / 0 to Stop): " << COLOR_RESET;
				cin >> end;
				cout << COLOR_HEADER << "--------------------------------------------------------\n\n" << COLOR_RESET;
				if(end==0) break;
			}while(product_index<product_size);
	
		// -------------------------------------------------------------
		// OPTION 2: Product Printing / Inventory Display
		// -------------------------------------------------------------
		}else if (choice==2){		// Products display module
			cout << COLOR_HEADER << "========================================================\n";
			cout << "||                 INVENTORY PRODUCT LIST             ||\n";
			cout << "========================================================\n\n" << COLOR_RESET;
			if(product_index>0){
				// Header layout using setw and border formatting
				cout << COLOR_BOLD << "+------------+--------------------+------------+------------+\n";
				cout << "| " << left << setw(10) << "CODE" << "| " << setw(18) << "PRODUCT NAME" << "| " << setw(10) << "PRICE ($)" << "| " << setw(10) << "IN STOCK" << "|\n";
				cout << "+------------+--------------------+------------+------------+\n" << COLOR_RESET;
				for(int i=0; i<product_index; i++){
					cout << "| " << left << setw(10) << product_code[i] 
					     << "| " << setw(18) << product_name[i] 
					     << "| $" << right << setw(8) << product_price[i] << " "
					     << "| " << right << setw(10) << product_quantity[i] << " |\n";
				}
				cout << COLOR_BOLD << "+------------+--------------------+------------+------------+\n" << COLOR_RESET;
			}else{
				cout << COLOR_ERROR << ">> No products registered in inventory...\n" << COLOR_RESET;
			}
			cout << "\n";
	
		// -------------------------------------------------------------
		// OPTION 3: Order Posting / Transactions
		// -------------------------------------------------------------
		}else if (choice ==3){			// Orders posting module
			cout << COLOR_HEADER << "========================================================\n";
			cout << "||                    ORDER POSTING                   ||\n";
			cout << "========================================================\n\n" << COLOR_RESET;
			
			// Display available inventory catalog for user reference before ordering
			if(product_index>0){
				cout << COLOR_LABEL << "Available Product Inventory:\n" << COLOR_RESET;
				cout << COLOR_BOLD << "+------------+--------------------+------------+------------+\n";
				cout << "| " << left << setw(10) << "CODE" << "| " << setw(18) << "PRODUCT NAME" << "| " << setw(10) << "PRICE ($)" << "| " << setw(10) << "IN STOCK" << "|\n";
				cout << "+------------+--------------------+------------+------------+\n" << COLOR_RESET;
				for(int i=0; i<product_index; i++){
					cout << "| " << left << setw(10) << product_code[i] 
					     << "| " << setw(18) << product_name[i] 
					     << "| $" << right << setw(8) << product_price[i] << " "
					     << "| " << right << setw(10) << product_quantity[i] << " |\n";
				}
				cout << COLOR_BOLD << "+------------+--------------------+------------+------------+\n\n" << COLOR_RESET;
			}
			
			do{
				if(product_index==0){		// Guard clause: abort order posting if catalog is empty
					cout << COLOR_ERROR << ">> Please add products to inventory before posting orders!\n" << COLOR_RESET;
					break;
				}
				
				// Handle customer metadata (re-use header info if appending items to same order)
				if(end==0){					// New order header input
					cout << COLOR_LABEL << "\nEnter Order #: " << COLOR_RESET;
					cin >> order[order_index];
					cout << COLOR_LABEL << "Enter Customer Name: " << COLOR_RESET;
					cin >> customer[order_index];
				}else if(end==1){           // Multi-item order continuation: inherit order ID and customer name
					order[order_index]=order[order_index-1];
					customer[order_index]=customer[order_index-1];
				}
				
				cout << COLOR_LABEL << "Enter Product Code to Order: " << COLOR_RESET;
				cin >> code_chk;
				bool chk=false;
	
				// Linear search to verify requested product exists and capture array index
				for(int a=0; a<product_index; a++){
					if(code_chk==product_code[a]){		// Match product code to derive inventory index
						chk=true;						
						index_of_prdct=a;
						break;
					}
				}
	
				// Prompt loop until a valid existing product code is entered
				while(chk==false){		
					cout << COLOR_ERROR << ">> Product not found! Enter valid Product Code: " << COLOR_RESET;
					cin >> code_chk;
					for(int a=0; a<product_index; a++){
						if(code_chk==product_code[a]){
							chk=true;
							index_of_prdct=a;
							break;
						}else{
							chk=false;
						}
					}
				}
	
				// Map product metadata into order line item arrays
				pro_code[order_index]=code_chk;		
				odr_pro_name[order_index]=product_name[index_of_prdct];		
	
				// Quantity check: validate stock availability and deduct from inventory exactly once
				cout << COLOR_LABEL << "Enter Order Quantity: " << COLOR_RESET;
				cin >> qty1;						
				while(qty1 > product_quantity[index_of_prdct] || qty1 <= 0){
					cout << COLOR_ERROR << ">> Stock insufficient! Enter qty <= " << product_quantity[index_of_prdct] << " (and > 0): " << COLOR_RESET;
					cin >> qty1;
				}
				qty[order_index]=qty1;
				product_quantity[index_of_prdct]=product_quantity[index_of_prdct]-qty[order_index];
				order_index++; // Increment total recorded order line item index
	
				cout << COLOR_SUCCESS << "\n--------------------------------------------------------\n";
				cout << ">> Order line item recorded successfully!\n";
				cout << "--------------------------------------------------------\n" << COLOR_RESET;
				cout << COLOR_BOLD << "Add another item to this order / new order? (1 to Continue / 0 to End): " << COLOR_RESET;
				cin >> end;
				cout << COLOR_HEADER << "--------------------------------------------------------\n" << COLOR_RESET;
				if(end==0) break;
			}while (order_index<100);
	
		// -------------------------------------------------------------
		// OPTION 4: Received Orders Display
		// -------------------------------------------------------------
		}else if (choice==4){		// Order printing / summary module
			cout << COLOR_HEADER << "========================================================\n";
			cout << "||                  RECEIVED ORDERS LIST              ||\n";
			cout << "========================================================\n\n" << COLOR_RESET;

			if (order_index>0){
				cout << COLOR_BOLD << "+------------+--------------------+--------------------+------------+\n";
				cout << "| " << left << setw(10) << "ORDER #" << "| " << setw(18) << "CUSTOMER" << "| " << setw(18) << "PRODUCT" << "| " << setw(10) << "QTY" << "|\n";
				cout << "+------------+--------------------+--------------------+------------+\n" << COLOR_RESET;
				for(int j=0; j<order_index; j++){
					cout << "| " << left << setw(10) << order[j] 
					     << "| " << setw(18) << customer[j] 
					     << "| " << setw(18) << odr_pro_name[j] 
					     << "| " << right << setw(10) << qty[j] << " |\n";
				}
				cout << COLOR_BOLD << "+------------+--------------------+--------------------+------------+\n" << COLOR_RESET;
			}else{
				cout << COLOR_ERROR << ">> No orders recorded yet...\n" << COLOR_RESET;
			}
			cout << "\n";
	
		// -------------------------------------------------------------
		// OPTION 5: Sales Invoice & Revenue Summary
		// -------------------------------------------------------------
		}else if (choice==5){		// Sales invoice generation module
			cout << COLOR_HEADER << "========================================================\n";
			cout << "||            SALES INVOICES & REVENUE REPORT         ||\n";
			cout << "========================================================\n\n" << COLOR_RESET;
			
			string prev_order,nxt_order;
			bool price_chk=false;
			int price, tot_price=0, tot_earning=0, index4price;
			
			if(order_index==0) {
				cout << COLOR_ERROR << ">> No pending orders to calculate invoice...\n" << COLOR_RESET;
			}
			
			// Process each line item and group by order number
			for (int x=0; x<order_index; x++){
				// Group heading when encountering a new order ID
				if(order[x]!=prev_order){
					cout << COLOR_LABEL << "\n[ INVOICE FOR ORDER #" << order[x] << " | CUSTOMER: " << customer[x] << " ]\n" << COLOR_RESET;
					cout << COLOR_BOLD << "+------------+--------------------+------------+------------+\n";
					cout << "| " << left << setw(10) << "CODE" << "| " << setw(18) << "PRODUCT NAME" << "| " << setw(10) << "QTY" << "| " << setw(10) << "SUBTOTAL" << "|\n";
					cout << "+------------+--------------------+------------+------------+\n" << COLOR_RESET;
				}
				
				// Linear search to lookup product unit price
				for(int p=0; p<product_index; p++){		
					if(pro_code[x]==product_code[p]){
						price_chk=true;
						index4price=p;
						break;
					}
				}
				
				// Compute item subtotal and accumulate totals
				price=qty[x]*product_price[index4price];
				tot_price = tot_price + price;
				tot_earning = tot_earning + price;
				
				cout << "| " << left << setw(10) << pro_code[x] 
				     << "| " << setw(18) << odr_pro_name[x] 
				     << "| " << right << setw(10) << qty[x] << " "
				     << "| $" << right << setw(8) << price << " |\n";
				
				prev_order=order[x];
				nxt_order=order[x+1];
				
				// Detect boundary between distinct orders to print total order cost
				if(order[x] != nxt_order){
					cout << COLOR_BOLD << "+------------+--------------------+------------+------------+\n" << COLOR_RESET;
					cout << COLOR_TOTAL << "| ORDER TOTAL: $" << tot_price << COLOR_RESET << "\n";
					cout << COLOR_HEADER << "--------------------------------------------------------\n" << COLOR_RESET;
					tot_price=0; // Reset order accumulator for next order
				}
			}
			
			if (order_index > 0) {
				cout << COLOR_SUCCESS << "\n========================================================\n";
				cout << "|| GRAND TOTAL EARNINGS: $" << tot_earning << "\n";
				cout << "========================================================\n\n" << COLOR_RESET;
			}
			
		// -------------------------------------------------------------
		// OPTION 6: Exit System
		// -------------------------------------------------------------
		}else if (choice==6){
			cout << COLOR_SUCCESS << "Thank you for using Sales Management System. Exiting...\n" << COLOR_RESET;
			break;
		}else{
			cout << COLOR_ERROR << ">> Invalid selection! Please enter a choice between 1 and 6.\n" << COLOR_RESET;
		}
	
	}
	return 0;
}
