import boto3
import requests
import serial
import os
import json
ser = serial.Serial('/dev/ttyACM0')
ser.flushInput()
while True:
    ser_bytes = ser.readline()
    decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
    url1 = os.environ.get('URL1')
    url2 = os.environ.get('URL2')
    if url1:
        try:
            response = requests.get(url1)
            if response.status_code == 200:
                data = response.text.strip()
                data = data.strip('ï»¿')
                data_json = json.loads(data)
                decoded_bytes = decoded_bytes.replace('}', '')
                decoded_bytes = decoded_bytes + ',"temp2":'+data_json[0]['temp2m']
                decoded_bytes = decoded_bytes + '}'
        except requests.exceptions.RequestException as e:
            print(e)
    if url2:
        try:
            headers = {'Content-Type': 'application/json'}
            response = requests.get(url2, headers=headers)
            if response.status_code == 200:
                data = response.text.strip()
                data = data.strip('ï»¿')
                data_json = json.loads(data)
                decoded_bytes = decoded_bytes.replace('}', '')
                decoded_bytes = decoded_bytes + ',"precipitation":'+str(data_json["status"]["precip"]['value'])
                decoded_bytes = decoded_bytes + '}'
        except requests.exceptions.RequestException as e:
            print(e)
    client = boto3.client('lambda')
    response = client.invoke( FunctionName = "put-records", InvocationType = "RequestResponse", Payload = decoded_bytes)
    print(decoded_bytes+'\n')
    print(response['Payload'].read())
