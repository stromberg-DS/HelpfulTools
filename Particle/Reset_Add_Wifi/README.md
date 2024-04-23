This basic code clears out all previous wifi SSIDs and passwords. You will need to create your own file called "credentials.h" and put the wifi info there. "Credentials_EXAMPLE.h" shows what this should look like. "credentials.h" should be saved in the same directory as your code (/src/ most likely). 

"credentials.h" is necessary because it will not be pushed to github with the rest of your code. This allows you to put sensitive info (wifi passwords and such) in your code without sharing it with the world. I have included "credentials_EXAMPLE.h" because it will not be removed and can show what your credentials file will look like. 