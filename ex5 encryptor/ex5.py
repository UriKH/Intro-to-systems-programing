from abc import ABC, abstractmethod
import json
import os


# ________________________________________ Utility Functions ________________________________________

def get_abc():
    """
    Creates a list of the abc
    :return: a list of the abc
    """
    return list('abcdefghijklmnopqrstuvwxyz')

# ________________________________________ An Abstract Cipher Class ________________________________________


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


# ________________________________________ Implementation ________________________________________

class CaesarCipher(Cipher):
    """
    Caesar cipher encryption method
    """

    def __init__(self, key):
        abc_map = get_abc()
        super().__init__(key, abc_map)

    def encrypt(self, message):
        encrypted = ''

        for letter in message:
            if not letter.isalpha():
                encrypted += letter
                continue

            is_upper_case = False
            if letter.isupper():
                is_upper_case = True

            letter = self.m_abc[(self.m_abc.index(letter.lower()) + self.m_key) % len(self.m_abc)]
            encrypted += letter.upper() if is_upper_case else letter
        return encrypted

    def decrypt(self, message):
        return CaesarCipher(-self.m_key).encrypt(message)

    def key_shift(self, delta) -> None:
        """
        Shifts the key by some delta
        :param delta: a value to shift the key by
        """
        self.m_key += delta


class VigenereCipher(Cipher):
    """
    Vigenere cipher encryption method
    """

    def __init__(self, key_list):
        """
        Creates a Vigenere cipher encryption
        :param key_list: a list of values as key
        """
        super().__init__([CaesarCipher(value) for value in key_list], get_abc())
        self.m_key_raw = key_list.copy()

    def encrypt(self, message):
        encrypted = ''
        non_alpha_counter = 0

        for i, letter in enumerate(message):
            if not letter.isalpha():
                non_alpha_counter += 1
                encrypted += letter
                continue
            encrypted += self.m_key[(i - non_alpha_counter) % len(self.m_key)].encrypt(letter)
        return encrypted

    def decrypt(self, message):
        reversed_key = [-key for key in self.m_key_raw]
        return VigenereCipher(reversed_key).encrypt(message)


def loadEncryptionSystem(dir_path, plaintext_suffix):
    # open configurations file
    with open(os.path.join(dir_path, 'config.json'), 'r') as jsonFile:
        configurations = json.load(jsonFile)

        configurations['encrypt'] = bool(configurations['encrypt'])
        if configurations['type'] == "Vigenere":
            configurations['type'] = VigenereCipher(configurations['key'])
        else:
            configurations['type'] = CaesarCipher(configurations['key'])

        # encrypt or decrypt every relevant file in the dir
        for filename in os.listdir(dir_path):
            current_file_path = os.path.join(dir_path, filename)
            root, extension = os.path.splitext(current_file_path)
            extension = extension.split('.')[-1]

            if not ((extension == plaintext_suffix and configurations['encrypt'])
                    or (extension == 'enc' and not configurations['encrypt'])):
                continue

            with open(current_file_path, 'r') as file:
                file_data = file.read()

                if configurations['encrypt']:
                    data = configurations['type'].encrypt(file_data)
                    new_file_path = root + '.enc'
                else:
                    data = configurations['type'].decrypt(file_data)
                    new_file_path = root + f'.{plaintext_suffix}'

                with open(new_file_path, 'w') as new_file:
                    new_file.write(data)
