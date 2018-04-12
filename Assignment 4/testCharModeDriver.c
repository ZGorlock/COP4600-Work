#include "testCharModeDriver.h"


static char receive[BUFFER_LENGTH]; 


int main(void) {
	int ret, fd, fd2;
	char stringToSend[BUFFER_LENGTH];
   
	printf("Starting device test code example...\n");
	fd = open("/dev/chardriverin", O_RDWR);             // Open the device with read/write access
	fd2 = open("/dev/chardriverout", O_RDWR);             // Open the device with read/write access
	if (fd < 0 || fd2 < 0){
		perror("Failed to open the device...");
		return errno;
	}


	printf("\nTesting normal read/write\n");
	char stringToSend1[BUFFER_LENGTH];
	strncpy(stringToSend1, "Testing testing 123", BUFFER_LENGTH);

	ret = write(fd, stringToSend1, strlen(stringToSend1));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend1);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, strlen(stringToSend1));
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);


	printf("\nTesting max read/write\n");
	char stringToSend2[BUFFER_LENGTH];
	strncpy(stringToSend2, "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", BUFFER_LENGTH);

	ret = write(fd, stringToSend2, strlen(stringToSend2));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend2);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, strlen(stringToSend2));
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);


	printf("\nTesting consecutive read/write\n");
	char stringToSend3a[BUFFER_LENGTH];
	strncpy(stringToSend3a, "1", 1);

	ret = write(fd, stringToSend3a, 1);
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend3a);

	char stringToSend3b[BUFFER_LENGTH];
	strncpy(stringToSend3b, "2", 1);

	ret = write(fd, stringToSend3b, 1);
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend3b);

	char stringToSend3c[BUFFER_LENGTH];
	strncpy(stringToSend3c, "3", 1);

	ret = write(fd, stringToSend3c, 1);
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend3c);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, 1);
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, 1);
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, 1);
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);


	printf("\nTesting write overflow\n");
	char stringToSend4[BUFFER_LENGTH];
	strncpy(stringToSend4, "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", BUFFER_LENGTH);

	ret = write(fd, stringToSend4, strlen(stringToSend4));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend4);

	char stringToSend5[BUFFER_LENGTH];
	strncpy(stringToSend5, "1111", BUFFER_LENGTH); //only 3 spaces available

	ret = write(fd, stringToSend5, strlen(stringToSend5));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend5);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, BUFFER_LENGTH);
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);


	printf("\nTesting read underflow\n");
	char stringToSend6[BUFFER_LENGTH];
	strncpy(stringToSend6, "111", BUFFER_LENGTH);

	ret = write(fd, stringToSend6, strlen(stringToSend6));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend6);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, 4); //only 3 characters available
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);

	
	printf("\nTesting 'UCF'\n");
	char stringToSend7[BUFFER_LENGTH];
	strncpy(stringToSend7, "UCF", BUFFER_LENGTH);

	ret = write(fd, stringToSend7, strlen(stringToSend7));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend7);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, BUFFER_LENGTH);
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);

	
	printf("\nTesting '.*UCF'\n");
	char stringToSend8[BUFFER_LENGTH];
	strncpy(stringToSend8, "abcdUCF", BUFFER_LENGTH);

	ret = write(fd, stringToSend8, strlen(stringToSend8));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend8);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, BUFFER_LENGTH);
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);

	
	printf("\nTesting '.*UCF.*'\n");
	char stringToSend9[BUFFER_LENGTH];
	strncpy(stringToSend9, "abcdUCFabcd", BUFFER_LENGTH);

	ret = write(fd, stringToSend9, strlen(stringToSend9));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend9);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, BUFFER_LENGTH);
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);

	
	printf("\nTesting multiwrite 'UCF'\n");
	char stringToSend10a[BUFFER_LENGTH];
	strncpy(stringToSend10a, "U", BUFFER_LENGTH);

	ret = write(fd, stringToSend10a, strlen(stringToSend10a));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend10a);
	
	char stringToSend10b[BUFFER_LENGTH];
	strncpy(stringToSend10b, "C", BUFFER_LENGTH);

	ret = write(fd, stringToSend10b, strlen(stringToSend10b));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend10b);
	
	char stringToSend10c[BUFFER_LENGTH];
	strncpy(stringToSend10c, "F", BUFFER_LENGTH);

	ret = write(fd, stringToSend10c, strlen(stringToSend10c));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend10c);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, BUFFER_LENGTH);
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);

	
	printf("\nTesting multiwrite '.*UCF.*'\n");
	char stringToSend11a[BUFFER_LENGTH];
	strncpy(stringToSend11a, "testingtestingU", BUFFER_LENGTH);

	ret = write(fd, stringToSend11a, strlen(stringToSend11a));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend11a);
	
	char stringToSend11b[BUFFER_LENGTH];
	strncpy(stringToSend11b, "C", BUFFER_LENGTH);

	ret = write(fd, stringToSend11b, strlen(stringToSend11b));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend11b);
	
	char stringToSend11c[BUFFER_LENGTH];
	strncpy(stringToSend11c, "Ftestingtesting", BUFFER_LENGTH);

	ret = write(fd, stringToSend11c, strlen(stringToSend11c));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend11c);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, BUFFER_LENGTH);
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);

	
	printf("\nTesting multiwrite '.*U.*C.*F.*'\n");
	char stringToSend12a[BUFFER_LENGTH];
	strncpy(stringToSend12a, "testingtestingU", BUFFER_LENGTH);

	ret = write(fd, stringToSend12a, strlen(stringToSend12a));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend12a);
	
	char stringToSend12b[BUFFER_LENGTH];
	strncpy(stringToSend12b, "Ctestingtesting", BUFFER_LENGTH);

	ret = write(fd, stringToSend12b, strlen(stringToSend12b));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend12b);
	
	char stringToSend12c[BUFFER_LENGTH];
	strncpy(stringToSend12c, "Ftestingtesting", BUFFER_LENGTH);

	ret = write(fd, stringToSend12c, strlen(stringToSend12c));
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Wrote [%s]\n", stringToSend12c);

	memset(&receive[0], 0, sizeof(receive));
	ret = read(fd2, receive, BUFFER_LENGTH);
	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("Read  [%s]\n", receive);
	

	close(fd);
	close(fd2);


	return SUCCESS;



	//printf("Type in a short string to send to the kernel module:\n");
	//scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)
	//printf("Writing message to the device [%s].\n", stringToSend);
	//ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
	//if (ret < 0){
	//	perror("Failed to write the message to the device.");
	//	return errno;
	//}
 
	//printf("Press ENTER to read back from the device...\n");
	//getchar();
 
	//printf("Reading from the device...\n");
	//ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM
	//if (ret < 0){
	//	perror("Failed to read the message from the device.");
	//	return errno;
	//}
   
	//printf("The received message is: [%s]\n", receive);
	//printf("End of the program\n");
   
	//return SUCCESS;
}
