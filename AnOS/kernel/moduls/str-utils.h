#ifndef STRUTILS
#define STRUTILS

static inline void strcopy(char* dst, char* src){
    for(int i = 0; src[i] != '\0'; ++i)
        dst[i] = src[i];
}

static inline int strlength(const char* s){
    int len = 0;
    for(; s[len] != '\0'; ++len);

    return len;
}

static inline int compare(char* str1, char* str2){
    while(*str1 != '\0' && *str1 == *str2){
        ++str1;
        ++str2;
    }
    int result1 = (unsigned char)(*str2) - (unsigned char)(*str1);
    
    return result1;
}

static inline int ncompare(char* str1, char* str2, int count){
    if(count == 0) return 0;
    
    while(count-- > 0 && *str1 && *str2 && *str1 == *str2){
        str1++;
        str2++;
    }
    
    if (count == (unsigned int)-1)
        return 0;
    else
        return (unsigned char)*str1 - (unsigned char)*str2;
}

#endif // STRUTILS