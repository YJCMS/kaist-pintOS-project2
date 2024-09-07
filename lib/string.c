#include <string.h>
#include <debug.h>

/* Copies SIZE bytes from SRC to DST, which must not overlap.
   Returns DST. */
/* 겹치지 않아야 하는 SIZE 바이트를 SRC에서 DST로 복사합니다.
	DST를 반환합니다. */
void *
memcpy (void *dst_, const void *src_, size_t size) {
	unsigned char *dst = dst_;
	const unsigned char *src = src_;

	ASSERT (dst != NULL || size == 0);
	ASSERT (src != NULL || size == 0);

	while (size-- > 0)
		*dst++ = *src++;

	return dst_;
}

/* Copies SIZE bytes from SRC to DST, which are allowed to
   overlap.  Returns DST. */
/* 겹칠 수 있는 SIZE 바이트를 SRC에서 DST로 복사합니다.  
	DST를 반환합니다. */
void *
memmove (void *dst_, const void *src_, size_t size) {
	unsigned char *dst = dst_;
	const unsigned char *src = src_;

	ASSERT (dst != NULL || size == 0);
	ASSERT (src != NULL || size == 0);

	if (dst < src) {
		while (size-- > 0)
			*dst++ = *src++;
	} else {
		dst += size;
		src += size;
		while (size-- > 0)
			*--dst = *--src;
	}

	return dst;
}

/* Find the first differing byte in the two blocks of SIZE bytes
   at A and B.  Returns a positive value if the byte in A is
   greater, a negative value if the byte in B is greater, or zero
   if blocks A and B are equal. */
/* 주어진 두 메모리 블록 A와 B에서 서로 다른 첫 번째 바이트를 찾습니다.
	A의 바이트가 더 크면 양수를 반환합니다.
	B의 바이트가 더 크면 음수를 반환합니다.
	A와 B가 같으면 0을 반환합니다. */
int
memcmp (const void *a_, const void *b_, size_t size) {
	const unsigned char *a = a_;
	const unsigned char *b = b_;

	ASSERT (a != NULL || size == 0);
	ASSERT (b != NULL || size == 0);

	for (; size-- > 0; a++, b++)
		if (*a != *b)
			return *a > *b ? +1 : -1;
	return 0;
}

/* Finds the first differing characters in strings A and B.
   Returns a positive value if the character in A (as an unsigned
   char) is greater, a negative value if the character in B (as
   an unsigned char) is greater, or zero if strings A and B are
   equal. */
/* 문자열 A와 B에서 서로 다른 첫 번째 문자를 찾습니다.
   A의 문자가 더 크면 양수를 반환합니다.
   B의 문자가 더 크면 음수를 반환합니다.
   A와 B가 같으면 0을 반환합니다. */
int
strcmp (const char *a_, const char *b_) {
	const unsigned char *a = (const unsigned char *) a_;
	const unsigned char *b = (const unsigned char *) b_;

	ASSERT (a != NULL);
	ASSERT (b != NULL);

	while (*a != '\0' && *a == *b) {
		a++;
		b++;
	}

	return *a < *b ? -1 : *a > *b;
}

/* Returns a pointer to the first occurrence of CH in the first
   SIZE bytes starting at BLOCK.  Returns a null pointer if CH
   does not occur in BLOCK. */
/* BLOCK에서 CH가 처음 나타나는 위치를 가리키는 포인터를 반환합니다.
   BLOCK의 처음 SIZE 바이트 내에서 찾습니다.
   CH가 BLOCK에 없으면 null 포인터를 반환합니다.
*/  
void *
memchr (const void *block_, int ch_, size_t size) {
	const unsigned char *block = block_;
	unsigned char ch = ch_;

	ASSERT (block != NULL || size == 0);

	for (; size-- > 0; block++)
		if (*block == ch)
			return (void *) block;

	return NULL;
}

/* Finds and returns the first occurrence of C in STRING, or a
   null pointer if C does not appear in STRING.  If C == '\0'
   then returns a pointer to the null terminator at the end of
   STRING. */
char *
strchr (const char *string, int c_) {
	char c = c_;

	ASSERT (string);

	for (;;)
		if (*string == c)
			return (char *) string;
		else if (*string == '\0')
			return NULL;
		else
			string++;
}

/* Returns the length of the initial substring of STRING that
   consists of characters that are not in STOP. */
size_t
strcspn (const char *string, const char *stop) {
	size_t length;

	for (length = 0; string[length] != '\0'; length++)
		if (strchr (stop, string[length]) != NULL)
			break;
	return length;
}

/* Returns a pointer to the first character in STRING that is
   also in STOP.  If no character in STRING is in STOP, returns a
   null pointer. */
char *
strpbrk (const char *string, const char *stop) {
	for (; *string != '\0'; string++)
		if (strchr (stop, *string) != NULL)
			return (char *) string;
	return NULL;
}

/* Returns a pointer to the last occurrence of C in STRING.
   Returns a null pointer if C does not occur in STRING. */
char *
strrchr (const char *string, int c_) {
	char c = c_;
	const char *p = NULL;

	for (; *string != '\0'; string++)
		if (*string == c)
			p = string;
	return (char *) p;
}

/* Returns the length of the initial substring of STRING that
   consists of characters in SKIP. */
size_t
strspn (const char *string, const char *skip) {
	size_t length;

	for (length = 0; string[length] != '\0'; length++)
		if (strchr (skip, string[length]) == NULL)
			break;
	return length;
}

/* Returns a pointer to the first occurrence of NEEDLE within
   HAYSTACK.  Returns a null pointer if NEEDLE does not exist
   within HAYSTACK. */
char *
strstr (const char *haystack, const char *needle) {
	size_t haystack_len = strlen (haystack);
	size_t needle_len = strlen (needle);

	if (haystack_len >= needle_len) {
		size_t i;

		for (i = 0; i <= haystack_len - needle_len; i++)
			if (!memcmp (haystack + i, needle, needle_len))
				return (char *) haystack + i;
	}

	return NULL;
}

/* Breaks a string into tokens separated by DELIMITERS.  The
   first time this function is called, S should be the string to
   tokenize, and in subsequent calls it must be a null pointer.
   SAVE_PTR is the address of a `char *' variable used to keep
   track of the tokenizer's position.  The return value each time
   is the next token in the string, or a null pointer if no
   tokens remain.

   This function treats multiple adjacent delimiters as a single
   delimiter.  The returned tokens will never be length 0.
   DELIMITERS may change from one call to the next within a
   single string.

   strtok_r() modifies the string S, changing delimiters to null
   bytes.  Thus, S must be a modifiable string.  String literals,
   in particular, are *not* modifiable in C, even though for
   backward compatibility they are not `const'.

   Example usage:

   char s[] = "  String to  tokenize. ";
   char *token, *save_ptr;

   for (token = strtok_r (s, " ", &save_ptr); token != NULL;
   token = strtok_r (NULL, " ", &save_ptr))
   printf ("'%s'\n", token);

outputs:

'String'
'to'
'tokenize.'
*/
/* 문자열을 DELIMITERS로 구분된 토큰들로 나눕니다.
   첫 호출 시에는 S가 문자열이어야 하며, 이후 호출 시에는 null 포인터여야 합니다.
   SAVE_PTR는 토크나이저의 위치를 추적하는 char * 변수의 주소입니다.
   각 호출에서 다음 토큰을 반환하며, 더 이상 토큰이 없으면 null 포인터를 반환합니다.
   인접한 여러 구분 문자는 하나의 구분 문자로 처리되고, 반환되는 토큰은 빈 문자열이 아닙니다.
   호출마다 DELIMITERS를 변경할 수 있습니다.
   strtok_r()는 문자열 S를 수정하므로, S는 수정 가능한 문자열이어야 하며, 문자열 리터럴은 수정 불가능합니다. */
char *
strtok_r (char *s, const char *delimiters, char **save_ptr) {
	char *token;

	ASSERT (delimiters != NULL);
	ASSERT (save_ptr != NULL);

	/* If S is nonnull, start from it.
	   If S is null, start from saved position. */
	if (s == NULL)
		s = *save_ptr;
	ASSERT (s != NULL);

	/* Skip any DELIMITERS at our current position. */
	while (strchr (delimiters, *s) != NULL) {
		/* strchr() will always return nonnull if we're searching
		   for a null byte, because every string contains a null
		   byte (at the end). */
		if (*s == '\0') {
			*save_ptr = s;
			return NULL;
		}

		s++;
	}

	/* Skip any non-DELIMITERS up to the end of the string. */
	token = s;
	while (strchr (delimiters, *s) == NULL)
		s++;
	if (*s != '\0') {
		*s = '\0';
		*save_ptr = s + 1;
	} else
		*save_ptr = s;
	return token;
}

/* Sets the SIZE bytes in DST to VALUE. */

/* 특정 value으로 size만큼 메모리 초기화 */
void *
memset (void *dst_, int value, size_t size) {
	unsigned char *dst = dst_;

	ASSERT (dst != NULL || size == 0);

	while (size-- > 0)
		*dst++ = value;

	return dst_;
}

/* Returns the length of STRING. */
/* 문자열 길이 반환 */
size_t
strlen (const char *string) {
	const char *p;

	ASSERT (string);

	for (p = string; *p != '\0'; p++)
		continue;
	return p - string;
}

/* If STRING is less than MAXLEN characters in length, returns
   its actual length.  Otherwise, returns MAXLEN. */
size_t
strnlen (const char *string, size_t maxlen) {
	size_t length;

	for (length = 0; string[length] != '\0' && length < maxlen; length++)
		continue;
	return length;
}

/* Copies string SRC to DST.  If SRC is longer than SIZE - 1
   characters, only SIZE - 1 characters are copied.  A null
   terminator is always written to DST, unless SIZE is 0.
   Returns the length of SRC, not including the null terminator.

   strlcpy() is not in the standard C library, but it is an
   increasingly popular extension.  See
http://www.courtesan.com/todd/papers/strlcpy.html for
information on strlcpy(). */
/* 문자열 SRC를 DST로 복사
   만약 SRC의 길이가 SIZE - 1자를 초과하면, 최대 SIZE - 1자까지만 복사
   SIZE가 0이 아닌 경우, DST에는 항상 null 종료 문자가 추가
   SRC의 길이를 반환하며, null 종료 문자는 포함되지 않음
   strlcpy()는 표준 C 라이브러리에 포함되어 있지 않지만, 점점 더 많이 사용되는 확장입니다.*/

// 문자열을 안전하게 복사하며, dst가 src보다 작을 경우에도 버퍼 오버플로우가 발생하지 않도록 처리
// 만약 dst의 크기가 충분하지 않다면, src의 일부만 복사되고 null 종료 문자가 추가됩니다.
// 반환값은 src의 전체 길이로, 이를 통해 호출자는 원본 문자열의 크기를 확인할 수 있습니다.
size_t
strlcpy (char *dst, const char *src, size_t size) {
	size_t src_len;

	ASSERT (dst != NULL);
	ASSERT (src != NULL);

	src_len = strlen (src);
	if (size > 0) {
		size_t dst_len = size - 1;
		if (src_len < dst_len)
			dst_len = src_len;
		memcpy (dst, src, dst_len);
		dst[dst_len] = '\0';
	}
	return src_len;
}

/* Concatenates string SRC to DST.  The concatenated string is
   limited to SIZE - 1 characters.  A null terminator is always
   written to DST, unless SIZE is 0.  Returns the length that the
   concatenated string would have assuming that there was
   sufficient space, not including a null terminator.

   strlcat() is not in the standard C library, but it is an
   increasingly popular extension.  See
http://www.courtesan.com/todd/papers/strlcpy.html for
information on strlcpy(). */
/* 문자열 SRC를 DST에 붙여넣습니다.
   붙여넣은 문자열의 길이는 SIZE - 1자로 제한됩니다.
   SIZE가 0이 아닌 경우, DST에는 항상 null 종료 문자가 추가됩니다.
   충분한 공간이 있었다고 가정할 때, 연결된 문자열의 길이를 반환합니다. (null 종료 문자는 포함되지 않습니다.)
   strlcat()은 표준 C 라이브러리에 포함되어 있지 않지만, 점점 더 많이 사용되는 확장입니다. */

// 이 함수는 문자열을 연결할 때, DST의 버퍼 크기를 초과하지 않도록 조절하며, 안전하게 문자열을 붙여넣습니다.
// DST의 끝에 SRC를 추가하고, 결과 문자열이 null로 종료되도록 합니다.
// 반환값은 SRC와 DST를 연결했을 때의 전체 길이로, 이를 통해 호출자는 연결된 문자열의 전체 길이를 알 수 있습니다.
size_t
strlcat (char *dst, const char *src, size_t size) {
	size_t src_len, dst_len;

	ASSERT (dst != NULL);
	ASSERT (src != NULL);

	src_len = strlen (src);
	dst_len = strlen (dst);
	if (size > 0 && dst_len < size) {
		size_t copy_cnt = size - dst_len - 1;
		if (src_len < copy_cnt)
			copy_cnt = src_len;
		memcpy (dst + dst_len, src, copy_cnt);
		dst[dst_len + copy_cnt] = '\0';
	}
	return src_len + dst_len;
}

