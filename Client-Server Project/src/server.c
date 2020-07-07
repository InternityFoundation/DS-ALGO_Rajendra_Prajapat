/**************************************************************************************************************************
 * 								SSL/TLS server program
 * 													
 * 				Features: secure, multithread, sends close notifications 
 * 													
 * 
 * 				Install the OpenSSL library, for the ubuntu use the below command.
 *													 
 *				      $ sudo apt-get install -y libssl-dev
 *
 *				Generate certificate
 *				      $ openssl req -x509 -nodes -days 365 -newkey rsa:1024 -keyout mycert.pem -out mycert.pem
 *													
 * 				compile 
 * 					  $ g++ -Wall -o ser  server.c -L/usr/lib -lssl -lcrypto -lpthread -lsqlite3
 * 						
 * 				run
 * 					  $ sudo ./ser port_number 
 * 				
 *              example: sudo ./ser 8081
 * 
 * 
 * *************************************************************************************************************************/
#include <sqlite3.h>
#include <ctime>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "openssl/ssl.h"
#include "openssl/err.h"
#define FAIL    -1
#define ts std::time(nullptr)


/* CALLBACK FUNCTIONS FOR SQLITE3_EXEC FUNCTION  */


static int select_callback(void *NotUsed,int argc,char **argv,char **szColName){
  int *flag = (int*)NotUsed;
  *flag = 1;
  return 0;
}

static int fetch_info(void *info,int argc,char **argv,char **szColName){  
  if(argv[0]){
    char *res=(char*)info;
    strcpy(res,"Description : ");
    strcat(res,argv[0]);  
  if(argv[1]){
    strcat(res," ,\nContact : ");
    strcat(res,argv[1]);   
  }
  }

  return 0;
}

static int callback(void *NotUsed,int argc,char **argv,char **szColName){
  return 0;
}

/* CALLBACK FUNCTIONS ENDS */

// Create the SSL socket and start listening on given port
int
OpenListener (int port)
{
  int sd;
  struct sockaddr_in addr;
  sd = socket (PF_INET, SOCK_STREAM, 0);
  bzero (&addr, sizeof (addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons (port);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind (sd, (struct sockaddr *) &addr, sizeof (addr)) != 0)
    {
      perror ("can't bind port");
      abort ();
    }

  if (listen (sd, 10) != 0)
    {
      perror ("Can't configure listening port");
      abort ();
    }
  return sd;
}

//Initiate CTX 
SSL_CTX *
InitServerCTX (void)
{
  const SSL_METHOD *method;

  //SSL_METHOD *method;
  SSL_CTX *ctx;
  OpenSSL_add_all_algorithms ();	/* load & register all cryptos, etc. */
  SSL_load_error_strings ();	/* load all error messages */
  method = TLSv1_2_server_method ();	/* create new server-method instance */
  ctx = SSL_CTX_new (method);	/* create new context from method */
  if (ctx == NULL)
    {
      ERR_print_errors_fp (stderr);
      abort ();
    }
  return ctx;
}


//To load the Certificates
void
LoadCertificates (SSL_CTX * ctx, char *CertFile, char *KeyFile)
{
  if (SSL_CTX_use_certificate_file (ctx, CertFile, SSL_FILETYPE_PEM) <= 0)
    {
      ERR_print_errors_fp (stderr);
      abort ();
    }

  /* set the private key from KeyFile (may be the same as CertFile) */
  if (SSL_CTX_use_PrivateKey_file (ctx, KeyFile, SSL_FILETYPE_PEM) <= 0)
    {
      ERR_print_errors_fp (stderr);
      abort ();
    }

  /* verify private key */
  if (!SSL_CTX_check_private_key (ctx))
    {
      fprintf (stderr, "Private key does not match the public certificate\n");
      abort ();
    }
}

void
ShowCerts (SSL * ssl)
{
  X509 *cert;
  char *line;
  cert = SSL_get_peer_certificate (ssl);

  if (cert != NULL)
    {
      printf ("\n%ld  :  Server certificates:",ts);
      line = X509_NAME_oneline (X509_get_subject_name (cert), 0, 0);
      printf ("\n%ld  :  Subject: %s",ts, line);
      free (line);
      line = X509_NAME_oneline (X509_get_issuer_name (cert), 0, 0);
      printf ("\n%ld  :  Issuer: %s",ts, line);
      free (line);
      X509_free (cert);
    }
  else
    printf ("No certificates.\n");
}


//handle a Client
void *
thread_handler (void *in)
{
  SSL *ssl = (SSL *) in;
  printf ("\n%ld  :  thread created",ts);
  char buf[1024] = { 0 };
  int sd, bytes = 4;
  char ServerResponse[1048];
  if (SSL_accept (ssl) == FAIL)	/* do SSL-protocol accept */
    {
      ERR_print_errors_fp (stderr);
    }
  else
    {
      ShowCerts (ssl);		/*show certificate from client certificates */
      sqlite3 *db;
      int rc = sqlite3_open("file.db",&db);
      if(!rc)
        printf("\n%ld  :  database opened succesfully !",ts);
      else{
        printf("\n%ld  :  Error in opening database",ts);
        return 0;
      }      
      while (1)
        {
          //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
          //Your Implimentation Goes HEAR
          //SSL_read(ssl, buf, sizeof(buf));  To receive
          //SSL_write(ssl, ServerResponse, strlen(ServerResponse)); To send 
          // NOTE: For every read in server there should be a write method in client 

          /* follwing lines of code read from client and store it in buf */
          

          char user_name[1024] = { 0 },password[1024] = {0};
          bytes = SSL_read (ssl, buf, sizeof (buf));
          if(buf[0]=='1'){
            //printf("\n.");
            bytes = SSL_read (ssl, user_name, sizeof (user_name));

            if (bytes <= 0)
              {
                printf ("\n%ld  :  Error",ts);
                break;
              }
            user_name[bytes] = '\0';
            //printf ("\n%ld  :  Client user_name: \"%s\"\n",ts, user_name);

            //if client says exit
            if (strncmp ("exit", user_name, 4) == 0)
              {
                printf ("\n%ld  :  Server Exit...",ts);
                break;
              }
            bytes = SSL_read (ssl, password, sizeof (password));

            if (bytes <= 0)
              {
                printf ("\n%ld  :  Error",ts);
                break;
              }
            password[bytes] = '\0';
            //printf ("\nClient password: \"%s\"\n", password);
            std::string sql_stmt;
            char *err =0; 
            sql_stmt = "SELECT name,password FROM users WHERE name='"+std::string(user_name)+"';";
            int info_present = 0;
            rc = sqlite3_exec(db,sql_stmt.c_str(),select_callback,&info_present,&err);
            if(rc != SQLITE_OK)
            {
              std::cout << std::endl << ts << "  :  SQL Fetch Error: " <<  err ;
              strcpy(ServerResponse,"Fail");
              SSL_write (ssl, ServerResponse, strlen (ServerResponse));
            }     
            else if(info_present){
              std::cout << std::endl << ts << "  :  User with same user_name already exists. ";
              SSL_write(ssl,"SameUser",8);                        
            }  


            sql_stmt = "INSERT INTO users(name,password) VALUES('"+std::string(user_name)+"','"+std::string(password)+"');";
            err=0;
            rc = sqlite3_exec(db,sql_stmt.c_str(),callback,0,&err);
            if(rc != SQLITE_OK)
            {
              std::cout << std::endl << ts << "  :  SQL Insert Error: " <<  err;
              break;
            }else{
              printf("\n%ld  :  User %s has signed up",ts,user_name);
              strcpy(ServerResponse,"Success");
              SSL_write (ssl, ServerResponse, strlen (ServerResponse));
            }            

          }


          else if(buf[0]=='2'){
            bytes = SSL_read (ssl, user_name, sizeof (user_name));

            if (bytes <= 0)
              {
                printf ("\n%ld  :  Error",ts);
                break;
              }
            user_name[bytes] = '\0';
            //printf ("\n%ld  :  Client user_name2: \"%s\"",ts user_name);

            //if client says exit
            if (strncmp ("exit", user_name, 4) == 0)
              {
                printf ("\n%ld  :  Server Exit...",ts);
                break;
              }
            bytes = SSL_read (ssl, password, sizeof (password));

            if (bytes <= 0)
              {
                printf ("\n%ld  :  Error",ts);
                break;
              }
            password[bytes] = '\0';
            //printf ("Client password: \"%s\"\n", password);
            std::string sql_stmt = "SELECT name,password FROM users WHERE name='"+std::string(user_name)+"' AND password='"+std::string(password)+"';";
            char *err=0;
            int row_present=0;
            rc = sqlite3_exec(db,sql_stmt.c_str(),select_callback,&row_present,&err);


            if(rc != SQLITE_OK)
            {
              std::cout << std::endl << ts << "  :  login SQL Error: " <<  err ;
              strcpy(ServerResponse,"Fail");
              SSL_write (ssl, ServerResponse, strlen (ServerResponse));
              break;
            }else{
              if(row_present){
                printf("\n%ld  :  User - %s has logged in",ts, user_name);
                strcpy(ServerResponse,"Success");
                SSL_write (ssl, ServerResponse, strlen (ServerResponse));
                char opt[2]={0};                                
                do{  
                  fflush(stdout);
                  SSL_read(ssl,opt,sizeof(opt));
                  if(opt[0]=='1'){
                    sql_stmt = "SELECT description,contact FROM users WHERE name='"+std::string(user_name)+"' AND password='"+std::string(password)+"';";                    
                    char *e=0;
                    char desc[1024]={0};
                    rc = sqlite3_exec(db,sql_stmt.c_str(),fetch_info,(void*)(&desc),&e);
                    if(rc != SQLITE_OK){
                      std::cout << std::endl << ts <<"  :  View SQL Error: " <<  e ;
                    }
                    if(strlen(desc)){
                      SSL_write(ssl,desc,sizeof(desc));
                      printf("\n%ld  :  Displayed description for user %s !",ts,user_name);
                    }
                    else{
                      strcpy(desc,"No Information found !");
                      SSL_write(ssl,desc,sizeof(desc));
                      printf("\n%ld  :  Null description Displayed for user %s !",ts,user_name); 
                    }
                  }

                  else if(opt[0]=='2'){
                    SSL_read(ssl,buf,sizeof(buf));
                    if(buf[0]=='1'){
                      char new_pass[1024]={0};
                      SSL_read(ssl,new_pass,sizeof(new_pass));                      
                      sql_stmt = "SELECT name,password FROM users WHERE name='"+std::string(user_name)+"';";
                      int info_present = 0;
                      rc = sqlite3_exec(db,sql_stmt.c_str(),select_callback,&info_present,&err);
                      if(rc != SQLITE_OK)
                      {
                        std::cout << std::endl << ts << "  :  login SQL Error: " <<  err ;
                        strcpy(ServerResponse,"Fail");
                        SSL_write (ssl, ServerResponse, strlen (ServerResponse));
                      }     
                      else if(!info_present){
                        std::cout << std::endl << ts << "  :  No password to Update ";
                        SSL_write(ssl,"Fail",4);                        
                      }
                      else{                 
                        sql_stmt = "UPDATE users SET password='"+std::string(new_pass)+"' WHERE name='"+std::string(user_name)+"';";
                        char *e=0;
                        rc = sqlite3_exec(db,sql_stmt.c_str(),callback,NULL,&e);
                        if(rc != SQLITE_OK){
                          std::cout << std::endl << ts << "  :  Update password SQL Error: " <<  e ;
                          SSL_write(ssl,"Fail",4);
                        }else{
                          SSL_write(ssl,"Success",7);
                        }
                      }
                      printf("\n%ld  :  Update password completed succesfully for user %s !",ts, user_name);
                    }
                    else if(buf[0]=='2'){
                      char new_desc[1024]={0};
                      SSL_read(ssl,new_desc,sizeof(new_desc));
                      sql_stmt = "SELECT name,password FROM users WHERE name='"+std::string(user_name)+"';";
                      int info_present = 0;
                      rc = sqlite3_exec(db,sql_stmt.c_str(),select_callback,&info_present,&err);
                      if(rc != SQLITE_OK)
                      {
                        std::cout << std::endl << ts << "  :  SQL Fetch Error: " <<  err ;
                        strcpy(ServerResponse,"Fail");
                        SSL_write (ssl, ServerResponse, strlen (ServerResponse));
                      }     
                      else if(!info_present){
                        std::cout << std::endl << ts << "  :  No description to Update ";
                        SSL_write(ssl,"Fail",4);                        
                      }  
                      else{                       
                        sql_stmt = "UPDATE users SET description='"+std::string(new_desc)+"' WHERE name='"+std::string(user_name)+"';";
                        char *e=0;
                        rc = sqlite3_exec(db,sql_stmt.c_str(),callback,NULL,&e);
                        if(rc != SQLITE_OK){
                          std::cout << std::endl << ts << "  :  Update description SQL Error: " <<  e ;
                          SSL_write(ssl,"Fail",4);
                        }else{
                          SSL_write(ssl,"Success",7);
                        }
                      }
                      printf("\n%ld  :  Update description completed succesfully for user %s!",ts,user_name);
                    }
                    else if(buf[0]=='3'){
                      char new_contact[1024]={0};
                      SSL_read(ssl,new_contact,sizeof(new_contact));
                      sql_stmt = "SELECT name,password FROM users WHERE name='"+std::string(user_name)+"';";
                      int info_present = 0;
                      rc = sqlite3_exec(db,sql_stmt.c_str(),select_callback,&info_present,&err);
                      if(rc != SQLITE_OK)
                      {
                        std::cout << std::endl << ts << "  :  SQL Fetc Error: " <<  err ;
                        strcpy(ServerResponse,"Fail");
                        SSL_write (ssl, ServerResponse, strlen (ServerResponse));
                      }     
                      else if(!info_present){
                        std::cout << std::endl << ts << "  :  No contact to Update ";
                        SSL_write(ssl,"Fail",4);                        
                      }  
                      else{                       
                        sql_stmt = "UPDATE users SET contact='"+std::string(new_contact)+"' WHERE name='"+std::string(user_name)+"';";
                        char *e=0;
                        rc = sqlite3_exec(db,sql_stmt.c_str(),callback,NULL,&e);
                        if(rc != SQLITE_OK){
                          std::cout << std::endl << ts << "  :  Update contact SQL Error: " <<  e ;
                          SSL_write(ssl,"Fail",4);
                        }else{
                          SSL_write(ssl,"Success",7);
                        }
                      }
                      printf("\n%ld  :  Update contact completed succesfully for user %s!",ts,user_name);                      
                    }
                  }

                  else if(opt[0]=='3'){
                    SSL_read(ssl,buf,sizeof(buf));
                    if(!strcmp(buf,"Confirm")){
                      sql_stmt = "SELECT name,password FROM users WHERE name='"+std::string(user_name)+"';";
                      int info_present = 0;
                      rc = sqlite3_exec(db,sql_stmt.c_str(),select_callback,&info_present,&err);
                      if(rc != SQLITE_OK)
                      {
                        std::cout << std::endl << ts << "  :   SQL Fetch Error: " <<  err ;
                        strcpy(ServerResponse,"Fail");
                        SSL_write (ssl, ServerResponse, strlen (ServerResponse));
                      }     
                      else if(!info_present){
                        std::cout << std::endl << ts << "  :  No account to delete ";
                        SSL_write(ssl,"Fail",4);                        
                      }       
                      else{                  
                        sql_stmt = "DELETE FROM users WHERE name='"+std::string(user_name)+"';";
                        char *e=0;
                        rc = sqlite3_exec(db,sql_stmt.c_str(),callback,NULL,&e);
                        if(rc != SQLITE_OK){
                          std::cout << std::endl << ts << "  :  Delete account SQL Error: " <<  e ;
                          SSL_write(ssl,"Fail",4);
                        }else{
                          SSL_write(ssl,"Success",7);
                          printf("\n%ld  :  Deleted account of user %s succesfully !",ts, user_name);
                          break;
                        }
                      }
                    }
                  }

                }while(opt[0]!='4');
              }else{
                printf("\n%ld  :  Invalid login credentials",ts);
                SSL_write(ssl,"FailLogin",9);
              }
            }
          }else{
            printf("\n%ld  :  Client exit...",ts);
            break;
          }


        }
        if(db)
        {
          sqlite3_close(db);
        }
    }

  printf ("\n%ld  :  closing the connection",ts);
  sd = SSL_get_fd (ssl);	/* get socket connection */
  SSL_shutdown (ssl);
  SSL_free (ssl);		/* release SSL state */
  close (sd);			/* close connection */
  return 0;
}

int
main (int count, char *Argc[])
{
  setbuf(stdout, NULL);
  SSL_CTX *ctx;
  int server;
  char *portnum;

  //root access or not
  if (getuid () != 0)
    {
      printf ("\nrun with sudo!!");
      exit (0);
    }

  if (count != 2)
    {
      printf ("\n%ld  :  Usage: %s <portnum>\n",ts, Argc[0]);
      exit (0);
    }

  // Initialize the SSL library
  SSL_library_init ();
  portnum = Argc[1];
  ctx = InitServerCTX ();	/* initialize SSL */
  char mycert[] = "mycert.pem";
  LoadCertificates (ctx, mycert, mycert);	/* load certs */
  server = OpenListener (atoi (portnum));	/* create server socket */

  struct sockaddr_in addr;
  socklen_t len = sizeof (addr);
  SSL *ssl;

  int cli_fd;
  while (1)
    {
      printf ("\n%ld  :  Server is listening",ts);
      fflush(stdout);
      cli_fd = accept (server, (struct sockaddr *) &addr, &len);	/* accept connection as usual */
      if (cli_fd == -1)
	{
	  perror ("accept");
	  continue;
	}

      //Information about the client
      printf ("\n%ld  :  Connection: %s:%d\n",ts, inet_ntoa (addr.sin_addr),
	      ntohs (addr.sin_port));

      int fd = cli_fd;

      ssl = SSL_new (ctx);	/* get new SSL state with context */
      SSL_set_fd (ssl, fd);	/* set connection socket to SSL state */
      SSL *new_ssl = (SSL *) malloc (sizeof (ssl));
      new_ssl = ssl;

      pthread_t pthread;
      /* Create thread to serve connection to client. */
      if (pthread_create (&pthread, NULL, thread_handler, (void *) new_ssl) !=
	  0)
	{
	  perror ("pthread_create");
	  free (new_ssl);
	  continue;
	}
    }
  pthread_exit (NULL);
  close (server);		/* close server socket */
  SSL_CTX_free (ctx);		/* release context */
}
