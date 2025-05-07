# utils.py
import os
import base64
import hashlib
import pickle
import sys
from datetime import datetime
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import padding

if getattr(sys, 'frozen', False):
    BASE_DIR = os.path.dirname(sys.executable)
else:
    BASE_DIR = os.path.dirname(__file__)

# AES加密
AES_KEY = hashlib.sha256(b'rc_key').digest()  # 32字节密钥
AES_IV = b'rc_iv_2024_12345'  # 16字节IV

def encrypt(data: bytes, key: bytes = AES_KEY, iv: bytes = AES_IV) -> bytes:
    padder = padding.PKCS7(128).padder()
    padded_data = padder.update(data) + padder.finalize()
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    ct = encryptor.update(padded_data) + encryptor.finalize()
    return base64.b64encode(ct)

def decrypt(data: bytes, key: bytes = AES_KEY, iv: bytes = AES_IV) -> bytes:
    ct = base64.b64decode(data)
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    decryptor = cipher.decryptor()
    padded_data = decryptor.update(ct) + decryptor.finalize()
    unpadder = padding.PKCS7(128).unpadder()
    return unpadder.update(padded_data) + unpadder.finalize()

# 密码校验
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

# 数据加载与保存
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

# 身份证号推算出生日期、地点、年龄（简化版）
def get_person_info(id_number: str):
    # 18位身份证
    if len(id_number) == 18:
        birth = id_number[6:14]
        birth_date = f"{birth[:4]}-{birth[4:6]}-{birth[6:8]}"
        try:
            age = datetime.now().year - int(birth[:4])
        except:
            age = ''
        # 地点可根据前6位查字典，这里简化
        location = id_number[:6]
        return birth_date, location, age
    return '', '', ''
