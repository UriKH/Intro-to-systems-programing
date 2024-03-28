from abc import ABC, abstractmethod
import json
import os


class Cipher(ABC):
    """
    Class representation of a general cipher
    """

    @abstractmethod
    def __init__(self, name: str, key):
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

    @classmethod
    def get_name(cls) -> str:
        """
        Gets the name of the encryption method
        :return: name of the method
        """
        pass


class CaesarCipher(Cipher):
    """
    Caesar cipher encryption method
    """
    ABC_LENGTH = ord('z') - ord('a') + 1

    def __init__(self, key: int):
        super().__init__('Caesar', key)
        self.m_shortened_key = CaesarCipher.simplify_key(key)

    def encrypt(self, message: str) -> str:
        encrypted = ''

        for letter in message:
            if not letter.isalpha():
                encrypted += letter
                continue

            upper_lower = ord('A') if letter.isupper() else ord('a')
            letter_index = (ord(letter) - upper_lower + self.m_shortened_key) % self.ABC_LENGTH
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
        self.m_shortened_key = CaesarCipher.simplify_key(self.m_key)

    @classmethod
    def simplify_key(cls, key: int):
        """
        Simplifies the key to a none negative small number
        :param key: the key to simplify
        :return: the simplified key
        """
        return key % cls.ABC_LENGTH if key > 0 else cls.ABC_LENGTH - ((-key) % cls.ABC_LENGTH)

    @classmethod
    def get_name(cls) -> str:
        return "Caesar"


class VigenereCipher(Cipher):
    def __init__(self, key_list: list):
        super().__init__('Vigenere', key_list)
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

    @classmethod
    def get_name(cls) -> str:
        return "Vigenere"


# def print_cipher(message: str, cipher: Cipher):
#     print(f'original: {message}\n'
#           f'encrypted: {cipher.encrypt(message)}\n'
#           f'decrypted: {cipher.decrypt(cipher.encrypt(message))}\n')


def loadEncryptionSystem(dir_path: str, plaintext_suffix: str):
    with open(os.path.join(dir_path, 'config.json'), 'r') as jsonFile:
        configurations = json.load(jsonFile)

    configurations['encrypt'] = bool(configurations['encrypt'])

    if configurations['type'] == CaesarCipher.get_name():
        configurations['type'] = CaesarCipher(configurations['key'])
    elif configurations['type'] == VigenereCipher.get_name():
        configurations['type'] = VigenereCipher(configurations['key'])
    else:
        raise ValueError(f'encryption type must be: {CaesarCipher.get_name()} or {VigenereCipher.get_name()}')

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
