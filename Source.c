#include<stdlib.h>
#include<stdio.h>
#include<string.h>

main()
{
	FILE *fp,*fw;
	fp = fopen("F://client_1.bin", "rb+");
	fw = fopen("F://server_1.bin", "wb+");
	char ch;
	char ch1 = '1';char ch0 = '0';
	char msg[100];// = (char*)malloc(sizeof(char));
	char msg1[100];// = (char*)malloc(sizeof(char));
	fread(&ch, sizeof(char), 1, fp);
	fwrite(&ch1, sizeof(char), 1, fw);
	int pointer = 1;
	int pointer2 = 1;
	//printf("%c", ch);
	printf("waiting for connection..\n");
	fclose(fw);
	while (1)
	{
		if (ch == '1')
		{
			rewind(fp);
			fread(&ch, sizeof(char), 1, fp);
		}
		else if (ch == '0')
		{
			fw = fopen("F://server_1.bin", "rb+");
			memset(msg, 0, sizeof(msg));
			fseek(fp, pointer2, SEEK_SET);
			//fread(&length, sizeof(int), 1, fp);
			fread(msg, sizeof(char)*100, 1, fp);
			if (strcmp(msg, "exit") == 0)
				exit(0);
			pointer2 = pointer2+100;
			fseek(fp, 0, SEEK_SET);
			fwrite(&ch1, sizeof(char), 1, fp);
			printf("Client:%s\n", msg);
			//char msg1[100];
			memset(msg1, 0, sizeof(msg1));
			printf("Enter the msg to send:('exit' to exit)\n");
			gets(msg1);
			fseek(fw, pointer, SEEK_SET);
			//length = strlen(msg1);
			fwrite(msg1, sizeof(char) * 100, 1, fw);
			pointer=pointer+100;
			fseek(fw, 0, SEEK_SET);
			fwrite(&ch0, sizeof(char), 1, fw);
			fseek(fp, 0, SEEK_SET);
			fread(&ch, sizeof(char), 1, fp);
			//printf("ch::%c", ch);
			if (strcmp(msg1, "exit") == 0)
				exit(0);
			fclose(fw);
		}
		fseek(fp, 0, SEEK_SET);
		fread(&ch, sizeof(char), 1, fp);


	}
	fclose(fp);
	getch();
	return 0;
}