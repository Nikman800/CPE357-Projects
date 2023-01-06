#include <stdio.h>

int main() {
	int c, i,charnum;
	i = 0;
	charnum = 0;

	while ((c = getchar()) != EOF) { /*EOF is nothing*/
		if (c == '\t') {
			while (i < 8) {
				putchar(' ');
				i++;
				charnum++;
			}
			i = 0;
		}
		else if (c == '\b') {
			i--;
			charnum--;
			
			/*if (charnum < 0) { when char no goes below zero*/
				/*return 0; error statement*/
			if (charnum < 0) {
				charnum = 0;
				i = 0;
			}
			if (i == -1) { /*when i goes below zero*/
				i = 7;
			}
			putchar(c);
		}
		else if (c == '\n') {
			i = 0;
			charnum = 0;
			putchar('\n');
		}
		else {
			putchar(c);
			i++;
			charnum++;
			if (i >= 8) {
				i = 0;
			}
		}
	}
	return 0;
}
