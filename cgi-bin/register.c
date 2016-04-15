#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
	FILE *rusers = fopen("users.txt","r"); //NEED PATH FOR users.txt if not in your cgi-bin
	FILE *ausers = fopen("users.txt","a"); //NEED PATH FOR users.txt if not in your cgi-bin
	FILE *errorf = fopen("error_R.txt","r"); 
	FILE *successf = fopen("success.txt","r");

	char *usernm = calloc(1,50);
	char *passwd = calloc(1,50);
	char *fullnm = calloc(1,100);
	char *jobdes = calloc(1,150);
	char *token = calloc(1,50);

	char post[500];
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
	int noapp = 0;
	int i = 0;
	int ch;
	
	while ((*c = getchar()) != EOF && a<n)
 	{
		if (a < 500) {
        	if (*c !='+') post[a]=*c;
          	else post[a]=' ';
			a++; }
 	}
	post[a] = '\0';
		
	//Tokenize variables

	token = strtok(post,"=");
	usernm = strtok(NULL,"&");
        token = strtok(NULL,"=");
        passwd = strtok(NULL,"&");
        token = strtok(NULL,"=");
        fullnm = strtok(NULL,"&");
        token = strtok(NULL,"=");
        jobdes = strtok(NULL,"&");

	strcat(usernm, "\n");
	
	//Prepare browser for html
	printf("Content-Type:text/html\n\n");
	printf("<html>");
	//printf("hi");
	
	if (rusers==NULL) {
		printf("<head><title>ERROR</title></head>");
		printf("<body><p>Unable to open file!</p></body>");
		return;
	}

	fgets(line,99,rusers);
	while (!feof(rusers)) {
		if (strcmp(line,usernm) == 0) {
			//ERROR message page w/ 2 links to LANDING OR LOGIN
			while ((ch=fgetc(errorf)) != EOF) putchar(ch);

			
			noapp = 1; //Used to break append to file (if username doesnt exist)
			break;
		}
		for (i=0; i<4; i++) {
			fgets(line,99,rusers);
		}
	}

	//Assuming username doesn't already exist, append to end of file and open SUCESS PAGE
	if (noapp == 0) {
		fprintf(ausers,"%s%s\n%s\n%s\n", usernm, passwd, fullnm, jobdes);
		
		while ((ch=fgetc(successf)) != EOF) putchar(ch);
	}

	fclose(errorf);
	fclose(successf);
	fclose(rusers); // Should this be above append statement with ausers FILE??
	fclose(ausers);
	
	printf("</html>");

	return 0;
}

