#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/csapp.h" 


#define LINESIZE 25 

// Number file directories open at a time
#define NFD 4
#define DEBUG 1
#define MAXNAMESIZE 256
#define BUFFLEN 128

char* directory_a, *directory_b;

int search_a(const char *fpath, const struct stat *sb,int typeflag);
int remove_from_b(const char *fpath, const struct stat *sb,int typeflag);

int main(int argc, char* argv[])
{
    

    /* Check for wrong arguments */
    if(argc != 3)
        return -1;
    
    /* Get directorys from arguments */
    directory_a = argv[1];
    directory_b = argv[2];
    
    int rv;
    /* Traverse the directory a */
    rv = ftw(directory_a,&search_a,1);
    if(rv !=0)
    {
        printf("Error with directory search, a\nError code: %d\n",rv);
        exit(-1);
    }
    /* Traverse directory b */
    rv = ftw(directory_b,&remove_from_b,1);
    if(rv !=0)
    {
        printf("Error with directory search, b\nError code: %d\n",rv);
        exit(-1);
    }
    return 0;
}

/* Removes any files that are contained in directory b but not in directory a */
int remove_from_b(const char *fpath, const struct stat *sb,int typeflag)
{
    /* Skip directory */
    if(memcmp(fpath,"./b\0",4) == 0)
        return 0;
    
    /* Create expected filepath a by replacing b*/
    char *path_a = malloc(MAXNAMESIZE);;
    strcpy(path_a,fpath);

    char *iter = path_a;
    while(*iter != 'b')
    {
        iter++;
    }
    /* replace b */
    *iter = 'a';

    /* Fle doesn't exists in a, remove from directory b */
    if(access(path_a,F_OK) == -1)
    {
        remove(fpath);
        printf("File found in b thats not in a, removed file from b\n");
    }

}

/* Duplicates any files in directory A that are missing from directory b
*  and replaces duplicate files with the most up to date version 
*/
int search_a(const char *fpath, const struct stat *sb,int typeflag)
{
    /* Skip director a */
    if(memcmp(fpath,"./a\0",4) == 0)
        return 0;

    /* Generate expected file path for b */
    char *path_b = malloc(MAXNAMESIZE);;
    strcpy(path_b,fpath);
    char *iter = path_b;
    while(*iter != 'a')
    {
        iter++;
    }
    
    /* replace a with b */
    *iter = 'b';

    /* Fle exists in b */
    if(access(path_b,F_OK) != -1)
    {
        int fdb = open(path_b,O_RDWR);
        int fda = open(fpath,O_RDWR);

        struct stat stat_b;
        Stat(path_b, &stat_b);

        if(stat_b.st_mtim.tv_sec < sb->st_mtim.tv_sec)
        {
            /* Reopen with trunc argument to clear contents */
            close(fdb);
            fdb = open(path_b, O_TRUNC|O_RDWR);
            
            size_t read_count=1;
            char buff[BUFFLEN];

            /* Read contents of file a and write to file b */
            while((read_count = rio_readn(fda,buff,BUFFLEN)) != 0)
            {
                rio_writen(fdb,buff,read_count);
            }

            /* Close both files */
            close(fdb);
            close(fda);
            printf("Updated file b from file a\n");
        }
        else
        {           
            /* Reopent iwth trunc to clear contents */
            close(fda);
            fda = open(fpath, O_TRUNC|O_RDWR);

            int read_count=1;
            char buff[BUFFLEN];

            /* Read contents of file a and write to file b */
            while((read_count = rio_readn(fdb,buff,BUFFLEN)) != 0)
            {
                rio_writen(fda,buff,read_count);
            }

            /* Close both files */
            close(fdb);
            close(fda);
            printf("Updated file a from file b\n");
        }
    }
    else
    {
        /* Open and create file b and open file a for writing */
        int fdb = open(path_b,O_CREAT|O_TRUNC|O_RDWR);
        int fda = open(fpath,O_RDWR);

        size_t read_count=1;
        char buff[BUFFLEN];

        /* Read contents of file a and write to file b */
        while((read_count = Rio_readn(fda,buff,BUFFLEN-1)) != 0)
        {
            Rio_writen(fdb,buff,read_count);
        }

        /* Update file permissions of b to match a and close both files */
        chmod(path_b,sb->st_mode);
        close(fdb);
        close(fda);
        printf("File in a not found in b\n added file a to b\n");
    }

    return 0;
}
