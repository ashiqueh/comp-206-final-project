#include <stdio.h>
#include <stdlib.h>

int main(){
	//Basic headers for the website
	printf("Content-type: text/html\r\n\r\n <html> <head><title> See a Friend </title></head> <body bgcolor=\"#333333\" text=\"white\"> <center><img src=\"http://cs.mcgill.ca/~ahossa5/logo-white-transparent.png\"><br>");

	//Obtaining user information from POST
	char string[1000];
	int n = atoi(getenv("CONTENT_LENGTH"));
	char* userID = fgets(string, n+1, stdin);
	//Increments the userID pointer so that the pointer starts after the "user=" portion of the string
	userID = userID + 7;

	//Opens a FILE struct for the friends.txt
	FILE* friends = fopen("/home/2014/ahossa5/public_html/cgi-bin/friends.txt", "r");
	char line[10000];
	//Iterates through the file line-by-line
	while(fgets(line, 10000, friends)){
		//Tokenizes the line by space
		char *token = (char*)strtok(line, " ");
		//If the first person in a list of fiends in friends.txt and the user and the same, then we proceed to printing
		if(strcmp(token, userID) == 0){
			//We do not print a profile for the first user (self) so the first 'boolean' keeps track of whether or not we have printed
			int first = 1;
			while(token != NULL){
				//Not the first user, so we print a submit form for one of the friends. The form has a hidden field, which is read by the program used to generate the page.
				if(first == 0){
					printf("<form action=\"friendPage.cgi\" method=\"POST\"> <input type=\"submit\" value =\"");
					puts(token);
					printf("\"> <input type=\"hidden\" name=\"friendID\" value=\"");
					puts(token);
					printf("\"> <input type=\"hidden\" name=\"userID\" value=\"");
					puts(userID);
					printf("\"> </form>");
					token = (char*)strtok(NULL, " ");
				}
				else{
					puts(token);
					printf("<br> Your friends are:");
					token = (char*)strtok(NULL, " ");
					first = 0;
				}
			}
		}
	}
	//Completes the HTML and includes a return to the Dashboard.
	printf("<br><form action=\"dashboard.py\" method=\"POST\"> <input type=\"submit\" value=\"Return to Dashboard\"> <input type=\"hidden\" name=\"userID\" value=\"");
	printf("%s", userID);
	printf("\"></form>");
	printf("</center></body></html>");
	return 0;
}