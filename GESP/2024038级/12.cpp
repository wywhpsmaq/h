int primes[MAXP], num = 0;
bool isPrime[MAXN] = {false};
void sieve() {
    for (int n = 2; n <= MAXN; n++) {
        if (!isPrime[n]) primes[num++] = n;
        for (int i = 0; i < num && n * primes[i] <= MAXN; i++) {
            isPrime[n * primes[i]] = true;
            if (n % primes[i] == 0) break;
        }
    }
}