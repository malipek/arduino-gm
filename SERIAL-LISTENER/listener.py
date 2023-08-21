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
    url = os.environ.get('URL')
    if url:
        response = requests.get(url)
        if response.status_code == 200:
            data = response.text.strip()
            data = data.strip('ï»¿')
            data_json = json.loads(data)
            decoded_bytes = decoded_bytes.replace('}', '')
            decoded_bytes = decoded_bytes + ',"temp2":'+data_json[0]['temp2m']
            decoded_bytes = decoded_bytes + ',"precipitation":'+data_json[0]['precipitation']
            decoded_bytes = decoded_bytes + '}'
    client = boto3.client('lambda')
    response = client.invoke( FunctionName = "put-records", InvocationType = "RequestResponse", Payload = decoded_bytes)
    print(response['Payload'].read())
