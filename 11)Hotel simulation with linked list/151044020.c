#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Customer{
    char name[15];
    char surname[15];
    int age;
    int room;
    char gender[7];
    struct Customer * next;
};


struct Room{
    int number;
    int capacity;
    int floor;
    int customer_number;
    struct Customer * customers;
    struct Customer  tail_customer;
    struct Room * next;
};

void read_room_txt(struct Room *myHotel){
    FILE * fp;
    char file_name [] = "rooms.txt";
    char in [100];
    int number,capacity,floor,i=1;
    char useless;
    struct Room * current = myHotel;
    fp = fopen(file_name,"r");
    if(fp == NULL){
        printf("ERROR\n");
    }
    else{
        while(fgets(in,99,fp)){
            sscanf(in,"%d%c%d%c%d",&number,&useless,&capacity,&useless,&floor);
            current->capacity = capacity;           
            current->floor = floor;           
            current->number = number;
            current->customer_number = 0;
            current->next = malloc(sizeof(struct Room));
            current = current->next;
        }
        current->next = NULL;
    }
}



void print_hotel(struct Room  myHotel){
    struct Room * current = &myHotel;
    while(current->next != NULL){
        printf("%d %d %d \n",current->number,current->capacity,current->floor);
        current = current->next;
    }
}

struct Room * get_room(int room_number,struct Room  *myHotel){
    struct Room * current = myHotel;
    while(current->next != NULL){
        if(current->number == room_number)
        	return current;        
        current = current->next;
    }
    return NULL;
}

void read_customers_txt(struct Room *myHotel){
    FILE * fp;
    char file_name [] = "customers.txt";
    char in [100];
    int number,age,i=1;
    char useless;
	char name[15];
	char surname[15];
	char tmpGender[7];
	int room_number;
    struct Room *current_room;
    fp = fopen(file_name,"r");
    if(fp == NULL){
        printf("ERROR\n");
    }
     
    else{
    
        while(fgets(in,99,fp)){
            struct Customer *current = malloc(sizeof(struct Customer));	
			sscanf(in,"%d %c %[^,] %c %d %c %s",&room_number,&useless,name,&useless,&age,&useless,tmpGender);	
            current_room = get_room(room_number,myHotel);
           	strcpy(current->name,name);
			strcpy(current->surname,surname);
			strcpy(current->gender,tmpGender);  
			current->room=number;			                  
			current->age=age;
			 		   printf("%s  %s 5555 ",current->name,current->surname);

			if(current_room->customers==NULL){
				current_room->customers=current;
				current_room->tail_customer=*current;
			 	current_room->tail_customer.next = NULL;   	
			 			   printf("%s%s",current->name,current->surname);

			}
           else{
           		current_room->tail_customer.next=current;
           		current_room->tail_customer=*current;
 				current_room->tail_customer.next = NULL;      
				   				   printf("%s%s",current->name,current->surname);


           		
		   }
		   printf("%s%s",current->name,current->surname);
        }
     		 
    }
    		   printf("%s %s",name,surname);

}




int main() {
    struct Room myHotel;
    read_room_txt(&myHotel);
    print_hotel(myHotel);
    get_room(10100,&myHotel);
    return 0;
}
