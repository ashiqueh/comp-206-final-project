#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	FILE *users = fopen("users.txt","r"); //NEED PATH FOR users.txt if not in your cgi-bin
	FILE *errorf = fopen("error_L.txt","r");
	
	char *usernm = calloc(1,50);
	char *usernmd = calloc(1,50);
	char *passwd = calloc(1,50);
	char *token = calloc(1,50);	

	char post[300];
	char line[100];
	char c[10];
	int a = 0;
    int n;

    char *clen = getenv("CONTENT_LENGTH");
    if (clen == NULL) {
    printf("Content-Type:text/html\n\n");
    printf("<html>");

    printf("NULL ERROR");
    printf("</html>");
    return 0;
    }
    else {
    int n = atoi(getenv("CONTENT_LENGTH"));
    }
	int bvar = 0;
	int ch;
	int i;

	while ((*c = getchar()) != EOF && a<n)
 	{
		if (a < 200) {
        	if (*c != '+') post[a]=*c;
          	else post[a]=' ';
			a++; }
 	}
	post[a] = '\0';

	//Tokenizing variables
	token = strtok(post,"=");
	usernm = strtok(NULL,"&");
	token = strtok(NULL,"=");
	passwd = strtok(NULL,"&");
	strcpy(usernmd, usernm);		
	
	strcat(usernm, "\n");
	strcat(passwd, "\n");	

	printf("Content-Type:text/html\n\n");
	printf("<html>");

	if (users==NULL) {
		printf("<head><title>ERROR</title></head>");
		printf("<body><p>Unable to open file!</p></body>");
		return;
	}

	//Functionality test
	//printf("Content-type: text/html");
	//printf("<html><body><h1>Hello world</h1></body></html>");

	fgets(line,99,users);
	while (!feof(users)) {
		if (strcmp(line,usernm) == 0) {
			fgets(line,99,users);
			if (strcmp(line,passwd) == 0) {
				//LOGIN USER, either by launching python script, or printf URL to allow user info in hidder
				
				printf("<head>");
				printf("<title> Elite Dragons </title>");
				printf("</head>");

				printf("<body bgcolor=\"#333333\" text=\"white\">");

				printf("<br>");
				printf("<center><img src=\"http://cs.mcgill.ca/~ahossa5/logo-white-transparent.png\"</center>");
				printf("<br><br>");

				printf("<center>Sucessfully logged in! Click below to continue to your dashboard. </center>");

				printf("<br><br>");

				printf("<center>");
				printf("<form name=\"login\" action=\"http://cgi.cs.mcgill.ca/~jzuo1/cgi-bin/dashboard.py\" method=\"post\">");
				printf("<input type=\"hidden\" name=\"userID\" value=\"%s\">",usernmd);
				printf("<input type=\"submit\" value=\"Go to Dashboard!\"></div>");
				printf("</form>");
				printf("</center>");

				printf("</body>");

				bvar = 1;
				break;
			}
			else {
				//ERROR message page w/ 2 links to landing/login
				while ((ch=fgetc(errorf)) != EOF) putchar(ch);

				bvar = 1;
				break;
			}
		}
		else {
			for (i=0; i<4; i++) {
				fgets(line,99,users); //Different user's pass, full name, job des, next username
			}
		}
	}

	if (bvar == 0) {
	while ((ch=fgetc(errorf)) != EOF) putchar(ch);
	}

	fclose(errorf);
	fclose(users);

	printf("</html>");

	return 0;
}

