int prime(const int n) {
    if(n < 2) return 0; // 0 is not prime
    if(n == 2) return 1; // 2 is prime
    if(n % 2 == 0) return 0; // even numbers are not prime
    for(int i = 3; i*i <= n; i += 2) { // only odd numbers
        if(n % i == 0) return 0; // if n is divisible by i, then n is not prime
    }
    return 1; // n is prime
}