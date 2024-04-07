#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<math.h>
#include<string.h>

void encrypt(char s[], int n) {
	for (int i = 0; s[i] != 0; i++)
	{
		if (s[i] >= 97 && s[i] <= 122)
			s[i] = 'a' + ((s[i] - 'a' + n) % 26 + 26) % 26;
		else
			if (s[i] >= 65 && s[i] <= 90)
				s[i] = 'A' + ((s[i] - 'A' + n) % 26 + 26) % 26; // so basically we add another 26 because when a number x < 26, x % 26 = x, therefore the program works for negative keys as well
	}
}

float e[26] = { 8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0 ,6.1 ,7.0, 0.2, 0.8, 4.0, 2.4, 6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1 };

float distance(int x[])
{
	float sum = 0;
	for (int i = 'a'; i <= 'z'; i++) {
		float e1 = e[i - 'a'];
		sum += ((x[i] - e1) * (x[i] - e1)) / e1;
	}
	return sum;
}

int main()
{
	FILE* fp;
	fp = fopen("distribution.txt", "w");

	char str[500], enc[500];
	int c[400] = { 0 };
	int index = 0;
	fgets(str, sizeof(str), stdin); //read the string from user
	
	for (int i = 0; str[i] != '\0'; i++)
		c[str[i]]++; //count the occurency of the letters

	for (int i = 'a'; i <= 'z'; i++)
	{
		fprintf(fp, "%d\n", c[i]); //add occurences to file
	}
	
	float mini = 99999;
	for (int i = 'a'; i <= 'z'; i++) { //str
		int c[500] = { 0 }; //frequency vector for occurences of letter in text
		strcpy(enc, str);
		encrypt(enc, i - 'a'); //shift to all possibilities of a letter
		for (int i = 0; enc[i] != '\0'; i++)
			c[enc[i]]++; //we count the number of ocurrences and add them to the vector

		float d = distance(c);
		if (d < mini) {
			mini = d;
			index = i - 'a'; //we store the index which shifts the text to a more likely one
		}

	}
	encrypt(str,index);

	printf("%s", str);

	return 0;
}