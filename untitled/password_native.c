#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

static uint64_t fnv1a(const char *s) {
    uint64_t h = 1469598103934665603ULL;
    while (*s) {
        h ^= (unsigned char)*s++;
        h *= 1099511628211ULL;
    }
    return h;
}

static void trim_newline(char *s) {
    s[strcspn(s, "\r\n")] = '\0';
}

static void read_line(const char *prompt, char *buf, size_t n) {
    fputs(prompt, stdout);
    fflush(stdout);
    if (!fgets(buf, (int)n, stdin)) exit(1);
    trim_newline(buf);
}

int main(void) {
    char long_s[32], fav[256], name[256], shoe[256], shirt[256];
    char hashbuf[32];
    const char *special = "~!@#$%^&*()_+`-={}|[]:\"'<>?,./";

    read_line("How long should the password be?: ", long_s, sizeof long_s);
    read_line("what is your favorite number?: ", fav, sizeof fav);
    read_line("Give a food name: ", name, sizeof name);
    read_line("What brand of shoes you wear?: ", shoe, sizeof shoe);
    read_line("What color is your shirt: ", shirt, sizeof shirt);

    long requested = strtol(long_s, NULL, 10);
    if (requested < 0 || requested > 1000000) {
        fputs("Invalid password length.\n", stderr);
        return 1;
    }

    snprintf(hashbuf, sizeof hashbuf, "%llu", (unsigned long long)fnv1a(fav));

    const char *pools[4] = { hashbuf, name, special, shoe };
    size_t lens[4] = { strlen(hashbuf), strlen(name), strlen(special), strlen(shoe) };

    /* Original Python reads shirt/hash(short), but does not put them in ol. */
    (void)shirt;

    char *password = malloc((size_t)requested + 1);
    if (!password) return 1;

    srand((unsigned)time(NULL) ^ (unsigned)(uintptr_t)password);
    for (long i = 0; i < requested; ++i) {
        int pool;
        do { pool = rand() % 4; } while (lens[pool] == 0);
        password[i] = pools[pool][rand() % lens[pool]];
    }
    password[requested] = '\0';

    printf("Your new password is: %s\n", password);

    char shuffle[16];
    read_line("Do you want to shuffle your password? y/n: ", shuffle, sizeof shuffle);
    if (shuffle[0] == 'y') {
        for (long i = requested - 1; i > 0; --i) {
            long j = rand() % (i + 1);
            char t = password[i];
            password[i] = password[j];
            password[j] = t;
        }

        putchar('[');
        for (long i = 0; i < requested; ++i) {
            if (i) fputs(", ", stdout);
            printf("'%c'", password[i]);
        }
        puts("]");
    }

    free(password);
    return 0;
}
