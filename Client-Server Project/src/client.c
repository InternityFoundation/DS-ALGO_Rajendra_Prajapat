/**************************************************************************************************************************
 * 													SSL/TLS client program
 * 													Author: Rajendra Prajapat, Abhishek Bhagate
 * 													
 * 													 
 * 													g++ -Wall -o cli  client.c -L/usr/lib -lssl -lcrypto
 * 													./cli server_ip port_number
 * 													example: ./cli 127.0.0.1 8081
 * 
 * *************************************************************************************************************************/



#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "sha512.hh"
#include <iostream>
#include <string>
#define FAIL    -1


int
OpenConnection (const char *hostname, int port)
{
  int sd;
  struct hostent *host;
  struct sockaddr_in addr;

  if ((host = gethostbyname (hostname)) == NULL)
    {
      perror (hostname);
      abort ();
    }

  sd = socket (PF_INET, SOCK_STREAM, 0);
  bzero (&addr, sizeof (addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons (port);
  addr.sin_addr.s_addr = *(long *) (host->h_addr);

  if (connect (sd, (struct sockaddr *) &addr, sizeof (addr)) != 0)
    {
      close (sd);
      perror (hostname);
      abort ();
    }

  return sd;
}


SSL_CTX *
InitCTX (void)
{
  SSL_METHOD *method;
  SSL_CTX *ctx;
  OpenSSL_add_all_algorithms ();	/* Load all algorithms supported by client */
  SSL_load_error_strings ();	/* load error messages */
  method = (SSL_METHOD*)TLSv1_2_client_method();                                                                    /* Create new client-method instance */
  ctx = SSL_CTX_new (method);	/* Create new context */

  if (ctx == NULL)
    {
      ERR_print_errors_fp (stderr);
      abort ();
    }

  return ctx;
}

void
ShowCerts (SSL * ssl)
{
  X509 *cert;
  char *line;
  cert = SSL_get_peer_certificate (ssl);	/* get the server's certificate */
  if (cert != NULL)
    {
      printf ("\n\tServer certificates:");
      line = X509_NAME_oneline (X509_get_subject_name (cert), 0, 0);
      printf ("\n\tSubject: %s", line);
      free (line);		/* free the malloc'ed string */
      line = X509_NAME_oneline (X509_get_issuer_name (cert), 0, 0);
      printf ("\n\tIssuer: %s", line);
      free (line);		/* free the malloc'ed string */
      X509_free (cert);		/* free the malloc'ed certificate copy */
    }
  else
    printf ("\n\tInfo: No client certificates configured.");
}


int
main (int count, char *strings[])
{
  SSL_CTX *ctx;
  int server;
  SSL *ssl;
  char buf[1024] = { 0 };
  int bytes;
  char *hostname, *portnum;

  if (count != 3)
    {
      printf ("\n\tusage: %s <hostname> <portnum>\n", strings[0]);
      exit (0);
    }

  SSL_library_init ();
  hostname = strings[1];
  portnum = strings[2];
  ctx = InitCTX ();
  server = OpenConnection (hostname, atoi (portnum));
  ssl = SSL_new (ctx);		/* create new SSL connection state */
  SSL_set_fd (ssl, server);

  if (SSL_connect (ssl) == FAIL)	/* check the connection */
    {
      ERR_print_errors_fp (stderr);
    }
  else
    {
      printf ("\n\n\tConnected with %s encryption\n", SSL_get_cipher (ssl));
      ShowCerts (ssl);
      while (1)
        {

          //**************************************************************************
          //SSL_read(ssl, buf, sizeof(buf));  To receive
          //SSL_write(ssl, ServerResponse, strlen(ServerResponse)); To send 
          // NOTE: For every read in server there should be a write method in client 

          /* follwing lines of code write to server stored in to_server */
		  printf("\n\n\tCLIENT-SERVER\n\n\t1. SIGNUP\n\t2. LOGIN\n\t3. Exit\n\t=>\t");
		  char option[2]={0};
		  scanf("%s",option);
          SSL_write (ssl, option, strlen (option)); 
		  if(option[0]=='1'){

			  char to_server_user_name[1024] = { 0 };
		      //printf ("=> Write for server : ");
		      printf("\n\tEnter user_name\t: ");
		      //scanf ("%s", to_server_user_name);
		      fflush(stdin);
		      scanf(" %[^\n]s",to_server_user_name);
		      
		      SSL_write (ssl, to_server_user_name, strlen (to_server_user_name));	/* encrypt & send message */
		      if (strncmp ("exit", to_server_user_name, 4) == 0)
		        {
		          printf ("Client Exit...\n");
		          break;
		        }	
			  printf("\tEnter password\t: ");
			  //scanf(" %[^\n]s",to_server_password);
			  char *pass = getpass("");
			  std::string hash = sw::sha512::calculate(std::string(pass));
			  strcpy(pass,hash.c_str());
  		  	SSL_write (ssl, pass, strlen (pass));	/* encrypt & send message */

		    memset (buf, 0, 1024);
		    bytes = SSL_read (ssl, buf, sizeof (buf));	 //get reply & decrypt 
		    if(!strcmp(buf,"Success")){
          		printf("\n\tUser registeration completed succesfully !\n");
	        }else if(!strcmp(buf,"SameUser")){
	          	printf("\n\tUser with same user-name exists. Try again with different user-name !\n");
	        }else{
	        	printf("\n\tSomething went wrong !");
	        }
		    
		   }


       else if(option[0]=='2'){
        char to_server_user_name[1024] = { 0 },to_server_password[1024]={0};
          //printf ("Write for server2 : ");
          printf("\n\tEnter user_name : ");
          scanf (" %[^\n]s", to_server_user_name);
          SSL_write (ssl, to_server_user_name, strlen (to_server_user_name)); /* encrypt & send message */
          if (strncmp ("exit", to_server_user_name, 4) == 0)
            {
              printf ("\n\tClient Exit...\n");
              break;
            } 
        printf("\tEnter password : ");
        char *pass = getpass("");
        std::string hash = sw::sha512::calculate(std::string(pass));
		strcpy(pass,hash.c_str());
        SSL_write (ssl, pass, strlen (pass)); /* encrypt & send message */

        memset (buf, 0, 1024);
        bytes = SSL_read (ssl, buf, sizeof (buf));   //get reply & decrypt 
        if(bytes<=0)printf("error\n");
        if(strcmp(buf,"Success")){
          printf("\n\tCould not login ! Please check your login credentials again.");
        }else{
          printf("\n\tUser Login succesful !");
          int opt = 0;
          // User will be displayed a menu and will be looped through it until he logs out using exit option
          do{
            printf("\n\n\n\t\tMain Menu\n\n\t1.View Account information\n\t2.Update Account information\n\t3.Delete Account\n\t4.Exit\n\n\tSelect Option=>\t ");
            scanf("%d",&opt);
            switch(opt){
              case 1:{      
              // Views Account information - currently outputs description and contact details information stored in the user account          
                SSL_write (ssl, "1", 1); 
                char desc[1024]={0};
                SSL_read (ssl, desc, sizeof (desc));   //get reply & decrypt 
                printf("\nFrom server : \n\n%s",desc);
                break;
              }
              case 2:{
              	// Will display menu to let user choose what parameter of program he wants to modify and proceed accordingly. 
                SSL_write (ssl, "2", 1); 
                printf("\n\tUpdate you account information :");
                printf("\n\n\tWhat field of your account do you want to upgrade?\n\t1.password\n\t2.description\n\t3.contact\n\tSelect Option\t=> ");
                int opt2;
                scanf("%d",&opt2);
                // Takes new password and updates the current password
                if(opt2==1){
                  SSL_write(ssl,"1",1);
                  printf("\n\tEnter the new password =>\t ");
                  char *pass = getpass("");
                  std::string hash = sw::sha512::calculate(std::string(pass));
			  	  strcpy(pass,hash.c_str());
                  SSL_write(ssl,pass,sizeof(pass));
                }
                // Takes new description and updates the description of account
                else if(opt2==2){
                  SSL_write(ssl,"2",1);
                  printf("\n\tEnter the new description for your account =>\t ");
                  char desc[1024]={0};
                  scanf(" %[^\n]s",desc);
                  SSL_write(ssl,desc,sizeof(desc)); 
                }
                // Takes new contact and updates the description of contact
                else if(opt2==3){
                  SSL_write(ssl,"3",1);
                  printf("\n\tEnter the new contact for your account =>\t ");
                  char cont[1024]={0};
                  scanf(" %[^\n]s",cont);
                  SSL_write(ssl,cont,sizeof(cont)); 
                }        
                // If user presses any other key, nothing will update        
                else{ 
                  printf("\n\tNothing updated !");
                  break;
                }
                // Checking if updation was done successfully on server side          
                SSL_read(ssl,buf,sizeof(buf));
                if(strcmp(buf,"Success")){
                  printf("\n\tSomething went wrong in updating");
                }else{
                  printf("\n\tAccount has been updated successfully !");
                }
                break;
              }
              case 3:{
              	// Will get confirmation from user for account deletion and then delete the user account.
              	// User will be logged out once the account is deleted
                SSL_write (ssl, "3", 1);
                printf("\n\tAre you sure you want to delete your account ? \n\tPress 1 to confirm\n\tPress 0 to cancel\n\t=>\t");
                int opt2;
                scanf("%d",&opt2);
                if(opt2==1){
                  SSL_write(ssl,"Confirm",7);
                  SSL_read(ssl,buf,sizeof(buf));
                  if(strcmp(buf,"Success")){
                    printf("\n\tSomething went wrong in deleting");
                  }else{
                    printf("\n\tAccount has been deleted successfully !");
                    opt=4;
                    break;
                  }
                }else{
                  SSL_write(ssl,"Cancel",6);
                  printf("\n\tExiting delete process...\n\tNothing deleted !");
                }  
                break;
              }
              case 4:{
              	// Exits the loop and logs out the currrently logged in user
                SSL_write (ssl, "4", 1); 
                break;
              }
            }
          }while(opt!=4);

        }   
       }
       else{
       	printf("\n\tExiting...\n");
       	break;
       }		  
          
        }

      SSL_shutdown (ssl);
      SSL_free (ssl);		/* release connection state */
    }

  close (server);		/* close socket */
  SSL_CTX_free (ctx);		/* release context */
  return 0;
}
