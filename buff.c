
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* 
    1. added comment here above main to check git \\
    2. adding this to check amend option to the earlier commit
    3. added to check the diffs commands:
*/


int main(int argc, char* argv[])
{

    int pgm_msg_send_max = 2;
    int msg_sending_count = 0;
    char send_msg_content[] = "PGMSendMsg:with#\0";
    char msg_buff[1024], *cptr;

    cptr = (char *)malloc(1024 * sizeof(char));

     if (0 > argc)
     {
         pgm_msg_send_max = atoi (argv[1]);
        printf(" here msg count is %d \n",pgm_msg_send_max);
    }

    while (msg_sending_count < pgm_msg_send_max) {

                int str_len_cnt = 0;
                sprintf (cptr, "%s%d",send_msg_content,msg_sending_count);
                cptr[sizeof(send_msg_content)+sizeof(msg_sending_count)+1] = '\0';
                 str_len_cnt = strlen(send_msg_content);
                msg_sending_count++;
                printf("msg is now with %d: %s \n",msg_sending_count,send_msg_content);
            }

    printf("done \n");

    return 0;
}



