#include "csapp.h"
#include <ftw.h>
/* Globals */
char* search_str;
char* replace_str;
char* prepend_str;

static int f_search(const char* fpath, const struct stat *sb, int tFlag,struct FTW * ftwbuf)
{
    /* Don't try and open the source directory */
    if(strcmp(fpath, "./testdir\0") == 0)
    {
        printf("File is actually directory\n");
        return 0;
    }
    
    /* Open temporary file */
    int fd = open(fpath,O_RDWR);
    int temp_fd = open("tempfile",O_CREAT|O_RDWR|O_TRUNC);

    /* Change permissions */
    chmod("tempfile",S_IWUSR|S_IRUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    
    char current_char;
    int read;
    int index;
    int found_index = 0;
    int str_found = 0;

    printf("Searching file %s for string %s\n",fpath,search_str);
    
    /* Search and replace search string */
    while((read = rio_readn(fd,&current_char,1)) > 0)
    {
        /* If character is in follow sequence */
        if(current_char == search_str[found_index])
        {
            printf("Found character: %c\n",current_char);
            found_index++;

            /* Sequence found, replace in temp file */
            if(found_index == (strlen(search_str)))
            {
                printf("Replacing string\n");
                Rio_writen(temp_fd,replace_str,strlen(replace_str));
                str_found = 1;
                found_index = 0;
            }
        }
        else
        {
            int i;
            /* Print any sequence partial segments */
            if(found_index != 0)
                Rio_writen(temp_fd,search_str,found_index);

            /* Write current character */
            Rio_writen(temp_fd,&current_char,1);
            found_index = 0;
        }

        /* Increment index */
        index++;
    }

    printf("Search string %s\n",str_found ? "found" : "not found, searching for prepend string");

    /* Close and reopen files to return to begginning */
    close(fd);
    close(temp_fd);
    fd = open(fpath,O_TRUNC|O_RDWR);
    temp_fd = open("tempfile",O_RDWR);


    /* Reset variables */
    found_index = 0;
    index = 0;

    /* Check if string was found and replaced */
    if(!str_found)
    while((read = rio_readn(temp_fd,&current_char,1)) > 0)
    {
        /* Prepend sequence is detected */
        if(current_char == prepend_str[found_index])
        {
            found_index++;
            if(found_index == strlen(prepend_str))
            {
                printf("Prepend string %s found,prepending search string %s\n",prepend_str,search_str);
                Rio_writen(fd,search_str,strlen(search_str));
                Rio_writen(fd,prepend_str,strlen(prepend_str));
                found_index = 0;
            }
        }
        else
        {
            int i;
            /* Write partial prepend segment */
            if(found_index > 0)
                Rio_writen(fd,prepend_str,found_index);

            /* Write current character */
            Rio_writen(fd,&current_char,1);
            found_index = 0;
        }

        /* Increment index */
        index++;
    }
    else
    {
        printf("Copying temporary file contents to %s\n",fpath);
        /* Search string found, copy contents of temporary file to original file */
        char buff[50];
        while((read = rio_readn(temp_fd,&buff,50)) > 0)
        {
            Rio_writen(fd,&buff,read);
        }
    }

    /* Close files */
    close(fd);
    close(temp_fd);

    return 0;
}

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        printf("Incorrect number of arguments\n");
        exit(-1);
    }

    /* Get parameters */ 
    search_str = argv[1];
    replace_str = argv[2];
    prepend_str = argv[3];
    char search_d[] = "./testdir";
   
    /* Search files */
    int rv;
    rv = ftw(search_d,f_search,1);


    return 0;
}

