#include <stdio.h>
#include <stdlib.h>

int main(){
	//Basic headers for the website
	printf("Content-type: text/html\r\n\r\n <html> <head><title> Your Friend </title></head> <body bgcolor=\"#333333\" text=\"white\"> <center><img src=\"http://cs.mcgill.ca/~ahossa5/logo-white-transparent.png\"><br>");

	//Obtaining friend information from POST
	char string[1000];
	int n = atoi(getenv("CONTENT_LENGTH"));
	char* data = (char*)fgets(string, n, stdin);
	//Tokenizes the input at "=" and "%", which indicate the beginning and end of a new ID
	char* friendID = (char*)strtok(data, "=");
	friendID = (char*)strtok(NULL, "%");
	
	char* userID = (char*)strtok(NULL, "=");
	userID = (char*)strtok(NULL, "%");

	FILE* users = fopen("/home/2016/cvanei1/public_html/cgi-bin/users.txt", "r");
	char* line = malloc(10000);
	//Iterates through the file line-by-line
	while(fgets(line, 10000, users)){
		//Tokenizes the string to remove the 
		line = (char*)strtok(line, "\n");
		//printf("%s compared to %s", friendID, line);
		//If the line matches the friend, we print their information in a table
		if(strcmp(line, friendID) == 0){
			//Printing username
			printf("<table><tr> <td>Username:</td> <td>");
			printf("%s", line);
			printf("</td></tr>");

			//Two fgets to skip the password line and printing real name
			fgets(line, 10000, users);
			fgets(line, 10000, users);
			line = (char*)strtok(line, "\n");
			printf("<tr> <td>Full Name:</td> <td>");
			printf("%s", line);
			printf("</td></tr>");

			//Printing occupation
			fgets(line, 10000, users);
			line = (char*)strtok(line, "\n");
			printf("<tr> <td>Occupation:</td> <td>");
			printf("%s", line);
			printf("</td></tr></table>");
			break;
		}
		//Otherwise, we pass the next three lines because they do not contain username information
		else{
			fgets(line, 10000, users);
			fgets(line, 10000, users);
			fgets(line, 10000, users);
		}
	}
	//Button to return to seeFriends
	printf("<br><form action=\"seeFriends.cgi\" method=\"POST\"> <input type=\"submit\" value=\"Return to see a friend\"> <input type=\"hidden\" name=\"userID\" value=\"");
	printf("%s", userID);
	printf("\"></form></center></body></html>");
	return 0;
}
