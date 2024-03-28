import base64

def base64_encode(data):
    encoded_bytes = base64.b64encode(data.encode('utf-8'))
    encoded_data = encoded_bytes.decode('utf-8')
    return encoded_data

def base64_decode(encoded_data):
    decoded_bytes = base64.b64decode(encoded_data.encode('utf-8'))
    decoded_data = decoded_bytes.decode('utf-8')
    return decoded_data

def main():
    input_data = "Hello, World!"  # 输入字符串
    encoded_data = base64_encode(input_data)
    print("Base64 Encoded Data:", encoded_data)

    decoded_data = base64_decode(encoded_data)
    print("Base64 Decoded Data:", decoded_data)

if __name__ == '__main__':
    main()