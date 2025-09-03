# utils.py
import os
import base64
import hashlib
import pickle
import sys
from datetime import datetime
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
import secrets
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives import hmac
from cryptography.hazmat.primitives import keywrap
if getattr(sys, 'frozen', False):
    BASE_DIR = os.path.dirname(sys.executable)
else:
    BASE_DIR = os.path.dirname(__file__)
# AES加密
AES_KEY = hashlib.sha256(b'rc_key').digest()  # 32字节密钥
GCM_IV_SIZE = 12
GCM_TAG_SIZE = 16

def encrypt(data: bytes, key: bytes = AES_KEY) -> bytes:
    iv = secrets.token_bytes(GCM_IV_SIZE)
    cipher = Cipher(algorithms.AES(key), modes.GCM(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    ct = encryptor.update(data) + encryptor.finalize()
    tag = encryptor.tag
    # 返回: base64(IV+tag+密文)
    return base64.b64encode(iv + tag + ct)

def decrypt(data: bytes, key: bytes = AES_KEY) -> bytes:
    raw = base64.b64decode(data)
    iv = raw[:GCM_IV_SIZE]
    tag = raw[GCM_IV_SIZE:GCM_IV_SIZE+GCM_TAG_SIZE]
    ct = raw[GCM_IV_SIZE+GCM_TAG_SIZE:]
    cipher = Cipher(algorithms.AES(key), modes.GCM(iv, tag), backend=default_backend())
    decryptor = cipher.decryptor()
    return decryptor.update(ct) + decryptor.finalize()
PASS_HASH_FILE = os.path.join(BASE_DIR, 'data', 'password.dat')
def check_password(input_pwd: str, idx: int = 0) -> bool:
    if not os.path.exists(PASS_HASH_FILE):
        return False
    with open(PASS_HASH_FILE, 'rb') as f:
        enc = f.read()
        try:
            pwds = pickle.loads(decrypt(enc))
            return input_pwd == pwds[idx]
        except Exception:
            return False
def save_passwords(pwds):
    with open(PASS_HASH_FILE, 'wb') as f:
        f.write(encrypt(pickle.dumps(pwds)))
def load_passwords():
    if not os.path.exists(PASS_HASH_FILE):
        return []
    with open(PASS_HASH_FILE, 'rb') as f:
        enc = f.read()
        try:
            return pickle.loads(decrypt(enc))
        except Exception:
            return []
def load_data():
    data_file = os.path.join(BASE_DIR, 'data', 'rcdata.dat')
    if not os.path.exists(data_file):
        return []
    with open(data_file, 'rb') as f:
        enc = f.read()
        try:
            return pickle.loads(decrypt(enc))
        except Exception:
            return []
def save_data(data):
    data_file = os.path.join(BASE_DIR, 'data', 'rcdata.dat')
    with open(data_file, 'wb') as f:
        f.write(encrypt(pickle.dumps(data)))
def load_location_map():
    if hasattr(load_location_map, 'location_map'):
        return load_location_map.location_map
    location_map = {}
    csv_path = os.path.join(os.path.dirname(BASE_DIR), '6699.csv')
    if os.path.exists(csv_path):
        with open(csv_path, 'r', encoding='utf-8') as f:
            for line in f:
                parts = line.strip().split(',')
                for i in range(0, len(parts)-1, 2):
                    code = parts[i].strip()
                    name = parts[i+1].strip()
                    if code and name:
                        location_map[code] = name
    load_location_map.location_map = location_map
    return location_map
def get_location_name(code: str):
    location_map = load_location_map()
    for length in (6, 4, 2):
        if len(code) >= length:
            name = location_map.get(code[:length])
            if name:
                return name
    return code
def get_person_info(id_number: str):
    if len(id_number) == 18:
        birth = id_number[6:14]
        birth_date = f"{birth[:4]}-{birth[4:6]}-{birth[6:8]}"
        try:
            age = datetime.now().year - int(birth[:4])
        except:
            age = ''
        location_code = id_number[:6]
        location = get_location_name(location_code)
        return birth_date, location, age
    return '', '', ''