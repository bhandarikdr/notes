#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CLR_RED "\x1B[31m"
#define CLR_WHT "\x1B[37m"
#define CLR_NORM "\x1B[0m"
void show_notes();
void show_queried_note(char*);
void add_note();
void create_db();
void u_help();
void truncate();

MYSQL *get_connection(){
   MYSQL *conn;
   char *server = "localhost";
   char *user = "ntuser";
   char *password = "ntuser32"; /* set me first */
   char *database = "notesdb";
   conn = mysql_init(NULL);
	 /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   return conn;
}

/*main program*/
int main(int argc, char *argv[]) {
if(argc > 1){
	if(strcmp(argv[1],"-a")==0 || strcmp(argv[1],"add")==0)
	add_note();
	else if(strcmp(argv[1],"-c")==0 || strcmp(argv[1],"configure")==0)
	create_db();
	else if(strcmp(argv[1],"-h")==0 || strcmp(argv[1],"help")==0)
	u_help();
	else if(strcmp(argv[1],"-t")==0 || strcmp(argv[1],"truncate")==0)
	truncate();
	else
	show_queried_note(argv[1]);
}
else
show_notes();
return 0;
}

/* create the notesdb database and mynotes table*/
void create_db(){
MYSQL *con;
MYSQL *conn;
   char *server = "localhost";
   char *user = "root";
   char *pass;
	pass = malloc(20*sizeof(char)); 
	printf("Password for 'root'@'localhost': ");
	gets(pass);
   con = mysql_init(NULL);
         /* Connect to database */
   if (!mysql_real_connect(con, server,
         user, pass, NULL, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
   }
	
	if (mysql_query(con, "CREATE DATABASE notesdb"))
	{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
	}
printf("database created...\n");
if (mysql_query(con, "CREATE USER ntuser@localhost IDENTIFIED BY 'ntuser32'"))
        {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
        }
printf("user for database created...\n");
if (mysql_query(con, "GRANT ALL ON notesdb.* to ntuser@localhost"))
        {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
        }
printf("granted permissions to user on the database...\n");
mysql_close(con);
printf("\ncreating table for notes...\n");
conn = get_connection();

if(mysql_query(conn, "CREATE TABLE mynotes(id int(5) auto_increment primary key,title varchar(60), text varchar(900))")){
fprintf(stderr, "%s\n", mysql_error(conn));
exit(1);
}
printf("table created... Congratulation!\n");
mysql_close(conn);
}

/*truncate database values*/
void truncate(){
	MYSQL *conn;
	conn = get_connection();
if(mysql_query(conn,"TRUNCATE mynotes")){
fprintf(stderr, "%s\n", mysql_error(conn));
	exit(1);
	}
mysql_close(conn);
}


/*show stored notes*/
void show_notes(){
	int i=0;
	MYSQL *conn;
	MYSQL_RES *res;
   	MYSQL_ROW row;
   conn = get_connection();  
   
   /* send SQL query */
   if (mysql_query(conn, "select * from mynotes")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /* show  notes in the database */
   printf("%sStored notes...\n",CLR_WHT);
	printf("%s",CLR_NORM);
   while ((row = mysql_fetch_row(res)) != NULL){
	i++;
        printf("   %s[%s]    %s%s\n",CLR_WHT,row[0],CLR_RED,row[1]);
	}
	if(i<1)
	printf("\t<EMPTY>\n");
	else
	printf("\n%s  Found [%d] note(s)!\n",CLR_WHT,i); 
        //set to normal color
        printf("%s",CLR_NORM);
   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
}

/*show queried note*/
void show_queried_note(char *id){
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
	int n,i;
  
	char query[400] = "select * from mynotes where id=";
	strcat(query,id);
	char title[60];
	char text[900];

   conn = get_connection();
   
   /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /*print the note */
	row = mysql_fetch_row(res);
printf("%sReading note[%s]...\n",CLR_WHT, id);
        printf("%s\t\t%s\n",CLR_RED,row[1]);
n=strlen(row[1]);
printf("%s\t\t",CLR_NORM);
for(i=0;i<n;i++)
printf("=");
printf("\n\n");
	printf("  %s%s\n",CLR_WHT,row[2]);
        //set to normal color
        printf("%s",CLR_NORM);
   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
}

/*Add note*/
void add_note(){
        MYSQL *conn;
        char query[1100] = "insert into mynotes(title,text) values('";
        char *title,*eltit;
        char *text,*txet;
	int c, i, j=0;
title = malloc(60*sizeof(char));
eltit = malloc(70*sizeof(char));
text = malloc(900*sizeof(char));
txet = malloc(1000*sizeof(char));
	printf("\nTitle : ");
	gets(title);
//puts(title);
	for(i=0;i<=strlen(title);i++){
		c=title[i];
		if(c=='\''){
			eltit[j++]='\'';
			eltit[j++]=c;
		}
		else eltit[j++]=c;
	}
//puts(eltit);
	printf("Type your note.....\n");
	gets(text);
//puts(text);
	j=0;
	for(i=0;i<=strlen(text);i++){
                c=text[i];
                if(c=='\''){
                        txet[j++]='\'';
			txet[j++]=c;
		}
                else txet[j++]=c;
	}
//puts(txet);

/*
printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
printf("%s\n\n%s\n",title,text);
printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
*/
	strcat(query,eltit);
	strcat(query,"','");
	strcat(query,txet);
	strcat(query,"')");

   conn = get_connection();
      /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
printf("Success !\n");
mysql_close(conn);

}

/* user help */
void u_help(){
printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
printf("uses\n");
printf("=====\n\n");

printf("$./notes                ==> lists all notes\n");
printf("$./notes <id>           ==> displays note identified by <id>\n");
printf("$./notes -a|-add        ==> adds notes\n");
printf("$./notes -c|-configure  ==> creates database and table\n");
printf("$./notes -h|-help       ==> uses help\n");
printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
