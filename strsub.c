#include <stdio.h>
#include <stdlib.h>

void usage() {
	printf("strsub <pattern> <sub> <string>\nInput a pattern to replace, what to replace it with, and the string to perform the operation on.\n");
}

/**
 * Compute length of a string by finding the number of characters before the null terminator ('\0')
 *
 * @param char *x string to find the length of
 */
int len(char *x) {
	int l = 0;
	while (1) {
		if (*x == '\0') {
			return l;
		}
		l++;
		x++;
	}
	return l;
}

/**
 * Finds if two strings are equal when restricting the comparison to a certain length
 *
 * @param x one string
 * @param y the other string
 * @param lx the length of x to look in
 * @param ly the length of y to look in
 */
int streqBound(char *x, char *y, int lx, int ly) {	
	if (lx != ly) {
		return 0;
	}
	for (int i = 0; i < lx; i++) {
		if ( *(x + i) != *(y + i) ) {
			return 0;
		}
	}
	return 1;
}

/**
 * Finds locations of a given pattern inside a larger text, and the number of times the pattern occurs.
 *
 * @param pattern the pattern to search for
 * @param x where to search for pattern
 * @param lP length of pattern
 * @param lX length of x
 * 
 * @return pointer, which first points to the number of matches. The index of all the other matches are stored in the addresses that follow
 */
int *findMatches(char* pattern, char *x, int lP, int lX) {
	int nMatches = 0;
	for (int i = 0; i < lX - lP + 1; i++) {
		if (streqBound(pattern, x+i, lP, lP)) {
			nMatches++;
		}
	}
	int *result = (int *) malloc((nMatches + 1) * sizeof(int));
	*result = nMatches;
	int matchesMatched = 0;
	for (int i = 0; i < lX - lP + 1 && matchesMatched < nMatches; i++) {
		if (streqBound(pattern, x+i, lP, lP)) {
			matchesMatched++;
			*(result + matchesMatched) = i;
		}
	}
	return result;
}

/**
 * Helper function to print out the value returned by findMatches
 *
 * @param matches value returned by findMatches
 */
void printMatches(int *matches) {
	int n = *matches;
	printf("nMatches: %d\n", n);
	for (int i = 1; i <= n; i++) {
		printf("%d ", *(matches + i));
	}
	printf("\n");
}

int main(int argc, char** argv) {
	if (argc < 3) {
		usage();
		return 1;
	}
	char *pattern = *(argv + 1);
	char *sub = *(argv + 2);
	char *x = *(argv + 3);
	int lP = len(pattern);
	int lS = len(sub);
	int lX = len(x);
	int lenEq = lP == lS;
	// can modify in place, and only need to do one pass
	if (lenEq){
		if (lP == 1) {
			for (int i = 0; i < lX; i++) {
				if (*(x + i) == *pattern) {
					*(x + i) = *sub;
				}
			}
		} else {
			int j = 1;
			for (int i = 0; i < lX - lP + 1; i++) {
				if ((*x + i) == *pattern) {
					int matching = 1;
					while (matching && j < lP) {
						matching = *(x + i + j) == *(pattern + j);
						j++;
					}
					if (matching) {
						for (int c = 0; c < lP; c++) {
							*(x + i + c) = *(sub + c);
						}
					}
				}
			}
		}
		printf("%s\n", x);
	} else {
		// calculate the length of the resulting string by getting the difference between the
		// pattern and its replacement, multiplying it by the number of times it will appear,
		// and then adding that to the length of the original string
		int *matches = findMatches(pattern, x, lP, lX);
		int nMatches = *matches++;
		int lR = nMatches * (lS - lP) + lX;
		char *result = (char *) malloc( lR * sizeof(char));
		int i = 0;
		int j = 0;
		int matchesMatched = 0;
		int offset = lS - lP;
		while (i < lX) {
			if (matchesMatched < nMatches && i == *(matches)){
				for (int j = 0; j < lS; j++) {
					*(result + i + offset * matchesMatched + j) = *(sub + j);
				}
				matchesMatched++;
				matches++;
				i += lP - 1;
			} else {
				*(result + i + offset * matchesMatched) = *(x + i);
			}	
			i++;
		}
		printf("%s\n", result);
	}
	return 0;

}

