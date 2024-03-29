from abc import ABC, abstractmethod
import json
import os


def get_abc_length() -> int:
    """
    Calculates the length of the abc
    :return: the length of the abc
    """
    return ord('z') - ord('a') + 1


def simplify_key(key: int, abc_length: int):
    """
    Simplifies the key to a none negative small number
    :param key: the key to simplify
    :return: the simplified key
    """
    return key % abc_length if key > 0 else abc_length - ((-key) % abc_length)


class Cipher(ABC):
    """
    Class representation of a general cipher
    """

    @abstractmethod
    def __init__(self, key):
        """
        Creates a cipher
        :param name: the name of the encryption method
        :param key: the encryption key
        """
        self.m_key = key

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
        self.m_abc_length = get_abc_length()
        self.m_shortened_key = simplify_key(key, self.m_abc_length)

    def encrypt(self, message: str) -> str:
        encrypted = ''

        for letter in message:
            if not letter.isalpha():
                encrypted += letter
                continue

            upper_lower = ord('A') if letter.isupper() else ord('a')
            letter_index = (ord(letter) - upper_lower + self.m_shortened_key) % self.m_abc_length
            letter_index += upper_lower
            encrypted += chr(letter_index)
        return encrypted

    def decrypt(self, message: str) -> str:
        temp_decrypt = CaesarCipher(-self.m_shortened_key)
        return temp_decrypt.encrypt(message)

    def key_shift(self, delta: int) -> None:
        """
        Shifts the key by some delta
        :param delta: a value to shift the key by
        """
        self.m_key += delta
        self.m_shortened_key = simplify_key(self.m_key, self.m_abc_length)


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
        self.m_key = key_list.copy()

    def encrypt(self, message: str):
        caesar_key = [CaesarCipher(key) for key in self.m_key]
        encrypted = ''

        space_counter = 0
        for i, letter in enumerate(message):
            if not letter.isalpha():
                space_counter += 1
                encrypted += letter
                continue
            encrypted += caesar_key[(i - space_counter) % len(caesar_key)].encrypt(letter)
        return encrypted

    def decrypt(self, message: str):
        reversed_key = [-key for key in self.m_key]
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
