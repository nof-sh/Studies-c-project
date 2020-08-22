#include "MAIN.h"

int main(int argc, char *argv[])
{
    int i, numOfErrors = 0;

    if (argc >= 1)
    {
        for (i = 1; i < argc; i++)
        {
            /* First Read */
            numOfErrors += first_pass(argv[i]);

            if (!numOfErrors)
            {
                /* Second Read */
                numOfErrors += secondPass(argv[i]);
            }

            /* If there are no errors */
	        if (!numOfErrors)
	        {
		        /* Create all the output files */
		        ObjectFile(argv[i], IC, DC/*, memoryArr*/);
		        ExternFile(argv[i]/*, linesArr, numOflines*/);
		        EntriesFile(argv[i]);
		        printf("success, output files for \"%s.as\" created.\n", argv[i]);

	        }
	    
        }
        return 1;
    }

    else
        return 0;
        
}
	

