from abc import ABC, abstractmethod
import json
import os


def get_abc_map():
    """
    Creates an abc to letter index map
    :return: the mapped abc
    """
    return {char: i for i, char in enumerate(list('abcdefghijklmnopqrstuvwxyz'))}


def simplify_key(key, abc_length):
    """
    Simplifies the key to a none negative small number
    :param key: the key to simplify
    :param abc_length: the length of the abc
    :return: the simplified key
    """
    return key % abc_length if key > 0 else abc_length - ((-key) % abc_length)


def calculate_new_char(alphabet, char, shift):
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
    def __init__(self, key, abc_map):
        """
        Creates a cipher
        :param key: the encryption key
        :param abc_map: letter to index mapping dictionary 
        """
        self.m_abc = abc_map
        self.m_key = key
    
    @abstractmethod
    def encrypt(self, message):
        """
        Encrypt a message using the key
        :param message: a message to encrypt
        :return: the encrypted message
        """
        pass

    @abstractmethod
    def decrypt(self, message):
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

    def __init__(self, key):
        abc_map = get_abc_map()
        super().__init__(simplify_key(key, len(abc_map)), abc_map)

    def encrypt(self, message):
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

    def decrypt(self, message):
        temp_decrypt = CaesarCipher(-self.m_key)
        return temp_decrypt.encrypt(message)

    def key_shift(self, delta) -> None:
        """
        Shifts the key by some delta
        :param delta: a value to shift the key by
        """
        self.m_key = simplify_key(self.m_key + delta, len(self.m_abc))


class VigenereCipher(Cipher):
    """
    Vigenere cipher encryption method
    """

    def __init__(self, key_list):
        """
        Creates a Vigenere cipher encryption
        :param key_list: a list of values as key
        """
        super().__init__([CaesarCipher(value) for value in key_list], get_abc_map())
        self.m_key_raw = key_list.copy()

    def encrypt(self, message):
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

    def decrypt(self, message):
        reversed_key = [-key for key in self.m_key_raw]
        return VigenereCipher(reversed_key).encrypt(message)


def loadEncryptionSystem(dir_path, plaintext_suffix):
    # open configurations file
    with open(os.path.join(dir_path, 'config.json'), 'r') as jsonFile:
        configurations = json.load(jsonFile)

    if configurations['type'] == "Vigenere":
        configurations['type'] = VigenereCipher(configurations['key'])
    else:
        configurations['type'] = CaesarCipher(configurations['key'])
    
    # encrypt or decrypt every relevant file in the dir
    for filename in os.listdir(dir_path):
        current_file_path = os.path.join(dir_path, filename)
        path_pieces = current_file_path.split('.')

        if not ((path_pieces[-1] == plaintext_suffix and configurations['encrypt'])
                or (path_pieces[-1] == 'enc' and not configurations['encrypt'])):
            continue

        with open(current_file_path, 'r') as file:
            file_data = file.read()

        if configurations['encrypt'] == 'True':
            data = configurations['type'].encrypt(file_data)
            new_file_path = '.'.join(path_pieces[:-1]) + '.enc'
        else:
            data = configurations['type'].decrypt(file_data)
            new_file_path = '.'.join(path_pieces[:-1]) + f'.{plaintext_suffix}'

        with open(new_file_path, 'w') as file:
            file.write(data)
