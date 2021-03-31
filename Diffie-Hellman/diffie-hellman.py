from random import randint
from math import ceil, sqrt

def is_prime(num, primes=[]):
    """ returns True if num is prime. 
    optional parameter primes is a list of known primes 
    """
    
    # 2 is the smallest prime, so anything less is not prime
    if num < 2: return False

    # if its in our list of primes primes we don't need to check it
    if num in primes: return True

    # only ever need to check up to the square root of a value
    limit = ceil(sqrt(num))

    # if our number is divisible by any number from 2 to it's root, it's not prime
    for i in range(2, limit):
        if num % i == 0:
            return False

    # if it's not divisible by any of those, then it's prime!
    return True


def generate_prime(minimum):
    """ generates a prime greater in the range [minimum, minimum**2) """
    
    num = 0
    while (not is_prime(num)):
        num = randint(minimum, minimum**2)
    
    return num


def get_key(keys):
    """ generates a user's public key given their private keys as a tuple """
    return keys[0] * keys[1]


if __name__ == '__main__':
    minimum = 5
    # generate public base and modulus
    """
    p = generate_prime(minimum)
    b = generate_base(p)
    """
    p = 71
    b = 56

    # generate two primes for each user
    Bob = (generate_prime(minimum), generate_prime(minimum))
    Alice = (generate_prime(minimum), generate_prime(minimum))

    # share their public keys
    Bpublic = b**get_key(Bob) % p
    Apublic = b**get_key(Alice) % p

    # compute shared secret number
    Bsecret = Apublic**get_key(Bob) % p
    Asecret = Bpublic**get_key(Alice) % p

    print(f"{Bsecret} and {Asecret} are the secret numbers!")
