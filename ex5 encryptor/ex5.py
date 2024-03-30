from abc import ABC, abstractmethod
import json
import os


def get_abc_map() -> dict:
    """
    Calculates the length of the abc
    :return: the length of the abc
    """
    return {'a': 0, 'b': 1, 'c': 2, 'd': 3, 'e': 4, 'f': 5, 'g': 6, 'h': 7, 'i': 8, 'j': 9, 'k': 10, 'l': 11, 'm': 12,
            'n': 13, 'o': 14, 'p': 15, 'q': 16, 'r': 17, 's': 18, 't': 19, 'u': 20, 'v': 21, 'w': 22, 'x': 23, 'y': 24,
            'z': 25}


def simplify_key(key: int, abc_length: int) -> int:
    """
    Simplifies the key to a none negative small number
    :param key: the key to simplify
    :param abc_length: the length of the abc
    :return: the simplified key
    """
    return key % abc_length if key > 0 else abc_length - ((-key) % abc_length)


def calculate_new_char(alphabet: dict, char: chr, shift: int) -> chr:
    """
    Calculate the new char based on the shift
    :param alphabet: the alphabet to encrypt by
    :param char: the character to shift
    :param shift: the shift of the alphabet by Caesar cipher
    :return: the new character
    """
    swap = [k for k, _ in alphabet.items()]
    return swap[(alphabet[char] + shift) % len(alphabet)]


class Cipher(ABC):
    """
    Class representation of a general cipher
    """

    @abstractmethod
    def __init__(self, key: list | int):
        """
        Creates a cipher
        :param key: the encryption key
        """
        self.m_abc = get_abc_map()
        if type(key) is list:
            self.m_key = [CaesarCipher(value) for value in key]
        elif type(key) is int:
            self.m_key = simplify_key(key, len(self.m_abc))

    @abstractmethod
    def encrypt(self, message: str) -> str:
        """
        Encrypt a message using the key
        :param message: a message to encrypt
        :return: the encrypted message
        """
        pass

    @abstractmethod
    def decrypt(self, message: str) -> str:
        """
        Decrypts a message using the key
        :param message: a message to decrypt
        :return: the decrypted message
        """
        pass


class CaesarCipher(Cipher):
    """
    Caesar cipher encryption method
    """

    def __init__(self, key: int):
        super().__init__(key)

    def encrypt(self, message: str) -> str:
        encrypted = ''
        is_upper_case = False

        for letter in message:
            if not letter.isalpha():
                encrypted += letter
                continue

            if letter.isupper():
                is_upper_case = True

            letter = calculate_new_char(self.m_abc, letter.lower(), self.m_key)
            encrypted += letter.upper() if is_upper_case else letter
            is_upper_case = False
        return encrypted

    def decrypt(self, message: str) -> str:
        temp_decrypt = CaesarCipher(-self.m_key)
        return temp_decrypt.encrypt(message)

    def key_shift(self, delta: int) -> None:
        """
        Shifts the key by some delta
        :param delta: a value to shift the key by
        """
        self.m_key = simplify_key(self.m_key + delta, len(self.m_abc))


class VigenereCipher(Cipher):
    """
    Vigenere cipher encryption method
    """

    def __init__(self, key_list: list[int]):
        """
        Creates a Vigenere cipher encryption
        :param key_list: a list of values as key
        """
        super().__init__(key_list)
        self.m_key_raw = key_list.copy()

    def encrypt(self, message: str):
        # caesar_key = [CaesarCipher(key) for key in self.m_key]
        encrypted = ''

        space_counter = 0
        for i, letter in enumerate(message):
            if not letter.isalpha():
                space_counter += 1
                encrypted += letter
                continue
            encrypted += self.m_key[(i - space_counter) % len(self.m_key)].encrypt(letter)
        return encrypted

    def decrypt(self, message: str):
        reversed_key = [-key for key in self.m_key_raw]
        return VigenereCipher(reversed_key).encrypt(message)


def loadEncryptionSystem(dir_path: str, plaintext_suffix: str):
    with open(os.path.join(dir_path, 'config.json'), 'r') as jsonFile:
        configurations = json.load(jsonFile)

    configurations['encrypt'] = bool(configurations['encrypt'])

    if configurations['type'] == "Caesar":
        configurations['type'] = CaesarCipher(configurations['key'])
    elif configurations['type'] == "Vigenere":
        configurations['type'] = VigenereCipher(configurations['key'])
    else:
        raise ValueError(f'encryption type unknown')

    for filename in os.listdir(dir_path):
        current_file_path = os.path.join(dir_path, filename)
        path_pieces = current_file_path.split('.')

        if not ((path_pieces[-1] == plaintext_suffix and configurations['encrypt'])
                or (path_pieces[-1] == 'enc' and not configurations['encrypt'])):
            continue

        with open(current_file_path, 'r') as file:
            file_data = file.read()

        if configurations['encrypt']:
            data = configurations['type'].encrypt(file_data)
            new_file_path = '.'.join(path_pieces[:-1]) + '.enc'
        else:
            data = configurations['type'].decrypt(file_data)
            new_file_path = '.'.join(path_pieces[:-1]) + f'.{plaintext_suffix}'

        with open(new_file_path, 'w') as file:
            file.write(data)
