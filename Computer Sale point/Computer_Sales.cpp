#ifdef _WIN32
#include<windows.h>
#endif
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cctype>
using namespace std;

// ANSI Color Codes for Visual Interface
const string COLOR_RESET   = "\033[0m";
const string COLOR_HEADER  = "\033[1;36m"; // Bright Cyan
const string COLOR_LABEL   = "\033[1;33m"; // Bright Yellow
const string COLOR_SUCCESS = "\033[1;32m"; // Bright Green
const string COLOR_ERROR   = "\033[1;31m"; // Bright Red
const string COLOR_TOTAL   = "\033[1;35m"; // Bright Magenta
const string COLOR_BOLD    = "\033[1m";

// -------------------------------------------------------------
// DATA STRUCTURES DEFINITION
// -------------------------------------------------------------

// Store Structure: Holds rich hardware inventory data in parallel arrays
struct Store{
	int str_no[50]={0};         // Serial / Item ID numbers
	int str_price[50];          // Unit price of computer/laptop (RS)
	int str_qty[50];            // Available stock quantity
	int str_RAM[50];            // Installed RAM capacity in GB
	int str_SSD[50];            // Installed SSD / NVMe storage in GB (0 = None)
	int str_HDD[50];            // Installed HDD storage in GB (0 = None)
	string str_company[50];     // Manufacturer Brand (e.g., HP, DELL, LENOVO, APPLE)
	string str_model[50];       // Computer model designation (e.g., Pavilion, ZBook, ThinkPad)
	string str_gen[50];         // Processor model (e.g., i7-8750H, i5-10300H, M1-8-Core)
	string str_gpu[50];         // Dedicated GPU (e.g., 4GB GTX 1050, 6GB RTX 2070, Integrated)
}str;

// Sales Structure: Holds customer purchase orders and sales transaction records
struct Sales{
	string customer[50];        // Customer full name
	string cnic[50];            // Formatted CNIC identifier (#####-#######-#)
	string ph_no[50];           // Formatted contact phone number (+92XXXXXXXXXX)
	string address[50];         // Customer delivery address
	string sale_company[50];    // Purchased computer manufacturer brand
	string sale_model[50];      // Purchased computer model designation
	string sale_gen[50];        // Purchased processor model
	string sale_gpu[50];        // Purchased dedicated GPU specification
	int sale_qty[50];           // Number of units purchased
	int sale_price[50];         // Total calculated sale price for transaction line item
	int sale_RAM[50];           // Final RAM configuration in GB (including upgrades)
	int sale_SSD[50];           // Final SSD NVMe capacity in GB (including upgrades)
	int sale_HDD[50];           // Final HDD storage capacity in GB
}sls;

// -------------------------------------------------------------
// FUNCTION PROTOTYPES
// -------------------------------------------------------------
void Menu();                            // Displays main user interface choice options
void storeAddition(int*);               // Appends new computer hardware stock items
void storeUpdation(int);                // Edits existing hardware attributes by serial number
void storeDeletion(int*);               // Deletes hardware entry from inventory by serial number
void storeData(int);                    // Displays tabulated active inventory catalog
void salesInfo(int*, int);              // Captures customer orders, processes upgrades & appends to file
void salesReport(int);                  // Generates single-customer or store-wide sales report
void printHeader();                     // Renders corporate application header banner
void saveStoreData(int);                // Persists runtime inventory array state to store.txt
void saveSalesData(int);                // Persists runtime sales array state to sales.txt
string formatSSD(int);                 // Helper to format SSD capacity for screen output
string formatHDD(int);                 // Helper to format HDD capacity for screen output

// -------------------------------------------------------------
// MAIN PROGRAM EXECUTION ENTRY POINT
// -------------------------------------------------------------
int main(){
#ifdef _WIN32
	// Enable ANSI escape sequence processing on Windows consoles
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &dwMode)) {
		SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}
#endif

	int choice, index=0, sales_index=0;
	printHeader();
	
	// ---------------------------------------------------------
	// FILE HANDLING 1: Load Inventory Data from "store.txt"
	// ---------------------------------------------------------
	ifstream store("store.txt", ios::in);
	string gen, gpu, Ram, Ssd, Hdd, Price, Qty;
	while(store >> str.str_company[index] >> str.str_model[index] >> gen >> gpu >> Ram >> Ssd >> Hdd >> Price >> Qty){
		str.str_no[index] = index+1; // Assign 1-indexed serial number
		
		for (int i=0; i<gen.length(); i++){
			if(gen[i] == '-'){
				gen[i] = ' ';
			}
		}
		str.str_gen[index] = gen;

		for (int i=0; i<gpu.length(); i++){
			if(gpu[i] == '-'){
				gpu[i] = ' ';
			}
		}
		str.str_gpu[index] = gpu;
		
		istringstream CRAM(Ram);
		istringstream CSSD(Ssd);
		istringstream CHDD(Hdd);
		istringstream CPrc(Price);
		istringstream CQTY(Qty);

		CRAM >> str.str_RAM[index];
		CSSD >> str.str_SSD[index];
		CHDD >> str.str_HDD[index];
		CPrc >> str.str_price[index];
		CQTY >> str.str_qty[index];
		index++; // Increment stored inventory count
	}
	store.close();

	// ---------------------------------------------------------
	// FILE HANDLING 2: Load Sales Records from "sales.txt"
	// ---------------------------------------------------------
	ifstream sales_input("sales.txt", ios::in);
	string v_ram, v_ssd, v_hdd, v_qty, v_price;
	while(sales_input >> sls.customer[sales_index] >> sls.cnic[sales_index] >> sls.ph_no[sales_index] >> sls.address[sales_index] >>
		sls.sale_company[sales_index] >> sls.sale_model[sales_index] >> sls.sale_gen[sales_index] >> sls.sale_gpu[sales_index] >>
		v_ram >> v_ssd >> v_hdd >> v_qty >> v_price){

		if(!sls.customer[sales_index].empty()){
			istringstream C_RAM(v_ram.substr(0, v_ram.length()-2));		
			istringstream C_SSD(v_ssd.substr(0, v_ssd.length()-2));
			istringstream C_HDD(v_hdd.substr(0, v_hdd.length()-2));
			istringstream C_QTY(v_qty);
			istringstream C_PRC(v_price);

			C_RAM >> sls.sale_RAM[sales_index];
			C_SSD >> sls.sale_SSD[sales_index];
			C_HDD >> sls.sale_HDD[sales_index];
			C_QTY >> sls.sale_qty[sales_index];
			C_PRC >> sls.sale_price[sales_index];
			
			string tmp_name = sls.customer[sales_index];
			for(int i=0; i<tmp_name.length(); i++){
				if(tmp_name[i]=='-'){
					tmp_name[i]=' ';
				}
			}
			sls.customer[sales_index] = tmp_name;
			
			string tmp_gen = sls.sale_gen[sales_index];
			for(int i=0; i<tmp_gen.length(); i++){
				if(tmp_gen[i]=='-'){
					tmp_gen[i]=' ';
				}
			}
			sls.sale_gen[sales_index] = tmp_gen;

			string tmp_gpu = sls.sale_gpu[sales_index];
			for(int i=0; i<tmp_gpu.length(); i++){
				if(tmp_gpu[i]=='-'){
					tmp_gpu[i]=' ';
				}
			}
			sls.sale_gpu[sales_index] = tmp_gpu;
			
			bool found_match = false;
			int qty_id = 0;
			for(int j=0; j<index; j++){
				if(sls.sale_company[sales_index]==str.str_company[j] && sls.sale_model[sales_index]==str.str_model[j] && 
				sls.sale_gen[sales_index]==str.str_gen[j] && sls.sale_gpu[sales_index]==str.str_gpu[j]){
					qty_id = j;
					found_match = true;
					break;
				}
			}
			if(found_match){
				str.str_qty[qty_id] -= sls.sale_qty[sales_index];
			}
			sales_index++;
		}
	}
	sales_input.close();

	// ---------------------------------------------------------
	// INTERACTIVE MAIN MENU LOOP
	// ---------------------------------------------------------
	do{
		Menu();
		cin>>choice;
		system("cls");
		
		printHeader();
		
		if(choice == 1){
			storeAddition(&index);          // Module 1: Add new stock items
		}else if(choice == 2){
			cout << COLOR_LABEL << "\n[ INVENTORY RECORD UPDATION ]\n" << COLOR_RESET;
			cout << COLOR_HEADER << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;
			storeData(index);
			storeUpdation(index);           // Module 2: Edit existing stock item
		}else if(choice == 3){
			cout << COLOR_LABEL << "\n[ INVENTORY RECORD DELETION ]\n" << COLOR_RESET;
			cout << COLOR_HEADER << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;
			storeData(index);
			storeDeletion(&index);          // Module 3: Remove stock item
		}else if(choice == 4){
			cout << COLOR_LABEL << "\n[ INVENTORY STOCK CATALOG ]\n" << COLOR_RESET;
			cout << COLOR_HEADER << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;
			storeData(index);               // Module 4: Display inventory catalog
		}else if(choice == 5){
			salesInfo(&sales_index, index); // Module 5: Customer order entry & upgrades
		}else if(choice == 6){
			salesReport(sales_index);       // Module 6: Generate invoices & total revenue
		}
		
		if(choice != 7){
			cout<<endl;
			system("pause");
			system("cls");
			printHeader();
		}
	}while(choice != 7);
	
	// Persist all runtime array changes (additions, edits, deletions, sales) to store.txt and sales.txt
	saveStoreData(index);
	saveSalesData(sales_index);
	
	cout << COLOR_SUCCESS << "\n>> All data saved. Thank you for using Nexus Tech Computer Systems. System exiting...\n" << COLOR_RESET;
	return 0;
}

// Helper function: format SSD for display
string formatSSD(int ssd_gb){
	if(ssd_gb <= 0) return "None";
	return to_string(ssd_gb) + " GB";
}

// Helper function: format HDD for display
string formatHDD(int hdd_gb){
	if(hdd_gb <= 0) return "None";
	if(hdd_gb >= 1024) return to_string(hdd_gb / 1024) + " TB";
	return to_string(hdd_gb) + " GB";
}

// -------------------------------------------------------------
// USER-DEFINED FUNCTION IMPLEMENTATIONS
// -------------------------------------------------------------

// Display corporate header banner (143 chars width)
void printHeader(){
	cout << COLOR_HEADER << "===============================================================================================================================================\n";
	cout << "||                                               NEXUS TECH COMPUTER SYSTEMS (PVT) LTD.                                                      ||\n";
	cout << "||                                             Enterprise Inventory & Point of Sale System                                                   ||\n";
	cout << "===============================================================================================================================================\n" << COLOR_RESET;
}

// Display main menu options (143 chars width)
void Menu(){
	cout << COLOR_LABEL << " [1]" << COLOR_RESET << " Add Inventory Stock     " << COLOR_LABEL << "[2]" << COLOR_RESET << " Update Inventory      " << COLOR_LABEL << "[3]" << COLOR_RESET << " Delete Stock Item\n";
	cout << COLOR_LABEL << " [4]" << COLOR_RESET << " View Store Catalog     " << COLOR_LABEL << "[5]" << COLOR_RESET << " Post Sales Order     " << COLOR_LABEL << "[6]" << COLOR_RESET << " Sales Reports & Invoices\n";
	cout << COLOR_LABEL << " [7]" << COLOR_RESET << " Exit System & Save Data\n";
	cout << COLOR_HEADER << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;
	cout << COLOR_BOLD << "Enter your selection (1-7): " << COLOR_RESET;
}

// Add new hardware item into inventory
void storeAddition(int *index){
	char further='y';
	cout << COLOR_LABEL << "\n[ INVENTORY STOCK ADDITION ]\n" << COLOR_RESET;
	cout << COLOR_HEADER << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;
	while(further == 'y' || further == 'Y'){
		str.str_no[*index] = str.str_no[*index-1]+1;
		cout << COLOR_LABEL << "\nEnter PC Manufacturer Brand (e.g., DELL, HP, LENOVO, APPLE): " << COLOR_RESET;
		string company;
		cin>>company;
		
		for(int i=0; i<company.length(); i++){
			company[i] = toupper(company[i]);
		}
		str.str_company[*index] = company;
		
		cout << COLOR_LABEL << "Enter Laptop Model (e.g., Pavilion-15, ZBook-15): " << COLOR_RESET;
		cin>>str.str_model[*index];
		cout << COLOR_LABEL << "Enter Processor Model (e.g., i7-8750H, i5-10300H): " << COLOR_RESET;
		cin.ignore();
		getline(cin,str.str_gen[*index]);
		cout << COLOR_LABEL << "Enter Dedicated GPU (e.g., 4GB-GTX-1050 or Integrated): " << COLOR_RESET;
		getline(cin,str.str_gpu[*index]);
		cout << COLOR_LABEL << "Enter Installed RAM (GB): " << COLOR_RESET;
		cin>>str.str_RAM[*index];
		cout << COLOR_LABEL << "Enter Installed SSD / NVMe Storage (GB, 0 if None): " << COLOR_RESET;
		cin>>str.str_SSD[*index];
		cout << COLOR_LABEL << "Enter Installed Hard Disk HDD Storage (GB, 0 if None): " << COLOR_RESET;
		cin>>str.str_HDD[*index];
		cout << COLOR_LABEL << "Enter Unit Price (RS.): " << COLOR_RESET;
		cin>>str.str_price[*index];
		cout << COLOR_LABEL << "Enter Initial Stock Quantity: " << COLOR_RESET;
		cin>>str.str_qty[*index];
		*index +=1;
		
		cout << COLOR_SUCCESS << "\n>> Record added to inventory successfully!\n" << COLOR_RESET;
		cout << COLOR_BOLD << "Add another product? (y/n): " << COLOR_RESET;
		cin>>further;
	}
}

// Update specific fields of an inventory item by serial number
void storeUpdation(int index){
	int sr_no, update_id = 0, update;
	cout << COLOR_LABEL << "\nEnter Serial No. (Sr.No) to update: " << COLOR_RESET;
	cin>>sr_no;
	
	for(int i=0; i<index; i++){
		if(sr_no == str.str_no[i]){
			update_id = i;
			break;
		}
	}
	
	do{
		cout << COLOR_LABEL << "\nSelect Field to Update:\n" << COLOR_RESET;
		cout << "1. Brand/Company   2. Model Designation  3. Processor Model\n";
		cout << "4. Dedicated GPU   5. RAM (GB)           6. SSD / NVMe (GB)\n";
		cout << "7. HDD (GB)        8. Price (RS.)        9. Stock Quantity\n";
		cout << "10. Complete & Finish Updation\n";
		cout << COLOR_BOLD << "-> Option (1-10): " << COLOR_RESET;
		cin>>update;
		if(update == 1){
			cout << COLOR_LABEL << "Updating Brand (" << str.str_company[update_id] << ") to: " << COLOR_RESET;
			cin>>str.str_company[update_id];
		}else if(update == 2){
			cout << COLOR_LABEL << "Updating Model (" << str.str_model[update_id] << ") to: " << COLOR_RESET;
			cin>>str.str_model[update_id];
		}else if(update == 3){
			cout << COLOR_LABEL << "Updating Processor (" << str.str_gen[update_id] << ") to: " << COLOR_RESET;
			cin.ignore();
			getline(cin,str.str_gen[update_id]);
		}else if(update == 4){
			cout << COLOR_LABEL << "Updating Dedicated GPU (" << str.str_gpu[update_id] << ") to: " << COLOR_RESET;
			cin.ignore();
			getline(cin,str.str_gpu[update_id]);
		}else if(update == 5){
			cout << COLOR_LABEL << "Updating RAM (" << str.str_RAM[update_id] << " GB) to: " << COLOR_RESET;
			cin>>str.str_RAM[update_id];
		}else if(update == 6){
			cout << COLOR_LABEL << "Updating SSD Storage (" << str.str_SSD[update_id] << " GB) to: " << COLOR_RESET;
			cin>>str.str_SSD[update_id];
		}else if(update == 7){
			cout << COLOR_LABEL << "Updating HDD Storage (" << str.str_HDD[update_id] << " GB) to: " << COLOR_RESET;
			cin>>str.str_HDD[update_id];
		}else if(update == 8){
			cout << COLOR_LABEL << "Updating Unit Price (RS. " << str.str_price[update_id] << ") to RS.: " << COLOR_RESET;
			cin>>str.str_price[update_id];
		}else if(update == 9){
			cout << COLOR_LABEL << "Updating Quantity (" << str.str_qty[update_id] << ") to: " << COLOR_RESET;
			cin>>str.str_qty[update_id];
		}
	}while(update != 10);
	cout << COLOR_SUCCESS << ">> Inventory record updated successfully!\n" << COLOR_RESET;
}

// Display formatted table of store inventory (143 chars width)
void storeData(int index){
	if(index == 0){
		cout << COLOR_ERROR << "\n>> No inventory records found in system catalog...\n" << COLOR_RESET;
	}else{
		cout << COLOR_BOLD << "+-------+------------+-----------------------+-----------------+-----------------------+---------+---------+---------+---------------+-------+\n";
		cout << "| " << left << setw(6) << "SR NO" << "| " << setw(11) << "BRAND" << "| " << setw(22) << "MODEL" << "| " << setw(16) << "PROCESSOR" << "| " << setw(22) << "DEDICATED GPU" << "| " << setw(8) << "RAM" << "| " << setw(8) << "SSD NVME" << "| " << setw(8) << "HDD" << "| " << setw(14) << "PRICE (RS)" << "| " << setw(6) << "QTY" << "|\n";
		cout << "+-------+------------+-----------------------+-----------------+-----------------------+---------+---------+---------+---------------+-------+\n" << COLOR_RESET;
		for(int i=0; i<index; i++){
			cout << "| " << left << setw(6) << str.str_no[i]
			     << "| " << setw(11) << str.str_company[i]
			     << "| " << setw(22) << str.str_model[i]
			     << "| " << setw(16) << str.str_gen[i]
			     << "| " << setw(22) << str.str_gpu[i]
			     << "| " << right << setw(5) << str.str_RAM[i] << " GB "
			     << "| " << right << setw(8) << formatSSD(str.str_SSD[i]) << " "
			     << "| " << right << setw(8) << formatHDD(str.str_HDD[i]) << " "
			     << "| RS." << right << setw(10) << str.str_price[i] << " "
			     << "| " << right << setw(5) << str.str_qty[i] << " |\n";
		}
		cout << COLOR_BOLD << "+-------+------------+-----------------------+-----------------+-----------------------+---------+---------+---------+---------------+-------+\n" << COLOR_RESET;
	}
}

// Delete inventory item by serial number (shifts elements left)
void storeDeletion(int *index){
	int sr_no, delete_id = 0;
	cout << COLOR_LABEL << "\nEnter Serial No. (Sr.No) to delete: " << COLOR_RESET;
	cin>>sr_no;
	
	for(int i=0; i<*index; i++){
		if(sr_no == str.str_no[i]){
			delete_id = i;
			break;
		}
	}
	
	for(int j=delete_id; j<*index -1; j++){
		str.str_company[j] = str.str_company[j+1];
		str.str_model[j] = str.str_model[j+1];
		str.str_gen[j] = str.str_gen[j+1];
		str.str_gpu[j] = str.str_gpu[j+1];
		str.str_RAM[j] = str.str_RAM[j+1];
		str.str_SSD[j] = str.str_SSD[j+1];
		str.str_HDD[j] = str.str_HDD[j+1];
		str.str_price[j] = str.str_price[j+1];
		str.str_qty[j] = str.str_qty[j+1];
	}
	*index -=1;
	cout << COLOR_SUCCESS << ">> Item deleted from inventory successfully!\n" << COLOR_RESET;
}

// Process customer purchase, handle RAM/SSD hardware upgrades & write transaction to file
void salesInfo(int *index, int str_index){
	cout << COLOR_LABEL << "\n[ CUSTOMER ORDER & SALES TRANSACTION ]\n" << COLOR_RESET;
	cout << COLOR_HEADER << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;
	char further = 'n';
	cout << COLOR_LABEL << "Enter Customer Full Name: " << COLOR_RESET;
	string temp;
	cin.ignore();
	getline(cin,temp);
	
	for(int a=0; a<temp.length(); a++){
		temp[a] = toupper(temp[a]);
	}
	sls.customer[*index] = temp;
	
	cout << COLOR_LABEL << "Enter Customer CNIC (13 digits without hyphens): " << COLOR_RESET;
	do{
		getline(cin,temp);
		if(temp.length() != 13) cout << COLOR_ERROR << ">> Invalid CNIC! Enter exactly 13 digits: " << COLOR_RESET;
	}while(temp.length() != 13);
	
	sls.cnic[*index] += temp.substr(0,5) + "-" + temp.substr(5,7) + "-" + temp[temp.length()-1];
	cout << COLOR_SUCCESS << ">> Formatted CNIC: " << sls.cnic[*index] << "\n" << COLOR_RESET;
	
	cout << COLOR_LABEL << "Enter Contact Phone No. (+92): +92" << COLOR_RESET;
	do{
		cin>>temp;
		sls.ph_no[*index] = "+92" + temp;
		if(sls.ph_no[*index].length() != 13) cout << COLOR_ERROR << ">> Invalid Phone No! Enter 10 digits after +92: " << COLOR_RESET << "\n+92";
	}while(sls.ph_no[*index].length() != 13);
	
	cout << COLOR_LABEL << "Enter Delivery Address: " << COLOR_RESET;
	cin.ignore();
	getline(cin,sls.address[*index]);
	
	do{
		if(further == 'y' || further == 'Y'){
			sls.customer[*index] = sls.customer[*index -1];
			sls.cnic[*index] = sls.cnic[*index -1];
			sls.ph_no[*index] = sls.ph_no[*index -1];
			sls.address[*index] = sls.address[*index -1];
		}
		
		int found=0, srl_no, buy_id = 0;
		
		do{
			cout << COLOR_LABEL << "\nEnter Computer Brand Name (e.g., DELL, HP, LENOVO, APPLE): " << COLOR_RESET;
			string company;
			cin>>company;
			for (int i=0; i < company.length(); i++){
				company[i] = toupper(company[i]);
			}
			sls.sale_company[*index] = company;
			
			cout << COLOR_BOLD << "\nAvailable " << company << " Laptops in Stock:\n";
			cout << "+-------+------------+-----------------------+-----------------+-----------------------+---------+---------+---------+---------------+-------+\n";
			cout << "| " << left << setw(6) << "SR NO" << "| " << setw(11) << "BRAND" << "| " << setw(22) << "MODEL" << "| " << setw(16) << "PROCESSOR" << "| " << setw(22) << "DEDICATED GPU" << "| " << setw(8) << "RAM" << "| " << setw(8) << "SSD NVME" << "| " << setw(8) << "HDD" << "| " << setw(14) << "PRICE (RS)" << "| " << setw(6) << "QTY" << "|\n";
			cout << "+-------+------------+-----------------------+-----------------+-----------------------+---------+---------+---------+---------------+-------+\n" << COLOR_RESET;
			for(int i=0; i<str_index; i++){
				if(str.str_company[i] == sls.sale_company[*index] && str.str_qty[i] > 0){
					cout << "| " << left << setw(6) << str.str_no[i]
					     << "| " << setw(11) << str.str_company[i]
					     << "| " << setw(22) << str.str_model[i]
					     << "| " << setw(16) << str.str_gen[i]
					     << "| " << setw(22) << str.str_gpu[i]
					     << "| " << right << setw(5) << str.str_RAM[i] << " GB "
					     << "| " << right << setw(8) << formatSSD(str.str_SSD[i]) << " "
					     << "| " << right << setw(8) << formatHDD(str.str_HDD[i]) << " "
					     << "| RS." << right << setw(10) << str.str_price[i] << " "
					     << "| " << right << setw(5) << str.str_qty[i] << " |\n";
					found++;
				}
			}
			cout << COLOR_BOLD << "+-------+------------+-----------------------+-----------------+-----------------------+---------+---------+---------+---------------+-------+\n" << COLOR_RESET;
			if(found == 0) cout << COLOR_ERROR << ">> No available stock found for brand: " << company << ". Try another brand.\n" << COLOR_RESET;
		}while(found == 0);
		
		cout << COLOR_LABEL << "\nEnter Serial No. (Sr.No) of selected laptop: " << COLOR_RESET;
		cin>>srl_no;
		for(int i=0; i<str_index; i++){
			if (srl_no == str.str_no[i]){
				buy_id = i;
				break;
			}
		}
		
		sls.sale_model[*index]	= str.str_model[buy_id];
		sls.sale_gen[*index]	= str.str_gen[buy_id];
		sls.sale_gpu[*index]    = str.str_gpu[buy_id];
		sls.sale_RAM[*index]	= str.str_RAM[buy_id];
		sls.sale_SSD[*index]	= str.str_SSD[buy_id];
		sls.sale_HDD[*index]	= str.str_HDD[buy_id];
		
		// RAM Hardware Upgrade Module
		cout << COLOR_LABEL << "Do you wish to upgrade RAM? (y/n): " << COLOR_RESET;
		char yes;
		cin>>yes;
		int choice, Ram, price_4gb[3]={4000,5000,3500}, price_8gb[3]={6000,9000,8000};
		if(yes == 'y' || yes == 'Y'){
			cout << COLOR_LABEL << "Select RAM Upgrade Capacity (4 for 4GB, 8 for 8GB): " << COLOR_RESET;
			cin>>Ram;
			if(Ram == 4){
				cout << "1. Kingston 4GB (RS. 4000)\n2. Corsair 4GB  (RS. 5000)\n3. Crucial 4GB  (RS. 3500)\n";
				cout << COLOR_BOLD << "-> Select Brand Option (1-3): " << COLOR_RESET;
				cin>>choice;
				sls.sale_RAM[*index] += Ram;
				sls.sale_price[*index] = price_4gb[choice-1];
			}else if(Ram == 8){
				cout << "1. Kingston 8GB (RS. 6000)\n2. Corsair 8GB  (RS. 9000)\n3. Crucial 8GB  (RS. 8000)\n";
				cout << COLOR_BOLD << "-> Select Brand Option (1-3): " << COLOR_RESET;
				cin>>choice;
				sls.sale_RAM[*index] += Ram;
				sls.sale_price[*index] = price_8gb[choice-1];
			}
		}
		
		// SSD Storage Hardware Upgrade Module
		cout << COLOR_LABEL << "Do you wish to add SSD Storage Upgrade? (y/n): " << COLOR_RESET;
		cin>>yes;
		if(yes == 'y' || yes == 'Y'){
			cout << "1. Samsung 970 EVO 250GB NVMe SSD (RS. 12000)\n2. WD Blue 500GB NVMe SSD (RS. 18000)\n";
			cout << COLOR_BOLD << "-> Select SSD Option (1-2): " << COLOR_RESET;
			cin>>choice;
			if(choice == 1){
				sls.sale_SSD[*index] += 250;
				sls.sale_price[*index] += 12000;
			}else if(choice == 2){
				sls.sale_SSD[*index] += 500;
				sls.sale_price[*index] += 18000;
			}
		}
		
		cout << COLOR_LABEL << "Enter Quantity of Laptops to purchase: " << COLOR_RESET;
		cin>>sls.sale_qty[*index];
		str.str_qty[buy_id] -= sls.sale_qty[*index];
		sls.sale_price[*index] = (sls.sale_price[*index] + str.str_price[buy_id]) * sls.sale_qty[*index];
		
		*index +=1;
		cout << COLOR_SUCCESS << "\n>> Order transaction recorded successfully!\n" << COLOR_RESET;
		cout << COLOR_BOLD << "Add another item to this customer order? (y/n): " << COLOR_RESET;
		cin>>further;
	}while(further == 'y' || further == 'Y');
}

// Generate single order customer receipt or total sales report
void salesReport(int sales_index){
	cout << COLOR_LABEL << "\n[ SALES INVOICES & REVENUE REPORTS ]\n" << COLOR_RESET;
	cout << COLOR_HEADER << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;
	cout << "1. Single Customer Invoice Receipt\n2. Complete Store Sales Report\n";
	cout << COLOR_BOLD << "-> Option (1-2): " << COLOR_RESET;
	int report, index = 0, tot_price=0;
	bool found=0;
	string name;
	cin>>report;
	
	if(report == 1){
		cout << COLOR_LABEL << "Enter Customer Full Name: " << COLOR_RESET;
		cin.ignore();
		getline(cin,name);
		for(int a=0; a<name.length(); a++){
			name[a] = toupper(name[a]);
		}
		for(int i=0; i<sales_index; i++){
			if(name == sls.customer[i]){
				index = i;
				found = 1;
				break;
			}
		}
		if(found == 1){
			system("cls");
			printHeader();
			cout << COLOR_LABEL << "\n[ INVOICE RECEIPT ]\n" << COLOR_RESET;
			cout << COLOR_BOLD << "Customer Name : " << sls.customer[index] << "\n";
			cout << "CNIC          : " << sls.cnic[index] << "\n";
			cout << "Phone No      : " << sls.ph_no[index] << "\n";
			cout << "Address       : " << sls.address[index] << "\n" << COLOR_RESET;
			cout << COLOR_HEADER << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;
			
			cout << COLOR_BOLD << "+-------------+------------------------+-------------------+------------------------+---------+---------+---------+---------+---------------------+\n";
			cout << "| " << left << setw(12) << "BRAND" << "| " << setw(23) << "MODEL" << "| " << setw(17) << "PROCESSOR" << "| " << setw(23) << "DEDICATED GPU" << "| " << setw(8) << "RAM" << "| " << setw(8) << "SSD NVME" << "| " << setw(8) << "HDD" << "| " << setw(8) << "QTY" << "| " << setw(19) << "TOTAL PRICE (RS)" << "|\n";
			cout << "+-------------+------------------------+-------------------+------------------------+---------+---------+---------+---------+---------------------+\n" << COLOR_RESET;
			for(int i=0; i<sales_index; i++){
				if(name == sls.customer[i]){
					cout << "| " << left << setw(12) << sls.sale_company[i]
					     << "| " << setw(23) << sls.sale_model[i]
					     << "| " << setw(17) << sls.sale_gen[i]
					     << "| " << setw(23) << sls.sale_gpu[i]
					     << "| " << right << setw(5) << sls.sale_RAM[i] << " GB "
					     << "| " << right << setw(8) << formatSSD(sls.sale_SSD[i]) << " "
					     << "| " << right << setw(8) << formatHDD(sls.sale_HDD[i]) << " "
					     << "| " << right << setw(7) << sls.sale_qty[i] << " "
					     << "| RS." << right << setw(15) << sls.sale_price[i] << " |\n";
					tot_price += sls.sale_price[i];
				}
			}
			cout << COLOR_BOLD << "+-------------+------------------------+-------------------+------------------------+---------+---------+---------+---------+---------------------+\n" << COLOR_RESET;
			cout << COLOR_TOTAL << "GRAND TOTAL AMOUNT DUE: RS. " << tot_price << COLOR_RESET << "\n";
		}else{
			cout << COLOR_ERROR << ">> No orders recorded for customer: " << name << "\n" << COLOR_RESET;
		}
	}else if(report == 2){
		cout << COLOR_HEADER << "\n===============================================================================================================================================\n";
		cout << "||                                               STORE-WIDE SALES SUMMARY REPORT                                                             ||\n";
		cout << "===============================================================================================================================================\n\n" << COLOR_RESET;
		
		cout << COLOR_BOLD << "+-------------------+------------------+----------------+-------------+------------------------+---------+---------+---------+-------+-------------------+\n";
		cout << "| " << left << setw(17) << "CUSTOMER" << "| " << setw(16) << "CNIC" << "| " << setw(14) << "PHONE" << "| " << setw(11) << "BRAND" << "| " << setw(23) << "MODEL" << "| " << setw(8) << "RAM" << "| " << setw(8) << "SSD NVME" << "| " << setw(8) << "HDD" << "| " << setw(6) << "QTY" << "| " << setw(17) << "TOTAL PRICE (RS)" << "|\n";
		cout << "+-------------------+------------------+----------------+-------------+------------------------+---------+---------+---------+-------+-------------------+\n" << COLOR_RESET;
		for(int i=0; i<sales_index; i++){
			cout << "| " << left << setw(17) << sls.customer[i]
			     << "| " << setw(16) << sls.cnic[i]
			     << "| " << setw(14) << sls.ph_no[i]
			     << "| " << setw(11) << sls.sale_company[i]
			     << "| " << setw(23) << sls.sale_model[i]
			     << "| " << right << setw(5) << sls.sale_RAM[i] << " GB "
			     << "| " << right << setw(8) << formatSSD(sls.sale_SSD[i]) << " "
			     << "| " << right << setw(8) << formatHDD(sls.sale_HDD[i]) << " "
			     << "| " << right << setw(5) << sls.sale_qty[i] << " "
			     << "| RS." << right << setw(13) << sls.sale_price[i] << " |\n";
			tot_price += sls.sale_price[i];
		}
		cout << COLOR_BOLD << "+-------------------+------------------+----------------+-------------+------------------------+---------+---------+---------+-------+-------------------+\n" << COLOR_RESET;
		cout << COLOR_SUCCESS << "CUMULATIVE STORE SALES REVENUE: RS. " << tot_price << "\n" << COLOR_RESET;
	}
}

// Save all runtime inventory stock array records back to store.txt
void saveStoreData(int index){
	ofstream store("store.txt", ios::out | ios::trunc);
	for(int i=0; i<index; i++){
		string gen = str.str_gen[i];
		for(int j=0; j<gen.length(); j++){
			if(gen[j] == ' '){
				gen[j] = '-';
			}
		}
		string gpu = str.str_gpu[i];
		for(int j=0; j<gpu.length(); j++){
			if(gpu[j] == ' '){
				gpu[j] = '-';
			}
		}
		store << str.str_company[i] << "\t\t" 
		      << str.str_model[i] << "\t\t" 
		      << gen << "\t" 
		      << gpu << "\t" 
		      << str.str_RAM[i] << "\t" 
		      << str.str_SSD[i] << "\t" 
		      << str.str_HDD[i] << "\t" 
		      << str.str_price[i] << "\t\t" 
		      << str.str_qty[i] << "\n";
	}
	store.close();
}

// Save all runtime sales order array records back to sales.txt
void saveSalesData(int sales_index){
	ofstream sales("sales.txt", ios::out | ios::trunc);
	for(int i=0; i<sales_index; i++){
		string cust = sls.customer[i];
		for(int j=0; j<cust.length(); j++){
			if(cust[j] == ' '){
				cust[j] = '-';
			}
		}
		string gen = sls.sale_gen[i];
		for(int j=0; j<gen.length(); j++){
			if(gen[j] == ' '){
				gen[j] = '-';
			}
		}
		string gpu = sls.sale_gpu[i];
		for(int j=0; j<gpu.length(); j++){
			if(gpu[j] == ' '){
				gpu[j] = '-';
			}
		}
		string addr = sls.address[i];
		for(int j=0; j<addr.length(); j++){
			if(addr[j] == ' '){
				addr[j] = '-';
			}
		}
		sales << cust << " " 
		      << sls.cnic[i] << " " 
		      << sls.ph_no[i] << " " 
		      << addr << " " 
		      << sls.sale_company[i] << " " 
		      << sls.sale_model[i] << " " 
		      << gen << " " 
		      << gpu << " " 
		      << sls.sale_RAM[i] << "GB " 
		      << sls.sale_SSD[i] << "GB " 
		      << sls.sale_HDD[i] << "GB " 
		      << sls.sale_qty[i] << " " 
		      << sls.sale_price[i] << "\n";
	}
	sales.close();
}
